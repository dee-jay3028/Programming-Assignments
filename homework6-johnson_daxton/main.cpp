#include "linkedtree.h"
#include "bst.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <fstream>

/*
Daxton Johnson- CS302 HW6
Driver creates 100 unique randomly generated values in the range 0 to 200, and inserts
all unique values into a binary search tree object to be manipulated and output via 3 
different types of traversal. Tree height and traversal outputs are stored in "SearchTreeData.txt"
*/

int main(){
    BinarySearchTree<int> numbersTree;
    LinkedTree<int> testTree;
    std::ofstream fileOut;
    fileOut.open("SearchTreeData.txt");
    int numbers[100];
    srand((unsigned) time(0));
    for(int i = 0; i < 100; i++){
        bool unique = true;
        int newNum = (rand() % 200);
        for(int j = 0; j <= i; j++){
            if(numbers[j] == newNum){
                unique = false;
            }
        }
        if(unique){
            numbers[i] = newNum;
        } else {
            i--;
        }
    }
    //std::cout<<"NUMBERS: "<<std::endl;
    for(int i = 0; i < 100; i++){   
        //std::cout<<numbers[i]<<std::endl;
        numbersTree.add(numbers[i]);
        testTree.add(numbers[i]);
    }
    fileOut<<"TREE HEIGHT: "<<numbersTree.getHeight()<<std::endl;
    fileOut<<"PREORDER OUTPUT: "<<std::endl;
    numbersTree.preorderTraversal(fileOut);
    fileOut<<std::endl<<"INORDER OUTPUT: "<<std::endl;
    numbersTree.inorderTraversal(fileOut);
    fileOut<<std::endl<<"POSTORDER OUTPUT: "<<std::endl;
    numbersTree.postorderTraversal(fileOut); 
}