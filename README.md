# ATmega32 Two-Axis Laser Engraver Controller

Embedded firmware and Proteus simulation of a **2-axis (X/Y) laser engraving machine** built around an **ATmega32** microcontroller.
The user defines up to five geometric shapes through a 4×4 keypad and a 128×64 graphic LCD; the firmware stores them in EEPROM, rasterizes them in integer/step space, and drives two stepper motors and a laser module to trace each shape, while mirroring the laser path on the GLCD in real time.

> **Final project of the Microprocessors course — University of Kashan (2023).**
> Author: **Sina Mozaffari Rad**

---

## Highlights

- **Bare-metal C on an 8-bit AVR** (ATmega32 @ 8 MHz, CodeVisionAVR) — direct register-level control of every peripheral, no RTOS.
- **Hardware/software co-design**: the same firmware image (`PROJECT.hex`) runs inside a full Proteus schematic with the MCU, steppers, H-bridge drivers, keypad, GLCD and laser.
- **Classic rasterization algorithms implemented for motion control**, where each pixel is a physical motor step:
  - **Bresenham's line algorithm** for lines,
  - **Midpoint (Bresenham) circle algorithm** with 8-way octant symmetry for circles,
  - **Parametric polar interpolation** (`atan2`, `sin`, `cos`) for circular sectors (arcs).
- **Stepper sequencing in software**: per-axis phase tables for forward/reverse rotation, phase continuity across moves, and step timing derived from a user-configurable **RPM**.
- **Non-volatile job storage**: shapes, work-table size and motor speed live in **EEPROM** and survive power cycles.
- **Defensive input validation**: every shape is bounds-checked against the configured table size before the head moves (out-of-range points, radius overflow, degenerate rectangles).
- **Menu-driven HMI** on a KS0108 GLCD with a scanned matrix keypad (row/column reversal technique, debounced by wait-for-release).

---

## System Architecture

```
                 ┌────────────────────────────┐
  4x4 Keypad ───►│ PORTC   (row/col scanning) │
                 │                            │
                 │          ATmega32          │── PORTA[7:0] ──► KS0108 GLCD data bus
                 │          8 MHz             │── PORTB[5:0] ──► GLCD control (E, R/W, RS, /RST, CS1, CS2)
                 │                            │── PORTB7     ──► Laser (LED in simulation)
                 │  EEPROM: shapes + config   │── PORTD[3:0] ──► L293D ──► X-axis stepper
                 │                            │── PORTD[7:4] ──► L293D ──► Y-axis stepper
                 └────────────────────────────┘
```

### Pin Map

| Port / Pin | Direction | Function |
|---|---|---|
| `PORTA[7:0]` | Out | GLCD data bus DB0–DB7 |
| `PB0` | Out | GLCD **E** |
| `PB1` | Out | GLCD **RD/WR** |
| `PB2` | Out | GLCD **RS** |
| `PB3` | Out | GLCD **/RST** |
| `PB4` / `PB5` | Out | GLCD **CS1** / **CS2** (two KS0108 halves) |
| `PB7` | Out | Laser enable |
| `PORTC[3:0]` / `PORTC[7:4]` | In/Out (swapped while scanning) | 4×4 keypad rows / columns |
| `PORTD[3:0]` | Out | X-axis stepper coils (through L293D) |
| `PORTD[7:4]` | Out | Y-axis stepper coils (through L293D) |

GLCD controller configuration in CodeVisionAVR:

![GLCD pin configuration](docs/glcd-pin-config.png)

### Simulation Components (Proteus)

| Component | Proteus model | Role |
|---|---|---|
| Microcontroller | `ATMEGA32` | Main controller, runs `Debug/Exe/PROJECT.hex` |
| Display | 128×64 GLCD with dual **KS0108** controllers | User interface + live laser-path preview |
| Keypad | `KEYPAD-SMALLCALC` (4×4) | Data entry and navigation |
| Motor drivers | **L293D** dual H-bridge (×2) | Coil drivers for the steppers |
| Motors | `BISTEPPER` (×2) | X and Y axis actuators |
| Laser | Green LED | Visual stand-in for the laser module |

---

## Operating Modes

On power-up the GLCD asks for a mode (`1`–`3`):

### Mode 1 — Job Editor
Lists five shape slots (`not defined`, `line`, `rectangle`, `circle`, `circular sector`).
Selecting a slot shows its stored parameters and allows editing; an empty slot goes straight to definition.

| Shape | Parameters |
|---|---|
| Line | start `(x1, y1)`, end `(x2, y2)` |
| Rectangle | opposite corners `(x1, y1)`, `(x2, y2)` |
| Circle | center `(x, y)`, radius `r` |
| Circular sector | center `(x, y)`, start point `(x1, y1)`, end point `(x2, y2)` |

### Mode 2 — Machine Configuration
Displays and edits the **work-table size** (X × Y, default 128 × 64 to match the GLCD) and the **stepper speed in RPM** (default 60).

### Mode 3 — Run Job
Executes all defined shapes in order. For each shape the head performs a rapid move to the start point, the laser is enabled, and the contour is traced step by step. Every lit position is also drawn on the GLCD (`y` is flipped so the origin is at the bottom-left, like a machine table). Press **ON/C** to return to the menu.

### Keypad Conventions

| Key | Meaning |
|---|---|
| `0`–`9` | Digits / menu choices |
| `=` | Confirm numeric entry |
| `+` | Edit / Yes |
| `−` | No / Edit RPM (in Mode 2) |
| `ON/C` | Back / Exit current mode |

---

## Implementation Details

### EEPROM Data Layout

All persistent state is a single `eeprom char data[38]` array:

| Offset | Content |
|---|---|
| `7·i + 0` | Type of shape *i* (`0` = none, `1` line, `2` rectangle, `3` circle, `4` sector), *i* = 0…4 |
| `7·i + 1 … 7·i + 6` | Up to six coordinate bytes for shape *i* |
| `35` | Table width (X) |
| `36` | Table height (Y) |
| `37` | Stepper speed (RPM) |

### Stepper Motor Control

Each axis uses a 4-entry coil-energizing table for each direction. Before a move, the firmware reads the current coil state back from `PORTD` to find its position in the sequence, so consecutive moves continue from the correct phase instead of jumping. Step timing is derived from the configured speed:

```
ms_per_revolution = 60 000 / RPM
ms_per_step       = ms_per_revolution / 4      (4 full steps per revolution model)
```

One motor step corresponds to one unit in the table coordinate system (one GLCD pixel).

### Shape Tracing

- **Line** — integer Bresenham: the axis with the larger delta steps every iteration; the decision variable `p` decides when the minor axis steps. No floating point in the inner loop.
- **Rectangle** — four axis-aligned edges traced in sequence, returning to the start corner.
- **Circle** — midpoint circle algorithm (`d = 3 − 2r`); for each computed `(x, y)` the head visits all eight symmetric octant points around the center and returns, so only one eighth of the circle is actually computed.
- **Circular sector** — radius is the distance from the center to the start point; start and end angles come from `atan2`, and the arc is sampled with an angular step of `Δθ / (2πr)` so consecutive samples are about one step apart. Works in both angular directions.

The head position (`xhead`, `yhead`) is tracked in software (open-loop), and all moves are relative to it.

---

## Repository Structure

```
.
├── PROJECT.c                 # Complete firmware source (CodeVisionAVR C)
├── PROJECT.prj               # CodeVisionAVR project (chip, clock, GLCD & memory settings)
├── Debug/Exe/
│   ├── PROJECT.hex           # Compiled flash image (loaded by the Proteus model)
│   └── PROJECT.eep           # EEPROM image
├── proteus/
│   └── TEST_PROJECT.pdsprj   # Proteus schematic & simulation
└── docs/
    └── glcd-pin-config.png   # KS0108 control-pin configuration
```

## Build and Simulate

**Requirements:** CodeVisionAVR 3.x, Proteus 8.x

1. Open `PROJECT.prj` in CodeVisionAVR and build (target: ATmega32, 8 MHz). The output goes to `Debug/Exe/PROJECT.hex`.
2. Open `proteus/TEST_PROJECT.pdsprj` in Proteus. The ATmega32 is already linked to `..\Debug\Exe\PROJECT.hex` by relative path, so a prebuilt image works without recompiling.
3. Start the simulation and use the on-screen keypad:
   - Mode `2` → check/adjust table size and RPM,
   - Mode `1` → define shapes,
   - Mode `3` → run the job and watch the steppers, laser LED and GLCD trace.

## Possible Extensions

- Timer-interrupt-driven step generation instead of blocking `delay_ms`, freeing the CPU during motion.
- Microstepping and acceleration/deceleration ramps.
- Limit switches for homing and closed-loop position correction.
- Receiving jobs over USART (e.g. a G-code subset) instead of keypad entry.

---

**Course:** Microprocessors — University of Kashan
**Tools:** C · AVR ATmega32 · CodeVisionAVR · Proteus 8
