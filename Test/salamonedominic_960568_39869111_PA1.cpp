//Dominic Salamone

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Node
{
	string line;
	Node* next;
};

class LinkedList
{
	private:
		int size;
		Node *head;
		Node *tail;

	public:
		LinkedList()
		{
			init();
		}

		void init()
		{
			size = 0;
			head = NULL;
			tail = NULL;
		}

		void insert(int lineNumber, string line)
		{
			Node* current = head;
			Node* prev = head;
			Node* temp = new Node();
			
			temp->line = line;

			if(lineNumber > size + 1)
				return;

			if(lineNumber == 1)
			{
				head = temp;
				head->next = current;
			}
			
			else
			{
				for(int i = 1; i < lineNumber; i++)
				{
					prev = current;
					current = current->next;
				}

				prev->next = temp;
				temp->next = current;

			}

			size++;		
		}

		void insertEnd(string line)
		{
			Node* temp = new Node();
			temp->line = line;

			if(tail == NULL)
			{
				head = temp;
				tail = temp;
			}
			else
			{
				tail->next = temp;
				tail = temp;
			}

			temp->next = NULL;
			size++;
		}

		void deleteLine(int lineNumber)
		{ 
			Node* prev = head;  
			Node* current = head;

			if(lineNumber > size)
				return;

			for(int i = 1; i < lineNumber; i++)
			{
				prev = current;
				current = current->next;
			}

			Node* temp = current;
			prev->next = current->next;
			delete temp;
			size--;
		}

		void edit(int lineNumber, string line)
		{
			Node* current = new Node();
			current = head;

			for(int i = 1; i < lineNumber; i++)
			{
				current = current->next;
			}

			current->line = line;
		}

		void print()
		{
			Node* current = head;

			if(size == 0)
				return;

			for(int i = 1; i <= size; i++)
			{
				cout << i << " " << current->line << endl;
				current = current->next;
			}
		}

		void search(string search)
		{
			Node* current = head;
			int i = 1;
			bool found = false;

			while(current != NULL)
			{
				if(current->line.find(search) != string::npos)
				{
					cout << i << " " << current->line << endl;
					found = true;
				}

				current = current->next;
				i++;
			}

			if(!found)
				cout << "not found" << endl;
		}
};

int main()
{
	string command = "";
	string line = "";

	LinkedList document;

	int lineNumber = 0;

	while(command != "quit")
	{
		cin >> command;

		if(command == "insert" || command == "delete" || command == "edit")
			cin >> lineNumber;

		getline(cin, line);

		if(command == "insertEnd")
		{
			line = line.substr(2, line.size() - 3);
			document.insertEnd(line);
		}

		else if(command == "insert")
		{
			line = line.substr(2, line.size() - 3);
			document.insert(lineNumber, line);
		}

		else if(command == "delete")
		{
			document.deleteLine(lineNumber);
		}

		else if(command == "edit")
		{
			line = line.substr(2, line.size() - 3);
			document.edit(lineNumber, line);
		}

		else if(command == "print")
		{
			document.print();
		}

		else if(command == "search")
		{
			line = line.substr(2, line.size() - 3);
			document.search(line);
		}
	}

	return 0;
}