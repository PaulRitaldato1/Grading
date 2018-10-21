#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
class Node
{
	public:
		string value;
		Node* prev;
		Node* next;
};

class LinkedList
{
	public:
		int size;
		Node* head;
		Node* tail;
		LinkedList()
		{
			head = NULL;
			tail = NULL;
			size = 0;
		}
		
		void insertEnd(string text)
		{
			Node* add = new Node;
			add->value = text;
			if(size==0) //when list is empty the head and tail will both point to the new node
			{
				head= add;
				tail = add;
			}
			if(size == 1)	//when only two elements, the head will point to first, the tail to the second
			{
				tail = new Node;
				tail->value = text;
				tail->prev = head;
				head->next = tail;
			}
			else 		//in all other instances it will simply be added to the tail
			{	
				
				tail->next = add;
				tail = add;
			}
			
			size++;
		}

		void insert(string text, int index)
		{
			Node* pre = new Node;
	    	Node* curr = new Node;
			Node* p = new Node;
			p->value = text;
			curr = head;
			if(index<=size)//will only insert if it doesnt cause a space between the previous tail and new node
			{
				if (size == 0) //if first node, both head and tail will point to it
			    {
			        head= p;
			        tail = p;
			        
			    }
			    else if (size == index) //if its at the end we can utilize other method
			    {
			    	
			    	insertEnd(text);
			    	size--;   //size is increased in insertEnd method and this method, but only needs to happen once
			    }
			    else if (index==0) // if its the first node it just needs to have the head point to it
			    {	
			    	p->next =head;
			    	head = p;
			    }
			    else
			    {

			        for(int i = 0; i < index; i++) //finds where to insert
			        {
			            pre = curr;
			             if (pre== NULL)   
			               break;   
			            curr = pre->next;
			        } 
			        p->value = text; //actual insertion of node
			        pre->next = p;
			        p->prev = pre;
			        p->next =curr;
			        curr->prev=p;
			    }
			    size++;
			}
		 
		}

		void del(int index)
		{
			
			Node* pre = new Node;
			Node* curr = new Node;
			Node* temp = new Node;
			if(index<size) //will only delete if node exists
			{
		    	pre = head;
		    	curr = pre->next;
		    	if (index == 0) //have the head point to the next node
			    {
			        head = head->next;
			        
			    }	
				else
			    {
			        for(int i = 0; i < index-2; i++) //find node to delete
			        {
			            pre = curr;
			     		curr= pre->next;
			        } 
			        if(size-1 == index) //if last node set tail to its previous node
			        {
			        	tail->value = curr->value;
			        	tail = curr;
			        	tail->next = NULL;
			        }
			        else 	//otherwise delete node
			        {
			        	temp = curr->next;
			        	pre->next= temp;
			        	temp->prev = pre;
			        }
			    
				}
		   	size--;
		    }
		}
		 void edit(string text, int index)
		{
			Node* pre = new Node;
	    	Node* curr = new Node;
	    	pre = head;
	    	curr = pre->next;
	    	if(index<size) //will only edit if it exists
	    	{
	    		if(index ==0) 
		    	{
		    		head->value = text;
		    	}
		    	else 
		    	{
		    		for(int i = 0; i < index-1; i++)
			    	{
			            pre = curr;
			     		curr= pre->next;
			    	}
			    	curr->value = text; 
		    	}
	    	}
		}
			
		void print()
		{
			Node* temp = new Node;
			temp = head;

			for(int i = 0; i<size;i++)
			{
				cout <<i+1<<" "<< temp->value << endl;
				if(temp->next != NULL)
					temp=temp->next;
					
			}			
		}
		void search(string text)
		{
			Node* curr = head;
		    int i = 1;
		    int done = 0;
		    do
		    {
		        if(curr->value.find(text) != string::npos) //if present it will print out the whole node
		        {
		           cout<<i<<" "<<curr->value<<endl;
		           done =1;
		        }
		        i++;
		        curr= curr->next;
		    }
		    while (curr->next != NULL); //goes through whole list except final element
		    if(curr->value.find(text) != string::npos) //checks final element
		        {
		           cout<<i<<" "<<curr->value<<endl;
		           done =1;
		        }
		    if (done != 1) //done will equal 0 if something was never found
		        cout<<"not found"<<endl;
		}    
};



int main()
{
	bool cont = true;
	string command;
	int pos;
	string com[3];
	int count =0;
	int ind;
	LinkedList* list = new LinkedList;
	while (cont== true)  // allows program to continue until quit is called
	{
		getline(cin,command); //takes in the whole string, which will later be parsed

		if ((pos=command.find(" ")) == (string::npos)) //if there are no spaces only one word, must be the command quit, 
		{
			com[0]=command; //com[0] always holds command
			count++;
		}
		else
		{
			pos=command.find(" ");   //command is always first word so will always precede first space
			com[0]=command.substr(0,pos);
			command.erase(0,pos+1);  //by erasing, if an index exists it will always be the first char of the new string
			count++;
		}
		
		pos=command.find('"');
		if(pos != string::npos)
		{
			com[1]= command.substr(pos+1,command.size()-pos-2); //text is always at the end, so by creating a substring from first instance of
			count++;											//" to the end of the string and subtract/add for size of " you get text
		}
		else
		{
			com[1]=command.at(0); 
			count++;
		}
		com[2]=command.at(0); //puts the index at com[2], if it exists
		if (count>1)
		{
			if ('0'<com[2].at(0)<'9')
			{
				ind = com[2].at(0)-'0'-1; // makes the index into a integer value, and subtracts 1 since it gives line number, rather than actual index
			}
		}
		if(com[0]=="insertEnd")
		{
			list->insertEnd(com[1]);
		}
		else if(com[0]=="insert")
		{
			list->insert(com[1],ind);
		}
		else if(com[0]=="delete")
		{
			list->del(ind);
		}
		else if(com[0]=="edit")
		{
			list->edit(com[1], ind);
		}
		else if(com[0]=="print")
		{
			list->print();
		}
		else if(com[0]=="search")
		{
			list->search(com[1]);
		}
		else if(com[0]=="quit")
		{
			cont = false; // causes the while loop to end

		} 
	} 
}




