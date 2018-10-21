//http://www.bigocheatsheet.com/
#include <iostream>
#include <sstream>
using namespace std;

class LinkedList // create linked list class
{
public:
	class Node 
	{
	     public:
	     string valInNode;
	     Node* next;   
	};

	Node *head;
	Node *tail;

	LinkedList()
	{ //constructor
			head = NULL;
	}

	void insertEnd(string valPassedIn)//O(n)
	{
		Node *insertNode = new Node();
		Node *current;//local variable to method
		insertNode->valInNode = valPassedIn;

		if(head == NULL)
		{
			head = insertNode;
		}
		else
		{
			current = head;
			while(current->next != NULL)//iterate to end of list
			{
				current = current->next;
			}

			current->next = insertNode; //node = to node
		}
	}


	void print()//O(n)
	{
		Node *current;//local variable to method
		current = head;
		int i = 1;
			while(current != NULL)//iterate to end of list
			{
				cout<<i<<" "<<current->valInNode<<endl;
				current = current->next;
				i++;
			}

	}

	int length(Node *head)
	{
		if (head == NULL)
		{
			return 0;
		}

		else
			return 1 + length(head->next);
	}

	void insert(int secondword,string thirdword) // 3, "text" O(n)
	{
		
		if(secondword<1 || secondword > length(head)+1)
		{
			return;
		}

		Node *current;//local variable to method
		Node *temp = new Node();

		temp->valInNode = thirdword;

			current = head;
			if (secondword  == 1)
			{
				temp->next = head;
				head = temp;
				return;
			}


			for(int i=0;i<secondword-2;i++)//iterate to end of list
			{
				current = current->next;
			}
			temp->next = current->next;
			current->next = temp;
	}

	void search(string substring)//O(n)
	{
		Node *current = head;
		int stringnum =1;
		while(current->next != NULL)
		{
			if(current->valInNode.find(substring) != string::npos)	
				{
					cout<<stringnum << " "<<current->valInNode<<endl;
					
				}
			stringnum++;
			current = current->next;
		}

			if(current->valInNode.find(substring) != string::npos)	
				{
					cout<<stringnum << " "<<current->valInNode<<endl;
					
				}
			else
			{
				cout<<"not found"<<endl;
			}
		
	}

	void deletes(int numberdel)//O(n)
	{
		Node *current;//local variable to method
		Node *previous;
		current = head;
		previous = head;
		int i = 2;
		if (numberdel == 1)
		{
				head = current->next;
				delete previous;
  		}

		current= current->next;


		while(current != NULL)
		{
			if (i == numberdel)
			{
				//cout<<current->valInNode<<endl;
				//cout<<previous->valInNode<<endl;
				Node *temp = current;
				current = current->next;
				previous->next = current;

				//cout<<current->valInNode<<endl;
				//cout<<previous->valInNode<<endl;

				delete temp;
				
				return;
			}
			current = current->next;
			previous = previous ->next;
			i++;
		}	



			
	}

	void edit(int numedit,string newword)//O(n)
	{
		Node *current;//local variable to method
		Node *temp = new Node();
		temp->valInNode = newword;
		current = head;
			for(int i=0;i<numedit-1;i++)//iterate to end of list
			{
				current = current->next;
			}
			current->valInNode = temp->valInNode;
	}


};

int main(){
	LinkedList* list = new LinkedList;
	string phrase="";
	string firstword= "";
	string secondword= "";
	string thirdword= "";
	string newString;
	string thirdString;


	while(phrase != "quit")
	{
		getline (cin,phrase);
		int index = 0;
		
		firstword = phrase.substr(index,phrase.find(" "));
		index = phrase.find(" ");
		newString = phrase.substr(index+1);


		if (firstword == "insertEnd")
		{
			secondword = newString.substr(1,newString.length()-2);
			list -> insertEnd(secondword);
			phrase = "";

		}

		else if(firstword == "insert")
		{
			secondword = newString.substr(0,newString.find(" "));
			index = newString.find(" ");
			thirdString = newString.substr(index+1);
		
			thirdword = thirdString.substr(1,thirdString.length()-2);

			stringstream sec(secondword);
			int secpassed;
			sec >> secpassed;

			list -> insert(secpassed, thirdword);
		}

		else if(firstword == "delete")
		{
			secondword = newString.substr(0,newString.length());
			stringstream del(secondword);
			int delpassed;
			del >> delpassed;
			list->deletes(delpassed);
		}

		else if(firstword == "edit")
		{
			secondword = newString.substr(0,newString.find(" "));
			index = newString.find(" ");
			thirdString = newString.substr(index+1);
		
			thirdword = thirdString.substr(1,thirdString.length()-2);
			

			stringstream pass(secondword);
			int editpassed;
			pass >> editpassed;

			list -> edit(editpassed, thirdword);
		}

		else if(firstword == "print")
		{
			list->print();
		}

		else if(firstword == "search")
		{
			secondword = newString.substr(1,newString.length()-2);
			list->search(secondword);
		}

		else
			{
				return 0;
			}


	}
  	
}

