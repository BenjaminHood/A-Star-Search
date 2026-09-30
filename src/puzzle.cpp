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

bool isSolvable(const Board& board) {
    int rows = board.size();
    int cols = board[0].size();

    std::vector<int> tiles;
    int blank_row = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int v = board[row][col];
            if (v == 0) blank_row = row;
            else tiles.push_back(v);
        }
    }

    int inversions = 0;
    for (size_t i = 0; i < tiles.size(); i++)
        for (size_t j = i + 1; j < tiles.size(); j++)
            if (tiles[i] > tiles[j]) inversions++;

    int blank_row_from_bottom = rows - blank_row;
    return (inversions + blank_row_from_bottom) % 2 == 1;
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