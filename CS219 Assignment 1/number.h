#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>

//One easy object to store a hex value passed in at construction, and automatically convert it to both 32 bit unsigned decimal and binary

class Number {
    std::string hexNum;
    uint32_t decNum;
    std::string binNum;
    public:
        Number();
        Number(std::string);
        Number(uint32_t);
        Number(const Number& rhs);
        std::string getHexNum();
        uint32_t getDecNum();
        std::string getBinNum();
        void setNewHex(std::string);
};

#endif