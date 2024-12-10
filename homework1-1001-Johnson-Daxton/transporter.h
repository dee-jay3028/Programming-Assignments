#ifndef TRANSPORTER_H
#define TRANSPORTER_H

//class interface for any form of transportation with capacity

template <class T>
class Transporter {
    public:
        virtual void loadItem(T) = 0;
        virtual void unloadItem() = 0;
        virtual void empty() = 0;
        virtual void move() = 0;
        virtual bool isEmpty() = 0;
        virtual int getNumItems() = 0;
};

#endif
