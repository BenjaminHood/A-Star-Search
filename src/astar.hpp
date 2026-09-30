#pragma once
#include "puzzle.hpp"

int heuristic(const Board& board);

struct SolveResult {
    int moves = -1;          // -1 means unsolved
    std::vector<Board> path;  // start and goal inclusive; empty if unsolved
};

SolveResult solve(Board board);