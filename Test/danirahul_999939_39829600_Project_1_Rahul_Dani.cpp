//Rahul Dani - UFID:9013-1693
//COP 3530 Project 1

#include <iostream> //Import the following libraries.
#include <string>
#include <algorithm>
using namespace std;

struct node //Node Creation
{
	string data;
	node *next;
};
class linkedlist //The Linked List class with specific functions.
{
		private:
		node *head, *tail;
		public:
		linkedlist() //Sets head and tail to NULL.
		{
			head=NULL;
			tail=NULL;
		}
		void insertEnd(string line) //Inserts at the End of the List
		{
			node *temp=new node;
			temp->data=line;
			temp->next=NULL;
			if(head==NULL)
			{
				head=temp;
				tail=temp;
				temp=NULL;
			}
			else
			{
				tail->next=temp;
				tail=temp;

			}
		}
		int listSize(){ //Returns the size of the Linked List.
			int count = 1;
			node* current = head;
			while (current != NULL)
			{
			count++;
			current = current->next;
		}
		return count;
		}

		void print() //Prints the Linked List.
		{
			node *temp=new node;
			temp=head;
			int counter = 1;
			while(temp!=NULL)
			{
				cout<<counter<<" "<<temp->data << endl;
				temp=temp->next;
				counter++;
			}
		}

		void insert(int pos, string letters) //Inserts string at a given position.
		{
			node *pre=new node;
			node *cur=new node;
			node *temp=new node;
			cur=head;
			for(int i=1;i<pos;i++)
			{
				pre=cur;
				cur=cur->next;

			}
			temp->data=letters;
			pre->next=temp;
			temp->next=cur;

		}
		void edit(int pos, string letters) //Edits string at the given position.
		{
			node *pre=new node;
			node *cur=new node;
			node *temp=new node;
			cur=head;
			for(int i=1;i<pos;i++)
			{
				pre=cur;
				cur=cur->next;
			}
			temp->data=letters;
			pre->next=temp;
			temp->next=cur->next;
		}

		void search(string letters){ //Searches the linked list for any instances of the string.
			node *pre=new node;
			node *cur=new node;
			node *temp=new node;
			temp = head;
			int counter = 1;
			bool found = false;
			while(temp!=NULL){
				if(temp->data.find(letters)!= -1){
					cout<<counter<<" "<<temp->data<<endl;
					temp=temp->next;
					counter++;
					found = true;
				}
				else {
					temp=temp->next;
					counter++;

				}
			}
			if(found == false){
					cout << "not found" <<endl;
			}

		}

		void delete_val (int pos) //Deletes the string at the given position.
		{
			node *current=new node;
			node *previous=new node;
			current=head;
			for(int i=1;i<pos;i++)
			{
				previous=current;
				current=current->next;

			}
			previous->next=current->next;
		}
};
int main() //Main method.
{
	linkedlist obj; //Creates an object to refer to LinkedList class.
	while(true){

		string userInput="";
		getline(cin, userInput); //User input of the line.
		int position = userInput.find(" "); //Finds the first whitespace.

		string command = userInput.substr(0,position); //First keyword taken before first whitespace.
		string line = userInput.substr(position+1); //New String with everything after first whitespace.

		if ( line.front() == '"' ) {
    line.erase( 0, 1 ); //Erase the first quote.
    line.erase( line.size() - 1 ); //Erase the last quote.
		}

		if(command == "insertEnd"){ //Runs insertEnd.
				obj.insertEnd(line);
		}
		else if(command == "insert"){ //Runs insert.

			string digitString = line.substr(0,1);
			int number = stoi(digitString);
			string newLine = line.substr(line.find_first_of("\"")+1, line.find_last_of("\"") - line.find_first_of("\"")-1);

  		if(number >= (obj.listSize())+1){ //Tests if insert value is in range.

			}
			else{
			obj.insert(number, newLine);
			}
		}
		else if(command == "delete"){ //Runs delete.
			string digitString = line.substr(0,1);
			int number = stoi(digitString);
			if(number >= obj.listSize()){ //Tests if delete is in range.

			}
			else{
			obj.delete_val(number);
			}
		}
		else if(command == "edit"){ //Runs edit.
			string digitString = line.substr(0,1);
			int number = stoi(digitString);
			string newLine = line.substr(line.find_first_of("\"")+1, line.find_last_of("\"") - line.find_first_of("\"")-1);
			if(number >= obj.listSize()){ //Tests if edit is in range.

			}
			else{
			obj.edit(number, newLine);
			}
		}
		else if(command == "print"){ //Runs print.
				obj.print();
		}
		else if(command == "search"){ //Runs search.
				obj.search(line);
		}
		else if(command == "quit"){ //Quits the program.
			return 0;
		}
		else {
			cout << "Invalid input" << endl; //If keyword is not the desired keyword.
		}
	}
}
