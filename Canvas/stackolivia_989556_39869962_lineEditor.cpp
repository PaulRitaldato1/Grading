//your linked list implementation here
#include <iostream>

struct Node {
    public:
        std::string value;
        Node* next = NULL;
};

class list {
    public:
        Node* head;
		
		list();
    
        //Node* createNode(std::string text);
        Node* insert(int line, std::string text);
        Node* insertEnd (std::string text);
        Node* deleteNode(int line);
        Node* edit(int line, std::string text);
        void print();
        int search(std::string text); 
};

list::list()
{
	head = new Node;
	head->next= NULL;
};

Node* list::insert(int line, std::string text)
{
	Node* node = new Node;
	node->value = text;
    //point line-1 to this node; save a ref to line-1->next; point this node to line-1->next;
	Node* iter = new Node;
	iter=head;
	for (int i=0;i<line-1;i++)
	{
		iter=iter->next;
	}
	Node* temp = new Node;
	temp=iter->next;
	
	node->next = temp;
	iter->next = node;
	
	//head=this->head;
    return head;

}

Node* list::insertEnd(std::string text)
{
    Node* node= new Node;
    node->value = text;
    node->next = NULL;
    
    // iterate so that the last node points here instead of null
    Node* iter = new Node;
    iter = head;
    while ((iter->next) != NULL)
    {
        iter=iter->next;
    }
    iter->next = node;
	//delete iter; //is this how I want to delete the iterator to free memory?
	
	return head;
}

Node* list::deleteNode(int line)
{
	//check if it's head 
	//if next == data, then do the switch 
	//use two pointers for better code
	//current = next, prev = current , have another node for the deleted function so it's outside
	
	
	Node* prev = new Node;
	Node* curr = new Node;
	Node* bye = new Node;
	prev=head;
	if (prev->next!=NULL)
	{
		curr=prev->next;
	}
	for (int i=0;i<=line;i++)
	{
		prev=curr;
		curr=curr->next;
	}
	bye = curr;
	curr=curr->next;
	prev->next=curr;
	delete bye;
	
	return head;
};

Node* list::edit(int line, std::string text)
{
	Node* iter= new Node;
	iter=head;
	for (int i=1;i<=line;i++)
	{
		iter=iter->next;
	}
	iter->value=text;
	
	return head;
};

void list::print()
{
	int line = 1;
	Node* iter = new Node;
	iter=head;
    iter=iter->next;
	int index=iter->value.find('"');
	while (iter != NULL)
	{
		std::cout << line << " " << iter->value.substr(index+1,(iter->value).size()-(index+2)) <<std::endl;
		line++;
        iter=iter->next;
	}
};

//use an int iterator; go through list until there is some matching text found; 
//If found, print out line number and value of that node. Return line number. 
//If not found, print "not found" and return -1;

/*
int index=input.find('"'); 
std::string text = input.substr(index+1,input.size()-(index+2));
*/
int list::search(std::string text)
{
	int i=1;
	Node* iter = new Node;
	iter=head;
	iter=iter->next;
	std::size_t found;
	int index=iter->value.find('"');
	while (iter !=NULL)
	{
		found =(iter->value).find(text);
		if (found!=std::string::npos)
        {
            std::cout << i << " " << iter->value.substr(index+1,(iter->value).size()-(index+2)) << std::endl;
			return 0;
        }
		iter=iter->next;
		i++;
	}
	std::cout << "not found" << std::endl;
	return 1;
};


/* functions to create:

insertEnd "text"  -- insert given text at the end of the document
insert 3 "text" --insert given text at the line indicated by index given
delete 3 --- delete line at index given
edit 3 "text" --- replace the line at the index given with the given text
print -- print the entire document, with line numbers
search "text" -- print the line number and line that contains the given text.  print "not found" if it is not found

*/




        //your line editor implementation here
int main()
{
    //your code to invoke line editor here
    list* lineEdit = new list;
	
	std::string input;
	bool isQuit=true;
    
	while (isQuit)
	{
		std::getline(std::cin, input);
        
		if (input.find("insertEnd")!=std::string::npos)
		{
			lineEdit->insertEnd(input);
		}
		else if (input.find("insert")!=std::string::npos)
		{
			//TODO: parse for line and text
            int line;
            std::string text;
            lineEdit->insert(line, text);
		}
		else if (input.find("delete")!=std::string::npos)
		{
            //TODO: parse for line
			int line;
			lineEdit->deleteNode(line);
		}
		else if (input.find("edit")!=std::string::npos)
		{
			int line;
			//TODO: parse to find line and text 
			int index=input.find('"');
			std::string text = input.substr(index-3,input.size()-(index));
			
			lineEdit->edit(2, input);
		}
		else if (input.find("print")!=std::string::npos)
		{
			lineEdit->print();
		}
		else if (input.find("search")!=std::string::npos)
		{
            //search for position of first quote, rfind for last quote
            int index=input.find('"');
			std::string text = input.substr(index+1,input.size()-(index+2));
            lineEdit->search(text);
		}
		else 
		{
			isQuit=false;
		}
		
	}
	
    
}