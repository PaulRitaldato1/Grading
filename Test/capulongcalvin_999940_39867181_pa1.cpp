#include <iostream>
#include <queue>
#include <string>

struct Node {
	std::string value;
	Node *next = NULL;
};

class List {
public:
	Node* head;
	List();
};

List::List() {
	this->head = NULL;
}


int listLength(Node* head) {
	int length = 1;
	Node *curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
		length++;
	}
	return length;
}

void insertLast(Node* head, std::string str) {
	if (head->value == "") {
		head->value = str;
		return;
	}
	Node *newNode = new Node();
	newNode->value = str;
	Node *curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = newNode;
}

void insertAt(Node* head, int position, std::string str) {
	if (position > listLength(head) + 1)
		return;
	if (position == (listLength(head) + 1)) {
		insertLast(head, str);
		return;
	}
	if (head->value == "" && position == 0) {
		head->value = str;
		return;
	}
	Node *newNode = new Node();
	newNode->value = str;

	int currIndex = 1;
	Node* curr = head;
	while (currIndex < position - 1) {
		if (curr == NULL)
			return;
		curr = curr->next;
		currIndex++;
	}
	Node* next = curr->next;
	newNode->next = next;
	curr->next = newNode;
}


void remove(Node* head, int position) {
	if (position > listLength(head))
		return;
	if (position == 1) {
		head = head->next;
		return;
	}
	int currIndex = 1;
	Node* curr = head;
	while (currIndex < position - 1) {
		curr = curr->next;
		currIndex++;
	}
	Node* next = curr->next->next;
	curr->next = next;
}

void edit(Node* head, int position, std::string str) {
	if (position > listLength(head))
		return;
	int currIndex = 1;
	Node* curr = head;
	while (currIndex < position) {
		curr = curr->next;
		currIndex++;
	}
	curr->value = str;
}

std::queue<int> search(Node* head, std::string str) {
	std::queue<int> foundIndices;
	int index = 1;
	Node* curr = head;
	while (curr != NULL) {
		if (curr->value.find(str) != std::string::npos) {
			foundIndices.push(index);
		}
		curr = curr->next;
		index++;
	}
	if (foundIndices.empty())
		foundIndices.push(-1);
	return foundIndices;;
}

void print(Node* head) {
	int count = 1;
	Node* curr = head;
	while (curr != NULL) {
		std::cout << count << " " << curr->value;
		curr = curr->next;
		count++;
		std::cout << "\n";
	}
}

void printNode(Node* head, int position) {
	int currIndex = 1;
	Node* curr = head;
	while (currIndex < position) {
		curr = curr->next;
		currIndex++;
	}
	std::cout << position << " " << curr->value;
	std::cout << "\n";
}

std::string parseLine(std::string line) {
	return line.substr(2, line.length() - 3);
}

int main()
{
	Node *head = new Node();
	std::string command = "";
	std::string line = "";
	int lineNumber = 0;
	while (command != "quit") {
		std::cin >> command;
		if (command == "insertEnd") {
			std::getline(std::cin, line);
			line = parseLine(line);
			insertLast(head, line);
		}
		if (command == "insert") {
			std::cin >> lineNumber;
			std::getline(std::cin, line);
			line = parseLine(line);
			insertAt(head, lineNumber, line);
		}
		if (command == "delete") {
			std::cin >> lineNumber;
			remove(head, lineNumber);
		}
		if (command == "edit") {
			std::cin >> lineNumber;
			std::getline(std::cin, line);
			line = parseLine(line);
			edit(head, lineNumber, line);
		}
		if (command == "search") {
			std::getline(std::cin, line);
			line = parseLine(line);
			std::queue<int> foundIndices = search(head, line);
			while (!foundIndices.empty()) {
				int foundLineNumber = foundIndices.front();
				if (foundLineNumber == -1)
					std::cout << "not found" << "\n";
				else
					printNode(head, foundLineNumber);
				foundIndices.pop();
			}
		}
		if (command == "print")
			print(head);
	}
}