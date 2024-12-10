#include "myGraph.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <stdio.h>

void readFile(std::ifstream& input, int& numCities, std::string* cities);

void addEdges(std::ifstream& input, Graph<std::string>& citiesGraph);

void findShortestPath(Graph<std::string>& citiesGraph, std::string* cities);

int main(){
    std::ifstream input;
    int numCities = 5;
    std::string cities[5];
    input.open("distances.txt");
    readFile(input, numCities, cities);
    Graph<std::string> citiesGraph(numCities, cities);
    addEdges(input, citiesGraph);
    //citiesGraph.displayMatrix();
    findShortestPath(citiesGraph, cities);
    input.close();
}

void readFile(std::ifstream& input, int& numCities, std::string* cities){
    if(input.is_open()){
        std::string inputLine;
        std::getline(input, inputLine);
        for(int i = 0; i < 4; i++){
            cities[i] = inputLine.substr(0, inputLine.find_first_of(','));
            inputLine = inputLine.substr(inputLine.find_first_of(',')+1);
        }
        cities[4] = inputLine;
    } else {
        std::cout<<"File error!"<<std::endl;
    }
}

void addEdges(std::ifstream& input, Graph<std::string>& citiesGraph){
    if(input.is_open()){
        std::string inputLine;
        while(std::getline(input, inputLine)){
            std::string city1 = inputLine.substr(0, inputLine.find_first_of(','));
            inputLine = inputLine.substr(inputLine.find_first_of(',')+1);
            std::string city2 = inputLine.substr(0, inputLine.find_first_of(','));
            inputLine = inputLine.substr(inputLine.find_first_of(',')+1);
            int distance = std::stoi(inputLine);
            citiesGraph.add(city1, city2, distance);
        }
    } else {
        std::cout<<"File error!"<<std::endl;
    } 
}

void findShortestPath(Graph<std::string>& citiesGraph, std::string* cities){
    std::ofstream results;
    results.open("results.txt");
    srand((unsigned) time(0));
    int min = 999999;
    std::string travelCities[4];
    for(int i = 1; i < 5; i++){
        travelCities[i-1] = cities[i];
    }
    int permutations[24][4];
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 4; j++){
            bool unique = true;
            int nextDestination = (rand() % 4);
            for(int k = 0; k < j; k++){
                if(permutations[i][k] == nextDestination){
                    j--;
                    unique = false;
                }
            }
            if(unique){
                permutations[i][j] = nextDestination;
            }
        }
        bool unique = true;
        for(int j = 0; j < i; j++){
            bool uniqueColumn = false;
            for(int k = 0; k < 4; k++){
                if(permutations[j][k] != permutations[i][k]){
                    uniqueColumn = true;
                }
            }
            if(!uniqueColumn){
                unique = false;
                i--;
                break;
            }
        }
    }
    int solutionIndex = -1;
    for(int i = 0; i < 24; i++){
        int pathCost = 0;
        pathCost += citiesGraph.getEdgeWeight(cities[0], travelCities[permutations[i][0]]);
        for(int j = 0; j < 3; j++){
            pathCost += citiesGraph.getEdgeWeight(travelCities[permutations[i][j]], travelCities[permutations[i][j+1]]);
        }
        pathCost += citiesGraph.getEdgeWeight(travelCities[permutations[i][3]], cities[0]);
        if(pathCost < 999999 && pathCost > 0){
            if(pathCost < min){
                min = pathCost;
                solutionIndex = i;
            }
        }
        //std::cout<<pathCost<<" ";
    }
    //std::cout<<std::endl;
    results<<"POSSIBLE PERMUTATIONS: "<<std::endl;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 4; j++){
            results<<cities[permutations[i][j]]<<" ";
        }
        results<<std::endl;
    }
    results<<std::endl;
    results<<"The path with the minimum possible cost travels from "<<cities[0]<<" to ";
    for(int i = 0; i < 4; i++){
        results<<travelCities[permutations[solutionIndex][i]]<<" to ";
    }
    results<<cities[0]<<" again."<<std::endl;
    results<<"It covers "<<min<<" miles, and burns ~"<<min/40<<" gallons of gasoline at 40mpg."<<std::endl;
    results<<"(impossible routes are not included when choosing optimal path)"<<std::endl;
    results.close();
}