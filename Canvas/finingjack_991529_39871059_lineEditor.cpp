using namespace std;
#include <iostream>
#include <string>

// NODE IMPLEMENTATION
class Node{
    public:
        string line;
        int index;
        struct Node* next;
        Node(string, int);
};

Node::Node(string line, int index){
    this->line = line;
    this->index = index;
    next = NULL;
};

//LINKED LIST IMPLEMENTATION
class LinkedList{
    public:
        Node* head;
        Node* tail;
        int size;
        LinkedList();
        void insertEnd(string);
        void insert(int,string);
        void deleteNode(int);
        void edit(int,string);
        void search(string);
        void print();
};

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
    size = 0;
};

//LINE EDITOR FUNCTIONS
void LinkedList::insertEnd(string line){
    if(size == 0) {
        size = 1;
        head = new Node(line, size);
        return;
    } else if(size == 1){
        size = 2;
        tail = new Node(line, size);
        head->next = tail;
        return;
    } else {
        size++;
        Node* temp = new Node(line,size);
        tail->next = temp;
        tail = temp;
    }
};

void LinkedList::insert(int target, string text){
    if(target < 0 || target > size + 1){
        return;
    }
    Node* temp = head;
    if(head->index == target) {
        Node *inserted = new Node(text, target);
        head = inserted;
        head->next = temp;
        int t = target;
        while (temp != NULL) {
            t++;
            temp->index = t;
            temp = temp->next;
        }
        size++;
    } else if(tail->index + 1 == target){
        size++;
        Node* temp = new Node(text,target);
        tail->next = temp;
        tail = temp;
    } else {
        while (temp->next->index != target) {
            temp = temp->next;
        }
        Node *pushed = temp->next;
        Node *inserted = new Node(text, target);
        temp->next = inserted;
        inserted->next = pushed;
        int t = target;
        while (pushed != NULL) {
            t++;
            pushed->index = t;
            pushed = pushed->next;
        }
        size++;
    }
};

void LinkedList::deleteNode(int target){
    if(target < 0 || target > size){
        return;
    }
    Node* temp = head;
    if(head->index == target){
        Node* curr = temp->next;
        delete (temp);
        head = curr;
        int t = target;
        while (curr != NULL) {
            curr->index = t;
            curr = curr->next;
            t++;
        }
        size--;
    } else {
        while (temp->next->index != target) {
            temp = temp->next;
        }
        Node *curr = temp->next->next;
        delete (temp->next);
        temp->next = curr;
        int t = target;
        while (curr != NULL) {
            curr->index = t;
            curr = curr->next;
            t++;
        }
        size--;
    }
};

void LinkedList::edit(int i, string text) {
    if(i < 0 || i > size){
        return;
    }
    Node* temp = head;
    while(temp->index != i){
        temp = temp->next;
    }
    temp->line = text;
};

void LinkedList::search(string text){
    Node* temp = head;
    int count = 0;
    while(temp != NULL) {
        if(temp->line.find(text) != -1){
            cout << temp->index << " " << temp->line << endl;
            count++;
        }
        temp = temp->next;
    }
    if(count == 0) {
        cout << "Not found." << endl;
    }
};

void LinkedList::print(){
    Node* temp = head;
    while (temp != NULL){
        cout << temp->index << " " << temp->line << endl;
        temp = temp->next;
    }
};

//MAIN METHOD
int main(){
    LinkedList* list = new LinkedList();
    bool on = true;
    while(on) {
        string input;
        getline(cin, input);

        if (input.find("insertEnd") != -1) {
            string line = input.substr(input.find("\"")+1, input.length()-input.find("\"")-2); //obtain the line entered
            if(line.size() > 80){
                cout << "Line of invalid length";
            } else {
                list->insertEnd(line);
            }

        } else if (input.find("insert") != -1) {
            string line = input.substr(input.find("\"")+1, input.length()-input.find("\"")-2); //obtain the line entered
            if(line.size() > 80){
                cout << "Line of invalid length";
            } else {
                string numGet = input.substr(input.find(" ")+1, input.find("\"")-input.find(" ")-1); //obtain node number
                int num = stoi(numGet);
                list->insert(num,line);
            }

        } else if (input.find("delete") != -1) {
            string numGet = input.substr(input.find(" ")+1, input.find("\"")-input.find(" ")-1); //obtain node number
            int num = stoi(numGet);
            list->deleteNode(num);
        } else if (input.find("edit") != -1) {
            string line = input.substr(input.find("\"")+1, input.length()-input.find("\"")-2); //obtain the line entered
            if(line.size() > 80){
                cout << "Line of invalid length";
            } else {
                string numGet = input.substr(input.find(" ")+1, input.find("\"")-input.find(" ")-1); //obtain node number
                int num = stoi(numGet);
                list->edit(num,line);
            }

        } else if (input.find("search") != -1) {
            string line = input.substr(input.find("\"")+1, input.length()-input.find("\"")-2); //obtain the line entered
            if(line.size() > 80){
                cout << "Line of invalid length";
            } else {
                list->search(line);
            }

        } else if (input == "print") {
            list->print();

        } else if (input == "quit") {
            on = false;

        } else {
            cout << "That is not a valid method." << endl;
        }
    }
    return 0;
};