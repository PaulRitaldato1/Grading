#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct node
{
string value;
struct node *next;
};
//Head of the list
struct node *head=NULL; 

	
   	struct node* nodeBuilder(void);
	
	void checkNode(struct node *);
	void searchNode(struct node *,string);
	void deltNode(struct node *,int);
	void insToIndex(struct node *,int,string);
	void editNode(struct node *,int,string);
	void insToEnd(struct node *,string);
		
struct node* nodeBuilder(string value)// new node
{
    struct node *n=new node;
    n->value=value;
    n->next=NULL;
    return(n);
}
	
void checkNode(struct node *t)
{
    if(t==NULL)
        printf("Document is empty\n");
    else
    {
        int i=1;
        while(t)
        {
            cout<<i<<" "<<t->value<<endl;
            t=t->next;
            i++;
        }
    }
}

void searchNode(struct node *head, string str)//Finding or not the string
{
    if(head==NULL) //in the case of that the string was not fund
        return;
    
    struct node *it = head;
    int count = 0;
    while(it) {
        if (it->value.find(str)!=-1) {
            count++;
        }
        it = it->next;
    }
    if (count == 0) {
        cout << "not found" << endl;
        return;
    }
    
    int i=1;
    while(head) {
        if(head->value.find(str)!=-1) //in the case that the string is found
        {
            cout<<i++<<" "<<head->value<<endl;
        } else {
            i++;
        }
        head=head->next;
    }
}

void deltNode(struct node *t,int index)//Deleting line at specified index
{
    struct node *q; //Saving the line to be deleted
    struct node *prev=NULL; 
    int i;
    for(i=1;i<index;i++)
    {
        prev=t;
        t=t->next;
    }
    if(prev==NULL) //delete 1 line
    {
        q=t;
        head=head->next;
    }
    else
    {
        q=t;
        prev->next=t->next;
    }
    delete q; //Removing everything from memory
}

void insToIndex(struct node *t,int index,string temp)
{
    struct node *prev=NULL; //Storing at previous
    struct node* n=nodeBuilder(temp);
    int i;
    for(i=1;i<index;i++)
    {
        prev=t;
        t=t->next;
    }
    if(prev==NULL) //add node to the 1st pos.
    {
        n->next=head;
        head=n; 
    }
    else
    {
        n->next=t;
        prev->next=n;
    }
}

void editNode(struct node *t,int index,string temp)//Editing at specified index
{
    int i;
    for(i=1;i<index;i++)
    {
        t=t->next;
    }
    t->value=temp;
}

void insToEnd(struct node *t,string temp)//Implementation of function insertEnd
{
    struct node *n;
    n=nodeBuilder(temp);
    if(head==NULL)
        head=n;
    else
    {
        while(t->next!=NULL) //keep going till finish
            t=t->next;
        
        t->next=n; 
    }
}

int main()
{
    int index,t;      //variable t would be used for short term storage
    string userInpt; //Storing user's input
    string temp;     //Storing inserted text  
    string indexStr; //Storing index in string
    stringstream ops;

    while(1) //wait for the user to quit to quit
    {
        getline(cin,userInpt);
        if(userInpt=="print")
        {
            checkNode(head);
        }
        else if(userInpt=="quit")
            break; 
        else if(userInpt.substr(0,6)=="search")
        {
            temp=userInpt.substr(8);
            temp.pop_back(); //removing quotiation mark
            searchNode(head,temp);
        }
        else if(userInpt.substr(0,4)=="edit")
        {
            t=userInpt.find(" ",5); //look for char aftter 1st space


            indexStr=userInpt.substr(5,t-5);//Setting index position 

            //string index to # 
            ops<<indexStr;
            ops>>index;
            ops.clear();

            temp=userInpt.substr(t+2);
            temp.pop_back(); //removing quotiation mark
            editNode(head,index,temp);
        }
        else if(userInpt.substr(0,6)=="delete")
        {
            indexStr=userInpt.substr(7);

            //string index to # 
            ops<<indexStr;
            ops>>index;
            ops.clear();
            deltNode(head,index);
        }
        else if(userInpt.substr(0,9)=="insertEnd")
        {
            temp=userInpt.substr(11);
            temp.pop_back(); //removing quotiation mark
            insToEnd(head,temp);
        }
        else //Random index insertion
        {
            t=userInpt.find(" ",7); //search space after 1st space


            indexStr=userInpt.substr(7,t-7);//Setting index position 

            //string index to # 
            ops<<indexStr;
            ops>>index;
            ops.clear();

            temp=userInpt.substr(t+2);
            temp.pop_back(); //removing quotiation mark
            insToIndex(head,index,temp);
        }
    }
    return 0;
}