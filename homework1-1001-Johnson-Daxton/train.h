#ifndef TRAIN_H
#define TRAIN_H
#include "transporter.h"
#include <iostream>
#define MAX_SIZE 100

//Train template class to extend Transporter by adding array of items and weight attribute

template <class T>
class Train: public Transporter <T> {
    T Items[MAX_SIZE];
    int numItems;
    public:
        Train();
        Train(T*, int);
        Train(const Train& rhs);
        void loadItem(T) override;
        void unloadItem() override;
        void empty() override;
        void move() override;
        bool isEmpty() override;
        int getNumItems() override;
        T getItemAtIndex(int);
        int getTotalWeight();
};

#include "train.cpp"
#endif 