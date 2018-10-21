#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//Node class
class Node {
    //only contains data value and references to next and previous
    public: 
        string value; 
        Node* next = NULL; 
        Node* prev = NULL;
};

//List class
class List {
    //contains size, head and tail references, and methods acting on list
    private:
        int size;
        Node *head, *tail;
    public:
    List()
    {
        size = 0;
        head = new Node;
        tail = new Node;
        head = NULL;
        tail = NULL;
    }
    
    //handle size of list
    int getSize(){return size;}
    void incrementSize(){size++;}
    void decrementSize(){size--;}
    
    //insert node to end
    void insertEndNode(string nodeValue) {
        //if first node to insert, head and tail have same value
        if (head==NULL) {
            head = new Node;
            head->value = nodeValue;
            //head gets value, tail stays null
        } else if (tail==NULL){
            tail = new Node;
            tail->value = nodeValue;
            //this is if there's 1 element initially
            tail->prev = head;
            head->next = tail;
        } else {
            //create node to insert
            Node* insertedNode = new Node;
            insertedNode->value=nodeValue;
            insertedNode->prev=tail;
            tail->next=insertedNode;
            tail = insertedNode;    
        }
        incrementSize();
    }
    
    //insert node into position before index
    void insertNode(int index, string nodeValue)  {
        Node* insertedNode = new Node;
        insertedNode->value=nodeValue;
        //ignore out of bounds
        if (index < 1 or index > (getSize()+1)) {
            return;
        } else if (index==(getSize()+1)) {
            insertEndNode(nodeValue);
            return;
        } else if (index == 1) {
            insertedNode->next = head;
            head->prev = insertedNode;
            head = insertedNode;
        } else {
            int counter = 1;
            Node* current = head;
            //get to position before insertion, so position (index-1)
            while (counter<(index-1))
            {
                current = current->next;
                counter++;
            }
            //set connections
            Node* next = current->next;
            current->next = insertedNode;
            insertedNode->prev = current;
            
            insertedNode->next = next;
            next->prev = insertedNode;
        }
        incrementSize();
    }
    
    //delete node by index
    void deleteNode(int index)  {
        //in case of deleting head
        if (index < 1 or index > getSize()) {
            return;
        } else if(index ==1) {
            Node* temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
        } else if (index==getSize()) {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
        } else {
            //find node to delete
            int counter = 1;
            Node* toDelete = head;
            while (counter<index) {
                toDelete=toDelete->next;
                counter++;
            }
            //remove and reestablish connections
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            delete toDelete;
            }
            //decrease size of list
        decrementSize(); 
    }
    
    //edit node by index
    void editNode(int index, string nodeValue)  {
        //find node to delete
        int counter = 1;
        Node* toEdit = head;
        while (counter<index) {
            toEdit=toEdit->next;
            counter++;
        }
        //change value
        toEdit->value = nodeValue;
    }
    
    //search node by substring
    void searchNodes(string nodeValue)  {
        int counter = 1;
        Node* toSearch = head;
        bool foundSearch = false;
        //once found, print line number and entire string
        while (toSearch!=NULL) {
            if(toSearch->value.find(nodeValue) != string::npos) {
                cout << counter;
                cout << " ";
                cout << toSearch->value << endl;
                foundSearch = true;
            }
            counter++;
            toSearch = toSearch->next;
        }
        if(!foundSearch)
            cout << "not found" << endl;
    }
    
    //print entire list
    void printList()  {
        int counter = 1;
        Node* toPrint = head;
        //loop and print all objects
        while (toPrint!=NULL) {
            cout << counter;
            cout << " ";
            cout << toPrint->value << endl;
            counter++;
            toPrint = toPrint->next;
        }
    }
};	

//LineEditor class
class LineEditor {
    //creates List, allows understanding of commands
    private:
        List myDocument;
    public:
        List getList() {
            return myDocument;
        }
        bool parseCommand(string commandType, string commandValue, int index) {
            //define some variables
            bool quit = false;
            int first = commandValue.find_first_of('"');
            commandValue = commandValue.substr(first+1);
            commandValue = commandValue.substr(0,commandValue.length()-1);

            if (commandType.compare("insertEnd") == 0) {
                myDocument.insertEndNode(commandValue);
            } else if (commandType.compare("insert") == 0) {
                myDocument.insertNode(index, commandValue);
            } else if (commandType.compare("delete") == 0) {
                myDocument.deleteNode(index);
            } else if (commandType.compare("edit") == 0) {
                myDocument.editNode(index, commandValue);
            } else if (commandType.compare("search") == 0) {
                myDocument.searchNodes(commandValue);
            } else if(commandType.compare("print") == 0) {
                myDocument.printList();
            } else if ((commandType.compare("quit") == 0)) {
                return true;
            }
            return quit;
        }
};
  
int main(int argc, char** argv) {
    //loop controller
    bool quit = false;
    //three possible inputs
    string commandType;
    string commandValue;
    int index;
    //create line editor
    LineEditor projectEditor;
    //read commands, stop once quit command has come
    while(!quit) {
        cin >> commandType;
        if ((commandType.compare("insertEnd") == 0) || (commandType.compare("search") == 0)) {
            getline(cin,commandValue);
        } else if ((commandType.compare("insert") == 0) || (commandType.compare("edit") == 0)) {
            cin >> index;
            getline(cin,commandValue);
        } else if ((commandType.compare("delete") == 0)) {
            cin >> index;
        } 
        quit = projectEditor.parseCommand(commandType, commandValue, index);
    }
    return 0;
}