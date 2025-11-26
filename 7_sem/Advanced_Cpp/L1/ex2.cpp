#include <iostream>
#include <string>
#include <set>

using string_set = std::set<std::string>;
int main()
{
    string_set fruits = {"apple", "orange", "strawberry", "apple"};
    for(auto f : fruits)
    {
        std::cout << f << std::endl;
    }
}