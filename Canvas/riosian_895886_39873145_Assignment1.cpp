
// Ian Rios
// COP 3530
// Assignment #1
// 9/21/18
#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#define end1 "\n"

// Create List Class
class list {
	// Create Node Class
	class Node {
	public:
		int loc = 1;
		Node* next = NULL;
		char line[80] = "";

		void addLine(char * newLine) {
			// Define Char array with pointer
			strcpy_s(line, newLine);
		}
	};
	// Create Default Nodes for the list
private:
	Node *head;
	Node *tail;
public:
	list() {
		head = NULL;	// Point to NULL
		tail = NULL;
	}
	/* Add to the End of the list */
	void insertEnd(char * line) {																						// WORKS
		Node * temp = new Node;
		/* Point to NULL */
		temp->next = NULL;
		temp->addLine(line);
		if (head == NULL) {
			/* Update Pointer */
			head = temp;
			tail = temp;
		}
		else {
			//std::cout << "Tail value" << end1 << tail->loc << end1;
			temp->loc = tail->loc;
			//std::cout << "Temp String" << end1 << temp->line << end1;
			//std::cout << "Temp Loc value" << end1 << temp->loc << end1;
			tail->next = temp;		// Point to the new Tail
			tail = temp;			// Point tail to new last Node
			tail->loc++;			// Increment Loc
		}
	}
	/* Insert anywhere in the list */
	void insert(int loc, char * line) {																					// WORKS
		Node * traveler = head;			// Traveling Node
		/* Edge case insterting at the beggining */
		if (loc == 1) {
			Node * newHead =  new Node;
			/* Point to previous head of list */
			newHead->next = head;
			newHead->addLine(line);		// Add String to new Node
			head = newHead;
			/* Update loc value for the next Nodes */
			traveler = head->next;		// Location its default 1, so point to next node
			do {
				//traveler->loc++;			// Increment the rest of the locations
				traveler = traveler->next;	// Iterate to the next Node
			} while (traveler != NULL);
			return;
		}
		/* Iterate in the list until we find desired location */
		Node * prev = traveler;
		while (traveler != NULL) {
			// [1]->[2]->[3]    Instert 2
			// [1]->[2]->[3]->[4]
			if (traveler->loc == loc) {
				/* Create Node and declare values to be inserted */
				Node * insertMe = new Node;
				insertMe->loc = loc;
				insertMe->addLine(line);
				insertMe->next = traveler;
				prev->next = insertMe;
				break;
			}
			prev = traveler;
			traveler = traveler->next;	// Iterate to the next Node
		} 
		if (traveler == NULL) {
			std::cout << end1 << "ERROR: Location is out of bounds" << end1;
			return;
		}
		/* Increment the remaining locations of the list*/
		do {
			traveler->loc++;									// Increment the rest of the locations
			if (traveler->next == NULL) tail = traveler;		// Update Tail pointer
			traveler = traveler->next;							// Iterate to the next Node

			
		} while (traveler != NULL);
		//std::cout << "This is where we stopped : " <<traveler->loc << end1;
		//std::cout << "This is where Prev stopped : " << prev->loc << end1;
	}
	/*  Delete any line within the list */
	void deleteEntry(int loc) {																						// WORKS	
		Node * traveler = head;		// Traveling Node
		if (head == NULL) {
			std::cout << end1 << "ERROR: Cannot delete list is empty" << end1;
			return;
		}
		/* [1]->[2]->[3]->[4]  Delete 2
		   [1]->[2]->[3] */
		/* Edge case insterting at the beggining */
		if (loc == 1) {
			/* Point to new head of list */
			head = head->next;
			// If there is are no more items return
			if (head == NULL) return;
			traveler = head;
			do {
				traveler->loc--;			// Decrement the rest of the locations
				traveler = traveler->next;	// Iterate to the next Node
			} while (traveler != NULL);
			return;
		}
		/* Instert in the list until we find desired location */
		Node * prev = traveler;
		while (traveler != NULL) {
			if (traveler->loc == loc) {
				/* Edge case : Deleting last node*/
				if (traveler = tail) {
					tail = prev;		// Update Tail pointer
					prev->next = NULL;	// Delete Node
					return;
				}
				// Delete Node
				prev->next = traveler->next;
				break;
			}
			prev = traveler;
			traveler = traveler->next;	// Iterate to the next Node
		}
		if (head == NULL) return;
		if (traveler == NULL) {
			std::cout << end1 << "ERROR: Location is out of bounds" << end1;
			return;
		}
		traveler = prev->next;
		do {
			traveler->loc--;			// Decrement the rest of the locations
			traveler = traveler->next;	// Iterate to the next Node
		} while (traveler != NULL);
	}
	/* Print entire list */
	void print(void) {																								// WORKS																					
		std::cout << end1 << "---------" << end1;
		/* Traverse Entire List */
		Node * traveler = head;
		do {
			std::cout << end1 << traveler->loc << " " << traveler->line << end1;
			traveler = traveler->next;
		} while (traveler != NULL);
	}
	void edit(int loc, char * line) {																				// WORKS
		Node * traveler = head;
		while (traveler != NULL) {
			// Iterate and compare locations
			if (traveler->loc == loc) {
				// Edit line and return
				traveler->addLine(line);
				return;
			}
			traveler = traveler->next;
		}
		std::cout << end1 << "ERROR: Location Not Found, try a different value" << end1;
	}
	/* Search, print line number and the line that contains the given text */
	void search(char * line) {																						// WORKS
		Node * searcher = head;
		char cmpMe[80];
		strcpy_s(cmpMe,line);
		while (searcher != NULL) {
			// Iterate and compare strings
			if (strncmp(searcher->line, line, strlen(cmpMe)) == 0) {
				std::cout << searcher->loc << " " << searcher->line << end1;
				return;
			}
			searcher = searcher->next;
		}
		std::cout << end1 << "ERROR: Search Not Found!!" << end1;
	}
};



int main()
{
	// Create List Class
	list myList;
	char input[80] = "Here we go";
	char input1[80] = "It really works";
	char * ptr = &input[0];
	myList.deleteEntry(1);
	myList.insertEnd(ptr);
	ptr = &input1[0];
	myList.insertEnd(ptr);
	ptr = (char*) "Yolo" ;
	//myList.insert(2, ptr);
	myList.insertEnd(ptr);
	myList.print();
	ptr = (char*) "It really do be like that";
	myList.edit(4, ptr);
	myList.print();
	//myList.search(ptr);
	//ptr = (char*) "BOFA";
	myList.insert(3, ptr);
	myList.print();
	myList.deleteEntry(5);
	myList.print();
	//ptr = (char*) "wtf why??";
	//myList.insert(4, ptr);
	//myList.print();
	}




