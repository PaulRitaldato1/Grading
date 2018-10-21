#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

// class Node
struct Node 
{
	string data;
	int index;
	Node* nextNode;

	// constructer
	Node(string newData, int newIndex)
	{
		data = newData;
		nextNode = nullptr;
		index = newIndex;
	}

	void PrintNode()
	{
		cout << index << " " << data << "\n";
	}

};


class LinkList
{
// Internal List
private:
	// computational complexity is O(1)
	bool AddNode(Node* newNodePointer)
	{
		int counter = 1;
		// check to see if the list is empty
		if (head->nextNode == nullptr)
		{
			head->nextNode = newNodePointer;
			end = newNodePointer;
			head->index = counter;
			end->index = counter;

		}

		else if(head == end)
		{
			int index = end->index;
			end = newNodePointer;
			head->nextNode = end;
			end->index = index + 1;
		}

		// walk the last and find last node
		else
		{
			int index = end->index;

			end->nextNode = newNodePointer;
			end = newNodePointer;
			end->index = index + 1;
		}

		return true;
	}

// Public functions used by main
public:
	Node* head;
	Node* end;

	LinkList()
	{
		head = new Node("rootNode", 0);
	}

	// calls the private addNode function to add the node to the end of the list
	bool AddNode(string newData)
	{
		Node* newNodePointer = new Node(newData, 0);
		bool success = AddNode(newNodePointer);
		return success;
	}

	// computational complexity is O(n)
	// iterates through the list looking for the data
	bool FindNode(string data)
	{
		bool isFound = false;
		Node* currentPointer = head;
		while (currentPointer != nullptr)
		{
			string currentData = currentPointer->data;
			bool stringFound = (currentData.find(data) != string::npos);
			if (stringFound)
			{
				currentPointer->PrintNode();
				isFound = true;
			}
			currentPointer = currentPointer->nextNode;
		}
		if (!isFound)
		{
			cout << "not found\n";
		}
		return isFound;
	}

	// computational complexity is O(n)
	// iterates through the list looking for the matching index to edit the node
	bool EditNode(int nodeIndex, string newData)
	{
		Node* currentPointer = head;
		while (currentPointer != nullptr)
		{
			if (currentPointer->index == nodeIndex)
			{
				currentPointer->data = newData;
				return true;
			}
			currentPointer = currentPointer->nextNode;
		}
		return false;
	}

	// computational complexity is O(n)
	// iterates through the list looking for the matching index to removed the Node
	bool RemoveNode(int nodeIndex)
	{
		Node* currentPointer = head;
		while (currentPointer != nullptr)
		{
			Node* lastPointer = currentPointer;
			currentPointer = currentPointer->nextNode;
			if (currentPointer != nullptr && currentPointer->index == nodeIndex)
			{
				lastPointer->nextNode = currentPointer->nextNode;
				delete currentPointer;
				RenumberIndicies();
				return true;
			}
		}
		return false;
	}

	// computational complexity is O(n)
	// iteratates through the list to renumber the indicies
	void RenumberIndicies()
	{
		Node* currentPointer = head->nextNode;
		Node* lastPointer = head;
		int i = 1;
		while (currentPointer != nullptr)
		{
			currentPointer->index = i;
			i++;
			lastPointer = currentPointer;
			currentPointer = currentPointer->nextNode;
		}
	}

	// computational complexity is O(n)
	// iterates through the list looking for the correct index to insert Node
	bool InsertNode(int nodeIndex, string newData)
	{
		int i = 1;
		Node* currentPointer = head->nextNode;
		Node* lastPointer = head;
		bool inserted = false;

		while (currentPointer != nullptr)
		{
			i++;
			if (inserted)
			{
				currentPointer->index++;
			}
			else if (currentPointer->index == nodeIndex)
			{
				Node* newNodePointer = new Node(newData, nodeIndex);
				lastPointer->nextNode = newNodePointer;
				newNodePointer->nextNode = currentPointer;
				currentPointer->index++;
				inserted = true;
			}
			else if (currentPointer->nextNode == nullptr && nodeIndex == i)
			{
				AddNode(newData);
				return true;
			}
			lastPointer = currentPointer;
			currentPointer = currentPointer->nextNode;
			
		}
		return inserted;
	}

	// computational complexity is O(n)
	// it traverses printing each node
	void PrintList()
	{
		Node* currentPointer = head->nextNode;
		while (currentPointer != nullptr)
		{
			currentPointer->PrintNode();
			currentPointer = currentPointer->nextNode;
		}
	}
};

// used to find user commands
class StringParser
{
	char* workingString;
	int workingLength;
public:
	StringParser(string input)
	{
		workingString = new char[input.length() + 1];
		strcpy(workingString, input.c_str());
		workingLength = input.length();
	}

	// computational complexity is O(n)
	// gets the first string command
	string GetFirstWord()
	{

		int counter = 0;
	for (int i = 0; i < workingLength; i++)
	{
		if (isspace(workingString[i]))
		{
			counter = i;
			break;
		}
	}

	if (counter == 0 && workingLength < 10)
	{
		return workingString;
	}

	char temp[10];
	strncpy(temp, workingString, counter);
	temp[counter] = '\0';
	string newString(temp);
	return newString;
	}

	// computational complexity is O(n)
	// used to grab the data
	string GetStringArgument()
	{
		bool foundFirst = false;
	int firstQuote = 0;
	int secondQuote = 0;
	for (int i = 0; i < workingLength; i++)
	{
		if (workingString[i] == '\"')
		{
			if (!foundFirst)
			{
				firstQuote = i;
				foundFirst = true;
			}
			else
			{
				secondQuote = i + 1;
				break;
			}
		}
	}
	int length = secondQuote - firstQuote;
	string newString(workingString);
	string temp = newString.substr(firstQuote, length);

	return temp;

	}

	// computational complexity is O(n)
	// used to grab the data
	string GetStringArgumentNoQuote()
	{
		bool foundFirst = false;
	int firstQuote = 0;
	int secondQuote = 0;
	for (int i = 0; i < workingLength; i++)
	{
		if (workingString[i] == '\"')
		{
			if (!foundFirst)
			{
				firstQuote = i + 1;
				foundFirst = true;
			}
			else
			{
				secondQuote = i;
				break;
			}
		}
	}
	int length = secondQuote - firstQuote;
	string newString(workingString);
	string temp = newString.substr(firstQuote, length);
	return temp;
	}

	// computational complexity is O(n)
	// used to find the index int argument for the user command 
	int GetIntArgument()
	{
		bool foundFirst = false;
	int firstSpace = 0;
	int secondSpace = 0;
	for (int i = 0; i < workingLength; i++)
	{
		if (workingString[i] == ' ')
		{
			if (!foundFirst)
			{
				firstSpace = i + 1 ;
				foundFirst = true;
			}
			else
			{
				secondSpace = i;
				break;
			}
		}
	}
	int length = secondSpace - firstSpace;
	string newString(workingString);
	string temp = newString.substr(firstSpace, length);
	int retInt = -1;
	stringstream convert(temp);
	convert >> retInt;
	return retInt;
	}
};

int main()
{
	string userInput;
	LinkList lineList;

	// keeps looping until the word quit is found
	while (userInput.compare("quit") != 0)
	{
		getline(cin, userInput);

		// used to parse the command
		StringParser inputParser(userInput);
		string firstWord = inputParser.GetFirstWord();

		if (firstWord == "insertEnd")
		{
			string secondWord = inputParser.GetStringArgumentNoQuote();
			lineList.AddNode(secondWord);
		}
		if (firstWord == "print")
		{
			lineList.PrintList();
		}
		if (firstWord == "edit")
		{
			int catchNum = inputParser.GetIntArgument();
		}
		if (firstWord == "search")
		{
			string secondWord = inputParser.GetStringArgumentNoQuote();
			lineList.FindNode(secondWord);
		}
		if (firstWord == "edit")
		{
			int catchNum = inputParser.GetIntArgument();
			string secondWord = inputParser.GetStringArgumentNoQuote();
			lineList.EditNode(catchNum, secondWord);
		}
		if (firstWord == "insert")
		{
			int catchNum = inputParser.GetIntArgument();
			string secondWord = inputParser.GetStringArgumentNoQuote();
			lineList.InsertNode(catchNum, secondWord);
		}
		if (firstWord == "delete")
		{
			int catchNum = inputParser.GetIntArgument();
			lineList.RemoveNode(catchNum);
		}
	}
}