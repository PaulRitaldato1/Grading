#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class lineEdit
{
private:
	struct node
	{
		string data;
		node *next;
	};

public:
	int pos = 1;
	node *head = new node;
	node *tail = new node;
	lineEdit()
	{
		head = NULL;
		tail = NULL;
	}
	//methods
	void insert(int index, string text);
	void insertEnd(string text);
	void deleteAt(int index);
	void editText(int index, string text);
	void print(node *head);
	void searchText(node *p, string text);
};

void lineEdit::insert(int index, string text)
{
	//insert given text at the line indicated by index given
	if (index == 1)
	{
		node *temp = new node;
		temp->data = text;
		temp->next = head;
		head = temp;
	}
	else
	{

		node *curr = new node;
		node *prev = new node;
		node *temp = new node;
		curr = head;
		for (int i = 1; i < index; i++)
		{
			if (curr == NULL)
			{
				return;
			}
			prev = curr;
			curr = curr->next;
		}
		temp->data = text;
		prev->next = temp;
		temp->next = curr;
	}
}

void lineEdit::insertEnd(string text)
{
	//insert given text at the end of the document
	node *temp = new node;
	temp->data = text;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void lineEdit::deleteAt(int index)
{

	// delete line at index given
	if(index == 1)
	{
		node *temp = new node;
		temp = head;
		head = head->next;
		delete temp;
	}
	else
	{
		node *curr = new node;
		node *prev = new node;


		curr = head;
		for (int i = 1; i < index; i++)
		{
			if (curr == NULL)
			{
				return;
			}
			prev = curr;
			curr = curr->next;
		}
		if (curr == NULL)
		{
			return;
		}
		prev->next = curr->next;
	}
}

void lineEdit::editText(int index, string text)
{
	//replace the line at the index given with the given text
	deleteAt(index);
	insert(index, text);
}

void lineEdit::print(node *head)
{
	int count = 1;
	//print the entire document, with line numbers
	while (head)
	{
		cout << count << " " << head->data << "\n";
		head = head->next;
		count++;
	}

}

void lineEdit::searchText(node *head, string text)
{
	pos = 1;
	bool test = true;
	while (head != NULL)
	{
		if (head->data == text || head->data.find(text) != -1)
		{
			cout << pos << " " << head->data << "\n";
			test = false;
		}
		head = head->next;
		pos++;
	}

	if (test == true)
	{
		cout << "not found\n";
	}

}

int main()
{
	lineEdit doc1;
	
	string input;
	while (input != "quit")
	{
		getline(cin, input); //getting input
		//Variables
		string command = "";
		string number = "";
		string text = "";
		int num = 0;
		
		// For loop to get the command
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] != ' ')
			{
				command += input[i];
			}
			else
				break;
		}
		// For loop to get the number
		for (int i = command.length()+1; i < input.length(); i++)
		{
			if (command == "insertEnd" || command == "search")
				break;
			if (input[i] != ' ')
			{
				number += input[i];
			}
			else
				break;
		}
		// For loops to get the text
		if(command == "insertEnd" || command == "search")
			for (int i = command.length() + number.length() + 2; i < input.length(); i++)
			{
				if (input[i] != '"')
				{
					text += input[i];
				}
				else
					break;
			}
		else
			for (int i = command.length() + number.length() + 3; i < input.length(); i++)
		{	
			if (input[i] != '"')
			{
				text += input[i];
			}
			else
				break;
		}
		
		//checking for correct input
		//cout <<"command: " <<command << " number: " << number << " text: " << text << "\n";
		
		//selextion if statement
		if (command == "insert")
		{
			num = stoi(number);
			doc1.insert(num, text);
		}
		else if(command == "insertEnd")
		{
			doc1.insertEnd(text);
		}
		else if (command == "delete")
		{
			num = stoi(number);
			doc1.deleteAt(num);
		}
		else if (command == "edit")
		{
			num = stoi(number);
			doc1.editText(num, text);
		}
		else if (command == "print")
		{
			doc1.print(doc1.head);
		}
		else if (command == "search")
		{
			doc1.searchText(doc1.head,text);
		}

	}

}
