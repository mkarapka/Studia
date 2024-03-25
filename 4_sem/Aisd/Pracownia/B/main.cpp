#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    int x, y;
};

struct Result {
    Point tab[3];
    float dist = __FLT_MAX__;
};

void print_result(Result res) {
    for (int i = 0; i < 3; i++) {
        printf("%d %d\n", res.tab[i].x, res.tab[i].y);
    }
}

bool compare_x(Point &p1, Point &p2) { return p1.x < p2.x; }

bool compare_y(Point &p1, Point &p2) { return p1.y < p2.y; }

float dist(Point p, Point q) {
    float dx = (p.x - q.x), dy = (p.y - q.y);
    return sqrt(dx * dx + dy * dy);
}

float sum_of_dist(Point p1, Point p2, Point p3) {
    return dist(p1, p2) + dist(p2, p3) + dist(p1, p3);
}

Result min(Result &r1, Result &r2) { return (r1.dist < r2.dist) ? r1 : r2; }

Result bF(Point points[], int n) {
    Result res;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int p = j + 1; p < n; p++) {
                float d = sum_of_dist(points[i], points[j], points[p]);
                if (d < res.dist) {
                    res.dist = d;
                    res.tab[0] = points[i];
                    res.tab[1] = points[j];
                    res.tab[2] = points[p];
                }
            }
        }
    }
    return res;
}

void stripCl(std::vector<Point> &strip, float d, Result &res) {
    typedef std::vector<Point> vec;
    float tmp = d;
    for (auto i = vec::size_type(0); i < strip.size(); i++) {
        for (auto j = vec::size_type(i + 1);
             j < strip.size() && (strip[j].y - strip[i].y < d); j++) {
            for (auto p = vec::size_type(j + 1);
                 p < strip.size() && (strip[p].y - strip[i].y < d); p++) {
                tmp = sum_of_dist(strip[i], strip[j], strip[p]);
                if (tmp < d) {
                    d = tmp;
                    res.dist = d;
                    res.tab[0] = strip[i];
                    res.tab[1] = strip[j];
                    res.tab[2] = strip[p];
                }
            }
        }
    }
}

Result smallest_trio(Point Px[], Point Py[], int n) {
    if (n < 6) {
        return bF(Px, n);
    }

    int mid = n / 2;
    Point mid_point = Px[mid];

    Point PyL[mid];
    Point PyR[n - mid];

    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (Py[i].x <= mid_point.x) {
            PyL[l] = Py[i];
            l++;
        } else {
            PyR[r] = Py[i];
            r++;
        }
    }

    Result resL = smallest_trio(Px, PyL, mid);
    Result resR = smallest_trio(Px + mid, PyR, n - mid);

    Result resMin = min(resL, resR);
    float d = resMin.dist / 2;

    std::vector<Point> strip;
    for (int i = 0; i < n; i++) {
        if (abs(Py[i].x - mid_point.x) < d) {
            strip.push_back(Py[i]);
        }
    }

    Result check_strip;
    stripCl(strip, d, check_strip);
    return check_strip.dist < resMin.dist ? check_strip : resMin;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points_x[n], points_y[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points_x[i].x, &points_x[i].y);
        points_y[i] = points_x[i];
    }

    // Sorting points to recive arrays order by x and y
    std::sort(points_x, points_x + n - 1, compare_x);
    std::sort(points_y, points_y + n - 1, compare_y);

    Result res = smallest_trio(points_x, points_y, n);
    print_result(res);

    return 0;
}