#include "stdafx.h"
#include<iostream>
#include "LinkedList.h"


LinkedList::LinkedList()
{
	size = 0;
	head = nullptr;
}
LinkedList::~LinkedList()
{}

void LinkedList::insert(string str) {
	size++;
	Node* h = new Node(str);
	if (head==nullptr) {
		this->head = h;
		return;
	}
	Node* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = h;
}
void LinkedList::insert(int n, string str) {
	if (n > size + 1 || n<=0)
		return;
	size++;
	Node* h = new Node(str);
	if (n == 1) {
		if (head == nullptr) {
			head = h;
		}
		else {
			h->next = head;
			head = h;
		}
		return;
	}
	Node* temp = head;
	for (int i = 2; i < n; i++) {
		temp = temp->next;
	}
	h->next = temp->next;
	temp->next = h;
}
void LinkedList::del(int n) {
	if (n <= 0 || n > size) {
		return;
	}
	size--;
	if (n == 1) {
		Node* temp = head->next;
		delete head;
		head = temp;
		return;
	}
	Node* temp = head;
	for (int i = 2; i < n; i++) {
		temp = temp->next;
	}
	Node* s = temp->next;
	temp->next = s->next;
	delete s;
	return;
}
void LinkedList::edit(int n, string str) {
	if (n <= 0 || n > size) {
		return;
	}
	Node* temp = head;
	for (int i = 1; i < n; i++) {
		temp = temp->next;
	}
	temp->line = str;
	return;
}

pair<int, string> LinkedList::search(string str)
{
	Node* temp = head;
	int count = 1;
	while (temp != nullptr) {
		if (temp->line.find(str)!=string::npos) {
			return make_pair(count, temp->line);
		}
		temp = temp->next;
		count++;
	}
	return make_pair(-1, "");
}

void LinkedList::print() {
	if (head==nullptr) {
		return;
	}
	int count = 1;
	Node* temp = head;
	while (temp != nullptr) {
		std::cout << count << " " << temp->line<<std::endl;
		temp = temp->next;
		count++;
	}
	return;
}