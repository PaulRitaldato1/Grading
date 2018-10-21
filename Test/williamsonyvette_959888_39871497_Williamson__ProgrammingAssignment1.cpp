//Programming Assignment 1 - Implement a Line Editor using Linked Lists
//By Yvette Williamson

#include <iostream>
#include <string>
#include<sstream>
using namespace std;

class Node {
private:
//intialization and declaration of variables
	string line;
	Node*next = NULL;

public:
//Declaraction and intialization of methods in class Node

	Node* insert(Node*poem, std::string line, int lineNum)
	{
		//insert method insert new Node, new line, in the linked list at a desired line number

		//intialization and declaration of variables
		Node *current = new Node;
		Node *prev = new Node;
		Node *win = new Node;
		int track = 1;

		line = line.substr(1, line.length());

		//Checks to make sure the string is valid
		if (line.at(0) != '"') {
			return poem;
		}

		win->line = line;

		//checks to see if insert is at beginning of the linked list, to insert line in only if the string in the Node is empty
		//else, the string inserts the entire new Node at beginning of linked list
		if (lineNum == 1 && poem->line == "")
		{
			poem->line = line;
			return poem;

		}
		else if (lineNum == 1)
		{
			win->next = poem;
			return win;
		}

		current = poem;

		//while loop for traversing through Nodes
		//if line number is equal to track, new Node is inserted
		while (current != NULL)
		{
			if (current->next == NULL && track + 1 == lineNum)
			{
				current->next = win;
				return poem;
			}
			else if (current->next != NULL && track + 1 == lineNum)
			{
				prev = current;
				current = current->next;
				prev->next = win;
				win->next = current;
				return poem;
			}
			track++;
			current = current->next;
		}
		return poem;
	}

	void insertEnd(Node*poem, std::string line) {
		//insertEnd method inserts Node at end of linked list

		//if statement to check if the Node at the head of the linked list is empty
		if (poem->line == "") {
			poem->line = line;
			return;

		}

		//intialization and declaration of variables
		Node *in = new Node;

		//while loop for traversing through Nodes
		//Once end is found, inserts new Node
		while (poem != NULL) {
			if (poem->next == NULL) {
				in->line = line;
				poem->next = in;
				return;
			}
			poem = poem->next;
		}
	}

	void search(Node*poem, std::string line, int lineNum) {
		//search method looks for a string in the linked list, then outputs line that the string was found in

		//intialization and declaration of variables
		int counter = 1;
		std::string comp = "";
		bool founder = false;
		std::string token = "";

		//while loop for traversing through Nodes
		//searches through each Node for string and outputs each line that contains the string
		//if not found, method outputs "not found"
		while (poem != NULL) {
			comp = poem->line;
			line = line.substr(1, line.length() - 2);
			if (comp.find(line) != std::string::npos) {
				founder = true;
				comp = comp.substr(1, comp.length() - 2);
				std::cout << counter << " " << comp << std::endl;

			}
			counter++;
			poem = poem->next;
		}
		if (founder) {
			return;
		}
		else {
			std::cout << "not found" << std::endl;
		}
	}

	void edit(Node*poem, std::string line, int lineNum) {
		//intialization and declaration of variables
		int counter = 1;
		line = line.substr(1, line.length());

		//while loop for traversing through Nodes
		//Once counter equals the line number, the line of the Node will be edited
		while (poem != NULL) {
			if (counter == lineNum) {
				poem->line = line;
			}
			counter++;
			poem = poem->next;
		}
	}

	Node* removal(Node*poem, std::string line, int lineNum) {
		//removal method removes unwanted Node in linked list

		//intialization and declaration of variables
		int counter = 1;
		Node *prev = new Node;
		Node *current = new Node;
		Node *temp = new Node;

		//Checks if the head of the linked list needs to be removed
		if (lineNum == 1)
		{
			temp = poem;
			poem = poem->next;
			delete temp;
			return poem;
		}

		prev = poem;
		current = poem->next;

		//while loop for traversing through Nodes
		//When line number matches the counter number, the node needed for removal will be taken out and deleted
		while (current != NULL)
		{
			if (counter + 1 == lineNum && current->next != NULL)
			{
				temp = current;
				current = current->next;
				prev->next = current;
				delete temp;
				return poem;
			}
			else if (counter + 1 == lineNum && current->next == NULL)
			{
				prev->next = NULL;
				return poem;
			}
			prev = current;
			counter++;
			current = current->next;
		}
		return poem;
	}

	void print(Node*poem) {
		//print method outputs the line in each node

		//intialization and declaration of variables
		int counter = 1;
		std::string line = "";

		//while loop for traversing through Nodes
		while (poem != NULL && poem->line != "")
		{
			line = poem->line;
			line = line.substr(1, line.length() - 2);
			std::cout << counter;
			std::cout << " " << line << std::endl;
			poem = poem->next;
			counter++;
		}

	}
};

int main()
{
	//intialization and declaration of variables
	Node * poem = new Node;
	std::string option = "";
	std::string line = "";
	std::string left = "";
	std::string strnum = "";
	int lineNum = 0;
	int i = 0;
	char delim = '"';
	std::string toe = "";
	char space = ' ';

	//While loop to continually receive input until the user enters "quit"
	//incorrect input is ignored
	while (option != "quit") {
		option = "";
		left = "";
		toe = "";
		line = "";
		strnum = "";

		//Get input from user then put in string stream
		std::getline(std::cin, left);
		std::istringstream ss(left);

		//while loop is for taking out words that could be the option, line, or line number(strnum, which later converts to lineNum)
		while (std::getline(ss, toe, space))
		{
			if (option == "")
			{
				option = toe;
			}
			else if (strnum == "")
			{
				strnum = toe;

				if (strnum.at(0) == delim)
				{
					line = strnum;
				}
			}
			else
			{
				line = line + " " + toe;
			}
		}

		if (strnum == line)
		{
			strnum.clear();
		}

		//converts string in strnum variable to integer
		if (!(std::istringstream(strnum) >> lineNum))
			lineNum = 0;

		//Menu of options. If option found, will call the corresponding function
		if (option == "insert") {
			poem = poem->insert(poem, line, lineNum);

		}
		else if (option == "insertEnd") {
			poem->insertEnd(poem, line);

		}
		else if (option == "delete") {
			poem = poem->removal(poem, line, lineNum);
		}
		else if (option == "edit") {
			poem->edit(poem, line, lineNum);

		}
		else if (option == "search") {
			poem->search(poem, line, lineNum);
		}
		else if (option == "print") {
			poem->print(poem);

		}

	}
	return 0;


}