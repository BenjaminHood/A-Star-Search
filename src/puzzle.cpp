#include "puzzle.hpp"
#include <random>

std::vector<Board> get_neighbours(Board& board) {
    std::vector<Board> neighbours;

    int rows_size = board.size();
    int cols_size = board[0].size();

    int zero_row = 0;
    int zero_col = 0;
    for (int row = 0; row < rows_size; row++) {
        for (int col = 0; col < cols_size; col++) {
            if (board[row][col] == 0) {
                zero_row = row;
                zero_col = col;
            }
        }
    }

    const std::pair<int, int> moves[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (const auto& move : moves) {
        int new_row = zero_row + move.first;
        int new_col = zero_col + move.second;

        if (new_row >= 0 && new_row < rows_size && new_col >= 0 && new_col < cols_size) {
            auto neighbour = board;
            std::swap(neighbour[zero_row][zero_col], neighbour[new_row][new_col]);
            neighbours.push_back(neighbour);
        }
    }

    return neighbours;
}

std::string serialize(const Board& board) {
    std::string s;
    for (auto& row : board)
        for (int v : row) s += char('0' + v);
    return s;
}

Board randomScramble(int moves, unsigned seed) {
    Board board{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};

    std::mt19937 rng(seed);
    for (int i = 0; i < moves; i++) {
        auto options = get_neighbours(board);
        std::uniform_int_distribution<size_t> dist(0, options.size() - 1);
        board = options[dist(rng)];
    }
    return board;
}