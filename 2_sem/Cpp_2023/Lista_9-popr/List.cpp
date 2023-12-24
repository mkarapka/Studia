#include "List.hpp"
#include <iostream>

// funkcje związane z sortowaniem
template<typename T, typename Compare>
void calc::ifSorted(List<T> &list, Compare compare){
    if(isSorted(list,compare)){
        std::cout << "Lista jest posortowana :)" << std::endl;
    }
    else{
        std::cout << "Lista nie jest posortowana :(" << std::endl;
    }
}

template <typename T, typename Compare>
bool calc::isSorted(List<T> &list, Compare compare)
{
    if (list.isEmpty()){
        return true;
    }
    else if (list.length() == 1){
        return true;
    }
    else
    {
        for (int i = 0; i < list.length() - 1; i++)
        {
            
            if (!compare(list[i], list[i + 1])){
                return false;
            }
        }
        return true;
    }
}

template <typename T, typename Compare>
void calc::sort(List<T> &list, Compare compare)
{
    int ind_max;
    for (int i = 0; i < list.length(); i++)
    {
        ind_max = i;
        for (int j = i + 1; j < list.length(); j++)
        {
            if (compare(list[j], list[ind_max]))
                ind_max = j;
        }
        swap(list[i], list[ind_max]);
    }
}

template <typename T>
void calc::swap(T *a, T *b)
{
    T t = *a;
    *a = *b;
    *b = t;
}
//------------------------------------------

// podstawowe operacje na Listach
template <typename T>
bool calc::List<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
int calc::List<T>::length() const
{
    if (isEmpty())
    {
        return 0;
    }
    int i = 1;
    Node *actualNode = head;
    while (actualNode->next != nullptr)
    {
        i++;
        actualNode = actualNode->next;
    }
    return i;
}

template <typename T>
int calc::List<T>::count(T value) const
{
    int i = 0;
    Node *actualNode = head;
    while (actualNode->next != nullptr)
    {
        if (actualNode->value == value)
            i++;
        actualNode = actualNode->next;
    }
    if (actualNode->value == value)
        i++;
    return i;
}

template <typename T>
int calc::List<T>::index(T value) const
{
    if (head->value == value)
        return 0;
    int i = 1;
    Node *actualNode = head;
    while (actualNode->next != nullptr && actualNode->next->value != value)
    {
        actualNode = actualNode->next;
        i++;
    }
    if (i == length())
        return -1;
    return i;
}

template <typename T>
void calc::List<T>::removeAll(T value)
{
    Node* prev = nullptr;
    Node* actualNode = head;
    
    while (actualNode->value == value and actualNode != nullptr)
    {
        head = actualNode->next;
        delete actualNode;
        actualNode = head;
    }
    if(actualNode != nullptr){
        prev = actualNode;
        actualNode = actualNode->next;
        while (actualNode != nullptr)
        {
            if(actualNode->value == value){
                prev->next = actualNode->next;
                delete actualNode;
                actualNode = prev->next;
            }
            else{
                prev = actualNode;
                actualNode = actualNode->next;
            }
        }
        prev->next = actualNode;
    }
    delete actualNode;
}
    
template <typename T>
void calc::List<T>::remove(T value)
{
    Node* tmp;
    Node *actualNode = head;
    while (actualNode->next != nullptr && actualNode->next->value != value)
    {
        actualNode = actualNode->next;
    }
    if (actualNode->next != nullptr){
        tmp = actualNode->next;
        actualNode->next = actualNode->next->next;
        delete tmp;
    }
}

template <typename T>
T calc::List<T>::popBack()
{
    if (isEmpty())
        throw std::range_error("Nie można usunąć ostatniego elementu z pustej listy!");
    Node *actualNode = head;
    Node* tmp;
    if (actualNode->next == nullptr)
    {
        tmp = actualNode;
        T returnValue = actualNode->value;
        head = nullptr;
        delete tmp;
        return returnValue;
    }
    while (actualNode->next->next != nullptr)
    {
        actualNode = actualNode->next;
    }
    T returnValue = actualNode->next->value;
    tmp = actualNode->next;
    actualNode->next = nullptr;
    delete tmp;
    return returnValue;
}

template <typename T>
T calc::List<T>::popFront()
{
    Node* tmp;
    if (isEmpty())
        throw std::range_error("Nie można usunąć ostatniego elementu z pustej listy!");
    T returnValue = head->value;
    tmp = head;
    head = head->next;
    delete tmp;
    return returnValue;
}

template <typename T>
T calc::List<T>::pop(int pos)
{
    if (isEmpty())
    {
        throw std::range_error("Nie można usunąć elementu z pustej listy!");
    }
    else if (pos == 0)
    {
        return popFront();
    }
    else
    {
        if (pos >= length())
        {
            throw std::range_error("Nie mozna usunac elementu z listy z podanej pozycji!");
        }
        int i = 1;
        Node *actualNode = head;
        while (i != pos)
        {
            actualNode = actualNode->next;
            i++;
        }
        T returnValue = actualNode->value;
        Node* tmp = actualNode->next;
        actualNode->next = actualNode->next->next;
        delete tmp;
        return returnValue;
    }
}

template <typename T>
void calc::List<T>::addBack(T value)
{
    if (isEmpty())
    {
        head = new Node(value);
    }
    else
    {
        Node *actualNode = head;
        while (actualNode->next != nullptr)
        {
            actualNode = actualNode->next;
        }
        actualNode->next = new Node(value);
    }
}

template <typename T>
void calc::List<T>::addFront(T value)
{

    Node *newNode = new Node(value);
    if (!isEmpty())
    {
        newNode->next = head;
    }
    head = newNode;
}

template <typename T>
void calc::List<T>::insert(T value, int pos)
{
    if (pos == 0)
        addFront(value);
    else
    {
        if (pos > length())
        {
            throw std::range_error("Nie mozna dodac elementu do listy na podana pozycje!");
        }
        Node *newNode = new Node(value);
        int i = 1;
        Node *actualNode = head;
        while (i != pos)
        {
            actualNode = actualNode->next;
            i++;
        }
        newNode->next = actualNode->next;
        actualNode->next = newNode;
    }
}

// konstruktory
template <typename T>
calc::List<T>::List(List<T> &&other) noexcept
{
    head = other.head;
    other.head = nullptr;
}

template <typename T>
calc::List<T>::List(const std::initializer_list<T> &il) : List()
{
    for (T e : il)
    {
        addBack(e);
    }
}

template <typename T>
calc::List<T>::List(const List<T> &other) : List()
{
    Node *actualNode = other.head;
    while (actualNode != nullptr)
    {
        addBack(actualNode->value);
        actualNode = actualNode->next;
    }
}

template <typename T>
calc::List<T>::List()
{
    head = nullptr;
}

template <typename T>
calc::List<T>::~List()
{
    while (head)
    {
        Node *next = head->next;
        delete head;
        head = next;
    }
}

template <typename T>
T &calc::List<T>::operator[](int idx) const
{
    if (isEmpty())
    {
        throw std::range_error("Pusta lista!");
    }
    else if (idx == 0)
    {
        return head->value;
    }
    else
    {
        if (idx >= length())
        {
            throw std::range_error("Nie ma na liscie elementu o podanej pozycji!");
        }
        int i = 0;
        Node *actualNode = head;
        while (i != idx)
        {
            actualNode = actualNode->next;
            i++;
        }
        return actualNode->value;
    }
}