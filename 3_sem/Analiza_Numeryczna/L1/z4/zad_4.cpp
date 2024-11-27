#include<iostream>
#include<vector>
#include <iomanip>
std::vector<double> list_of_sequence(int n){
    std::vector<double> lst = {1.0};
    double var = -1.0 * lst[0] / 9.0;
    lst.push_back(var);
    for (int i = 2; i < n+1; i++)
    {
        var = 80.0/9.0 * lst[i-1] + lst[i-2];
        lst.push_back(var);
    }
    return lst;
}

void print_list_of_range(int begin, int end){
    std::vector<double> lst = list_of_sequence(end);
    double x = -1.0/9;
    double var = 1;
    if(begin >= 0){
        for (int i = begin; i < end+1; i++)
        {
            std::cout << "wyraz numer" << i << std::endl;
            std::cout << std::setprecision(16) <<  lst[i] << std::endl;
            std::cout << var << std::endl;
            var = var * x;
            std::cout << std::endl;
            
        }
    }
}

int main(){
    print_list_of_range(0,50);
    return 0;
}