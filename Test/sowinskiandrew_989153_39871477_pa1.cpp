//I do not actually use all of these, I just like to include them
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
//NOTE ON PROGRAM STRUCTURE: It was unclear as to how this program should be created, other than that we had to use our own linked list to implement it
//As a result, I do not have a linked list class, but rather I maintain my linked list within the methods of the program. 
//The data is still stored, edited, and added to as a linked list, but it does not have its own class.
//I cleared this with prof. Resch on thursday and she said it was okay to structure my program like this.
using namespace std;

//Node class to make a linked list from scratch
class Node {
public:
	string value;
	Node* next = NULL;
};

//variables used in multiple methods, as well as two nodes
string input;
Node *head = new Node;
Node *last = head;
int txtLength;
bool stringError = false;

//method used multiple times throughout the program to take user input and turn it into a string
string getPhrase()
{
	//this section of the method gets the remaining part of the line to be checked for validity.
	string concat = "";
	getline(std::cin, concat);
	//the two if statements below check to see if the input is valid and throw an error bool if it is not
	if (concat.substr(1, 1) != "\"" || concat.substr(concat.length() - 1, 1) != "\"")
	{
		stringError = true;
	}
	concat = concat.substr(2, concat.length() - 3);
	if (concat.length() >= 81)
	{
		stringError = true;
	}
	return concat;
}

void insertEnd()
{
	//very basic method that takes the last element of the current list and directs it to the new node with the phrase inside of it
	string concat = getPhrase();
	if (stringError == true)
	{
		stringError = false;
		return;
	}
	Node *temp = new Node;
	temp->value = concat;
	last->next = temp;
	last = temp;
	txtLength++;
	//this textlength variable keeps track of how long the list is so we dont have to make a count method
}

//takes an input number, the phrase returned by getPhrase(), and inserts the phrase at the correct index number
void inserter()
{
	Node* p = new Node;
	Node* temp = new Node;
	int count = 0;
	p = head;
	string input;
	cin >> input;
	int insertDex = 0;
	//this try-catch ensures that bad user input will not crash the program
	try
	{
		insertDex = stoi(input);
	}
	catch (std::invalid_argument) {
		return;
	}

	if (insertDex == 1 && txtLength == 0)
	{
		insertEnd();
		return;
	}
	string concat = getPhrase();
	if (stringError == true)
	{
		stringError = false;
		return;
	}
	temp->value = concat;
	//list iterator to go through every element of the linked list, breaks out of the loop once the phrase has been added
	while (p != NULL)
	{
		if (count == insertDex - 1)
		{
			//basic linked list manipulation
			temp->next = p->next;
			p->next = temp;
			txtLength++;
			break;
		}
		++count;
		p = p->next;
	}
}

//prints all of the elements of the list (other than the hidden head) along with their line numbers
void printer()
{
	Node* p = new Node;
	int index = -1;
	int count = 1;
	p = head->next;
	while (p != NULL)
	{
		index = count;
		cout << to_string(count) + " " + p->value << '\n';
		++count;
		p = p->next;
	}
}

//deletes the element of the list at a given index, if the index is within range
void deleter()
{
	Node* p = new Node;
	int count = 0;
	p = head;
	string input;
	cin >> input;
	int deleteDex = 0;
	//this try-catch ensures that bad user input will not crash the program
	try
	{
		deleteDex = stoi(input);
	}
	catch (std::invalid_argument) {
		return;
	}

	//iterates through the list to find the correct node to delete
	while (p != NULL)
	{

		if (count == deleteDex - 1)
		{
			//If the last element is to be deleted, the previous node's "next" data has to be set to NULL
			if (deleteDex == txtLength + 1)
			{
				p->next = NULL;
				txtLength--;
			}
			//If the node being deleted is within the list, the previous element's "next" data is set to the node after the one being deleted
			else
			{
				//makes sure that a null pointer will not be thrown by an out of bounds call
				if (txtLength > 0)
				{
					p->next = p->next->next;
					txtLength--;
				}
				else
				{
					return;
				}
			}
			break;
		}
		++count;
		p = p->next;
	}
}

//iterates through the nodes, looking for one that contains the search. Returns the index and whole phrase if it is found, and "not found" if not
void searcher()
{
	Node* p = new Node;
	int index = -1;
	int count = 0;
	p = head;
	string concat = getPhrase();
	bool found = false;
	//linked list iterator
	while (p != NULL)
	{
		//if the search is found the output is printed and a variale is set to disbale the "not found" statement
		if (p->value.find(concat) != std::string::npos)
		{
			index = count;
			std::cout << to_string(count) + " " + p->value << '\n';
			found = true;
		}
		++count;
		p = p->next;
	}
	//not found statement
	if (found == false)
	{
		cout << "not found" << "\n";
	}
}

//The edit function is essentially a combination of the delete and insert functions, using identical sturcuture with slightly different node manipulation
void editer()
{
	//variables include various counts, the index that is being edited, the required nodes, and the phrase that is being inserted
	Node* p = new Node;
	Node* temp = new Node;
	int count = 0;
	p = head;
	string input;
	cin >> input;
	int editDex = 0;
	//this try-catch ensures that bad user input will not crash the program
	try
	{
		editDex = stoi(input);
	}
	catch (std::invalid_argument) {
		return;
	}
	string concat = getPhrase();
	if (stringError == true)
	{
		stringError = false;
		return;
	}
	temp->value = concat;

	//basic iterator that goes through the entire list unless broken
	while (p != NULL)
	{
		//if the index is not outside of the linkes list and the node is found, the new node is switched for the old one to make an "edit"
		if ((count == editDex - 1) && (editDex != txtLength + 1))
		{
			temp->next = p->next->next;
			p->next = temp;
			break;
		}
		++count;
		p = p->next;
	}
}

//continues to take user input in a loop until the program is quit
void looper()
{
	while (input != "quit")
	{
		//just a bunch of if statemnts to determine keywords
		cin >> input;

		if (input == "insertEnd") {
			insertEnd();
		}
		else if (input == "print") {
			printer();
		}
		else if (input == "delete") {
			deleter();
		}
		else if (input == "search") {
			searcher();
		}
		else if (input == "insert") {
			inserter();
		}
		else if (input == "edit") {
			editer();
		}
	}
}

//a very complicated main function, as you can see.
int main()
{
	looper();
	//did not include a return statemnt becasue I was told that it could cause problems for stepik
}