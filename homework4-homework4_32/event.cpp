#include "event.h"

Event::Event(){
    time = duration = 0;
    type = "null";
}

Event::Event(int nTime, int nDur, std::string nType){
    time = nTime;
    duration = nDur;
    type = nType;
}

Event::Event(const Event& rhs){
    time = rhs.time;
    duration = rhs.duration;
    type = rhs.type;
}

int Event::getTime(){
    return time;
}

int Event::getDuration(){
    return duration;
}

std::string Event::getType(){
    return type;
}

void Event::setTime(int nTime){
    time = nTime;
}

void Event::setDuration(int nDur){
    duration = nDur;
}

void Event::setType(std::string nType){
    type = nType;
}

bool Event::operator>=(const Event& other) const{
    return time <= other.time;
}