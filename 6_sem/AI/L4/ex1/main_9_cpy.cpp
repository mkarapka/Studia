#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>
using namespace std;

#define X first
#define Y second


const int DIRECTIONS = 8;
const int BOARD_SIZE = 64, BOARD_LEN = 8;

const int ROW[DIRECTIONS] = {-1, -1, 0, +1, +1, +1, 0, -1};
const int COL[DIRECTIONS] = {0, +1, +1, +1, 0, -1, -1, -1};

const pair < int, int > CORNERS[4] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};

int CELL_SCORE[BOARD_LEN][BOARD_LEN] = {
        {20, -3, 11,  8,  8,  11, -3,  20},
        {-3, -7, -4,  1,  1, -4,  -7, -3},
        {11, -4,  2,  2,  2,  2,  -4 , 11},
        {8,   1,  2, -3, -3,  2,   1,  8},
        {8,   1,  2, -3, -3,  2,   1,  8},
        {11, -4,  2,  2,  2,  2,  -4,  11},
        {-3, -7, -4,  1,  1, -4,  -7, -3},
        {20, -3, 11,  8,  8,  11, -3,  20}};

class State {
public:

    bool player[BOARD_LEN][BOARD_LEN];
    bool opponent[BOARD_LEN][BOARD_LEN];

    State(bool starting = false) { reset(starting); }

    void reset(bool starting) {
        for(int i = 0; i < BOARD_LEN; i++) {
            for(int j = 0; j < BOARD_LEN; j++) {
                player[i][j] = opponent[i][j] = false;
            }
        }
        player[3][4] = player[4][3] = true;
        opponent[3][3] = opponent[4][4] = true;

        if(!starting) swap_players();
    }

    inline void set_player_cell(int row, int col, bool value) {
        if(is_legal_position(row, col)) player[row][col] = value;
    }

    inline bool get_player_cell(int row, int col) const {
        return is_legal_position(row, col) & player[row][col];
    }

    inline void set_opponent_cell(int row, int col, bool value) {
        if(is_legal_position(row, col)) opponent[row][col] = value;
    }

    inline bool get_opponent_cell(int row, int col) const {
        return is_legal_position(row, col) & opponent[row][col];
    }

    void swap_players() {
        swap(player, opponent);
    }

    void make_move(int row, int col) {
        set_player_cell(row, col, true);
        for(int d = 0; d < DIRECTIONS; d++) {
            if(!possible_move(row, col, d)) continue;
            int new_row = row + ROW[d];
            int new_col = col + COL[d];
            while(get_opponent_cell(new_row, new_col)) {
                set_player_cell(new_row, new_col, true);
                set_opponent_cell(new_row, new_col, false);
                new_row += ROW[d];
                new_col += COL[d];
            }
        }
    }

    inline bool is_legal_position(int row, int col) const {
        return (row >= 0 && row < 8) && (col >= 0 && col < 8);
    }

    bool possible_move(int row, int col, int d) const {
        row += ROW[d], col += COL[d];
        if(!is_legal_position(row, col) || !get_opponent_cell(row, col)) return false;
        while(is_legal_position(row, col) && get_opponent_cell(row, col)) {
            row += ROW[d];
            col += COL[d];
        }
        return (is_legal_position(row, col) && get_player_cell(row, col));
    }

    vector < pair < int, int > > get_actions() const {
        vector < pair < int, int > > res;
        for(int row = 0; row < BOARD_LEN; row++) {
            for(int col = 0; col < BOARD_LEN; col++) {
                if(get_player_cell(row, col) || get_opponent_cell(row, col)) continue;
                for(int d = 0; d < DIRECTIONS; d++) {
                    if(possible_move(row, col, d)) {
                        res.push_back({row, col});
                        break;
                    }
                }
            }
        }
        return res;
    }

    inline int calculate_ratio(int player, int opponent) const {
        return 100 * ((double)(player - opponent)) / (player + opponent);
    }

    int heuristic_value() const {
        pair<int, int> plr_opp_pair = count_player_opponent_cells();
        int player_cells = plr_opp_pair.first;
        int opponent_cells = plr_opp_pair.second;
        int board_bilans = player_cells - opponent_cells;


        int ratio = calculate_ratio(player_cells, opponent_cells);

        int player_corners = 0;
        int opponent_corners = 0;

        for(pair < int, int > p : CORNERS) {
            int row = p.X, col = p.Y;
            if(get_player_cell(row, col)) player_corners++;
            else if(get_opponent_cell(row, col)) opponent_corners++;
        }

        int corner_ratio = 0;
        if(player_corners + opponent_corners)
            corner_ratio = calculate_ratio(player_corners, opponent_corners);


        int player_close_corners = 0;
        int opponent_close_corners = 0;
        for(pair < int, int > p : CORNERS) {
            int row = p.X, col = p.Y;
            if((get_player_cell(row, col) || get_opponent_cell(row, col))) continue;
            for(int d = 0; d < DIRECTIONS; d++) {
                int new_row = row + ROW[d], new_col = col + COL[d];
                if(is_legal_position(new_row, new_col)) {
                    if(get_player_cell(new_row, new_col)) player_close_corners++;
                    else if(get_opponent_cell(new_row, new_col)) opponent_close_corners++;
                }
            }
        }

        int close_corner_value = (player_close_corners - opponent_close_corners);

        return ((10 * ratio) + (800 * corner_ratio) + (-12 * 380 * close_corner_value) + (80 * board_bilans));
    }

    pair<int, int> count_player_opponent_cells() const {
        int player_cells = 0, opponent_cells = 0;
        for(int i = 0; i < BOARD_LEN; i++)
            for(int j = 0; j < BOARD_LEN; j++)
                if(get_player_cell(i, j))
                    player_cells++;
                else if(get_opponent_cell(i, j))
                    opponent_cells++;
        return pair<int, int>{player_cells, opponent_cells};
    }

    int utility() const {
        pair<int, int> plr_opp_pair = count_player_opponent_cells();
        return plr_opp_pair.first - plr_opp_pair.second;
    }


    bool is_terminal() const {
        return get_actions().empty();
    }

    inline bool is_terminal(vector < pair < int, int > > actions) const {
        return actions.empty();
    }

    void make_action(int row, int col) {
        if(row != -1 && col != -1) make_move(row, col);
        swap_players();
    }

    State make_new_state(int row, int col) {
        State res = *this;
        res.make_action(row, col);
        return res;
    }

};
class MCTS_node
{
    public:
    State state;
    pair<int, int> move;
    MCTS_node* parent;
    vector<MCTS_node*> children;
    int visits;
    double wins;

    MCTS_node(const State& s, pair<int, int> m, MCTS_node* p = nullptr)
            : state(s), move(m), parent(p), visits(0), wins(0){}

    ~MCTS_node() {
        for (auto child : children) delete child;
    }
};

class AI {
    const int INF = 1e9;
    mt19937 rand_generator;
    double EXP_CONST = sqrt(2);

public:

    pair<int, int> get_best_action(State state){
        return mcts_search(state, 1.0);
    }

    pair<int, int> mcts_search(State root_state, double time_limit){
        auto start = chrono::high_resolution_clock::now();

        MCTS_node* root = new MCTS_node(root_state, {-1,-1}, nullptr);

        int i = 0;
        while(true){
            auto now = chrono::high_resolution_clock::now();
            double elapsed = chrono::duration<double>(now - start).count();
            if(elapsed > time_limit) break;

            MCTS_node* node = tree_policy(root);
            double reward = rollout(node->state);
            backpropagation(node, reward);
            ++i;
        }

        MCTS_node* best = nullptr;
        int best_visits = 1;
        for(auto child : root->children){
            if(child->visits > best_visits){
                best_visits = child->visits;
                best = child;
            }
        }
        pair<int, int> result = best ? best->move : pair<int, int>{-1, -1};
        delete root;
        return result;
    }

    MCTS_node* tree_policy(MCTS_node* node){
        while(!node->state.is_terminal()){
            auto actions = node->state.get_actions();
            if(node->children.size() < actions.size()){
                return expand(node);
            } else {
                node = best_child(node, EXP_CONST);
            }
        }
        return node;
    }

    MCTS_node* expand(MCTS_node* node) {
           auto actions = node->state.get_actions();
           set<pair<int, int>> tried;
           for (auto child : node->children) tried.insert(child->move);
           for (auto action : actions) {
               if (tried.count(action) == 0) {
                   State new_state = node->state.make_new_state(action.first, action.second);
                   MCTS_node* child = new MCTS_node(new_state, action, node);
                   node->children.push_back(child);
                   return child;
               }
           }
           return node;
       }

    double rollout(State state)
    {
        bool player_turn = true;
        while(!state.is_terminal()){
            auto actions = state.get_actions();
            if(actions.empty()){
                player_turn = !player_turn;
                state.swap_players();
                continue;
            }
            auto act = actions[rand_generator() % actions.size()];
            state.make_action(act.first, act.second);
        }
        // int result = state.utility();
        // if(result > 0)
        //     return 1.0;
        // else if(result == 0)
        //     return 0.5;
        // else
        //     return 0.0;
        return state.heuristic_value() * (player_turn == true ? 1 : -1);
    }

    void backpropagation(MCTS_node* node, double reward){
        while(node){
            node->visits += 1;
            node->wins = node->wins + (reward - node->wins);
            node = node->parent;
        }
    }

    // UCB1
    MCTS_node* best_child(MCTS_node* node, double c) {
        MCTS_node* best = nullptr;
        double best_value = -INF;
        for (auto child : node->children) {
            double ucb = (child->wins / (child->visits + 1e-6)) +
                        c * sqrt(log(node->visits + 1) / (child->visits + 1e-6));
            if (ucb > best_value) {
                best_value = ucb;
                best = child;
            }
        }
        return best;
    }
};



void say(string s) {
    cout << s << "\n";
    fflush(stdout);
}

void say(int row, int col) {
    swap(row, col);
    cout << "IDO" << " " << row << " " << col << "\n";
    fflush(stdout);
}

int main() {

    State Game(true);
    AI Ai;
    double t0, t1;

    say("RDY");

    while(true) {

        string str;
        cin >> str;

        if(str == "BYE") break;
        if(str == "UGO") {
            cin >> t0 >> t1;

            auto p = Ai.get_best_action(Game);

            say(p.Y, p.X);

            Game.make_action(p.X, p.Y);

        } else if(str == "HEDID") {
            cin >> t0 >> t1;

            int row, col; cin >> col >> row;
            swap(row, col);

            Game.make_action(row, col);

            auto p = Ai.get_best_action(Game);

            say(p.Y, p.X);

            Game.make_action(p.X, p.Y);

        } else if(str == "ONEMORE") {
            Game.reset(true);
            say("RDY");
        }

    }
}
