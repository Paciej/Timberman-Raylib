# Timberman (C++ / raylib)

A simple fast–paced 2D arcade game inspired by Timberman, written in C++ using the **raylib** library.[web:6][web:5]

You chop a tree as fast as you can while dodging branches, competing for the highest score on the built‑in leaderboard.[web:12][web:18]

---

## Screenshots

> Replace the paths below with actual image paths from your repository (for example: `assets/screenshots/main-menu.png`).

- **Main Menu**  
  ![Main Menu](Timberman/Resources/Assets/Screenshots/screenshot_main_menu.png)

- **In‑Game**  
  ![Gameplay](Timberman/Resources/Assets/Screenshots/screenshot_game.png)

- **Game Over Screen**  
  ![Game Over](Timberman/Resources/Assets/Screenshots/screenshot_death.png)

---

## Gameplay

- Chop the tree by pressing the control keys (left/right) to decide which side you stand on.
- Avoid incoming branches; if a branch hits the player, the run is over.
- A timer (or shrinking bar) forces you to keep chopping quickly to stay alive.
- Each successful chop increases your score; the game gradually becomes more difficult.

---

## Features

- **Background music** that loops during gameplay.
- **Sound effects** for chopping, warnings, and game over events.[web:9]
- Pixel‑art or simple 2D **assets** for player, tree, branches, and UI.[web:11]
- **Settings menu** for:
  - Volume levels (music / SFX).
  - Basic video or gameplay options (where applicable).
- **Leaderboard** storing best scores and showing top runs on a dedicated screen.

---

## Controls

- Move left: `←` (Left Arrow) or `A`
- Move right: `→` (Right Arrow) or `D`
- Confirm / Chop: same movement keys
- Back / Exit: `Esc`

(Adjust this section if your actual key bindings differ.)

---

## Tech Stack

- Language: C++
- Framework: raylib (2D rendering, input, audio)[web:6][web:5]
- Assets: custom sprites, bitmap fonts, and sound files loaded at runtime.[web:11]

---

## Getting Started

### Prerequisites

- C++17 or newer toolchain (GCC/Clang/MSVC).
- raylib installed on your system, or available as a submodule/prebuilt library.[web:11][web:4]

### Building

Update this section to match your project:

```bash
# Example for CMake-based project
git clone https://github.com/<your-username>/<your-repo>.git
cd <your-repo>
mkdir build && cd build
cmake ..
cmake --build .
