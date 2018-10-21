
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
		//initiallizes the class and sets the head and tail to NULL
		linkedlist() 
		{
			head=NULL;
			tail=NULL;
		}
		//end of list insert
		void insertEnd(string line) 
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
		//inserts a string at the position
		void insert(int pos, string letters)
		{
			node *prev = new node;
			node *cur = new node;
			node *temp = new node;
			cur = head;
			for (int i = 1; i < pos; i++)
			{
				prev = cur;
				cur = cur->next;

			}
			temp->data = letters;
			prev->next = temp;
			temp->next = cur;

		}
		//makes a change at the position defined
		void edit(int pos, string letters) 
		{
			node *prev=new node;
			node *cur=new node;
			node *temp=new node;
			cur=head;
			for(int i=1;i<pos;i++)
			{
				prev=cur;
				cur=cur->next;
			}
			temp->data=letters;
			prev->next=temp;
			temp->next=cur->next;
		}
		//searches for the string
		void search(string letters){ 
			node *prev=new node;
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
		//deletes at the position
		void delete_val (int pos) 
		{
			node *curr=new node;
			node *prev=new node;
			curr=head;
			for(int i=1;i<pos;i++)
			{
				prev=curr;
				curr=curr->next;

			}
			prev->next=curr->next;
		}
		//gives the size
		int listSize() {
			int count = 1;
			node* curr = head;
			while (curr != NULL)
			{
				count++;
				curr = curr->next;
			}
			return count;
		} 
		//prints
		void print()
		{
			node *temp = new node;
			temp = head;
			int counter = 1;
			while (temp != NULL)
			{
				cout << counter << " " << temp->data << endl;
				temp = temp->next;
				counter++;
			}
		}
};
int main() //Main method.
{
	linkedlist obj; //Creates an object to refer to LinkedList class.
	while(true){

		string userInput="";
		//user inputs the command and then the first word is found and stored as the command
		getline(cin, userInput); 
		int position = userInput.find(" "); 
		string command = userInput.substr(0,position); 
		string line = userInput.substr(position+1); 
		//deletes the quotes
		if ( line.front() == '"' ) {
			    line.erase( 0, 1 ); 
				line.erase( line.size() - 1 ); 
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
			if(number >= obj.listSize()){

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
