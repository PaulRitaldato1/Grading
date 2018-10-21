#include <string>
#include <iostream>
using namespace std;
//your linked list implementation here
struct Node
{
    std::string value; //maybe limit to 80 characters e.g. char val[80];
    Node* next;
};

class LinkedList
{
    public:
    Node* head;
    LinkedList()
    {
        head = NULL;
    }
};

class Document
{
    public:
    LinkedList* list;
    Document()
    {
        list = new LinkedList();
    }
    void print() //tested and works
    {
        int lineNum = 1;
        Node* n = list->head;
        while(n != NULL)
        {
            cout << lineNum << " " << n->value << endl;
            lineNum++;
            n = n->next;
        }
    }
    void insertEnd(std::string line) //tested and works
    {
        Node* n = new Node();
		Node* newNode = new Node();
		newNode->value = line;
		newNode->next = NULL;
		
		n = list->head;
		if(n == NULL)
		{
			list->head = newNode;
		}
		else
		{
			while(n->next != NULL)
			{
				n = n->next;
			}
			n->next = newNode;
		}
        
		
		
    }
    void insert(int lineIndex, std::string line) // inserting at 1 and beyond the end crashes the program
    {
		
		if(lineIndex < 1)
			return;
		
		if(lineIndex == 1)
		{
			Node* t = new Node();
			t->value = line;
			t->next = list->head;
			list->head = t;
		}
		
        int count = 1;
        Node* n =  new Node();
		n = list->head;
        Node* newNode = new Node();
        newNode->value = line;
		newNode->next = NULL;
		
        while(count != (lineIndex-1) && n != NULL)
        {
			
            n = n->next;
			
            count++;
			
			
        }
        if(n == NULL)
			return;
        newNode->next = n->next;
        n->next = newNode;
        
    }
    void del(int lineIndex) //deleting -- works?
    {
		
		if(lineIndex == 1)
		{
			list->head = list->head->next;
			return;
		}
		
		
		
        int count = 1;
        Node* n = new Node();
		n = list->head;
        while(count != (lineIndex-1) && n != NULL)
        {

            n = n->next;
			
            count++;
        }
        if(n == NULL || n->next == NULL)
			return;
        n->next = n->next->next;
        
    }
    void edit(int lineIndex, std::string line)
    {
        int count = 1;
        Node* n = new Node();
		n = list->head;
        while(count < lineIndex && n != NULL)
        {
            n = n->next;
            count++;
        }
        n->value = line;
    }
    void search(std::string text) // works
    {
        Node* n =  new Node();
		n = list->head;
        int count = 1;
		bool fl = true;
        while(n != NULL)
        {
            if(n->value.find(text) != std::string::npos)
            {
                cout << count << " " << n->value << endl;
				fl = false;
            }
            count++;
			n = n->next;
        }
		if(fl)
			cout << "not found" << endl;
    }
    
};
        //your line editor implementation here

int main()
{
    //your code to invoke line editor here
    string line = "";
    int index = -1;
    string cmd = "";
    Document* doc = new Document();
    string secondToken = "";
    string thirdToken = "";
    
    while(line != "quit")
    {
        getline(cin, line);
        cmd = line.substr(0, line.find(" "));
        
        secondToken = line.substr(line.find(" ")+1,line.length() - (line.find(" ")+1));
        thirdToken = secondToken.substr(secondToken.find(" ")+1,secondToken.length() - (secondToken.find(" ")+1));
        if(cmd == "print" || line == "print")
            doc->print();
        else if(cmd == "insert")
        {
            doc->insert(stoi(secondToken.substr(0, secondToken.find(" "))), thirdToken.substr(1, secondToken.length() - (3 + (secondToken.substr(0, secondToken.find(" ")).length()) ))); //not right?
        }
        else if(cmd == "insertEnd")
        {
            doc->insertEnd(secondToken.substr(1, secondToken.length() - 2));
        }
        else if(cmd == "delete")
        {
            doc->del(stoi(secondToken.substr(0, secondToken.find(" ")))); // not right?
        }
        else if(cmd == "search")
        {
			doc->search(secondToken.substr(1, secondToken.length() - 2));
        }
        else if(cmd == "edit")
        {
			doc->edit(stoi(secondToken.substr(0, secondToken.find(" "))), thirdToken.substr(1, secondToken.length() - (3 + (secondToken.substr(0, secondToken.find(" ")).length()) )));
        }
        else if(cmd == "quit" || line == "quit") //The command syntax was not recognized
        {
			break;
			
        }
		else
		{
			cout << "command not recognized" << endl;
		}
        
    }
    
}