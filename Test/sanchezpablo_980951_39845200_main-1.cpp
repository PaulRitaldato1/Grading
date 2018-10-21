//COP3530               Assignment 1            Pablo Sanchez
#include <iostream>
#include <string>
#include <iostream>

using namespace std;
//LinkedList.h
class LinkedList {
public:
    struct Node{
    public:
        std::string value;
        Node* next;
        Node* prev;

        Node(){
            this->value = "";
            this->next = nullptr;
            this->prev = nullptr;
        }

        Node(const std::string& value){
            this->value = value;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };
    LinkedList();
    ~LinkedList();
    void Add(const std::string& s); //add item to back of the list
    void Print(); //print all items in list
    void Insert(int index, const std::string& value); //insert item at specified index
    void Remove(int index); //remove item at specified index
    bool isEmpty(); //returns whether the list is empty or not
    void Search(const std::string& query); //returns lines containing a specified string

private:
    Node* head;
    Node* tail;
    int size;
};


//LinkedList.cpp

//constructor
LinkedList::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

//destructor
LinkedList::~LinkedList(){
    Node* iterator = this->head;
    while (iterator != this->tail){
        iterator->next = this->head;
        delete iterator;
        iterator = this->head;
        if (this->head == this->tail) {
            delete head;
        }
    }
}

//Add node to back of the list
void LinkedList::Add(const std::string& s){
    auto* newNode = new LinkedList::Node(s);
    if (this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
    }
    else{
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }
    this->size++;
}

//print contents of the list
void LinkedList::Print(){
    if (this->isEmpty()){
        //std::cout << "List is empty" << std::endl;
        return;
    }
    Node* iterator = this->head;
    int count = 1;
    while(iterator != nullptr){
        std::cout << count <<" " << iterator->value << std::endl;
        iterator = iterator->next;
        count++;
    }
}

//inserts Node at index given
void LinkedList::Insert(int index, const std::string& value){
    bool success = false;
    int counter = 0;
    auto* newNode = new Node(value);
    Node* iterator = this->head;
    if (index == this->size){ //if insertion is at end of list
        this->Add(value);
        return;
    }
    while(iterator != nullptr){
        if (index == 0){ //if insertion is at beginning of list
            newNode->next = this->head;
            this->head = newNode;
            this->size++;
            return;
        }
        if (counter == index){ //if insertion is in the middle of list
            newNode->next = iterator;
            newNode->prev = iterator->prev;
            iterator->prev->next = newNode;
            iterator->prev = newNode;
            this->size++;
            return;
        }
        counter++;
        iterator = iterator->next;
    }
    if (!success){
        //error
    }
}

//remove item at specified index
void LinkedList::Remove(int index){
    bool success = false;
    int counter = 0;
    Node* iterator = this->head;
    while (iterator != nullptr){
        if (index == 0){ //if at the beginning of list
            if (this->head->next != nullptr){
                this->head->next->prev = nullptr;
            }
            this->head = this->head->next;
            delete iterator;
            this->size--;
            //updateSize();
            return;
        }
        if (counter == index){
            if (iterator == this->tail){ //if at end of list
                this->tail = iterator->prev;
            }
            iterator->prev->next = iterator->next;
            if (iterator->next != nullptr){ //if in middle of list
                iterator->next->prev = iterator->prev;
            }
            delete iterator;
            this->size--;
            return;
        }
        counter++;
        iterator = iterator->next;
    }
    if (!success){
        //error
    }
}

//returns whether list is empty or not
bool LinkedList::isEmpty(){
    if (this->head == nullptr){
        return true;
    }
    else{return false;}
}

//search for a string, prints lines containing string
void LinkedList::Search(const std::string& query){
    Node* iterator = this->head;
    bool success = false;
    int counter = 1;
    while (iterator != nullptr){
        std::string::size_type pos = iterator->value.find(query, 0);
        if (pos != std::string::npos){
            std::cout << counter << " " << iterator->value << std::endl;
            success = true;
        }
        counter++;
        iterator = iterator->next;
    }
    if (!success){std::cout << "not found" << std::endl;}
}

//main.cpp

//extracts string within quotes, used for inserting/editing text
string findString(const string& s){
    int startIndex = 0;
    int endIndex = 0;
    startIndex = s.find_first_of("\"") + 1;
    endIndex = s.find_last_of("\"");
    string result = s.substr(startIndex, endIndex - startIndex);
    return result;
}

//extracts integer from user input, used for finding index that user specified
int findInt(const string& s){
    int beginning = -1;
    int end = -1;
    //find index of first digit
    for (int i = 0; s[i] != '\0'; i++){
        if (isdigit(s[i]) && beginning == -1){
            beginning = i;
        }
        else{
            //sets ending index
            if (isdigit(s[i]) && beginning != -1){
                end = i;
            }
        }
    }
    //if only the beginning is found, then the beginning is also the end: 1 digit number
    if (beginning != -1 && end == -1){end = beginning;}

    if (beginning != -1 && end != -1){
        string toParse = s.substr(beginning, end - beginning + 1);
        int toReturn = stoi(toParse);
        return toReturn;
    }

    return -1; //-1 returned if no digit is found
}

//used to recognize what command the user typed in, calls appropriate command
void parse(const string& query, LinkedList& list, bool& repeat){
    string cmd = query.substr(0, query.find_first_of("\""));
    if (cmd.find("insertEnd", 0) != string::npos){
        if (query.find_first_of("\"", 0) == query.find_last_of("\"", 0)){
            //cout << "Please enter the string to insert inside quotes" << endl; error
            return;
        }
        string text = findString(query);
        if (text.size() > 80){
            //cout << "Error: string cannot be over 80 characters long" << endl; error
            return;
        }
        list.Add(text);
        return;
    }
    if (cmd.find("insert", 0) != string::npos){
        if (query.find_first_of("\"", 0) == query.find_last_of("\"", 0)){
            //cout << "Please enter the string to insert inside quotes" << endl; error
            return;
            }
            string text = findString(query);
        if (text.size() > 80){
            //cout << "Error: string cannot be over 80 characters long" << endl; error
            return;
        }
            int index = findInt(query) - 1;
            list.Insert(index, text);
        return;
    }
    if (cmd.find("delete", 0) != string::npos){
        int index = findInt(query) - 1;
        list.Remove(index);
        return;
    }
    if (cmd.find("edit", 0) != string::npos){
        if (query.find_first_of("\"", 0) == query.find_last_of("\"", 0)){
            //cout << "Please enter the string to insert inside quotes" << endl; error
            return;
        }
        string text = findString(query);
        if (text.size() > 80){
            //cout << "Error: string cannot be over 80 characters long" << endl; error
            return;
        }
        int index = findInt(query) - 1;
        list.Remove(index);
        list.Insert(index, text);
        return;
    }
    if (cmd.find("print", 0) != string::npos){
        list.Print();
        return;
    }
    if (cmd.find("search", 0) != string::npos){
        if (query.find_first_of("\"", 0) == query.find_last_of("\"", 0)){
            //cout << "Please enter the string to search for inside quotes" << endl; error
            return;
        }
        string text = findString(query);
        list.Search(text);
        return;
    }
    if (cmd.find("quit", 0) != string::npos){
        repeat = false;
        return;
    }
    //cout << "Command not recognized" << endl; error
}

int main() {
    auto* myList = new LinkedList();
    bool repeat = true;

    while (repeat){
        string query;
        getline(cin, query);
        parse(query, *myList, repeat);
    }

    return 0;
}

