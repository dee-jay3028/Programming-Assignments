#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>

//Basic person class to fill bus with

class Person {
    int height;
    std::string name;
    public:
        Person();
        Person(int, std::string);
        Person(const Person&);
        int getHeight();
        std::string getName();
        void setHeight(int);
        void setName(std::string);
        bool operator>(const Person&);
        friend std::ostream& operator<<(std::ostream&, Person);
};

#endif