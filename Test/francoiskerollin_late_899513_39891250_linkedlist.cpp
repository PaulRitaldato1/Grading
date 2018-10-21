#include <algorithm>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include <string>
#include <sstream>

using namespace std;

//Node Declaration

struct Node

{

	int pos;
	string text;

	struct Node *next;

};



class LinkedList

{

private:
	Node *head;
public:

	LinkedList()

	{

		head = NULL;

	}

	Node *NewNode(string text)

	{
		Node *temp = new(struct Node);

		temp->pos = 0;
		temp->text = text;

		temp->next = NULL;

		return temp;

	}

//Inserting new Node at end of LinkedList

	void insertEnd()

	{

		string text;

		//cout<<"Enter the text to be inserted: ";

		getline(cin, text);

		text.erase(std::remove( text.begin(), text.end(), '\"' ), text.end() );

		//cout<<text<<endl;

		struct Node *temp, *tempHead;

		temp = NewNode(text);

		tempHead = head;

		if(head==NULL)

		{

			head=temp;
			head->pos = 1;

		}

		else

		{
			int count = 2;
			while (tempHead->next != NULL)

			{

				tempHead = tempHead->next;   
				count ++;
			}

			temp->pos = count;
			tempHead->next = temp;

		}

		temp->next = NULL;


		//cout<<"Element Inserted at last"<<endl;  

	}


//Inserting a new Node at a given position

	void insert()

	{

		int pos;

		string text;

		//cout<<"Enter the postion at which Node to be inserted: ";

		cin>>pos;

		//cout<<"Enter the text to be inserted: ";

		getline(cin, text);
		text.erase(std::remove( text.begin(), text.end(), '\"' ), text.end() );
		text.erase(0,1);
		//cout<<text<<endl;


		struct Node *temp, *tempHead, *ptr;

		temp = NewNode(text);

		temp->pos = pos;

		int i;

		tempHead = head;

		while (tempHead->next != NULL && tempHead->pos < pos)

		{

			tempHead = tempHead->next;
		}

		i = tempHead->pos+1;

		if (i == temp->pos)
			tempHead->next = temp;

	}


// Delete element at a given position



	void delete_pos()

	{

		int pos, i;

		if (head == NULL)

		{

			cout<<"List is empty"<<endl;

			return;

		}

		//cout<<"Enter the position of text to be deleted: ";

		cin>>pos;

		struct Node *tempHead, *ptr;

		tempHead = head;


			while (tempHead->next != NULL && tempHead->pos != pos)

			{

				tempHead = tempHead->next;

			}

			if (tempHead->pos == pos)

			{

				tempHead = head;

				for (i = 1;i < pos;i++)

				{

					ptr = tempHead;

					tempHead = tempHead->next;

				}

				ptr->next = tempHead->next;

			}

			//cout<<"Element Deleted"<<endl;

	}


//Edit a given Node

	void edit()

	{

		int pos, i;

		string text;

		if (head == NULL)

		{

			cout<<"List is empty"<<endl;

			return;

		}

		//cout<<"Enter the Node postion to be edited: ";

		cin>>pos;

		//cout<<"Enter the new text: ";

		getline(cin, text);
		text.erase(std::remove( text.begin(), text.end(), '\"' ), text.end() );
		text.erase(0,1);

		struct Node *tempHead, *ptr;

		tempHead = head;

		if (pos == 1)

		{

			head->text = text;

		}

		else

		{

			while (tempHead->next != NULL )

			{



				tempHead = tempHead->next;

				if (tempHead->pos == pos)
				{
					tempHead->text = text;  
					break;
				}

				if (tempHead->next == NULL)

				{

					cout<<"Out of Range";

					return;

				}

			}

		}

		//cout<<"edited"<<endl;

	}


// Searching for an element


	void search()

	{

		string text;

		if (head == NULL)

		{

			cout<<"List is empty"<<endl;

			return;

		}

		//cout<<"Enter text to be searched: ";

		getline(cin, text);
		text.erase(std::remove( text.begin(), text.end(), '\"' ), text.end() );

		struct Node *tempHead;

		tempHead = head;

		size_t found;

		while (tempHead != NULL)

		{

			found = tempHead->text.find(text);

			if (found != string::npos)

			{

				cout<<tempHead->pos<<" "<<tempHead->text<<endl;

				return;

			}

			tempHead = tempHead->next;

		}

		cout<<"not found"<<endl;  

	}

//print Elements of a link list


	void print()

	{

		struct Node *temp;

		if (head == NULL)

		{

			cout<<"The List is Empty"<<endl;

			return;

		}

		temp = head;

		//cout<<"Elements of list are: "<<endl;

		while (temp != NULL)

		{

			cout<<temp->pos<<" "<< temp->text<<endl;

			temp = temp->next;

		}

	}

};


main()

{

	string choice;
	int Nodes, element, position, i;

	LinkedList sl;

	while (1)

	{

/*		cout<<"1.Insert Node at the end (type insertEnd)"<<endl;

		cout<<"2.Insert Node at position (type insert)"<<endl;

		cout<<"3.Delete a Particular Node (type delete)"<<endl;

		cout<<"4.edit Node text (type edit)"<<endl;

		cout<<"5.Search Element (type search)"<<endl;

		cout<<"6.print Linked List (type print)"<<endl;

		cout<<"7.Exit (type quit) "<<endl;

		cout<<"Enter your choice : ";*/

		cin>>choice;
		cin.ignore();



		if(choice ==  "insertEnd")
		{
			//cout<<"Inserting Node at End: "<<endl;
			
			sl.insertEnd();
			
			//cout<<endl;
			
		}

		else if(choice == "insert")
		{
			//cout<<"Inserting Node at a given position:"<<endl;
			
			sl.insert();
			
			//cout<<endl;
			
		}

		else if(choice == "delete")
		{
			//cout<<"Delete Node at given position: "<<endl;
			
			sl.delete_pos();
			
		}

		else if(choice == "edit")
		{
			//cout<<"edit Node text:"<<endl;  
			
			sl.edit();
			
			//cout<<endl;
			
		}

		else if(choice == "search")
		{
			
			//cout<<"Search element in Link List: "<<endl;
			
			sl.search();
			
			//cout<<endl;
			
		}

		else if(choice == "print")
		{
			
			//cout<<"print elements of link list"<<endl;
			
			sl.print();
			
			//cout<<endl;
			
		}

		else if(choice == "quit")
		{
			
			//cout<<"Exiting..."<<endl;
			
			exit(1);
			
			break;  
		}

		else
		{

			cout<<"Wrong choice"<<endl;

		}
	}
}
