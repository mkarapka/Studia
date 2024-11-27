#include<iostream>
#include<cmath>
#include<vector>
std::vector<double> list_of_sequence(int n){
    std::vector<double> lst = {log(2023/2024)};
    for (int i = 1; i <= n; i++)
    {
        double val = 1.0/i - 2023 * lst[i-1];
        lst.push_back(val);
    }
    return lst;
}
void print_list_of_range(int begin, int end, int jump){
    std::vector<double> lst = list_of_sequence(end);
    if(begin >= 0){
        for (int i = begin; i < end+1; i+= jump)
        {
            std::cout << i << ": " <<  lst[i] << std::endl;
        }
    }
}
int main(){
    std::cout << "Wartości całek I_0, I_2, ..., I_20:\n";
    print_list_of_range(0, 20, 2);

    std::cout << "Wartości całek I_1, I_3, ..., I_19:\n";
    print_list_of_range(1, 20, 2);
    return 0;
}