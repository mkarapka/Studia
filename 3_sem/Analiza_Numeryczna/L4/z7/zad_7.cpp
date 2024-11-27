#include<iostream>
#include<cmath>

double fun_2(double xn, double a, int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << xn << ", i = " << i << std::endl;
        xn = xn - (xn * xn - a) / (2.0 * xn);
    }
    
    return xn;
}

int main(){
    std::cout << fun_2(0.0000000000000000000000000001, 1/3.0 * 1/256.0, 500);
    std::cout << fun_2(1230, 1/3.0 * 1/256.0, 500);
    // std::cout << fun_2(0.0000000000000000000000000001, 6, 500);
    // std::cout << fun_2(2, 6, 500);

    return 0;
}