#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

class Person
{
public:
    string name;
    string last_name;
    int age;
    int weight;
    double height;
    Person(const string& n, const string& ln, int a, int w, double h)
        : name(n), last_name(ln), age(a), weight(w), height(h) {}
};

auto calculateBMI = [](const Person& p) {
    // BMI = weight(kg) / (height(m) * height(m))
    return p.weight / (p.height * p.height);
};

ostream& operator<<(ostream& os, const Person& p)
{
    os << p.name << " " << p.last_name << ", Age: " << p.age
       << ", Weight: " << p.weight << "kg, Height: " << p.height << "m"
       << ", BMI: " << calculateBMI(p);
    return os;
}

void printPeople(const deque<Person> people)
{
    for(const auto& p : people)
    {
        cout << p << endl;
    }
}

int main()
{
    std::deque<Person> people = {
        {"Anna",    "Kowalska",    29,  64, 1.68},
        {"Marek",   "Nowak",       40,  94, 1.82},
        {"Ewa",     "Wiśniewska",  18,  53, 1.60},
        {"Tomasz",  "Wójcik",      54,  102, 1.74},
        {"Zofia",   "Kamińska",    71,  70, 1.65},
        {"Jan",     "Lewandowski", 33,  85, 1.91},
        {"Piotr",   "Dąbrowski",   27, 109, 1.97},
        {"Alicja",  "Zielińska",   22,  59, 1.66},
        {"Maria",   "Szymańska",   46,  88, 1.73},
        {"Paweł",   "Wójcik",      37, 120, 1.93},
        {"Magda",   "Krawczyk",    31,  67, 1.70},
        {"Kamil",   "Szulc",       42, 112, 1.80}
    };

    cout << "BMI before sorting:" << endl;
    auto people_cp = people;
    printPeople(people_cp);
    cout << "-------------------------" << endl;

    sort(people_cp.begin(), people_cp.end(), [&](const Person& lp, const Person& rp)
        {
            return calculateBMI(lp) < calculateBMI(rp);
        });

    printPeople(people_cp);

    // people_cp = people;
    cout << "Reduced BMI:" << endl;
    transform(people_cp.begin(), people_cp.end(), people_cp.begin(), [](Person person){
        person.weight = person.weight * 0.9;
        return person;
    });
    printPeople(people_cp);

    auto isHeavy = [](const Person& p){
        return p.weight > 100;
    };
    deque<Person> heavy, light;

    copy_if(people_cp.begin(), people_cp.end(), back_inserter(heavy), isHeavy);
    copy_if(people_cp.begin(), people_cp.end(), back_inserter(light), [&](const Person& p){
        return !isHeavy(p);
    });
    cout << "Heavy people (weight > 100kg):" << endl;
    printPeople(heavy);
    cout << "Light people (weight <= 100kg):" << endl;
    printPeople(light);

    cout << "The oldest and the youngest person:" << endl;
    auto minmax_age = minmax_element(people_cp.begin(), people_cp.end(), 
    [](const Person& lp, const Person& rp){
        return lp.age < rp.age;
    });
    cout << "Youngest: " << *(minmax_age.first) << endl;
    cout << "Oldest: " << *(minmax_age.second) << endl;

}