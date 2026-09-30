#pragma once
#include <string>
#include <vector>

using Board = std::vector<std::vector<int>>;

std::vector<Board> get_neighbours(Board& board);

std::string serialize(const Board& board);
