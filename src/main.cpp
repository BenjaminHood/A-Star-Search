#include <iostream>
#include <sstream>
#include "astar.hpp"

// build with ./build/solve "1 2 3 4 5 6 7 8 9 10 11 0 13 14 15 12"
// Parses 16 space-separated integers into a 4x4 board
static bool parseBoard(const std::string& s, Board& board) {
    std::istringstream iss(s);
    board.assign(4, std::vector<int>(4));
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            if (!(iss >> board[row][col])) return false;
    return true;
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

    int moves = solve(board);

    if (moves == -1) {
        std::cout << "No solution found (or search space exhausted).\n";
    } else {
        std::cout << "Solved in " << moves << " moves.\n";
    }

    return 0;
}
