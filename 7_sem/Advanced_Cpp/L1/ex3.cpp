#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include <vector>

enum class names : u_int16_t
{
    Mikołaj,
    Michał,
    Maja,
    Agata,
    Kamil,
    Robert,
    Anastazja
};

void say_something(std::string statement, names name)
{
    switch (name)
    {
    case names::Mikołaj:
        std::cout << "Hi Mikołaj, " << statement << std::endl;
        break;
    case names::Michał:
        std::cout << "Hi Michał, " << statement << std::endl;
        break;
    case names::Maja:
        std::cout << "Hi Maja, " << statement << std::endl;
        break;
    case names::Agata:
        std::cout << "Hi Agata, " << statement << std::endl;
        break;
    case names::Kamil:
        std::cout << "Hi Kamil, " << statement << std::endl;
        break;
    case names::Robert:
        std::cout << "Hi Robert, " << statement << std::endl;
        break;
    case names::Anastazja:
        std::cout << "Hi Anastazja, " << statement << std::endl;
        break;
    default:
        break;
    }
}

std::string rand_choice(std::vector<std::string> statements)
{
    auto rand_idx = rand() % statements.size();
    return statements[rand_idx];
}

int main()
{
    std::vector<names> names_list = {
        names::Mikołaj, 
        names::Robert, 
        names::Michał, 
        names::Maja, 
        names::Agata, 
        names::Anastazja, 
        names::Kamil
    };

    std::vector<std::string> statements = {"How you're doing?", "How was yesterday?", "Nice to meet you."};

    for(auto n : names_list)
    {
        say_something(rand_choice(statements), n);
    }
}