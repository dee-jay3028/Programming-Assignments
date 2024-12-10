#include "linkedStack.h"

template <class T>
linkedStack<T>::linkedStack(){
    top = nullptr;
}

template <class T>
bool linkedStack<T>::isEmpty() const {
    if(top != nullptr){
        return false;
    } else {
        return true;
    }
}

template <class T>
bool linkedStack<T>::push(const T& newEntry){
    Node<T>* temp = new Node<T>(newEntry);
    if(top != nullptr){
        temp->setNext(top);
        top = temp;
        return true;
    } else {
        temp->setItem(newEntry);
        top = temp;
        return true;
    }
    return false;
}

template <class T>
bool linkedStack<T>::pop(){
    bool canPop = !isEmpty();
    if(canPop){
        Node<T>* temp = top;
        top = top->getNext();
        delete temp;
    }
    return canPop;
}

template <class T>
T linkedStack<T>::peek() const{
    bool canPeek = !isEmpty();
    if(canPeek){
        return top->getItem();
    } else {
        throw "empty stack";
    }
}

template<class T>
linkedStack<T>::~linkedStack(){
    while(top != nullptr){
        Node<T>* temp = top;
        top = top->getNext();
        delete temp;
    }
}