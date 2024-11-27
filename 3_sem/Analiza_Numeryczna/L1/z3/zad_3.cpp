#include<iostream>
#include<cmath>
template<typename T>
T function(T value){
    T value_2 = value * value;
    T result = 14 * (1 - cos(17.0 * value)) / value_2;
    return result;
}

template<typename T>
void print_result(T value){
    int begin = 11, end = 20;
    for (int i = begin; i <= end; i++)
    {
        std::cout << function(pow(value, -1 * i)) << std::endl;
    }
}

int main(){
    float y = 10;
    double x = 10;

    std::cout << "Dla pojedyńczej precyzji" << std::endl;
    print_result(y);

    std::cout << "Dla podwójnej precyzji" << std::endl;
    print_result(x);
    return 0;
}