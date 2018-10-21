#include <iostream>
#include <string>

int capacity = 0;

struct node
{
	std::string text;
	node *next = nullptr;
	node *prev = nullptr;
}; 


class LinkedList
{
private:
	node *head;
	node *tail;
	node *tracker;

public:
	LinkedList();
	void insertEnd(std::string myText);
	void insert(int i, std::string myText);
	void deleteLine(int i);
	void edit(int i, std::string newText);
	void print();
	void search(std::string s);
};

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

void LinkedList::search(std::string s)
{
    // Initializaion of variables to keep track of values
	int counter = 1;
	tracker = head;
    bool found = false;
    
    // Main functionality to find if string contains substring
	while (tracker != nullptr)
	{
		std::string base = tracker->text;
		if (base.find(s) != std::string::npos) { 
			std::cout << counter << " " << base << std::endl;
            found = true;
		}
		tracker = tracker->next;
		++counter;
	}
    
    // If found was never triggered to be true, that means not at least one match was found
    if (!found)
        std::cout << "not found" << std::endl;
}

void LinkedList::insertEnd(std::string myText)
{
    // Insert text to the end of the list. Always increase capacity
	node *newNode = new node;
	newNode->text = myText;
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;	
	}
    capacity++;
}

void LinkedList::insert(int i, std::string myText)
{
    // Check if index is valid
	if (i <= capacity + 1)
	{
        // Initialize variables
		node *newNode = new node;
		newNode->text = myText;
		tracker = head;
		int counter = 1;
        
        // If index is 0 or 1, push the node to the front of the list
        if (i == 0 || i == 1)
		{
			newNode->next = tracker;
			head = newNode;
		}
		else
		{
			int counter = 1;
			while (counter != i - 1)
			{
				if (tracker->next == nullptr)
				{
					break;
				}
				tracker = tracker->next;
				counter++;
			}
            // If the next node is not NULL, then make connection. Else, the next node is NULL
			tracker->next != nullptr ? newNode->next = tracker->next : newNode->next = nullptr;
			tracker->next = newNode;
		}
		capacity++;
	}
}

void LinkedList::deleteLine(int i)
{
    // Validates if index is within range
	if (i <= capacity)
	{
		int counter = 1;
		tracker = head;
		while (counter != i - 1)
		{
			tracker = tracker->next;
			counter++;
		}
		tracker->next = tracker->next->next;
		capacity--;
	}
}

void LinkedList::edit(int i, std::string newText)
{
    // Validate if index i is within capacity
    if (i < capacity) {
        int counter = 1;
        tracker = head;
        while (counter != i)
        {
            tracker = tracker->next;
            counter++;
        }
        tracker->text = newText;
    }
}

void LinkedList::print()
{
	node *reader = head;
	int lineNumber = 1;
	while (reader != nullptr)
	{
		std::string checkLength = reader->text;
        // Do not print if the line is longer than 80 characters
		if (checkLength.size() < 80)
			std::cout << lineNumber << " " << reader->text << std::endl;
		reader = reader->next;
		lineNumber++;
	}
}

int main()
{
    LinkedList myList;
	std::string line;
	std::string command;
	std::string text;
	int index = 0;
    bool errorCheckQuote;

	while (command.compare("quit") != 0)
	{
        // Clear out the command and text for next iteration
		command.clear();
		text.clear();
		std::getline(std::cin, line);
		int i = 0;
        errorCheckQuote = false;
        index = 0;

		// Find the command
		while (i < line.length() && !isspace(line[i]))
		{
			command.push_back(line[i]);
			++i;
		
		}
	
		// Increment i until double quotations is reached, if double quotations exist.
		// Also obtain an index if there is a number between command and opening quotations
		while (i < line.length() && line[i] != '"')
		{
			if (isdigit(line[i]))
			{
				index = line[i] - 48;
			}
			++i;
		}
        
        // Increment i to skip including double quotation in text
        if(line[i] == '"') 
		    ++i;

		// Obtain the text within quotations
		while (i < line.length() && line[i] != '"')
		{
			text.push_back(line[i]);
			++i;
		}
        if(line[i] == '"')
            errorCheckQuote = true;
        // Invoking the commands
        if (command.compare("insertEnd") == 0 && errorCheckQuote)
            myList.insertEnd(text);
        else if (command.compare("insert") == 0 && errorCheckQuote)
            myList.insert(index, text);
        else if (command.compare("print") == 0)
            myList.print();
        else if (command.compare("search") == 0 && errorCheckQuote)
            myList.search(text);
        else if (command.compare("delete") == 0)
            myList.deleteLine(index);
        else if (command.compare("edit") == 0 && errorCheckQuote && index != 0)
            myList.edit(index, text);
	}
}