#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() {
        next = prev = nullptr;
    }

    Node(T value) {
        data = value;
        next = prev = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }

};
