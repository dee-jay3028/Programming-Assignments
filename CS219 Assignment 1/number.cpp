#include "number.h"

Number::Number(){
    hexNum = "0";
    binNum = "0";
    decNum = 0;
}

Number::Number(std::string newHex){
    hexNum = newHex;
    std::stringstream conv;
    conv << std::hex << hexNum;
    conv >> decNum;
    std::bitset<32> binary(decNum);
    binNum = binary.to_string();
}

Number::Number(uint32_t newInt){
    //constructor overload for an integer parameter at construction? Implement later
}

Number::Number(const Number& rhs){
    hexNum = rhs.hexNum;
    std::stringstream conv;
    conv << std::hex << hexNum;
    conv >> decNum;
    std::bitset<32> binary(decNum);
    binNum = binary.to_string();
}

std::string Number::getHexNum(){
    return hexNum;
}

uint32_t  Number::getDecNum(){
    return decNum;
}

std::string Number::getBinNum(){
    return binNum;
}

void Number::setNewHex(std::string newHex){
    hexNum = newHex;
    std::stringstream conv;
    conv << std::hex << hexNum;
    conv >> decNum;
    std::bitset<32> binary(decNum);
    binNum = binary.to_string();
}