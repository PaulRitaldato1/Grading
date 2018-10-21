#include <string.h>
#include <iostream>
#include <string>

struct Node {
	Node* next;
	std::string line;
};

class List {
private:
	Node* head;
	Node* tail;
public:
	List();
	~List();
	void insertEnd(std::string l);
	void insert(std::string l, int index);
	void del(int index);
	void edit(std::string l, int index);
	void print();
	void search(std::string l);
	void quit();
};

List::List() {
	head = nullptr;
	tail = nullptr;
}

//TO DO
List::~List() {

}

void List::insertEnd(std::string l) {
	Node* newLine = new Node();
	int start = l.find('"');
	//second "
	int start2 = l.find('"', start+1);
	std::string l2 = l.substr(start+1, start2 - start-1);
	newLine->line = l2;
	newLine->next = nullptr;
	if (head == nullptr) {
		head = newLine;
		tail = head;
	}
	else {
		tail->next = newLine;
		tail = newLine;
	}
}

void List::insert(std::string l, int index) {
	Node* current = head;
	Node* newLine = new Node();
	int start = l.find('"');
	//second "
	int start2 = l.find('"', start + 1);
	std::string l2 = l.substr(start+1, start2 - start-1);
	newLine->line = l2;
	if (index == 1) {
		newLine->next = head;
		head = newLine;
	}
	else {
		for (int i = 0; i < index - 2; i++) {
			current = current->next;
		}
		newLine->next = current->next;
		current->next = newLine;
	}
}

void List::del(int index) {
	Node* current = head;
	Node* toDelete;
	if (index == 1) {
		current = head;
		head = head->next;
		delete current;
	}
	else {
		for (int i = 0; i < index - 2 && current->next != nullptr; i++) {
			current = current->next;
		}
		toDelete = current->next;
		current->next = toDelete->next;
		delete toDelete;
	}
}

void List::edit(std::string l, int index) {
	Node* current = head;
	int start = l.find('"');
	//second "
	int start2 = l.find('"', start + 1);
	std::string l2 = l.substr(start+1, start2 - start-1);
	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}
	current->line = l2;
}

void List::print() {
	Node* current = head;
	int i = 1;
	while (current != tail) {
		std::cout << i << " " << current->line << std::endl;
		i++;
		current = current->next;
	}
	std::cout << i << " " << current->line << std::endl;
}

void List::search(std::string l) {
	Node* current = head;
	int start = l.find('"');
	//second "
	int start2 = l.find('"', start + 1);
	std::string l2 = l.substr(start+1, start2 - start-1);
	int i = 1;
	while(current != tail) {
		if (current->line.find(l2) == std::string::npos) {
			current = current->next;
			i++;
		}
		else {
			std::cout << i << " " << current->line << std::endl;
		}
	}
	if (current->line.find(l2) != std::string::npos) {
		std::cout << i << " " << current->line << std::endl;
	}
}

int main() {
	List* document = new List();
	std::string line1;
	int end = -1;
	do {
		std::getline(std::cin, line1);
	
		if (line1.find("insertEnd") != std::string::npos) {
			document->insertEnd(line1);
		}
		else if (line1.find("insert") != std::string::npos) {
			int pos = std::stoi(line1.substr(7, 1));
			document->insert(line1, pos);
		}
		else if (line1.find("delete") != std::string::npos) {
			int pos = std::stoi(line1.substr(7, 1));
			document->del(pos);
		}
		else if (line1.find("edit") != std::string::npos) {
			int pos = std::stoi(line1.substr(5, 1));
			document->edit(line1, pos);
		}
		else if (line1.find("print") != std::string::npos) {
			document->print();
		}
		else if (line1.find("search") != std::string::npos) {
			document->search(line1);
		}
		else if (line1.find("quit") != std::string::npos) {
			end = 0;
		}
	} while (end == -1);

}