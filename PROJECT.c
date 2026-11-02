/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : FINAL_PROJECT
Version : 
Date    : 6/29/2023
Author  : Sina Mozaffari Rad
Company : UOK
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>

// Graphic Display functions
#include <glcd.h>
#include <delay.h>
// Font used for displaying text
// on the graphic display
#include <font5x7.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Declare your global variables here
eeprom char data[38];
char xhead = 0;
char yhead = 0;
char headstate = 0;
int keypadfunction(void){
      char Keycode;
      char input = 0;
      DDRC = 0xF0;
      PORTC = 0x0F;
      Keycode = PINC | 0xF0;
      if(Keycode != 0xFF) {
        glcd_clear(); 
        DDRC = 0x00;
        DDRC = 0x0F;
        PORTC = 0xF0;
        Keycode = Keycode & (PINC | 0x0F);      
//COLLUMN 1          
                  if(Keycode == 0xEE){
                      input = 7;
                  }
                  if(Keycode == 0xED){
                      input = 4;
                  }
                  if(Keycode == 0xEB){
                      input = 1;
                  }
                  if(Keycode == 0xE7){
                      input = -1;
					    //ON/C
				
				  }
//COULLUMN 2
				  if(Keycode == 0xDE){
					  input = 8;
				  }
				  if(Keycode == 0xDD){
					  input =  5;
				  }
				  if(Keycode == 0xDB){
					  input =  2;
				  }
				  if(Keycode == 0xD7){
					  input =  0;
					 
				  }
//COLLUMN 3:
				  if(Keycode == 0xBE){
					  input = 9;
				  }
				  if(Keycode == 0xBD){
					  input = 6;
				  }
				  if(Keycode == 0xBB){
					  input = 3;
				  }
				  if(Keycode == 0xB7){
					  //result
				  }
			  
//COULLUMN 4:

				  if(Keycode == 0x7E){
					//we do not support divide function in this calculator
				  }
				  if(Keycode == 0x7D){
					//we do not support multiply function in this calculator
				  }
				  if(Keycode == 0x7B){
					  //subtract
                      input = -3;
				  }
				  if(Keycode == 0x77){
					  //add
                      input = -2;
				  }
                  while ((PINC | 0x0F) != 0xFF);
      } 
      return(input);
}
int keypadfunction2(void){
    char Keycode;
    char input = 0;
    char flag = 0 ; 
    char glcd_buffer[20];
    while(flag != 1) {      
      DDRC = 0xF0;
      PORTC = 0x0F;
      Keycode = PINC | 0xF0;
      if(Keycode != 0xFF) {  
        DDRC = 0x00;
        DDRC = 0x0F;
        PORTC = 0xF0;
        Keycode = Keycode & (PINC | 0x0F);      
//COLLUMN 1          
                  if(Keycode == 0xEE){
                      input = input * 10 + 7;
                  }
                  if(Keycode == 0xED){
                      input = input * 10  + 4;
                  }
                  if(Keycode == 0xEB){
                      input = input * 10 + 1;
                  }
                  if(Keycode == 0xE7){
					    //ON/C
				
				  }
//COULLUMN 2
				  if(Keycode == 0xDE){
					  input = input * 10 + 8;
				  }
				  if(Keycode == 0xDD){
					  input = input * 10 + 5;
				  }
				  if(Keycode == 0xDB){
					  input = input * 10 + 2;
				  }
				  if(Keycode == 0xD7){
					  input = input * 10 + 0;
					 
				  }
//COLLUMN 3:
				  if(Keycode == 0xBE){
					  input = input * 10 + 9;
				  }
				  if(Keycode == 0xBD){
					  input = input * 10 + 6;
				  }
				  if(Keycode == 0xBB){
					  input = input * 10 + 3;
				  }
				  if(Keycode == 0xB7){
                      flag = 1;
					  //result
				  }
			  
//COULLUMN 4:

				  if(Keycode == 0x7E){
					//we do not support divide function in this calculator
				  }
				  if(Keycode == 0x7D){
					//we do not support multiply function in this calculator
				  }
				  if(Keycode == 0x7B){
					  //subtract
				  }
				  if(Keycode == 0x77){
					  //add
				  }
                  while ((PINC | 0x0F) != 0xFF); 
      }
      sprintf(glcd_buffer,"%d",input);
	  glcd_outtextxy(0, 40,glcd_buffer); 
   }
   glcd_clear(); 
   return(input);
}
char intializeType(char index){
    char i = index;
    char input = 0; 
    char str[25]; 
    while(input > 4 || input < 1){
    sprintf(str,"ENTER type of item %d\n",i+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"(1:line)");
    glcd_outtextxy(0, 10,str);
    sprintf(str,"(2:rectangle)");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(3:circle)");
    glcd_outtextxy(0, 30,str);
    sprintf(str,"(4:circular sector)"); 
    glcd_outtextxy(0, 40,str); 
    input = keypadfunction();
    }
    glcd_clear();  
    return(input);
}    
void editItems(char index, char type){
    char i = index; 
    int input2 = 0;
    char signed input = -1; 
    char str[25];  
    glcd_clear(); 
    if(type == 0){ 
        data[7*(i)] = intializeType(i);
    }
    else{
        while(input > -2  || input < -3) {
            sprintf(str,"Do you want to change\ntype of item?\n(yes : + / no : -)");
            glcd_outtextxy(0, 0,str);                                
            input = keypadfunction();
        }
        if(input == -2){
                data[7*(i)] = intializeType(i); 
            }

    }
    
    if(data[7*(i)] == 1 || data[7*(i)] == 2){
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER x1 of (x1,y1)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+1] = input2; 
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER y1 of (x1,y1)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    } 
    data[(7*(i))+2] = input2;   
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER x2 of (x2,y2)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    } 
    data[(7*(i))+3] = input2;
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER y2 of (x2,y2)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+4] = input2;
    glcd_clear(); 
    }  
                      
    else if(data[7*(i)] == 3){ 
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER x center(x,y)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+1] = input2;
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER y center(x,y)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+2] = input2;
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER r of circle\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+3] = input2;
    glcd_clear();   
    }
                      
    else if(data[7*(i)] == 4){ 
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER x center(x,y)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+1] = input2;
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER y center(x,y)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+2] = input2;
    glcd_clear();
    input2 = -1; 
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER x1 of (x1,y1)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+3] = input2; 
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER y1 of (x1,y1)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    } 
    data[(7*(i))+4] = input2;   
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER x2 of (x2,y2)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    } 
    data[(7*(i))+5] = input2;
    glcd_clear();
    input2 = -1;
    while(input2 > 255 || input2 < 0){
    sprintf(str,"ENTER dimensions of\nitem %d\n",(i)+1);
    glcd_outtextxy(0, 0,str);
    sprintf(str,"ENTER y2 of (x2,y2)\n");
    glcd_outtextxy(0, 20,str);
    sprintf(str,"(= : ENTER)");
    glcd_outtextxy(0, 30,str);
    input2 = keypadfunction2(); 
    }
    data[(7*(i))+6] = input2;
    glcd_clear();
    }
    sprintf(str,"SAVING DATA...");
    glcd_outtextxy(0, 40,str);
    delay_ms(1000);
    glcd_clear();
}

void showItems(char i,char type){
    char str[20];
    char index = i;
    signed char input = 0;
    if(type == 1){   //line
        while(input > -1 || input < -2){ 
        sprintf(str,"item %d)line\n",index+1);
        glcd_outtextxy(0, 0,str);   
        sprintf(str,"(x1 =%d,y1 =%d)",data[7*index+1],data[7*index+2]);
        glcd_outtextxy(0, 10,str);
        sprintf(str,"(x2 =%d,y2 =%d)",data[7*index+3],data[7*index+4]);
        glcd_outtextxy(0, 20,str);
        sprintf(str,"EDIT(+ on keypad)");
        glcd_outtextxy(0, 30,str);
        sprintf(str,"Return to list items\n(ON/C)");
        glcd_outtextxy(0, 40,str);
        input = keypadfunction(); 
        }
                        
        if(input == -2) {   
            editItems(index,type);     
        }
    } 
    
    if(type == 2){   //rectangle
        while(input > -1 || input < -2){ 
        sprintf(str,"item %d)rectangle\n",index+1);
        glcd_outtextxy(0, 0,str);   
        sprintf(str,"(x1 =%d,y1 =%d)",data[7*index+1],data[7*index+2]);
        glcd_outtextxy(0, 10,str);
        sprintf(str,"(x2 =%d,y2 =%d)",data[7*index+3],data[7*index+4]);
        glcd_outtextxy(0, 20,str);
        sprintf(str,"EDIT(+ on keypad)");
        glcd_outtextxy(0, 30,str);
        sprintf(str,"Return to list items\n(ON/C)");
        glcd_outtextxy(0, 40,str);
        input = keypadfunction(); 
        }
                        
        if(input == -2) {   
            editItems(index,type);     
        }
    }

    if(type == 3){   //circle
        while(input > -1 || input < -2){ 
        sprintf(str,"item %d)circle\n",index+1);
        glcd_outtextxy(0, 0,str);   
        sprintf(str,"center(x=%d,y=%d)",data[7*index+1],data[7*index+2]);
        glcd_outtextxy(0, 10,str);
        sprintf(str,"radius = %d",data[7*index+3]);
        glcd_outtextxy(0, 20,str);
        sprintf(str,"EDIT(+ on keypad)");
        glcd_outtextxy(0, 30,str);
        sprintf(str,"Return to list items\n(ON/C)");
        glcd_outtextxy(0, 40,str);
        input = keypadfunction(); 
        }
                        
        if(input == -2) {   
            editItems(index,type);     
        } 
    }
    if(type == 4){   //circular sector
        while(input > -1 || input < -2){ 
        sprintf(str,"item%d)circular sector\n",index+1);
        glcd_outtextxy(0, 0,str);   
        sprintf(str,"center(x=%d,y=%d)",data[7*index+1],data[7*index+2]);
        glcd_outtextxy(0, 10,str);
        sprintf(str,"start(x1=%d,y1=%d)",data[7*index+3],data[7*index+4]);
        glcd_outtextxy(0, 20,str);
        sprintf(str,"end(x2=%d,y2=%d)",data[7*index+5],data[7*index+6]);     
        glcd_outtextxy(0, 30,str);
        sprintf(str,"EDIT(+ on keypad)");
        glcd_outtextxy(0, 40,str);
        sprintf(str,"Return to list items\n(ON/C)");
        glcd_outtextxy(0, 50,str);
        input = keypadfunction(); 
        }
                        
        if(input == -2) {   
            editItems(index,type);     
        } 
    }           
}
float calculateDelay(char R){
    char RPM = R;
    float SPR = 60.00/(RPM);   //seconds per revolution 
    float MPR = SPR * 1000;
    return (MPR);  //miliseconds per revolution
}

void moveStepperX(char s,signed char dir) {  //Rightward move of stepper mottor = Forward on x-asis
  char i = 0;                                   //Leftward move of stepper mottor = Backward on x-asis
  float delay = calculateDelay(data[37]);//data[37] = RPM
  char steps = s;
  signed char direction = dir;
  char start = 0;
  char pattern1[4] = {
  0b00000010,  //step1
  0b00000100,  //step2
  0b00001000,  //step3 
  0b00000001   //step4
  };
  char pattern2[4] = {
  0b00000100,  //step 1
  0b00000010,  //step 2
  0b00000001,  //step 3
  0b00001000   //step 4
  };
  for (i = 0; i < 4 ; i++) {
      if(((PORTD & 0x0F) == pattern1[i]) && (direction == 1)){
            start = i;
      }
      if(((PORTD & 0x0F) == pattern2[i]) && (direction == -1)){
            start = i;
      } 
  }
  for (i = 0; i < steps; i++) {
      start++;
      if(direction == 1) {
        PORTD = (PORTD & 0xF0) + pattern1[start%4];
      }
      if(direction == -1){
        PORTD = (PORTD & 0xF0) + pattern2[start%4];  
      }
      delay_ms(delay / 4.00); //we assume that stepper motor angle is 90 and steps per revolution is 4
    }
}

void moveStepperY(char s, signed char dir) { //Rightward move of stepper mottor = Forward on y-asis
  char i = 0;                                   //Leftward move of stepper mottor = Backward on y-asis
  float delay = calculateDelay(data[37]);//data[37] = RPM 
  char steps = s;
  signed char direction = dir;  
  char start = 0;
  char pattern1[4] = {
  0b00100000,  //step1
  0b01000000,  //step2
  0b10000000,  //step3 
  0b00010000   //step4
  };
  char pattern2[4] = {
  0b01000000,  //step 1
  0b00100000,  //step 2
  0b00010000,  //step 3
  0b10000000   //step 4
  };
  for (i = 0; i < 4 ; i++) {
      if(((PORTD & 0xF0) == pattern1[i]) && (direction == 1)){
            start = i;
      }
      if(((PORTD & 0xF0) == pattern2[i]) && (direction == -1)){
            start = i;
      } 
  }
  for (i = 0; i < steps; i++) {
      start++;
      if(direction == 1) {
        PORTD = (PORTD & 0x0F) + pattern1[start%4];
      }
      if(direction == -1){
        PORTD = (PORTD & 0x0F) + pattern2[start%4];  
      }
      delay_ms(delay / 4.00); //we assume that stepper motor angle is 90 and steps per revolution is 4
    }
}

void glcd_laser(void) {
    if(headstate == 1)
    {
        glcd_setpixel(xhead,63-yhead);
    }
}
void lineFunction(char in){ 
    char index = in;
    int dx = data[(index*7)+3] - data[(index*7)+1];
    int dy = data[(index*7)+4] - data[(index*7)+2];
    int stepsX = abs(dx);
    int stepsY = abs(dy);
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    int p =0; 
    char i = 0;
    char str[20];
    if( data[(index*7)+3]> data[35] ||  data[(index*7)+1] > data[35] || data[(index*7)+4] > data[36] ||  data[(index*7)+2] > data[36]) {
        sprintf(str,"ERROR!\nLine dots are out of tabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
    }    
    if(xhead < data[(index*7)+1]) {   //x1
        moveStepperX((data[(index*7)+1] - xhead),1);
        xhead += (data[(index*7)+1] - xhead); 
    }
    else{
        moveStepperX(xhead - data[(index*7)+1],-1);
        xhead -= (xhead - data[(index*7)+1]);
    }
    if(yhead < data[(index*7)+2]) {   //y1
        moveStepperY(data[(index*7)+2] - yhead,1);
        yhead += (data[(index*7)+2] - yhead); 
    }
    else{
        moveStepperY(yhead - data[(index*7)+2],-1);
        yhead -= (yhead - data[(index*7)+2]);
    }
    //TURNING Laser ON  
    delay_ms(2000);
    PORTB.7 = 1;
    if (stepsX > stepsY) {
        p = 2 * stepsY - stepsX;
        for (i = 0; i < stepsX; i++) {
            moveStepperX(1, stepX);
            if (p >= 0) {
                moveStepperY(1, stepY);
                p = p - 2 * stepsX;
                yhead += stepY;
            }
            p = p + 2 * stepsY;
            xhead += stepX;
            headstate = 1; //turn on the laser on (x1,y1)
            glcd_laser();
            headstate = 0;
        }
    }     
    else {
        p = 2 * stepsX - stepsY;
        for (i = 0; i < stepsY; i++) {
            moveStepperY(1, stepY);
            if (p >= 0) {
                moveStepperX(1, stepX);
                p = p - 2 * stepsY; 
                xhead += stepX;
            }
            p = p + 2 * stepsX;
            yhead += stepY;
            headstate = 1; //turn on the laser on (x1,y1)
            glcd_laser();
            headstate = 0;
        }
    }
    PORTB.7 = 0;
}

void rectangleFunction(char in){
    char index = in;
    int dx = data[(index*7)+3] - data[(index*7)+1];
    int dy = data[(index*7)+4] - data[(index*7)+2];
    int stepsX = abs(dx);
    int stepsY = abs(dy);
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    char i = 0;
    char str[20];
    if(data[(index*7)+3]> data[35] ||  data[(index*7)+1] > data[35] || data[(index*7)+4] > data[36] ||  data[(index*7)+2] > data[36]) {
        sprintf(str,"ERROR!\nRecangle dots are out of tabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
    }
    if(data[(index*7)+3] == data[(index*7)+1] || data[(index*7)+4] ==  data[(index*7)+2]) {
        sprintf(str,"ERROR!\nRecangle dots are in same x-asis oy y-asis!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
    }
    
    if(xhead < data[(index*7)+1]) {   //x1
        moveStepperX((data[(index*7)+1] - xhead),1);
        xhead += (data[(index*7)+1] - xhead); 
    }
    else{
        moveStepperX(xhead - data[(index*7)+1],-1);
        xhead -= (xhead - data[(index*7)+1]);
    }
    if(yhead < data[(index*7)+2]) {   //y1
        moveStepperY(data[(index*7)+2] - yhead,1);
        yhead += (data[(index*7)+2] - yhead); 
    }
    else{
        moveStepperY(yhead - data[(index*7)+2],-1);
        yhead -= (yhead - data[(index*7)+2]);
    }
    //TURNING Laser ON  
    delay_ms(2000);
    PORTB.7 = 1;

    for (i = 0; i < stepsX; i++) {
            moveStepperX(1, stepX);
            xhead += stepX;
            headstate = 1; //turn on the laser 
            glcd_laser();
            headstate = 0; 
    }   
    
    for (i = 0; i < stepsY; i++) {
            moveStepperY(1, stepY);
            yhead += stepY;
            headstate = 1; //turn on the laser
            glcd_laser();
            headstate = 0;
    }
    
    for (i = 0; i < stepsX; i++) {
            moveStepperX(1, (-1*stepX));
            xhead += (-1*stepX);
            headstate = 1; //turn on the laser 
            glcd_laser();
            headstate = 0; 
    }
    for (i = 0; i < stepsY; i++) {
            moveStepperY(1, (-1*stepY));
            yhead += (-1*stepY);
            headstate = 1; //turn on the laser
            glcd_laser();
            headstate = 0;
    }
    PORTB.7 = 0; 
           
}
void Octants(char x,char y) {
    
    // Plot pixels in all eight octants 
    //octant 1 
    moveStepperX(x, 1);  
    xhead += x;
    moveStepperY(y, 1);
    yhead += y;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    yhead -= y;
    moveStepperY(y, -1);
    
    //octant 2
    moveStepperY(y, -1);
    yhead -= y;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    xhead -= x; 
    moveStepperX(x, -1);
     
    //octant 3
    moveStepperX(x, -1); 
    xhead -= x;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    yhead += y;
    moveStepperY(y,  1);
    
    //octant 4
    moveStepperY(y, 1);
    yhead += y;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    xhead += x; //recenter head of laser
    yhead -= y;
    moveStepperX(x,  1);
    moveStepperY(y, -1);
    
    //octant 5
    moveStepperX(y, 1);  
    xhead += y;
    moveStepperY(x, 1);
    yhead += x;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    xhead -= y; 
    moveStepperY(x, -1);
    
    //octant 6
    moveStepperX(y, -1); 
    xhead -= y;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    yhead -= x;
    moveStepperY(x, -1);
    
    //octant 7
    moveStepperY(x, -1);
    yhead -= x;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    xhead += y; 
    moveStepperX(y,  1);
    
    //octant 8
    moveStepperX(y, 1); 
    xhead += y;
    headstate = 1; //turn on the laser 
    PORTB.7 = 1;
    glcd_laser();
    headstate = 0;
    PORTB.7 = 0;
    xhead -= y; //recenter head of laser
    yhead += x;
    moveStepperX(y, -1);
    moveStepperY(x,  1);
    
 }
void circleFunction(char in){ 
  char index = in;
  char x = 0;
  char y = data[(index*7)+3]; //radius
  int decision = 3 - 2 * data[(index*7)+3]; //radius 
  char str[20]; 
  if( data[(index*7)+1] > data[35] ||  data[(index*7)+2] > data[36]) {
        sprintf(str,"ERROR!\nCenter dot is out of tabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
  }
  if(data[(index*7)+1] + data[(index*7)+3] > data[35] || data[(index*7)+1] - data[(index*7)+3] < 0 || data[(index*7)+2] + data[(index*7)+3] > data[36] || data[(index*7)+2] - data[(index*7)+3] < 0) {
        sprintf(str,"ERROR!\nRadius is out of\ntabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
    }  
  if(xhead < data[(index*7)+1]) {   //x1
        moveStepperX((data[(index*7)+1] - xhead),1);
        xhead += (data[(index*7)+1] - xhead); 
    }
  else{
        moveStepperX(xhead - data[(index*7)+1],-1);
        xhead -= (xhead - data[(index*7)+1]);
  }
  if(yhead < data[(index*7)+2]) {   //y1
        moveStepperY(data[(index*7)+2] - yhead,1);
        yhead += (data[(index*7)+2] - yhead); 
  }
  else{
        moveStepperY(yhead - data[(index*7)+2],-1);
        yhead -= (yhead - data[(index*7)+2]);
  }
    
  while (y >= x) {
    Octants(x, y);

    if (decision < 0) {
          decision += 4 * x + 6;
    } 
    else {
      decision += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }

  PORTB.7 = 0;
  
} 

void moveToPosition(char x, char y) {
    int stepsX = x - xhead;
    int stepsY = y - yhead;

    if (stepsX > 0) {
        moveStepperX(stepsX, 1);
        xhead += stepsX;
        
    } else if (stepsX < 0) {
        moveStepperX(-stepsX, -1);
        xhead += stepsX;
    }

    if (stepsY > 0) {
        moveStepperY(stepsY, 1);
        yhead += stepsY;
    } else if (stepsY < 0) {
        moveStepperY(-stepsY, -1);
        yhead += stepsY;
    }   
    glcd_laser();
}

void circularsectorFunction(char in){
    char index = in;
    char x1 = data[(index*7)+1];
    char y1 = data[(index*7)+2];
    char x2 = data[(index*7)+3];
    char y2 = data[(index*7)+4];
    char x3 = data[(index*7)+5];
    char y3 = data[(index*7)+6];
    int radius = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    float startAngle = atan2(y2 - y1, x2 - x1);
    float endAngle = atan2(y3 - y1, x3 - x1);
    float angle;
    int x = 0;
    int y =0; 
    int num_steps = 2 * PI * radius;
    char str[20];    
    float angle_step;
    angle_step = (endAngle - startAngle) / num_steps;
    angle = startAngle; 
      
    if( data[(index*7)+1] > data[35] ||  data[(index*7)+2] > data[36]) {
        sprintf(str,"ERROR!\nCenter dot is out of tabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
    }
    if( data[(index*7)+3] > data[35] ||  data[(index*7)+4] > data[36] ||  data[(index*7)+5] > data[35] ||  data[(index*7)+6] > data[36]) {
        sprintf(str,"ERROR!\nStart or End dot\nis out of tabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
    }
    if(x1 + radius > data[35] || x1 - radius < 0 || y1 + radius > data[36] || y1 - radius < 0) {
        sprintf(str,"ERROR!\nRadius is out of\ntabel range!");
        glcd_outtextxy(0, 0,str);
        delay_ms(1000);
        glcd_clear();
        return;
     }
     // start position
    if(xhead < data[(index*7)+3]) {   //x2
        moveStepperX((data[(index*7)+3] - xhead),1);
        xhead += (data[(index*7)+3] - xhead); 
    }
    else{
        moveStepperX(xhead - data[(index*7)+3],-1);
        xhead -= (xhead - data[(index*7)+3]);
    }
    if(yhead < data[(index*7)+4]) {   //y2
        moveStepperY(data[(index*7)+4] - yhead,1);
         yhead += (data[(index*7)+4] - yhead); 
    }
    else{
        moveStepperY(yhead - data[(index*7)+4],-1);
        yhead -= (yhead - data[(index*7)+4]);
    }
          
    //starting move on sector of circle
    if(angle <= endAngle) {
    while (angle <= endAngle) { 
        x = x1 + radius * cos(angle);
        y = y1 + radius * sin(angle);

         
        PORTB.7 = 1;
        headstate = 1;
        moveToPosition(x, y); 
        headstate = 0;
        PORTB.7 = 0;
        
        angle += angle_step; 
    }
    }
    else{
    while (angle >= endAngle) {
        x = x1 + radius * cos(angle);
        y = y1 + radius * sin(angle);

         
        PORTB.7 = 1;
        headstate = 1;
        moveToPosition(x, y); 
        headstate = 0;
        PORTB.7 = 0;
        
        angle += angle_step; 
    }
    }
}




    


void main(void)
{
// Declare your local variables here
char start[30];
char str[30];
char Keycode;
signed char input = 0;
char input2 = 0;
char i = 0;
char flag =0;

// Variable used to store graphic display
// controller initialization data
GLCDINIT_t glcd_init_data;

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P 
PORTC=(1<<PORTC7) | (1<<PORTC6) | (1<<PORTC5) | (1<<PORTC4) | (1<<PORTC3) | (1<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out  
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (1<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Graphic Display Controller initialization
// The KS0108 connections are specified in the
// Project|Configure|C Compiler|Libraries|Graphic Display menu:
// DB0 - PORTA Bit 0
// DB1 - PORTA Bit 1
// DB2 - PORTA Bit 2
// DB3 - PORTA Bit 3
// DB4 - PORTA Bit 4
// DB5 - PORTA Bit 5
// DB6 - PORTA Bit 6
// DB7 - PORTA Bit 7
// E - PORTB Bit 0
// RD /WR - PORTB Bit 1
// RS - PORTB Bit 2
// /RST - PORTB Bit 3
// CS1 - PORTB Bit 4
// CS2 - PORTB Bit 5

// Specify the current font for displaying text
glcd_init_data.font=font5x7;
// No function is used for reading
// image data from external memory
glcd_init_data.readxmem=NULL;
// No function is used for writing
// image data to external memory
glcd_init_data.writexmem=NULL;

glcd_init(&glcd_init_data);
delay_ms(200);
glcd_clear();

for (i = 0; i < 5; i++) {
    data[7 * i] = 0;  //at first no type 
    //data[0] =type item 1, data[7] = type item 2, data[14] = type item 3, data[21]= type item 4, data[28] =type item 5
  }
data[35] = 128;  //default x of table
data[36] = 64; //default y of table
data[37] = 60; //default RPM

while (1)
      {                    
      sprintf(start,"PLEASE ENTER THE MODE(1-3):");          
      glcd_outtextxy(0, 0,start);
      DDRC = 0xF0;
      PORTC = 0x0F;
	  Keycode = PINC | 0xF0;
	  if(Keycode != 0xFF) { 
        glcd_clear(); 
	    DDRC = 0x00;
		DDRC = 0x0F;
		PORTC = 0xF0;
		Keycode = Keycode & (PINC | 0x0F);      
//COLLUMN 1		  
				  if(Keycode == 0xEE){
					  input = 7;
				  }
				  if(Keycode == 0xED){
					  input = 4;
				  }
				  if(Keycode == 0xEB){
					  input = 1;
				  }
				  if(Keycode == 0xE7){
                      input = -1;
					    //ON/C
				
				  }
//COULLUMN 2
				  if(Keycode == 0xDE){
					  input = 8;
				  }
				  if(Keycode == 0xDD){
					  input =  5;
				  }
				  if(Keycode == 0xDB){
					  input =  2;
				  }
				  if(Keycode == 0xD7){
					  input =  0;
					 
				  }
//COLLUMN 3:
				  if(Keycode == 0xBE){
					  input = 9;
				  }
				  if(Keycode == 0xBD){
					  input = 6;
				  }
				  if(Keycode == 0xBB){
					  input = 3;
				  }
				  if(Keycode == 0xB7){
					  //result
				  }
			  
//COULLUMN 4:

				  if(Keycode == 0x7E){
					//we do not support divide function in this calculator
				  }
				  if(Keycode == 0x7D){
					//we do not support multiply function in this calculator
				  }
				  if(Keycode == 0x7B){
					  //subtract
				  }
				  if(Keycode == 0x77){
					  //add
				  }
      while ((PINC | 0x0F) != 0xFF); 
           
      if(input > 3 || input <= 0) {
        input = 0 ;
        sprintf(str,"You are not in range!(1-3)"); 
        glcd_outtextxy(0, 20,str);
      }
      
      else {        
      sprintf(str,"STARTING MODE %d ...",input); 
      glcd_outtextxy(0, 40,str);
      delay_ms(1000); 
      glcd_clear();
      }
     }
        
     if(input == 1){
      flag = 0;
      while(flag != 1){
        //mode1 
        input = 0;
        while(input > 5 || input < -1  || input == 0){ 
                sprintf(str,"Choose an item to \nedit(1-5).Exit(ON/C)\n"); 
                glcd_outtextxy(0, 0,str); 
                for(i = 0; i < 5; i++){ 
                    if (data[i * 7] == 0){ //not defined
                        sprintf(str,"%d)not defined",i+1);
                        glcd_outtextxy(0, 9*(i+2),str);
                    }
                    
                    else if (data[i * 7] == 1){ //line
                        sprintf(str,"%d)line",i+1);
                        glcd_outtextxy(0, 9*(i+2),str);
                    }    
                    
                    else if (data[i * 7] == 2){ //rectangle
                        sprintf(str,"%d)rectangle",i+1);
                        glcd_outtextxy(0, 9*(i+2),str);
                    }
                    
                    else if (data[i * 7] == 3){ //circle
                        sprintf(str,"%d)circle",i+1);
                        glcd_outtextxy(0, 9*(i+2),str);
                    }      
                    
                    else if (data[i * 7] == 4){ //circular sector
                        sprintf(str,"%d)circular sector ",i+1);
                        glcd_outtextxy(0, 9*(i+2),str); 
                    }
                }
                input = keypadfunction();
        }    
                if(input == -1) {
                    glcd_clear();
                    sprintf(str,"EXITING MODE 1...");
                    glcd_outtextxy(0, 40,str);
                    delay_ms(1000);
                    glcd_clear();
                    flag = 1;
                }
                else if(input == 1) {   //ITEM 1 show and edit
                    glcd_clear(); 
                    if(data[0] != 0){
                        showItems(0,data[0]);
                        glcd_clear();                     
                    }
                     
                    if(data[0] == 0){
                        editItems(0,data[0]); 
                    }

                }
                else if(input == 2) { //ITEM 2 show and edit
                    glcd_clear(); 
                    if(data[7] != 0){
                        showItems(1,data[7]);
                        glcd_clear();                     
                    }
                     
                    if(data[7] == 0){
                        editItems(1,data[7]); 
                    }
                }
                else if(input == 3) {  //ITEM 3 show and edit
                    glcd_clear(); 
                    if(data[14] != 0){
                        showItems(2,data[14]);
                        glcd_clear();                     
                    }
                     
                    if(data[14] == 0){
                        editItems(2,data[14]); 
                    }    
                }
                else if(input == 4) { //ITEM 4 show and edit
                    glcd_clear(); 
                    if(data[21] != 0){
                        showItems(3,data[21]);
                        glcd_clear();                     
                    }
                     
                    if(data[21] == 0){
                        editItems(3,data[21]); 
                    }   
                }
                else if(input == 5) { //ITEM 5 show and edit
                    glcd_clear(); 
                    if(data[28] != 0){
                        showItems(4,data[28]);
                        glcd_clear();                     
                    }
                     
                    if(data[28] == 0){
                        editItems(4,data[28]); 
                    }              
                }
        input = 0;
      } 
     }
      
      if(input == 2){
      //mode2
        input = 0; 
        flag = 0;
        while(flag != 1){
            while(input < -3 || input > -1  || input == 0){ //show table & RPM of stepper motors
                sprintf(str,"Table size:\n"); 
                glcd_outtextxy(0, 0,str); 
                sprintf(str,"x = %d , y = %d\n",data[35],data[36]); 
                glcd_outtextxy(0, 10,str);
                sprintf(str,"RPM = %d",data[37]); 
                glcd_outtextxy(0, 20,str);
                sprintf(str,"EDIT table(+)"); 
                glcd_outtextxy(0, 30,str);
                sprintf(str,"EDIT RPM(-)"); 
                glcd_outtextxy(0, 40,str);
                sprintf(str,"Exit(ON/C)"); 
                glcd_outtextxy(0, 50,str);    
                input = keypadfunction();
            } 
            
            if(input == -1) {
                glcd_clear();
                sprintf(str,"EXITING MODE 2...");
                glcd_outtextxy(0, 40,str);
                delay_ms(1000);
                glcd_clear();
                flag = 1;
            }
            glcd_clear();
            if(input == -2){ //table edit
                input2 = 0;
                while(input2 > 255 || input2 < 1) {
                    sprintf(str,"ENTER x of table\n(= : ENTER)"); 
                    glcd_outtextxy(0, 0,str);
                    input2 = keypadfunction2(); 
                }
                data[35] = input2;
                input2 = 0;
                glcd_clear();
                while(input2 > 255 || input2 < 1) {
                    sprintf(str,"ENTER y of table\n(= : ENTER)"); 
                    glcd_outtextxy(0, 0,str);
                    input2 = keypadfunction2(); 
                }
                data[36] = input2;   
            }   
        
            if(input == -3){ //RPM edit
                input2 = 0;
                while(input2 > 255 || input2 < 1) {
                    sprintf(str,"ENTER RPM\n(= : ENTER)"); 
                    glcd_outtextxy(0, 0,str);
                    input2 = keypadfunction2(); 
                }
                data[37] = input2; 
            } 
            input = 0;
        }
      } 
      
      if(input == 3) { 
      //mode3
          input = 0; 
          for(i = 0; i < 5; i++) { 
            if(data[i*7] == 1) { //line 
                lineFunction(i); 
            } 
            else if(data[i*7] == 2) { //rectangle
                rectangleFunction(i);
            }  
            else if(data[i*7] == 3) { //circle
                circleFunction(i);
            }  
            else if(data[i*7] == 4) { //circular sector
                circularsectorFunction(i);
            } 
          }
          while(input < -1 || input > -1  || input == 0)
                input = keypadfunction();   
          if(input == -1) {
                glcd_clear();
                sprintf(str,"EXITING MODE 3...");
                glcd_outtextxy(0, 40,str);
                delay_ms(1000);
                glcd_clear();
                flag = 1;
          }
      }
      
       
     
      
   }
}
