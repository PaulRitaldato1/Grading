#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <cctype>
using namespace std;

struct LinkedList
{
	struct Node
	{
		string data;
		Node* next;
	};

	enum Methods {INSERTEND, INSERT, DELETEAT, REPLACEAT, PRINT, SEARCH, ERROR};
	Node* head;
	Node* tail;
	int nodeCount;
	Methods functionToCall;

	LinkedList()
	{
		head = nullptr;
		tail = nullptr; // I didn't fully implement a tail pointer
		nodeCount = 0;
	}
	
	void insertEnd(string text) // insert at the end
	{
		Node* node = new Node;
		node->data = text;
		node->next = nullptr;

		if (head == nullptr)
		{
			tail = node;
			head = tail;
			tail->next = nullptr;
		}
		else if (head->next == nullptr)
		{
			head->next = node;
			node->next = nullptr;
			tail = node;
		}	
		else
		{
			tail->next = node;
			node->next = nullptr;
			tail = node;
		}
		this->nodeCount++;
	}

	void insert(int line, string text) // insert line at
	{
		if (nodeCount <= 0 || line > nodeCount + 1 || line <= 0)
		{
			return;
		}

		Node* current = head;
		Node* prev = head;
		Node* node = new Node;
		int i = 1;

		node->data = text;  
		if (line == 1)
		{
			node->next=head;
			head = node;
			this->nodeCount++;
		}
		else
		{
			while (i != line)
			{
				prev = current;
				current = current->next;
				i++;
			}
			node->next = current;
			prev->next = node;
			this->nodeCount++;
		}
		 return;
	}

	void deleteAt(int lineNum) // delete line at 
	{
		if (this->head == nullptr)
		{
			return;
		}

		int i = 1;

		Node* current  = head;
		Node* previous = current;

		while (i < lineNum)
		{
			previous = current;
			current  = current->next;
			i++;
		}

		if (current == nullptr)
			return;

		if (current == head)
		{
			head = current->next;
		}
		else
		{
			previous->next = current->next;
		}
		delete current;
		nodeCount--;
	}

	void replaceAt(int line, string text) // replace at
	{
		Node* current = head;
		int i;
		if (head == nullptr)
		{
			return;
		}

		if (line < 1 || line > nodeCount)
		{
			return;
		}

		for (i = 1; i < line; i++)
		{
			current = current->next;
		}
		if (line == i)
		{
			current->data = text;
		}
	}

	void print() // print document with line numbers
	{
		if (head == nullptr)
		{
			return;
		}

		int i = 1;
		Node* current = head;
		while (current != nullptr)
		{
			cout << i << " " << current->data << endl;
			current = current->next;
			i++;
		}
	}

	int search(string text) // print line and line number that contains text
	{
		int count = 1; 
		int result = -1;
		int foundLine = -1;
		bool foundIt = false;
		
		Node* current = head;
		
		while (current != nullptr)
		{
			int found = current->data.find(text);

			if (found != string::npos)
			{
				foundIt = true;
				cout << count << " " << current->data << endl;
				result = count;
				//count++;
			}
			current = current->next;
			count++;
		}
		// if not found, print "not found"
		if (foundIt == false)
		{
			cout << "not found" << endl;
		}
		return result;
	}

	void error() // used to let me know a useable function wasn't found 
	{
		//cout << "Error. No method to call" << endl;
	}

	string toLower(string& str) // turns the user input into lowercase
	{
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}

	Methods convert(string& str)
	{
		if (toLower(str) == "insertend") {return INSERTEND;}
		if (toLower(str) == "insert") {return INSERT;}
		if (toLower(str) == "delete") {return DELETEAT;}
		if (toLower(str) == "edit") {return REPLACEAT;}
		if (toLower(str) == "print") {return PRINT;} 
		if (toLower(str) == "search") {return SEARCH;}
		return ERROR;
	}

	bool findFunction(string& funcName) // finds a useable function
	{
		bool result = false;
		//string testName;
		//funcName >> testName;	
		
		this->functionToCall = convert(funcName);
		
		if (functionToCall != 7)
		{
			result = true;
		}
		return result;
	}
	
	void functionSwitcher(string words = "", int lineNum = 0) // makes the switch between useable functions
	{
		switch(this->functionToCall)
		{
			case INSERTEND:
				insertEnd(words);
				break;
			case INSERT:
				insert(lineNum, words);   
				break;
			case DELETEAT:
				deleteAt(lineNum);
				break;
			case REPLACEAT: 
				replaceAt(lineNum, words);
				break;
			case PRINT:
				print();
				break;
			case SEARCH:
				search(words);
				break;
			case ERROR:
				// error();
			default:
				break;
		}
	}

	void setLine(string& words, string& temp)  // removes quotes from the text being analyzed
	{

		if (ispunct(temp[0]))
		{
			temp = temp.substr(1, temp.size() - 1);
		}
		if (ispunct(temp[temp.size() - 1]))
		{
			temp = temp.substr(0, temp.size() - 1);
		}

		if (words.size() != 0)
		{
			words = words + " " + temp;
		}
		else 
		{
			words = temp;
		}
	}

	void userInput() // main method to get user input
	{
		string input = "";
		int i = 0; 
		//cout << "Enter line of text" << endl;
		getline(cin, input);
		
		while (input != "quit")
		{
			istringstream line;
			line.str(input);
			string words = "";
			string tempFuncName = "";
			string test = "";
			int lineNumber = 1;
			i = 0; 

			while (!line.eof())
			{
				if (i == 0 && (line >> tempFuncName))
				{
					findFunction(tempFuncName);
				}
				else if (line.fail())
				{
					string dummy;
					line >> dummy;
					line.clear();
					line.ignore();
					continue;
				}
				if (i == 1 && (line >> lineNumber))
				{
				//	cout << "line number is " << lineNumber << endl;
				}
				else if (line.fail())
				{
					setLine(words, test);
					line.clear();
				}
				if (i > 1 && (line >> test))
				{
					setLine(words, test);
				}
				else if (line.fail())
				{
					string dummy;
					line >> dummy;
					line.clear();
					line.ignore();
					continue;
				}
				i++;
			}
			//cout << "The words are " << words << endl;
			functionSwitcher(words, lineNumber);

			cin.clear();
			input.clear();
			//cout << "Enter line of text" << endl;
			getline(cin, input);
		}
	}
};

int main()
{
	LinkedList mylist;
	mylist.userInput();
}
