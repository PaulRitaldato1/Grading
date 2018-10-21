#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class LinkedList {
public:
	LinkedList();
	void deleteNode(int index);
	void editNodeData(string newData, int index);
	void printList();
	void insertEnd(string data);
	void insert(string data, int index);
	void search(string data);


private:
	struct node {
		string data;
		node* next;
	};
	node* head;
	node* tail;
};

LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;
}

void LinkedList::insert(string data, int index) {
	node* current = head;
	node* newNode = new node;
	newNode->data = data;
	if (index == 1) {
		newNode->next = current;
		head = newNode;
		return;
	}
	for (int i = 0; i < index-2; i++) {
		current = current->next;
		if (current == NULL) return;
	}
	
	newNode->next = current->next;
	current->next = newNode;
}

void LinkedList::search(string data) {
	node* current = head;
	int counter = 1;
	bool found = false;
	while (current != NULL) {
		if (current->data.find(data) != string::npos) {
			cout << counter << " " + current->data + "\n";
			found = true;
		}
		counter++;
		current = current->next;
	}
	if(!found) cout << "not found\n";
}

void LinkedList::deleteNode(int index) {
	node* current = head;
	if (index == 1) {
		if (head != NULL) {
			head = head->next;
			return;
		}
		return;
	}

	for (int i = 0; i < index-2; i++) {
		if (current->next == NULL) break;
		else current = current->next;
	}
	if (current->next != NULL) {
		current->next = current->next->next;
	}
}

void LinkedList::editNodeData(string newData, int index) {
	node* current = head;
	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}
	current->data = newData;
}

void LinkedList::insertEnd(string data) {
	node* Tail = new node;
	Tail->next = NULL;
	Tail->data = data;
	if (head != NULL) {
		tail->next = Tail;
		tail = Tail;
	}
	else {
		head = Tail;
		tail = Tail;
	}
}


void LinkedList::printList() {
	node* current;
	current = head;
	int counter = 1;
	while (true) {
		if (current) {
			cout << counter << " " + current->data + "\n";
			counter++;
			current = current->next;
		}
		else {
			break;
		}
	}
}

int main(){
	
	LinkedList list = LinkedList();
	string function;
	int index;
	string input;
	while (true) {
		cin >> function;
		if (function.find("insertEnd") != string::npos) {
			getline(cin, input);
			input = input.substr(2, input.length()-3);
			list.insertEnd(input);
			continue;
		}
		if (function.find("insert") != string::npos) {
			cin >> index;
			getline(cin, input);
			input = input.substr(2, input.length() - 3);
			list.insert(input, index);
			continue;
		}
		if (function.find("print") != string::npos) {
			list.printList();
			continue;
		}
		if (function.find("search") != string::npos) {
			getline(cin, input);
			input = input.substr(2, input.length() - 3);
			list.search(input);
			continue;
		}
		if (function.find("delete") != string::npos) {
			cin >> index;
			list.deleteNode(index);
			continue;
		}
		if (function.find("edit") != string::npos) {
			cin >> index;
			getline(cin, input);
			input = input.substr(2, input.length() - 3);
			list.editNodeData(input, index);
			continue;
		}
		if (function.find("quit") != string::npos) {
			break;
		}
	}
	return 0;

}