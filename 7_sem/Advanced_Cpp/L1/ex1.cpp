#include <iostream>
#include <string>

int main()
{
    std::string ii_uwr = R"(
    Instytut Informatyki Uniwersytetu Wrocławskiego,
    Fryderyka Joliot-Curie 15, 
    50-300 Wrocław
    )";

    std::string windows_path = R"(C:\Program Files\Common Files\Microsoft Shared)";

    std::string quotes_and_brackets = R"txt())))))))))()"()))\n"""""""""""")txt";

    std::cout << ii_uwr << std::endl;
    std::cout << windows_path << std::endl;
    std::cout << quotes_and_brackets << std::endl;
}