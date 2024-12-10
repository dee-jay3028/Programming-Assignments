#include "helpers.h"

void createItems(Person* nPeople, Cargo* nFreight){
    Cargo hay = Cargo(10, "Hay");
    Cargo coal = Cargo(50, "Coal");
    Cargo cows = Cargo(100, "Cows");
    nFreight[0] = hay;
    nFreight[1] = coal;
    nFreight[2] = cows;
    Person javier = Person(130, "Javier");
    Person arthur = Person(150, "Arthur");
    Person lenny = Person(140, "Lenny");
    nPeople[0] = javier;
    nPeople[1] = arthur;
    nPeople[2] = lenny;
}

void fillBus(Bus<Person>& nBus, Person* nPeople){
    for(int i = 0; i < 3; i++){
        nBus.loadItem(nPeople[i]);
    }
}

void fillTrain(Train<Cargo>& nTrain, Cargo* nCargo){
    for(int i = 0; i < 3; i++){
        nTrain.loadItem(nCargo[i]);
    }
}

std::ostream& operator<<(std::ostream& out, Person outPerson){
    out<<outPerson.name<<"- Height: "<<outPerson.height<<"cm"<<std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, Cargo outCargo){
    out<<outCargo.type<<"- Weight: "<<outCargo.weight<<"kg"<<std::endl;
    return out;
}