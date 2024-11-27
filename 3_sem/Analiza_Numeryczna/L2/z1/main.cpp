#include <iostream>
#include <cmath>
int main(){

    double x = 0.001;
    std::cout << 1.0 /(sqrt( pow(x,14) + 1 ) + 1) << std::endl;
    return 0;
}