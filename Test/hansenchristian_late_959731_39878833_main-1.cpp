/*
 * 
 * Line Editor with Linked Lists
 * 
 * by Christian Hansen
 * 
 */

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

//creates Node
class node 
{
	public:
	node* next;
	string content = "";
};

class list 
{
	public:
    node* head;
    node* tail;
    
    //inserts text at given position
	void insert(string text, int position) 
	{
		node* prev = head;
		node* temp = head;
		node* newNode = new node;
		newNode->content = text;
		
		if (head == NULL) 
		{
			head = newNode;
			tail = head;
			return;
		}
		
		for (int i = 1; i < position; i++) 
		{
			if (temp == NULL)
				return;
			prev = temp;
			temp = temp->next;
		}
		
		if(temp == head) 
		{
			newNode->next = temp;
			head = newNode;
			return;
		}
		
		if(temp == tail) 
		{
			prev->next = newNode;
			newNode->next = temp;
			tail = temp;
			return;
		}
		
		prev->next = newNode;
		newNode->next = temp;
		
		return;
	}
	
	//function to delete Line
	void deleteLine(int position, int listSpot) 
	{
		if (head == NULL) 
			return;

		if (position-1 == 0 && head->next == NULL) 
		{
			head = NULL;
			return;
		} 
		
		else if (position-1 == 0 && head->next != NULL) 
		{
			head = head->next;
			return;
		}
		
		node* temp = head;
		node* prev = head;
		for (int i = 1; i < position; i++) 
		{
			if (temp == NULL)
				return;
			prev = temp;
			temp=temp->next;
		}
	 
		if (temp == tail) 
		{
			tail = prev;
			prev->next = NULL;
			return;
		}
		
		node* post = temp->next;
		prev->next = post;
		return;
    }
    
    //adds node
	void addNode(string text, int position) 
	{
		node* newNode = new node;
		newNode->content = text;
			
		if (head == NULL) 
		{
			head = newNode;
			tail = head;
			return;
		}
		
		node* temp = head;
		while (temp != tail) 
		{
			temp = temp->next;
		}
		
		temp->next = newNode;
		temp= temp->next;
		tail = temp;
		return;
    }
    
    //edits text at given line
	void edit(int line, string text) 
	{
		if (head == NULL)
			return;
		node* temp = head;
		for (int i = 0; i < line-1; i++) 
		{
			if (temp == NULL) 
				return;
			temp = temp->next;
		}
		temp->content = text; 
    }
    
    //prints entire document
	void print() 
	{
		int line = 0;
		if (head == NULL) 
			return; 
		
		else
		{	
			node* temp = head;
			while (temp != NULL) 
			{
				line++;
				cout << line << " " << temp->content << endl;
				temp = temp->next;
			}
		}
    }
    
    //searches for text
	void search(string text) 
	{
		bool notFound = true;
		int line = 0;
		if (head == NULL) 
		{
			cout << "not found" << endl;
			return;
		}
		
		node* temp = head;
		while(temp!= NULL) 
		{
			line++;
			
			size_t found = temp->content.find(text);
			if (found!=std::string::npos)
			{
				cout << line << " " << temp->content << endl;
				notFound = false;
			}
			
				
			temp = temp->next;
		}
		if (notFound)
			cout << "not found" << endl;
		return;
    }
};

list *document = new list();

//checks that a command is in quotation marks
string checkInput(string text) 
{
    string temp = "";
    if (text.front() != 34 || text.back() != 34) 
        return "";
    else
    {	
        for (int i = 0; i < text.length(); i++) 
        {
            if (text[i] != '"')
                temp.push_back(text[i]);
        }
	}
    text = temp;
    return text;
}

//makes sure a line is given
int checkLine(string text) 
{
    int j = 0;
    int e = 0;
    int newNum = 0;
    int r = 0;
    
    for (int i = 0; i < text.length(); i++) 
    {
        int temp = (int) text[i];
        if (temp < 58 && temp > 47) 
        {
            j += (temp - 48) * pow(10, e);
            e++;
        }
        if (text[i] == '"') 
        {
            while(j != 0)
            {
                r = j % 10;
                newNum = newNum * 10 + r;
                j /= 10;
            }
            return newNum; 
        }
    }
    while(j != 0)
    {
        r = j % 10;
        newNum = newNum * 10 + r;
        j /= 10;
    }
    return newNum;
}

//breaks up command and text
string breakCommand(string text) 
{
    for (int i = 0; i < text.length(); i++) 
    {
        if (text[i] == '"') 
        {
			text = text.substr(i, text.length()-i);
			return text; 
        }
    }
    return text;
}

//main method
int main() 
{
    string input; 
    int lineChoice = 0;
    int listSpot = 0;
    while (getline(cin, input)) 
    {
        string receivedCommand = "", text = "";
        for (int i = 0; i < input.length(); i++)
        {
            if (isspace(input[i])) 
            {
                receivedCommand = input.substr(0,i);
                text = input.substr(i+1, input.length()-(i+1));
                break;
            }
            
        }
        
        if (receivedCommand.empty())
        receivedCommand = input;

		//long process that converts commands to choices for case switch
		int choice = -1;
		if (receivedCommand == "insertEnd")
			choice = 0;
		else if (receivedCommand == "insert")
			choice = 1;
		else if (receivedCommand == "delete")
			choice = 2;
		else if (receivedCommand == "edit")
			choice = 3;
		else if (receivedCommand == "print")
			choice = 4;
		else if (receivedCommand == "search")
			choice = 5;
		else if (receivedCommand == "quit")
			choice = 6;


		//case switch for commands
		switch(choice) 
		{
			case 0:
				text = checkInput(text);
				if (!text.empty()) 
				{
					listSpot++;
					document->addNode(text, listSpot); 
				}
				break; 
			case 1:
				lineChoice = checkLine(text);
				text = breakCommand(text);
				text = checkInput(text);
				if (!text.empty())
				{
					document->insert(text, lineChoice);
					listSpot++;
				}
				break;
			case 2:
				lineChoice = checkLine(text);
				if (lineChoice <= listSpot) 
				{
					document->deleteLine(lineChoice, listSpot);
					listSpot--; 
				}
				break;
			case 3:
				lineChoice = checkLine(text);
				text = breakCommand(text);
				text = checkInput(text);
				if (!text.empty())
					document->edit(lineChoice, text);
				break;
			case 4:
				document->print();
				break;
			case 5:
				text = checkInput(text);
				if (!text.empty())
					document->search(text);
				break;
			case 6:
				exit(1);
				break;
			default:
				break;
				
		}
    }
    return 0;
}



