#include <stack.hpp>

template<class T>
StackNode<T>::StackNode(T value, StackNode<T> *next) {
    this->value = value;
    this->next = next;
}

template<class T>
StackNode<T>::~StackNode() {
    this->next = NULL;
}

template<class T>
Stack<T>::Stack() {
    this->head = NULL;
}

template<class T>
Stack<T>::~Stack() {
    StackNode<T> *p = this->head;
    while (p != NULL) {
        StackNode<T> *q = p->next;
        delete p;
        p = q;
    }
    this->head = NULL;
}

template<class T>
bool Stack<T>::empty() {
    if (this->head == NULL)
        return true;
    else
        return false;
}

template<class T>
T Stack<T>::pop() {
    T value = this->head->value;
    StackNode<T> *p = this->head;
    if (p->next == NULL)
        this->head = NULL;
    else
        this->head = p->next;
    delete p;
    return value;
}

template<class T>
void Stack<T>::push(T value) {
    StackNode<T> *p = new StackNode<T>(value, NULL);
    if (this->head == NULL) {
        this->head = p; 
    } else {
        p->next = this->head;
        this->head = p;
    }
}

template class Stack<int>;
