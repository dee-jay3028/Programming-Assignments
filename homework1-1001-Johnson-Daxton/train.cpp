template <typename T>
Train<T>::Train(){
    numItems = 0;
}

template <typename T>
Train<T>::Train(T* nItems, int nNumItems){
    numItems = nNumItems;
    for(int i = 0; i < numItems; i++){
        Items[i] = nItems[i];
    }
}

template <typename T>
Train<T>::Train(const Train& rhs){
    numItems = rhs.numItems;
    for(int i = 0; i < numItems; i++){
        Items[i] = rhs.Items[i];
    }
}

template <typename T>
void Train<T>::loadItem(T nItem){
    Items[numItems] = nItem;
    numItems++;
}

template <typename T>
void Train<T>::unloadItem(){
    numItems--;
}

template <typename T>
void Train<T>::empty(){
    numItems = 0;
}

template <typename T>
void Train<T>::move(){
    std::cout<<"Train has reached the next station!"<<std::endl;
}

template <typename T>
bool Train<T>::isEmpty(){
    if(numItems == 0){
        return true;
    } else {
        return false;
    }
}

template <typename T>
int Train<T>::getNumItems(){
    return numItems;
}

template <typename T>
T Train<T>::getItemAtIndex(int index){
    if(index >= 0 && index < numItems){
        return Items[index];
    }
    return T();
}

template <typename T>
int Train<T>::getTotalWeight(){
    int total = 0;
    for(int i = 0; i < numItems; i++){
        total = total + Items[i].getWeight();
    }
    return total;
}