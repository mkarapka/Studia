#include <iostream>
#include <algorithm>
struct sum
{
    sum():total(0){};
    int total;

    void operator()(int element) 
    { 
       total+=element; 
    }
};
int main()
{
    sum s;

    int arr[] = {0, 1, 2, 3, 4, 5};
    s = std::for_each(arr, arr+6, s);
    std::cout << s.total << std::endl; // prints total = 15;
}