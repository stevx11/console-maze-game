# Labyrinth of Knossos

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)
![Build](https://img.shields.io/badge/build-Visual%20Studio%20%7C%20g%2B%2B-blueviolet)

A turn-based console maze game written in modern C++. Guide a robot through a procedurally generated labyrinth, collect power-ups, and escape before the Minotaur catches you.

The project focuses on **object-oriented design**, **manual memory management**, **procedural generation**, and **performance measurement**, organized into clearly separated modules.

```
# U # # # # # # # # # # # # #
# R . . . . . . . . . . # . #
# # # # # . # # # . # # # . #
# P . . . . # . # . . . . . #
# # # . # . # . # . # P # # #
# . . . # . . . # . # . . . #
# . . . # . # # # # # . # # #
# . . . # . . . # . # . . . #
# . # # # . # # # . # . # # #
# P # . . . . . . . . . . . #
# . # . # M # . # # # . # # #
# . . . . . # . # . # . . . #
# . # . # . # . # . # . # # #
# . # . # . # . . . . . . . #
# # # # # # # # # # I # # # #
Enter move (W/A/S/D):
```

## Features

- **Procedural maze generation**: every run produces a new labyrinth of any size from 15×15 upward, with randomized entry and exit points.
- **Enemy AI**: the Minotaur roams the maze and attacks when the robot is adjacent.
- **Power-up system** built on a polymorphic item hierarchy, with each effect lasting 3 turns:

  | Item   | Effect                                         |
  |--------|------------------------------------------------|
  | Sword  | Defeat the Minotaur on contact                 |
  | Shield | Survive an encounter with the Minotaur         |
  | Hammer | Break through walls                            |
  | Fog    | Limits visibility to a 3×3 area (a hazard)     |

- **Performance profiling**: generation time is measured with a high-resolution `std::chrono` timer and logged to `labyrinth_generation_log.txt`.
- **Session reporting**: each game's outcome (`WIN`, `LOSS`, `QUIT`) and the full final maze are appended to `game_session_log.txt`.
- **Input validation** for command-line arguments and player moves.

## Architecture

```
LavirintKnosos/
├── main.cpp                 # Entry point, argument parsing
├── game/
│   ├── Game.{h,cpp}         # Game loop, turn order, win/loss logic
│   ├── Robot.{h,cpp}        # Player movement, collisions, item pickup
│   └── Minotaur.{h,cpp}     # Enemy movement and combat resolution
├── labyrinth/
│   ├── Labyrinth.{h,cpp}    # Grid storage, rendering, fog-of-war view
│   └── Generator.{h,cpp}    # Static factory that builds and times a maze
├── items/
│   └── Items.h              # Abstract Item base, concrete items, PowerUpManager
└── utils/
    ├── Timer.{h,cpp}        # High-resolution timing
    └── Utils.{h,cpp}        # File I/O and report formatting
```

**Design highlights**

- **Separation of concerns**: maze data, generation, entities, and game flow each live in their own module.
- **Factory pattern**: `Generator::generate()` encapsulates the full build pipeline (walls → items → entry/exit) and its timing.
- **Polymorphism**: `Sword`, `Shield`, `Hammer`, and `Fog` derive from an abstract `Item` class with virtual `getEffect()` and `getType()`.
- **Encapsulated state**: `PowerUpManager` owns all power-up timers, keeping the `Robot` class focused on movement.
- **RAII-style cleanup**: the `Labyrinth` and `Game` destructors free the dynamically allocated grid, items, and entities.

## Getting Started

### Prerequisites

- A C++17 compiler (MSVC, g++, or clang++)
- Visual Studio 2022 (optional, a solution file is included)

### Build with Visual Studio

1. Open `LavirintKnosos/LavirintKnosos.sln`.
2. Choose the **Release | x64** configuration.
3. Build the solution (`Ctrl+Shift+B`).

### Build from the command line

```bash
cd LavirintKnosos
g++ -std=c++17 -O2 -o labyrinth main.cpp game/*.cpp labyrinth/*.cpp utils/*.cpp
```

## Usage

```bash
./labyrinth <rows> <columns> <number_of_items>
```

| Argument          | Constraint |
|-------------------|------------|
| `rows`            | ≥ 15       |
| `columns`         | ≥ 15       |
| `number_of_items` | ≥ 3        |

Example:

```bash
./labyrinth 25 40 10
```

### Controls

| Key | Action     |
|-----|------------|
| `W` | Move up    |
| `A` | Move left  |
| `S` | Move down  |
| `D` | Move right |
| `Q` | Quit       |

### Map legend

| Symbol | Meaning   |
|--------|-----------|
| `R`    | Robot (you) |
| `M`    | Minotaur  |
| `P`    | Item      |
| `#`    | Wall      |
| `.`    | Open path |
| `U`    | Entrance  |
| `I`    | Exit      |

## Performance

Generation is fast even for large mazes. Sample results from `labyrinth_generation_log.txt`:

| Size     | Cells  | Items | Generation time |
|----------|--------|-------|-----------------|
| 15×15    | 225    | 3     | 0.09 ms         |
| 50×50    | 2,500  | 25    | 0.43 ms         |
| 100×100  | 10,000 | 50    | < 1 ms          |

## Roadmap

- Guarantee solvability with a BFS path check after generation
- Smarter Minotaur pursuit using BFS or A* instead of random movement
- Replace raw pointers with `std::unique_ptr` and `std::vector`
- Cross-platform screen clearing (currently uses the Windows `cls` command)
- Unit tests for generation, movement, and combat logic
- CMake build for easier cross-platform setup
