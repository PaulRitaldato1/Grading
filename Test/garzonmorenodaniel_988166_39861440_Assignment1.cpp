// Assignment1.cpp : node struct, linked list implementation, and main function tailored to specifications
// Author: Daniel Garzon Moreno
// COP3530
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <vector>


/*
	Created a struct node with two data points: lineNumber and phrase
	Each node will have reference to its next node (singly)
*/
struct Node 
{
	std::string phrase;
	int lineNumber;
	Node* next = NULL;
};

/*
	List definition: insert, insertEnd, erase, edit, search, and print defined below in implementation
	Note: getSize() is only used for logic in main method
*/
class LList 
{
	//Instance variable holding the first node of list
	Node* head;

	public:
		LList();
		void insertEnd(std::string phrase);
		void insert(int lineNumber, std::string phrase);
		void erase(int lineNumber);
		void edit(int lineNumber, std::string newSentence);
		bool search(std::string portion);
		int getSize();
		void print();

};

//List constructor
LList::LList()
{
	head = NULL;
}

//returns the size of the linked list by iterating and adding one to a counter variable
int LList::getSize() 
{
	int size = 0;
	Node* current = head;

	while (current != NULL) 
	{
		size++;
		current = current->next;
	}

	return size;
}

//insertEnd implementation
void LList::insertEnd(std::string sentence)
{
	int counter = 1;
	Node* current = head;
	Node* addNode = new Node();
	addNode->phrase = sentence;

	//Special case: if list is empty, make new node the head of the list
	if (current == NULL) 
	{
		addNode->next = head;
		addNode->lineNumber = counter;
		head = addNode;
	}

	//general case: iterate through list until we find last node of list
	//Add node to end and make it point to NULL
	//Note: addNode's line number is simply the current node in the iteration + 1
	else 
	{
		while (current != NULL)
		{
			if (current->next == NULL)
			{
				current->next = addNode;
				addNode->next = NULL;
				addNode->lineNumber = current->lineNumber + 1;
				return;
			}
			current = current->next;
		}
	}
}

//Insert implementation
void LList::insert(int lineNumber, std::string phrase)
{
	Node* addNode = new Node();
	addNode->lineNumber = lineNumber;
	addNode->phrase = phrase;

	//Special case: when I insert node as head node
	if (lineNumber == 1) 
	{
		addNode->next = head;
		head = addNode;
	}

	//General case: iterate up to lineNumber, save the previous node and the next node
	//insert between both and make sure previous points to add node and add node points to next node
	else
	{
		Node * current = head;
		Node * pre = new Node();

			for (int i = 1; i < lineNumber; i++)
			{
				pre = current;
				current = current->next;
			}

			pre->next = addNode;
			addNode->next = current;
		
	}

	//Simply iterate through and add one to anything greater than or equal to line number
	//Note: don't add one to addNode
	Node * it = head;

	while(it != NULL)
	{	
		if (addNode->lineNumber <= it->lineNumber && it != addNode) 
		{
			it->lineNumber = it->lineNumber + 1;
		}

		it = it->next;
	}
}

//Erase implementation
void LList::erase(int lineNum)
{
	Node * current = new Node();
	Node * previous = new Node();

	current = head;

	//Special case: erasing head
	//Make sure to point head to current->next
	if (lineNum == 1)
	{
		current->next = head->next;
		head = current->next;
	}

	//General case: iterate up to the node you wanna erase and set its previous node to point to the node after the one we're erasing
	else
	{
		for (int i = 1; i < lineNum; i++)
		{
			previous = current;
			current = current->next;
		}

		previous->next = current->next;
	}

	//simply decrements anything greater than or equal to the line number
	Node * it = head;
	while (it != NULL) 
	{
		if (it->lineNumber >= lineNum) 
		{
			it->lineNumber--;
		}
		it = it->next;
	}	
}

//Edit implementation
void LList::edit(int lineNumber, std::string newSentence)
{
	Node* current = head;
	
	//Iterate through linked list and when I find the node I want to edit I set the phrase the the newSentence
	while (current != NULL) 
	{
		if (current->lineNumber == lineNumber)
		{
			current->phrase = newSentence;
			return;
		}
		current = current->next;
	}
}

//Search implementation
bool LList::search(std::string portion)
{
	Node* current = head;
	int counter = 0;

	//iterating through the list I use the find function to check whether I've found a subset or identical match to the portion of a phrase passed in
	while(current != NULL) 
	{
		std::size_t pos = current->phrase.find(portion);

		//find returns a position which should not equal to npos and if this is true, I print the line containing the portion
		//Note: I keep a counter in case to not find anything trigger a method variable defined above
		if (pos != std::string::npos) 
		{
			std::cout << current->lineNumber << " " << current->phrase << std::endl;
			counter++;
		}

		current = current->next;
	}

	if (counter > 0) 
	{
		return true;
	}
	//print out in case nothing is found
	else 
	{
		std::cout << "not found" << std::endl;
		return false;
	}
}

//print implementation
void LList::print()
{
	Node* current = head;

	//iterate through linked list and print line number followed by phrase
	while (current != NULL) 
	{
		std::cout << current->lineNumber << " " << current->phrase << std::endl;

		current = current->next;
	}

}



int main()
{

	//create a phrase linked list and user input string
	LList * phraseList = new LList();

	std::string userInput;

	do
	{
		std::string command;
		std::string phrase;
		std::string temp;
		int lineNum;
		int counter = 0;

		//using getline and stringstream I tokenize each part of the input respective to the command
		getline(std::cin, userInput);
		std::stringstream ss(userInput);
		ss >> command;

		//print command is not followed by a line number or phrase so I skip this
		if (command.compare("print") != 0)
		{
			//extract the line number for commands that require such parameter
			if (command.compare("insert") == 0 || command.compare("edit") == 0 || command.compare("delete") == 0)
			{
				ss >> lineNum;
			}

			//concatenate rest of the tokens into a string temp value
			while (!ss.eof())
			{
				if (counter == 0)
				{
					ss >> temp;
					phrase = phrase + temp;
				}
				else
				{
					ss >> temp;
					phrase = phrase + " " + temp;
				}
				counter++;
			}
			
			//Check for balance quotation marks in order to actually save the phrase
			int quoteCount = 0;
			int i = 0;

			while (i < phrase.length() && phrase.length() > 0)
			{
				if (phrase.at(i) == '\"') 
				{
					quoteCount++;
				}
				
				i++;
			}

			// only command without a need of a phrase is delete and print (print already taken care of)
			//Note: if there's only 0 or 1 quotes, I continue loop and ask for input againq
			if (command.compare("delete") != 0) 
			{
				if (quoteCount <= 1) 
				{
					continue;
				}
			}

			//using this erase algorithm from the <algorithm> include, I remove the quotes from the phrase
			phrase.erase(
				remove(phrase.begin(), phrase.end(), '\"')
				, phrase.end());
		}

		//call method for respective command

		if (command.compare("insert") == 0)
		{
			//taking care of out of bounds calls
			if (phraseList->getSize() < lineNum && (phraseList->getSize() + 1 != lineNum))
			{
				continue;
			}
			phraseList->insert(lineNum, phrase);
		}
		else if (command.compare("insertEnd") == 0)
		{
			phraseList->insertEnd(phrase);
		}
		else if (command.compare("print") == 0)
		{
			phraseList->print();
		}
		else if (command.compare("edit") == 0) 
		{
			phraseList->edit(lineNum, phrase);
		}
		else if (command.compare("search") == 0)
		{
			phraseList->search(phrase);
		}
		else if (command.compare("delete") == 0)
		{
			//taking care of out of bounds call
			if (phraseList->getSize() < lineNum)
			{
				continue;
			}
			phraseList->erase(lineNum);
		}
	}
	 while (userInput.compare("quit") != 0);

	return 0;

}