#include <queue.hpp>

template<class T>
QueueNode<T>::QueueNode(T value, QueueNode<T> *next, QueueNode<T> *prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template<class T>
QueueNode<T>::~QueueNode() {
    this->next = this->prev = NULL;
}

template<class T>
Queue<T>::Queue() {
    this->head = this->tail = NULL;
}

template<class T>
Queue<T>::~Queue() {
    QueueNode<T> *p = this->head;
    while (p != NULL) {
        QueueNode<T> *q = p->next;
        delete p;
        p = q;
    }
    this->head = this->tail = NULL;
}

template<class T>
bool Queue<T>::empty() {
    if (this->head == NULL && this->tail == NULL)
        return true;
    else
        return false;
}

template<class T>
T Queue<T>::pop() {
    T value = this->head->value;

    QueueNode<T> *p = this->head;
    if (p->next == NULL)
        this->head = this->tail = NULL;
    else
        this->head = p->next;
    delete p;

    return value;
}

template<class T>
void Queue<T>::push(T value) {
    QueueNode<T> *p = new QueueNode<T>(value, NULL, NULL);
    if (this->tail == NULL) {
        this->head = this->tail = p;
    } else {
        this->tail->next = p;
        p->prev = this->tail;
        this->tail = p;
    }
}

template class Queue<int>;
