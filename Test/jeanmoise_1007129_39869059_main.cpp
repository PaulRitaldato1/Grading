//
//  main.cpp
//  COP3530 Programming Assignment 1
//
//  Created by Moise Jean on 9/17/18.
//  Copyright © 2018 Moise Jean. All rights reserved.
//

#include <iostream>
#include <sstream>
using namespace std;

//Creating struct node
struct node
{
    string data;
    struct node *next;
};

//Variables declaration
struct node *start=NULL;
struct node* newNode(void);
void addLast(struct node *,string);
void addAt(struct node *,int,string);
void removeAt(struct node *,int);
void edit(struct node *,int,string);
void display(struct node *);
void search(struct node *,string);


//Creating node to store  user input
struct node* newNode(string value)
{
    struct node *n=new node;
    n->data=value;
    n->next=NULL;
    return(n);
}
//Inserting text at the end
void addLast(struct node *p,string temp)
{
    struct node *n;
    n=newNode(temp);
    if(start==NULL)
        start=n;
    else
    {
        while(p->next!=NULL)
            p=p->next;
        p->next=n;
    }
}
//Adding text at index
void addAt(struct node *p,int index,string temp)
{
    struct node *prev=NULL;
    struct node* n=newNode(temp);
    int i;
    for(i=1;i<index;i++)
    {
        prev=p;
        p=p->next;
    }
    if(prev==NULL)
    {
        n->next=start;
        start=n;
    }
    else
    {
        n->next=p;
        prev->next=n;
    }
}
//Removing text at index
void removeAt(struct node *p,int index)
{
    struct node *current;
    struct node *prev=NULL;
    int i;
    for(i=1;i<index;i++)
    {
        prev=p;
        p=p->next;
    }
    if(prev==NULL)
    {
        current=p;
        start=start->next;
    }
    else
    {
        current=p;
        prev->next=p->next;
    }
    delete current;
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
//Searching text in the linked list
void search(struct node *p,string temp)
{
    int i=1, f=0;
    while(p)
    {
        if(p->data.find(temp)!=-1)
        {
            cout<<i<<" "<<p->data<<endl;
            f=1;
        }
        p=p->next;
        i++;
    }
    if(f==0)
        cout<<"not found"<<endl;
}
void display(struct node *p)
{
    if(p==NULL)
        printf("Linked list is empty\n");
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

int main()
{
    //Variables declaration
    string command;
    string temp;
    string str_index;
    int index;
    int p;
    stringstream ss;

    printf("User Commands list & Description:\n");
    printf("insertEnd \"text\"     --insert given text at the end of the document.\n");
    printf("insert 3  \"text\"     --insert given text at the line indicated by index given.\n");
    printf("delete 3             --delete line at index given\n");
    printf("edit 3    \"text\"     --replace the line at the index given with the given text.\n");
    printf("print                --print the entire document, with line numbers.\n");
    printf("search    \"text\"     --print the line number and line that contains the given text\n");
    printf("                       or print \"not found\" if it is not found.\n");
    printf("quit                 --quit/exit the program\n\n");
    printf("Enter your command(s):\n\n");
    while(1) //Loop till user wants to quit
    {
        getline(cin,command);
        if(command=="print")
        {
            display(start);
        }
        else if(command=="quit")
            break;
        else if(command.substr(0,6)=="search")
        {
            temp=command.substr(8);
            temp.pop_back();
            search(start,temp);
        }
        else if(command.substr(0,4)=="edit")
        {
            p=command.find(" ",5);
            str_index=command.substr(5,p-5);
            ss<<str_index;
            ss>>index;
            ss.clear();
            temp=command.substr(p+2);
            temp.pop_back();
            edit(start,index,temp);
        }
        else if(command.substr(0,6)=="delete")
        {
            str_index=command.substr(7);
            ss<<str_index;
            ss>>index;
            ss.clear();
            removeAt(start,index);
        }
        else if(command.substr(0,9)=="insertEnd")
        {
            temp=command.substr(11);
            temp.pop_back();
            addLast(start,temp);
            
        }
        else
        {
            p=command.find(" ",7);
            str_index=command.substr(7,p-7);
            ss<<str_index;
            ss>>index;
            ss.clear();
            temp=command.substr(p+2);
            temp.pop_back();
            addAt(start,index,temp);
        }
    }
    return 0;
}
