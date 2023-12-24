#pragma once

namespace calc
{
template<typename T>
class List
{
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& d, Node* n=nullptr) : data(d), next(n) {}

    };

    
public:
    Node* head;
    int size;
    List() : head(nullptr), size(0) {} 
    
    void insert(T data, int index);
 
    ~List();
};
};
