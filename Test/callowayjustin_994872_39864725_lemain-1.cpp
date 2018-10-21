#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// dir for running in Ubuntu: /mnt/c/users/justi/source/repos/DSA\ PA1

struct Node {
	string text;
	Node *next;
};

Node* insertAtEnd(Node *&head, string text) {	
	Node *addedNode = new Node();	//new node to be added to the list
	addedNode->text = text;			//set it's data to the inputted text
	addedNode->next = NULL;			//doesn't point to the next node because it will be at the end

	if (head == NULL) {		//if there is no head
		head = addedNode;	//the new node is now the head node
		return head;
	}
	else {
		Node *prev = head;		//track the head as the first node before the node you want to add
		while (prev->next) {	//while the node behind points to another node
			prev = prev->next;	//traverse the list
		}
		prev->next = addedNode;	//when the previous node no longer points to a node, make it point to the node you created
		return head;
	}
}

Node* deleteNode(Node*&head, int index, int length) {
		Node *prev = new Node();	//keep track of previous node
		length = 1;					//keep track of where you are in the list

		if (length == index) {		//if you are trying to delete the head
			Node *temp = head;		//set head to temp node
			head = head->next;		//head is getting deleted, so the new head node is the next node in the list
			delete temp;
			return head;
		}

		Node *current = head;		//keep track of head
		while (length < index && current->next) {	//while you haven't gotten to the right position yet and there is a next node to traverse to
			prev = current;							//traverse the list
			current = current->next;
			length++;								//move your position
		}
		if (length == index) {						//make sure you're in the right spot
			prev->next = current->next;				//skips over the node you're going to delete
			delete current;
			return head;
		}
		else {										//index is OOB
			return head;
		}
	return head;
}

Node* insertNode(Node*&head, int index, string text) {	
	Node* current = head;		//keep track of head
	Node* prev = new Node();	//keep track of previous node
	Node* temp = new Node();	//node that gets inserted
	int length = 1;				//keeps track of your position in the list

	while (length < index && current) {	//while you haven't gotten to the place you want to insert yet
		prev = current;			//traverse list
		current = current->next;
		length++;				//move your position
	}

	if (length == index) {		//check that you actually are where you want to insert
		temp->text = text;		//set temp node's text to input
		prev->next = temp;		//point the previous node to the new node
		temp->next = current;	//temp node points to the next node in the list
		return head;
		}
	else {						//index is OOB
		return head;
	}
}

Node* editNode(Node*&head, int index, string text) {
	int length = 1;								//keeps track of position in list
	Node *current = head;						//start at head

	while (length < index) {					//while you haven't gotten to the node you want to edit
		current = current->next;				//traverse list
		length++;
	}

	if (length == index && current) {			//you're at the correct spot and the node actually exists
		current->text = text;					//set text to the new input text
		return head;
	}
	else {
		return head;
	}
}

Node* searchNode(Node*&head, string text) {
	int length = 1;												//keep track of position in list
	Node *current = head;
	bool print = false;											//makes sure that something was found when searched for

	while (current) {	
		if (current->text.find(text) != string::npos) {			//if anything in the node's text matches the input
			cout << length << " " << current->text << endl;		//print line number and text
			print = true;										//we've found something, set to true
			current = current->next;							//go to next node
			length++;
		}
		else {
			current = current->next;							//you didn't find anything in that node, traverse
			length++;
			continue;
		}
	}

	if (!print) {						//if nothing was ever printed...
		cout << "not found" << endl;	//the text is nowhere in the list
	}
	return head;
}

int main() {
	Node *head = NULL;	//head node
	int length;			//where you currently are in the list
	int index;			//where you want to insert/delete/edit
	char convert;		//to convert the given index into an int
	int printLength;	//keeps track of what line the printing is on
	string input;		//input line
	char q = '\"';		//for taking out the second quotation marking
	int delim;			//takes index of where second quote was found

	while (true) {

		getline(cin, input);	//for getting input

		if (!(input.find("insertEnd") == string::npos)) {	//if command is "insertEnd"
			input = input.substr(11, input.length());		//cuts input down to text
			delim = input.find(q);							//for eliminating quote
			input = input.substr(0, delim);					//now just text with no quotes
			if (input.length() > 80) {
				continue;
			}
			insertAtEnd(head, input);
		}

		else if (!(input.find("edit") == string::npos)) {		
			convert = input[5];								//takes the number from the command
			index = (int)convert;							//cast string to int, in ASCII
			index = index - 48;								//convert from ASCII to regular decimal
			input = input.substr(8, input.length());
			delim = input.find(q);
			input = input.substr(0, delim);
			if (input.length() > 80) {
				continue;
			}
			editNode(head, index, input);
		}

		else if (!(input.find("insert") == string::npos)) {	
			convert = input[7];
			index = (int)convert;
			index = index - 48;
			input = input.substr(10, input.length());
			delim = input.find(q);
			input = input.substr(0, delim);
			if (input.length() > 80) {
				continue;
			}
			insertNode(head, index, input);
		}

		else if (!(input.find("search") == string::npos)) {
			input = input.substr(8, input.length());
			delim = input.find(q);
			input = input.substr(0, delim);
			if (input.length() > 80) {
				continue;
			}
			searchNode(head, input);

		}

		else if (!(input.find("delete") == string::npos)) {	
			length = 0;
			convert = input[7]; 
			index = (int)convert;	
			index = index - 48;
			deleteNode(head, index, length);
		}

		else if (!(input.find("print") == string::npos)) {	
			Node *current = head;										//starts at the beginning of the list
			printLength = 1;											//start at line 1
			while (current != NULL) {
				cout << printLength << " " << current->text << endl;	//prints text of node with line number
				current = current->next;								//go to next node
				printLength++;											//increment line number
			}
		}

		else if (!(input.find("quit") == string::npos)) {
			exit(0);
		}

		else {
			continue;
		}
	}
	return 0;
}