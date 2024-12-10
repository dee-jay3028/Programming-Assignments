#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <iostream>

class Event {
    int time, duration;
    std::string type;
    public:
        Event();
        Event(int, int, std::string);
        Event(const Event& rhs);
        int getTime();
        int getDuration();
        std::string getType();
        void setTime(int);
        void setDuration(int);
        void setType(std::string);
        bool operator>=(const Event& other) const;
};

#endif