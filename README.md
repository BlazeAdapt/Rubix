# Rubix

A Rubik's Cube solver built using an **ESP32-CAM, computer vision, servos, and two different solving approaches**.

The ESP32-CAM scans the cube, converts the detected colors into a cube state, gets a solution, and then physically executes the moves using the servo mechanism.

## How it works

The ESP32-CAM scans the cube and uses the camera to figure out the colors of each sticker. From that, it builds the current cube state.

The cube can then be solved in two ways:

| Kociemba | F2L |
|---|---|
| Python-based | C-based |
| Two-phase algorithm | Custom F2L solver |
| Runs on the server | Standalone implementation |

Once a solution is generated, the ESP32 receives the moves and uses the servos to physically solve the cube.

## Two Solvers

The project currently has two different approaches to solving the cube.

### Kociemba

The main solver uses the **Kociemba two-phase algorithm**. The cube state is sent from the ESP32 to a Python server, which calculates a solution and sends the moves back.

### F2L

`f2l_solve.c` contains a **custom F2L-based solver written in C**.

Instead of searching for a solution using Kociemba, it approaches the cube by solving the cross and then inserting the four F2L pairs.

The F2L solver is kept separate so it can be developed and tested independently, with the eventual possibility of running the solving process locally.

## 🔧 Hardware

- **ESP32-CAM** — camera, Wi-Fi and main controller
- **OV2640** — captures the cube
- **2 servos** — physically manipulate the cube
- **3×3 Rubik's Cube**

The ESP32 handles the vision, networking and movement. The current servo setup uses GPIO **13** and **15**.

## 📷 Computer Vision

The ESP32-CAM captures the cube and uses **HSV-based color detection** to identify the stickers.

```text
Image -> Sticker detection -> Color classification -> Cube state -> Solver
```

## Project Structure

```text
Rubix/
├── server/
│   └── ...              # Kociemba solver
│
├── rubix_esp.ino        # ESP32-CAM firmware
├── f2l_solve.c          # Custom F2L solver
└── README.md
```

## $Tech

**ESP32-CAM · C/C++ · Python · OpenCV/Computer Vision · Kociemba · F2L · Servos · Wi-Fi**



### Built to make a machine that can **see → solve → physically solve** a Rubik's Cube.

**[GitHub →](https://github.com/BlazeAdapt/Rubix)**
