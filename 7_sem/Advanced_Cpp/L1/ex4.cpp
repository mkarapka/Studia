#include <iostream>
#include <string>

auto generate_nth_lucas_number(u_int64_t n)
{
    if(n == 0) return 2ull;
    if(n == 1) return 1ull;
    return generate_nth_lucas_number(n - 1) + generate_nth_lucas_number(n - 2);
}

void print_n_Lucas_numbers(u_int64_t n)
{
    for(u_int64_t i = 0; i < n; i++)
    {
        std::cout << generate_nth_lucas_number(i) << ", ";
        std::cout << typeid(generate_nth_lucas_number(i)).name();
    }
    std::cout << std::endl;
}
// First 16 Lucas numbers
// 2, 1, 3, 4, 7, 11, 18, 29, 47, 76, 123, 199, 322, 521, 843, 1364
int main()
{
    print_n_Lucas_numbers(16);
}