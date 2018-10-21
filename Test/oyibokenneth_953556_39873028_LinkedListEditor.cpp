//============================================================================
// Name: LinkedListEditor.cpp
// Author      : Kenneth Oyibo
//============================================================================

#include <iostream>
#include <string>

using namespace std;

class LinkedListEditor{

private:
	//Here I construct my node structure
	struct node{
		string text;
		node*next;
	};
	node *head;
	node *tail;

public:
	LinkedListEditor(){

		head = NULL;	//head and tail are set equal to null
		tail = NULL;

	}

	/*
	 * This method inserts a string at the end of a linked list
	 */
	void insertEnd(string line){
		node *temp = new node;
		temp->text = line;
		//if the head is empty, create a temp node and assign it as the head and the tail
		if (head == NULL){
			head = temp;
			tail = temp;
		}
		else{
			//assign the temp node as the new tail of the linked list
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
	}

/*
 * This method insert a text at the specified index
 */
	void insertPosition(int index, string line){
		int i;
		int counter = 1;
		int position = index;
		string value = line;
		node*temp = new node();
		temp ->text = line;
		node*start = new node;
		node*current = new node;
		start = head;
		/*
		 * while start is not pointing to head or tail
		 * increment counter and point start to the next linked list
		 */
		while (start != NULL)
		{
			start = start->next;
			++counter;
		}
		//if the index required to insert is 1, call the insert End function
		if (position == 1)
		{
			if (head == NULL)
			{
				insertEnd(value); //call the add to end function
			}
			else
			{
				current = head;
				head = temp;
				head->next = current;
			}
		}
		//check to see if boundary conditions are satisfied
		else if (position > 1 && position <= counter){
			start = head;
			for (i = 1; i < position; i++)
			{
				current = start;
				start = start->next;
			}
			current->next = temp;
			temp->next = start;
		}
		else
		{
			//display nothing
		}
	}



	void deletePosition(int index){
		int position = index;
		int counter = 0;
		int i = 0;
		if (head == NULL)
		{
			cout<<"Document is empty, you cannot delete"<<endl;
			return;
		}
		node *temp = new node();
		node*current = new node();
		temp = head;
		//if index to delete is 1, then delete head
		if (position == 1)
		{
			head = temp->next;
		}
		else
		{
			//else while temp is not at the end, increment temp
			while (temp != NULL)
			{
				temp = temp->next;
				counter++;
			}
			//check to see if boundary conditions are satisifed
			if (position > 0 && position <= counter)
			{
				temp = head;
				for (i = 1;i < position;i++)
				{
					current = temp;
					temp = temp->next;
				}
				current->next = temp->next;
			}
			else
			{
				return;
				//display nothing
			}
			free(temp);
		}
	}

	void editText(int index, string text){
		int position = index;
		int i = 0;
		string value = text;
		//if head is empty
		if (head == NULL)
		{
			//display nothing and return
			return;
		}
		node *temp = new node();
		temp = head;
		if (position == 1)
		{
			head->text = value;
		}
		else
		{
			//increment till you get to the position you want to edit
			for (i = 0;i < position - 1;i++)
			{
				if (temp == NULL)
				{
					return;
				}
				temp = temp->next;
			}
			temp->text = value;
		}
	}

	void searchText(string text){
		node*temp = new node;
		temp = head;
		int i = 1;
		while(temp){
			if(temp->text.find(text)!= -1){
				cout<<i<< " "<<temp->text<<endl;
			}
			temp= temp->next;
			i++;
		}
		if (temp==NULL)
            cout<<"not found"<< endl;
			return;
	}

	/*
	 * This method prints the entire linked list with numbers
	 */

	void printList(){
		node*current = head;
		int counter = 0;
		while(current!=NULL){
			cout<<++counter<<" "<<current->text<< endl;
			current = current->next;
		}
	}
};

using namespace std;
#include<bits/stdc++.h>

int main() {

	LinkedListEditor listEditor; //create a new object
	stringstream convert;	//this will be used to convert from string to int
	string userInput;  //this stores the users input
	string userText;	//this stores the text
	string index;		//string index is stored
	int int_index;		//this stores the int index
	int temp;
	//this will loop forever until the user quits it
	while(1){
		getline(cin,userInput); //This reads the sample lines
		/*
		 * The strings are checked for key words and the
		 * index or text needed is grabbed by substrings to be passed
		 * as parameters to the methods
		 */
		if(userInput=="print")
		{
		listEditor.printList();
		}
		else if(userInput=="quit")
		break;
		else if(userInput.substr(0,6)=="search")
		{
		userText=userInput.substr(8);
		userText.erase(userText.size()-1); // this removes the quotes at the end
		listEditor.searchText(userText);
		}

		else if(userInput.substr(0,4)=="edit")
		{
		temp=userInput.find(" ",5); //find the text after the edit and quotes
		index=userInput.substr(5,temp-5);
		convert<<index;	//change string to int value
		convert>>int_index;
		convert.clear();
		userText = userInput.substr(8);
        userText.erase(userText.size()-1);
		listEditor.editText(int_index,userText);
		}
		else if(userInput.substr(0,9)=="insertEnd")
		{
		userText=userInput.substr(11);
		userText.erase(userText.size()-1);
		listEditor.insertEnd(userText);
		}
		else if(userInput.substr(0,6)=="insert"){
		temp = userInput.find(" ",7);
		index = userInput.substr(7,temp-7);
		convert<<index;	//change string to int value
		convert>>int_index;
		convert.clear();
		userText = userInput.substr(10);
        userText.erase(userText.size()-1);
		listEditor.editText(int_index,userText);

		}

	}
	return 0;

}
