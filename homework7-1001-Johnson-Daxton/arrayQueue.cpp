#include "arrayQueue.h"

template <typename T>
ArrayQueue<T>::ArrayQueue(){
    front = rear = -1;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const{
    return (front == -1);
}

template <typename T>
bool ArrayQueue<T>::enqueue(const T& newEntry){
    if(rear + 1 == front || (front == 0 && rear == DEFAULT_SIZE)){
        throw "array full!";
    }
    rear++;
    if(rear == DEFAULT_SIZE){
        rear = 0;
    }
    if(front == -1){
        front = 0;
    }
    items[rear] = newEntry;
    return true;
}

template <typename T>
bool ArrayQueue<T>::dequeue(){
    if(isEmpty()){
        throw "array empty!";
    }
    if(front == rear){
        front = rear = -1;
    } else {
        front++;
        if(front == DEFAULT_SIZE){
            front = 0;
        }
    }
    return true;
}

template <typename T>
T ArrayQueue<T>::peekFront() const{
    if(isEmpty()){
        throw "array empty!";
    }
    return items[front];
}