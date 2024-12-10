#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "arrayQueue.h"
#include <iostream>
#include <string>

template <class T>
class PriorityQueue: public ArrayQueue<T> {
    public:
        PriorityQueue();
        bool enqueue(const T& newEntry);
};

#include "priorityQueue.cpp"
#endif