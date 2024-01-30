#pragma once
#include <iostream>

template<class T>
struct QueueNode {
    T value;
    QueueNode<T> *next;
    QueueNode<T> *prev;

    QueueNode(T value, QueueNode<T> *next, QueueNode<T> *prev);
    ~QueueNode();
};

template<class T>
class Queue {
    private:
        QueueNode<T> *head;
        QueueNode<T> *tail;
    public:
        Queue();
        ~Queue();

        bool empty();
        T pop();
        void push(T value);
};
