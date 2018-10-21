//Project 1: Line Editor by Devin Blem
#include<iostream>
using namespace std;

//node declaration
struct node
{
	string data;
	struct node *next;
}*head;

//linked list class declaration
class linkedList
{
public:

	//prints out all values in the list and their corresponding line number
	void Print()
	{
		struct node *temp;
		if (head == NULL)
		{
			cout << "The list is empty" << endl;
			return;
		}
		int counter = 1;
		temp = head;
		while (temp != NULL)
		{
			cout << counter << " " << temp->data << endl;
			counter++;
			temp = temp->next;
		}
	}
	//create a new node with user given data
	node *addNode(string str)
	{
		struct node *temp;
		temp = new (struct node);
		if (temp == NULL)
		{
			cout << "memory not allocated " << endl;
			return 0;
		} else
			{
			temp->data = str;
			temp->next = NULL;
			return temp;
			}
		}
	//inserts user string into specified node in linked list
	void insertNode()
	{
		int pos, count = 1;
		string userValue;
		cout << "Enter the line to be inserted: ";
		getline(std::cin, userValue);
		struct node *temp, *ptr, *x;
		temp = addNode(userValue);
		cout << "Enter the desired position for the node to be inserted: ";

		cin >> pos;
		//check to make sure that input is an integer
		if (cin.fail())
		{

			cout << "Insertion failed, input needs to be an integer value"
					<< endl;

			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
		else
		{
			cout << endl;
		}

		x = head;
		while (x != NULL)
		{
			x = x->next;
			count++;
		}
		if (pos == 1)
		{
			if (head == NULL)
			{
				head = temp;
				head->next = NULL;
			} else
			{
				ptr = head;
				head = temp;
				head->next = ptr;
			}
		}
		else if (pos>1 && pos<=count)
		{
			x = head;
			for (int i=1; i<pos; i++)
			{
				ptr = x;
				x = x->next;
			}
			ptr->next = temp;
			temp->next = x;
		}
		else
		{
			//cout << "Position is out of range" << endl;
		}
	}

	//insert user input to the end of linked list
	void insertEnd()
	{
		string userValue;
		cout << "Enter the line to be inserted to end of document: " << endl;
		getline(std::cin, userValue);

		struct node *temp, *t;
		temp = addNode(userValue);
		t = head;
		if (t == NULL)
		{
			head = temp;
		}
		else
		{
			while (t->next != NULL)
			{
				t = t->next;
			}
			t->next = temp;
		}
		temp->next = NULL;
	}

	//deletes a specified node
	void deleteNode()
	{
		int pos, i, counter = 0;
		if (head == NULL)
		{
			cout << "List is empty" << endl;
			return;
		}
		cout << "Enter the desired position of node to be deleted: ";
		cin >> pos;
		if (cin.fail())
						{

							cout << "Insertion failed, input needs to be an integer value"
									<< endl;

							cin.clear();
							cin.ignore(1000, '\n');
						}
		struct node *temp, *ptr;
		temp = head;
		if (pos == 1)
		{
			head = temp->next;
		}
		else
		{
			while (temp != NULL)
			{
				temp = temp->next;
				counter++;
			}
			if (pos > 0 && pos <= counter)
			{
				temp = head;
				for (i = 1; i < pos; i++)
				{
					ptr = temp;
					temp = temp->next;
				}
				ptr->next = temp->next;
			}
			else
			{
				//cout << "Position out of range" ;
					cout	<< endl;
			}
			free(temp);
		}
	}

	/* Traverses the list for given key phrase
	 * returns all instances of the key phrase including line number
	 */
	void search()
	{
		string value;
		if (head == NULL)
		{
			cout << "List is empty" << endl;
			return;
		}
		cout << "Enter text to be searched: ";

		struct node *temp;
		temp = head;
		int pos = 1;
		cin >> value;
		while (temp != NULL)
		{

			if (temp->data.find(value) != string::npos)
			{
				cout << pos << " " << temp->data;
			}

			temp = temp->next;
			pos++;
		}
	}

	//edits specified line in list to new user value
	void editList()
	{
		int pos, i;
		string value;
		string dummyVar;
		if (head == NULL)
		{
			cout << "List is empty" << endl;
			return;
		}
		cout << "Enter the position of the node to be edited: ";
		cin >> pos;
		if (cin.fail())
				{

					cout << "Insertion failed, input needs to be an integer value"
							<< endl;

					cin.clear();
					cin.ignore(1000, '\n');
					return;
				}
		cout << "Enter the new sentence: ";
		getline(cin, dummyVar);
		getline(cin, value);

		struct node *n;
		n = head;
		if (pos == 1)
		{
			head->data = value;
		}
		else
		{
			for (i = 0; i < pos-1; i++)
			{
				if (n == NULL)
				{
					return;
				}
				n = n->next;
			}
			n->data = value;
		}
		cout << endl;
	}

	linkedList()
	{
		head = NULL;
	}
};

//main method to invoke line editor program
int main()
{
	linkedList myList;
	head = NULL;

	string userInput = "";
	cout << endl << "--------------------------" << endl;
	cout << endl << "Please type your command" << endl;
	cout << endl << "--------------------------" << endl;
	cout << "insertEnd " << endl;
	cout << "insert " << endl;
	cout << "delete " << endl;
	cout << "edit" << endl;
	cout << "search" << endl;
	cout << "print" << endl;
	cout << "quit " << endl;
	while (userInput != "quit") {

		getline(std::cin, userInput);

		if (userInput.substr(0, 5) == "print")
		{
			myList.Print();
			cout << endl;
		}
		else if (userInput.substr(0, 9) == "insertEnd")
		{
			myList.insertEnd();
			cout << endl;
		}

		else if (userInput.substr(0, 4) == "quit")
		{
			cout << "quitting line editor \n";
			cout << endl;
			exit(1);
		}

		else if (userInput.substr(0, 6) == "delete")
		{
			myList.deleteNode();
			cout << endl;
		}

		else if (userInput.substr(0, 4) == "edit")
		{
			myList.editList();
			cout << endl;
		}

		else if (userInput.substr(0, 6) == "search")
		{
			myList.search();
			cout << endl;
		}
		else if (userInput.substr(0, 6) == "insert"
				&& userInput.substr(7, 9) != "End")
		{
			myList.insertNode();
			cout << endl;
		}
	}
}
