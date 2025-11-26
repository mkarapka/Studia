#include <iostream>
#include <vector>
#include <string>


struct Person
{
    std::string name;
    std::string last_name;
    unsigned age;
};

std::vector<Person> sort_records(std::vector<Person> persons_list)
{
    std::sort(persons_list.begin(), persons_list.end(), 
        [&](Person L, Person R){return std::tie(L.last_name, L.name, L.age) > std::tie(R.last_name, R.name, R.age);});
    return persons_list;
}

int main()
{
    std::vector<Person> persons_list = {
        {"Anna", "Kowalski", 28},
        {"Piotr", "Nowak", 35},
        {"Maria", "Wiśniewska", 42},
        {"Jan", "Kowalski", 31},      
        {"Katarzyna", "Dąbrowska", 26},
        {"Tomasz", "Lewandowski", 29},
        {"Agnieszka", "Wójcik", 33},
        {"Marcin", "Kamiński", 24},
        {"Magdalena", "Kowalczyk", 37},
        {"Robert", "Zieliński", 40},
        {"Aleksandra", "Szymański", 22},
        {"Michał", "Kowalski", 45}    
    };

    auto sorted_persons_list = sort_records(persons_list);
    for(auto p : sorted_persons_list)
    {
        std::cout << "[" << p.name << ", " << p.last_name << ", " << p.age << "]" << std::endl;
    }
}