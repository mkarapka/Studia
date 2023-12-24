#include <iostream>
#include <cmath>
double power_(double value, int exp){
    double  result = 1;
    for(int i = 0; i < exp; i++)
    {
        result = result * value;
    }
    return result;
}
double f(double value){
    double x_14 = power_(value, 14);
    double result = 4046 * (sqrt(x_14 + 1) - 1) / x_14;
    return result;
}


int main(){
    
    std::cout << f(0.001) << std::endl;
    return 0;
}