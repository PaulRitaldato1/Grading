#include "List.h"
#include <iostream>
#include <string>

Node::Node(std::string line) {
	this->line = line;
	this->next = NULL;
}

//Inserts node at the end of list
void List::insertEnd(std::string line) {

	//Checks if line length is less than 80 characters, otherwise terminates
	if(line.length() > 82) {
		//std::cout<<"Line length larger than 80 characters"<<std::endl;
		return;
	}

	//Checks if line starts and ends with quotation marks, otherwise terminates
	if(line.at(0) != '"' || line.at(line.length() - 1) != '"' || line.length() == 1) {
		//std::cout<<"No quotation marks"<<std::endl;
		return;
	}
	Node* newNode = new Node(line);
	size ++; 
	
	//If the list is empty, set new node to head and tail
	if(head == NULL) {
		head = newNode;
		tail = newNode;
		return;
	}
	//Otherwise, set tail to new node after going to end of list
	tail->next = newNode;
	tail = newNode;
	return;
}

//Inserts node at desired index
void List::insert(std::string line, int index) {

	//Checks if line length is less than 80 characters
	if(line.length() > 82) {
		//std::cout<<"Line length larger than 80 characters"<<std::endl;
		return;
	}

	//Checks if line starts and ends with quotation marks
	if(line.at(0) != '"' || line.at(line.length() - 1) != '"' || line.length() == 1) {
		//std::cout<<"No quotation marks"<<std::endl;
		return;
	}

	//Checks for invalid input
	if(index < 1 || index > size + 1) {
		//std::cout<<"Index out of bounds"<<std::endl;
		return;
	}

	Node* newNode = new Node(line);
	size ++;
	//If index = 1, replace prev head with new node
	if(index == 1) {
		newNode->next = head;
		head = newNode;
		return;
	}
	Node* curr = head;
	Node* prev = NULL;
	//Iterate through loop until index, with new node being in between prev and curr
	for(int i = 1; i < index; i ++) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = newNode;
	newNode->next = curr;
	//If new node next is NULL, set it to tail
	if(curr == NULL) {
		tail = newNode;
	}
	return;
}

//Removes node at desired index
void List::remove(int index) {

	//Checks for invalid input
	if(index < 1 || index > size) {
		//std::cout<<"Index out of bounds"<<std::endl;
		return;
	}
	Node* curr = head;
	Node* prev = NULL;
	size --;
	//If deleting index 0, change head to next node
	if(index == 1) {
		Node* temp = curr;
		head = curr->next;
		delete(temp);
		return;
	}
	//Iterate through loop, will change prev->next = curr->next and delete curr
	for(int i = 1; i < index; i ++) {
		prev = curr;
		curr = curr->next;
	}
	Node* temp = curr;
	prev->next = curr->next;
	delete(curr);
	return;
}

//Edit a previous node's data
void List::edit(std::string newLine, int index) {

	//Checks if line length is less than 80 characters
	if(newLine.length() > 82) {
		//std::cout<<"Line length larger than 80 characters"<<std::endl;
		return;
	}

	//Checks if line starts and ends with quotation marks
	if(newLine.at(0) != '"' || newLine.at(newLine.length() - 1) != '"' || newLine.length() == 1) {
		//std::cout<<"No quotation marks"<<std::endl;
		return;
	}
	//Checks for invalid input
	if(index < 1 || index > size + 1) {
		//std::cout<<"Index out of bounds"<<std::endl;
		return;
	}
	Node* curr = head;
	//Iterate through loop, continue until curr is desired node to edit
	for(int i = 1; i < index; i ++) {
		curr = curr->next;
	}
	curr->line = newLine;
	return;
}

//Prints out the entire list 
void List::print() {
	Node* curr = head;
	for(int i = 0; i < size; i ++) {
		std::cout<<i + 1<<" "<<curr->line.substr(1, curr->line.length() - 2)<<std::endl;
		curr = curr->next;
	}
}

//Searches for the (first) line with the desired text
void List::search(std::string line) {

	//Checks if line length is less than 80 characters
	if(line.length() > 82) {
		//std::cout<<"Line length larger than 80 characters"<<std::endl;
		return;
	}

	//Checks if line starts and ends with quotation marks
	if(line.at(0) != '"' || line.at(line.length() - 1) != '"' || line.length() == 1) {
		//std::cout<<"No quotation marks"<<std::endl;
		return;
	}

	Node* curr = head;
	bool lineFound = false;
	line = line.substr(1, line.length() - 2);

	for(int i = 0; i < size; i ++) {
		std::size_t found = curr->line.find(line);
		if(found != std::string::npos) {
			std::cout<<i + 1<<" "<<curr->line.substr(1, curr->line.length() - 2)<<std::endl;
			lineFound = true;
		}
		curr = curr->next;
	}
	if(!lineFound) {
		std::cout<<"not found"<<std::endl;
	}
	return;
}

int main() {
	bool keepRunning = true;
	List* document = new List();
	while(keepRunning) {
		std::string command;
		std::cin>>command;
		if(command.compare("insertEnd") == 0) {
			std::string newLine;
			std::cin.ignore(1);
			std::getline(std::cin, newLine);
			document->insertEnd(newLine);
		}
		else if(command.compare("insert") == 0) {
			int index;
			std::cin>>index;
			std::string newLine;
			std::cin.ignore(1);
			std::getline(std::cin, newLine);
			document->insert(newLine, index);
		}
		else if(command.compare("delete") == 0) {
			int index;
			std::cin>>index;
			document->remove(index);
		}
		else if(command.compare("print") == 0) {
			document->print();
		}
		else if(command.compare("search") == 0) {
			std::string searchLine;
			std::cin.ignore(1);
			std::getline(std::cin, searchLine);
			document->search(searchLine);
		}
		else if(command.compare("edit") == 0) {
			int index;
			std::cin>>index;
			std::string newLine;
			std::cin.ignore(1);
			std::getline(std::cin, newLine);
			document->edit(newLine, index);
		}
		else if(command.compare("quit") == 0) {
			keepRunning = false;
		}
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}
	return 0;
}