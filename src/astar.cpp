#include "astar.hpp"
#include <cstdlib>
#include <queue>
#include <tuple>
#include <unordered_set>

int heuristic(const Board& board) {
    int h = 0;
    int rows_size = board.size();
    int cols_size = board[0].size();

    for (int row = 0; row < rows_size; row++) {
        for (int col = 0; col < cols_size; col++) {
            int value = board[row][col];

            if (value == 0) {
                continue;
            }

            int goal_row = (value - 1) / cols_size;
            int goal_col = (value - 1) % cols_size;

            h += abs(row - goal_row);
            h += abs(col - goal_col);
        }
    }

    return h;
}

SolveResult solve(Board board) {
    SolveResult result;

    Board end{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};

    // state is (f, g, board), where f is the estimated 
    // total cost (g + h)
    using State = std::tuple<int, int, Board>;  

    // the pq is sorted by f
    auto cmp = [](const State& a, const State& b) { return std::get<0>(a) > std::get<0>(b); };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> open(cmp);

    // frontier
    open.push({heuristic(board), 0, board});

    // visited states
    std::unordered_set<std::string> closed{};
    closed.insert(serialize(board));

    // reconstructing the path
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, Board> keyToBoard;
    keyToBoard[serialize(board)] = board;

    // while there are states to explore
    while (!open.empty()) {
        // retrieve the highest priority state from the queue
        auto [f, g, cur_board] = open.top();
        open.pop();

        // check if the goal has been reached
        if (cur_board == end) {
            // create a vector and store the path
            std::vector<Board> path;
            std::string key = serialize(cur_board);
            while (true) {
                path.push_back(keyToBoard[key]);
                auto it = parent.find(key);
                if (it == parent.end()) {
                    break;
                }
                key = it->second;
            }
            std::reverse(path.begin(), path.end());

            result.moves = g;
            result.path = path;
            return result;
        }

        // if the current board is not the goal, generate all boards reachable
        for (auto& neighbour : get_neighbours(cur_board)) {
            // convert to string for hash set
            std::string key = serialize(neighbour);

            // check whether neighbour is already in closed
            if (closed.count(key)) {
                continue;
            }
            closed.insert(key);

            // record parent of neighbour for path reconstruction
            parent[key] = serialize(cur_board);
            keyToBoard[key] = neighbour;

            // calculate cost of reaching neighbour
            int new_g = g + 1;

            // adds neighbouring board to pq
            open.push({new_g + heuristic(neighbour), new_g, neighbour});
        }
    }

    return result;
}