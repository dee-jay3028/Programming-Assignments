#include "person.h"

Person::Person(){
    name = "";
    height = 0;
}

Person::Person(int nHeight, std::string nName){
    name = nName;
    height = nHeight;
}

Person::Person(const Person& rhs){
    name = rhs.name;
    height = rhs.height;
}

int Person::getHeight(){
    return height;
}

std::string Person::getName(){
    return name;
}

void Person::setHeight(int nHeight){
    height = nHeight;
}

void Person::setName(std::string nName){
    name = nName;
}

bool Person::operator>(const Person& rhs){
    return height > rhs.height;
}