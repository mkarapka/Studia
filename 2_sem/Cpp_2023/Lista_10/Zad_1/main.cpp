#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "manipulators.hpp"
using namespace manips;
int main() {
    std::vector<std::string> lines;
    std::string line;

    std::cout << "Podaj linie, zeby zakonczyc pozostaw linie pusta" << colon << std::endl;

    while (std::getline(std::cin, line) && !line.empty()) {
        lines.push_back(line);
    }

    std::sort(lines.begin(), lines.end());

    for (int i = 0; i < lines.size(); i++) {
        std::cout << index(i, 2) << colon << lines[i] << '\n';
    }

    std::cout << "Podaj dwie linie" << colon <<  std::endl;
    while (std::getline(std::cin >> clearline, line) && !line.empty()) {
        std::cout << "Wprowadzono" << colon << line << '\n';
    }

    std::cout << "Podaj linie:" << std::endl;
    std::cin >> ignore(3) >> line;
    std::cout << "Linia bez 3 pierwszych znakow, poprzedona przecikiem" 
    << colon << comma << line << std::endl;

    return 0;
}