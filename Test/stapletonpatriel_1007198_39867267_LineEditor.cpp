// LineEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//your linked list implementation here
template <class T>
class LinkedList {
	struct Node {
		T data;
		Node* next = nullptr;
		Node* previous = nullptr;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

public:
	void Insert(T data) {
		Node* newNode = new Node();
		newNode->data = data;

		if (head != nullptr) {
			//Add to end
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
			count++;
		}
		else {
			//Add first node
			head = newNode;
			tail = head;
		}
	}

	void InsertAt(int index, T data) {
		int counter = 1;
		Node* tracer = head->next;
		Node* newNode = new Node();
		newNode->data = data;

		if (index == 0) {
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
			count++;
		}
		else if (index > (count + 1)) {
			return;
		}
		else if (index == (count + 1)) {
			Insert(data);
		}
		else {
			while (tracer != nullptr) {
				if (counter == index) {
					newNode->previous = tracer->previous;
					newNode->next = tracer;
					tracer->previous->next = newNode;
					tracer->previous = newNode;
					count++;
					return;
				}
				counter++;
				tracer = tracer->next;
			}
		}
	}

	void EditAt(int index, T data) {
		int counter = 0;
		Node* tracer = head;
		while (tracer != nullptr) {
			if (index == counter) {
				tracer->data = data;
			}
			counter++;
			tracer = tracer->next;
		}
	}

	void Print() {
		Node* tracer = head;
		while (tracer != nullptr) {
			cout << tracer->data << endl;
			tracer = tracer->next;
		}
	}

	void Remove(int index) {
		Node* tracer = head;
		int counter = 0;
		while (tracer != nullptr) {
			if (index == counter) {
				if (index == 0) {
					head = head->next;
					tracer = head->previous;
					delete tracer;
					head->previous = nullptr;
				}
				else if (index == count) {
					tail = tail->previous;
					tracer = tail->next;
					delete tracer;
					tail->next = nullptr;
				}
				else {
					tracer->previous->next = tracer->next;
					tracer->next->previous = tracer->previous;
					delete tracer;
				}
				count--;
				return;
			}
			tracer = tracer->next;
			counter++;
		}
	}

	Node* headNode() {
		return head;
	}

	Node* TailNode() {
		return tail;
	}

	int TotalCount() {
		return count;
	}

};

//your line editor implementation here

class LineEditor {
	LinkedList<string> list;
public:
	void ProcessInput() {
		string line, command, rest;
		while (getline(cin, line)) {
			command = "";
			rest = "";
			istringstream lineStream(line);
			getline(lineStream, command, ' ');
			getline(lineStream, rest);
			if (command.compare("quit") == 0) {
				return;
			}
			else {
				ProcessCommand(command, rest);
			}
		}
	}

	void ProcessCommand(string command, string text) {

		if (command.compare("insertEnd") == 0) {
			text = Trim(text);
			if (text.length() > 80)
				return;
			list.Insert(text);
		}
		else if (command.compare("insert") == 0) {

			string integer;
			istringstream lineStream(text);
			getline(lineStream, integer, ' ');
			int index = stoi(integer);
			getline(lineStream, text);
			text = Trim(text);
			if (text.length() > 80)
				return;
			list.InsertAt(index - 1, text);

		}
		else if (command.compare("edit") == 0) {

			string integer;
			istringstream lineStream(text);
			getline(lineStream, integer, ' ');
			int index = stoi(integer);
			getline(lineStream, text);
			text = Trim(text);
			if (text.length() > 80)
				return;
			list.EditAt(index - 1, text);

		}
		else if (command.compare("print") == 0) {
			Print();
		}
		else if (command.compare("search") == 0) {
			text = Trim(text);
			Search(text);
		}
		else if (command.compare("delete") == 0) {
			string integer;
			istringstream lineStream(text);
			getline(lineStream, integer, ' ');
			int index = stoi(integer);
			list.Remove(index - 1);
		}

	}

	void Print() {
		auto tracer = list.headNode();
		int counter = 1;
		while (tracer != nullptr) {
			cout << counter << " " << tracer->data << endl;
			tracer = tracer->next;
			counter++;
		}
	}

	void Search(string term) {
		int counter = 1;
		bool discover = false;
		vector<string> result;
		auto tracer = list.headNode();
		while (tracer != nullptr) {
			size_t found = tracer->data.find(term);
			if (found != string::npos) {
				result.push_back(to_string(counter) + " " + tracer->data);
				discover = true;
			}
			tracer = tracer->next;
			counter++;
		}
		if (discover) {
			for (string x : result)
				cout << x << endl;
		}
		else {
			cout << "not found" << endl;
		}
	}


	string Trim(string text) {
		string trimmed;
		istringstream lineStream(text);
		getline(lineStream, trimmed, '"');
		getline(lineStream, trimmed, '"');
		return trimmed;
	}
};

int main()
{
	LineEditor editor;
	editor.ProcessInput();
	return 0;
}