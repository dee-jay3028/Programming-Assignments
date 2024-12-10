#include "priorityQueue.h"

template <typename T>
PriorityQueue<T>::PriorityQueue(){
    this->front = this->rear = -1;
}

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry){
    if(this->rear + 1 == this->front || (this->front == 0 && this->rear == this->DEFAULT_SIZE)){
        throw "array full!";
    }
    int index = 0;
    this->rear++;
    if(this->front == -1){
        this->front = 0;
    }
    for(int i = this->front; i != this->rear; i++){
        if(i == this->DEFAULT_SIZE){
            i = 0;
        }
        if(newEntry >= this->items[i]){
            index = i;
            for(int j = this->rear; j != i; j--){
                if(j == -1){
                    j = this->DEFAULT_SIZE;
                }
                this->items[j] = this->items[j-1];
            }
            break;
        }
        if(i+1 == this->rear){
            index = this->rear; 
            break;
        }
    }
    this->items[index] = newEntry;
    return true;
}