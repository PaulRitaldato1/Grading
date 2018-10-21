#include<bits/stdc++.h>
using namespace std;

struct node {
    string data;
    struct node *next;
};

struct node *start=NULL; //Global variable will point to start of the node i.e 1st line

//Function declaration
struct node* createnode(void);
void insertnodeatlast(struct node *,string);
void insertnode(struct node *,int,string);
void deletenode(struct node *,int);
void modify(struct node *,int,string);
void viewnode(struct node *);
void search(struct node *,string);

int main() {
    string command; //TO store user's input
    string temp; //To store "text"
    string str_index; //To store index in string format
    int index,p; //p is for temporary storage
    stringstream ss;

    while(1) { //Loop till user wants to quit
        getline(cin,command);
        if(command=="print") {
            viewnode(start);
        }
        else if(command=="quit")
        break; //exit from loop
        else if(command.substr(0,6)=="search") {
            temp=command.substr(8);
            temp.pop_back(); //remove last character that is "(quote)
            search(start,temp);
        }
        else if(command.substr(0,4)=="edit") {
            p=command.find(" ",5); //search space after 1st space

            str_index=command.substr(5,p-5); //index will lie between 1st space and 2nd space of command

            ss<<str_index; //convert string index to numerical index
            ss>>index;
            ss.clear();

            temp=command.substr(p+2); //pass first two inputs (space and quotation mark)
            temp.pop_back(); //remove last character that is "(quote)
            modify(start,index,temp);
        }
        else if(command.substr(0,6)=="delete") {
            str_index=command.substr(7);

            ss<<str_index; //convert string index to numerical index
            ss>>index;
            ss.clear();
            deletenode(start,index);
        }
        else if(command.substr(0,9)=="insertEnd") {
            temp=command.substr(11);
            temp.pop_back(); //remove last character that is "(quote)
            insertnodeatlast(start,temp);
        }
        else { //insert at random index
            p=command.find(" ",7); //search space after 1st space


            str_index=command.substr(7,p-7); //index will lie between 1st space and 2nd space of command

//convert string index to numerical index
            ss<<str_index;
            ss>>index;
            ss.clear();

            temp=command.substr(p+2);
            temp.pop_back(); //remove last character that is "(quote)
            insertnode(start,index,temp);
        }
    }
    return 0;
}

//This will create a new node(line)
struct node* createnode(string value) {
    struct node *n=new node;
    n->data=value;
    n->next=NULL;
    return(n);
}

//Inserts new line at the end
void insertnodeatlast(struct node *p,string temp) {
    struct node *n;
    n=createnode(temp);
    if(start==NULL)
    start=n;
    else {
        while(p->next!=NULL) //Move till end
        p=p->next;
        p->next=n; //Add new node(line) at the end
    }
}

//Add new line at the specified index
void insertnode(struct node *p,int index,string temp) {
    struct node *prev=NULL; //To store the node that is previous of the node to be added
    struct node* n=createnode(temp);
    int i;
    for(i=1;i<index;i++) {
        prev=p;
        p=p->next;
    }

    if(prev==NULL) { //Node is to be added at first position
        n->next=start;
        start=n; //start will now point to this newly added line as it is 1st line
    }
    else {
        n->next=p;
        prev->next=n;
    }
}

//Delete a line at specified index
void deletenode(struct node *p,int index) {
    struct node *q; //To store the node(line) to be deleted
    struct node *prev=NULL; //To store the node that is previous of the node to be deleted
    int i;
    for(i=1;i<index;i++) {
        prev=p;
        p=p->next;
    }
    if(prev==NULL) { //1st Node(line) is to be deleted
        q=p;
        start=start->next;
    }
    else {
        q=p;
        prev->next=p->next;
    }
    delete q; //Free the memory allocated to this node
}

//To edit the line at specified index
void modify(struct node *p,int index,string temp) {
    int i;
    for(i=1;i<index;i++) {
        p=p->next;
    }
    p->data=temp;
}

//To find and print the string
void search(struct node *p,string temp) {
    int i=1;
    while(p) {
        if(p->data.find(temp)!=-1) { //string is found
            cout<<i<<" "<<p->data<<endl;
            break;
        }
        p=p->next;
        i++;
    }
    if(p==NULL) //string not found
    cout<<"not found"<<endl;
}

//To view the document, print line by line or document is empty
void viewnode(struct node *p) {
    if(p==NULL)
    printf("Document is empty\n");
    else {
        int i=1;
        while(p) {
            cout<<i<<" "<<p->data<<endl;
            p=p->next;
            i++;
        }
    }
}