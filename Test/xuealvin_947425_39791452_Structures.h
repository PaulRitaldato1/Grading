#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <string>
#include <iostream>
#include <map>

using namespace std;

struct node {

	string line;
	node *next;
};

class linkedList {

private:
	node *head, *tail;

public:
	linkedList() {

		head = nullptr;
		tail = nullptr;

	}

	int getSize() {
		
		int size = 0;
		node* temp = head;
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}

		return size;
	
	}


	void insertEnd(string lineData) {

		node *temp = new node;
		temp->line = lineData;
		temp->next = NULL;

		if (head == NULL) {

			head = temp;
			tail = temp;
			temp = NULL;

		}
		else {
			while (tail->next != NULL) {
				tail = tail->next;
			}
			tail->next = temp;
			tail = temp;

		}


	}

	void insert(int lineNumber, string lineData) {
		node *prev = new node;
		node *curr = new node;
		node *temp = new node;
		curr = head;

		for (int i = 1; i < lineNumber; i++) {
			prev = curr;
			curr = curr->next;
		}

		temp->line = lineData;
		prev->next = temp;
		temp->next = curr;
	}


	void deleteLine(int lineNumber) {

		node *curr = new node;
		node *prev = new node;
		curr = head;

		for (int i = 1; i < lineNumber; i++) {
			prev = curr;
			curr = curr->next;
		}
		prev->next = curr->next;

	}

	void editLine(int lineNumber, string lineData) {

		deleteLine(lineNumber);
		insert(lineNumber, lineData);

	}

	void print() {

		node *temp = new node;
		temp = head;
		int lineNum = 1;

		while (temp != NULL) {

			cout << lineNum << " " << temp->line << "\n";
			temp = temp->next;
			lineNum++;

		}

	}

	void search(string lineData) {

		node* dummy = new node;
		dummy->next = head;
		int lineNum = 1;
		bool exists = false;

		node* curr = dummy;
		while (curr->next != nullptr) {

			if (curr->next->line.find(lineData) != string::npos) {

				cout << lineNum << " " << curr->next->line << "\n";
				curr = curr->next;
				exists = true;
				lineNum++;
				
			}
			else {
				curr = curr->next;
				lineNum++;
			}
		}
		if (!exists) {
			cout << "Not found." << "\n";
		}

	}

};


#endif

