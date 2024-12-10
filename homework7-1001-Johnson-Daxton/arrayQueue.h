#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H
#include "queue.h"

//Array based queue implementation pulled from a different assignment

template <class T>
class ArrayQueue: public QueueInterface<T> {
    protected:
        static const int DEFAULT_SIZE = 50;
        T items[DEFAULT_SIZE];
        int front, rear;
    public:
        ArrayQueue();
        bool isEmpty() const; 
        bool enqueue(const T& newEntry); 
        bool dequeue(); 
        T peekFront() const; 
};

#include "arrayQueue.cpp"
#endif