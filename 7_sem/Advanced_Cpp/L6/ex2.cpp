#include <iostream>
#include <list>

using namespace std;

class Point
{
public:
    int x, y;
    int red, green, blue;
    string name;
    Point(int x, int y, int r, int g, int b, const string &n) : 
    x(x), y(y), red(r), green(g), blue(b), name(n) {}
};

ostream &operator<<(ostream &os, const Point &p)
{
    os << p.name << " (R:" << p.red << ", G:" << p.green << ", B:" << p.blue
       << "), Coords: (" << p.x << ", " << p.y << ")";
    return os;
}

void printColors(const list<Point> &colors)
{
    for (const auto &color : colors)
    {
        cout << color << endl;
    }
}

double getLumination(const Point &p)
{
    return 0.3 * p.red + 0.59 * p.green + 0.11 * p.blue;
}

int main()
{
    list<Point> points = {
        {2, 3, 255, 0, 0, "Red"},
        {-5, 4, 0, 255, 0, "Green"},
        {-2, -2, 0, 0, 255, "Blue"},
        {1, -7, 255, 255, 0, "Yellow"},
        {3, 6, 0, 255, 255, "Cyan"},
        {-6, 7, 255, 0, 255, "Magenta"},
        {-1, 5, 192, 192, 192, "Silver"},
        {4, -6, 128, 128, 128, "Gray"},
        {6, 2, 128, 0, 0, "Maroon"},
        {7, 3, 128, 128, 0, "Olive"},
        {-4, 3, 0, 128, 0, "DarkG"},
        {-8, -5, 128, 0, 128, "Purple"},
        {-6, -8, 0, 128, 128, "Teal"},
        {8, 7, 0, 0, 128, "Navy"},
        {1, 1, 255, 165, 0, "Orange"},
        {0, 8, 210, 105, 30, "Choco"},
        {3, -4, 255, 192, 203, "Pink"},
        {2, 0, 255, 215, 0, "Gold"},
        {-7, 2, 173, 216, 230, "LtBlue"},
        {-5, -1, 34, 139, 34, "Forest"},
        {-8, 0, 47, 79, 79, "Slate"},
        {5, -3, 245, 245, 220, "Beige"},
        {0, 0, 0, 0, 0, "Black"}};

    auto points_cp = points;
    points_cp.remove_if([&](const Point &point)
                        { return point.name.length() > 5; });
    cout << "Points after removing names longer than 5 characters:" << endl;
    printColors(points_cp);


    cout << "-------------------------" << endl;
    auto isQI = [](const Point& p)
    {
        return p.x > 0 && p.y > 0;
    };

    auto isQII = [](const Point& p)
    {
        return p.x < 0 && p.y > 0;
    };
    auto isQIII = [](const Point& p)
    {
        return p.x < 0 && p.y < 0;
    };
    auto isQIV = [](const Point& p)
    {
        return p.x > 0 && p.y < 0;
    };

    int qI = count_if(points.begin(), points.end(), isQI);
    int qII = count_if(points.begin(), points.end(), isQII);
    int qIII = count_if(points.begin(), points.end(), isQIII);
    int qIV = count_if(points.begin(), points.end(), isQIV);
    cout << "Quadrant counts:" << endl;
    cout << "I: " << qI << endl;
    cout << "II: " << qII << endl;
    cout << "III: " << qIII << endl;
    cout << "IV: " << qIV << endl;

    cout << "-------------------------" << endl;
    cout << "Points sorted by lumination (descending):" << endl;
    points_cp = points;
    
    printColors(points_cp);
    points_cp.sort(
        [&](const Point& lp, const Point& rp)
        {
            return getLumination(lp) > getLumination(rp);
        });
    printColors(points_cp);

    auto isDarkPoint = [&](const Point& p)
    {
        return getLumination(p) < 64.0;
    };

    cout << "-------------------------" << endl;
    cout << "Number of dark points (lumination < 64): "
         << count_if(points.begin(), points.end(), isDarkPoint) << endl;

}