#pragma once

#include <iostream>

namespace calc {
    template<typename T>
    class List {
    private:
        // Wewnętrzna klasa Node, reprezentująca pojedyńczego node
        class Node {
        public:
            Node(const T &v, Node *n = nullptr) : value(v), next(n) {};
            T value;
            Node *next;
        };
    public:
        // Konstruktory i destruktor klasy
        List();
        ~List();
        List(const std::initializer_list<T> &il);
        List(const List &other);
        List(List &&other) noexcept;

        // Podstawowe operacje na liście jednokierunkowej 
        void insert(T value, int pos);
        void addFront(T value);
        void addBack(T value);
        T pop(int pos);
        T popFront();
        T popBack();
        void remove(T value);
        void removeAll(T value);
        int index(T value) const;
        int count(T value) const;
        int length() const;
        bool isEmpty() const;

    
        T &operator[](int index) const;

        friend std::ostream& operator<<(std::ostream& output, const List<T>& list) {
        std::string result = "[";
        if (list.isEmpty()) {
            result += "]";
        } else {
            int l = list.length();
            for (int i = 0; i < l; i++) {
                if constexpr (std::is_same_v<T, std::string>) {
                    result += "\"" + list[i] + "\"";
                } 
                else {result += std::to_string(list[i]);}
                if (i != l - 1)
                    result += ", ";
                else
                    result += "]";
            }
        }
        output << result;
        return output;
    }

    public:
        Node *head;
    };

    // Sprawdzanie czy lista jest posortowana
    template<typename T, typename Compare>
    bool isSorted(List<T> &list, Compare compare );

    // Sortowanie listy
    template<typename T, typename Compare>
    void sort(List<T> &list, Compare compare);

    // Stos
    template<typename T>
    class Stack : protected List<T> {
    public:
        void add(T value) { List<T>::addBack(value); };
        T pop() { return List<T>::popBack(); };
        using List<T>::isEmpty;
        using List<T>::length;

        friend std::ostream &operator<<(std::ostream &output, const Stack<T> &stack) {
            std::string result = "[";
            if (stack.isEmpty()) {
                result += "]";
            } else {
                int l = stack.length();
                for (int i = 0; i < l; i++) {
                    if constexpr (std::is_same_v<T, std::string>) {
                    result += "\"" + stack[i] + "\"";
                    } 
                    else {result += std::to_string(stack[i]);}

                    if (i != l - 1)
                        result += ", ";
                    else
                        result += "]";
                }
            }
            output << result;
            return output;
        }
    };

    // Kolejka 
        template<typename T>
        class Queue : protected List<T> {
        public:
            void add(T value) { Queue<T>::addFront(value); };
            T pop() { return List<T>::popBack(); };
            using List<T>::isEmpty;
            using List<T>::length;

            friend std::ostream &operator<<(std::ostream &output, const Queue<T> &queue) {
                std::string result = "[";
                if (queue.isEmpty()) {
                    result += "]";
                } else {
                    int l = queue.length();
                    for (int i = 0; i < l; i++) {
                        if constexpr (std::is_same_v<T, std::string>) {
                        result += "\"" + queue[i] + "\"";
                        } 
                        else {result += std::to_string(queue[i]);}

                        if (i != l - 1)
                            result += ", ";
                        else
                            result += "]";
                    }
                }
                output << result;
                return output;
            }
        };
    template<typename T, typename Compare>
    void ifSorted(List<T> &list, Compare compare);

    template <typename T>
    void swap(T *a, T *b);
}



