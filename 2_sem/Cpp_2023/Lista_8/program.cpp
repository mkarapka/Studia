#include <iostream>
#include "wymierne.hpp"
#include <math.h>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace obliczenia;

int main() {
    Wymierne a(1, 2);
    Wymierne b(2, 3);
    Wymierne c = a + b;
    Wymierne d = a - b;
    Wymierne e = a * b;
    Wymierne f = a / b;
    Wymierne g = -a;
    Wymierne h = !a;

    int liczba = ++a;
    double result = --c;
    std::cout << "a: ";
    to_str(a);
    std::cout << "b: ";
    to_str(b);
    std::cout << "c: ";
    to_str(c);
    std::cout << "d: ";
    to_str(d);
    std::cout << "e: ";
    to_str(e);
    std::cout << "f: ";
    to_str(f);
    std::cout << "g: ";
    to_str(g);
    std::cout << "h ";
    to_str(h);
    std::cout << liczba << std::endl;
    double x = 1, y = 2;
    double z = x/y;
    int ff = round(z);
    std::cout << result << std::endl;
    return 0;
}   
