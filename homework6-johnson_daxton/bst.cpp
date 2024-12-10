#include "bst.h"

template <typename T>
BinarySearchTree<T>::BinarySearchTree(){
    root = nullptr;
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() const{
    return root == nullptr;
}

template <typename T>
int BinarySearchTree<T>::getNumberOfNodes() const{
    return getNumNodesHelper(root);
}

template <typename T>
T BinarySearchTree<T>::getRootData() const{
    return root->getItem();
}

template <typename T>
bool BinarySearchTree<T>::add(const T& newEntry){
    LinkedTreeNode<T>* newNodePtr = new LinkedTreeNode<T>(newEntry);
    //std::cout<<"NEW ENTRY: "<<newNodePtr->getItem()<<std::endl;
    root = placeNode(root, newNodePtr);
    //std::cout<<"NEW ROOT: "<<root->getItem()<<std::endl;
    return true;
}

template <typename T>
int BinarySearchTree<T>::getNumNodesHelper(LinkedTreeNode<T>* subTreePtr) const{
    if(subTreePtr != nullptr){
        return 1 + getNumNodesHelper(subTreePtr->getLeftChildPtr()) + getNumNodesHelper(subTreePtr->getRightChildPtr());
    } else {
        return 0;
    }
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& newEntry){
    if(contains(newEntry)){ 
        LinkedTreeNode<T>* targetPtr = findNode(root, newEntry);
        removeNode(targetPtr);
    } else {
        return false;
    }
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& anEntry) const{
    LinkedTreeNode<T>* found = findNode(root, anEntry);
    if(found != nullptr){
        return true;
    } else {
        return false;
    }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    this->destroyTree(root);
}

template <typename T>
LinkedTreeNode<T>* BinarySearchTree<T>::findParent(LinkedTreeNode<T>* subTreePtr, LinkedTreeNode<T>* targetPtr){
    if(subTreePtr != nullptr){
        if(subTreePtr->getLeftChildPtr() == targetPtr || subTreePtr->getRightChildPtr() == targetPtr){
            return subTreePtr;
        } else if (subTreePtr->getItem() > targetPtr->getItem()){
            return findParent(subTreePtr->getLeftChildPtr(), targetPtr);
        } else {
            return findParent(subTreePtr->getRightChildPtr(), targetPtr);
        }
    }
    return subTreePtr;
}

template <typename T>
LinkedTreeNode<T>* BinarySearchTree<T>::placeNode(LinkedTreeNode<T>* subTreePtr, LinkedTreeNode<T>* newNodePtr){
    if(subTreePtr == nullptr){
        return newNodePtr;
    } else if (subTreePtr->getItem() > newNodePtr->getItem()){
        LinkedTreeNode<T>* leftPtr = subTreePtr->getLeftChildPtr();
        //std::cout<<"ITEM BEING EVALUATED: "<<subTreePtr->getItem()<<std::endl;
        leftPtr = placeNode(leftPtr, newNodePtr);
        subTreePtr->setLeftChildPtr(leftPtr);
        return subTreePtr;
    } else {
        LinkedTreeNode<T>* rightPtr = subTreePtr->getRightChildPtr();
        //std::cout<<"ITEMS BEING EVALUATED: "<<subTreePtr->getItem()<<", "<<newNodePtr->getItem()<<std::endl;
        rightPtr = placeNode(rightPtr, newNodePtr);
        subTreePtr->setRightChildPtr(rightPtr);
        return subTreePtr;
    }
}

template <typename T>
LinkedTreeNode<T>* BinarySearchTree<T>::removeNode(LinkedTreeNode<T>* nodePtr){
    if(nodePtr->isLeaf()){
        LinkedTreeNode<T>* parent = findParent(root, nodePtr);
        if(parent->getLeftChildPtr() == nodePtr){
            parent->setLeftChildPtr(nullptr);
        } else {
            parent->setRightChildPtr(nullptr);
        }
        delete nodePtr;
    } else if (nodePtr->getRightChildPtr() == nullptr){
        LinkedTreeNode<T>* parent = findParent(root, nodePtr);
        if(parent->getLeftChildPtr() == nodePtr){
            parent->setLeftChildPtr(nodePtr->getLeftChildPtr());
        } else {
            parent->setRightChildPtr(nodePtr->getLeftChildPtr());
        }
        delete nodePtr;
    } else if (nodePtr->getLeftChildPtr() == nullptr){
        LinkedTreeNode<T>* parent = findParent(root, nodePtr);
        if(parent->getLeftChildPtr() == nodePtr){
            parent->setLeftChildPtr(nodePtr->getRightChildPtr());
        } else {
            parent->setRightChildPtr(nodePtr->getRightChildPtr());
        }
        delete nodePtr;
    } else {
        T newValue;
        LinkedTreeNode<T>* temp;
        temp = removeLeftmostNode(nodePtr->getRightChildPtr(), newValue);
        nodePtr->setRightChildPtr(temp);
        nodePtr->setItem(newValue);
        return nodePtr;
    }
}

template <typename T>
int BinarySearchTree<T>::getHeight() const{
    return getHeightHelper(root);
}

template <typename T>
int BinarySearchTree<T>::getHeightHelper(LinkedTreeNode<T>* subTreePtr) const{
    if(subTreePtr == nullptr){
        return 0;
    }
    else{
        return 1+std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
    }
}

template <typename T>
LinkedTreeNode<T>* BinarySearchTree<T>::removeLeftmostNode(LinkedTreeNode<T>* nodePtr, T& inorderSuccessor){
    if(nodePtr != nullptr){
        if(nodePtr->getLeftChildPtr() == nullptr){
            inorderSuccessor = nodePtr->getItem();
            return removeNode(nodePtr);
        } else {
            LinkedTreeNode<T>* temp = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
            nodePtr->setLeftChildPtr(temp);
            return nodePtr;
        }
    }
}

template <typename T>
LinkedTreeNode<T>* BinarySearchTree<T>::removeValue(LinkedTreeNode<T>* subTreePtr, const T target, bool& success){
    if(subTreePtr != nullptr){
        if(contains(target)){
            LinkedTreeNode<T>* targetPtr = findNode(root, target);
            success=true;
            return removeNode(targetPtr);
        } else {
            success = false;
            return subTreePtr;
        }
    } else {
        success = false;
        return subTreePtr;
    }
}

template <typename T>
LinkedTreeNode<T>* BinarySearchTree<T>::findNode(LinkedTreeNode<T>* subTreePtr, const T& target) const{
    if(subTreePtr != nullptr){
        if(subTreePtr->getItem() == target){
            return subTreePtr;
        } else if (subTreePtr->getItem() > target){
            return findNode(subTreePtr->getLeftChildPtr(), target);
        } else {
            return findNode(subTreePtr->getRightChildPtr(), target);
        }
    }
    return subTreePtr;
}

template <typename T>
void BinarySearchTree<T>::preorderTraversal(std::ostream& out){
    preorder(out, root);
}

template <typename T>
void BinarySearchTree<T>::inorderTraversal(std::ostream& out){
    inorder(out, root);
}

template <typename T>
void BinarySearchTree<T>::postorderTraversal(std::ostream& out){
    postorder(out, root);
}

template <typename T>
void BinarySearchTree<T>::preorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        out<<subTreePtr->getItem()<<", ";
        preorder(out, subTreePtr->getLeftChildPtr());
        preorder(out, subTreePtr->getRightChildPtr());
    }
}

template <typename T>
void BinarySearchTree<T>::inorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        inorder(out, subTreePtr->getLeftChildPtr());
        out<<subTreePtr->getItem()<<", ";
        inorder(out, subTreePtr->getRightChildPtr());
    }
}

template <typename T>
void BinarySearchTree<T>::postorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        postorder(out, subTreePtr->getLeftChildPtr());
        postorder(out, subTreePtr->getRightChildPtr());
        out<<subTreePtr->getItem()<<", ";
    }
}