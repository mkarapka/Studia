#include <iostream>
#include<string>
#include "List.hpp"
#include "List.cpp"
bool CompareStrings(const std::string& str1, const std::string& str2) {
    if(str1 == str2) return 1;
    return std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end());
}

int main() {

    calc::List<std::string> list;
    
    std::cout << "Długość listy przed dodaniem elemntów:" << list.length() << std::endl;
    // dodawanie elementów do listy:
    list.addBack("apple");
    list.addBack("banana");
    list.addBack("pineapple");
    std::cout << list << std::endl;
    std::cout << "\nDługość listy po dodaniu elementów:" << list.length() << std::endl;
    // dodanie elementu do na przód listy
    list.addFront("strawberry");
    std::cout << "lista po addFront(Strawberry)" << std::endl;
    std::cout << list << std::endl;

    // usunięcie elementu z lity
    list.pop(1);
    std::cout << "\nStan listy po pop(1)" << std::endl;
    std::cout << list << std::endl;

    list.insert("apple", 1);
    std::cout << "Stan listy po insert(apple, 1)" << std::endl;
    std::cout << list << std::endl;
    calc::List<std::string> list2(list);

    std::cout << "\nStan listy 2, która skopiowała zawartość listy 1" << std::endl;
    std::cout << list2 << std::endl;

    // test popFront() i popBack()
    std::string word;
    word = list2.popBack();
    std::cout << "\nStan listy po popBack()" << std::endl;
    std::cout << list2 << std::endl;
    std::cout << "Zwrócona wartość: ";
    std::cout << word << std::endl;

    word = list2.popFront();
    std::cout << "\nI następnie po popFront()" << std::endl;
    std::cout << list2 << std::endl;
    std::cout << "Zwrócona wartość: ";
    std::cout << word << std::endl;

    // test remove
    list2.addBack("blueberry");
    list2.addBack("banana");
    std::cout << "\nStan listy przed remove(banana)" << std::endl;
    std::cout << list2 << std::endl;
    list2.remove("banana");
    std::cout << "I stan po wykonaniu operacji" << std::endl;
    std::cout << list2 << std::endl;

    // test removeAll
    for (int i = 0; i < 4; i++)
    {
        list2.addFront("orange");
        list2.addFront("raspberry");
    }
    std::cout << "\nDodanie do listy parę zmiennych:" << std::endl;
    std::cout << list2 << std::endl;
    std::cout << "Oraz wyczyszczenie z niej wszystkich zmiennych o nazwie orange" << std::endl;
    list2.removeAll("orange");
    std::cout << list2 << std::endl;

    // test count 
    std::cout << "\nIlość zmiennych o nazwie raspberry: ";
    std::cout << list2.count("raspberry") << std::endl;

    // test index
    std::cout << "Index dla zmiennej o nazwie apple: " << list2.index("apple") << std::endl;
    std::cout << "Index dla zmiennej o nazwie raspberry: " << list2.index("raspberry") << std::endl;

    
    std::cout << "\nWypisanie zmiennej dla indeksu 5: " << list2[5] << std::endl;
    list2.insert("stawberry", 1);
    list2.insert("orange", 4);

    // sortowanie 
    calc::ifSorted(list2,CompareStrings);
    calc::sort(list2,CompareStrings);
    std::cout << list2 << std::endl;
    calc::ifSorted(list2,CompareStrings);
    
    calc::List<std::string> list3 = {"apple", "cherry", "banana", "raspberry" , "orange"};
    std::cout << "\nLista przed i po sortowaniu:" << std::endl << list3 << std::endl; 
    calc::sort(list3,CompareStrings);
    std::cout << list3 << std::endl;;

    // Stack
    calc::Stack<std::string> stack;
    stack.add("apple");
    stack.add("orange");
    stack.add("banana");

    std::cout << "\nZawartość stosu przed pop: " << stack << std::endl;
    stack.pop();
    std::cout << "Zawartość stosu przed pop: " << stack << std::endl;

    // Queue
    calc::Queue<std::string> queue;
    queue.add("apple");
    queue.add("orange");
    queue.add("banana");

    std::cout << "\nKolejka przed pop: " << queue << std::endl;
    queue.pop();
    std::cout << "Kolejka po pop: " << queue << std::endl;
}
