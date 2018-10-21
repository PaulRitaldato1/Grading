#include <string>
#include <iostream>

using namespace std;
//Node class for LL
class Data
{
public:
	string line;
	int lineNumber;
};
//Node class for LL
class Node
{
	public:
		Data data;
		Node* next;
};
//Linked List Class containing all of the necessary opperators for the text editor
class LinkedList
{
public:
	Node* head;
	int count = 0;
	bool first = true;
	//constructor creates the first node and the LL object
	LinkedList() {
		this->count = 1;
		Node* node = new Node();
		//this->head = node;
		//node->data.line = in;
		//node->data.lineNumber = 1;
		//node->next = NULL;
	}
	Node* findEnd();
	void addEnd(string data);
	bool addIndex(string data, int index);
	void updateLineNumbers(Node* current);
	bool deleteIndex(int LineNumber);
	bool editIndex(string data, int index);
	void print();
	void search(string data);
};
//Find pointer to the last Node, to set next when adding to the end
Node* LinkedList::findEnd()
{
	Node* current = this->head;
	Node* next = current->next;
	while (next != NULL)
	{
		current = next;
		next = current->next;
	}
	return current;
}
//add Node to the end of the LL
void LinkedList::addEnd(string data)
{
	Node* newNode = new Node();
	newNode->data.line = data;
	newNode->next = NULL;
	if (first)
	{
		this->head = newNode;
		newNode->data.lineNumber = 1;
		first = false;
		return;
	}
	//add 1 to line number of last entry, and add the variable to the new line number
	newNode->data.lineNumber= findEnd()->data.lineNumber + 1;
	findEnd()->next = newNode;
	this->count++;
	return;
}
//updating line numbers after index add, delete etc
void LinkedList::updateLineNumbers(Node* current)
{
	current = this->head;
	Node* next = current->next;
	current->data.lineNumber = 1;
	while (next != NULL)
	{
		next->data.lineNumber = current->data.lineNumber + 1;
		current = next;
		next = current->next;
	}
	//current->data.lineNumber = next->data.lineNumber + 1;
}
//add Node at index of the LL returns true if successful
bool LinkedList::addIndex(string data, int index)
{
	//return false if out of range;
	if (index > count && index < 1)
		return false;
	Node* current = this->head;
	Node* next = current->next;
	//if index==1 update head
	if (index == 1)
	{
		Node* newNode = new Node();
		//define new node data
		newNode->data.line = data; 
		if (first)
		{
			this->head = newNode;
			newNode->data.lineNumber = 1;
			first = false;
			return true;
		}
		//new node next is head
		newNode->next = this->head;
		//newNode is the new Head
		this->head = newNode;
		updateLineNumbers(current);
		count++;
		return true;
	}
	for (int i = 0; i < index-2; i++)
	{
		current = next;
		next = current->next;
	}
	Node* newNode = new Node();
	//define new node data
	newNode->data.line = data;
	//new node next is previous next
	newNode->next = current->next;
	//previous nodes next is new Node
	current->next = newNode;
	updateLineNumbers(current);
	count++;
	return true;
}
//edit data at line Number return false if out of range
bool LinkedList::editIndex(string line, int lineNumber)
{
	//check if out of range
	if (lineNumber > count || lineNumber < 1)
		return false;
	//init temp Nodes
	Node* current = this->head;
	Node* next = current->next;
	//find Node where data.lineNumber == lineNumber
	while (current->data.lineNumber != lineNumber)
	{
		current = next;
		next = current->next;
	}
	//edit the line
	current->data.line = line;
	return true;
}
//print all entries in the LL
bool LinkedList::deleteIndex(int lineNumber)
{
	if (lineNumber > count || lineNumber < 1)
		return false;
	//init temp Nodes
	Node* current = this->head;
	Node* next = current->next;
	//delete head
	if (lineNumber == 1)
	{
		this->head = next;
		updateLineNumbers(this->head);
		return true;
	}
	
	//find Node where data.lineNumber == lineNumber
	while (current->data.lineNumber != lineNumber-1)
	{
		current = next;
		next = current->next;
	}
	//handles last node exception
	if (count==lineNumber)
	{
		current->next = NULL;
		return true;
	}
	//"delete" the line, set currents next to the following node
	current->next = next->next;
	updateLineNumbers(current);
	return true;
}
void LinkedList::search(string search)
{
	Node* current = this->head;
	Node* next = current->next;
	while (next != NULL)
	{
		if (current->data.line.find(search) != string::npos)
		{
			cout << current->data.lineNumber << " " << current->data.line << endl;
			return;
		}
		current = next;
		next = current->next;
	}
	//checking if found in last entry
	if (current->data.line.find(search) != string::npos)
	{
		cout << current->data.lineNumber << " " << current->data.line << endl;
		return;
	}
	return;
}
void LinkedList::print()
{
	Node* current = this->head;
	Node* next = current->next;
	//while not last entry print out entry
	while (next != NULL)
	{
		cout<<current->data.lineNumber <<" "<< current->data.line<<endl;
		current = next;
		next = current->next;
	}
	//print the last entry when next=NULL
	cout << current->data.lineNumber << " " << current->data.line<<endl;
}



int main()
{
	LinkedList* list = new LinkedList();
	bool first = false;
	string input,opcode;
	int index;
	while (opcode != "quit")
	{
		std::getline(cin, input);
		opcode = input.substr(0, input.find(' '));
		input = input.substr(input.find(' ')+1);
		if (opcode == "insertEnd")
		{
			list->addEnd(string(input).substr(1,string(input).length()-2));
		}
		else if (opcode == "insert")
		{
			index = stoi(input.substr(0, input.find(' ')));
			input = input.substr(input.find(' ') + 1);
			list->addIndex(string(input).substr(1, string(input).length() - 2), index);
		}
		else if (opcode == "delete")
		{
			index = stoi(input);
			list->deleteIndex(index);
		}
		else if (opcode == "search")
		{
			list->search(string(input).substr(1, string(input).length() - 2));
		}
		else if (opcode == "edit")
		{
			index = stoi(input.substr(0, input.find(' ')));
			input = input.substr(input.find(' ') + 1);
			list->editIndex(string(input).substr(1, string(input).length() - 2), index);
		}
		else if (opcode == "print")
		{
			list->print();
		}
	}
	
    return 0;
}

