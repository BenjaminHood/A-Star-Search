#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>

using Board = std::vector<std::vector<int>>;

class Puzzle {
public:
    explicit Puzzle(Board initial);

    const Board& initial_state() const;

    Board goal_state() const;

    std::vector<Board> get_neighbours(const Board& board) const;

    int heuristic(const Board& board) const;

    std::string serialize(const Board& board) const;

    bool is_goal(const Board& board) const;

    bool is_valid() const;

private:
    Board initial_;
    int rows_;
    int cols_;
};

#endif