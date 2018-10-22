#include <string>
#include <iostream>

class LinkedList{
	struct Node{
		private:
			std::string text;
			Node* next = NULL;
		public:
			Node(std::string text);
			void setText(std::string text);
			void setNext(Node* next);
			std::string getText();
			LinkedList::Node* getNext();
	};
	private:
		LinkedList::Node* head = NULL;
		LinkedList::Node* tail = NULL;
	public:
		void setHead(LinkedList::Node* head);
		void setTail(LinkedList::Node* tail);
		LinkedList::Node* getHead();
		LinkedList::Node* getTail();
		void insertEnd(std::string text); //inserts after tail
		void insert(std::string text, int index); //insert at index (indexing starts at 1)
		void deleteLine(int index); //deletes at index (indexing starts at 1)
		void edit(std::string text, int index); //edits text at index (indexing starts at 1)
		void print(); //prints all lines
		void search(std::string text); //searches text for substring
};

LinkedList::Node::Node(std::string text){
	this->text = text;
}

void LinkedList::Node::setText(std::string text){
	this->text = text;
}

void LinkedList::Node::setNext(Node* next){
	this->next = next;
}

std::string LinkedList::Node::getText(){
	return text;
}

LinkedList::Node* LinkedList::Node::getNext(){
	return next;
}

void LinkedList::setHead(LinkedList::Node* head){
	this->head = head;
}

void LinkedList::setTail(LinkedList::Node* tail){
	this->tail = tail;
}

LinkedList::Node* LinkedList::getHead(){
	return head;
}

LinkedList::Node* LinkedList::getTail(){
	return tail;
}

void LinkedList::insertEnd(std::string text){
	Node* addNode = new Node(text);
	if(!getTail()){ //if no nodes exist, will set new node as both head and tail since length of LinkedList is 1
		setHead(addNode);
		setTail(addNode);
	}
	else{ 
		getTail()->setNext(addNode);
		setTail(addNode);
	}
}

void LinkedList::insert(std::string text, int index){
	Node* currentNode = getHead(); //currentNode will iterate to the Node before the point of insertion
	if(index <= 0){
		return;
	}
	else if(!getHead() && index == 1){ //if no nodes exist and index is 1, will set head and tail to added node
		Node* addNode = new Node(text);
		setHead(addNode);
		setTail(addNode);
	}
	else if(index == 1){ //if head node exists and index is 1, will reassign head
		Node* addNode = new Node(text);
		addNode->setNext(getHead());
		setHead(addNode);
	}
	else if(!getHead()){ //if no nodes exist and index != 1, LinkedList will not change
		return;
	}
	else{
		for(int i = 0; i < index - 2; i++){ //iterates to Node before point of insertion, will be skipped if index == 2 
			currentNode = currentNode->getNext();
			if(!currentNode){ //previous Node must exist
				return;
			}
		}
		Node* addNode = new Node(text);
		addNode->setNext(currentNode->getNext());
		currentNode->setNext(addNode);
	}
}

void LinkedList::deleteLine(int index){
	Node* currentNode = getHead();
	if(index <= 0){
		return;
	}
	else if(index == 1 && getHead()){ //if head exists and is deleted, reassigns head (works if head->next is null)
		setHead(getHead()->getNext());
		delete currentNode;
	}
	else if(getHead() && getHead()->getNext()){ //for all lines other than head, if no other lines exist block skipped
		currentNode = getHead()->getNext();
		Node* previousNode = getHead();
		for(int i = 0; i < index - 2; i++){ //iterates to node to be deleted, block skipped if index == 2 
			previousNode = currentNode;
			currentNode = currentNode->getNext();
			if(!currentNode){
				return;
			}
		}
		if(!currentNode->getNext()){ //if tail to be deleted, reassigns tail and does not assign the new tail's next ptr
			previousNode->setNext(NULL); //removes link to old tail (will be deleted)
			setTail(previousNode);
			delete(currentNode);
			return;
		}
		previousNode->setNext(currentNode->getNext()); //reassigns previousNode's next to skip deleted node
		delete(currentNode);
	}
}

void LinkedList::edit(std::string text, int index){
	Node* currentNode = getHead();
	if(index <= 0 || !currentNode){//invalid index or if no nodes exist
		return;
	}
	for(int i = 0; i < index - 1; i++){
		currentNode = currentNode->getNext();
		if(!currentNode){
			return;
		}
	}
	currentNode->setText(text);
}

void LinkedList::print(){
	Node* currentNode = getHead();
	int index = 1;
	while(currentNode){
		std::cout << index << " " << currentNode->getText() << std::endl;
		++index;
		currentNode = currentNode->getNext();
	}
}

void LinkedList::search(std::string text){
	Node* currentNode = getHead();
	bool isTextFound = false;
	int index = 1;
	while(currentNode){
		if(currentNode->getText().find(text) != std::string::npos){
			std::cout << index << " " << currentNode->getText() << std::endl;
			isTextFound = true;
		}
		++index;
		currentNode = currentNode->getNext();
	}
	if(!isTextFound){
		std::cout << "not found" << std::endl;
	}
}

int main(){
	LinkedList textList;
	std::string userCommand;
	int lineNumber;
	std::string text;
	while(true){
		std::cin >> userCommand;
		if(userCommand == "insertEnd"){
			std::getline(std::cin, text);
			text = text.substr(2, text.length() - 3); //starts after leading space and quote, ends at end of string (before end quote)
			textList.insertEnd(text);
		}
		else if(userCommand == "insert"){
			std::cin >> lineNumber;
			std::getline(std::cin, text);
			text = text.substr(2, text.length() - 3);
			textList.insert(text, lineNumber);
		}
		else if(userCommand == "delete"){
			std::cin >> lineNumber;
			textList.deleteLine(lineNumber);
		}
		else if(userCommand == "edit"){
			std::cin >> lineNumber;
			std::getline(std::cin, text);
			text = text.substr(2, text.length() - 3);
			textList.edit(text, lineNumber);
		}
		else if(userCommand == "print"){
			textList.print();
		}
		else if(userCommand == "search"){
			std::getline(std::cin, text);
			text = text.substr(2, text.length() - 3);
			textList.search(text);
		}
		else if(userCommand == "quit"){
			return 0;
		}
	}
	return 0;
}