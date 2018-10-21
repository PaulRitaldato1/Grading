// Programming Assignment 1 Gerrad Hardy.cpp : Defines the entry point for the console application.
//Gerrad Hardy
//COP 3530

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct Node
{
	string data;
	Node *next;
};
//Complete
Node* insertEndMethod(Node *head, string data)
{
	struct Node *temp = new Node;
	temp->data = data;
	temp->next = NULL;
	Node *last = head;

	if (head == NULL) //if first line is blank
	{
		head = temp;
		return head;
	}
	else
	{
		//traverse list
		while (last->next != NULL)
		{
			last = last->next;
		}
		//change next of the last node to the new node
		last->next = temp;
		return head;
	}
}
//Complete
Node* insertIndexMethod(Node* head, int index, string data)
{
	Node *temp1 = new Node();
	temp1->data = data;
	temp1->next = NULL;

	if (index == 1)
	{
		temp1->next = head;
		head = temp1;
		return head;
	}
	else
	{
		Node *temp2 = head;
		for (int i = 0; i < index - 2; i++)
		{
			temp2 = temp2->next;	//points temp2 to index-1 position
		}
		temp1->next = temp2->next;	// places temp1 after temp 2 which is at index-1 position
		temp2->next = temp1;  //adjust link of index-1 to the new node at index
		return head;
	}
}
//Complete
Node* deleteIndexMethod(Node* head, int index)
{
	struct Node* tempBefore = head;
	if (index == 1)
	{
		tempBefore=head->next;
		delete(head);
		head = tempBefore;
		return head;
		//deletes head node and replaces with next node

	}
	else
	{
		for (int i = 0; i < index - 2; i++)
		{
			tempBefore = tempBefore->next;
			//tempBefore points to the postion before the index (index-1)
		}
		struct Node* tempIndex = tempBefore->next; //(index)
		tempBefore->next = tempIndex->next; //node before index points to node after index removing node at index
		return head;
	}
}
//Complete
Node* editIndexMethod(Node* head, int index, string data)
{
	Node *temp = new Node;
	temp->data = data;
	temp->next = NULL;

	if (index == 1)
	{
		head->data = temp->data;
		return head;
	}
	else
	{
		temp = head;
		for (int i = 1; i < index; i++)
		{
			temp = temp->next;
		}
		temp->data = data;

		return head;
	}

}
//Complete
void printMethod(Node* head)

{
	int lineNumber = 1;
	struct Node* last = head;
	if (head == NULL) //if first line is blank
	{
		cout << "List is empty" << endl;
		return;
	}
	else
	{
		while (last != NULL)
		{
			cout << lineNumber << " " << last->data << endl;
			last = last->next;
			lineNumber++;
		}
		return;
	}
}
//Complete
void searchMethod(Node* head, string data)
{
	Node *current = new Node();
	bool found = false;
	current = head;

	int lineNumber = 1;

	while (current != NULL)
	{

		if (current->data == data)
		{
			cout << lineNumber << " " << current->data << endl;
			found = true;
		}
		current = current->next;
		lineNumber++;

	}
	if (found == false)
	{
		cout << "not found" << endl;
	}
	return;
}
//Complete
int main()
{
	////////////////////////Variable Decleration///////////////////
	string insertEnd = "insertEnd ";
	string insertIndex = "insert ";
	string deleteIndex = "delete ";
	string editIndex = "edit ";
	string print = "print";
	string search = "search ";
	string quit = "quit";

	string input;	//user input

	//creates linked list
	struct Node *head = NULL;

	//While loop runs until "quit" is entered
	while (input.compare(quit))
	{
		////////////finds which how many lines are filled//////////
		int lineNumber = 0;
		struct Node* last = new Node();
		last = head;
		while (last != NULL)
		{
			last = last->next;
			lineNumber++;
		}
		////////////////////////////////////////////////////////////

		cout << "Hello. Welcome to the line editor. Please enter command..." << endl;
		getline(cin, input);
		int firstSpace = input.find_first_of(' '); //finds space in order to create substring for commands
		int secondSpace = input.substr(firstSpace + 1, input.length()).find_first_of(' ');//finds the length between first space and second space in order to determine size of index
		int firstQuote = input.find_first_of('"');
		int lastQuote = input.find_last_of('"');
		int lineLength = lastQuote - firstQuote;//finds length of the actual input

		///////////////////////////////////consider switch instead of if statements///////////////////////////////////
		///////////////////////////////////logic for choosing which method to run/////////////////////////////////////
		if (insertEnd.compare(input.substr(0, firstSpace + 1)) == 0)
		{
			head = insertEndMethod(head, input.substr((input.find_first_of('"') + 1), lineLength - 1));    //passes a substring starting from one after the first quoation mark to one before the last quotation mark
		}
		else if (insertIndex.compare(input.substr(0, firstSpace + 1)) == 0)
		{
			int lineIndex = stoi(input.substr(firstSpace + 1, secondSpace));
			if (lineIndex > lineNumber + 1)
			{
				cout << "Line out of bounds" << endl;
			}
			else
			{
				head = insertIndexMethod(head, lineIndex, input.substr((input.find_first_of('"') + 1), lineLength - 1));
			}
		}
		else if (deleteIndex.compare(input.substr(0, firstSpace + 1)) == 0)
		{
			if ((stoi(input.substr(firstSpace + 1, input.length())) > lineNumber) || stoi(input.substr(firstSpace + 1, input.length())) <= 0)
			{
				cout << "Line out of bounds" << endl;
			}
			else
			{
				deleteIndexMethod(head, stoi(input.substr(firstSpace + 1, input.length())));//parses index value into int
			}
		}
		else if (editIndex.compare(input.substr(0, firstSpace + 1)) == 0)
		{
			int lineIndex = stoi(input.substr(firstSpace + 1, secondSpace));
			if (lineIndex > lineNumber)
			{
				cout << "Line out of bounds" << endl;
			}
			else
			{
				head = editIndexMethod(head, lineIndex, input.substr((input.find_first_of('"') + 1), lineLength - 1));
			}

		}
		else if (print.compare(input) == 0)
		{
			printMethod(head);
		}
		else if (search.compare(input.substr(0, firstSpace + 1)) == 0)
		{
			searchMethod(head, input.substr((input.find_first_of('"') + 1), lineLength - 1));
		}
		else if (quit.compare(input) == 0)
		{
			cout << "Thank your for editing." << endl;
		}
		else
		{
			cout << "Please enter correct command" << endl;
		}


	}
}
