#include <iostream>
#include <vector>
#include <utility>
#include <set>

auto range_binary_search(std::vector<int> &numbers, int target)
{
    auto left = numbers.begin(), right = numbers.end();

    while (right > left)
    {
        auto mid = left + (right - left) / 2;

        if (auto cmp = *mid <=> target; cmp >= 0)
            right = mid;
        else
            left = mid + 1;
    }
    auto first = left;

    right = numbers.end();
    while (right > left and *(left + 1) == target)
    {
        auto mid = left + (right - left) / 2;

        if (auto cmp = *mid <=> target; cmp > 0)
            right = mid - 1;
        else
            left = mid;
    }
    auto last = left;

    return std::make_pair(first, last);
}

int main()
{
    std::vector<int> numbers = {1, 2, 3, 3, 3, 5, 5, 5, 6, 7, 7, 7, 7, 8, 9, 10, 11, 11, 11, 11, 12, 13, 13};
    std::set reduced_numbers(numbers.begin(), numbers.end());

    for (auto n : reduced_numbers)
    {
        auto [left, right] = range_binary_search(numbers, n);
        std::cout << 
        "Range for " << n << ": " << 
        "[" << std::distance(numbers.begin(), left) << ", " << 
        std::distance(numbers.begin(), right) << "]" << std::endl;
    }
}