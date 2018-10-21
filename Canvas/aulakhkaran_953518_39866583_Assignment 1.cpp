#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/******** LIST CLASS ********/
class list
{
	struct node
	{
	 	std::string line;
	 	node* next;
	};

	private:
		node* head;
		node* tail;
		int size;

	public:
		list():head(NULL), size(0) {}
		void insertEnd(string line)
		{
			size++;
			node* tmp = new node;
			tmp->line = line;

			if (!head)
			{
				head = tmp;
				tail = tmp;
			}
			else
			{
				tail->next = tmp;
				tail = tmp;
			}			
		}
		bool insert(int lineNumber, string line)
		{
			if (lineNumber < 1 || lineNumber > size + 1)
				return true;
			if (lineNumber == size + 1)
			{
				insertEnd(line);
				return false;
			}
			if (lineNumber == 1)
			{
				node* newHead = new node;
				newHead->line = line;
				newHead->next = head;
				head = newHead;
				size++;
				return false;
			}
			node* previous = head;	
			node* tmp = new node;
			tmp->line = line;
			for (int i = 0; i < lineNumber - 2; i++)
			{
				if (!previous->next)
					return true;
				else 
					previous = previous->next;
			}
			node* next = previous->next;
			previous -> next = tmp;
			tmp -> next = next;
			size++;
			return false;	
		}
		bool search(string search)
		{
			bool error = true;
			int line_num = 0;
			node* tmp = head;
			while (tmp)
			{
				line_num++;
				if (tmp->line.find(search) != string::npos)
				{
					cout << line_num << " " << tmp->line << endl;
					error = false;
				}
				if (tmp->next)
					tmp = tmp->next;
				else
					return error;
			}
			return error;
		}
		bool edit(int lineNumber, string newLine)
		{
			if (lineNumber < 1 || lineNumber > size + 1)
				return true;
			node* tmp = head;
			for (int i = 0; i < lineNumber - 1; i++)
			{
				if (!tmp->next)
					return true;
				else 
					tmp = tmp->next;
			}
			tmp->line = newLine;
			return false;
		}
		bool delete_(int lineNumber)
		{
			if (lineNumber < 1 || lineNumber > size)
				return true;

			if (lineNumber == 1)
			{
				node* temp = head;
				head = head->next;
				delete temp;
				size--;
				return false;
			}

			node* previous = head;
			for (int i = 0; i < lineNumber-2; i++)
				previous = previous->next;

			if (lineNumber == size)
			{
				node* temp = previous->next;
				previous->next = NULL;
				tail = previous;
				delete temp;
				size--;
				return false;
			}
			else
			{
				node* temp = previous->next;
				previous->next = temp->next;
				delete temp;
				size--;
				return false;
			}
		}
		void print()
		{
			node* tmp = head;
			int pageNum = 0;

			while(tmp)
			{
				pageNum++;
				cout << pageNum << " " << tmp->line << endl;
				if (tmp->next)
					tmp = tmp->next;
				else
					return;
			}
			return;
		}
		~list()
		{
			node* ptr;
			for (ptr = head; head; ptr = head)
			{
		    	head = head->next;
		    	delete ptr;
		   	}
		}
};	

/************ MAIN ***************/

int main ()
{
	list* myList = new list();
	string input;              // used to gather input from the users
	int lineNumber;            // stores the required int to send to the list class
	bool error;                // used to shoot an error message each time a list method is performed unsuccsessfully

	for (;;)
	{
		int first_space;               // stores the index of the first space in the input
		int second_space = -1;         // stores second space
		bool found_space = false;      // true only if atleast one space is found 
		string command = "";           // stores the first word (command)
		string number = "";            // stores the number for commands that require a number
		string text = "";              // stores the text to add/edit/search for 
		
		// the for loop below iterates through the entire input to find & store the first and second space
		// for ease of parsing later on
		getline(cin, input);
		int input_size = input.size();
		for (int i = 0; i < input_size; i++)
		{
			if (input.at(i) == 32)
			{
				if (!found_space)
				{
					first_space = i;
					found_space = true;
				}
				else 
				{
					second_space = i;
					break;
				} 
			}
		}

		// if there was no space found that means the only input was the command, used for print & quit
		if (!found_space)
			command = input;
		else
			command = input.substr(0, first_space);

		if (command.compare("insertEnd") == 0) 
		{
			text = input.substr(first_space + 1, input_size);
			// the next two if statements gets rid of the qoutes in the text
			if (text.at(text.size() - 1) == 34)
				text = text.substr(0, text.size() - 1); 
			if (text.at(0) == 34)
				text = text.substr(1, text.size() - 1);
			if (text.size() > 0)
	 			myList->insertEnd(text);
		}
		else if (command.compare("insert") == 0)
		{ 
			number = input.substr(first_space + 1, second_space - first_space - 1);
			istringstream (number) >> lineNumber;
			// the next two if statements gets rid of the qoutes in the text
			text = input.substr(second_space + 1, input_size);
			if (text.at(text.size() - 1) == 34)
				text = text.substr(0, text.size() - 1); 
			if (text.at(0) == 34)
				text = text.substr(1, text.size() - 1);
			error = myList->insert(lineNumber, text);
		}
		else if (command.compare("search") == 0)
		{
			text = input.substr(first_space + 1, input_size);
			// the next two if statements gets rid of the qoutes in the text
			if (text.at(text.size() - 1) == 34)
				text = text.substr(0, text.size() - 1); 
			if (text.at(0) == 34)
				text = text.substr(1, text.size() - 1);
			error = myList->search(text);
			if (error)
				cout << "not found\n";
		}
		else if (command.compare("edit") == 0)
		{
			number = input.substr(first_space + 1, second_space - first_space - 1);
			istringstream (number) >> lineNumber;
			text = input.substr(second_space + 1, input_size);
			// the next two if statements gets rid of the qoutes in the text
			if (text.at(text.size() - 1) == 34)
				text = text.substr(0, text.size() - 1); 
			if (text.at(0) == 34)
				text = text.substr(1, text.size() - 1);
			error = myList->edit(lineNumber, text);
		}
		else if (command.compare("delete") == 0)
		{
			number = input.substr(first_space + 1, second_space - first_space - 1);
			istringstream (number) >> lineNumber;
			error = myList->delete_(lineNumber);
		}
		else if (command.compare("print") == 0)
			myList->print();
		else if (command.compare("quit") == 0)
			return 0;
	}
}