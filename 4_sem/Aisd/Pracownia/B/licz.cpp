#include <iostream>
#include <math.h>

struct Point {
    int x, y;
};

float dist(Point p, Point q) {
    float dx = (p.x - q.x), dy = (p.y - q.y);
    return sqrt(dx * dx + dy * dy);
}

float sum_of_dist(Point p1, Point p2, Point p3) {
    return dist(p1, p2) + dist(p2, p3) + dist(p1, p3);
}

void print_points(Point points[], const int &n) {
    std::cout << "(x, y)" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "(" << points[i].x << ", " << points[i].y << ")" << std::endl;
    }
}
int main() {
    Point p1 = {-6, 5}, p2 = {-4, 2}, p3 = {-1, 0}, p4 = {-2, 6}, p5 = {5, 4};
    std::cout << sum_of_dist(p1, p2, p3) << std::endl;
    std::cout << sum_of_dist(p1, p2, p4) << std::endl;
    return 0;
}