#pragma once
#include <iostream>

template<class T>
struct LinkedListNode {
    T value;
    LinkedListNode<T> *next;
    LinkedListNode<T> *prev;
    LinkedListNode(T value = 0, LinkedListNode<T>* next = NULL, LinkedListNode<T> *prev = NULL);
    ~LinkedListNode();
};

template<class T>
class LinkedList {
    private:
         LinkedListNode<T> *root;
    public:
         LinkedList();
         ~LinkedList();

         LinkedListNode<T>* insert(T value);
         LinkedListNode<T>* find(T value);
         LinkedListNode<T>* remove(T value);
         int size();

         LinkedListNode<T>* getRoot();
};


