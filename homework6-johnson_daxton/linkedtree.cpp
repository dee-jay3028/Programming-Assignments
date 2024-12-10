#include "linkedtree.h"

template <typename T>
LinkedTree<T>::LinkedTree(){
    root = nullptr;
}

template <typename T>
bool LinkedTree<T>::isEmpty() const{
    return root == nullptr;
}

template <typename T>
int LinkedTree<T>::getHeight() const{
    return getHeightHelper(root);
}

template <typename T>
int LinkedTree<T>::getNumberOfNodes() const{
    return getNumNodesHelper(root);
}

template <typename T>
T LinkedTree<T>::getRootData() const{
    return root->getItem();
}

template <typename T>
bool LinkedTree<T>::add(const T& newEntry){
    LinkedTreeNode<T>* newNodePtr = new LinkedTreeNode<T>(newEntry);
    root = balancedAdd(root, newNodePtr);
    return true;
}

template <typename T>
bool LinkedTree<T>::remove(const T& anEntry){
    bool found;
    removeValue(root, anEntry, found);
    return found;
}

template <typename T>
void LinkedTree<T>::clear(){
    destroyTree(root);
}

template <typename T>
bool LinkedTree<T>::contains(const T& anEntry) const{
    bool success = false;
    findNode(root, anEntry, success);
    return success;
}

template <typename T>
LinkedTree<T>::~LinkedTree() {
    destroyTree(root);
}   

template <typename T>
void LinkedTree<T>::preorderTraversal(std::ostream& out){
    preorder(out, root);
}

template <typename T>
void LinkedTree<T>::inorderTraversal(std::ostream& out){
    inorder(out, root);
}

template <typename T>
void LinkedTree<T>::postorderTraversal(std::ostream& out){
    postorder(out, root);
}

template <typename T>
int LinkedTree<T>::getHeightHelper(LinkedTreeNode<T>* subTreePtr) const{
    if(subTreePtr == nullptr){
        return 0;
    }
    else{
        return 1+std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
    }
}

template <typename T>
int LinkedTree<T>::getNumNodesHelper(LinkedTreeNode<T>* subTreePtr) const{
    if(subTreePtr != nullptr){
        return 1 + getNumNodesHelper(subTreePtr->getLeftChildPtr()) + getNumNodesHelper(subTreePtr->getRightChildPtr());
    } else {
        return 0;
    }
}

template <typename T>
LinkedTreeNode<T>* LinkedTree<T>::balancedAdd(LinkedTreeNode<T>* subTreePtr, LinkedTreeNode<T>* newNodePtr){
    if(subTreePtr == nullptr){
        return newNodePtr;
    } else {
        LinkedTreeNode<T>* leftPtr = subTreePtr->getLeftChildPtr();
        LinkedTreeNode<T>* rightPtr = subTreePtr->getRightChildPtr();
        if(getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){
            rightPtr = balancedAdd(rightPtr, newNodePtr);
            subTreePtr->setRightChildPtr(rightPtr);
        } else {
            leftPtr = balancedAdd(leftPtr, newNodePtr);
            subTreePtr->setLeftChildPtr(leftPtr);
        }
        return subTreePtr;
    }
}

template <typename T>
LinkedTreeNode<T>* LinkedTree<T>::removeValue(LinkedTreeNode<T>* subTreePtr, const T target, bool& success){
    LinkedTreeNode<T>* remTarget = findNode(subTreePtr, target, success);
    if(subTreePtr != nullptr && remTarget != nullptr){
        if(remTarget->isLeaf()){
            delete remTarget;
        } else {

        }
    } else {
        return nullptr;
    }
}

template <typename T>
LinkedTreeNode<T>* LinkedTree<T>::moveUpValues(LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        if(!subTreePtr->isLeaf()){
            if(subTreePtr->getRightChildPtr()!=nullptr){
                return moveUpValues(subTreePtr->getRightChildPtr());
            } else {
                return moveUpValues(subTreePtr->getLeftChildPtr());
            }
        } else {
            return subTreePtr;
        }
    }
    return subTreePtr;
}

template <typename T>
LinkedTreeNode<T>* LinkedTree<T>::findNode(LinkedTreeNode<T>* subTreePtr, const T& target, bool& success) const{
    if(subTreePtr != nullptr){
        if(subTreePtr->getItem() == target){
            success = true;
            return subTreePtr;
        }
        LinkedTreeNode<T>* temp = findNode(subTreePtr->getLeftChildPtr(), target, success);
        if(temp != nullptr){
            return temp;
        } else {
            return findNode(subTreePtr->getRightChildPtr(), target, success);
        }   
    } else {
        return nullptr;
    }
}

template <typename T>
void LinkedTree<T>::destroyTree(LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

template <typename T>
void LinkedTree<T>::preorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        out<<subTreePtr->getItem()<<", ";
        preorder(out, subTreePtr->getLeftChildPtr());
        preorder(out, subTreePtr->getRightChildPtr());
    }
}

template <typename T>
void LinkedTree<T>::inorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        inorder(out, subTreePtr->getLeftChildPtr());
        out<<subTreePtr->getItem()<<", ";
        inorder(out, subTreePtr->getRightChildPtr());
    }
}

template <typename T>
void LinkedTree<T>::postorder(std::ostream& out, LinkedTreeNode<T>* subTreePtr){
    if(subTreePtr != nullptr){
        postorder(out, subTreePtr->getLeftChildPtr());
        postorder(out, subTreePtr->getRightChildPtr());
        out<<subTreePtr->getItem()<<", ";
    }
}