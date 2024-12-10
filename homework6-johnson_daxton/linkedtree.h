#ifndef LINKEDTREE_H
#define LINKEDTREE_H
#include <algorithm>
#include <iostream>
#include "linkedtreenode.h"
#include "tree.h"

/*
Linked implementation of a binary node tree ADT, using the 
LinkedTreeNode class as nodes. Includes and implements all 
functions listed in the "tree.h" templated interface, as well
as other useful functions.
*/

template<class T>
class LinkedTree: public TreeInterface<T>{
    LinkedTreeNode<T>* root;                                                                                                                                                                                                    
    public: 
        LinkedTree();
        bool isEmpty() const;
        int getHeight() const;
        int getNumberOfNodes() const; 
        T getRootData() const;
        void setRootData(const T& newData);
        bool add(const T& newEntry);
        bool remove(const T& anEntry);
        void clear(); 
        bool contains(const T& anEntry) const;
        ~LinkedTree();
        void preorderTraversal(std::ostream& out);
        void inorderTraversal(std::ostream& out);
        void postorderTraversal(std::ostream& out);
    protected: 
        int getHeightHelper(LinkedTreeNode<T>* subTreePtr) const;
        int getNumNodesHelper(LinkedTreeNode<T>* subTreePtr) const;
        LinkedTreeNode<T>* balancedAdd(LinkedTreeNode<T>* subTreePtr, LinkedTreeNode<T>* newNodePtr);
        LinkedTreeNode<T>* removeValue(LinkedTreeNode<T>* subTreePtr, const T target, bool& success);
        LinkedTreeNode<T>* moveUpValues(LinkedTreeNode<T>* subTreePtr);
        LinkedTreeNode<T>* findNode(LinkedTreeNode<T>* subTreePtr, const T& target, bool& success) const;
        void destroyTree(LinkedTreeNode<T>* subTreePtr);
        void preorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr);
        void inorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr);
        void postorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr);
};

#include "linkedtree.cpp"

#endif