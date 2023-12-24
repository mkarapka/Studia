#include "lista_3.hpp"
#include <iostream>

int main(){
    Liczba num(10.0);
    num.Show_value(); // Output: 10
    num.History(); // Output: 10

    num.Change_val(20.0);
    num.Show_value(); // Output: 20
    num.History(); // Output: 20 10

    num.Change_val(30.0);
    num.Show_value(); // Output: 30
    num.History(); // Output: 30 20

    num.Change_val(40.0);
    num.Show_value(); // Output: 40
    num.History(); // Output: 40 30

    num.Change_val(50.0);
    num.Show_value(); // Output: 50
    num.History(); // Output: 50 40

    num.Pick(30.0);
    num.Show_value(); // Output: 30

    num.Pick(15.0); // Output: W historii nie ma takiej wartości
    num.Show_value(); // Output: 30

    return 0;
}