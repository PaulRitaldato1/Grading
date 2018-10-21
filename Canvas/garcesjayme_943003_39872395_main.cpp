#include<bits/stdc++.h>
using namespace std;

struct node
{
    string data;
    struct node *next;
};

struct node *start=NULL;

//These are the function declarations
struct node* createnode(void);
void insertnodeatlast(struct node *,string);
void insertnodeatrandom(struct node *,int,string);
void deletenodeatrandom(struct node *,int);
void modify(struct node *,int,string);
void viewnode(struct node *);
void search(struct node *,string);

int main()
{
    string command; //Stores user input
    string temp; //Stores "text"
    string str_index; //To store index in string format
    int index,v; //v is used as temporary storage
    stringstream ss;

    while(1) //Loops until the user decides to quit
    {
        getline(cin,command);
        if(command=="print")
        {
            viewnode(start);
        }
        else if(command=="quit")
            break;
        else if(command.substr(0,6)=="search")
        {
            temp=command.substr(8);
            temp.pop_back(); //removes "
            search(start,temp);
        }
        else if(command.substr(0,4)=="edit")
        {
            v=command.find(" ",5);

//The index will lie between 1st space and 2nd space of command
            str_index=command.substr(5,v-5);


            ss<<str_index;
            ss>>index;
            ss.clear();

            temp=command.substr(v+1);
            temp.pop_back(); //remove last character that is "(quote)
            modify(start,index,temp);
        }
        else if(command.substr(0,6)=="delete")
        {
            str_index=command.substr(7);


            ss<<str_index;
            ss>>index;
            ss.clear();
            deletenodeatrandom(start,index);
        }
        else if(command.substr(0,9)=="insertEnd")
        {
            temp=command.substr(11);
            temp.pop_back(); 
            insertnodeatlast(start,temp);
        }
        else
        {
            v=command.find(" ",7); //search space after 1st space

//Note that index will lie between 1st space and 2nd space of command
            str_index=command.substr(7,v-7);

//convert string index to numerical index
            ss<<str_index;
            ss>>index;
            ss.clear();

            temp=command.substr(v+2);
            temp.pop_back(); //removes " at the end
            insertnodeatrandom(start,index,temp);
        }
    }
    return 0;
}

//This will create a new node
struct node* createnode(string value)
{
    struct node *n=new node;
    n->data=value;
    n->next=NULL;
    return(n);
}

//Inserts new line at the end
void insertnodeatlast(struct node *v,string temp)
{
    struct node *n;
    n=createnode(temp);
    if(start==NULL)
        start=n;
    else
    {
        while(v->next!=NULL) 
            v=v->next;
        v->next=n; 
    }
}

//Add new line at the specified index
void insertnodeatrandom(struct node *v,int index,string temp)
{
    struct node *prev=NULL; //To store the node that is previous of the node to be added
    struct node* n=createnode(temp);
    int i;
    for(i=1;i<index;i++)
    {
        prev=v;
        v=v->next;
    }
    if(prev==NULL) //Node is to be added at first position
    {
        n->next=start;
        start=n; 
    }
    else
    {
        n->next=v;
        prev->next=n;
    }
}

//Delete a line at specified index
void deletenodeatrandom(struct node *v,int index)
{
    struct node *q; //To store the node(line) to be deleted
    struct node *prev=NULL; //To store the node that is previous of the node to be deleted
    int i;
    for(i=1;i<index;i++)
    {
        prev=v;
        v=v->next;
    }
    if(prev==NULL) //1st Node is deleted 
    {
        q=v;
        start=start->next;
    }
    else
    {
        q=v;
        prev->next=v->next;
    }
    delete q; 
}

//Edits line at specified index
void modify(struct node *v,int index,string temp)
{
    int i;
    for(i=1;i<index;i++)
    {
        v=v->next;
    }
    v->data=temp;
}

//This finds and prints the string
void search(struct node *v,string temp)
{
    int i=1;
    while(v)
    {
        if(v->data.find(temp)!=-1) //string ound
        {
            cout<<i<<" "<<v->data<<endl;
            break;
        }
        v=v->next;
        i++;
    }
    if(v==NULL) //string not found
        cout<<"not found"<<endl;
}

void viewnode(struct node *v)
{
    if(v==NULL)
        printf("Document is empty\n");
    else
    {
        int i=1;
        while(v)
        {
            cout<<i<<" "<<v->data<<endl;
            v=v->next;
            i++;
        }
    }
}