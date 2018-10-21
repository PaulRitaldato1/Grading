#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct node
{
    string message;
    struct node* nextNode;
};

struct node* head = NULL; // points to head of the list

// declare functions
struct node* createNewNode(void);
void insertEnd(struct node*, string);
void insertIndex(struct node*, int, string);
void deleteNode(struct node*, int);
void edit(struct node*, int, string);
void print(struct node*);
void search(struct node*, string);

int main()
{
    string command; // takes in users input
    string text; // the document text
    string stringIndex; // index of line as a string
    int index,temp; // temporary variable
    stringstream stringConversion;
    int lineNumber = 0;

    while(true) { // loops till the user inputs "quit"
        getline(cin,command);
        if(command == "print") {
            print(head);
        }
        else if(command == "quit") {
            break; // exit
        }
        else if(command.substr(0, 6) == "search") {
            text = command.substr(8);
            text.pop_back();
            search(head, text);
        }
        else if(command.substr(0, 4) == "edit") {
            temp = command.find(" ", 5);
            stringIndex = command.substr(5, temp - 5);

            // converts the string index to int index
            stringConversion << stringIndex;
            stringConversion >> index;
            stringConversion.clear();

            text = command.substr(temp + 1);
            text.pop_back();
            edit(head, index, text);
        }
        else if(command.substr(0, 6) == "delete") {
            stringIndex = command.substr(7);

            // converts the string index to int index
            stringConversion << stringIndex;
            stringConversion >> index;
            stringConversion.clear();

            // checks to see if the command is valid
            if(index <= lineNumber){
                deleteNode(head, index);
                lineNumber--;
            }
        }
        else if(command.substr(0, 9) == "insertEnd") {
            text = command.substr(11);
            text.pop_back();
            insertEnd(head,text);
            lineNumber++;
        }
        else {
            temp = command.find(" ",7);
            stringIndex = command.substr(7,temp - 7);

            // convert string index to int index
            stringConversion << stringIndex;
            stringConversion >> index;
            stringConversion.clear();

            text = command.substr(temp + 2);
            text.pop_back();

            // checks to see if the command is valid
            if(index <= lineNumber || index == lineNumber + 1){
                insertIndex(head,index,text);
                lineNumber++;
            }
        }
    }
    return 0;
}

// creates a new node
struct node* createNewNode(string value) {
    struct node* n = new node;
    n -> message = value;
    n -> nextNode = NULL;
    return(n);
}

// inserts text at the end of list
void insertEnd(struct node* temp,string text) {
    struct node* n;
    n = createNewNode(text);
    if(head == NULL) {
        head = n;
    }
    else {
        while(temp -> nextNode != NULL) // transverse the entire list to the end
            temp = temp -> nextNode;
        temp -> nextNode = n; // creates a new node
    }
}

// insert text at the given index
void insertIndex(struct node* temp,int index,string text) {
    struct node* prev = NULL; // saves previous node text
    struct node* n = createNewNode(text);
    for(int i = 1; i < index; i++) {
        prev = temp;
        temp = temp -> nextNode;
    }
    if(prev == NULL) {
        n -> nextNode = head;
        head = n; // the new line becomes the head
    }
    else {
        n -> nextNode = temp;
        prev -> nextNode = n;
    }
}

// deletes node at given index
void deleteNode(struct node* temp, int index) {
    struct node* curr;
    struct node* prev = NULL; // to store the node that is previous of the node to be deleted
    for(int i = 1; i < index; i++) {
        prev = temp;
        temp = temp -> nextNode;
    }
    if(prev == NULL) {
        curr = temp;
        head = head -> nextNode;
    }
    else
    {
        curr = temp;
        prev -> nextNode = temp -> nextNode;
    }
    delete curr; // no garbage collection in C++
}

// edits node at given index
void edit(struct node* temp,int index, string text) {
    for(int i = 1; i < index; i++) {
        temp = temp -> nextNode;
    }
    temp -> message = text;
}

// finds node
void search(struct node* temp, string text) {
    int i = 1;
    int count = 0;
    while(temp) {
        if(temp -> message.find(text) != -1) //string is found
        {
            cout << i << " " << temp -> message << endl;
            count++;
        }
        temp = temp -> nextNode;
        i++;
        }
    if(temp == NULL && count == 0) {
        cout << "not found" << endl;
        //string not found
    }
}

// prints node if found
void print(struct node* temp)
{
    if(temp == NULL) {
        printf("Empty, please fill up document\n");
    }
    else {
        int i = 1;
        while(temp) {
            cout << i << " " << temp -> message << endl;
            temp = temp -> nextNode;
            i++;
        }
    }
}