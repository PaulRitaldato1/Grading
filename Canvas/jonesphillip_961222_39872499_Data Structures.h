#include <iostream>
#include <string>
#include <string.h>

using namespace std;

struct Node
{
	char data[80];
	Node *next;
};

Node* insert_front(Node* head, string &s)
{
	Node *temp = new Node;
	strcpy(temp->data, s.c_str());
	temp->next = head;
	return temp;
}

void insert_end(Node* head, string &s)
{
    Node* temp = head;
    Node* newNode = new  Node;
    newNode->next = NULL;
    string st = s.substr(2);
    int pos = st.find("\"");
    string str = s.substr(2,(pos));
    strcpy(newNode->data, str.c_str());
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insert(Node* head, int pos, string &s)
{
    Node* temp = head;
    Node* newNode = new Node;
    Node *prevNode = temp;
    Node *nextNode = temp->next;
    for(int i = 0; i < (pos-1); i++)
    {
        prevNode = nextNode;
        nextNode = prevNode->next;
    }
    newNode->next = nextNode;
    string st = s.substr(2);
    int posQ = st.find("\"");
    string str = s.substr(2,(posQ));
    strcpy(newNode->data, str.c_str());
    prevNode->next = newNode;
}

void deleteNode(Node* head, int pos)
{   
    Node* currNode = head->next;
    Node* prevNode = head;
    Node* nextNode = head->next->next;
    for(int i = 1; i < pos; i++)
    {
        prevNode = currNode;
        currNode = currNode->next;
        nextNode = nextNode->next;
    }
    prevNode->next = currNode->next;
}

void edit(Node* head, int pos, string &s)
{
    Node* temp = head;
    for(int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    strcpy(temp->data, s.c_str());
}

void print(Node* head)
{
    Node *temp = head->next;
    int lineNumber = 1;
    while(temp->next != NULL)
    {
        cout << lineNumber << " " << temp->data;
        cout << "\n";
        temp = temp->next;
        lineNumber++;
    }
    cout << lineNumber << " " << temp->data << "\n";
}

void search(Node* head, string &s)
{
    Node *temp = head;
    int lineNumber = 0;
    string data;
    bool f = false;
    while(temp->next != NULL)
    {
        data = temp->data;
        size_t found = data.find(s);
        if(found != string::npos)
        {
            cout << lineNumber << " " << data << "\n";
            f = true;
        }
        lineNumber++;
        temp = temp->next;
    }
    data = temp->data;
    size_t found = data.find(s);
        if(found != string::npos)
        {
            cout << lineNumber << " " << data << "\n";
            f = true;
        }
    if(!f)
        cout << "not found\n";
    
}

int main()
{
	Node *head = new Node;
    head->next = NULL;
    int numItems = 0;
    int loop = 1;
    string instruction;
    int counter = 1;
    while(loop == 1 && counter < 100)
    {
        cin >> instruction;
        if(instruction.compare("insertEnd") == 0)
        {
            string s;
            getline(cin, s);
            insert_end(head, s);
            numItems++;
        }
        else if(instruction.compare("insert") == 0)
        {
            int pos;
            cin >> pos;
            string s;
            getline(cin, s);
            if(pos <= numItems + 1)
            {
                if(pos > 1)
                    insert(head, pos, s);
                else if(pos == 1)
                    head = insert_front(head, s);
                numItems++;
            }
        }
        else if(instruction.compare("delete") == 0)
        {
            int pos;
            cin >> pos;
            if(pos <= numItems)
            {
                deleteNode(head, pos);
                numItems--;
            }
        }
        else if(instruction.compare("edit") == 0)
        {
            int pos;
            cin >> pos;
            string s;
            getline(cin, s);
            string st = s.substr(2);
            int posQ = st.find("\"");
            string str = s.substr(2,(posQ));
            edit(head, pos, str);
        }
        else if(instruction.compare("search") == 0)
        {
            string s;
            getline(cin, s);
            string st = s.substr(2);
            int pos = st.find("\"");
            string str = s.substr(2,(pos));
            search(head, str);
        }
        else if(instruction.compare("print") == 0)
        {
            print(head);
        }
        else if(instruction.compare("quit") == 0)
        {
            loop = 2;
        }
        counter++;
    }
            
            
        
    
}