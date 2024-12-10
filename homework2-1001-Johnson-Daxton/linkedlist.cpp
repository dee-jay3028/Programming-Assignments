template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const{
	// enforce precondition
	if((position >= 1) && (position <= itemCount)){
		// Count from the beginning of the chain
		Node<ItemType>* curPtr = headPtr;
		for (int skip = 1; skip < position; skip++){
			curPtr = curPtr->getNext();
		}
		return curPtr;
	}
	return nullptr;
}

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0){}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList){
	headPtr = nullptr;
    itemCount = aList.itemCount;
	if(itemCount == 0){
		return;
	}
	Node<ItemType>* temp;
	Node<ItemType>* curr = aList.headPtr;
	while(curr != nullptr){
		Node<ItemType>* newEntry = new Node<ItemType>(curr->getItem());
		if(headPtr == nullptr){
			headPtr = newEntry;
			temp = headPtr;
		} else {
			temp->setNext(newEntry);
			temp = newEntry;
		}
		curr = curr->getNext();
	}
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const{
	return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const{
	return itemCount;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry){ 
	//std::cout<<"ADDING ITEM"<<std::endl;
	bool validPos = (newPosition >= 1) && (newPosition <= itemCount+1);
	if(validPos){
		Node<ItemType>* newNode = new Node<ItemType>(newEntry);
		//std::cout<<"STORING IN NODE: "<<newEntry<<std::endl;
		//std::cout<<"STORED IN NODE: "<<newNode->getItem()<<std::endl;
		if(newPosition == 1){
			if(headPtr == nullptr){
				headPtr = newNode;
				itemCount++;
			} else {
				newNode->setNext(headPtr);
				headPtr = newNode;
				itemCount++;
			}
		} else if (newPosition == itemCount+1){
			getNodeAt(newPosition - 1)->setNext(newNode);
			itemCount++;
		} else {
			newNode->setNext(getNodeAt(newPosition));
			getNodeAt(newPosition - 1)->setNext(newNode);
			itemCount++;
		}
	}
    return validPos;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position){
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove){
		Node<ItemType>* ptrToDelete = nullptr;
		if (position == 1){
			// Remove the first node in the chain
			ptrToDelete = headPtr; // Save pointer to node 
			headPtr = headPtr->getNext();// save pointer to next node
		}
		else{
			// Find node that is before the one to remove
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			// Point to node to remove
			ptrToDelete = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the prior node with the one after
			prevPtr->setNext(ptrToDelete->getNext());
		}

		ptrToDelete->setNext(nullptr);
		delete ptrToDelete;
		ptrToDelete = nullptr;
		itemCount--; // Decrease count of entries
	}
	return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear(){
	Node<ItemType>* current = headPtr;
	while(current != nullptr){
		Node<ItemType>* temp = current;
		current = current->getNext();
		delete temp;
	}
	headPtr = nullptr;
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const {
    ItemType temp;
	bool validPos = (position >= 1) && (position <= itemCount);
	if(validPos){
		temp = getNodeAt(position)->getItem();
	}
    return temp;
} 

template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType& newEntry){
	// enforce precondition
	bool ableToReplace = (position >= 1) && (position <= itemCount);
	if (ableToReplace){
		Node<ItemType>* nodePtr = getNodeAt(position);
		ItemType oldEntry = nodePtr->getItem();
		nodePtr->setItem(newEntry);	
		return oldEntry;	
	} 
	throw "Item not found";
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList(){
	clear();
} 
