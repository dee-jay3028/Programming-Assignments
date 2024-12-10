#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include "stack.h"
#include "node.h"

template <typename T>
class linkedStack: public StackInterface<T> {
    Node<T>* top;
    public:
        linkedStack();
        bool isEmpty() const; 
        bool push(const T& newEntry); 
        bool pop(); 
        T peek() const;
        ~linkedStack();
};

#include "linkedStack.cpp"
#endif