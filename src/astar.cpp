#include "astar.hpp"

#include <algorithm>
#include <tuple>
#include <functional>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>

int slidingPuzzle(Board board) {
    Board end{{1,2,3}, {4,5,0}};

    using State = std::tuple<int, int, Board>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> open{};
    
    open.push({heuristic(board), 0, board});
    
    std::unordered_set<std::string> closed {};
    closed.insert(serialize(board));

    while (!open.empty()) {
        auto [f, g, cur_board] = open.top();
        open.pop();

        if (cur_board == end) {
            return g;
        }

        for (auto& neighbour : get_neighbours(cur_board)) {
            std::string key = serialize(neighbour);
            if (closed.count(key)) {
                continue;
            }
            closed.insert(key);

            int new_g = g + 1;
            open.push({new_g + heuristic(neighbour), new_g, neighbour});
        }
    }
return -1;
}