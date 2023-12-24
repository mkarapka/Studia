#include <iostream>
#include<cmath>
#include <utility>
std::pair<double, double> fun_sq(double a, double b, double c){
    double x_1 = -((b + sqrt(pow(b,2) - 4 * a * c))/2 * a);
    double x_2 = -2 * c / (b + sqrt(pow(b,2) - 4 * a * c));
    return std::make_pair(x_1, x_2);
}
std::pair<double, double> wrong_fun(double a, double b, double c){
    double x_1 = -((b + sqrt(pow(b,2) - 4 * a * c))/2 * a);
    double x_2 = -((b - sqrt(pow(b,2) - 4 * a * c))/2 * a);
    return std::make_pair(x_1, x_2);
}
int main(){
    double a = 1, b = 12345678934, c = 1;
    auto result = fun_sq(a, b, c);
    auto result_2 = wrong_fun(a,b,c);
    
    std::cout << result.first << ", " << result.second << std::endl;
    std::cout << result_2.first << ", " << result_2.second << std::endl;

    return 0;
}