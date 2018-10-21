//your linked list implementation here
#include <string>
#include <iostream>
#include <sstream>
class Node {
    std::string text;
public:
    Node(std::string content); //constructor
    Node * next; //next node
    void setText(std::string text);
    std::string getText();
};

class LinkedList {
public:
    LinkedList(void); //constructor
    Node * head; //head node
    void insertEnd(std::string lineToEnter);
    void insertAtLine(std::string lineToEnter, int index);
    void deleteAtLine(int index);
    void editAtLine(std::string lineToEnter, int index);
    void printLines();
    void searchList(std::string linetoSearch);
};

        //your line editor implementation here
void LinkedList::insertEnd(std::string lineToEnter) {
    Node * curr = head;
    if (curr == NULL) {
    	head = new Node(lineToEnter);
    }
    else {
    	while (curr != NULL) {
		if (curr->next == NULL) { 
			curr->next = new Node(lineToEnter);
			break;
		}
		curr = curr->next;
	    }
    }
}

void LinkedList::insertAtLine(std::string lineToEnter, int index) {
	int lineIndex = 2;
	Node * curr = head;
	Node * temp = new Node(lineToEnter);
	if (curr == NULL && index == 1) {
		head = new Node(lineToEnter);
	}
	else {
		if (index == 1) {
			temp->next = curr;
			head = temp;
		}
		else {
			while (curr != NULL) {
				if (lineIndex == index) {
					temp->next = curr->next;
					curr->next = temp;
					break;
				}
				curr = curr->next;
				lineIndex++;
			}
		}
	}
}

void LinkedList::deleteAtLine(int index) {
	int lineIndex = 2;
	Node * curr = head;
    if (head != NULL) {
           if (index == 1) {
                head = head->next;
        	}
	        while (curr->next != NULL) {
        	    if (lineIndex == index) {
             		    curr->next = curr->next->next;
                        break;
        	    }
        	    else {
             		    curr = curr->next;   
			            lineIndex++;
        	    }
    	    }
    }
}

void LinkedList::editAtLine(std::string lineToEnter, int index) {
	int lineIndex = 1;
	Node * curr = head;
    	while (curr != NULL) {
		if (lineIndex == index) {
			curr->setText(lineToEnter);
			break;
		}
		curr = curr->next;
		lineIndex++;
	}
}

void LinkedList::printLines() {
    int lineIndex = 1;
    Node * curr = head;
    while (curr != NULL) {
	std::cout << lineIndex;
	std::cout << " ";
    std::cout << curr->getText() << std::endl;
	curr = curr->next;
	lineIndex++;
    }
}

void LinkedList::searchList(std::string lineToSearch) {
    int lineIndex = 1;
    Node * curr = head;
    bool containsText = false;
    bool textIsFound = false;
	while (curr != NULL) {
		for (int i = 0; i < 1 + curr->getText().length() - lineToSearch.length(); i++) {
			if (curr->getText().substr(i,lineToSearch.length()) == lineToSearch) {
				containsText = true;
				break;
			}
		}
		if (containsText) {
			std::cout << lineIndex;
			std::cout << " ";
			std::cout << curr->getText() << std::endl;
			containsText = false;
			textIsFound = true;
		}
		curr = curr->next;
		lineIndex++;
	}
	if (head == NULL || (!textIsFound)) {
		std::cout << "not found" << std::endl;
	}
}

LinkedList::LinkedList() { //creates empty linked list
	head = NULL;
}

Node::Node(std::string text) { //node constructor
    setText(text);
}

void Node::setText(std::string text) { 
    this->text = text;
}

std::string Node::getText() { 
    return text;
}

int main(){
    LinkedList lineEditor = *new LinkedList();
    //your code to invoke line editor here
    std::string command; //user input
    int index; //marks node to modify
    std::string indexString; //to be converted to integer
    bool tooManySpaces = false; //determines whether multiple spaces are being used
    int indexDigits = 1; //which digits of line is being sought
    while (true) {
	std::getline(std::cin, command);
	while (command.substr(0,1) == " ") { //deletes spaces before command
			command = command.substr(1, command.length()-1);
	}
	for (int i = 0; i < command.length(); i++) { //deletes unnecessary spaces between command and quotation marks
		if (command.substr(i,1) == "\"") {
			break;
		}
		if (command.substr(i,1) == " ") {
			if (tooManySpaces) {
				command = command.substr(0,i) + command.substr(i+1,command.length()-i); //deletes extraneous space
				i--; //moves i to new position
			}
			else {
				tooManySpaces = true; //start checking for multiple spaces
			}
		}
		else if (tooManySpaces) {
			tooManySpaces = false; //indicates streak of spaces has stopped
		}
	}
	if (command == "quit") {
		return 0;
	}
	if (command.substr(0,9) == "insertEnd") {
		command = command.substr(10,command.length()-10);
		if (command[0] == '\"' && command[command.length()-1] == '\"') {
			command = command.substr(1,command.length()-2);
			lineEditor.insertEnd(command);
		}
	}
	if (command.substr(0,6) == "insert" && command.substr(6,1) != "E") {
		while (true) {
			if (command.substr(indexDigits+7,1) != " ") {
				indexDigits++;
			}
			else {
				break;
			}
		}
		indexString = command.substr(7,indexDigits);
		std::istringstream (indexString) >> index;
		command = command.substr(8+indexDigits,command.length()-8-indexDigits);
		if (command[0] == '\"' && command[command.length()-1] == '\"') {
			command = command.substr(1,command.length()-2);
			lineEditor.insertAtLine(command, index);
		}
		indexDigits = 0;
	}
	if (command.substr(0,6) == "delete") {
        while (true) {
			if (command.length() > indexDigits+7 && command.substr(indexDigits+7,1) != " ") {
				indexDigits++;
			}
			else {
				break;
			}
		}
		indexString = command.substr(7,indexDigits);
		std::istringstream (indexString) >> index;
		lineEditor.deleteAtLine(index);
        indexDigits = 0;
	}
	if (command.substr(0,4) == "edit") {
        while (true) {
			if (command.substr(indexDigits+5,1) != " ") {
				indexDigits++;
			}
			else {
				break;
			}
		}
		indexString = command.substr(5,indexDigits);
		std::istringstream (indexString) >> index;
		command = command.substr(6+indexDigits,command.length()-6-indexDigits);
		if (command[0] == '\"' && command[command.length()-1] == '\"') {
			command = command.substr(1,command.length()-2);
			lineEditor.editAtLine(command, index);
		}
        indexDigits = 0;
	}
	if (command.substr(0,5) == "print") {
		lineEditor.printLines();
	}
	if (command.substr(0,6) == "search") {
		command = command.substr(7,command.length()-7);
		if (command[0] == '\"' && command[command.length()-1] == '\"') {
			command = command.substr(1,command.length()-2);
			lineEditor.searchList(command);
		}
	}
    }
}
