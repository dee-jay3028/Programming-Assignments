#ifndef BUS_H
#define BUS_H
#include "transporter.h"
#include <iostream>
#define MAX_SIZE 100

//Bus class to extend transporter by adding fare & template array

template <typename T>
class Bus: public Transporter <T> {
    T Items[MAX_SIZE];
    int numItems;
    float fare;
    public:
        Bus();
        Bus(T*, int, float);
        Bus(const Bus&);
        void loadItem(T) override;
        void unloadItem() override;
        void empty() override;
        void move() override;
        bool isEmpty() override;
        int getNumItems() override;
        T getItemAtIndex(int);
        float getTotalFare();
        float getFare();
        void setFare(float);
};

#include "bus.cpp"
#endif