//
//  pa1.cpp
//  
//
//  Created by Nicholas Ionata on 9/20/18.
//

#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

class Node {
	public:
		Node(std::string value);
		std::string data;
		Node* next;
};

//Implementation of Node class
Node::Node(std::string value) {
	data = value;
	next = NULL;
}

class LinkedList {
	private:
		Node* head;
	public:
		LinkedList();
		void insertEnd(std::string value);
		void insert(int index, std::string value);
		void deleteLine(int index);
		void edit(int index, std::string value);
		void print();
		void search(std::string value);
};

//Implementation of LinkedList class
LinkedList::LinkedList() {
	head = NULL;
}

void LinkedList::insertEnd(std::string value) {
	Node* node = new Node(value);
	Node* currentNode = head;
	
	if(currentNode) {
		while(currentNode->next != NULL) {
			currentNode = currentNode->next;
		}
		
		currentNode->next = node;
	} else {
		head = node;
	}
}

void LinkedList::insert(int index, std::string value) {
	Node* node = new Node(value);
	
	if(!head) {
		head = node;
		return;
	}
	
	if(index == 1) {
		Node* temp = head;
		head = node;
		head->next = temp;
	}
	
	Node* prevNode = head;
	Node* currentNode = head->next;
	int currentIndex = 2;
	
	while(currentIndex < index) {
		if(!currentNode) {
			return;
		}
		
		prevNode = currentNode;
		currentNode = currentNode->next;
		currentIndex++;
	}
	
	prevNode->next = node;
	node->next = currentNode;
}

void LinkedList::deleteLine(int index) {
	if(index == 1) {
		head = head->next;
		return;
	}
	
	Node* currentNode = head->next;
	Node* prevNode = head;
	int currentIndex = 2;
	
	while(currentIndex < index) {
		if(!currentNode->next) {
			return;
		}
		
		prevNode = currentNode;
		currentNode = currentNode->next;
		currentIndex++;
	}
	
	prevNode->next = currentNode->next;
}

void LinkedList::edit(int index, std::string value) {
	Node* currentNode = head;
	int currentIndex = 1;
	
	while(currentIndex < index) {
		if(!currentNode->next) {
			return;
		}
		
		currentNode = currentNode->next;
		currentIndex++;
	}
	
	currentNode->data = value;
}

void LinkedList::print() {
	if(!head) {
		return;
	}
	
	Node* currentNode = head;
	int index = 1;
	
	do {
		std::cout << index << " " << currentNode->data << std::endl;
		currentNode = currentNode->next;
		index++;
	} while(currentNode != NULL);
}

void LinkedList::search(std::string value) {
	Node* currentNode = head;
	int currentIndex = 1;
	bool found = false;
	
	while(currentNode) {
		if(currentNode->data.find(value) != std::string::npos) {
			std::cout << currentIndex << " " << currentNode->data << std::endl;
			found = true;
		}
		
		currentNode = currentNode->next;
		currentIndex++;
	}
	
	if(!found) {
		std::cout << "not found" << std::endl;
	}
}

int main() {
	LinkedList* document = new LinkedList();
	bool running = true;
	
	while(running) {
		std::string cmd, baseCmd;
		int firstIndex;
		
		std::getline(std::cin, cmd);
		firstIndex = cmd.find(" ");
		baseCmd = cmd.substr(0, firstIndex);
		
		if(baseCmd == "insertEnd") {
			std::string value = cmd.substr(firstIndex + 1);
			if(value.find("\"") != std::string::npos) {
				value = value.substr(1, value.length() - 2);
			}
			document->insertEnd(value);
		} else if(baseCmd == "insert") {
			std::string args = cmd.substr(firstIndex + 1);
			int secondIndex = args.find(" ");
			std::string lineNumber = args.substr(0, secondIndex);
			std::string value = args.substr(secondIndex + 1, args.length());
			if(value.find("\"") != std::string::npos) {
				value = value.substr(1, value.length() - 2);
			}
			document->insert(std::stoi(lineNumber, NULL), value);
		} else if(baseCmd == "delete") {
			std::string lineNumber = cmd.substr(firstIndex + 1);
			document->deleteLine(std::stoi(lineNumber, NULL));
		} else if(baseCmd == "edit") {
			std::string args = cmd.substr(firstIndex + 1);
			int secondIndex = args.find(" ");
			std::string lineNumber = args.substr(0, secondIndex);
			std::string value = args.substr(secondIndex + 1);
			if(value.find("\"") != std::string::npos) {
				value = value.substr(1, value.length() - 2);
			}
			document->edit(std::stoi(lineNumber, NULL), value);
		} else if(baseCmd == "print") {
			document->print();
		} else if(baseCmd == "search") {
			std::string value = cmd.substr(firstIndex + 1);
			if(value.find("\"") != std::string::npos) {
				value = value.substr(1, value.length() - 2);
			}
			document->search(value);
		} else if(baseCmd == "quit") {
			running = false;
		} else {
			std::cout << "That command doesn't exist! Try agian." << std::endl;
		}
	}
};

