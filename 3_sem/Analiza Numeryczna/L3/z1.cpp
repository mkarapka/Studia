#include <iostream>
#include<cmath>
#include <utility>
// a) 
double wrong_1(double x){
    return pow((pow(x,3) + sqrt(pow(x,6) + pow(2023,2))), -1);
}
double fun_1(double x){
    return (pow(x,3) - sqrt(pow(x,6) + pow(2023,2)))/ pow(2023, 2);
}
// b)
double wrong_2(double x){
    return log2(x) - 2.0;
}
double fun_2(double x){
    return log2(x/4.0);
}
// c)
double wrong_3(double x){
    return pow(x, -3) * (M_1_PI/2.0 - x - 1.0/atan(x));
}
double fun_3(double x){
    return atan(x)/pow(x,3) - 1/pow(x,2);
}
int main(){
    double t1 = fun_1(1000000000.0), w1 = wrong_1(1000000000.0);
    double z = 4.00000000000001;
    double t2 = fun_2(z), w2 = wrong_2(z);
    double t3 = fun_3(0.000000210321321), w3 = wrong_3(0.000000210321321);

    // std::cout << "dobra: " << t1 << " zła: " << w1 << std::endl;
    std::cout << "dobra: " << t2 << " zła: " << w2 << std::endl;
    // std::cout << "dobra: " << t3 << " zła: " << w3 << std::endl;

    return 0;
}