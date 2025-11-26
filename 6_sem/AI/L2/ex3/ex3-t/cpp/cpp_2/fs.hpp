#pragma once
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

struct pair {
  pair(int y, int x) : y(y), x(x) {}
  int y;
  int x;

  bool operator==(const pair &other) const {
    return y == other.y && x == other.x;
  }
};

struct pairHash {
  std::size_t operator()(const pair &p) const {
    return std::hash<int>()(p.y) ^ (std::hash<int>()(p.x) << 1);
  }
};

typedef std::vector<std::vector<char>> vec2char;
typedef std::unordered_set<pair, pairHash> pair_set;

struct result {
  result(int f, pair_set &state, std::string path)
      : f(f), state(state), path(path) {}
  int f;
  pair_set state;
  std::string path;

  bool operator<(const result &other) const { return f > other.f; }
};

struct pairSetHash {
  std::size_t operator()(const pair_set &ps) const {
    std::size_t seed = 0;
    for (const auto &p : ps) {
      // Kombinacja wartości haszujących elementów w zbiorze
      seed ^= pairHash{}(p) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

pair_set get_points(vec2char &board, char letter);

pair add(vec2char &board, const pair &ran_coords, pair &move);

int potencial(pair_set &rangers_state, pair_set &goal_points);

std::vector<result> next_moves(pair_set &rangers_state, vec2char &board,
                               pair_set &goal_points);

std::string Astar(vec2char &board, pair_set &start_points,
                  pair_set &goal_points);
