#include <iostream>
#include <stdexcept>
#include "FileOutput.hpp"
int main()
{
    std::string filename = "test.bin";
    {
        File::Wyjscie out(filename);
        out.zapisz(42);
        out.zapisz(123);
        out.zapisz(85);
    }

    {
        File::Wejscie in1(filename);

        int a, b, c;

        in1.odczytaj(a);
        in1.odczytaj(b);
        in1.odczytaj(c);

        std::cout << "Liczby odczytane z pliku:" << std::endl;
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
    }

    {
        File::Wejscie in2(filename);

        std::cout << "Odczytywanie pliku bajt po bajcie:" << std::endl;

        unsigned char byte;
        do {
            in2.odczytaj(byte);
            std::cout << "Wartosc: " << std::dec << static_cast<int>(byte);
            std::cout << " Hex: " << std::hex << static_cast<int>(byte);
            std::cout << " Znak: ('" << static_cast<char>(byte) << "')" << std::endl;
        } while (!in2.eof());
    }

    return 0;
}

