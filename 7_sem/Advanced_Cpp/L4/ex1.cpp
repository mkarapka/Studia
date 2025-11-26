#include <iostream>

template <typename T>
using fun = T(*)(T);

template <typename T>
void transform(T tab[], int n, fun<T> f)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = f(tab[i]);
    }
}

int square(int x) { return x * x; }

int main()
{
    int n = 8;
    int tab[n] = {1, 2, 3, 4, 5, 6, 7, 8};

    transform(tab, n, square);

    for (auto elem : tab)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}