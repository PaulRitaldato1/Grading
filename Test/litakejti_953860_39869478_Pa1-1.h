/*
Author: Kejti Lita
UFID: 9455-0140
Date: 09/21/2018
Class: COP3530
Description: A line editor that implements a linked list
				to insert, delete, search, edit or print the lines.
				The linked list class for the line edditor.
*/
#include <iostream>
#include <cstdlib>

using namespace std;

class Node
{
public:
	Node* next;
	string data;
};

using namespace std;

class LinkedList
{
public:
	int length;
	Node* head;

	LinkedList();
	void add(string line, int position);
	void deleteNode(int position);
	void edit(string line, int position);
	void search(string line);
	void print();
	
};

LinkedList::LinkedList() {
	this->length = 0;
	this->head = NULL;
}

void LinkedList::add(string line, int position) {
	/**
	Adds nodes to a linked list given a position.

	@param line: The string we want to add.
	@param position: position where we want to add the string.
	@return void

	*/
	Node* curr = new Node();
	Node* temp = new Node();
	Node* help = new Node();
	int index = 1;
	temp->data = line;
	help = curr;


	if (this->head == NULL && position == 1) {
		curr->next = this->head;
		this->head = temp;
	}
	else {
		curr = this->head;
		if (position != 0) {
			if (position == 1) {
				temp->next = this->head;
				this->head = temp;
			}
			else {
				while (curr->next != NULL) {
					if (position == index) {
						break;
					}
					help = curr;
					curr = curr->next;
					index = index + 1;
				}
				
				if (curr->next==NULL && position == index +1 ) {
					curr->next = temp;
					temp->next = NULL;
				}
				else if (position == index){
					help->next = temp;
					temp->next = curr;
				}
			}
		}
		else {
			if (this->head == NULL) {
				temp->next = this->head;
				this->head = temp;
			}
			else {
				while (curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = temp;
				temp->next = NULL;
			}
		}
	}

}

void::LinkedList::deleteNode(int position) {
	/**
	Deletes a node from the linked list at a specific position.

	@param postiion:  the position of the node to be deleted.
	@return void
	*/

	Node* curr = new Node();
	Node* temp = new Node();
	curr = this->head;
	int index = 1;

	if (position == 1) { //if deleting head
		this->head = this->head->next;
	}
	else { //if not deleting head
		bool found = false;
		while (curr->next != NULL) {
			if (index == position) {//break if found position
				found = true;
				break;
			}
			else {
				index = index + 1;
				temp = curr;
				curr = curr->next;
			}
		}

		if (found == true ) {
			temp->next = curr->next;
			delete curr;
		}
		else {
			if (position == index && curr->next == NULL) { //if deletion was for the end.
				temp->next = NULL;
				delete curr;
			}
		}

	}

}
void::LinkedList::edit(string line, int position) {
	/**
	Edits a line in a lined list given the new line and the postition.
	
	@param line: The new string that is going to replace the current one.
	@param position: position of the node to be edited
	@return void
	
	*/
	Node* curr = new Node();
	int index = 1;
	if (position == 1) {//if we want to edit head
		this->head->data = line;
	}
	else {
		curr = this->head;
		while (position != index) {
			if (curr->next != NULL) {
				curr = curr->next;
				index = index + 1;
			}
		}
		curr->data = line;
	}
	
}
void::LinkedList::search(string line) {
	/**
	Searches for a specific string in the list and prints out the position and the node containing it.

	@param line: The string the user wants to search for.
	@return void

	*/
	int index = 1;
	bool found = false;
	Node* curr = new Node();
	curr = this->head;
	
	while (curr->next != NULL) {//Searching till the end of the list
		if (curr->data.find(line) != string::npos) {
			cout << index << " " << curr->data << endl;
			found = true;
		}
		index = index + 1;
		curr = curr->next;
	}
	if (curr->data.find(line) != string::npos && curr->next == NULL) {//checking for the end of the list
		cout << index << " " << curr->data << endl;
		found = true;
	}
	if (found == false) {
		cout << "not found" << endl;
	}

}
void LinkedList::print() {
	/**
	Prints the linked list

	@return void

	*/
	Node* head = this->head;
	int i = 1;
	while (head != NULL) {
		std::cout << i <<" "<< head->data << std::endl;
		head = head->next;
		i++;
	}
}
#pragma once

