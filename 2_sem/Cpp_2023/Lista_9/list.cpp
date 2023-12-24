#include "list.hpp"
#include<iostream>
template<typename T>
void calc::List<T>::insert(T data, int index){
    Node* new_node = new Node(data);
    if (index == 0) {
        new_node->next = head;
        head = new_node;
    }
    else{
        Node* tmp = head;
        for (int i = 0; i < index - 1 && tmp->next != nullptr; i++)
        {
            tmp = tmp->next;
        }
        new_node->next = tmp->next;
        tmp->next = new_node;
    }

} 

template<typename T> calc::List<T>::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
        std::cout << "chuj";
    }
};

