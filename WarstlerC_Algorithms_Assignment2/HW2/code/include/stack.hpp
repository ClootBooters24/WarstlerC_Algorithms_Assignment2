#pragma once
#include <iostream>

template<class T>
struct StackNode {
    T value;
    StackNode<T> *next;

    StackNode(T value, StackNode<T> *next);
    ~StackNode();
};

template<class T>
class Stack {
    private:
        StackNode<T> *head;
    public:
        Stack();
        ~Stack();

        bool empty();
        T pop();
        void push(T value);
};
