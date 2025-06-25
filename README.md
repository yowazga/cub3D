# 🎮 cub3D

> “My first RayCaster with MiniLibX” — a tribute to *Wolfenstein 3D* and the roots of modern FPS engines.

## 📌 Project Overview

**cub3D** is a 42 graphics project inspired by the iconic *Wolfenstein 3D*. The goal is to build a first-person view 3D maze using a technique called **raycasting**.

This project is an introduction to:
- Fundamental **graphics programming**
- 2D math & linear algebra
- Parsing `.cub` map files
- Building a **simple game engine** from scratch using **MiniLibX**

---

## 🧠 Learning Objectives

- Understanding how raycasting works (math + rendering)
- Reading and validating configuration and map files
- Handling user input (keyboard events)
- Implementing a smooth graphical experience (FPS-style movement)
- Structuring and optimizing large C codebases

---

## 🛠 Features

- ✅ First-person camera in a 3D world built from 2D maps
- ✅ Wall textures based on direction (N/S/E/W)
- ✅ Floor and ceiling coloring
- ✅ Smooth movement using `W`, `A`, `S`, `D` and rotation with arrow keys
- ✅ Clean exit on `ESC` or window close
- ✅ Map parsing with error handling and input validation

---

## 🎮 Controls

| Key        | Action                |
|------------|------------------------|
| `W`, `A`, `S`, `D` | Move forward/back/left/right |
| `←`, `→`   | Rotate view left/right |
| `ESC`      | Quit the game          |
| Red cross  | Window close (also quits) |

---
## 📄 .cub Map File Format
```bash
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
```
- **NO**, **SO**, **WE**, **EA**: paths to wall textures

- **F**: RGB floor color

- **C**: RGB ceiling color

- Map must be surrounded by **1**s (walls)

- Map must contain exactly one starting position: **N**, **S**, **E**, or **W**

## 🌟 Bonus Features

- ✅ Wall collision (player cannot walk through walls)

- ✅ Minimap showing the top-down view of the map

- ✅ Animated sprites or enemies

- ✅ Mouse look for rotation

- ✅ Door mechanics and secret passages
## 🧪 How to Run
```bash
make
./cub3D maps/example.cub
```
Make sure:

- The .cub file is valid

- Textures exist and are accessible

- MiniLibX is properly installed
