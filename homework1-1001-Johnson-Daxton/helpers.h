#ifndef HELPERS_H
#define HELPERS_H
#include "person.h"
#include "cargo.h"
#include "train.h"
#include "bus.h"
#include <iostream>

//Helper functions to make main driver less cluttered/set up program

void createItems(Person*, Cargo*);

void fillBus(Bus<Person>&, Person*);

void fillTrain(Train<Cargo>&, Cargo*);

#endif