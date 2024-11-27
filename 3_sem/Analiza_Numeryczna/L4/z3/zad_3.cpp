#include<iostream>
#include<cmath>
double fun(double x){
    return x - 0.49;
}

void bisection(const double a, const double b){
    double m, en;
    double tmp_a = a, tmp_b = b;
    for (int n = 0; n <= 5; n++)
    {
        m = (tmp_a + tmp_b)/2.0;
        en = pow(2,-1 * n - 1) * (b - a);

        if(fun(m) < 0){
            tmp_a = m;
        }
        else if (fun(m) == 0)
        {
            std::cout << "m == 0" << std::endl;
        }
        else{
            tmp_b = m;
        }
        std::cout << "dla n = " << n << std::endl;
        std::cout << "Przedział: [" << tmp_a  << "," << tmp_b << "]" << std::endl;
        std::cout << "m: " << m << std::endl;
        std::cout << "bład: " << std::abs(0.49 - m) << std::endl;
        std::cout << "en: " << en << std::endl << std::endl;
    }
    
}
int main(){
    bisection(0, 1);
    return 0;
}