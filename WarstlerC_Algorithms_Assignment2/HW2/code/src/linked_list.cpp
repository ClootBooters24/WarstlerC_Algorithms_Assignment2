#include <linked_list.hpp>

template<class T>
LinkedListNode<T>::LinkedListNode(T value, LinkedListNode<T>* next, LinkedListNode<T>* prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template<class T>
LinkedListNode<T>::~LinkedListNode() {
    this->next = NULL;
}


template<class T>
LinkedList<T>::LinkedList() {
     this->root = NULL;
}

template<class T>
LinkedList<T>::~LinkedList() {
    LinkedListNode<T> *p = this->root;
    while (p != NULL) {
        LinkedListNode<T> *q = p->next;
        delete p;
        p = q;
    }
    this->root = NULL;
}


template<class T>
LinkedListNode<T>* LinkedList<T>::insert(T value) {
    LinkedListNode<T> *p = this->find(value);
    if (p != NULL)
        return p;
    p = new LinkedListNode<T>(value, NULL);
    if (this->root == NULL)
        this->root = p;
    else {
        p->next = this->root;
        this->root = p;
    }
    return p;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::find(T value) {
    LinkedListNode<T> *p = this->root;
    while (p != NULL && p->value != value)
        p = p->next;
    return p;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::getRoot() {
    return this->root;
}



template<class T>
LinkedListNode<T>* LinkedList<T>::remove(T value) {
    LinkedListNode<T> *p = this->root;
    LinkedListNode<T> *q = NULL;

    while (p != NULL) {
        if (p->value == value) {
             if (q == NULL) 
                 this->root = p->next;
            else
                 q->next = p->next;
            delete p;
            break;
         }
        q = p;
        p = p->next;
    }

    return this->root;
}


template<class T>
int LinkedList<T>::size() {
    int cnt = 0;
    for (LinkedListNode<T> *p = this->root; p != NULL; p = p->next)
        ++cnt;
    return cnt;
}

template class LinkedListNode<int>;
template class LinkedList<int>;

