#include "state.hpp"

void print_board(const _2d& board){
    std::cout << "  ";
    for(auto i=0; i < board.size(); i++)
        std::cout << i << " ";
    std::cout << std::endl;
    int r = 0;
    for(auto& row : board){
        std::cout << r << " ";
        for(auto& col : row){
            if(col == -1)
              std::cout << "#";
            else
                std::cout << col;
            std::cout << " ";
        }
        std::cout << std::endl;
        r++;
    }
}

class Game{
    public:
    int CURRENT_COLOR = 0;
    int MAXIMIZER = 0;
    State state;

    std::vector<State> gen_next_states(State state){
        std::vector<State> states;
        std::vector<Point> pot_points = state.get_legal_points(CURRENT_COLOR);

        for(const auto& p : pot_points){
            std::vector<Point> all_to_flip =
                state.get_all_flippable(CURRENT_COLOR, p);

            State state_cp = state;
            if(!all_to_flip.empty()) {
                state_cp.board[p.row][p.col] = CURRENT_COLOR;
                for(const auto& p : all_to_flip){
                    state_cp.board[p.row][p.col] = CURRENT_COLOR;
                }
                states.push_back(state_cp);
            }
        }
        return states;
    }

        int AlphaBeta(State state, int depth, int player, int alpha, int beta){
            if(depth == 0) return state.heuristic(player);

            if(player == MAXIMIZER){
                int max_eval = INT_MIN;
                std::vector<State> new_states = gen_next_states(state);
                for(const auto& s : new_states){
                    int eval = AlphaBeta(s, depth - 1, player ^ 1, alpha, beta);
                    max_eval = std::max(max_eval, eval);
                }
                return max_eval;
            }
            else{
                int min_eval = INT_MAX;
                std::vector<State> new_states = gen_next_states(state);
                for(const auto& s : new_states){
                    int eval = AlphaBeta(s, depth - 1, player ^ 1, alpha, beta);
                    min_eval = std::min(min_eval, eval);
                }
                return min_eval;
        }
    }

    Point get_best_move(State state, int color, int depth){
        std::vector<Point> moves = state.get_legal_points(color);
        int best_value = INT_MIN;

        Point best_move;
        for(const auto& m : moves){
            State next_state = state;
            std::vector<Point> to_flip = state.get_all_flippable(color, m);

            if(!to_flip.empty()){
                next_state.board[m.row][m.col] = color;
                for(const auto& p : to_flip){
                    next_state.board[p.row][p.col] = color;
                }
                int value = AlphaBeta(state, depth, color, INT_MIN, INT_MAX);
                if(value > best_value){
                    best_value = value;
                    best_move = m;
                }
            }
        }
        return best_move;
    }
};

class AI {
public:
    int COLOR;

    AI(int color) : COLOR(color) {}

    Point make_random_move(std::vector<Point> moves){
        std::srand(std::time(nullptr));
        int idx = rand() % moves.size();
        Point rand_m = moves[idx];
        return rand_m;
    }
};



void say(std::string s){
    std::cout << s << "\n";
    std::fflush(stdout);
}

void say(int row, int col){
    std::swap(row, col);
    std::cout << "IDO" << " " << row << " " << col << "\n";
    std::fflush(stdout);
}

int main(){
    // Game new_game;
    // new_game.CURRENT_COLOR = 1;
    // new_game.player_states = new_game.gen_next_states(new_game.state);
    // std::cout << new_game.player_states.size();

    // for(auto& s : new_game.player_states){
    //     print_board(s.board);
    // }

    // new_game.CURRENT_COLOR = 0;
    // new_game.state = new_game.player_states[0];

    // new_game.player_states = new_game.gen_next_states(new_game.state);
    // std::cout << new_game.player_states.size();

    // for(auto& s : new_game.player_states){
    //     print_board(s.board);
    // }

    // std::cout << new_game.state.calculate_close_corner_ratio(0) << std::endl;
    // std::cout << new_game.state.calculate_pieces_ratio(0)  << std::endl;
    // std::cout << new_game.state.calculate_corners_ratio(0)  << std::endl;
    // std::cout << new_game.state.calculate_weighted_pieces(0)  << std::endl;

    // double t0, t1;

    // while(true){
    //     std::string str;
    //     std::cin >> str;

    //     if(str == "BYE") break;

    //     if(str == "UGO"){
    //         std::cin >> t0 >> t1;

    //     }
    //     else if(str == "HEDID"){
    //         std::cin >> t0 >> t1;

    //         int row, col;
    //         std::cin >> col >> row;
    //         std::swap(row, col);
    //     }
    //     else if(str == "ONEMORE"){
    //         //Game.reset();
    //         say("RDY");
    //     }
    // }
    //
    //
    Game new_game;
    int DEPTH=  6;
    int current_color = 0;
    AI ai(current_color ^ 1);
    bool player_move = true;
    // while (true) {
    //     std::vector<Point> moves = new_game.state.get_legal_points(current_color);
    //     if (moves.empty()) {
    //         // Sprawdź, czy przeciwnik może się ruszyć
    //         std::vector<Point> opp_moves = new_game.state.get_legal_points(current_color ^ 1);
    //         if (opp_moves.empty()) break; // Koniec gry
    //         current_color ^= 1;
    //         continue;
    //     }
    //     Point best_move = new_game.get_best_move(new_game.state, current_color, current_color);
    //     std::vector<Point> to_flip = new_game.state.get_all_flippable(current_color, best_move);
    //     new_game.state.board[best_move.row][best_move.col] = current_color;
    //     for (const auto& p : to_flip)
    //         new_game.state.board[p.row][p.col] = current_color;
    //     current_color ^= 1;
    // }

    while (true) {
           std::vector<Point> moves = new_game.state.get_legal_points(current_color);

           if (moves.empty()) {
               // Sprawdź, czy przeciwnik może się ruszyć
               std::vector<Point> opp_moves = new_game.state.get_legal_points(current_color ^ 1);
               if (opp_moves.empty()) break; // Koniec gry
               current_color ^= 1;
               player_move = !player_move;
               continue;
           }

           if (player_move) {
               // Gracz (lub AI grający jako gracz)
               Point best_move = new_game.get_best_move(new_game.state, current_color, DEPTH);
               std::vector<Point> to_flip = new_game.state.get_all_flippable(current_color, best_move);
               new_game.state.board[best_move.row][best_move.col] = current_color;
               for (const auto& p : to_flip)
                   new_game.state.board[p.row][p.col] = current_color;
           } else {
               // AI (losowy ruch)
               Point ai_move = ai.make_random_move(moves);
               std::vector<Point> to_flip = new_game.state.get_all_flippable(current_color, ai_move);
               new_game.state.board[ai_move.row][ai_move.col] = current_color;
               for (const auto& p : to_flip)
                   new_game.state.board[p.row][p.col] = current_color;
           }

           current_color ^= 1;
           player_move = !player_move;
       }
    print_board(new_game.state.board);
}
