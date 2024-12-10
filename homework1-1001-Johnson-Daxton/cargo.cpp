#include "cargo.h"

Cargo::Cargo(){
    type = "";
    weight = 0;
}

Cargo::Cargo(int nWeight, std::string nType){
    weight = nWeight;
    type = nType;
}

Cargo::Cargo(const Cargo& rhs){
    weight = rhs.weight;
    type = rhs.type;
}

std::string Cargo::getType(){
    return type;
}

int Cargo::getWeight(){
    return weight;
}

void Cargo::setType(std::string nType){
    type = nType;
}

void Cargo::setWeight(int nWeight){
    weight = nWeight;
}

int operator+(int num, Cargo& rhs){
    return num + rhs.getWeight();
}