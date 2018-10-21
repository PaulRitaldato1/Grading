#include <iostream>
#include <string>

struct node {
	node();
	~node();
	std::string line;
	node* next;
};

class linkedlist {
private:
	node * head, *tail;
public:
	linkedlist();
	~linkedlist();
	void insertEnd(std::string text); //insertEnd "text"  -- insert given text at the end of the document
	void insert(int index, std::string text); //insert 3 "text" --insert given text at the line indicated by index given
	void deleteLine(int index); //delete 3 --- delete line at index given
	void edit(int index, std::string text); //edit 3 "text" --- replace the line at the index given with the given text
	void print(); //print -- print the entire document, with line numbers
	void search(std::string text); //search "text" -- print the line number and line that contains the given text. print "not found" if it is not found
	int findLength();
};

linkedlist::linkedlist() {
	head = nullptr;
	tail = nullptr;
}

linkedlist::~linkedlist() {
	node* tracker = new node;
	tracker = head;

	while (tracker->next != nullptr) {
		node* nextOne = tracker->next;
		delete tracker;
		tracker = nextOne;
	}
}

node::node() {

}

node::~node() {

}

void linkedlist::insertEnd(std::string text) {
	//creating the node to be added and adding data
	node* newline = new node;
	newline->line = text;

	//if the list is empty, set the head and tail to the new node
	if (head == nullptr) {
		head = newline;
		tail = newline;
		head->next = nullptr;
		tail->next = nullptr;
	}
	else { 
		//if not empty, use tail to add newline to end of list
		tail->next = newline;
		newline->next = nullptr;
		tail = newline;
	}
}

void linkedlist::insert(int index, std::string text) {
	//intitializing node pointers and variables
	node* newline = new node;
	newline->line = text;
	node* prev = new node;
	prev = head;
	node* tracker = new node;
	tracker = head;
	int currLength = findLength();

	//the node cannot be added one above the current length, so return
	if (index > currLength + 1) {
		return;
	}

	//add node at the start of the list
	if (index == 1) {
		newline->next = head;
		head = newline;
		if (head->next == nullptr) {
			tail = newline;
		}
	}

	//add node at end of the list
	if (index == currLength && index != 1) {
		while (tracker->next != nullptr) {
			prev = tracker;
			tracker = tracker->next;
		}
		prev->next = newline;
		newline->next = tracker;
		tail = newline->next;
	}

	//add node in the middle of the list
	if (index != 1 && index != currLength) {
		for (int i = 0; i < index - 1; i++) {
			prev = tracker;
			tracker = tracker->next;
		}
		prev->next = newline;
		newline->next = tracker;
		if (newline->next == nullptr) {
			tail = newline;
		}
	}

}

void linkedlist::deleteLine(int index) {
	//initialize tracker and prev nodes
	node* tracker = new node;
	tracker = head;
	node* prev = new node;
	prev = head;
	int currLength = findLength();

	//if there is no line to be deleted, return
	if (index > currLength) {
		return;
	}

	//the node to be deleted is the first node
	if (index == 1) {
		head = head->next;
		if (head->next == nullptr) {
			tail = head;
		}
	}

	//the node to be deleted is the last node
	if (index == currLength && index != 1) {
		tracker = head->next;

		while (tracker->next != nullptr) {
			prev = prev->next;
			tracker = tracker->next;
		}
		delete tracker;
		prev->next = nullptr;
		tail = prev;
	}

	//the node to be deleted is in the middle of the list
	if (index != 1 && index != currLength) {
		for (int i = 0; i < index - 1; i++) {
			prev = tracker;
			tracker = tracker->next;
		}
		prev->next = tracker->next;
		delete tracker;
	}
}

void linkedlist::edit(int index, std::string text) {
	//initialize tracker node pointer
	node* tracker = new node;
	tracker = head;

	//iterate until reaching the correct node
	for (int i = 0; i < index - 1; i++) {
		if (tracker == nullptr) {
			break;
		}
		tracker = tracker->next;
	}
	//edit the text of the proper node
	tracker->line = text;
}

void linkedlist::print() {
	//initialize pointer nodes and index
	node* tracker = new node;
	tracker = head;
	int index = 1;

	//iterate through and print each node
	while (tracker != nullptr) {
		std::cout << index << " ";
		std::cout << tracker->line << std::endl;

		tracker = tracker->next;
		index++;
	}
}

void linkedlist::search(std::string text) {
	//initialize bools and pointer nodes and variables
	node* tracker = new node;
	tracker = head;
	bool stringFound = false;
	bool stringFoundEver = false;
	int index = 1;

	while (tracker != nullptr) {
		stringFound = false;
		//if the string has been found, change bool values
		if (tracker->line.find(text) != std::string::npos) {
			stringFound = true;
			stringFoundEver = true;
		}
		if (stringFound) {
			//print the line of the found string
			std::cout << index << " " << tracker->line << std::endl;
		}
		tracker = tracker->next;
		index++;
	}
	if (!stringFoundEver) {
		std::cout << "not found" << std::endl;
	}
}

int linkedlist::findLength() {
	int length = 0;

	node* tracker = new node;
	tracker = head;

	while (tracker != nullptr) {
		++length;
		tracker = tracker->next;
	}

	return length;
}

int getNum(std::string input) {
	//integer extractor adapted from https://stackoverflow.com/questions/23232190/extracting-integers-from-strings-in-c-with-arbitrary-structure

	int start = input.find_first_of("0123456789");
	int end = input.find_last_of("0123456789");

	std::string numString = input.substr(start, end - start + 1);
	int index = atoi(numString.c_str());

	return index;
}

std::string getText(std::string input) {
	int start = input.find_first_of('"');
	int end = input.length();

	std::string text = input.substr(start + 1, end);
	text = text.substr(0, text.length() - 1);

	return text;
}

bool checkForQuotes(std::string input) {
	bool quotesFound = false;
	if (input.find('"') != std::string::npos) {
		quotesFound = true;
	}
	return quotesFound;
}

int main() {

	linkedlist* list = new linkedlist;
	std::string input;
	std::string command;
	std::string text;
	std::string numString;

	while (command != "quit") {
		int index = 0;

		std::getline(std::cin, input);

		command = input.substr(0, input.find_first_of(" "));

		if (command == "insertEnd") {
			if (!checkForQuotes(input)) {
				continue;
			}
			text = getText(input);
			list->insertEnd(text);
		}
		else if (command == "insert") {
			if (!checkForQuotes(input)) {
				continue;
			}
			index = getNum(input);
			text = getText(input);
			list->insert(index, text);
		}
		else if (command == "delete") {
			index = getNum(input);
			list->deleteLine(index);
		}
		else if (command == "edit") {
			if (!checkForQuotes(input)) {
				continue;
			}
			index = getNum(input);
			text = getText(input);
			list->edit(index, text);
		}
		else if (command == "print") {
			list->print();
		}
		else if (command == "search") {
			if (!checkForQuotes(input)) {
				continue;
			}
			text = getText(input);
			list->search(text);
		}
		else if (command == "quit") {
			break;
		}

	}
	
}