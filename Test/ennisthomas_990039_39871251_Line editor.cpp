// Line editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class linkedList {
private:
	struct nodeObject {
		string data;
		nodeObject *next;
	};
	typedef struct nodeObject * nodePointer;

	nodePointer head;
	nodePointer tail;
	nodePointer temp;
	nodePointer curr;
	nodePointer prev;
	nodePointer insertNode;

public:
	linkedList();

	void addNode(string data);
	void deleteNode(int index);
	void printList();
	void searchList(string data);
	void insertList(int index, string data);
	void editList(int index, string data);
};

linkedList::linkedList() {
	head = NULL;
	tail = NULL;
}

void linkedList::addNode(string data) {
	nodePointer newTail = new nodeObject;
	newTail->data = data;
	newTail->next = NULL;

	if (head == NULL) {
		head = newTail;
		tail = newTail;
	}
	else {
		tail->next = newTail;
		tail = newTail;
	}
}

void linkedList::deleteNode(int index) {
	nodePointer temp = head;
	nodePointer curr = head;
	nodePointer prev = head;
	int count = 1;

	for (int i = 1; i < index; i++) {
		if (curr->next != NULL) {
			prev = curr;
			curr = curr->next;
			count++;
		}
	}
	if (count < index) {
		return;
	}
	if (head == NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
	else {
		temp = curr;
		prev->next = curr->next;
		delete temp;
	}
}

void linkedList::printList() {
	nodePointer curr = head;
	int lineNum = 1;
	if (head == NULL) {
		cout << "Nothing to print" << endl;
	}
	curr = head;
	while (curr != NULL) {
		
		cout << lineNum << " " << curr->data;
		cout << endl;
		if (curr->next != NULL) {
			curr = curr->next;
			lineNum++;
		}
		else {
			break;
		}
	}
}

void linkedList::searchList(string data) {
	int count = 1;
	bool didPrint = false;
	curr = head;
	if (head == NULL) {
		cout << "Nothing in list yet." << endl;
	}
	else {
		while (curr != NULL) {
			if (curr->data.find(data) != -1) {
				cout << count << " " << curr->data << endl;
				count++;
				curr = curr->next;
				didPrint = true;
			}
			else if (curr->next == NULL && didPrint == false) {
				cout << "not found" << endl;
				break;
			}
			else if (curr->next == NULL) {
				break;
			}
			else {
				count++;
				curr = curr->next;
			}
		}
	}
}

void linkedList::insertList(int index, string data) {
	prev = head;
	curr = head;
	int count = 1;
	nodePointer insertNode = new nodeObject;
	insertNode->data = data;
	for (int i = 1; i < index; i++) {
		if (curr->next != NULL) {
			prev = curr;
			curr = curr->next;
			count++;
		}
	}
	if (count + 1 == index) {
		curr->next = insertNode;
		insertNode->next = NULL;
	}
	else if (count < index) {
		return;
	}
	else {
		insertNode->next = curr;
		prev->next = insertNode;
	}
}

void linkedList::editList(int index, string data) {
	curr = head;
	for (int i = 1; i < index; i++) {
		curr = curr->next;
	}
	curr->data = data;
}

int main()
{
	linkedList lineEditor;
	string input;
	string text;
	string indexChar;
	int indexNum;
	int temp;
	stringstream stream;
	bool keepGoing = true;

	while (keepGoing) {

		getline(cin, input);

		if (input == "quit") {
			break;
		}
		else if (input == "print") {
			lineEditor.printList();
		}
		else if (input.substr(0,9) == "insertEnd") {
			text = input.substr(11);
			text.pop_back();
			lineEditor.addNode(text);
		}
		else if (input.substr(0, 6) == "delete") {
			indexChar = input.substr(7);
			stream << indexChar;
			stream >> indexNum;
			stream.clear();
			lineEditor.deleteNode(indexNum);
		}
		else if (input.substr(0, 6) == "insert") {
			temp = input.find(" ", 7);
			indexChar = input.substr(7, temp - 7);
			stream << indexChar;
			stream >> indexNum;
			stream.clear();
			text = input.substr(temp + 2);
			text.pop_back();
			lineEditor.insertList(indexNum, text);
		}
		else if (input.substr(0, 4) == "edit") {
			temp = input.find(" ", 5);
			indexChar = input.substr(5, temp - 5);
			stream << indexChar;
			stream >> indexNum;
			stream.clear();
			text = input.substr(temp + 2);
			text.pop_back();
			lineEditor.editList(indexNum, text);
		}
		else if (input.substr(0, 6) == "search") {
			text = input.substr(8);
			text.pop_back();
			lineEditor.searchList(text);
		}
	}
    return 0;
}

