#include<iostream>
#include<cmath>

double fun_2(double xn, double a, int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << xn << ", i = " << i << std::endl;
        xn = xn - (a * xn * xn - 1.0) / (2.0 * a * xn);
    }
    
    return xn;
}

int main(){
    std::cout << fun_2(2, 6, 10);
    return 0;
}