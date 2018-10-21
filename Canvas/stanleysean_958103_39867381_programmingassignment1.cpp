//your linked list implementation here
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std;

struct Node { 
    string value; 
    struct Node* next; 
};
        
//your line editor implementation here
Node* insertEnd(Node *head, string text) {
	Node* last = new Node();			// creates a node to store the last node's value and last->next

    last->value = text;
    last->next = nullptr;			// the end of the list will point to NULL

    if (head == nullptr) {				// sets head = last if the list is empty
        head = last;
	}
	else {
        Node* temp = new Node();			// creates a temp node	
        temp = head;						// points temp to head

        while (temp->next != nullptr) {		// iterates through list to find last node
            temp = temp->next;
        }

        temp->next = last;				// inserts the last node to the list
    }
	
    return head;
}

Node* insert(Node* head, int line, string text) {
    Node* insertLine = new Node();			// creates a new node
    insertLine->value = text;			// and sets its value to the user-inputted text
    
	if (line == 0) {			// if inserting at the beginning of the list,
        insertLine->next = head;			// then insertLine becomes the new head
        return insertLine; 
    }
    
    int i = 0;
    Node* current = head;			// creates a temporary node and sets it to head
    
	while (i < line - 1) {			// loops through the list until the desired line is reached
        current = current->next;			// sets current equal to the next node			
        if (current == nullptr)
            return nullptr;
        i++;
    }
    
    Node* aft = current->next;			// creates a new node and sets it to the node after current
    current->next = insertLine;			// current next is set to the node containing the user-inputted text
    insertLine->next = aft;			// the node after insertLine is set to the node after current's previous value
    
	return head;
}

Node* deleto(Node* head, int line) {
    if (head == nullptr)            // if list is empty return nullptr
        return nullptr; 
		
	Node* currCheck = head;            	
	int listLength = 0;   
    
	while (currCheck != nullptr) {			// loops through the list to find its length
        listLength++; 
        currCheck = currCheck->next; 
    } 	
		
    if (line >= listLength)			// if the user-inputted line number is greater than the length of the list, 
		return head;			// then exist the method
	
	Node* current = head;
	Node* last = head;
	
	if(line == 0) {
		head = current->next;			// if the first value in the list is equal to theValue, 
		current = head;			// set the new head to the next element and make current point to that element
	}
	
	int i = 0;
    while (i < line) {
       last = current;			// increments last by one node
       current = current->next;			// increments current by one node
	   i++;
	}
	
	last->next = current->next;             // stores value of next node in last
    current = last->next;             // points current to the next node
       
    return head;
}

Node* edit(Node* head, int line, string text) {
	if ((line == 0)) {			// if editing the first line, 
		head->value = text;			// edit the value of head and return head
		return head;
	}
	
	int i = 0;
	Node* current = head;			// creates a temporary node and sets it to head
	
	while (i < line) {			// loops through the list until the desired line is reached
		current = current->next;
		if (current == nullptr)
			return nullptr;
		i++;
	}
	
	current->value = text;			// the value of the node at the specified line is edited
	return head;
}
// use print to fix ghost node
void print(Node* head) {
    Node* current = head->next;			// creates a temporary node and sets it to head
    int lineNum = 1;			// starts a counter to keep track of line numbers
	
	while (current != nullptr) {			// loops through the list until the last node 
        cout << lineNum << " " << current->value << endl;			// prints the line number + the line of text in the node for each node in the list 
		current = current->next;			// goes to the next node
		lineNum++;			// increases the line counter by 1
	}
}

void search(Node* head, string text) {
	Node* current = head;			// creates a temporary node and sets it to head
	int lineNum = 0;			// starts a counter to keep track of line numbers
	bool isFound = false;			// boolean to be set to true if the text is found
	
	while (current != nullptr) {			// loops through the list until the last node
		if (current->value.find(text) != -1) {			// if the current node contains the user-inputted text,
			cout << lineNum << " " << current->value << endl;			// then display the line number + the line of text stored in the node
			isFound = true;
		}
		
		current = current->next;			// if the text is not found, go to the next node
		lineNum++;			// and increase the line counter by 1
	}
	
	if (!isFound)
		cout << "not found" << endl;			// prints "not found" if the text is not found in any node in the list
}

int main() {
    //your code to invoke line editor here
	Node* listStart = new Node();
	while (true) {
		int numOp;
		string op = "";
		string textIn = "";
		cin >> op;			// reads the user input 
		getline(cin, textIn);			// extracts characters from cin and stores them in textIn
		textIn.erase(0,1);			// removes the space at the beginning of the string 
		textIn.erase(remove(textIn.begin(), textIn.end(), '\"'), textIn.end());			// removes quotation marks
		
		if (op == "quit") {			// exits program if the user inputs "quit"
			return 0;
		}
		else if (op == "insertEnd") {
			insertEnd(listStart, textIn);
		}
		else if (op == "insert") {
			istringstream stream(textIn);
			stream >> numOp;			// stores the number in numOp
			textIn.erase(0,2);			// removes the number from textIn
			insert(listStart, numOp, textIn);
		}
		else if (op == "delete") {
			istringstream stream(textIn);
			stream >> numOp;			// stores the number in numOp
			textIn.erase(0,2);			// removes the number from textIn
			deleto(listStart, numOp);
		}
		else if (op == "edit") {
			istringstream stream(textIn);
			stream >> numOp;			// stores the number in numOp
			textIn.erase(0,2);			// removes the number from textIn
			edit(listStart, numOp, textIn);
		}
		else if (op == "print") {
			print(listStart);
		}
		else if (op == "search") {
			search(listStart, textIn);
		}
	}
}