//CS 302 Homework 1- Daxton Johnson
#include "helpers.h"

int main(){
    Bus myBus = Bus<Person>();
    Train myTrain = Train<Cargo>();
    Person People[3];
    Cargo Freight[3];
    createItems(People, Freight);
    fillBus(myBus, People);
    std::cout<<"Bus filled! "<<myBus.getNumItems()<<" Passengers (shortest to tallest): "<<std::endl;
    for(int i = 0; i < 3; i++){
        std::cout<<myBus.getItemAtIndex(i);
    }
    std::cout<<"Bus fare: "<<myBus.getFare()<<".00"<<std::endl;
    std::cout<<"Total collected: "<<myBus.getTotalFare()<<".00"<<std::endl;
    fillTrain(myTrain, Freight);
    std::cout<<std::endl;
    std::cout<<"Train filled! "<<myTrain.getNumItems()<<" Pieces of cargo: "<<std::endl;
    for(int i = 0; i < 3; i++){
        std::cout<<myTrain.getItemAtIndex(i);
    }
    std::cout<<"Total weight: "<<myTrain.getTotalWeight()<<"kg"<<std::endl;
    std::cout<<std::endl;
    myBus.move();
    myBus.unloadItem();
    std::cout<<"A passenger got off! "<<myBus.getNumItems()<<" Passengers left: "<<std::endl;
    for(int i = 0; i < 2; i++){
        std::cout<<myBus.getItemAtIndex(i);
    }
    myBus.setFare(4);
    std::cout<<"New fare: "<<myBus.getFare()<<".00"<<std::endl;
    std::cout<<"New total collected: "<<myBus.getTotalFare()<<".00"<<std::endl;
    std::cout<<std::endl;
    myTrain.move();
    myTrain.unloadItem();
    std::cout<<"Cargo unloaded! "<<myTrain.getNumItems()<<" Pieces of cargo left: "<<std::endl;
    for(int i = 0; i < 2; i++){
        std::cout<<myTrain.getItemAtIndex(i);
    }
    std::cout<<"Total weight: "<<myTrain.getTotalWeight()<<"kg"<<std::endl;
    std::cout<<std::endl;
    if(!myBus.isEmpty()){
        std::cout<<"The bus is not empty! Emptying..."<<std::endl;
    }
    myBus.empty();
    if(myBus.isEmpty()){
        std::cout<<"Bus empty!"<<std::endl;
    }
     if(!myTrain.isEmpty()){
        std::cout<<"The train is not empty! Emptying..."<<std::endl;
    }
    myTrain.empty();
    if(myTrain.isEmpty()){
        std::cout<<"Train empty!"<<std::endl;
    }
    return 0;
}