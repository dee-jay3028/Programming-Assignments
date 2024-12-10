#ifndef CARGO_H
#define CARGO_H
#include <string>

//Basic cargo class to fill train with

class Cargo {
    int weight;
    std::string type;
    public: 
        Cargo();
        Cargo(int, std::string);
        Cargo(const Cargo&);
        std::string getType();
        int getWeight();
        void setWeight(int);
        void setType(std::string);
        friend std::ostream& operator<<(std::ostream&, Cargo);
};

#endif