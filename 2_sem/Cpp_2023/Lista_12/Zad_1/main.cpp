#include<iostream>
#include "func.hpp"
int main() {
    
    // Create data
    std::vector<double> vd = {1.1, 2.2, 3.3};
    std::set<int> si = {1, 2, 3, 4};
    std::list<float> lf = {1.2f, 2.3f, 3.4f};

    // Create sumators
    Sumator<double> sumator_vd;
    Sumator<int> sumator_si;
    Sumator<float> sumator_lf;

    // Use std::for_each to accumulate values
    sumator_vd = std::for_each(vd.begin(), vd.end(), sumator_vd);
    sumator_si = std::for_each(si.begin(), si.end(), sumator_si);
    sumator_lf = std::for_each(lf.begin(), lf.end(), sumator_lf);

    std::cout << "double:\n";
    std::cout << "Sum: " << sumator_vd.getSum() << std::endl;
    std::cout << "Count: " << sumator_vd.getCount() << std::endl;
    std::cout << "Average: " << sumator_vd.getAverage() << std::endl;

    std::cout << "\nint:\n";
    std::cout << "Sum: " << sumator_si.getSum() << std::endl;
    std::cout << "Count: " << sumator_si.getCount() << std::endl;
    std::cout << "Average: " << sumator_si.getAverage() << std::endl;

    std::cout << "\nfloat:\n";
    std::cout << "Sum: " << sumator_lf.getSum() << std::endl;
    std::cout << "Count: " << sumator_lf.getCount() << std::endl;
    std::cout << "Average: " << sumator_lf.getAverage() << std::endl;
    return 0;
}
