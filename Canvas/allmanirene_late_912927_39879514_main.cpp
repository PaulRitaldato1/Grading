//  Proj 1 COP3530
//  Created by Irene Allman on 9/20/18.

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Node //NODE CLASS
{
    friend class List; //So list can access private elems
    
private:
    Node* next;
    string data; //To store phrase
public:
    Node();
};

class List //LINKED LIST CLASS
{
public:
    List();
    void insertEnd(string phrase);
    void insert(int index, string phrase);
    void del(int index);
    void edit(int index, string phrase);
    void print();
    void search(string search);
    int getsize();
    int size = 0;
private:
    Node* head;
};

Node::Node() //Initializes a node with next pointing to nothing
{
    next = NULL;
}

List::List() //Initializes a list without nodes and size of 0
{
    head = NULL; //In header as a pointer to head of list
}
void List::insertEnd(string phrase)
{
    Node* add = new Node();
    size++;
    
    if(head == NULL) //Checks is list is empty
    {
        head = add;
        head->next = NULL;
        head->data = phrase; //If phrase should be set here**
    }
    
    else
    {
        Node* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next; // Iterate until empty next node
        }
        temp->next = add;
        add->data = phrase;
        add->next = NULL;
    }
}

void List::insert(int index, string phrase)
{
    Node* add = new Node();
    add->data = phrase;
    Node* curr = head;
    size++;
    
    if(index == 1)
    {
        curr = head;
        head = add;
        add->next = curr;
    }
    else
    {
        if(curr->next != NULL)
        {
            for(int i = 0; i < (index-2); i++)
            {
                curr = curr->next;
            }
            
            add->next = curr->next;
            curr->next = add;
        }
    }
}
void List::del(int index)
{
    Node* temp = head;
    Node* toDel = head;
    size--;
    
    if(index == 1) //special case for if deleting head
    {
        head = head->next;
        free(temp);
    }
    else if(index == 2)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    else
    {
        for(int i = 0; i < (index-2); i++)
        {
            temp = temp->next;
            toDel = temp->next;
        }
        if(toDel!= NULL)
        {
            temp->next = toDel->next;
        }
        free(toDel);
    }
    
}
void List::edit(int index, string phrase)
{
    Node* add = new Node();
    add->data = phrase;
    
    if(index == 1)
    {
        add->next = head->next;
        head = add;
    }
    else if(index == 2)
    {
        Node* temp = head->next;
        head->next = add;
        add->next = temp->next;
        free(temp);
    }
    else
    {
        Node* temp = head;
        Node* curr = NULL;
        for(int i = 0; i < (index-2); i++)
        {
            temp = temp->next;
            curr = temp->next;
        }
        temp->next = add;
        add->next = curr->next;
    }
}
void List::print()
{
    Node* toPrint = head;
    int counter = 1;
    while(toPrint != NULL)
    {
        cout << counter << " " << toPrint->data << "\n" ;
        toPrint = toPrint->next;
        counter++;
    }
}
void List::search(string search)
{
    Node* toSearch = head;
    bool match = false;
    int line = 1;
    
    while(true) //Loop until NULL is reached without finding match
    {
        if(toSearch == NULL)
        {
            if(match == false)
            {
                cout << "Not found\n";
            }
            break;
        }
        
        string strCheck = toSearch->data;
        
        size_t index = strCheck.find(search);
        if(index == string::npos)
        {
            line++;
        }
        else
        {
            cout << line << " " << toSearch->data << "\n";
            match = true;
            line++;
        }
        toSearch = toSearch->next;
    }
}
int List::getsize()
{
    return size;
}

int main() {
    
    List* LL = new List();
    string input;
    while(true) //LOOPS MENU TO ADD COMMANDS
    {
        string input;
        getline(cin, input);
        
        if(input == "quit") { break; }
        if(input == "print") { LL->print(); }
        
        string cmd = "";
        string index = "";
        string lineTxt = "";
        
        //Cmd parse
        for(int i = 0; i < input.length(); i++)
        {
            if(input[i] == ' ')
            {
                input = input.substr(i+1, input.length()-1);
                break;
            }
            cmd += input[i];
        }
        //Index parse
        for(int i = 0; i < input.length(); i++)
        {
            if(input[i] == '"')
            {
                break;
            }
            if(input[i] == ' ')
            {
                input = input.substr(i+1, input.length()-1);
                break;
            }
            index += input[i];
        }
        //Line Text parse
        for(int i=0; i < input.length(); i++)
        {
            if(input[i] == '"')
            {
                lineTxt = input.substr(i+1, input.length()-2);
                break;
            }
        }
        //CARRY OUT METHODS BASED ON CMD VALUE
        if(cmd == "insertEnd") { LL->insertEnd(lineTxt); }
        if(cmd == "insert") { if(stoi(index) <= (LL->size)+2) {LL->insert(stoi(index), lineTxt);} } //CONVERT STR TO NUM
        if(cmd == "delete") { if(stoi(index) <= (LL->size)+1) {LL->del(stoi(index));} }
        if(cmd == "edit") { if(stoi(index) <= (LL->size)+1) {LL->edit(stoi(index), lineTxt);} }
        if(cmd == "search") { LL->search(lineTxt); }
    }
    return 0;
}
