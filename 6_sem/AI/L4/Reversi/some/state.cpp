#include "state.hpp"

_2d init_board(_2d& board){
    for(auto& row : board){
        std::fill(row.begin(), row.end(), -1);
    }

    board[3][3] = 0;
    board[3][4] = 1;
    board[4][3] = 1;
    board[4][4] = 0;
    return board;
}

State::State(){
    directions =
    {
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

inline bool State::is_legal_position(Point p){
    return (p.col >= 0 && p.col <= 7) && (p.row >= 0 && p.row <= 7);
}

bool State::is_next_to_opposite(_2d board, Point p, int color){
    for(auto& d : directions){
        Point check = p + Point(d.second);
        if(is_legal_position(check)){
            if(board[check.row][check.col] != -1 &&
                board[check.row][check.col] != color){
                return true;
            }
        }
    }
    return false;
}
std::vector<Point> State::get_legal_points(int color){
    std::vector<Point> points;

    for(auto r = 0;r < board.size(); r++){
        for(auto c = 0;c < board[r].size(); c++){
            if(board[r][c] == -1){
                if(is_next_to_opposite(board, {r, c}, color)){
                    points.push_back({r, c});
                }
            }
        }
    }
    return points;
}

std::vector<Point> State::get_flippable_in_direction(int color, Point start_point, Point direction) {
    std::vector<Point> to_flip;
    Point p = start_point + direction;

    while (is_legal_position(p) && board[p.row][p.col] == (color ^ 1)) {
        to_flip.push_back(p);
        p += direction;
    }

    if (is_legal_position(p) && board[p.row][p.col] == color && !to_flip.empty()) {
        return to_flip;
    }
    return {};
}

std::vector<Point> State::get_all_flippable(int color, Point st_pt){
    std::vector<Point> all_to_flip;
        for(auto& d : directions){
            std::vector<Point> to_flip = get_flippable_in_direction(color, st_pt, d.second);
            all_to_flip.insert(all_to_flip.end(), to_flip.begin(), to_flip.end());
        }
        return all_to_flip;
}

int State::heuristic(int color) {
    int pieces_ratio = calculate_pieces_ratio(color);
    int weights_bilance = calculate_weighted_pieces(color);
    int corner_ratio = calculate_corners_ratio(color);
    int near_corner_ratio = calculate_close_corner_ratio(color);
    return (pieces_ratio * 10) + (800 * corner_ratio) +
            (-12 * 380 * near_corner_ratio) + (80 * weights_bilance);


}

int State::calculate_pieces_ratio(int color){
    int player_pieces = 0, opponent_pieces = 0;
    for(auto r = 0; r < board.size(); r++){
        for(auto c = 0; c < board[r].size(); c++){
            if(board[r][c] != -1){
                if(board[r][c] == color)
                    player_pieces += 1;
                else
                    opponent_pieces += 1;
            }
        }
    }
    return 100 * (player_pieces - opponent_pieces) /
                    (player_pieces + opponent_pieces);
}

int State::calculate_weighted_pieces(int color){
    int weights_sum = 0;
    for(auto r = 0; r < board.size(); r++){
        for(auto c = 0; c < board[r].size(); c++){
            if(board[r][c] != -1){
                if(board[r][c] == color)
                    weights_sum += CELL_SCORE[r][c];
                else
                    weights_sum -= CELL_SCORE[r][c];
            }
        }
    }
    return weights_sum;
}

int State::calculate_corners_ratio(int color){
    int player_corners = 0, opponent_corners = 0;
    int corners[4][2] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};

    for (const auto& c : corners) {
        if(board[c[0]][c[1]] != -1){
            if(board[c[0]][c[1]] == color)
                player_corners += 1;
            else
                opponent_corners += 1;
        }
    }

    if ((player_corners + opponent_corners) == 0) return 0;
    return 100 * (player_corners - opponent_corners) /
                (player_corners + opponent_corners);
}

int State::calculate_close_corner_ratio(int color){
    int player_near_corners = 0, opponent_near_corners = 0;
    int corners[4][2] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};

    for (const auto& c : corners) {
        int i = (c[0] == 0 ? 1 : -1);
        int j = (c[1] == 0 ? 1 : -1);
        if(board[c[0] + i][c[1]] != -1){
            if(board[c[0] + i][c[1]] == color)
                player_near_corners += 1;
            else
                opponent_near_corners += 1;
        }
        if(board[c[0]][c[1] + j] != -1){
            if(board[c[0]][c[1] + j] == color)
                player_near_corners += 1;
            else
                opponent_near_corners += 1;
        }
    }
    if ((player_near_corners + opponent_near_corners) == 0) return 0;
    return 100 * (player_near_corners - opponent_near_corners) /
                (player_near_corners + opponent_near_corners);
}

void State::reset(){
    for(auto& row : board){
        for(auto& col : row) col = -1;
    }
}
