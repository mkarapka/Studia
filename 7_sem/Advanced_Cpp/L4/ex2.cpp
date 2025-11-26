#include <iostream>
#include <vector>
#include <list>
#include <set>

template <typename Container, typename F2>
class po_kolei
{
    Container f1;
    F2 f2;

public:
    po_kolei(Container f1, F2 f2) : f1(f1), f2(f2) {}

    template <typename T>
    void operator()(T &x)
    {
        f1(x);
        f2(x);
    }
};

auto square = [](int &x){
    x = x * x;
    return x;
};

auto addOne = [](int &x){
    x = x + 1;
    return x;
};

auto subOne = [](int &x){
    x = x - 1;
    return x;
};

template <typename Container>
void printContainer(Container cont)
{
    for (auto c : cont)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
    auto cp_nums = nums;

    std::cout << "nums after po_kolei(square, addOne): " << std::endl;
    std::for_each(nums.begin(), nums.end(), po_kolei(square, addOne));
    printContainer(nums);

    std::cout << "nums after po_kolei(po_kolei(square, addOne), subOne): " << std::endl;
    std::for_each(cp_nums.begin(), cp_nums.end(), po_kolei(po_kolei(square, addOne), subOne));
    printContainer(cp_nums);
}