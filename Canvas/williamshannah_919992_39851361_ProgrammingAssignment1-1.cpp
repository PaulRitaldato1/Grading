//Programming Assignment 1
//Hannah Williams

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


//Had to use g++ -std=c++11 programmingassignment1.cpp -o programmingassignment1

//Will be inserting all nodes at end; to keep track of order, will use currIndex!
//Since unspecified for multiples, find will only return FIRST found line which matches search criteria.


class node	
{
	public:
		string data;
		int index;
		node *nextPtr;
};

class LinkedList	
{
	public:
		node *head, *tail;
		int currIndex;			//keep track of highest index in list
		
		
	//constructor
	LinkedList()	
	{
		head = NULL;
		tail = NULL;
		currIndex = 0;
	}
	
	//prototypes
	void addNode(string strInput, int indexInput);
    node* findNodeIndex(int indexInput);
    void findNodeText(string textInput);
    void fixIndex(int indexInput, bool addFlag);
    void deleteLine(node *foundNode);
    void printList();
    
};


//Functions
//O(n)
void LinkedList::addNode(string strInput, int indexInput)	
{
	//to prevent the insertion of indices out of bounds....
	if ((tail != NULL) && (indexInput > (currIndex+1)) )
	{
		return;		//major bug: changed from ++ since the operator actually increments the stored value of index!!!
	}
	
	fixIndex(indexInput, true);
	
	node *tmp = new node;
	tmp->data = strInput;
	tmp->index = indexInput;
	tmp->nextPtr = NULL;
	
	
	if(head == NULL)	
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->nextPtr = tmp;
		tail = tmp;
	}
	
	currIndex++;
	return;
}

//O(n)
node* LinkedList::findNodeIndex(int indexInput)	
{
	node *tmp = head;
	
	//if desired node is head and is only one in list
	if (tmp->index == indexInput)
	{	
		return tmp;
	}
	
	
	//if desired node is not tail
	while (tmp != NULL)
	{
		if (tmp->index == indexInput)
		{
			return tmp;
		}
		
		tmp = tmp->nextPtr;	
	
	}
	
	//if desired node does not exist
	return NULL;
} 

//O(n)
void LinkedList::findNodeText(string textInput)
{
	node *tmp = head;
	bool foundText = false;
	
	//if desired node is not head
	while (tmp != NULL)
	{
		if (tmp->data.find(textInput) != string::npos) 
		{
			cout<<tmp->index<<" "<<tmp->data<<"\n";
			foundText = true;
		}
		
		tmp = tmp->nextPtr;	 
		
	}
	
	//if desired node does not exist
	if (foundText == false)
		cout<<"not found\n";
		
	//if finished
	return;
} 

//O(n) 
void LinkedList::fixIndex(int indexInput, bool addFlag)
{
	//if adding, must increment indices
	//if deleting, must decrement indices
	
	if (head == NULL)
	{
		return;
	}
	
	node *tmp = head;
	
	//if only one node in list
	if (tmp->nextPtr == NULL)
	{	
		return;
	}
	
	//if multiple nodes
	while (tmp != NULL)
	{
		if (tmp->index >= indexInput)
		{
			if (addFlag)
			{
				tmp->index = ((tmp->index) + 1);
			}
			
			else
			{
				tmp->index = ((tmp->index) - 1);
			}	
		}
		
		tmp = tmp->nextPtr;	
	
	}
	
	return;

}

//O(n^2)
void LinkedList::deleteLine(node *foundNode)
{
	node *tmp = head;
	
	//check for undeletables
	if (foundNode ==  NULL)
		return;
	
	//if desired node is head and is only one in list
	if (foundNode == head && foundNode == tail)
	{	
		head = NULL;
		tail = NULL;
		delete (foundNode);
		currIndex--;
		fixIndex(foundNode->index, false);
		return;
	}
		
	//if desired node is head
	if (foundNode == head)
	{	
		head = foundNode->nextPtr;
		delete (foundNode);
		currIndex--;
		fixIndex(foundNode->index, false);
		return;
	}
	
	
	//if desired node is in the middle or tail
	while (tmp != NULL)
	{
		if (tmp->nextPtr == foundNode)
		{
			//if tail
			if (foundNode == tail)
			{
				tmp->nextPtr = NULL;
				tail = tmp;
				delete(foundNode);
				currIndex--;
				fixIndex(foundNode->index, false);
				return;
			}
			
			//if middle
			else
			{
				tmp->nextPtr = foundNode->nextPtr;
				delete(foundNode);
				currIndex--;
				fixIndex(foundNode->index, false);
				return;
			}
		}
		
		tmp = tmp->nextPtr;	
	
	}
	
	//if desired node does not exist
	return;
    
}

//O(n^2)
void LinkedList::printList()
{
	if (head == NULL)
	{
		cout<<"Nothing to print.";
		return;
	}
	
	for (int i = 1; i<=currIndex; i++)
	{
		cout << i << " " << ((findNodeIndex(i))->data);
		cout <<"\n";
	}	
}


int main()	{
	
	 LinkedList *mainLinkedList = new LinkedList();
	string arg1;
	string arg2;
	string arg3;
	string delimiter = " ";

	/*
	cout<<"\n\nCommands:\n";
	cout<<"1. insertEnd \"text\" 	insert given text at the end of the document\n";
	cout<<"2. insert num \"text\" 	insert given text at the line indicated by index given\n";										//Menu
	cout<<"3. delete num: 		delete line at index given\n";
	cout<<"4. edit num \"text\": 	replace the line at the index given with the given text\n";
	cout<<"5. print: 		print the entire document with line numbers\n";
	cout<<"6. search \"text\": 	print the line number and line that contains the given text\n";
	cout<<"7. quit: 		exit the program\n";
	cout<<"Please input command. Surround all input text with quotation marks, and use appropriate spacing.\n";
	*/
	
	while(true)	{

		//set arguments to empty/NULL
		arg1 = "";
		arg2 = "";
		arg3 = "";
		
		//get user input (as string)
		string input = "";
		getline(cin, input);
		input = input + " ";										//delimiter looks for spaces, so must add extra space for input validation
		
		//parse input
		arg1 = input.substr(0, input.find(delimiter));
		
		if (arg1 == "insertEnd")
		{
			//separate arguments									//delimiter.length() == 1
			input.erase(0, input.find(delimiter) + 1);				//delete arg1
			delimiter = "\"";										//change delimiter to grab string in quotes
			input.erase(0, input.find(delimiter) + 1);				//delete quotes
			arg2 = input.substr(0, input.find(delimiter));			//save arg2
			input.erase(0, input.find(delimiter) + 1);				//delete everything up to next quotes
			delimiter = " ";
			input.erase(0, input.find(delimiter) + 1);				//delete space
			
			//some input validation (checking # of arguments)
			//if (input != "")
			//{
			//	cout<<"Invalid command. Too many arguments! \n";
			//	continue;
			//}	
			
			//make each line in the document 80 characters
			//arg2.resize(80);
			
			//perform command
			mainLinkedList->addNode(arg2, (mainLinkedList->currIndex + 1));
			
			continue;
		}
		
		
		if (arg1 == "insert")
		{
			//separate arguments
			input.erase(0, input.find(delimiter) + 1);				//delete arg1
			arg2 = input.substr(0, input.find(delimiter));			//save and delete arg2
			input.erase(0, input.find(delimiter) + 1);				//delimiter.length() == 1
			delimiter = "\"";										//change delimiter to grab string in quotes
			input.erase(0, input.find(delimiter) + 1);				//delete quotes
			arg3 = input.substr(0, input.find(delimiter));			//save arg3
			input.erase(0, input.find(delimiter) + 1);				//delete everything up to next quotes
			delimiter = " ";
			input.erase(0, input.find(delimiter) + 1);				//delete space
			
			//some input validation (checking # of arguments)
			//if (input != "")
			//{
			//	cout<<"Invalid command. Too many arguments! \n";
			//	continue;
			//}	
			
			//make each line in the document 80 characters
			//arg3.resize(80);
			
			//perform command (and convert arg2 to integer)
			mainLinkedList->addNode(arg3, stoi(arg2));
			
			continue;
		}
		
		if (arg1 == "delete")
		{
			//separate arguments
			input.erase(0, input.find(delimiter) + 1);				//delete arg1
			arg2 = input.substr(0, input.find(delimiter));			//save and delete arg2
			input.erase(0, input.find(delimiter) + 1);				//delimiter.length() == 1
			
			//some input validation (checking # of arguments)
			//if (input != "")
			//{
			//	cout<<"Invalid command. Too many arguments! \n";
			//	continue;
			//}	
			
			//perform command (and convert arg2 to integer)
			mainLinkedList->deleteLine(mainLinkedList->findNodeIndex(stoi(arg2)));
			continue;
		}	
		
		if (arg1 == "edit")
		{	
			//separate arguments
			input.erase(0, input.find(delimiter) + 1);				//delete arg1
			arg2 = input.substr(0, input.find(delimiter));			//save and delete arg2
			input.erase(0, input.find(delimiter) + 1);				//delimiter.length() == 1
			delimiter = "\"";										//change delimiter to grab string in quotes
			input.erase(0, input.find(delimiter) + 1);				//delete quotes
			arg3 = input.substr(0, input.find(delimiter));			//save arg3
			input.erase(0, input.find(delimiter) + 1);				//delete everything up to next quotes
			delimiter = " ";
			input.erase(0, input.find(delimiter) + 1);				//delete space
			
			//some input validation (checking # of arguments)
			//if (input != "")
			//{
			//	cout<<"Invalid command. Too many arguments! \n";
			//	continue;
			//}	
			
			//make each line in the document 80 characters
			//arg3.resize(80);
			
			//perform command (and convert arg2 to integer)
			mainLinkedList->deleteLine(mainLinkedList->findNodeIndex(stoi(arg2)));
			mainLinkedList->addNode(arg3, stoi(arg2));
			
			continue;
		}
		
		if (arg1 == "print")
		{
			//separate arguments
			input.erase(0, input.find(delimiter) + 1);				//delete arg1
			
			//some input validation (checking # of arguments)
			//if (input != "")
			//{
			//	cout<<"Invalid command. Too many arguments! \n";
			//	continue;
			//}
			
			mainLinkedList->printList();
				
			continue;
		}		
		
		if (arg1 == "search")
		{
			//separate arguments
			input.erase(0, input.find(delimiter) + 1);				//delete arg1
			delimiter = "\"";										//change delimiter to grab string in quotes
			input.erase(0, input.find(delimiter) + 1);				//delete quotes
			arg2 = input.substr(0, input.find(delimiter));			//save arg2
			input.erase(0, input.find(delimiter) + 1);				//delete everything up to next quotes
			delimiter = " ";
			input.erase(0, input.find(delimiter) + 1);				//delete space
			
			//some input validation (checking # of arguments)
			//if (input != "")
			//{
			//	cout<<"Invalid command. Too many arguments! \n";
			//	continue;
			//}		
			
			//perform command
			mainLinkedList->findNodeText(arg2);		
		}	
		
		if (arg1 == "quit")
		{
			break;
		}	
		
	}
	
	return 0;
	
}
