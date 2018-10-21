#include "LinkedList.h"
#include <iostream>


LinkedList::LinkedList() //Default Constructor
{
	head = nullptr;
	tail = nullptr;
}


LinkedList::~LinkedList() //Destructor
{
	Node* iter = head;
	while (iter != NULL) {
		Node *temp = iter;
		delete iter;
		iter = temp;
	}
}




void LinkedList::print() {
	iter = head;
	while (iter != nullptr) {
		std::cout << iter->lineNum << " " << iter->data << std::endl;
		iter = iter->next;
	}
	iter = nullptr;
}

void LinkedList::edit(int lineNum, std::string editLine)
{
	iter = head;
	int count = 1;
	while ((iter != nullptr) && (count < lineNum)) {
		iter = iter->next;
		++count;
	}
	iter->data = editLine;
	iter = nullptr;
}

void LinkedList::insertEnd(std::string newLine) {
	Node* newNode = new Node; 
	newNode->data = newLine;
	newNode->next = nullptr;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		newNode = NULL;
	}
	else {
		tail->next = newNode;
		tail = tail->next;
	}
	fixLineNum();
}

void LinkedList::insert(std::string insertLine, int insertSlot) {
	
	iter = head;
	int i = 1;
	if (insertSlot == 1) {
		Node* newNode = new Node;
		newNode->data = insertLine;
		newNode->next = head;
		head = newNode;
		iter->next = nullptr;
		fixLineNum();
		return; 
	}
	while ((iter != nullptr) && (i < insertSlot-1)) {
		iter = iter->next;
		i++;
	}
	if (iter == nullptr) {
		insertEnd(insertLine);
		return;
	}
	Node* newNode = new Node;
	newNode->data = insertLine;
	newNode->next = iter->next;
	iter->next = newNode;
	fixLineNum();
	
}

void LinkedList::deleteNode(int deleteSlot){
	if (head->lineNum == deleteSlot) {
		iter = head;
		head = head->next;
		iter->next = nullptr;
		fixLineNum();
		return;
	}
	Node* prev = head;
	iter = head->next;
	
	while ((iter != nullptr)) {
		if (iter->lineNum == deleteSlot) {
			prev->next = iter->next;
			iter->next = nullptr;
		}
		prev = iter;
		iter = iter->next;
	}

	fixLineNum();
}

void LinkedList::search(std::string searchString) {
	iter = head; 
	bool found = false;
	while (iter != nullptr) {
		if (iter->data.find(searchString) != std::string::npos) {
			std::cout << iter->lineNum << " " << iter->data << std::endl;
			found = true;
		}
		iter = iter->next;
	}
	if (found == false) { std::cout << "not found"; }
}

void LinkedList::fixLineNum() {
	iter = head;
	int i = 1;
	while (iter != nullptr) {
		iter->lineNum = i;
		iter = iter->next;
		++i;
	}
}

