#include <algorithm>
#include <bits/stdc++.h>
#include <array>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include<climits>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

typedef std::array<std::array<int, 8>, 8> _2d;

struct Point {
    int row, col;
    Point(int r = 0, int c = 0) : row(r), col(c) {}
    inline Point operator+=(const Point& other) {
        row += other.row;
        col += other.col;
        return *this;
    }
    inline Point operator+(const Point& other) const {
        return Point(row + other.row, col + other.col);
    }
};

typedef std::unordered_map<std::string, Point> str_to_direct;

_2d init_board(_2d& board) {
    for (auto& row : board) std::fill(row.begin(), row.end(), -1);
    board[3][3] = 0;
    board[3][4] = 1;
    board[4][3] = 1;
    board[4][4] = 0;
    return board;
}

class State {
public:
    _2d board;
    str_to_direct directions;
    int CELL_SCORE[8][8] = {
        {20, -3, 11,  8,  8,  11, -3,  20},
        {-3, -7, -4,  1,  1, -4,  -7, -3},
        {11, -4,  2,  2,  2,  2,  -4 , 11},
        {8,   1,  2, -3, -3,  2,   1,  8},
        {8,   1,  2, -3, -3,  2,   1,  8},
        {11, -4,  2,  2,  2,  2,  -4,  11},
        {-3, -7, -4,  1,  1, -4,  -7, -3},
        {20, -3, 11,  8,  8,  11, -3,  20}
    };

    State(bool starting = true) {
        directions = {
            {"N",  {-1, 0}},
            {"NE", {-1, 1}},
            {"E",  {0, 1}},
            {"SE", {1, 1}},
            {"S",  {1, 0}},
            {"SW", {1, -1}},
            {"W",  {0, -1}},
            {"NW", {-1, -1}}
        };
        board = init_board(board);
    }

    inline bool is_legal_position(Point p) const {
        return (p.row >= 0 && p.row < 8) && (p.col >= 0 && p.col < 8);
    }

    std::vector<Point> get_legal_points(int color) const {
        std::vector<Point> points;
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (board[r][c] != -1) continue;
                for (const auto& d : directions) {
                    Point p = Point(r, c) + d.second;
                    if (is_legal_position(p) && board[p.row][p.col] == (color ^ 1)) {
                        Point q = p + d.second;
                        while (is_legal_position(q) && board[q.row][q.col] == (color ^ 1))
                            q += d.second;
                        if (is_legal_position(q) && board[q.row][q.col] == color) {
                            points.emplace_back(r, c);
                            break;
                        }
                    }
                }
            }
        }
        return points;
    }

    std::vector<Point> get_flippable_in_direction(int color, Point start_point, Point direction) const {
        std::vector<Point> to_flip;
        Point p = start_point + direction;
        while (is_legal_position(p) && board[p.row][p.col] == (color ^ 1)) {
            to_flip.push_back(p);
            p += direction;
        }
        if (is_legal_position(p) && board[p.row][p.col] == color && !to_flip.empty())
            return to_flip;
        return {};
    }

    std::vector<Point> get_all_flippable(int color, Point st_pt) const {
        std::vector<Point> all_to_flip;
        for (const auto& d : directions) {
            auto to_flip = get_flippable_in_direction(color, st_pt, d.second);
            all_to_flip.insert(all_to_flip.end(), to_flip.begin(), to_flip.end());
        }
        return all_to_flip;
    }

    int heuristic(int color) const {
        int pieces_ratio = calculate_pieces_ratio(color);
        int weights_bilance = calculate_weighted_pieces(color);
        int corner_ratio = calculate_corners_ratio(color);
        int near_corner_ratio = calculate_close_corner_ratio(color);
        return (pieces_ratio * 10) + (800 * corner_ratio) +
               (-12 * 380 * near_corner_ratio) + (80 * weights_bilance);
    }

    int calculate_pieces_ratio(int color) const {
        int player_pieces = 0, opponent_pieces = 0;
        for (int r = 0; r < 8; ++r)
            for (int c = 0; c < 8; ++c)
                if (board[r][c] != -1)
                    (board[r][c] == color ? player_pieces : opponent_pieces)++;
        if (player_pieces + opponent_pieces == 0) return 0;
        return 100 * (player_pieces - opponent_pieces) / (player_pieces + opponent_pieces);
    }

    int calculate_weighted_pieces(int color) const {
        int weights_sum = 0;
        for (int r = 0; r < 8; ++r)
            for (int c = 0; c < 8; ++c)
                if (board[r][c] != -1)
                    weights_sum += (board[r][c] == color ? 1 : -1) * CELL_SCORE[r][c];
        return weights_sum;
    }

    int calculate_corners_ratio(int color) const {
        int player_corners = 0, opponent_corners = 0;
        int corners[4][2] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};
        for (const auto& c : corners) {
            if (board[c[0]][c[1]] == color) player_corners++;
            else if (board[c[0]][c[1]] == (color ^ 1)) opponent_corners++;
        }
        if (player_corners + opponent_corners == 0) return 0;
        return 100 * (player_corners - opponent_corners) / (player_corners + opponent_corners);
    }

    int calculate_close_corner_ratio(int color) const {
        int player_near_corners = 0, opponent_near_corners = 0;
        int corners[4][2] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};
        for (const auto& c : corners) {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = c[0] + dr, nc = c[1] + dc;
                    if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;
                    if (board[nr][nc] == color) player_near_corners++;
                    else if (board[nr][nc] == (color ^ 1)) opponent_near_corners++;
                }
            }
        }
        if (player_near_corners + opponent_near_corners == 0) return 0;
        return 100 * (player_near_corners - opponent_near_corners) / (player_near_corners + opponent_near_corners);
    }

    void reset(bool starting = true) {
        board = {};
        init_board(board);
    }
};

const int DEPTH = 5;
const int INF = std::numeric_limits<int>::max();

class AI {
public:
    int MAXIMIZER = 0, MINIMIZER = 1;

    std::pair<int, int> get_best_action(State state, int color) {
        int best_value = -INF;
        std::pair<int, int> best_move = {-1, -1};
        std::vector<Point> actions = state.get_legal_points(color);

        for (const auto& move : actions) {
            State next_state = state;
            std::vector<Point> to_flip = next_state.get_all_flippable(color, move);
            if (!to_flip.empty()) {
                next_state.board[move.row][move.col] = color;
                for (const auto& p : to_flip)
                    next_state.board[p.row][p.col] = color;
                int value = AlphaBeta(next_state, DEPTH - 1, color ^ 1, -INF, INF);
                if (value > best_value) {
                    best_value = value;
                    best_move = {move.row, move.col};
                }
            }
        }
        return best_move;
    }

    int AlphaBeta(State state, int depth, int color, int alpha, int beta) {
        std::vector<Point> actions = state.get_legal_points(color);
        if (depth == 0 || actions.empty()) {
            return state.heuristic(color);
        }

        if (color == MAXIMIZER) {
            int max_eval = -INF;
            for (const auto& move : actions) {
                State next_state = state;
                std::vector<Point> to_flip = next_state.get_all_flippable(color, move);
                if (!to_flip.empty()) {
                    next_state.board[move.row][move.col] = color;
                    for (const auto& p : to_flip)
                        next_state.board[p.row][p.col] = color;
                    int eval = AlphaBeta(next_state, depth - 1, color ^ 1, alpha, beta);
                    max_eval = std::max(max_eval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break;
                }
            }
            return max_eval;
        } else {
            int min_eval = INF;
            for (const auto& move : actions) {
                State next_state = state;
                std::vector<Point> to_flip = next_state.get_all_flippable(color, move);
                if (!to_flip.empty()) {
                    next_state.board[move.row][move.col] = color;
                    for (const auto& p : to_flip)
                        next_state.board[p.row][p.col] = color;
                    int eval = AlphaBeta(next_state, depth - 1, color ^ 1, alpha, beta);
                    min_eval = std::min(min_eval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) break;
                }
            }
            return min_eval;
        }
    }
};

void say(const std::string& s) {
    std::cout << s << std::endl;
    std::fflush(stdout);
}

void say(int row, int col) {
    std::swap(row, col);
    std::cout << "IDO " << row << " " << col << std::endl;
    std::fflush(stdout);
}

int main() {
    State Game(true);
    AI ai;
    say("RDY");

    int my_color = 0; // 0 - AI zaczyna, 1 - przeciwnik zaczyna
    double t0, t1;

    while (true) {
        std::string str;
        std::cin >> str;

        if (str == "BYE") break;

        if (str == "UGO") {
            std::cin >> t0 >> t1;
            my_color = 0;
            auto move = ai.get_best_action(Game, my_color);
            say(move.second, move.first);
            std::vector<Point> to_flip = Game.get_all_flippable(my_color, {move.first, move.second});
            Game.board[move.first][move.second] = my_color;
            for (const auto& p : to_flip)
                Game.board[p.row][p.col] = my_color;
        } else if (str == "HEDID") {
            std::cin >> t0 >> t1;
            int row, col;
            std::cin >> col >> row;
            std::swap(row, col);
            my_color = 0; // AI zawsze gra jako 0, przeciwnik jako 1
            std::vector<Point> to_flip = Game.get_all_flippable(my_color ^ 1, {row, col});
            Game.board[row][col] = my_color ^ 1;
            for (const auto& p : to_flip)
                Game.board[p.row][p.col] = my_color ^ 1;
            auto move = ai.get_best_action(Game, my_color);
            say(move.second, move.first);
            to_flip = Game.get_all_flippable(my_color, {move.first, move.second});
            Game.board[move.first][move.second] = my_color;
            for (const auto& p : to_flip)
                Game.board[p.row][p.col] = my_color;
        } else if (str == "ONEMORE") {
            Game.reset();
            say("RDY");
        }
    }
}
