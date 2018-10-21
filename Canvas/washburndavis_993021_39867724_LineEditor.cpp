// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <string>
#include <iostream>
//#include "Node.h"
#include <istream>
using namespace std;
class Node
{
public:
	Node();
	~Node();
	Node* next; //pointer to next node in list
	Node* previous; //pointer to previous node in list
	std::string lineValue; //stores the line we wish to have in our line editor

};



std::string userInput;
int lineInput;
Node* head = NULL;
Node* tail = NULL;



static void insertEnd(std::string input) //inserts node to end of linked list
{
	
	
	Node* insertionNode = new Node();
	insertionNode->lineValue = input;
	insertionNode->next = NULL;
	//sets the node to head if the list is initially empty
	if (head == NULL)
	{
		head = insertionNode;
		tail = insertionNode;
	
		
	}
	
	else //insert a node at the end of the list
	{
		insertionNode->previous = tail;
		tail->next = insertionNode;
		tail = insertionNode;
	}
}

static void insert(int index, std::string input) //inserts node at specified line 
{
	Node* insertionNode = new Node();
	insertionNode->lineValue = input;
	if (index == 1) //if the index is at the beginning of the list
	{
		insertionNode->next = head;
		head = insertionNode;
	}
	else
	{
		int i = 2;
		Node* current = head; //serves as beginning node to iterate through the current list
		while (i < index)
		{
			current = current->next;
			if (current == NULL) //if it reaches the end of the list without reaching the specified index, nothing is inserted
			{
				return;
			}
			i++;
		}
		Node* temp = current->next;
		insertionNode->previous = current;
		current->next = insertionNode;
		insertionNode->next = temp;
	}
	
}
static void deleteLine(int index)
{
	if (index == 1) //if index is at the beginning of the list
	{
		head = head->next;
	}

	int i = 1;
	Node* current = head; //serves as our node to help us through iterate through the list
	Node* temp = head; //temporary node to store the previous node and its pointers while iterating through
	while (i < index)
	{
		temp = current;
		current = current->next;
		if (current == NULL)
		{
			return;
		}
		
		i++;
	}
	if (current->next == NULL)
	{
		temp->next = NULL;
	}
	else
	{
		temp->next = current->next;
	}
}
static void edit(int index, std::string input) //edits the string value of a node at the given index
{
	int i = 1;
	Node* current = head;
	while (i < index)
	{
		if (current == NULL)
		{
			return;
		}
		current = current->next;
		i++;
	}
	current->lineValue = input;
}
static void search(std::string input) //searches for a given string and returns the line number and line if it is found
{
	int index = 1;
	bool isFound = false;
	Node* current = head;
	while (current != NULL)
	{
		
		if (current->lineValue.find(input) != std::string::npos)
		{
			std::cout << index;
			std::cout << " ";
			std::cout << current->lineValue << std::endl;
			isFound = true;
		}
		current = current->next;
		index++;
	}
	if (isFound == false)
	{
		std::cout << "not found" <<std::endl;
	}
	
}
static void print() //prints current linked list
{
	int index = 1;
	Node* temp = head;
	while (temp != NULL)
	{
		
		std::cout << index;
		std::cout << " ";
		std::cout << temp->lineValue << std::endl;
		temp = temp->next;
		index++;
	}
}


int main()
{
	std::cin >> userInput;
	int index;
	while (userInput != "quit")
	{
		if (userInput.substr(0,9) == "insertEnd")
		{
			cin.ignore();
			getline(std::cin, userInput);
			userInput = userInput.substr(1, userInput.size()-2);
			insertEnd(userInput);
		}
		if (userInput.substr(0, 6) == "insert" && userInput.substr(0, 9) != "insertEnd")
		{
			
			getline(std::cin, userInput);
			char num = userInput[1];
			index = num - '0';
			userInput = userInput.substr(4, userInput.size()-5);
			insert(index, userInput);
			
		}
		if (userInput.substr(0,6) == "delete")
		{
			getline(std::cin, userInput);
			char num = userInput[1];
			index = num - '0';
			deleteLine(index);
		}
		if (userInput.substr(0, 4) == "edit")
		{
			getline(std::cin, userInput);
			char num = userInput[1];
			index = num - '0';
			userInput = userInput.substr(4, userInput.size() - 5);
			edit(index, userInput);
		}

		if (userInput.substr(0, 6) == "search")
		{
			getline(std::cin, userInput);
			userInput = userInput.substr(2, userInput.size() - 3);
			search(userInput);

		}
		if (userInput == "print")
		{
			print();
		}
		std::cin >> userInput;
	}
    return -1;
}

