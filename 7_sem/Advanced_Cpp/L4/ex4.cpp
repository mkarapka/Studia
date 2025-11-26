#include <iostream>
#include <functional>

int main()
{
    std::function<int(int, int)> binom = [&binom](int n, int k){
        if (k > n) return 0;
        if (n == k || k == 0) return 1;
        return binom(n-1, k-1) + binom(n-1, k);
    };

    std::vector<std::pair<int, int>> pairs = {
        {8, 3}, {10, 6}, {2, 11}, {5, 4}, {7, 7},
        {4, 10},{12, 1}, {0, 9}, {3, 8}, {6, 2}
    };

    for(auto [n, k] : pairs)
    {
        std::cout << "binomial (" << n << ", " << k << ") == " << binom(n, k) << std::endl; 
    }
}