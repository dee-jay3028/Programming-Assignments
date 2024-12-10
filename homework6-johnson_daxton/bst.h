#ifndef BST_H
#define BST_H
#include "linkedtreenode.h"
#include "linkedtree.h"

/*
Binary search tree class, extending the binary node tree class
located in linkedtree.h/.cpp. Uses same base node class, but with ordered insertions
to maintain search tree structure.
*/

template <class T>
class BinarySearchTree: public LinkedTree<T>{
    LinkedTreeNode<T>* root;
    public:
        BinarySearchTree();
        bool isEmpty() const;
        int getHeight() const;
        int getNumberOfNodes() const; 
        T getRootData() const;
        bool add(const T& newEntry);
        bool remove(const T& anEntry);
        bool contains(const T& anEntry) const;
        ~BinarySearchTree();
        void preorderTraversal(std::ostream& out);
        void inorderTraversal(std::ostream& out);
        void postorderTraversal(std::ostream& out);
    protected:
        int getNumNodesHelper(LinkedTreeNode<T>* subTreePtr) const;
        int getHeightHelper(LinkedTreeNode<T>* subTreePtr) const;
        LinkedTreeNode<T>* findParent(LinkedTreeNode<T>* subTreePtr, LinkedTreeNode<T>* targetPtr);
        LinkedTreeNode<T>* placeNode(LinkedTreeNode<T>* subTreePtr, LinkedTreeNode<T>* newNodePtr);
        LinkedTreeNode<T>* removeNode(LinkedTreeNode<T>* nodePtr);
        LinkedTreeNode<T>* removeLeftmostNode(LinkedTreeNode<T>* nodePtr, T& inorderSuccessor);
        LinkedTreeNode<T>* removeValue(LinkedTreeNode<T>* subTreePtr, const T target, bool& success);
        LinkedTreeNode<T>* findNode(LinkedTreeNode<T>* subTreePtr, const T& target) const;
        void preorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr);
        void inorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr);
        void postorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr);

};

#include "bst.cpp"

#endif