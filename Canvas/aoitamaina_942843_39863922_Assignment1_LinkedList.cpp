// Assign1LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <algorithm>	//for find() to search and compare
#include <sstream>		//for istringstream to take the word after encountering a space

struct node
{
	std::string data;		//initialize data
	node *next;				//node pointer next to point to next node
};

class handler
{
private:
	node *head, *tail; 	//define node pointers called head and tail
public:
	handler() 	//constructor to set head and tail to NULL so it doesn't
				//hold garbage
	{
		head = NULL;	//set them to NULL so they don't have any data
		tail = NULL;
	}

	void insertEnd(std::string text)	//insertEnd command
	{
		node *temp = new node; 	//create new node pointer temp
		temp->data = text;		//temps data holds the text
		temp->next = NULL;		//set the next pointer to NULL

		if (head == NULL)		//if there is nothing at the head when insertEnd
		{
			head = temp;		//set head to temp
			tail = temp;		//set tail to temp
			temp = NULL;		//temp set to NULL
		}
		else					// if there is something there then just attach the info to the end of it
		{
			tail->next = temp;		//tail's next is pointing at the node temp making it the second node
			tail = temp;			//the node temp is now called tail
		}

	}

	void insert(int numb, std::string text)		//insert command
	{
		node *current = head;		//node pointer current that has head information
		node *previous = head;		//node pointer previous that has head information
		node *temp = new node;		//temp node
		temp->data = text;			//temp data holds text

		int numbList = 0;
		node *tracker = head;		//tracker node to keep track of the number of nodes in the list

		if (numb == 1 && current!= NULL)	//insert at 1
		{
			temp->next = current;		//pushes the current to second node and the temp node becomes the first node
			head = temp;				//update head
		}

		if (numb != 1 && current != NULL)	//insert anywhere BUT 1
		{
			int i = 1;
			while (i < numb && current != NULL)		//dont iterate if NULL in node
			{
				previous = current;					//make previous hold current information so that its always behind current
				current = current->next;			//current will move on to next node
				i++;
			}
			while (tracker != NULL)				//if tracker doesn't equal NULL
			{
				tracker = tracker->next;		//then it will move through the list of nodes
				numbList++;						//iterate to count the number of nodes
			}

			if (numb <= numbList + 1)			//allows the user to insert text in a non existing node at numbList + 1
			{
				previous->next = temp;			//make previous next point to the temp node
				temp->next = current;			//make the new node next to point at the current node
			}			
		}
	}

	void print() //print list
	{
		node *temp = new node;

		temp = head;			//temp walks to the first node
		int tracker = 1;		//this will track the number of nodes

		while (temp != NULL)	//as long as temp isn't empty
		{
			std::cout << tracker << " " << temp->data << "\n"; //print out temps data
			temp = temp->next; //temp walks to the next node
			tracker++;	//iterate
		}
	}

	void del(int line)	//delete command
	{
		node *current = head;
		node *previous = new node;

		while (current != NULL)		//as long as the nodes have something
		{
			if (line == 1)	//if user wants to delete the beginning of the list
			{
				head = current->next;	//current points to the next node which will be the head
				break;
			}

			int i = 1;	//iterator
			while (i < line)	//if i is less than line meaning not at the node the user wants
			{
				previous = current;			//previous lags behind so that its always behind current
				current = current->next;	//keep moving
				i++;	//iterate 
			}

			tail = previous;		//set previous as tail to denote end of list
			previous->next = NULL;	//make previous point to NULL ending the list and deleting last node

			if (i = line && current != NULL)	//once we are at the node user wants but not the head
			{
				previous->next = current->next;		//make previous node next point to where the current is pointing
				break;								//which deletes the node in between
			}
			if (current == NULL)		//if we try to delete a NULL node just break
			{
				break;
			}

		}
	}

	void edit(int line, std::string text)	//edit the line specified by user with text given

	{
		node *current = head;

		if (line == 1 && current != NULL)	//insert at 1
		{
			head->data = text;	//store the text into the data of head
		}
		else	//insert somewhere not 1
		{
			int i = 1;
			while (i < line && current != NULL)		//keep iterating till we're at line. don't if its empty
			{
				current = current->next;		//make current move along til we find the line to edit
				i++;
			}
			if (current != NULL)	//as long as current isn't empty
			{
				current->data = text;		//replace the data in current with the text
			}
			
		}
	}

	void search(std::string text)		//search node
	{
		std::string info;
		node *current = head;
		int i = 1;
		bool condition = false;

		while (current != NULL)		//while there is something in the node
		{
			
			info = current->data;	//info holds currents data
			std::size_t found = info.find(text); //find users text

			if (found != std::string::npos)		//if we did find the text
			{
				std::cout << i << " " << info << '\n';
				condition = true;	//if found set condition true
			}
			if (current->next != NULL)		//as long as were not at the end of the list
			{
				current = current->next;	//keep looking
				i++;
			}
			else		//if were at the end of the list break
			{
				break;
			}
			
		}
		if (condition == false)		//if we didn't find anything
		{
			std::cout << "not found\n";
		}
	}
};

int main()
{
	handler handler;	//initialize class
	std::string input;
	std::size_t quit;

	do {
		std::getline(std::cin, input);	//get user iput
				
		quit = input.find("quit"); //find "quit"

		std::size_t insertEnd = input.find("insertEnd"); //find "insertEnd"

		std::size_t insert = input.find("insert"); //find "insert"

		std::size_t del = input.find("delete"); //find "delete"

		std::size_t edit = input.find("edit"); //find "edit"

		std::size_t print = input.find("print"); //find "print"

		std::size_t search = input.find("search"); //find "search"

		char quo = '"'; //initialize character "

		if (insertEnd != std::string::npos) //if "insertEnd" is found
		{
			input.erase(0, 10); //erase "insertEnd(space)"
			input.erase(std::remove(input.begin(), input.end(), quo), input.end()); //removes all characters " from string input

			//cuts input if its more than 80
			int checkLen = input.length();
			if (checkLen > 80)
			{
				input.erase(80, checkLen - 80);
			}

			handler.insertEnd(input);
		}
		else if (insert != std::string::npos)
		{
			input.erase(0, 7);
			
			input.erase(std::remove(input.begin(), input.end(), quo), input.end()); //removes all characters " from string input
			
			std::istringstream iss(input);	//istringstream iss takes the first word after encountering a whitespace
			std::string numb;
			iss >> numb;	//stores the word into numb

			int number = std::stoi(numb); //change my string into int

			int length = numb.length();		//find the length of the digits
			input.erase(0, length+1);		//delete the digits out of the input

			char quo = '"';
			input.erase(std::remove(input.begin(), input.end(), quo), input.end()); //removes all characters " from string input

			//cuts input if its more than 80 chars
			int checkLen = input.length();
			if (checkLen > 80)
			{
				input.erase(80, checkLen - 80);
			}

			handler.insert(number, input);
		}
		else if (del != std::string::npos)
		{
			input.erase(0, 7);		//delete the word delete(space)

			std::istringstream iss(input);	//istringstream iss takes the first word after encountering a whitespace
			std::string numb;
			iss >> numb;	//stores the word into numb

			int number = std::stoi(numb); //change my string into int

			handler.del(number);
		}
		else if (edit != std::string::npos)
		{
			input.erase(0, 5);
			input.erase(std::remove(input.begin(), input.end(), quo), input.end()); //removes all characters " from string input

			std::istringstream iss(input);	//istringstream iss takes the first word after encountering a whitespace
			std::string numb;
			iss >> numb;	//stores the word into numb

			int number = std::stoi(numb); //change my string into int

			int length = numb.length();		//find the length of the digits
			input.erase(0, length + 1);		//delete the digits out of the input

			//cuts input if its more than 80 chars
			int checkLen = input.length();
			if (checkLen > 80)
			{
				input.erase(80, checkLen - 80);
			}

			handler.edit(number, input);
		}
		else if (print != std::string::npos)
		{
			handler.print();
		}
		else if (search != std::string::npos)
		{
			input.erase(0, 7);
			input.erase(std::remove(input.begin(), input.end(), quo), input.end()); //removes all characters " from string input

			//cuts input if its more than 80 chars
			int checkLen = input.length();
			if (checkLen > 80)
			{
				input.erase(80, checkLen - 80);
			}

			handler.search(input);
		}
	}while (quit == std::string::npos);
	
	if (quit != std::string::npos) //quit program 
	{
		return 0;
	}
}