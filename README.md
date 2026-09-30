# A* search: 15-Puzzle Solver

An implementation of A* search applied to the 15-puzzle (a 4x4 sliding tile puzzle).

## Build

```bash
mkdir -p build
g++ -std=c++17 -O2 -o build/solve src/main.cpp src/puzzle.cpp src/astar.cpp
```

## Usage

Solve a specific board by entering 16 space-seperated values, `0` for the blank space, for example: 
```bash
./build/solve --board "1 2 3 4 5 6 7 8 9 10 11 0 13 14 15 12"
```

Or generate a random solvable board with N legal moves from the goal, for example:

```bash
./build/solve --scramble 20 --seed 7
```

`-seed` is optional and by default is `1`, allowing for the reproduction of the same scramble across multiple runs