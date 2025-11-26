#include <iostream>
#include <memory>
#include <ctime>

class Counter
{
public:
    u_int64_t state = 1;
    ~Counter()
    {
        std::cerr << state;
    }
};


auto increase_random_elements(std::unique_ptr<Counter[]> counters_ptr, int deep, const int size)
{
    if(deep == 0) return counters_ptr;

    int steps = size * 0.1;
    for(int i = 0; i < steps; i++)
    {
        int p_10 = rand() % size;
        counters_ptr[p_10].state += 1;
    }
    return increase_random_elements(std::move(counters_ptr), deep-1, size);
}

int main()
{
    int size = 10;
    std::unique_ptr<Counter[]> counters_ptr = std::make_unique<Counter[]>(size);


    auto result = increase_random_elements(std::move(counters_ptr), 10, size);
    std::cout << "Zawartość Tablicy:" << std::endl;
    for(auto i=0; i<size;i++){
        std::cout << result[i].state;
    }
    std::cout << std::endl << "*************" << std::endl;
}