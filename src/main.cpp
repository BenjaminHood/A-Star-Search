#include <iostream>
#include <sstream>
#include "astar.hpp"

// mkdir -p build && g++ -std=c++17 -O2 -o build/solve src/main.cpp src/puzzle.cpp src/astar.cpp
// ./build/solve "1 2 3 4 5 6 7 8 9 10 11 0 13 14 15 12"
// Parses 16 space-separated integers into a 4x4 board
static bool parseBoard(const std::string& s, Board& board) {
    std::istringstream iss(s);
    board.assign(4, std::vector<int>(4));
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            if (!(iss >> board[row][col])) return false;
    return true;
}

static void printBoard(const Board& board) {
    for (auto& row : board) {
        for (int v : row) std::cout << v << " ";
        std::cout << "\n";
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0]
                  << " \"1 2 3 4 5 6 7 8 9 10 11 0 13 14 15 12\"\n"
                  << "(16 space-separated values, row-major, 0 = blank)\n";
        return 1;
    }

    Board board;
    if (!parseBoard(argv[1], board)) {
        std::cerr << "Could not parse 16 integers from the board argument.\n";
        return 1;
    }

    SolveResult result = solve(board);

    if (result.moves == -1) {
        std::cout << "No solution found (unexpected for a solvable board).\n";
        return 1;
    }

    std::cout << "Solved in " << result.moves << " moves.\n\n";
    std::cout << "Solution path:\n";
    for (size_t step = 0; step < result.path.size(); step++) {
        std::cout << "Step " << step + 1 << ":\n";
        printBoard(result.path[step]);
        std::cout << "\n";
    }

    return 0;
}
