#include <iostream>
#include <string>

class LinkedList
{
private:
	struct nodeObject {
		std::string data;
		nodeObject *next;
	};
	typedef struct nodeObject * nodePointer;
	nodePointer head;
	nodePointer tail;

public:
	LinkedList();
	void search(std::string value);
	void addNode(std::string value);
	void addNode(int index, std::string value);
	void editNode(int index, std::string value);
	void deleteNode(int index);
	void printList();
};
LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
}

void LinkedList::search(std::string value)
{
	nodePointer p= head;
	int count = 1;
    bool found=false;
	while (p != NULL)
	{
		if (p->data.find(value)!=std::string::npos)
		{
			std::cout <<count<< " "<< p->data<<"\n";
            found=true;
		}
		p = p->next;
		count++;
	}

    if(!found)
        std::cout << "not found\n";

	
}


void LinkedList::addNode(std::string value)
{
	if (value.size() > 80)
	{
		std::cout << "Text too long. Please keep below 80 characters.";
		return;
	}

	nodePointer newTail = new nodeObject;
	newTail->data = value;
	newTail->next = NULL;

	if (head != NULL) //if LinkedList has element(s).
	{
		tail->next = newTail;
		tail = newTail;
	}
	else //if LinkedList is empty
	{
		tail = newTail;
		head = newTail;
	}
}

void LinkedList::addNode(int index, std::string value)
{
	if (value.size() > 80)
	{
		return;
	}

	nodePointer newNode = new nodeObject;
	newNode->data = value;
    bool check=true;
    
	if (index == 0)
	{
		newNode->next = head;
		head = newNode;
	}
	else 
	{
		nodePointer track = head;

		for (int i = 0; i < index-1; i++)
		{
			if (track != NULL)
				track = track->next;
			else
            {
                check=false;
                i=index;
            }
		}
        if (track != NULL &&check)
        {
		    newNode->next = track->next;
		    track->next = newNode;
        }
	}

}
void LinkedList::editNode(int index, std::string value)
{
	if (index < 0)
	{
		return;
	}
	else if(head==NULL)
	{
		return;
	}


	nodePointer p = head;
	for (int i = 0; i < index; i++)
	{
		if (p->next != NULL)
			p = p->next;
		else
		{
			return;
		}
	}

	p->data = value;
}

void LinkedList::deleteNode(int index)
{
	if (head == NULL)
	{
		return;
	}
	if (index < 0)
	{
		return;
		
	}
	if (index == 0)
	{
		nodePointer p = head->next;
		delete head;
		head = p;
	}
	else 
	{
		nodePointer p;
		nodePointer q;
		p = head;
		q = head;

		for (int i = 0; i < index; i++)
		{
			if (q->next != NULL)
			{
				p = q;
				q = q->next;
			}
			else
			{
				return;
			}
		}

		p->next = q->next;
		delete q; //Valgrind on ubuntu
	

	}

}

void LinkedList::printList()
{
	nodePointer p = head;
	int line = 1;
	while (p != NULL)
	{
		std::cout << line<< " "<<p->data << "\n";
		p = p->next;
		line++;
	}


}

class LineEditor
{
private:
	LinkedList document;

public:
	LineEditor();
	void start();
};

LineEditor::LineEditor()
{
	LinkedList document;
}

void LineEditor::start() {
	bool t = true;

	while (t)
	{
        
		std::string input = "";
		getline(std::cin, input);


		std::string temp = input.substr(0, input.find(" "));

		if (temp.compare("insertEnd") == 0)
		{
            int start=input.find("\"")+1;
            int length= input.rfind("\"")-1-input.find("\"");
            
			temp = input.substr(start , length);
            

			document.addNode(temp);
		}
		else if (temp.compare("insert") == 0)
		{
			temp = input.substr(input.find(" ") + 1);
			std::string temp2 = temp.substr(0, temp.find(" "));
			int index = stoi(temp2);            //converts string to int.
            
            int start=input.find("\"")+1;
            int length= input.rfind("\"")-1-input.find("\"");
            
			temp = input.substr(start , length);
			

			document.addNode(index - 1, temp);

		}

		else if (temp.compare("edit") == 0)
		{
			temp = input.substr(input.find(" ") + 1);
			std::string temp2 = temp.substr(0, temp.find(" "));
			int index = stoi(temp2);            //converts string to int.

			int start=input.find("\"")+1;
            int length= input.rfind("\"")-1-input.find("\"");
            
			temp = input.substr(start , length);

			document.editNode(index - 1, temp);

		}
		else if (temp.compare("print") == 0)
		{
			document.printList();

		}
		else if (temp.compare("search") == 0)
		{
			int start=input.find("\"")+1;
            int length= input.rfind("\"")-1-input.find("\"");
            
			temp = input.substr(start , length);
            
			document.search(temp);

		}
		else if (temp.compare("delete") == 0)
		{
			temp = input.substr(input.find(" ") + 1);
			int index = stoi(temp);            //converts string to int.
			document.deleteNode(index - 1);
        }

		else if (temp.compare("quit") == 0)
		{
			t = false;
		}
		else
			std::cout << "Invalid command.\n\n";

	}
}

int main()
{
    LineEditor proj;
	
	proj.start();
	return 0;
}