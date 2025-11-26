#include <iostream>
#include <limits>
#include <cmath>

int main() {

    std::cout << "The nearest long double number to zero: " << std::numeric_limits<long double>::denorm_min() << std::endl;
    std::cout << "The max number of type long double: " << std::numeric_limits<long double>::max() << std::endl;

    // Is it possible to represent infitiny in this type?
    // Yes
    std::cout << "Inifinity in type long double: " << std::numeric_limits<long double>::infinity() << std::endl;

    std::cout << "Substraction 1 and 1+e == e: " << std::numeric_limits<long double>::epsilon() << std::endl; 
    
}