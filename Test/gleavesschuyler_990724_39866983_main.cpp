#include <iostream>
class LinkedList {
private:
    //will act as a node within the linked list, provides pointer to next node and data
    struct Node {
        Node *next;
        std::string data;
    };

    Node *head;
    Node *tail;

    int listSize;  //amt of nodes in list

public:
    //constructors
    LinkedList();

    //helper functions
    const int size();
    bool isEmpty();

    //main functions
    void insertEnd(std::string data);
    void insert(int index, std::string data);
    void search(std::string text);
    void edit(int index, std::string data);
    void deleteNode(int index);
    void print();
};

/**
 * Constructor - initializes all values to NULL
 */
LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;
    listSize = 0;
}


/**
 * Create a new node using the given data, and insert to the end of the list
 * @param data -> string given by user, max length 80 chars
 */
void LinkedList::insertEnd(std::string data) {
    //create new node and populate with data
    Node *newNode = new Node();
    newNode->data = data;

    //if the list is currently empty, then assign the head and tail as the newNode
    if (this->isEmpty()) {
        head = newNode;
        tail = newNode;
        listSize++;
    } else { //make current end of list point to newNode, and then set the new tail
        tail->next = newNode;
        tail = newNode;
        listSize++;
    }
}


/**
 * Insert a line of text into a specific index of the list, pushing what was there ahead of it
 * @param index -> location where to place the data (starts at 1)
 * @param data  -> string to be inputted
 */
void LinkedList::insert(int index, std::string data) {
    //if we are trying to insert at the end of the list, just call insertEnd
    if(index == (this->size()+1)){
        this->insertEnd(data);
    } else if ((index < this->size()+1) && (index > 0)) {  //if the index is within the bounds, then perform the insertion
        //create new node and populate with data
        Node* newNode = new Node();
        newNode->data = data;

        //if the index is one, then place at front of list
        if(index == 1){
            newNode->next = head;
            head = newNode;
            return;
        }

        //node to iterate
        Node* temp = head;

        //iterate to location right behind where we want to
        for(int i = 2; i < index; i++){
            temp = temp->next;
        }

        //place node in the proper location, attaching to node before, and pointing to node after
        newNode->next = temp->next;
        temp->next = newNode;

        //increment list size
        listSize++;
    }
}


/**
 * Will search through the linked list and return the line that has this string of text
 * @param text -> string we are looking for
 */
void LinkedList::search(std::string text) {
    Node* temp = head;
    int index  = 1;
    bool isFound = false;

    while(temp != NULL){
        //if text is a substring of the value in the current node
        if(temp->data.find(text) != std::string::npos){
            std::cout << index << " " << temp->data << std::endl;
            isFound = true;
        }

        //iterate and update index
        temp = temp->next;
        index++;
    }

    if(!isFound){
        std::cout << "not found" << std::endl;
    }
}


/**
 * Will edit a line, replacing it with the given text
 * @param index -> number of line to be edited
 * @param data  -> text to change line to
 */
void LinkedList::edit(int index, std::string data) {
    //if the index is out of bounds, then return
    if(index > this->size() || index < 1){
        return;
    }

    //create node to iterate and iterate to location
    Node* temp = head;
    for(int i = 1; i < index; i++){
        temp = temp->next;
    }

    //update node data
    temp->data = data;
}


/**
 * Will delete the node at the given index
 * @param index -> location of node we want to delete
 */
void LinkedList::deleteNode(int index) {
    //if the index is out of bounds
    if(index > this->size() || index < 1){
        return;
    }

    //create nodes to iterate, and store prev node in list
    Node* temp = head;
    Node* prev = NULL;

    //if we are deleting the first node in the list
    if(index == 1){
        listSize--;

        //if this is deleting the last node (by size) in the list, then set head / tail to NULL
        if(this->size() == 0){
            head = NULL;
            tail = NULL;
        } else {
            head = temp->next;
        }
        delete(temp);
        return;
    }

    //iterate to node we need to delete, and keep track of previous node
    for(int i = 1; i < index; i++){
        prev = temp;
        temp = temp->next;
    }

    //if we are deleting the last node (by index) in the list, then set the previous node to point to NULL
    if(index == this->size()){
        prev->next = NULL;
        tail = prev;
    } else {  //otherwise, link the previous node with the node after the one we are deleting
        prev->next = temp->next;
    }

    delete(temp);
    listSize--;
}


/**
 * Will print all nodes in the list, including line numbers (starting at 1)
 */
void LinkedList::print() {
    Node* temp = head;
    int index = 1;
    while(temp != NULL){
        std::cout << index << " " << temp->data << std::endl;
        temp = temp->next;
        index++;
    }
}


/**
 * @return listSize -> amount of nodes in the list
 */
const int LinkedList::size() {
    return listSize;
}


/**
 * @return true -> list is empty
 */
bool LinkedList::isEmpty() {
    return this->size() == 0;
}


/**
 * Will take the command from user,a nd return a number based on command
 * @return int of command
 *      1 -> insertEnd
 *      2 -> insert
 *      3 -> delete
 *      4 -> edit
 *      5 -> print
 *      6 -> search
 *      7 -> quit
 */
int parseCommand(std::string command){
    //return number based on command inputted
    if(command == "insertEnd"){ return 1; }
    if(command == "insert")   { return 2; }
    if(command == "delete")   { return 3; }
    if(command == "edit")     { return 4; }
    if(command == "print")    { return 5; }
    if(command == "search")   { return 6; }
    if(command == "quit")     { return 7; }

    return 0;  //if no command is reached, then return 0
}


/**
 * Will remove all spaces before the quotation begins, and after the quotations end
 * @param x -> passed by reference to edit string in memory
 */
void removeOuterSpaces(std::string &x){
    //remove initial spaces
    while(x.length() != 0 && x.at(0) == ' '){
        x = x.substr(1);
    }

    //remove end spaces
    while(x.length() != 0 && x.at(x.length()-1) == ' '){
        x = x.substr(0, x.length()-1);
    }
}


/**
 * Will verify that the first and last character of a string has quotations
 * @param x  -> string to be checked
 * @return  true -> quotations are present at BOTH front and end
 */
bool verifyQuotations(std::string x){
    return (x.at(0) == '\"') && (x.at(x.length()-1) == '\"');
}


/**
 * Will remove the leading and end characters, if they are quotations.
 * NOTE: does not check if they are quotations, only call if you have verified quotations
 * @param x  -> string to edit, passed by reference
 */
void removeQuotations(std::string &x){
    x = x.substr(1, x.length()-2);  //substring starting at 1 and going x.length()-2 indexes, will remove first and last
}


/**
 * Will make sure that all input data (not indexes) is clean and ready for use by linkedlist
 * @param data -> string user enters after command
 * @return true -> data successfully cleaned
 */
bool cleanData(std::string &data){
    //remove any whitespace before or after string
    removeOuterSpaces(data);

    //if the input is empty, or above 82 chars (80 chars + 2 quotations), then it fails validation
    if(data.empty() || data.size() > 82){
        return false;
    }

    //if there are quotations at the start and end of string (ie: proper format), then remove them
    if(verifyQuotations(data)) {
        removeQuotations(data);
        return true;
    }

    return false;
}


int main() {
    LinkedList *list = new LinkedList();

    bool isActive = true;
    while(isActive){
        //retrieve command (first word inputted by user)
        std::string command;
        std::cin >> command;

        //holds all possible input after the command
        std::string inputdata;
        int index;

        //parse command to see what the next steps are (each case will have its own set of inputs)
        switch(parseCommand(command)){
            /** insertEnd */
            case 1:
                //retrieve data and clean/verify it
                getline(std::cin, inputdata);
                if(cleanData(inputdata)){
                    list->insertEnd(inputdata);
                }
                break;

            /** insert */
            case 2:
                //retrieve and verify index is an integer
                std::cin >> index;
                if(std::cin.fail()){
                    std::cin.ignore();
                    std::cin.clear();
                    continue;
                }

                //retrieve data and clean/verify it
                getline(std::cin, inputdata);
                if(cleanData(inputdata)){
                    list->insert(index, inputdata);
                }
                break;

            /** delete */
            case 3:
                //retrieve and verify index is an integer
                std::cin >> index;
                if(std::cin.fail()){
                    std::cin.ignore();
                    std::cin.clear();
                    continue;
                }

                list->deleteNode(index);
                break;

            /** edit */
            case 4:
                //retrieve and verify index is an integer
                std::cin >> index;
                if(std::cin.fail()){
                    std::cin.ignore();
                    std::cin.clear();
                    continue;
                }

                //retrieve data and clean/verify it
                getline(std::cin, inputdata);
                if(cleanData(inputdata)){
                    list->edit(index, inputdata);
                }
                break;

            /** print */
            case 5:
                list->print();
                break;

            /** search */
            case 6:
                //retrieve data and clean/verify it
                getline(std::cin, inputdata);
                if(cleanData(inputdata)){
                    list->search(inputdata);
                }
                break;

            /** quit */
            case 7:
                isActive = false;
                break;

            /** invalid command*/
            default: //invalid command
                break;
        }
    }
    return 0;
}