# include <vector>

class Solution {
public:
    std::vector<std::vector<vector<int>>> get_neighbours(vector<vector<int>>& board) {
        std::vector<std::vector<vector<int>>> neighbours;

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

            if (new_row  >= 0 && new_row < rows_size && new_col >= 0 && new_col < cols_size) {
                auto neighbour = board;
                
                std::swap(neighbour[zero_row][zero_col], neighbour[new_row][new_col]);
                neighbours.push_back(neighbour);
            }
        }

        return neighbours;
    }

    int heuristic(const std::vector<std::vector<int>>& board) {
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

    std::string serialize(const std::vector<std::vector<int>>& board) {
        std::string s;
        for (auto& row : board)
            for (int v : row) s += char('0' + v);
        return s;
    }

    int slidingPuzzle(vector<vector<int>>& board) {
        std::vector<vector<int>> end{{1,2,3}, {4,5,0}};

        using State = std::tuple<int, int, std::vector<std::vector<int>>>;
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
};