template <typename T>
Bus<T>::Bus(){
    numItems = 0;
    fare = 2.0;
}

template <typename T>
Bus<T>::Bus(T* nItems, int nNumItems, float nFare){
    numItems = nNumItems;
    fare = nFare;
    for(int i = 0; i < numItems; i++){
        Items[i] = nItems[i];
    }
}

template <typename T>
Bus<T>::Bus(const Bus& rhs){
    numItems = rhs.numItems;
    fare = rhs.fare;
    for(int i = 0; i < numItems; i++){
        Items[i] = rhs.Items[i];
    }
}

template <typename T>
void Bus<T>::loadItem(T nItem){
    int i = numItems - 1;
    while(i >=0 && Items[i] > nItem){
        Items[i + 1] = Items[i];
        i--;
    } 
    Items[i + 1] = nItem;
    numItems++;
}

template <typename T>
void Bus<T>::unloadItem(){
    numItems--;
}

template <typename T>
void Bus<T>::empty(){
    numItems = 0;
}

template <typename T>
void Bus<T>::move(){
    std::cout<<"Bus has reached the next stop!"<<std::endl;
}

template <typename T>
bool Bus<T>::isEmpty(){
    if(numItems == 0){
        return true;
    } else {
        return false;
    }
}

template <typename T>
int Bus<T>::getNumItems(){
    return numItems;
}

template <typename T>
T Bus<T>::getItemAtIndex(int index){
    if(index >= 0 && index < numItems){
        return Items[index];
    }
    return T();
}

template <typename T>
float Bus<T>::getTotalFare(){
    return fare*numItems;
}

template <typename T>
float Bus<T>::getFare(){
    return fare;
}

template <typename T>
void Bus<T>::setFare(float nFare){
    fare = nFare;
}