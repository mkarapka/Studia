#include <iostream>
#include <functional>
int main() {
    std::function<void(int)> collatz = [&collatz](int n) -> void {
        std::cout << n << " ";

        // warunek zakończenia rekurencji
        if(n == 1) {
            return;
        }

        // rekurencyjne wywołanie
        else if(n % 2 == 0) {
            collatz(n / 2);
        }
        else {
            collatz(3 * n + 1);
        }
    };

    collatz(6);  // na przykład dla liczby 6
    return 0;
}
