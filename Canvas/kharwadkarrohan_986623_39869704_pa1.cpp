#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
using namespace std;

struct node {
	string data;
	node* next;
};

class list {
private:
	node* head;
	node* curr;

public:
	list() {
		head = NULL;
		curr = NULL;
	}

	void addToEnd(string text);
	void print();
	void insert(string text, int position);
	void deleteLine(int position);
	void edit(string text, int position);
	void search(string text);
};

//function to add to the end of the linked list
void list::addToEnd(string text) {
	//node to be added to the linked list
	node* toAdd = new node;
	toAdd->next = NULL;
	toAdd->data = text;

	if (head != NULL) {
		curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = toAdd;
	}

	//if the linked list is empty then the head becomes new node
	else {
		head = toAdd;
	}
}

//function to print the linked list with line numbers
void list::print() {
	//if the linked list is empty
	if (head == NULL) {
		cout << "Can't print an empty list" << endl;
		return;
	}

	int lineCount = 1;
	curr = head;

	//prints the linked list along with the line number
	while (curr->next != NULL) {
		cout << lineCount << " " << curr->data << endl;
		curr = curr->next;
		lineCount++;
	}
	//prints the last node of the list
	cout << lineCount << " " << curr->data << endl;
}

//function to insert a node into a given position in the linked list
void list::insert(string text, int position) {
	//node to be added to the linked list
	node* toAdd = new node;
	toAdd->next = NULL;
	toAdd->data = text;

	if (head != NULL) {
		int lineCount = 1;
		curr = head;

		//counts the number of nodes in the linked list
		while (curr->next != NULL) {
			curr = curr->next;
			lineCount++;
		}

		//if the given position is greater than one more than the max size of the linked list the function returns
		if (position > (lineCount + 1)) {
			return;
		}

		curr = head;
		int count = 1;

		//if the linked list is empty then the new node is made the head
		if (position == 1) {
			toAdd->next = head;
			head = toAdd;
			return;
		}

		//inserts node at the given position
		else if (position > 1) {
			while (count < position - 1) {
				curr = curr->next;
				count++;
			}

			toAdd->next = curr->next;
			curr->next = toAdd;
		}

		//adds node to the end of the linked list
		else if (position == (lineCount + 1)) {
			addToEnd(text);
		}
	}

	else {
		head = toAdd;
	}
}

//function to delete a given node from the linked list
void list::deleteLine(int position) {

	curr = head;
	int lineCount = 1;

	//counts the number of nodes in the linked list
	while (curr->next != NULL) {
		curr = curr->next;
		lineCount++;
	}

	//if the given position is greater than one more than the max size of the linked list the function returns
	if (position > lineCount) {
		return;
	}

	curr = head;
	int count = 1;

	//if the head is to be deleted then the node after the head is set to be the new head
	if (position == 1) {
		head = head->next;
	}

	//sets the curr node pointer to one node before the node that is to be deleted
	while (count < position - 1) {
		curr = curr->next;
		count++;
	}

	//the node that is to be deleted is unlinked from the linked list
	curr->next = curr->next->next;
}

//function to edit the value of a specified node
void list::edit(string text, int position) {

	curr = head;
	int count = 1;

	//if the head is to be edited then the head's data is set to the given data
	if (position == 1) {
		head->data = text;
	}

	//curr node pointer is moved to the node that is to be edited
	while (count < position) {
		curr = curr->next;
		count++;
	}
	//the data of the specified node is set to the given data
	curr->data = text;
}

//function to find the line number and data of a node based on a text input
void list::search(string text) {

	curr = head;
	int count = 1;

	//boolean to keep track of whether or not a result has been found
	bool found = false;

	while (curr != NULL) {
		//the .find() function returns -1 if the data is not found, if it is found then it is not equal to string::npos
		if ((curr->data).find(text) != string::npos) {
			cout << count << " " << curr->data << endl;
			found = true;
		}


		curr = curr->next;
		count++;
	}

	//if the node is not found then "not found" is printed
	if (!found) {
		cout << "not found" << endl;
	}
}

int main() {

	list docx;

	//this string stores user input
	string userInput = "";
	//this boolean is set to false once the user inputs "quit", breaking the while loop
	bool inputCondition = true;

	while (inputCondition) {
		//getline() function saves the user input into the userInput variable
		getline(cin, userInput);

		//for loop to go through the user input and remove any extra spaces
		for (int i = 0; i < userInput.length(); i++) {
			if (userInput[i] == '\"') {
				break;
			}

			else if (userInput[i] == ' ' && userInput[i + 1] == ' ') {
				userInput.erase(i, 1);
				i--;
			}
		}

		//if the user inputs "insertEnd" then this if statement is entered 
		if (userInput.substr(0, 9) == "insertEnd") {
			//the "insertEnd" is removed from the user input
			userInput = userInput.substr(11, userInput.length() - 2);
			//the message to be inserted is extracted from the user input
			string message = userInput.substr(0, userInput.length() - 1);
			//the message is added to the end of the linked list
			docx.addToEnd(message);
		}

		//if the user inputs "insert" then this if statement is entered
		//searches for "insert " to ensure that it isn't just the first six characters of "insertEnd"
		else if (userInput.substr(0, 7) == "insert ") {
			//the line number is saved into this string
			string sline = "";

			//a single digit number will be a digit followed by a character that is not a digit
			if (isdigit(userInput[7]) && !(isdigit(userInput[8]))) {
				//single digit number is saved into this string
				sline = userInput.substr(7, 1);
				//converted to an int
				int singleLine = std::stoi(sline);
				userInput = userInput.substr(10, userInput.length() - 2);
				//message extracted from user input
				string message = userInput.substr(0, userInput.length() - 1);
				//added to the required position of the linked list
				docx.insert(message, singleLine);
			}

			//for two digit numbers
			else if (isdigit(userInput[7]) && isdigit(userInput[8])) {
				//first digit saved
				sline += userInput[7];
				//second digit saved
				sline += userInput[8];
				int doubleLine = std::stoi(sline);
				userInput = userInput.substr(11, userInput.length() - 2);
				string message = userInput.substr(0, userInput.length() - 1);
				docx.insert(message, doubleLine);
			}
		}

		//if the user inputs delete
		else if (userInput.substr(0, 6) == "delete") {
			string sline = "";
			//single digit
			if (isdigit(userInput[7]) && !(isdigit(userInput[8]))) {
				sline = userInput.substr(7, 1);
				int singleLine = std::stoi(sline);
				docx.deleteLine(singleLine);
			}

			//double digit
			else if (isdigit(userInput[7]) && isdigit(userInput[8])) {
				sline += userInput[7];
				sline += userInput[8];
				int doubleLine = std::stoi(sline);
				docx.deleteLine(doubleLine);
			}
		}

		//if the user inputs edit
		else if (userInput.substr(0, 4) == "edit") {

			string sline = "";
			//single digit
			if (isdigit(userInput[5]) && !(isdigit(userInput[6]))) {
				sline = userInput.substr(5, 1);
				int singleLine = std::stoi(sline);
				userInput = userInput.substr(8, userInput.length() - 2);
				string message = userInput.substr(0, userInput.length() - 1);
				docx.edit(message, singleLine);
			}

			//double digit
			else if (isdigit(userInput[5]) && isdigit(userInput[6])) {
				sline += userInput[5];
				sline += userInput[6];
				int doubleLine = std::stoi(sline);
				userInput = userInput.substr(9, userInput.length() - 2);
				string message = userInput.substr(0, userInput.length() - 1);
				docx.insert(message, doubleLine);
			}
		}

		//if user inputs search
		else if (userInput.substr(0, 6) == "search") {
			userInput = userInput.substr(8, userInput.length() - 2);
			string message = userInput.substr(0, userInput.length() - 1);
			docx.search(message);
		}

		//if user inputs print
		else if (userInput.substr(0, 5) == "print") {
			docx.print();
		}

		//if user inputs quit
		else if (userInput.substr(0, 4) == "quit") {
			inputCondition = false;
			return 0;
		}

		//if user inputs an invalid command
		else {
			cout << "Invalid input. Please try again." << endl;
		}
	}
	return 0;
}