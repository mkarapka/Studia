#include <iostream>
#include <cmath>

void solve_quadratic_equation(int a, int b, int c)
{
    if (double delta = b * b - 4 * a * c; delta > 0)
    {
        double x1 = (-b - std::sqrt(delta)) / (2 * a);
        double x2 = (-b + std::sqrt(delta)) / (2 * a);
        std::cout << "Finded Coeffcients: " << "x1: " << x1 << " x2: " << x2 << std::endl;
    }
    else if (delta == 0)
    {
        double x = -b / (2 * a);
        std::cout << "Finded Coeffcients: " << "x: " << x << std::endl;
    }
    else
    {
        std::cout << "No real roots" << std::endl;
    }
}

int main()
{
    solve_quadratic_equation(1, -3, 2); // x^2 - 3x + 2 = 0
    solve_quadratic_equation(1, 2, 1);  // x^2 + 2x + 1 = 0
    solve_quadratic_equation(1, 0, 1);  // x^2 + 1 = 0
}