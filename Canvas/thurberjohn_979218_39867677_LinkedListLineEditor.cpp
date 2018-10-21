//Name: John Thurber | UFID: 1281-5397 | DS Project 1
using namespace std;
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
//Node implementation
struct node {
    string line = "";
    node *next = NULL;
};
//Global node to keep track of list, global variables to assist in tracking
//list length and whether the list is empty
node* nodeHead = new node;
bool isStart = true;
int nodeCount = 1;

//Method to insert a node at the end of the list
void insertEnd (string input){
    nodeCount++;
    node* temp = new node;
    temp = nodeHead;
    node* tail = new node;
    tail->line = input;
    tail->next = NULL;
    if (nodeHead->next == NULL && isStart == true){
        nodeHead = tail;
        isStart = false;
    }
    else {
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = tail;
    }
}

//Method to print the string and line numbers of every node in the list
void print(node* head) {
    node* temp = new node;
    temp = head;
    int counter = 1;
    while (temp->next !=  NULL){
        cout << counter << " " << temp->line << endl;
        temp = temp->next;
        counter++;
    }
    cout << counter << " " << temp->line << endl;
}

//Method to search each node in a list for a given string input - returns line number/full string of node
void search(node* head, string searchInput){
    node* temp = new node;
    temp = head;
    int counter = 1;
    bool oneOcc = false;
    size_t position = -1;
    while (temp->next != NULL){
        position = temp->line.find(searchInput);
        if (position != -1){
            cout << counter << " " << temp->line << endl;
            oneOcc = true;
        }
        temp = temp->next;
        counter++;
    }
    position = temp->line.find(searchInput);
    if (position != -1){
        cout << counter << " " << temp->line << endl;
        oneOcc = true;
    }
    if (oneOcc == false){
        cout << "not found" << endl;
    }
}

//Method to insert a node with a given string at a certain index in a list
void insert(node* head, int index, string newLine){
    if (index > nodeCount + 1){
        return;
    }
    nodeCount++;
    node* current = head;
    node* add = new node;
    add->next = NULL;
    add->line = newLine;
    if (index == 1){
        add->next = nodeHead;
        nodeHead = add;
        return;
    }
    for (int i = 0; i < index-2; i++){
        current = current->next;
        if (current == nullptr){
            cout << "index not found" << endl;
        }
   }
    add->next = current->next;
    current->next = add;
}

//Method to replace the string of the node at the given index with the string the user inputs
void edit (int index, string editString){
    node* editNode = new node;
    editNode->line = editString;
    node* temp = new node;
    temp->next = nodeHead;
    for (int i = 1; i < index; i++){
        temp = temp->next;
    }
    editNode->next = temp->next->next;
    temp->next = editNode;
}

//Method to delete a node at a given index
void remove (node* head, int index){
    nodeCount--;
    node* curr = head;
    node* prev = new node;
    prev->next = NULL;
    int i = 1;
    if (index == 1){
        nodeHead = curr->next;
        curr = nodeHead;
        return;
    }
    while (curr->next != NULL){
        if (i != index){
            prev = curr;
            curr = curr->next;
            i++;
        } else {
            prev->next = curr->next;
            curr = prev->next;
            return;
        }
    }
    if (curr->next == NULL && i == index){
        prev->next = NULL;
        return;
    }
}
int main()
{
    bool running = true;
    int i = 0;
	//Reads user input and pieces it apart into variables that can be used by the desired method
    while (running){
        string command = "";
        string userInput = "";
        int editNumber;
        cin >> command;
        getline(cin, userInput);
        userInput.erase(0,1);
        userInput.erase (
            remove(userInput.begin(), userInput.end(), '\"'),
            userInput.end()
        );
		//Utilizes pieced-apart input in order to determine and execute user commands
        if (command == "quit"){
            return 0;
        } else if (command == "insertEnd"){
            insertEnd(userInput);
        } else if (command == "print"){
            print(nodeHead);
        } else if (command == "edit"){
             istringstream stream(userInput);
             stream >> editNumber;
             userInput.erase(0,2);
             edit(editNumber, userInput);
        } else if (command == "search"){
            search(nodeHead, userInput);
        } else if (command == "insert"){
            istringstream stream2(userInput);
            stream2 >> editNumber;
            userInput.erase(0,2);
            insert(nodeHead, editNumber, userInput);
        } else if (command == "delete"){
            istringstream stream3(userInput);
            stream3 >> editNumber;
            userInput.erase(0,2);
            remove(nodeHead, editNumber);
            
        }
    }
}