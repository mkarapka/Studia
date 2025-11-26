#include <iostream>
#include <limits>
#include <string>

int main()
{
    auto min = std::numeric_limits<long long int>::min();
    auto max = std::numeric_limits<long long int>::max();
    auto max_str = std::to_string(max);
    // auto is = std::numeric_limits<long long int>::is
    std::cout << min << std::endl;
    std::cout << max << std::endl;
    std::cout << "Ilość cyfr dziesiętnych dla max:" << max << " : " << max_str.length() << std::endl;
}