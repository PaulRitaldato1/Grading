#include<bits/stdc++.h>
#include <iostream>

using namespace std;

struct node
{
    string data;
    struct node *next;
};

struct node *start=NULL; //this variable will cause the list to always point to the 1st line

//Functions
struct node* addLine(void);
void insertnodeatlast(struct node *,string);
void insertnodeatline(struct node *,int,string);
void deletenode(struct node *,int);
void edit(struct node *,int,string);
void viewnode(struct node *);
void search(struct node *,string);

int main()
{
    string command; //TO store user's input
    string temp; //To store "text"
    string str_index; //To store index in string format
    int index,p; //p is for temporary storage
    stringstream ss;

    while(1) //continuous loop until user wants to quit
    {
        getline(cin,command);
        if(command=="print")
        {
            viewnode(start);
        }
        else if(command=="quit")
            break; //exit from loop
        else if(command.substr(0,6)=="search")
        {
            temp=command.substr(8);
            temp.pop_back(); //remove last character that is "(quote)
            search(start,temp);
        }
        else if(command.substr(0,4)=="edit")
        {
            p=command.find(" ",5); //search space after 1st space

//Note that index will lie between 1st space and 2nd space of command
            str_index=command.substr(5,p-5);

//convert string index to numerical index
            ss<<str_index;
            ss>>index;
            ss.clear();

            temp=command.substr(p+2);
            temp.pop_back(); //remove last character that is "(quote)
            edit(start,index,temp);
        }
        else if(command.substr(0,6)=="delete")
        {
            str_index=command.substr(7);

//convert string index to numerical index
            ss<<str_index;
            ss>>index;
            ss.clear();
            deletenode(start,index);
        }
        else if(command.substr(0,9)=="insertEnd")
        {
            temp=command.substr(11);
            temp.pop_back(); //remove last character that is "(quote)
            insertnodeatlast(start,temp);
        }
        else //insert at random index
        {
            p=command.find(" ",7); //search space after 1st space

//Note that index will lie between 1st space and 2nd space of command
            str_index=command.substr(7,p-7);

//convert string index to numerical index
            ss<<str_index;
            ss>>index;
            ss.clear();

            temp=command.substr(p+2);
            temp.pop_back(); //remove last character that is "(quote)
            insertnodeatline(start,index,temp);
        }
    }
    return 0 ;
}

//Function to add a line to text editor
struct node* addLine(string value)
{
    struct node *x=new node;
    x->data=value;
    x->next=NULL;
    return(x);
}

//Inserts new line at the end
void insertnodeatlast(struct node *p,string temp)
{
    struct node *x;
    x=addLine(temp);
    if(start==NULL)
        start=x;
    else
    {
        while(p->next!=NULL) //Move till end
            p=p->next;
        p->next=x; //Add new node(line) at the end
    }
}

//Add new line at the specified index
void insertnodeatline(struct node *p,int index,string temp)
{
    struct node *prev=NULL; //To store the node that is previous of the node to be added
    struct node* n=addLine(temp);
    int i;
    for(i=1;i<index;i++)
    {
        prev=p;
        p=p->next;
    }
    if(prev==NULL) //Node is to be added at first position
    {
        n->next=start;
        start=n; //start will now point to this newly added line as it is 1st line
    }
    else
    {
        n->next=p;
        prev->next=n;
    }
}

//Delete a line at specified index
void deletenode(struct node *p,int index)
{
    struct node *q; //To store the node(line) to be deleted
    struct node *prev=NULL; //To store the node that is previous of the node to be deleted
    int i;
    for(i=1;i<index;i++)
    {
        prev=p;
        p=p->next;
    }
    if(prev==NULL) //1st Node(line) is to be deleted
    {
        q=p;
        start=start->next;
    }
    else
    {
        q=p;
        prev->next=p->next;
    }
    delete q; //Free the memory allocated to this node
}

//To edit the line at specified index
void edit(struct node *p,int index,string temp)
{
    int i;
    for(i=1;i<index;i++)
    {
        p=p->next;
    }
    p->data=temp;
}

//To find and print the string
void search(struct node *p,string temp)
{
    int i=1;
    int marker=0; //flag will set to 1 if string to be searched is found even once
    while(p)
    {
        if(p->data.find(temp)!=-1) //string is found
        {
            cout<<i<<" "<<p->data<<endl;
            marker=1;
        }
        p=p->next;
        i++;
    }
    if(marker==0) //string not found
        cout<<"not found"<<endl;
}


void viewnode(struct node *p)
{
    if(p==NULL)
        printf("Document is empty\n");
    else
    {
        int i=1;
        while(p)
        {
            cout<<i<<" "<<p->data<<endl;
            p=p->next;
            i++;
        }
    }
}