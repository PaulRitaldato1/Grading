// lineEditor_sub.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include<string>
using namespace std;

template<typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node *next = nullptr;
		Node *prev = nullptr;
	};
	//Constructors and Destructors
	LinkedList();
	LinkedList(const LinkedList<T> &list);
	~LinkedList();
	//Accessors
	void PrintForward() const;
	void PrintReverse() const;
	unsigned int NodeCount() const;
	void FindAll(vector<Node *> &outData, const T&value) const;
	const Node *Find(const T &value) const;
	Node *Find(const T &value);
	const Node * GetNode(unsigned int index) const;
	Node * GetNode(unsigned int index);
	Node *Head();
	const Node *Head() const;
	Node *Tail();
	const Node *Tail() const;
	void search(const string &value);
	//Insertion
	void AddHead(const T &value);
	void AddTail(const T &value);
	void AddNodesHead(T *value, unsigned int count);
	void AddNodesTail(T *value, unsigned int count);
	void InsertAfter(Node *n, const T &data);
	void InsertBefore(Node *n, const T &value);
	void InsertAt(const T &data, unsigned int index);
	//Removers
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T &value);
	bool RemoveAt(int index);
	void Clear();
	//Operators
	const T & operator[](unsigned int index) const;
	T & operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T> &operator=(const LinkedList<T> &rhs);
private:
	Node * head, *tail;
	int nodeCount;
};

//Constructors
template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {
}
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
	if (list.head == nullptr) {
		head = nullptr;
		tail = nullptr;
		nodeCount = 0;
	}
	else {
		Node *currentNode = list.head;
		head = nullptr;
		while (currentNode != nullptr) {
			this->AddTail(currentNode->data);
			currentNode = currentNode->next;
		}
	}
}
template<typename T>
LinkedList<T>::~LinkedList() {
	this->Clear();
}
//Operators
template<typename T>
const T & LinkedList<T>::operator[](unsigned int index) const {
	Node *current = head;
	unsigned int count = 0;
	while (count < index) {
		if (current->next == nullptr) {
			throw(out_of_range("Index out of bounds"));
		}
		else {
			current = current->next;
			count += 1;
		}
	}
	return current->data;
}
template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
	Node *current = head;
	unsigned int count = 0;
	while (count < index) {
		if (current->next == nullptr) {
			throw(out_of_range("Index out of bounds"));
		}
		else {
			current = current->next;
			count += 1;
		}
	}
	return current->data;
}
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
	Node *current = head;
	Node *current2 = rhs.head;
	if (nodeCount != rhs.nodeCount) {
		return false;
	}
	for (int i = 0; i < nodeCount; i++) {
		if (current->data != current2->data) {
			return false;
		}
		current = current->next;
		current2 = current2->next;
	}
	return true;
}
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
	if (this != &rhs) {
		nodeCount = rhs.nodeCount;
		LinkedList<T> temp(rhs);
		swap(temp.head, head);
		swap(temp.tail, tail);
		return *this;
	}
	return *this;
}
//Accessors
template<typename T> //used in line editor
void LinkedList<T>::PrintForward() const {
	int count = 1;
	Node *current = head;
	while (current != nullptr) {
		cout << count << current->data << endl;
		count++;
		current = current->next;
	}
}
template<typename T>
void LinkedList<T>::PrintReverse() const {
	Node *current = tail;
	while (current != nullptr) {
		cout << current->data << endl;
		current = current->prev;
	}
}
template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return (unsigned)nodeCount;
}
template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T&value) const {
	Node *current = head;
	while (current != nullptr) {
		if (current->data == value) {
			outData.push_back(current);
			current = current->next;
			continue;
		}
		current = current->next;
	}
}
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &value) const {
	Node *current = head;
	while (current != nullptr) {
		if (current->data == value) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &value) {
	Node *current = head;
	while (current != nullptr) {
		if (current->data == value) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
template<> //used in line editor
void LinkedList<string>::search(const string &value) {
	int found = 0;
	int count = 1;
	Node *current = head;
	unsigned int dif;
	while (current != nullptr) {
		dif = current->data.size() - value.size();
		if (dif < 0) {
			count += 1;
			current = current->next;
			continue;
		}
		else {
			for (unsigned int i = 0; i <= dif; i++) {
				if (current->data.compare(i, value.size(), value) == 0) {
					//cout << current->data.substr(i, value.size()) << "=" << value << endl;
					cout << count << current->data << endl;
					found += 1;
				}
			}
			count += 1;
			current = current->next;
		}
	}
	if (found == 0) {
		cout << "not found\n";
	}
}
template<typename T>
const typename LinkedList<T>::Node * LinkedList<T>::GetNode(unsigned int index) const {
	Node *current = head;
	unsigned int count = 0;
	while (count < index) {
		if (current->next == nullptr) {
			throw(out_of_range("Index out of bounds"));
		}
		else {
			current = current->next;
			count += 1;
		}
	}
	return current;
}
template<typename T>
typename LinkedList<T>::Node * LinkedList<T>::GetNode(unsigned int index) {
	Node *current = head;
	unsigned int count = 0;
	while (count < index) {
		if (current->next == nullptr) {
			throw(out_of_range("Index out of bounds"));
		}
		else {
			current = current->next;
			count += 1;
		}
	}
	return current;
}
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
	return head;
}
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const {
	return head;
}
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
	return tail;
}
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const {
	return tail;
}
//Insertions
template<typename T>
void LinkedList<T>::AddHead(const T &value) {
	Node *n = new Node;
	n->data = value;
	if (head == nullptr) {
		n->data = value;
		n->prev = nullptr;
		n->next = nullptr;
		head = n;
		tail = n;
	}
	else {
		n->prev = nullptr;
		n->next = head;
		head->prev = n;
		head = n;
	}
	nodeCount += 1;
}
template<typename T> //used in line editor
void LinkedList<T>::AddTail(const T &value) {
	Node *n = new Node;
	n->data = value;
	if (head == nullptr) {
		n->prev = nullptr;
		n->next = nullptr;
		head = n;
		tail = n;
	}
	else {
		n->prev = tail;
		n->next = nullptr;
		tail->next = n;
		tail = n;
	}
	nodeCount += 1;
}
template<typename T>
void LinkedList<T>::AddNodesHead(T *value, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		this->AddHead(*(value + (count - 1 - i)));
	}
	nodeCount += count;
}
template<typename T>
void LinkedList<T>::AddNodesTail(T *value, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		this->AddTail(*(value + i));
	}
	nodeCount += count;
}
template<typename T>
void LinkedList<T>::InsertAfter(Node *n, const T &value) {
	Node *newNode = new Node;
	newNode->data = value;
	newNode->next = n->next;
	newNode->prev = n;
	n->next->prev = newNode;
	n->next = newNode;
}
template<typename T> //used in line editor
void LinkedList<T>::InsertBefore(Node *n, const T &value) {
	Node *newNode = new Node;
	newNode->data = value;
	newNode->next = n;
	newNode->prev = n->prev;
	n->prev->next = newNode;
	n->prev = newNode;
}
template<typename T> // used in line editor
void LinkedList<T>::InsertAt(const T &value, unsigned int index) {
	if (index > (unsigned)(nodeCount)) {
		return;
		//throw(out_of_range("Index out of bounds"));
	}
	if (index == (unsigned)0) {
		this->AddHead(value);
	}
	else if (index == (unsigned)(nodeCount)) {
		this->AddTail(value);
	}
	else {
		Node *indexNode = head;
		for (unsigned int i = 0; i < index; i++) {
			indexNode = indexNode->next;
		}
		this->InsertBefore(indexNode, value);
		nodeCount += 1;
	}
}
//Removal
template<typename T>
bool LinkedList<T>::RemoveHead() {
	if (head == nullptr) {
		return false;
	}
	else if (head == tail) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node *n = head;
		head = head->next;
		head->prev = nullptr;
		delete n;
	}
	nodeCount -= 1;
	return true;
}
template<typename T>
bool LinkedList<T>::RemoveTail() {
	if (tail == nullptr) {
		return false;
	}
	else if (head == tail) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node *n = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete n;
	}
	nodeCount -= 1;
	return true;
}
template<typename T>
unsigned int LinkedList<T>::Remove(const T &value) {
	Node *current = head;
	Node *garbage;
	unsigned int count = 0;
	while (current != nullptr) {
		if (current->data == value) {
			garbage = current;
			current = current->next;
			garbage->prev->next = garbage->next;
			garbage->next->prev = garbage->prev;
			delete garbage;
			nodeCount -= 1;
			count += 1;
			continue;
		}
		current = current->next;
	}
	return count;
}
template<typename T> //Used in line editor
bool LinkedList<T>::RemoveAt(int index) {
	if (index == 0) {
		this->RemoveHead();
		return true;
	}
	else if (index == nodeCount - 1) {
		this->RemoveTail();
		return true;
	}
	if (index > nodeCount - 1) {
		return false;
	}
	Node *current = head;
	Node *garbage;
	int count = 0;
	while (count != index) {
		count += 1;
		current = current->next;
	}
	garbage = current;
	current = current->next;
	garbage->prev->next = garbage->next;
	garbage->next->prev = garbage->prev;
	delete garbage;
	nodeCount -= 1;
	return true;
}
template<typename T>
void LinkedList<T>::Clear() {
	while (this->RemoveHead()) {}
}

//your line editor implementation here

int main()
{
	//your code to invoke line editor here
	string input;
	LinkedList<string> doc;
	while (input != "quit") {
		cin >> input;
		if (input == "insertEnd") {
			string line;
			getline(cin, line);
			line.erase(1, 1);
			line.erase(line.size() - 1, 1);
			doc.AddTail(line);
		}
		else if (input == "insert") {
			int index;
			cin >> index;
			string line;
			getline(cin, line);
			line.erase(1, 1);
			line.erase(line.size() - 1, 1);
			doc.InsertAt(line, index - 1);
		}
		else if (input == "delete") {
			int index;
			cin >> index;
			doc.RemoveAt(index - 1);
		}
		else if (input == "edit") {
			int index;
			cin >> index;
			string line;
			getline(cin, line);
			line.erase(1, 1);
			line.erase(line.size() - 1, 1);
			doc.RemoveAt(index - 1);
			doc.InsertAt(line, index - 1);
		}
		else if (input == "print") {
			doc.PrintForward();
		}
		else if (input == "search") {
			string text;
			getline(cin, text);
			text.erase(1, 1);
			text.erase(text.size() - 1, 1);
			doc.search(text);
		}
	}
	return 0;
}
