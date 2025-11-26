#include "fs.hpp"

std::unordered_map<char, pair> UDLR = {
    {'U', {-1, 0}},
    {'D', {1, 0}},
    {'L', {0, -1}},
    {'R', {0, 1}},
};

pair_set get_points(vec2char &board, char letter) {
  pair_set points;
  for (int y = 0; y < (int)board.size(); y++) {
    for (int x = 0; x < (int)board[0].size(); x++) {
      char field = board[y][x];
      if (field == letter || field == 'B') {
        points.insert({y, x});
      }
    }
  }
  return points;
}

pair add(vec2char &board, const pair &ran_coords, pair &move) {
  pair new_coords = {ran_coords.y + move.y, ran_coords.x + move.x};
  return board[new_coords.y][new_coords.x] != '#' ? new_coords : ran_coords;
}

int potencial(pair_set &rangers_state, pair_set &goal_points) {
  int maxi = 0;
  for (const pair &r : rangers_state) {
    int min_dist = std::numeric_limits<int>::max();
    for (const pair &g : goal_points) {
      int dist = std::abs(r.x - g.x) + abs(r.y - g.y);
      min_dist = std::min(min_dist, dist);
    }
    maxi = std::max(maxi, min_dist);
  }
  return maxi;
}

std::vector<result> next_moves(pair_set &rangers_state, vec2char &board,
                               pair_set &goal_points) {
  std::vector<result> res;
  for (auto &move : UDLR) {
    pair_set new_rangers_state;
    for (const pair &r : rangers_state) {
      new_rangers_state.insert(add(board, r, move.second));
    }
    res.push_back({potencial(new_rangers_state, goal_points), new_rangers_state,
                   std::string(1, move.first)});
  }
  return res;
}

std::string Astar(vec2char &board, pair_set &start_points,
                  pair_set &goal_points) {

  std::string path = "";
  int f = potencial(start_points, goal_points);
  std::priority_queue<result> pq;
  pq.push({f, start_points, path});
  std::unordered_set<pair_set, pairSetHash> visited;

  while (!pq.empty()) {
    result ran_node = pq.top();
    pq.pop();
    visited.insert(ran_node.state);
    if (std::all_of(ran_node.state.begin(), ran_node.state.end(),
                    [&](pair field) {
                      return board[field.y][field.x] == 'G' or
                             board[field.y][field.x] == 'B';
                    }))
      return ran_node.path;
    std::vector<result> moves = next_moves(ran_node.state, board, goal_points);

    for (auto &m : moves) {
      if (visited.find(m.state) == visited.end()) {
        int g = ran_node.path.length() + 1;
        pq.push({m.f + g, m.state, ran_node.path + m.path});
      }
    }
  }
  return path;
}
