#include <iostream>
#include <sstream>
using namespace std;

//Node class takes in data 
class Node {
    public:
    string line;
    Node* next;
};

//LinkedList class executes the data 
class LinkedList {
    public:
    Node *head;
    LinkedList();
    int length;
    void printList();
    void insert(int index, string line);
    void remove(int index);
    void edit(int index, string line);
    void search(string line);
    void insertEnd(string line);
};

//gives head no value
LinkedList::LinkedList() {
    this->head = NULL;
} ;

void LinkedList::insertEnd(string line)
{
    if (this->head == NULL) {
        Node *head = new Node();
        this->head = head;
        head->line = line;
        this->length++;
        return;
    }
    
    Node *current=this->head;
    Node* addNode = new Node();
    addNode->line=line;
    while(current->next != NULL)
    {
        current=current->next;
    }
    current->next=addNode;
    this->length++;
    return;
}

void LinkedList::insert(int index, string line)
{
    index--;
    if (index < 0 || index > this->length) { return; }
    Node *current = this->head; 
    Node* addNode = new Node();
    addNode->line = line;
    int count = 0;
    if (index == 0)
    {
        head = addNode;
        addNode->next = current;
        return;
    }
    while (count != index - 1)
    {
        current = current->next;
        count++;
    }
    addNode->next = current->next;
    current->next = addNode;
}

void LinkedList::remove(int index)
{
    index--;
    if (index < 0 || index > this->length) { return; }
    int count = 0;
    Node *current = this->head;
    if (index == 0) {
        head = current->next;
        return;
    }
    while (count != index - 1) {
        current = current->next;
        count++;
    }
    if (current->next == NULL) {
        return;
    }
    else {
        current->next=current->next->next;
    }
}

void LinkedList::search(string line2)
{
    bool found = false;
    int i=0;
    string line;
    Node* current=this->head;

    while (current != NULL) {
        line = current->line;
        i++;

        if (line.find(line2) != string::npos) {
            cout << i << " " << line << endl;
            found = true;
        }
        current=current->next;
    }
    if (!found) {
        cout << "not found" << endl;
    }
}

void LinkedList::edit(int index, string line)
{
    if (index < 0 || index > this->length) { return; }
    int i=0;
    Node *current=this->head;
    while (i<index-1) {
        current=current->next;
        if(current==NULL) { return; }
        i++;
    }
    current->line=line;
}

void printList(LinkedList* list) 
{ 
    Node* n = list->head;
    int c=0;
    while (n != NULL) {
        c++;
        cout << c << " " << n->line << endl;
        n = n->next;
    }  
}

int main() 
{
    LinkedList* list = new LinkedList;
    string userInput;

    while (userInput != "quit") {
        getline(cin, userInput);

        string method;
        stringstream ss(userInput);
        ss >> method;

        if (method == "insertEnd") {
            string data = userInput.substr(11, userInput.length() - 12);
            list->insertEnd(data);
            cin.clear();
        }
        else if (method == "insert") {
            string data = userInput.substr(10, userInput.length() - 11);
            int num = (int)userInput[7]-'0';
            list->insert(num, data);
            cin.clear();
        }
        else if (method == "delete") {
            int num = (int)userInput[7]-'0';
            list->remove(num);
            cin.clear();
        }
        else if (method == "edit") {
            string data = userInput.substr(8, userInput.length() - 9);
            int num = (int)userInput[5]-48;
            list->edit(num, data);
            cin.clear();
        } 
        else if (method == "print") {
            printList(list);
            cin.clear();
        } 
        else if (method == "search") {
            string data = userInput.substr(8, userInput.length() - 9);
            list->search(data);
            cin.clear();
        } 
    }
    if (userInput == "quit") {
        return 0;
    }
} 