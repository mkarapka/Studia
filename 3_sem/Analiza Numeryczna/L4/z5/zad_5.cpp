#include<iostream>
#include<cmath>

double fun_2(double xn, double R, int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << xn << ", i = " << i << std::endl;
        xn = xn * (2 - xn * R);
    }
    
    return xn;
}

int main(){
    // Dla 6, [5,5,5], śr = 5
    // std::cout << fun_2 (0.3, 6, 10) << std::endl;
    // std::cout << fun_2 (0.2, 6, 10) << std::endl;
    // std::cout << fun_2 (0.1, 6, 10) << std::endl;
    
    // std::cout << fun_2 (0.4, 6, 10) << std::endl;
    // std::cout << fun_2 (0.34, 6, 10) << std::endl;

    // Dla 14 [10,6,6], śr = 7
    std::cout << fun_2 (0.14, 14, 10) << std::endl;
    std::cout << fun_2 (0.12, 14, 10) << std::endl;
    std::cout << fun_2 (0.04, 14, 10) << std::endl;
    //std::cout << fun_2 (0.15, 14, 10) << std::endl;
    // /std::cout << fun_2 (0.16, 14, 10) << std::endl;
    
    // Dla 8 [10,3,7], śr = 6
    std::cout << fun_2 (0.24, 8, 10) << std::endl;
    std::cout << fun_2 (0.12, 8, 10) << std::endl;
    std::cout << fun_2 (0.04, 8, 10) << std::endl;
    // std::cout << fun_2 (0.255, 8, 10) << std::endl;
    // std::cout << fun_2 (0.26, 8, 10) << std::endl;

    // (5 + 6 + 7)/3 = 6
    return 0;
}