#include <iostream>
#include <ratio>

template<int N>
struct HarmonicNumber;

template<>
struct HarmonicNumber<1> {
    using type = std::ratio<1, 1>;
};

template<int N>
struct HarmonicNumber {
    using type = std::ratio_add<typename HarmonicNumber<N-1>::type, std::ratio<1, N>>;
};


int main() {
    HarmonicNumber<43>::type harmonicValue;
    std::cout << harmonicValue.num << "/" << harmonicValue.den;
}