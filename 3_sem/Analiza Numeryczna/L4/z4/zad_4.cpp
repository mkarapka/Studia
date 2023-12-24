#include<iostream>
#include<cmath>
double fun(double x){
    return pow(x,4) - log(x + 4);
}
double bisection(double a, double b, double e){
    double m;
    while (std::abs(b - a) > e)
    {
        m = (a + b) / 2.0;

        if(fun(m) < 0) a = m;

        else if (fun(m) == 0) return m;

        else b = m;
    }
    return m;
}
int main(){
    std::cout << "Dla przedziału [-2,0]: " << bisection(0, -2.0, pow(10,-8)) << std::endl;
    std::cout << "Dla przedziału [0,2]: " << bisection(0, 2.0, pow(10,-8)) << std::endl;


    return 0;
}