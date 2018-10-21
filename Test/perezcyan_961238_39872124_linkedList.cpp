#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cctype>
#include<algorithm>
using namespace std;

//creating a node
struct node
{
    string info;
    struct node *next;
}*start;
 

//creating a class for the singly linked list
class linkedList
{
    public:
        node* create_node(string);
        void insert(int lineNum, string line);
        void insertEnd(string line); 
        void delete_pos(int lineNum);
        void search(string line);
        void edit(int lineNum, string line);
        void print();
        linkedList() 
        {
            start = NULL;
        }
};
 
//MAIN CLASS
main()
{
    int element, position, i;
    string command;
    string nodes;
    linkedList sl;
    start = NULL;
    while (1)
    {
        string str;
        getline(cin, str);

        string command = str.substr(0, str.find(' '));
        str.erase(0, str.find(' '));

        if (command=="insertEnd") {
            str.erase(
                remove(str.begin(), str.end(), '\"'),
                str.end()
                );
            string line = str;
            sl.insertEnd(line);
        } else if (command == "insert") {
            int lineNum = stoi(str.substr(0));
            str.erase(0,str.find('"'));
            str.erase(
                remove(str.begin(), str.end(), '\"'),
                str.end()
                );
            string line = str;
            sl.insert(lineNum, line);
        } else if (command == "edit") {
            int lineNum = stoi(str.substr(0));
            str.erase(0,str.find('"'));
            str.erase(
                remove(str.begin(), str.end(), '\"'),
                str.end()
                );
            string line = str;
            sl.edit(lineNum, line);
        } else if (command == "delete") {
            int lineNum = stoi(str.substr(0));
            str.erase(0,str.find('"'));

            sl.delete_pos(lineNum);
        } else if (command == "print") {
            sl.print();
        } else if (command == "search") {
            str.erase(
                remove(str.begin(), str.end(), '\"'),
                str.end()
                );
            string line = str;
            sl.search(line);
        }else {
            exit(1);
        }
        
    }
}
 
//create a node
node *linkedList::create_node(string line)
{
    struct node *temp, *s;
    temp = new(struct node); 
    if (temp == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        temp->info = line;
        temp->next = NULL;     
        return temp;
    }
}
 
 
//insertEnd command
void linkedList::insertEnd(string line)
{
    struct node *temp, *s;
    temp = create_node(line);
    s = start;
    while (s->next != NULL)
    {         
        s = s->next;        
    }
    temp->next = NULL;
    s->next = temp;
}
 
//insert command
void linkedList::insert(int lineNum, string line)
{
    int counter = 0; 
    struct node *temp, *s, *ptr;
    temp = create_node(line);
    int i;
    s = start;
    while (s != NULL)
    {
        s = s->next;
        counter++;
    }
    if (lineNum == 1)
    {
        if (start == NULL)
        {
            start = temp;
            start->next = NULL;
        }
        else
        {
            ptr = start;
            start = temp;
            start->next = ptr;
        }
    }
    if (lineNum > 1  && lineNum <= (counter+1))
    {
        s = start;
        for (i = 1; i < lineNum; i++)
        {
            ptr = s;
            s = s->next;
        }
        ptr->next = temp;
        temp->next = s;
    }
}
 
 
//delete
void linkedList::delete_pos(int lineNum)
{
    int i, counter = 0;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    struct node *s, *ptr;
    s = start;
    if (lineNum == 1)
    {
        start = s->next;
    }
    else
    {
        while (s != NULL)
        {
            s = s->next;
            counter++;  
        }
        if (lineNum > 0 && lineNum <= counter)
        {
            s = start;
            for (i = 1;i < lineNum;i++)
            {
                ptr = s;
                s = s->next;
            }
            ptr->next = s->next;
        }
        else
        {
            cout<<"Position out of range"<<endl;
        }
        free(s);
    }
}
 
/*
 * edit a given Node
 */
void linkedList::edit(int lineNum, string line)
{
    int i;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    struct node *s, *ptr;
    s = start;
    if (lineNum == 1)
    {
        start->info = line; 
    }
    else
    {
        for (i = 0;i < lineNum - 1;i++)
        {
            if (s == NULL)
            {
                cout<<"There are less than "<<lineNum<<" elements";
                return;
            }
            s = s->next;
        }
        s->info = line;  
    }
} 
 
//search
void linkedList::search(string line)
{
    int pos = 0;
    bool flag = false;
    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info.find(line) != string::npos)
        {
            flag = true;
            cout<<pos<<" "<<s->info<<endl;
        }
        s = s->next;
    }
    if (!flag)
        cout<<"not found"<<endl;  
}
 
//print
void linkedList::print()
{
    struct node *temp;
    int lineNum = 1;
    if (start == NULL)
    {
        cout<<"The list is empty"<<endl;
        return;
    }
    temp = start;
    while (temp != NULL)
    {
        cout<<lineNum<<" "<<temp->info<<endl;
        temp = temp->next;
        lineNum++;
    }
}