/*
Dustin Durden
Programming Assignment 1
COP 3530

Line editor using linked lists
*/

#include <algorithm>
#include <iostream>
#include <string>

//List definition
class List
{
	//Basic node class definition
	struct Node
	{
		std::string line;
		Node* next;
	};

	Node* head;
	Node* tail;
	int size;

//List member functions
public:
	List();
	void insertEnd(std::string s);
	void insert(int index, std::string s);
	void deleteLine(int index);
	void edit(int index, std::string s);
	void print();
	void search(std::string s);
	
	const static int CAPACITY = 80;
};

//Constructor
List::List()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

void List::insertEnd(std::string s)
{
	//Check to make sure the input doesn't exceed capacity
	if(s.size() > CAPACITY)
		return;

	Node* addNode = new Node;
	addNode->line = s;

	//If the list is empty
	if(head == NULL)
	{
		head = addNode;
		addNode->next = NULL;
		size++;
	}
	else
	{
		//Move the temporary node "last" to the end of the list
		//to insert the new node
		Node* last = head;
		while(last->next!= NULL)
			last = last->next;

		//Insert the new node, make it the tail, and increase
		//the size of the list
		last->next = addNode;
		addNode->next = NULL;
		tail = addNode;
		size++;
	}
}

void List::insert(int index, std::string s)
{
	//Check to make sure the input doesn't exceed capacity
	if(s.size() > CAPACITY)
		return;

	Node* current;
	Node* trail;
	//Node to be added
	Node* addNode = new Node; 
	addNode->line = s;

	//Variable used to add at the correct index
	int tempIndex = 1;

	//Set current to beginning of the list
	current = head;

	//If there is already a list
	if(head != NULL)
	{
		//Continues until the end of the list is reached or index is found
		while(current->next != NULL && tempIndex != index)
		{
			trail = current;
			current = current->next;
			tempIndex++;
		}

		//Add to head
		if(index == 1)
		{
			addNode->next = head;
			head = addNode;
			size++;
		}

		//Add to the end
		else if(current->next == NULL && index == tempIndex + 1)
		{
			insertEnd(s);
		}

		//If the given index is out of bounds for the list
		else if(index > size)
		{
			return;

		}

		//Add node to given index
		else
		{
			trail->next = addNode;
			addNode->next = current;
			size++;
		}
	}

	//List is empty so the node becomes the head
	else
	{
		if(index == 1)
		{
			head = addNode;
			addNode->next = NULL;
			size++;
		}

		//If the list is empty but the given index is not 1
		else
		{
			return;
		}
	}
}

void List::deleteLine(int index)
{
	Node* trail;
	Node* current;

	//Variable to find the line to be deleted
	int tempIndex = 1;

	current = head;

	//If the list is not empty
	if(head != NULL)
	{
		//Navigate through the list moving temporary pointers until
		//correct index is found or the end of the list is reached
		while(current->next != NULL && tempIndex != index)
		{
			trail = current;
			current = current->next;
			tempIndex++;

		}
		//If the given index is 1
		if(index == 1 )
		{
			//If the list has only 1 node
			if(size == 1)
			{
				head = NULL;
				delete current;
				size--;
				return;
			}

			//If the list has more than 1 node
			else
			{
				trail = current;
				current = current->next;
				trail->next = NULL;
				delete trail;
				head = current;
				size--;
				return;
			}
		}

		//If the index was not in the list
		if(tempIndex != index)
		{
			return;
		}

		//Set the previous node to point to the next node and delete
		//the node inbetween
		else
		{
			trail->next = current->next;
			size--;
			delete current;
		}
	}

	//If the list is empty
	else
	{
		return;
	}
}

void List::edit(int index, std::string s)
{
	//Check to make sure the input doesn't exceed capacity
	if(s.size() > CAPACITY)
		return;

	Node* current;

	//Variable to find the right index in the list
	int tempIndex = 1;

	current = head;
	//If the list is not empty
	if(head != NULL)
	{
		//Navigate the list until the end is reached or the given index
		//is found
		while(current->next != NULL && tempIndex != index)
		{
			current = current ->next;
			tempIndex++;
		}

		//If the end was reached and the index was not found
		if(current->next == NULL && tempIndex != index)
		{
			return;
		}

		//Makes the stored line equal to the new input
		else
		{
			current->line = s;
			return;
		}
	}

	//If the list is empty
	else
		return;
}

void List::search(std::string s)
{
	//Check to make sure the input doesn't exceed capacity to potentially
	//save time
	if(s.size() > CAPACITY)
		return;

	Node* current;

	//Variable used to give the correct index outputs
	int index = 1;

	//Boolean used to determine if search was successful
	bool found = false;

	current = head;
	//If the list is empty
	if(head != NULL)
	{
		//Navigate through the list
		while(current != NULL)
		{
			//If the string stored in the current node contains the string
			//to be found, output the index and stored string
			if(current->line.find(s) != std::string::npos)
			{
				std::cout << index << " " << current->line << std::endl;
				found = true;
			}

			//Increment index and move to next node
			current = current->next;
			index++;
		}

		//If the string was not in the list
		if(!found)
			std::cout << "not found\n";
	}
	//If the list is empty
	else
	{
		return;
	}
}

void List::print()
{
	//Simple print function
	Node* current = head;
	int i = 0;
	while(current != NULL)
	{
		std::cout<< ++i << " " << current->line << std::endl;
		current = current->next;
	}

}

//This method finds the text inbetween the quotes in the user input.
//It is used to extract the string and send it to the list functions
std::string findText(std::string input)
{
	int x;
	//If the input contains a double quote
	if(input.find("\"") != std::string::npos)
	{
		//Gets the index of the first double quote
		x = input.find("\"");

		//Makes a substring starting at the index of the first double quote
		std::string s = input.substr(x);
		return s;
	}
	//If quotes were not found
	else
	{
		return "error";
	}
}

//This method extracts the index given in the user input to
//send it to the list functions
int findIndex(std::string input)
{
	//If the input contains a number from 0-9
	if(input.find_first_of("0123456789") != std::string::npos)
	{
		//Character to int conversion
		return (int)input[input.find_first_of("0123456789")] - 48;
	}

	//If no integer index was found
	else
		return -1;
}

//Removes double quotes from string
void removeQuotes(std::string& input)
{
	input.erase(std::remove( input.begin(), input.end(), '\"' ),input.end());
}

int main()
{
	std::string input;

	//Loop breaker
	bool notDone = true;

	//Create list
	List list;

	//Goes until the user enters "quit"
	while(notDone)
	{
		//Gets user input and stores it in input variable
		std::getline(std::cin, input);

		//If the user entered "insertEnd"
		if(input.find("insertEnd") != std::string::npos)
		{
			//Get the line to be added
			std::string s = findText(input);

			//If the findText function returned "error" because of 
			//wrong quote format in input
			if(s.compare("error") == 0)
			{
				continue;
			}

			//Remove the quotes
			else
			{
				removeQuotes(s);
				//std::cout << s;
			}

			//Insert in the list
			list.insertEnd(s);
		}

		//If the user entered "insert"
		else if(input.find("insert") != std::string::npos)
		{
			//Checks if quotes are in the input and gets the 
			//characters inbetween the quotes
			std::string s = findText(input);

			//Same as in insertEnd method, only happens if there was
			//unexpected quote format in the input
			if(s.compare("error") == 0)
			{
				continue;
			}
			else
			{
				removeQuotes(s);
			}

			//Checks for integer index and extracts it from input string
			int y = findIndex(input);

			//If there was an error in finding the index from the given input
			if(y == -1)
			{
				continue;
			}

			list.insert(y,s);
		}

		//If the user entered "delete"
		else if(input.find("delete") != std::string::npos)
		{
			//Get the index of line to remove
			int y = findIndex(input);

			//If there was an error getting input
			if(y == -1)
			{
				continue;
			}

			list.deleteLine(y);
		}

		//If the user entered "edit"
		else if(input.find("edit") != std::string::npos)
		{
			//Get the new text
			std::string s = findText(input);

			//If there was an error getting new text
			if(s.compare("error") == 0)
			{
				continue;
			}

			else
			{
				removeQuotes(s);
			}

			//Get the index of line to edit
			int y = findIndex(input);

			//If there was an error finding the index
			if(y == -1)
			{
				continue;
			}

			list.edit(y, s);
		}

		//If the user entered "print"
		else if(input.find("print") != std::string::npos)
		{
			list.print();
		}

		//If the user entered "search"
		else if(input.find("search") != std::string::npos)
		{
			//Get the text to look for
			std::string s = findText(input);

			//If there was an error getting text
			if(s.compare("error") == 0)
			{
				continue;
			}

			else
			{
				removeQuotes(s);
			}

			list.search(s);
		}

		//If the user entered "quit"
		else if(input.find("quit") != std::string::npos)
		{
			//Set the loop breaker to false thus ending the loop
			notDone = false;
		}
	}

	return 0;
}