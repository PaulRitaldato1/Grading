/**
Nicole O'Donnell
Text Editor
**/

//**********************************************************************************//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//**********************************************************************************//

//******************************* Linked List - NODE *******************************//

class Node {
    public:
    string data;            // holds line
    Node* next = NULL;      // pointer to next node
};

struct Node* head; // global variable

//**********************************************************************************//

//************************* Methods to Determine User Input ************************//

// @param input: the user's full input
// @return: returns the user's line of text to modify
string getLine (string input) {
    string line;
    string::size_type first = input.find("\"");
    string::size_type last;
    if (first != string::npos) {
        last = input.find("\"\n");
        line = input.substr (first+1, last-first);
    }
    
    if (line.find("\"") != string::npos){
        last = line.find("\"");
        line = line.substr (0, line.length()-1);
    }
    return line;
}


// recieves the line number that the users wishes to insert/delete/edit/search
// @param input: the user's full input
// @return: returns the line number
int getNum (string input) {
    int start_position = 0;
    int end_position = 0;
    string num;
    string finding;
    
    for (int i = 0; i < input.length(); i++) {
        if (isdigit(input[i]) ) {
            start_position = i;
            finding = input.substr(start_position+1, input[input.length()-1]);
            break;
        }
    }
    if ( isdigit(input[input.length()-1] ) ) {
        num = input.substr( start_position, input.length()-1 );
    }
    else {
        for (int j = 0; j < finding.length(); j++) {
            if (!isdigit(finding[j]) ){
                end_position = j;
                num = input.substr( start_position, (end_position) );
            }
        }
    }
    
    int n = atoi(num.c_str()); // converts string to int
    return n;
}


// checks if input number is out-of-range
// @param input_num: the line number
// @return: 0 = within bounds
// @return: 1 = out of bounds
int range (int input_num) {
    
    // user's input number must be a valid line number
    if (input_num <= 0) {
        return 1;
    }
    
    Node* curr = head;
    int count = 1;
    while (curr != NULL) {   // checks number of nodes
        curr = curr->next;
        count++;
    }
    
    if (input_num > count) {
        return 1; // out of range
    }
    
    else
        return 0; // within bounds
}

//**********************************************************************************//

//*********************************** User Commands ********************************//

// inserts a new node at end of linked list with the user's input line as the node's data
// @param input_line: the user's line to insert into list
void insertEnd(string input_line) {

    // creates node for new given input line
    Node* newNode = new Node;
    newNode->data = input_line;
    newNode->next = NULL;
     
    // if list is empty, the first node is added
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    // finds last node and links the new node
    else {
        Node* curr = head;
        while (curr != NULL) {
            if (curr->next == NULL) {
                curr->next = newNode;
                return;
            }
            else
                curr = curr->next;
        }
    }
}


// inserts a new line into list
// @param input_line: the user's line of text to insert into list
// @param input_num: the line number the user wishes to insert the new line at
void insert (string input_line, int input_num) {
    Node* newNode = new Node;
    newNode->data = input_line;
    newNode->next = NULL;
    
    Node* curr = head;
    Node* prev = new Node;
    int i = 1;
    
    // checks if input num is out-of-range
    if (range(input_num) == 1) {
        return;
    }
    
    // if list is empty, empty list becomes the new node and creates the first node
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    // insert at beginning/head (if input position is the head)
    if (input_num == 1) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // insert in the middle of the list
    while (curr != NULL) {
        if (i == input_num) {
            prev->next = newNode;
            newNode->next = curr;
            return;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    
    // insert at end of list
    if (input_num == i) {
        insertEnd(input_line);
        return;
    }
}


// deletes specified line in list
// @param input_num: the line number that the user wishes to delete
void deleteNode (int input_num) {
    Node* curr = head;
    Node* prev = new Node;
    int i = 1;
    
    // checks if input is out of bounds
    if (input_num <= 0) {
        return;
    }
    
    // checks if linked list is empty
    if (head == NULL) {
        return;
    }
    
    // deleting when there is only one node in list
    if (head->next == NULL && (input_num == 1)) {
        head = NULL;
        return;
    }
    
    // deleting first line is list)
    if (input_num == 1) {
        head = head->next;
        return;
    }
    
    // deleting in middle/end of list
    while (curr != NULL) {
        if (i == input_num) {
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
}


// changes the line of text that the user specifies
// @param input_line: the new line of text that user wishes to replace with the old text
// @param input_num: the line number the user wants to edit
void edit (string input_line, int input_num) {
    Node* curr = head;
    int i = 1;
    while (curr != NULL) {
        if(input_num == i) {
            curr->data = input_line;
            return;
        }
        curr = curr->next;
        i++;
    }
}


// searches for lines in linked list with given keywords & prints out each line w/ its line number
// @param input_line: keywords that the user want to search for
void search (string input_line) {
    Node* curr = head;
    int index = 1;
    int found = 0;
    
    // if list is empty -> returns "not found"
    if (head == NULL) {
        cout << "not found\n";
        return;
    }
    
    while (curr != NULL) {
        if (curr->data.find(input_line) != std::string::npos) {
            cout <<  index << " " << curr->data << "\n";    // prints line & its line number
            found = 1;
        }
        curr = curr->next;
        index++;
    }
    
    // prints "not found" when keywords are not found within any lines of text in list
    if (found == 0)
        cout << "not found\n";
}


// prints each line of text with corresponding line number
void print () {
    
    // list is empty
    if (head == NULL) {
        cout << "-empty-\n";
        return;
    }
    
    Node* curr = head;
    int index = 1;
    while (curr != NULL){
        cout << index << " " << curr->data << "\n";
        curr = curr->next;
        index++;
    }
}


//**********************************************************************************//

//******************* Main Method - Determines the User's Command ******************//

int main(int argc, const char * argv[]) {
    
    std::string input;
    head = NULL;

    do {
        string line;
        getline(cin, input);
        
        if (input.find("\"") != std::string::npos)
            line = getLine(input);
        int lineNum = getNum(input);
        
        
        if (input.substr(0,9) == "insertEnd"){
            insertEnd(line);
            continue; // forces the next iteration of the loop to take place
        }
        
        if (input.substr(0,6) == "insert") {
            insert(line, lineNum);
            continue;
        }
        
        if (input.substr(0,6) == "delete") {
            deleteNode(lineNum);
            continue;
        }
        
        if (input.substr(0,4) == "edit") {
            edit(line, lineNum);
            continue;
        }
        
        if (input.substr(0,6) == "search") {
            search(line);
            continue;
        }
        
        if (input == "print") {
            print();
            continue;
        }
    } while (input != "quit");
        
    return 0;
}
