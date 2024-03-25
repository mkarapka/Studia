// Mikołaj Karapka
// 339286
// MBA
#include <iostream>

int main(){
    int a, b;

    std::cin >> a >> b;

    int first = (a + 2023) / 2024 * 2024;
    
    while (first <= b)
    {
        std::cout << first << " ";
        first += 2024;
    }
    return 0;
}