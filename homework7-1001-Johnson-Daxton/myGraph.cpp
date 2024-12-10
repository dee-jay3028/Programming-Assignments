#include "myGraph.h"

template <typename T>
Graph<T>::Graph(){
    numVertices = 0;
}

template <typename T>
Graph<T>::Graph(int numCities, T* cities){
    numVertices = numCities;
    //std::cout<<"NUM VERTICES: "<<numVertices<<std::endl;
    vertices = cities;
    adjacency = (int**)malloc(sizeof(int*)*numVertices);
    for(int i = 0; i < numVertices; i++){
        adjacency[i] = (int*)malloc(sizeof(int)*numVertices);
    }
    for(int i = 0; i < numVertices; i++){
        //std::cout<<"starting "<<i<<"th iteration"<<std::endl;
        for(int j = 0; j < numVertices; j++){
            //std::cout<<"starting "<<j<<"th subiteration"<<std::endl;
            adjacency[i][j] = 999999;
        }
    }
    //std::cout<<"done making graph"<<std::endl;
}

template <typename T>
int Graph<T>::getNumVertices() const {
    return numVertices;
}

template <typename T>
int Graph<T>::getNumEdges() const {
    int total = 0;
    for(int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            if(adjacency[i][j] != -1){
                total++;
            }
        }
    }
    return total;
}

template <typename T>
bool Graph<T>::add(T start, T end, int edgeWeight){
    int startIndex, endIndex = -1;
    bool startExists = false;
    bool endExists = false;
    for(int i = 0; i < numVertices; i++){
        if(start == vertices[i]){
            startExists = true;
            startIndex = i;
        }
        if(end == vertices[i]){
            endExists = true;
            endIndex = i;
        }
    }
    if(startExists && endExists){
        adjacency[startIndex][endIndex] = edgeWeight;
        adjacency[endIndex][startIndex] = edgeWeight;
    } else if ((!endExists && startExists) || (!startExists && endExists)){
        vertices = (T*)realloc(vertices, sizeof(T)*numVertices+1);
        adjacency = (int**)realloc(adjacency, sizeof(int*)*numVertices+1);
        for(int i = 0; i < numVertices+1; i++){
            adjacency[i] = (int*)realloc(adjacency[i], sizeof(int)*numVertices+1);
        }
        if(startExists){
            vertices[numVertices] = end;
            adjacency[startIndex][numVertices] = edgeWeight;
            adjacency[numVertices][startIndex] = edgeWeight;
        } else {
            vertices[numVertices] = start;
            adjacency[endIndex][numVertices] = edgeWeight;
            adjacency[numVertices][endIndex] = edgeWeight;
        }
        numVertices++;
    } else if (!endExists && !startExists){
        vertices = (T*)realloc(vertices, numVertices+2);
        adjacency = (int**)realloc(adjacency, numVertices+2);
        for(int i = 0; i < numVertices+2; i++){
            adjacency[i] = (int*)realloc(adjacency[i], numVertices+2);
        }
        vertices[numVertices] = start;
        vertices[numVertices+1] = end;
        adjacency[numVertices][numVertices+1] = edgeWeight;
        adjacency[numVertices+1][numVertices] = edgeWeight;
        numVertices += 2;
    }
    return true;
}

template <typename T>
bool Graph<T>::remove(T start, T end){
    int startIndex;
    int endIndex;
    for(int i = 0; i < numVertices; i++){
        if(vertices[i] == start){
            startIndex = i;
        } 
        if(vertices[i] == end){
            endIndex = i;
        }
    }
    
    adjacency[startIndex][endIndex] = 999999;
    return true;
}

template <typename T>
int Graph<T>::getEdgeWeight(T start, T end) const {
    int startIndex;
    int endIndex;
    for(int i = 0; i < numVertices; i++){
        if(vertices[i] == start){
            startIndex = i;
        } 
        if(vertices[i] == end){
            endIndex = i;
        }
    }
    return adjacency[startIndex][endIndex];
}

template <typename T>
void Graph<T>::depthFirstTraversal(T start){
    int startIndex;
    bool visited[5];
    int visitedOrder[5];
    int visitedIndex = 1;
    for(int i = 0; i < numVertices; i++){
        if(vertices[i] == start){
            startIndex = i;
        } 
    }
    ArrayStack<int> traverseStack;
    traverseStack.push(startIndex);
    visited[startIndex] = true;
    visitedOrder[0] = startIndex;
    while(!traverseStack.isEmpty()){
        bool cont = false;
        int nextIndex = 0;
        for(int i = 0; i < numVertices; i++){
            if(adjacency[startIndex][i] != 999999){
                if(!visited[i]){
                    cont = true;
                    nextIndex = i;
                    break;
                }
            }
        }
        if(!cont){
            traverseStack.pop();
        } else {
            traverseStack.push(nextIndex);
            visited[nextIndex = true];
            visitedOrder[visitedIndex] = nextIndex;
            visitedIndex++;
        }
    }
}

template <typename T>
void Graph<T>::breadthFirstTraversal(T start){
    int startIndex;
    bool visited[5];
    int visitedOrder[5];
    int visitedIndex = 1;
    for(int i = 0; i < numVertices; i++){
        if(vertices[i] == start){
            startIndex = i;
        } 
    }
    ArrayQueue<int> traverseQueue;
    traverseQueue.enqueue(startIndex);
    visited[startIndex] = true;
    visitedOrder[0] = startIndex;
    while(!traverseQueue.isEmpty()){
        int currentIndex = traverseQueue.peekFront();
        traverseQueue.dequeue();
        int adjacentNodes[numVertices-1];
        int numAdjacent = 0;
        for(int i = 0; i < numVertices; i++){
            if(adjacency[currentIndex][i] != 999999 && !visited[i]){
                adjacentNodes[numAdjacent] = i;
                numAdjacent++;
                visited[i] = true;
                visitedOrder[visitedIndex] = i;
            }
        }
        for(int i = 0; i < numAdjacent; i++){
            traverseQueue.enqueue(adjacentNodes[i]);
        }
    }
}

template <typename T>
void Graph<T>::displayMatrix(){
    std::cout<<"Vertices: ";
    for(int i = 0; i < numVertices-1; i++){
        std::cout<<vertices[i]<<", ";
    }
    std::cout<<vertices[numVertices-1]<<std::endl;
    std::cout<<std::endl;
    for(int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            std::cout<<adjacency[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }
}

template <typename T>
Graph<T>::~Graph(){
    for(int i = 0; i < numVertices; i++){
        delete[] adjacency[i];
    }
    delete[] adjacency;
}