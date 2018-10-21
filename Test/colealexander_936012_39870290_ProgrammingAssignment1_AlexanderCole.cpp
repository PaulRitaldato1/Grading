//Alexander Cole
//Data Structures and Algorithms
//COP3530
//21 September 2018

#include <string> 
#include <cstdlib> 
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//your linked list implementation here

struct node
{
    string line;
    node *next;
};

class List
{
    private:
        node * head;
        node * tail;
        int size;
    public:
    List()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    void insertEnd(string str);
    void insertNode(int index, string str);
    void deleteNode(int index);
    void editNode(int index, string str);
    void search(string str);
    void print();
};

void List::insertEnd(string str)
{
    //create a new node poiner "temp".
    node * temp = new node;
    temp->line = str;
    temp->next = NULL;
    //special condition for new node
    if(head == NULL)
    {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else
    { 
    //typical insertion at end
        tail->next = temp;
        tail = temp;
    }
    size++;
}
void List::print()
{
    //new node pointer "temp" will serve as an iterator.
    node * temp = new node;
    temp = head;
    int i = 1;
    //iterate through the list, and print the list's line data.
    while(temp!=NULL)
    {
        cout << i << " " ;
        cout << temp->line;
        cout << endl;
        temp = temp->next;
        i++;
    }
}
void List::insertNode(int index, string str)
{
    //filter our invalid index inputs.
    if(index < 1 || (index > size+1))
    {
        return;
    }
    if(index == size + 1)
    {
        insertEnd(str);
        return;
    }
    node * temp = new node;
    temp->line = str;
    //special case for insertion at the head.
    if(index == 1)
    {
        size++;
        temp->next = head;
        head = temp;
        return;
    }
    //create iterator node pointers, p and q.
    node * p = new node;
    node * q = new node;
   
    p = head;
    //iterate through list to the given index.
    for(int i = 1; i < index; i++)
    {
        q = p;
        p = p->next;                  
    }
    size++;
    //insert node.
    q->next = temp;
    temp->next = p;
}
void List::deleteNode(int index)
{
    //filter out invalid index inputs.
    if(index < 1 || index > size)
    {
        return;
    }
    //create iterator node pointer "p".
    node * p = new node;
    p = head;
    //special case for head removal.
    if(index == 1)
    {
        head = head->next;
        delete p;
        size--;
        return;
    }
    //create iterator node pointer "q".
    node * q = new node;
    //iterate through list to given index.
    for(int i = 1; i < index; i++)
    {
        q = p;
        p = p->next;
    }
    //special case for tail removal. 
    if(p->next == NULL)
        {
            size--;
            tail = q;
            q->next = NULL;
            delete p;
            return;
        }
    size--;
    //delete node in middle of list.
    q->next = p->next;
}

void List::editNode(int index, string str)
{
    //filter for invalid index input.
    if(index < 1 || index > size)
    {
        return;
    }
    //create iterator node pointer "temp".
    node * temp = new node;
    temp = head;
    //iterate to find index of node to edit.
    for(int i = 1; i < index; i++)
    {
        temp = temp->next;
    } 
    //replaces line with string. 
    temp->line = str;
}

string processString(string str)
{
    //create a char array that maxes out at 80 characters.
    char rawData[80];
    //copy the first 80 characters of the input to the array.
    strcpy(rawData, str.c_str());
    //remove quotations expected in the input.
    for(int i = 0; i < str.size() ; i++)
    {
        rawData[i] = rawData[i + 2];
    }
    for(int i = str.size(); i > str.size()-4; i--)
    {
        if(rawData[i])
        {
            rawData[i] = NULL;
        }
    }
    //convert back to a string.
    string data(rawData);
    return data;
}

void List::search(string str)
{
    //special case: empty list
    if(head == NULL)
    {
        cout << "not found";
        return;
    }
    //index place holder i.
    int i = 1;
    //k counts the number of finds.
    int k = 0;
    //create iterator node pointer.
    node * temp = new node;
    temp = head;
    //iterate through entire list.
    while(temp!=NULL)
    {
        //search line of current node for input as a substring.
        if(temp->line.find(str) != string::npos)
        {
            //print index with entire line containing substring input. 
            cout<< i << " " << temp->line << endl;
            k++;
        }
            i++;
            temp = temp->next;
    }
    //if no matches detected, return failiure message.
    if(k == 0)
    {
        cout << "not found" << endl;
    }    
}

int main() 
{
    string option;
    char lineNumber;
    string str;   
    List myList;
    
    while(option.compare("quit"))
    {
        //expected first word of line to be option.
        cin >> option;
        
        if(!option.compare("insertEnd"))
        {  
            //expected next input to be the line.
            getline(cin, str);
            //trim input text of quotations
            str = processString(str);
            myList.insertEnd(str);   
        }
        if(!option.compare("insert"))
        {
            //expected next input to be the index number.
            cin >> lineNumber;
            //parse input into an integer
            int a = lineNumber;
            a = a - 48; 
            //expected next input to be the line.
            getline(cin, str); 
            str = processString(str);
            myList.insertNode(a,str);
        }
        if(!option.compare("delete"))
        {  
            cin >> lineNumber;
            int a = lineNumber;
            a = a - 48;
            getline(cin, str);
            myList.deleteNode(a);
        }
        else if(!option.compare("edit"))
        {
            cin >> lineNumber;
            int a = lineNumber;
            a = a - 48 ;
            getline(cin, str);
            str = processString(str);
            myList.editNode(a, str);
        }
        else if(!option.compare("print"))
        { 
            myList.print();
        }
        else if(!option.compare("search"))
        {
            getline(cin, str);
            str = processString(str);
            myList.search(str);
        }
        else if(!option.compare("quit"))
        {
        
        }
        
    }
    return 0;
}