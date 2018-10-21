/*
 Author: Britton Chesley
 Description: Programming Assignment 1 for COP3530 Fall 2018
*/

#include <stddef.h>
#include <iostream>
#include <stdio.h>
#include <string>
///***** Linked List Implementation *****///
class List
{
private:
	struct Node {
		std::string data;
		Node *prev; //pointer to previous node
		Node *next; //pointer to next node
	};

public:
	List() //list constructor
	{
		init(); //initialization routine
	}
	~List() //list destructor
	{
		clear();
	}
	void clear()
	{ //this function deletes the entire linked list
		Node * to_delete;
		Node * parse = this->head;
		while (size != 0)
		{
			to_delete = parse;
			parse = parse->next;
			delete to_delete;
			size--;
		}
	}
	int getSize()
	{
		return size;
	}
	
	/*
		This function takes a string and creates a node at the end of the linked
		list with this string as its member data
	*/
	void insertEnd(std::string data)
	{
		Node * new_node = new Node();
		new_node->data = data;
		if (this->size == 0)
		{ //if first node
			new_node->prev = nullptr;
			new_node->next = nullptr;
			this->head = new_node;
			this->tail = new_node;
			this->size++;
			return;
		}
		new_node->prev = this->tail; //reassign pointers
		new_node->next = nullptr;
		(new_node->prev)->next = new_node;
		this->tail = new_node;
		this->size++;
	}
	/*
	This function takes a string and index and creates a node at the index given of the linked
	list with this string as its member data
	*/
	void insert(int index, std::string data)
	{
		//node to be added to the linked list
		Node *new_node = new Node();
		new_node->data = data;
		if (index > this->getSize() - 1)
		{
			//either out of bounds or first node to be added

			if (index == 0) //if insert at head
			{
				new_node->next = this->head;
				new_node->prev = nullptr;
				(this->head)->prev = new_node;
				this->head = new_node;
				if (this->size == 0)
				{
					this->tail = this->head;
				}
				this->size++;
				return;
			}
			else if (index == this->size)
			{
				//add to the end of the list
				new_node->next = nullptr;
				new_node->prev = this->tail;
				this->tail->next = new_node;
				this->tail = new_node;
				this->size++;
				return;
			}
			else
			{
				delete new_node; //otherwise 
				return;
			}
		}



		int n = 0;
		Node *parse = this->head;
		while (n < index - 1) //get node at index -1
		{
			parse = parse->next;
			n++;
		}

		//general conditons
		new_node->next = parse->next;
		new_node->prev = parse;
		
		(parse->next)->prev = new_node;
		parse->next = new_node;
		this->size++;
	}
	//this function deletes the node at the given index
	void delete_index(int index)
	{
		if (index > this->getSize() - 1)
		{
			return; //ignore invalid delete requests
		}

		if (index == 0)
		{
			//deleting head
			Node *oldHead = this->head;
			((this->head)->next)->prev = nullptr;
			this->head = (this->head)->next;
			delete oldHead;
		}
		else if (index == this->getSize() - 1)
		{
			//deleting tail
			Node *oldTail = this->tail;
			((this->tail)->prev)->next = nullptr;
			this->tail = (this->tail)->prev;
			delete oldTail;
		}
		else
		{
			//deleting somewhere in the middle
			Node *parse = this->head;
			int n = 0;
			while (n < index - 1) //get node before the index we want to delete
			{
				n++;
				parse = parse->next;
			}
			Node *to_delete = parse->next;
			((parse->next)->next)->prev = parse;
			parse->next = (parse->next)->next;
			delete to_delete;
		}
		this->size--;

	}
	/*
		this function takes an index and string and changes the member data
		of the node at the given index to the passed string
	*/
	void edit(int index, std::string data)
	{
		if (index > this->size - 1)
		{
			return;
		}
		int n = 0;
		Node * parse = this->head;
		while (n < index) //get exact node we want to edit
		{
			n++;
			parse = parse->next;
		}
		parse->data = data; //update data of the node
	}
	/*
	this function prints the entire linked list ("Document") 
	*/
	void print()
	{
		//print entire list
		Node *parse = this->head;
		int n = 0;
		while (n <= (this->size-1)) //parse through entire linked list
		{
			std::cout << (n+1) << " "; 
			std::cout << (parse->data); //print data in each node
			parse = parse->next;
			n++;
			std::cout << "\n";
		}

	}
	/*
		this function takes in a string and searches the linked list for the node(s)
		whose member data contains the given string, and prints out the nodes which 
		contain the passed string in their member data
	*/
	void search(std::string data)
	{
		if (this->size == 0)
		{
			std::cout << "not found\n";
			return;
		}
		int n = 0;
		Node* parse = this->head;
		size_t pos;
		while (n < this->size) //parse entire list
		{
			pos = (parse->data).find(data); //will return a std::string::npos if the string was not found
			if (pos != std::string::npos)
			{
				std::cout << (n + 1) << " " << (parse->data); //print out line number and line
				std::cout << "\n";
			}
			parse = parse->next;
			n++;
		}

		if (pos == std::string::npos)
		{
			std::cout << "not found\n";
		}
	}
	///private member variables
private:
	int size;
	Node *head;
	Node *tail;

	void init()
	{
		size = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		head->prev = tail;
		tail->next = head; //doubly linked list
		tail->prev = head;
	}
};



/****** Public functions (not class dependent)******/

/*
This function extracts the command in the user input string and returns this string
*/
std::string determine_command(std::string input)
{
	int start = -1;
	int stop = -1;
	std::string text = "";
	bool stop_loops = false;
	for (int i = 0; i < input.length() && !stop_loops; i++)
	{
		if (input.at(i) != *" ") //check for spaces at the beggining of the input string
		{
			start = i;
			for (int j = (i + 1); j < input.length(); j++) //start parsing at the given index where the first character is
			{
				if (input.at(j) == *" ") //if find a space, can determine the command text
				{
					stop = j;
					text = input.substr(start, (stop - start));
					stop_loops = true;
					break;
				}
				else if (j == input.length() - 1) //otherwise, if the loop parses to the end of the input string, then its either print, quit, or just garbage
				{
					if (input.substr(i, input.length() - i) == "print")
					{
						text = "print";
						stop_loops = true;
						break;
					}
					else if (input.substr(i, input.length() - i) == "quit")
					{
						text = "quit";
						stop_loops = true;
						break;
					}
				}
			}
		}
	}

	return text;
}


/*
	this function takes the user input string as a parameter
	and returns the digits found within the string
*/
int determine_digits(std::string str)
{
	std::string found_digits = "";
	for (int i = 0; i < str.size(); i++)
	{
		if (str.at(i) == *"\"")
		{
			break; //if find a " mark, passed all digits and dont want to get digits from text portion of command
		}
		if (str.at(i) < 58 && str.at(i) > 47) //get characters that are ascii digits
		{
			found_digits.push_back(str.at(i)); //append characters to string
		}
	}
	int digits = 0;
	int place = 1;
	//now have ascii characters, convert to decimal
	for (int i = found_digits.size() - 1; i >= 0; i--)
	{
		char ascii_dig = found_digits.at(i);
		int single_dig = ascii_dig - '0'; //convert to digit value
		digits = digits + (single_dig * place);
		place = place * 10;
	}
	return digits;

}

/*
	this function returns the text to be inputted into the linked list
	from the user input string
*/
std::string* determine_text(std::string str)
{
	std::string text;
	std::string body = "";
	int index_quote = -1;
	std::string *text_ptr = new std::string();
	int last_quote = -1;
	bool found_first = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (str.at(i) == *"\"" && !found_first) //parse till find the first quotation mark
		{
			index_quote = i;
			found_first = true;
		}
		else if (str.at(i) == *"\"") //find last quotation mark
		{
			last_quote = i;
		}
	}

	if (index_quote != -1)
	{
		text = str.substr(index_quote + 1, last_quote - index_quote - 1);
		*text_ptr = text;
	}
	else
	{
		text_ptr = nullptr;
	}
	return text_ptr;
}

int main()
{
	//get entire string 
	std::string input;

	//separate command from text data
	std::string command;
	std::string text;
	std::string split_text;
	int digits;

	List *document_list = new List();
	while (1)
	{
		std::string *text_ptr;
		std::getline(std::cin, input);
		command = determine_command(input);
		digits = determine_digits(input);
		digits = digits - 1; //this is due to the linked list being zero indexed and the output being 1 indexed
		text_ptr = determine_text(input);

			text = text.substr(0, 80); //cut message off at 80 characters
			if (command == "print")
			{
				document_list->print();
			}
			else if (command == "quit")
			{
				delete document_list;
				return 0;
			}
			else if (command == "insertEnd")
			{
				if (text_ptr != nullptr)
				{
					document_list->insertEnd(*text_ptr);
				}
			}
			else if (command == "insert")
			{
				if (text_ptr != nullptr)
				{
					document_list->insert(digits, *text_ptr);
				}
			}
			else if (command == "delete")
			{
				document_list->delete_index(digits);
			}
			else if (command == "edit")
			{
				document_list->edit(digits, *text_ptr);
			}
			else if (command == "search")
			{
				document_list->search(*text_ptr);
			}
			delete text_ptr; //since the determine_text function creates a new string object, delete this at the end of every command
	}

	return 0;
}