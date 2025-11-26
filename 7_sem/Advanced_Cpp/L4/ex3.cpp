#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <utility>
#include <numeric>

template <typename Container>
void printContainer(Container cont)
{
    for (auto c : cont)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

template <typename T>
class checkIfInRange
{
    T a, b;

public:
    checkIfInRange(T a, T b) : a(a), b(b) {}

    bool operator()(T x)
    {
        return x > a && x < b;
    }
};

class KthFromP
{
    int k, p, idx;

public:
    KthFromP(int k_in, int p_in) : k(k_in), p(p_in), idx(0) {}

    template <class T>
    void operator()(const T &x)
    {
        if (idx >= p && (idx - p) % k == 0)
            std::cout << x << " ";
        idx++;
    }
};

template<typename T>
struct Concat
{
    T operator()(T acc, T s) const { return acc + s; }
};

template<typename Container>
class findMinMax
{
public:
    auto operator()(const Container& container) const {
        using T = typename Container::value_type;

        if (container.empty())
            return std::make_pair(T{}, T{});

        T min = *container.begin();
        T max = *container.begin();

        for(const auto& item : container) {
            if (item < min) min = item;
            if (item > max) max = item;
        }
        return std::make_pair(min, max);
    }
};

int main()
{
    std::vector<double> nums = {1.2, 2.0, 3.1, 4.5, 5.4, 6.2, 7.7, 8.0};
    std::list<int> lst = {3, 15, 7, 2, 8, 1, 20, 5};
    std::set<std::string> words = {"Abc", "xyz", "hello", "world", "lorem", "ipsum"};


    // Printing values from certain range
    std::vector<double> filtered_nums;
    std::copy_if(nums.begin(), nums.end(), std::back_inserter(filtered_nums), checkIfInRange<double>(3.0, 6.0));
    printContainer(filtered_nums);

    std::list<int> filtered_lst;
    std::copy_if(lst.begin(), lst.end(), std::back_inserter(filtered_lst), checkIfInRange<int>(3, 15));
    printContainer(filtered_lst);

    std::set<std::string> filtered_words;
    std::copy_if(
        words.begin(), 
        words.end(), 
        std::inserter(filtered_words, filtered_words.end()), 
        checkIfInRange<std::string>("abc", "world")); 
    printContainer(filtered_words);


    // Printing every kth value from p position
    std::cout << "Every 2sd number from position 1:" << std::endl;
    KthFromP fun_double(2, 1);
    std::for_each(nums.begin(), nums.end(), fun_double);
    std::cout << std::endl;

    std::cout << "Every 3td number from position 2:" << std::endl;
    KthFromP fun_int(3, 2);
    std::for_each(lst.begin(), lst.end(), fun_int);
    std::cout << std::endl;

    std::cout << "Every 2sd number from position 0:" << std::endl;
    KthFromP fun_str(2, 0);
    std::for_each(words.begin(), words.end(), fun_str);
    std::cout << std::endl;
    

    // Select min and max element'
    auto pair_double = findMinMax<std::vector<double>>()(nums);
    std::cout << "Min: " << pair_double.first << ", Max: " << pair_double.second << std::endl;

    auto pair_int = findMinMax<std::list<int>>()(lst);
    std::cout << "Min: " << pair_int.first << ", Max: " << pair_int.second << std::endl;

    auto pair_str = findMinMax<std::set<std::string>>()(words);
    std::cout << "Min: " << pair_str.first << ", Max: " << pair_str.second << std::endl;
    

    // String concatenation
    std::string concat_result = std::accumulate(words.begin(), words.end(), std::string(), Concat<std::string>());
    std::cout << "Concatenation of set<string>: " << concat_result << std::endl;
}