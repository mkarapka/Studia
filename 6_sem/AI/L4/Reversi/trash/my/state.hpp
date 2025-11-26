#pragma once

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

typedef std::array<std::array<int, 8>, 8> _2d;

struct Point
{
    int col, row;
    Point(int y, int x) : col(x), row(y) {}
    Point() : col(0), row(0) {}

    inline Point operator+=(const Point& other) {
        col += other.col;
        row += other.row;
        return *this;
    }

    inline Point operator+(const Point& other) const {
        return Point{row + other.row, col + other.col};
    }
};

typedef std::unordered_map<std::string, Point> str_to_direct;



_2d init_board(_2d& board);


class State
{
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
            {20, -3, 11,  8,  8,  11, -3,  20}};



    State();

    inline bool is_legal_position(Point p);

    bool is_next_to_opposite(_2d board, Point p, int color);
    std::vector<Point> get_legal_points(int color);

    std::vector<Point> get_flippable_in_direction(int color, Point start_point, Point direction);

    std::vector<Point> get_all_flippable(int color, Point st_pt);

    int heuristic(int color);

    int calculate_pieces_ratio(int color);

    int calculate_weighted_pieces(int color);

    int calculate_corners_ratio(int color);

    int calculate_close_corner_ratio(int color);

    void reset();
};
