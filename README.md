# 🐍 Snake Game

A classic Snake game written in **C++** that runs directly in the Windows console

## Controls

| Key | Action |
|-----|--------|
| `W` | Move Up |
| `S` | Move Down |
| `A` | Move Left |
| `D` | Move Right |
| `ESC` | Quit game |
| `ENTER` | Restart (on Game Over screen) |

## Features

- **Colorful display** — yellow head, green body, red food, cyan walls
- **Score system** — earn +10 points for each food eaten
- **Level progression** — every 50 points raises your level
- **Increasing speed** — the snake moves faster as you level up
- **Self-collision detection** — the game ends if the snake bites itself
- **Wall wrap-around** — the snake passes through walls and appears on the other side
- **Start screen** — press any key to begin
- **Game Over screen** — choose to play again or quit
- **Responsive layout** — adapts when the terminal is resized

## Build & Run

### Requirements
- Windows OS
- A C++ compiler with Windows API support (e.g. **MinGW/GCC** or **MSVC**)

### Compile with GCC (MinGW)
```bash
git clone https://github.com/reikfowo17/Snake_Game.git
g++ Snake.cpp -o SnakeGame.exe
./SnakeGame.exe
```

### Compile with MSVC (Developer Command Prompt)
```bash
cl Snake.cpp /Fe:SnakeGame.exe
SnakeGame.exe
```

## Display

| Symbol | Meaning |
|--------|---------|
| `O`    | Snake head |
| `o`    | Snake body |
| `*`    | Food |
| `#`    | Wall border |

## Project Structure

```
Snake_Game/
├── Snake.cpp    # Main source file
└── README.md    # This file
```