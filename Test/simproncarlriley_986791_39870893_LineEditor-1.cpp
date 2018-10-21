#include <iostream>
#include <string>
#include <algorithm>

class LinkedList {
private:
	struct Node {
		std::string data;
		Node* next;
	};

	Node* head;
	Node* tail;
	Node* pointer;

public:
	LinkedList();
	bool InsertEnd(std::string text);
	void Insert(int index, std::string text);
	void Delete(int index);
	void Edit(int index, std::string text);
	void Print();
	void Search(std::string searchItem);
};

LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;
}

void LinkedList::Print() {
	pointer = head;
	int lineCounter = 1;
	while (pointer) {	//for loop exits when pointer == NULL.
		std::cout << lineCounter << " " << pointer->data << std::endl;
		pointer = pointer->next;
		lineCounter++;
	}
}

bool LinkedList::InsertEnd(std::string text) {
	Node* newTail = new Node();
	newTail->data = text;
	newTail->next = NULL;
	if (head == NULL && tail == NULL) {	//If the linked list is empty. 
		tail = newTail;
		head = newTail;
	}
	else {
		tail->next = newTail;	//Sets the last node in the list to point to the newly added node.
		tail = newTail;
	}
	return true;
}

void LinkedList::Insert(int index, std::string text) {
	pointer = head;
	Node* newNode = new Node();
	newNode->data = text;
	while (pointer) {
		if (index == 2) {
			newNode->next = pointer->next;
			pointer->next = newNode;
			return;
		}
		pointer = pointer->next;
		index--;
	}
}

void LinkedList::Delete(int index) {
	if ((head == tail) && index == 1) {	//Case for when the linked list contains only 1 Node.
		head = NULL;
		tail = NULL;
		return;
	}

	pointer = head;
	Node* deleteNode = head;

	if (index == 1) {	//Case for when the user wants to delete the head node in a list with more than 1 node.
		head = head->next;
		return;
	}

	while (deleteNode->next != NULL) {
		deleteNode = deleteNode->next;
		index--;
		if (index == 1) {
			if (deleteNode == tail) {	//Case for when the user wants to delete the tail node
				tail = pointer;
				pointer->next = NULL;
				return;
			}
			else {    	//Case for when the user wants to delete some node in the middle of the list.
				deleteNode = deleteNode->next;
				pointer->next = deleteNode;
				return;
			}
		}
		pointer = pointer->next;
	}
}

void LinkedList::Edit(int index, std::string text) {
	pointer = head;
	for (int counter = 1; pointer; counter++) {
		if (counter == index) {
			pointer->data = text;
			return;
		}
		pointer = pointer->next;
	}
	std::cout << "Index out of range" << std::endl;
	return;
}

void LinkedList::Search(std::string searchItem) {
	bool found = false;
	pointer = head;
	for (int counter = 1; pointer; counter++) {
		if (pointer->data.find(searchItem) != std::string::npos) {
			std::cout << counter << " " << pointer->data << std::endl;
			found = true;
		}
		pointer = pointer->next;
	}
	if (!found) {
		std::cout << "not found" << std::endl;
	}
}

int main()
{
	LinkedList lineEditor;
	std::string userInput = "";
	std::string text = "";
	int index = 0;

	while (true) {
		std::cin >> userInput;	//You must clear this input (see lines 20 - 21).
		std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);	//Makes the string lower case. From #include <algorithm>

		if (userInput.compare("insertend") == 0) {
			std::cin.clear();			//These two lines clear the input buffer so the getline function
			std::cin.ignore();			//only gets the text you want to insert and not the option you typed in earlier.
			getline(std::cin, text);
			if ((text.at(0) != '"') || (text.at(text.length() - 1) != '"') || (text.length() - 2 > 80)) {    //Checks to make sure                                                                                             that the input text has the quotation marks                                                                                           and if the input text is less than 80                                                                                                 characters (not including quotation marks).
				continue;
			}
			text = text.substr(1, text.length() - 2);	//This filters out the quotation marks in the user input.
			lineEditor.InsertEnd(text);
		}

		else if (userInput.compare("insert") == 0) {
			std::cin >> index;
			std::cin.clear();
			std::cin.ignore();
			getline(std::cin, text);
			if ((text.at(0) != '"') || (text.at(text.length() - 1) != '"') || (text.length() - 2 > 80)) {
				continue;
			}
			text = text.substr(1, text.length() - 2);	//This filters out the quotation marks in the user input.
			lineEditor.Insert(index, text);
		}

		else if (userInput.compare("delete") == 0) {
			std::cin >> index;
			lineEditor.Delete(index);
		}

		else if (userInput.compare("edit") == 0) {
			std::cin >> index;
			std::cin.clear();
			std::cin.ignore();
			getline(std::cin, text);
			if ((text.at(0) != '"') || (text.at(text.length() - 1) != '"') || (text.length() - 2 > 80)) {
				continue;
			}
			text = text.substr(1, text.length() - 2);	//This filters out the quotation marks in the user input.
			lineEditor.Edit(index, text);
		}

		else if (userInput.compare("print") == 0) {
			lineEditor.Print();
		}

		else if (userInput.compare("search") == 0) {
			std::cin.clear();
			std::cin.ignore();
			getline(std::cin, text);
			text = text.substr(1, text.length() - 2);	//This filters out the quotation marks in the user input.
			lineEditor.Search(text);
		}

		else if (userInput.compare("quit") == 0) {
			break;
		}
	}
}