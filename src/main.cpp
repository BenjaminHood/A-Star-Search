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

static void printUsage(const char* prog) {
    std::cerr
        << "Usage:\n"
        << "  " << prog << " --board \"1 2 3 4 5 6 7 8 9 10 11 0 13 14 15 12\"\n"
        << "  " << prog << " --scramble N [--seed S]\n"
        << "\n"
        << "  --board       16 space-separated values, row-major, 0 = blank.\n"
        << "  --scramble N  generate a random board N legal moves from the goal.\n"
        << "  --seed S      RNG seed for --scramble (default: 1).\n";
}

int main(int argc, char** argv) {
    std::string boardStr;
    int scrambleMoves = -1;
    unsigned seed = 1;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--board" && i + 1 < argc) boardStr = argv[++i];
        else if (arg == "--scramble" && i + 1 < argc) scrambleMoves = std::stoi(argv[++i]);
        else if (arg == "--seed" && i + 1 < argc) seed = static_cast<unsigned>(std::stoul(argv[++i]));
        else { printUsage(argv[0]); return 1; }
    }

    if (boardStr.empty() && scrambleMoves < 0) {
        printUsage(argv[0]);
        return 1;
    }

    Board board;
    if (!boardStr.empty()) {
        if (!parseBoard(boardStr, board)) {
            std::cerr << "Could not parse 16 integers from --board.\n";
            return 1;
        }
    } else {
        board = randomScramble(scrambleMoves, seed);
    }

    if (!isSolvable(board)) {
        std::cout << "This configuration is not solvable.\n";
        return 0;
    }

    SolveResult result = solve(board);

    std::cout << "Solved in " << result.moves << " moves.\n\n";
    std::cout << "Solution path:\n";
    std::cout << "Start:\n";
    printBoard(board);
    std::cout << "\n";
    for (size_t step = 1; step < result.path.size(); step++) {
        std::cout << "Step " << step << ":\n";
        printBoard(result.path[step]);
        std::cout << "\n";
    }

    return 0;
}
