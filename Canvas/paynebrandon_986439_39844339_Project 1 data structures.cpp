#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

//your linked list implementation here

struct Node
{
    std::string data;
    Node * next;
};

class list
{
    private:
        Node * head;
        Node * tail;
    public:
        void search(string userData);
        void insertEnd(string userData);
        void insert(int line, string userData);
        void del(int line);
        void edit(int line, string userData);
        void print();
        list()         
        {                     //makes list empty
            head = NULL;
            tail = NULL;
        }
};

//your line editor implementation here

void list::insertEnd(string userData) //inserts new node/line at the end of the list
{
    if (userData.size() > 80)  //80 character limit per line
    {
        return;
    }
    
    Node * temp = new Node;
    temp->data = userData;   
    temp->next = NULL;
    
    if (head == NULL) //if list is empty, new node is head and tail
    {
        head = temp;
        tail = temp;
        temp = NULL;
        return;
    }
    
    else //new node is added to end. tail is moved
    {
        tail->next = temp;
        tail = temp;
        return;
    }
}

void list::insert(int line, string userData)  //inserts a node/line anywhere in the list
{
    if (userData.size() > 80)  //80 character limit per line
    {
        return;
    }
    
    int index = 1;
    Node * temp = new Node;
    
    if (line == 1)   //makes new head if adding to the beginning
    {
        temp->data = userData;
        temp->next = head;
        head = temp;
    }
    
    Node * prev = new Node;
    Node * curr = head;
    
    for (index = 1; index < line; index++)
    {
        if (curr == NULL)  //end of list, index does not exist
        {
            if (curr == tail->next && ++index == line) //makes new tail. adds to end of list
            {
                curr->data = userData;
                tail->next = curr;
                tail = curr;
                return;
            }
            return;
        }  
        prev = curr;
        curr = curr->next;
    }
    temp->data = userData;
    prev->next = temp;
    temp->next = curr;
    return;
}

void list::del(int line)
{
    int index = 1;
    Node * prev = new Node;
    Node * curr = head;
    
    if (line == 1)   //deletes from front of list
    {
        head = head->next;
        return;
    }
    for (index = 1; index < line; index++)
    {
        if (curr == tail) //if line does not exist  
        {
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    
    
    curr = curr->next; //deletes line in between
    prev->next = curr;
}

void list::print() //prints page
{
    int line = 1;
    Node * curr = head;
    
    while (curr != NULL)
    {
        cout<< line++ << " " << curr->data <<endl;
        curr = curr->next;
    }
}

void list::edit(int line, string userData)  //edits a node/line
{
    if (userData.size() > 80)  //80 character limit per line
    {
        return;
    }
    
    int index = 1;
    Node * curr = head;
    
    while (curr != NULL && index < line)
    {
        curr = curr->next;
        index++;
    }
    if (curr == NULL)
    {
        return;
    }
    curr->data = userData;
}

void list::search(string userData)  //prints page number
{
    int index = 1;
    Node * curr = head;
    bool found = false;
    
    //if seraching for empty string, will return every line
    
    while (curr != NULL)
    {    
        if (curr->data.find(userData)!= string::npos)
        {
            cout<< index << " " << curr->data <<endl;
            found = true;
        }
        curr = curr->next;
        index++;
    }
    if (!found)
    {
        cout<<"not found"<<endl;
    }
    return;
}

int main()
{
    //your code to invoke line editor here
    
    list myList;  
    
    int lineNumber = 0;
    string response = "";
    string text = "";    
    
    while (response != "quit")
    {
    response = "";
    text = "";
    cin >> response;        //gets command from input
    getline(cin, text);     //gets the line number and text from input
      
    if (response == "insertEnd")
    {
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.front() == '"')
        {
            text.erase(0,1);
        }
        if (text.back() == '"')
        {
            text.erase(text.length()-1,text.length());
        }
          myList.insertEnd(text);
    }
        
    if (response == "insert")
    {
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.length() >0)
        {
        if (isdigit(text.at(0)))
            {
                lineNumber = text.front() - '0';
                text.erase(0,1);
            }
        }
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.front() == '"')
        {
            text.erase(0,1);
        }
        if (text.back() == '"')
        {
            text.erase(text.length()-1,text.length());
        }
        if (lineNumber > 0)
        {
            myList.insert(lineNumber, text);
        }
    }
        
    if (response == "delete")
    {
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.length() > 0)
        {
            if (isdigit(text.at(0)))
            {
                lineNumber = text.front() - '0';
            }
        }
        if (lineNumber > 0)
        {
            myList.del(lineNumber);
        }
    }
        
    if (response == "edit")
    {
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.length() > 0)
        {
            if (isdigit(text.at(0)))
            {
                lineNumber = text.front() - '0';
                text.erase(0,1);
            }
        }
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.front() == '"')
        {
            text.erase(0,1);
        }
        if (text.back() == '"')
        {
            text.erase(text.length()-1,text.length());
        }
        if (lineNumber > 0)
        {
            myList.edit(lineNumber, text);
        }
    }
        
    if (response == "print")
    {
        myList.print();
    }
        
    if (response == "search")
    {
        while (text.front() == ' ')
        {
            text.erase(0,1);
        }
        if (text.front() == '"')
        {
            text.erase(0,1);
        }
        if (text.back() == '"')
        {
            text.erase(text.length()-1,text.length());
        }
        myList.search(text);
    }
        lineNumber = 0;
        text = "";
        
    }
    return 0;
}