/*
Paul Calzada
University of Florida
Data Structures and Algorithms
Professor Cheryl Resch
Programming Assignment 1 - Implement a Line Editor using Linked Lists
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
	The following is the struct Node which defines a node for the linked list
*/
struct Node
{
	string text;		//the line of text that the node holds
	Node* next;			//the pointer to the next node in the linked list
	int linenum;		//the line number for this line
};
	
//The following defines the class linked list which contains the data for the line editor
class Linked_List
{
	
	
	private:		//the head and tail of the list are only accessible by the linked list
	Node* head;		//pointer to the head node
	Node* tail;		//pointer to the tail node
	
	public:  
	Linked_List()	//constructor of the linked list, initializing the head and tail to nothing
    {
      head=NULL;
	  tail=NULL;
    }
	
	//////////////////////////MEMBER FUNCTIONS/////////////////////////////////
	
	/*
	
		Function Name: insertEnd
		Purpose: This function takes a line of text and creates a new node with that text. This new node is placed at the END of the linked list
		Input Arguments: string text (line of text of the next node to be added to the end of the list)
		Output Arguments: 
		
	*/
	  void insertEnd(string text)
    {
		Node* temp = new Node;			//initialize the node to be appended
		temp->text = text;				//give this new node the line of the inputted text
		temp->next = NULL;				//set the next pointer of this node to NULL (because it will be placed at the end of the list)
		if(head == NULL)				//if the linked list is empty
		{
			temp->linenum = 1;			//this node is the new head. This means it is the first line of text. It needs a line number of 1
			head=temp;					//the node is the head
			tail=temp;					//the node is also the tail
			temp=NULL;					//remove the temp variable
		}
      else								//if the linked list has nodes and is not empty
      {	
		int templinenum = (tail->linenum)+1;		//the line number of this new node is simply the line number of the tail + 1 
													//(because we are appending the new node to the end)
		temp->linenum = templinenum;
		tail->next=temp;		//set the tail to have a next value of the new node
        tail=temp;				//set the new node to the tail because it is now the last value in the list
		
      }
    }
	
	
	/*
	
		Function Name: insert
		Purpose: This function takes a line of text and creates a new node with that text. This new node is placed in a position in the linked list
		Input Arguments: int linenumber (the linenumber that the new node would occupy)
						 string text (line of text of the next node to be added to the end of the list)
		Output Arguments: 
		
	*/
	  void insert(int linenumber, string text)
  {
	  
	  	if(linenumber > (tail->linenum + 1))			//if the requested linenumber is greater than 1 + the tail value, then it is out of range of insertion
			return;
			
		Node* previous = new Node;			//temp pointer to the previous node
		Node* current = new Node;			//temp pointer to the current node
		Node* temp = new Node;				//temp pointer to create the new node
		Node* adjuster = new Node;			//temp pointer to adjust line number values 
		temp->linenum = linenumber;			//assign the new node to have a line number of the inputted line number
		current = head;						//set current to the head value
		
		for(int i = 1;i < linenumber;i++)			//because an iterator is not used, a for loop is necessary to get to the proper index
		{
			previous = current;					//move previous pointer to current
			current = current->next;			//move current pointer to next 
		}
		
		//now we are at the position(line number) we wish to insert the new node at
			temp->text = text;		//set the new node's text to the inputted text
			previous->next = temp;			//set the previous next pointer to the new node, allowing the new node to be traversed TO
			temp->next = current;			//set the next pointer of the new node to the current node (which will occupy the next line)
											//now the new node can be traversed THROUGH
			
			//now we must adjust the line numbers of the nodes after the new node so that they are incremented by 1
			adjuster = current;				
			while(adjuster){
				
				adjuster->linenum = (adjuster->linenum + 1);		//increment the node's line number
				adjuster = adjuster->next;					//move to next node
				
			}
			
			
  }
	
	
	/*
	
		Function Name: deleteNode
		Purpose: This function deletes a node (line) from the linked list and adjusts the line numbers of the nodes after it to decrement by 1
		Input Arguments: int linenumber (the linenumber that the soon-deleted node occupies)
		Output Arguments: 
		
	*/
		  void deleteNode(int linenumber)
		{
			
			if(linenumber > (tail->linenum))	//if the inputted line number is outside the range of the linked list, then a delete cannot be performed
				return;
			
			Node* current=new Node;				//temp pointer for current node
			Node* previous=new Node;			//temp pointer for previous node
			Node* adjuster = new Node;			//temp pointer for adjusting line numbers after deletion
			bool didDelete = false;				//status flag for viewing if the deletion occured
			current = head;						//current is head

			while(current)			//while current is not null
			{
				if(current->linenum == linenumber){			//if the current line number is equal to the desired line number 
					
					previous->next = current->next;			//set the previous node's next pointer to point to the current node's next pointer. 
															//This essentially deletes current from use by this program
					didDelete = true;						//successful delete
					break;									//leave while loop
				}
				
			previous=current;						//move to next node
			current=current->next;
			
			}
			//now we need to adjust the line numbers so that after the deletion, all following nodes decrement their line numbers by 1
			if(didDelete = true){	//if the deletion occured
				adjuster = current->next;		//adjuster starts at the node that is after the deleted node
				while(adjuster){				//while adjuster exists
				
					adjuster->linenum = (adjuster->linenum - 1);			//subtract the line numbers by 1
					adjuster = adjuster->next;				//move to next node
				
				}
			}
			
		}
	
	/*
	
		Function Name: replace
		Purpose: This function replaces a node's text with the inputed text
		Input Arguments: int linenumber (the linenumber where the soon-old text occupies)
						string text (the text to replace the old text)
		Output Arguments: 
		
	*/
		void replace(int linenumber, string text)
		{
			Node* current = new Node;				//temp pointer to point to current node
			current = head;							//the current node starts at the head
			while(current)							//while current exists
			{
				if(current->linenum == linenumber){			//if we reach the correct line number
					
					current->text = text;					//replace the text
					
				}
				
			current = current->next;		//move to next node
			}
			
		}
	
	/*
	
		Function Name: print
		Purpose: This function prints the linked lists lines of text and line numbers
		Input Arguments:
		Output Arguments: 
		
	*/	
		  void print()
  {
			Node* temp = new Node;				//the node to be printed
			temp = head;						//start at the head
			while(temp)			//while the node exists
			{
				cout<<temp->linenum<<" "<<temp->text<<"\n";			//print the node's line number followed by its text value
				temp=temp->next;			//move to next node
			}
  } 
		
		
		
	/*
	
		Function Name: search
		Purpose: This function searches the linked list for all nodes which contains an inputted substring. The functions prints the node's information if found
		Input Arguments: string text (the text to search for)
		Output Arguments: 
		
	*/
		  void search(string text)
		{
			Node* current = new Node;				//temp pointer to point to the current node
			current = head;							//start at the head of the linked list
			bool flag = false;						//flag identifying if we have found a node with this substring
			while(current)						//while the current node exists
		{
			if((current->text).find(text) != std::string::npos){			//if the substring is inside the text of the current node
				std::cout << current->linenum << " " << current->text << endl;		//print the nodes info
				flag = true;			//set the flag
				
				//****notice we DO NOT break here from the loop because we want ALL nodes with the substring. Breaking would yield only the first node with a match
			}
						
			current = current->next;			//move to next node
			
		}

			if(flag == false){			//if no node has that substring,
				std::cout << "not found" << endl;			//print 
			}
			
		}
		
};




//////////////////////////////////////MAIN FUNCTION////////////////////////////////////////



//The main function takes user commands infinitly until quit is entered

int main()
{
	
	Linked_List list;		//create a linked list object
	string userInput = "";	//this string will contain the most current input from the user (the total input line)
	string command = "";	//this string will contain the substring of the total string that identifies which command or operation to perform
	string linenumber = "";	//this string will contain the subtring of the total string that identifies which line number the operation will perform on(not always necessary)
	string text = "";		//this string will contain the subtring of the total string that identifies the text that the operation will perform on(not always necessary)
	
	//INFINITE LOOP UNTIL QUIT OCCURS
	while(1){
		
		getline(cin,userInput);	//get the user input containing command and any arguments necessary
		command = userInput.substr(0,userInput.find(' '));		//extract the command from the total input
		
		//based on the command, the program performs various operations
			
		if(command == "insertEnd"){			//if the user enters insertEnd
			
			text = userInput.substr(userInput.find(' ')+1);			//extract the text from the total input
			
			text.erase(0,1);				//remove the first quotation from the text
			text.pop_back();				//remove the last quotation from the text
			
			list.insertEnd(text);			//insert new node at the end of the linked list with that text
			
		}
		
		else if(userInput == "print" || command == "print"){	//if the user enters print
			
			list.print();				//simply print all lines and line numbers
			
		}
		
		else if(command == "delete"){		//if user enters delete
			
			linenumber = userInput.substr(userInput.find(' ')+1);		//extract line number from user input
			int lnum = stoi(linenumber);			//convert the string line number to an actual integer we can use
			list.deleteNode(lnum);					//delete the node at that line number
			
		}
		
		else if(command == "edit"){			//if the user enters edit
			
			linenumber = userInput.substr(userInput.find(' ')+1,userInput.find(' ',userInput.find(' ')+1)); //extract line number from user input
			int lnum = stoi(linenumber);				//convert the string line number to an actual integer we can use
			text = userInput.substr(userInput.find(' ',userInput.find(' ')+1)+1);		//extract the text from the total input
			
			text.erase(0,1);				//remove the first quotations from the text
			text.pop_back();				//remove the last quotations from the text
			
			list.replace(lnum,text);		//replace the text at that node with the new inputted text
			
		}
		
		else if(command == "insert"){			//if the user enters insert
			
			linenumber = userInput.substr(userInput.find(' ')+1,userInput.find(' ',userInput.find(' ')+1));		//extract line number from total input
			int lnum = stoi(linenumber);		//convert string line number to integer so we can use it
			text = userInput.substr(userInput.find(' ',userInput.find(' ')+1)+1);		//extract text from total input
			
			text.erase(0,1);		//remove first quotation
			text.pop_back();		//remove last quotation
			
			list.insert(lnum,text);		//insert the new node at that line number and with the specified text
					
			
			
		}
		
		else if(command == "search"){			//if the user enters search
			
			
			text = userInput.substr(userInput.find(' ')+1);			//extract text from total user input
			
			text.erase(0,1);			//remove first quotation
			text.pop_back();			//remove last quotation
						
			list.search(text);			//search if the text is found
						
			
			
			
		}
		
		

		else if(userInput == "quit" || command == "quit"){			//if the user enters quit
			
				return 0;				//quit program
				
		}
		
	
		}
	
}