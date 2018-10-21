// Programming_Assignment_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


struct node
{
	string text;
	struct node *next;
};

struct node* makeNode(string value)
{
	struct node *n = new node;
	n->text = value;
	n->next = NULL;
	return(n);
}


struct node *head = NULL;



struct node* makeNode(string);
void insertEnd(struct node *, string);
void insert(struct node *, int, string);
void deleteLine(struct node *, int);
void edit(struct node *, int, string);
void print(struct node *);
void search(struct node *, string);




//User Commands:

//insertEnd "text"  --insert given text at the end of the document
void insertEnd(struct node *ptr, string text)
{
	struct node *newNode;
	newNode = makeNode(text);
	if (head == NULL)
		head = newNode;
	else
	{
		while (ptr->next != NULL) 
			ptr = ptr->next;
		ptr->next = newNode;
	}
}

//insert 3 "text" --insert given text at the line indicated by index given
void insert(struct node *ptr, int line, string text)
{
	struct node *iterator;
	int count = 0;
	iterator = head;
	while (iterator != 0)
	{
		count++;
		iterator = iterator->next;
	}

	struct node *prev = NULL; 
	struct node* newNode = makeNode(text);
	int i;


	if (count+1 < line) {
		return;
	}

	for (i = 1; i < line; i++)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL) 
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		newNode->next = ptr;
		prev->next = newNode;
	}
}

//delete 3 -- - delete line at index given
void deleteLine(struct node *ptr, int line)
{

	struct node *iterator;
	int count = 0;
	iterator = head;
	while (iterator != 0)
	{
		count++;
		iterator = iterator->next;
	}
	
	struct node *del;
	struct node *prev = NULL; 
	int i;

	if (count < line) {
		return;
	}
	for (i = 1; i < line; i++)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL)
	{
		del = ptr;
		head = head->next;
	}
	else
	{
		del = ptr;
		prev->next = ptr->next;
	}
	delete del;
}

//edit 3 "text" -- - replace the line at the index given with the given text
void edit(struct node *ptr,int line, string text) 
{
	int i;
	for (i = 1; i < line; i++)
	{
		ptr = ptr->next;
	}
	ptr->text = text;
}

//print -- print the entire document, with line numbers
void print(struct node *ptr) 
{

		if (ptr == NULL) 
		{
		printf("Unable to Print, File is Empty.\n");
		}

		else
		{
			int i = 1;
			while (ptr)
			{
				cout << i << " " << ptr->text << endl;
				ptr = ptr->next;
				i++;
			}
		}
}

//search "text" --print the line number and line that contains the given text.print "not found" if it is not found
void search(struct node *ptr, string text)
{
	int i = 1;
	bool found = false;
	while (ptr)
	{
		if (ptr->text.find(text) != -1)
		{
			cout << i << " " << ptr->text << endl;
			found = true;
		}
		ptr = ptr->next;
		i++;
	}
	if (ptr == NULL && found == false)
		cout << "not found" << endl;
}

//quit - quit / exit the program
void quit() 
{
	exit(0);
}




//Main Function
int main()
{

	string command;
	string tempText;
	string lineNumber;
	int tempLine;
	int spaceFinder;

	while (true) {
		getline(cin,command);

		if (command.substr(0,9) == "insertEnd") {
			tempText = command.substr(11);
			tempText.pop_back();
			insertEnd(head,tempText);
		}

		else if (command.substr(0,6) == "insert") {
			spaceFinder = command.find(" ", 7);
			lineNumber = command.substr(7, spaceFinder - 7);
			stringstream lineConvert(lineNumber);
			lineConvert >> tempLine;
			lineConvert.clear();
			tempText = command.substr(spaceFinder + 2);
			tempText.pop_back();
			insert(head, tempLine, tempText);
		}

		else if (command.substr(0,6) == "delete") {
			spaceFinder = command.find(" ", 7);
			lineNumber = command.substr(7, spaceFinder - 7);
			stringstream lineConvert(lineNumber);
			lineConvert >> tempLine;
			lineConvert.clear();
			deleteLine(head,tempLine);
		}

		else if (command.substr(0,4) == "edit") {
			spaceFinder = command.find(" ",5);
			lineNumber = command.substr(5, spaceFinder - 5);	
			stringstream lineConvert(lineNumber);
			lineConvert >> tempLine;
			lineConvert.clear();
			tempText = command.substr(spaceFinder+2);
			tempText.pop_back();
			edit(head, tempLine, tempText);
		}

		else if (command == "print") {
			print(head);
		}

		else if (command.substr(0,6) == "search") {
			tempText = command.substr(8);
			tempText.pop_back();
			search(head,tempText);
		}

		else if (command == "quit") {
			quit();
		}

   }
   return 0;
}
