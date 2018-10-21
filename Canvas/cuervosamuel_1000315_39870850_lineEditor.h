#pragma once
#include <string>

using namespace std;

struct node						//Creates the node structure
{
	string prog;
	node* next;
};

class list						//The class that allows you to create a linked list
{
private:
	node* head;
public:
	list()
	{
		head = NULL;
	}

	int size()					//This returns the overall size of the linked list
	{
		node* temp = new node;
		temp = head;

		int count = 0;
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}

		return count;
	}

	void push(string value)		//Creates the node at the head end
	{
		node* temp = new node;
		temp->prog = value;
		temp->next = head;
		head = temp;
	}

	void pushEnd(string value)     //Creates the node at the tail end
	{
		node* temp = new node;
		node* insert = new node;

		insert->prog = value;
		if (head == NULL)
		{
			head = insert;
			return;
		}

		temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = insert;

	}

	void add(int index, string value)  //Adds a value inbetween a node
	{

		node* prev = new node;
		node* curr = new node;
		node* insert = new node;
		insert->prog = value;

		curr = head;


		if (size() + 1 < index)
			return;
		for (int it = 1; it != index; it++)
		{

			prev = curr;
			curr = curr->next;
		}

		if (curr == NULL && prev != NULL)
		{
			prev->next = insert;
		}
		else if (curr == NULL && prev == NULL)
		{
			std::cout << "Error: the list is empty or the index is out bounds" << std::endl;
		}
		else
		{
			//prev = head;
			prev->next = insert;
			insert->next = curr;
		}
	}

	void replace(int index, string value)		//Replaces the string the node has with the given string at the given index
	{
		node* temp = new node;
		temp = head;

		if (size() < index)
			return;
		if (index <= 0)
		{
			cout << "Error: please enter a value over 0" << endl;
			return;
		}
		if (index == 1)
		{
			temp->prog = value;

			return;
		}
		for (int x = 1; x != index; x++)
		{
			if (temp == NULL)
			{
				cout << "Error: index is out of bounds" << endl;
				return;
			}
				
			temp = temp->next;
		}

		temp->prog = value;
	}

	void remove(int index)		//Removes the string at the given index
	{
		node* temp = new node;
		node* prev = new node;
		temp = head;

		if (size() < index)
			return
		for (int x = 1; x != index; x++)
		{
			prev = temp;
			temp = temp->next;
		}
		if (prev == NULL && temp == NULL)
		{
			cout << "Error: the list is empty or the index is out bounds" << endl;
		}
		else if (prev != NULL && temp == NULL)
		{
			prev->next = NULL;
		}
		else
		{
			prev->next = temp->next;
		}
	}

	void findText(string value)		//Finds the line that contains the string value and returns the line location and the entire line itself
	{
		node* temp = new node;

		temp = head;

		int it = 1;
		bool found = false;
		while (temp != NULL)
		{
			if (temp->prog.find(value) != -1)
			{
				cout << it << " " << temp->prog << endl;
				found = true;
			}
				
			temp = temp->next;
			it++;
		}
		if(found == false)
			cout << "not found" << endl;
	}

	void display()				//Prints the list
	{
		node* temp = new node;
		temp = head;
		
		int it = 0;
		while (temp != NULL)
		{
			it++;
			cout << it << " " << temp->prog << endl;
			temp = temp->next;
		}
	}
};
