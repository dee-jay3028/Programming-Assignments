#ifndef MYGRAPH_H
#define MYGRAPH_H
#include "graph.h"
#include "arrayQueue.h"
#include "arrayStack.h"
#include "stdlib.h"
#include <iostream>

//Graph interface implementation using an adjacency matrix to represent a complete, weighted, undirected collection of vertices.

template <class T>
class Graph: public GraphInterface<T> {
    int numVertices;
    T* vertices;
    int** adjacency;
    public:
        Graph();
        Graph(int numVertices, T* vertices);
        int getNumVertices() const;
        int getNumEdges() const;
        bool add(T start, T end, int edgeWeight);
        bool remove(T start, T end);
        int getEdgeWeight(T start, T end) const;
        void depthFirstTraversal(T start);
        void breadthFirstTraversal(T start);
        void displayMatrix();
        ~Graph();
};


#include "myGraph.cpp"
#endif