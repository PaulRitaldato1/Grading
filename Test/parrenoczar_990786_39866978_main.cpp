#include <iostream>

struct node {
    std::string data;
    node *next;

    node() {

        this->next = nullptr;
    }
};

class linkedList {
private:
    node *head, *tail;
public:
    linkedList();

    void insertEnd(const std::string &input);

    void insert(const int &index, const std::string &input);

    void deleteLine(const int &index);

    void edit(const int &index, const std::string &input);

    void print();

    void search(const std::string &input);
};

// Default constructor used to initialize a linked list. It just sets the head and tail equal to nullptr
linkedList::linkedList() {

    head = nullptr;
    tail = nullptr;
}

//Function to insert a string at the end of a linked list
void linkedList::insertEnd(const std::string &input) {

    node *tempNode = new node();    //the temp node is used for holding the data value that needs to be inserted
    tempNode->data = input;
    if (head == nullptr) {             //special case for inserting when the list is empty
        head = tempNode;
        tail = tempNode;
    } else {
        tail->next = tempNode;      //sets the current tail value for 'next' equal to the new node with the value that needs to be inserted
        tail = tempNode;            //moves the tail up since a new node has been inserted at the end
    }
}

//Function to insert a string at a given index. Only insert successfully if the index already exists or is at the end of the list
void linkedList::insert(const int &index, const std::string &input) {

    if ((index > 1 && head == nullptr) || index == 0) {       //case for is the list is empty and the index is greater than 1, or if the index is 0
        return;
    }

    node *tempNode = new node();    //the temp node is used for holding the data value that needs to be inserted
    tempNode->data = input;

    if (head == nullptr) {          //special case for inserting when the list is empty
        head = tempNode;
        tail = tempNode;
        return;
    }

    if (index == 1) {               //special case for if the index is the head
        tempNode->next = head;
        head = tempNode;
        return;
    }

    node *itrNode = head;                       //itrNode is used for iterating through the list
    for (int i = 1; i < index - 1; ++i) {       //the for loop stops just before the given index
        if (itrNode->next == nullptr) {         //if statement exits the function if the given index does not exist
            return;
        }

        itrNode = itrNode->next;
    }

    tempNode->next = itrNode->next;
    itrNode->next = tempNode;
    if (itrNode == tail) {          //if the index is being insert is 1 above the tail, this updates the tail
        tail = itrNode->next;
    }
}

//Function to delete a line at a given index
void linkedList::deleteLine(const int &index) {

    if (head == nullptr || index == 0) {       //case for is the list is empty or the index is 0
        return;
    }

    if (index == 1) {                   //special case for if the index is the head
        node *tempNode = head;
        head = head->next;
        delete (tempNode);
        return;
    }

    node *itrNode = head;
    for (int i = 1; i < index - 1; ++i) {           //the for loop stops just before the given index
        if (itrNode->next == nullptr) {            //if statement exits the function if the given index does not exist
            return;
        }

        itrNode = itrNode->next;
    }

    node *tempNode = itrNode->next;
    if (tempNode == nullptr) {          //if the index is out of bounds
        return;
    }
    itrNode->next = tempNode->next;

    if (itrNode->next == nullptr) {     //if the node being delete was the tail, this updates the tail to the previous node
        tail = itrNode;
    }

    delete (tempNode);
}

//Function to change the data at a given node
void linkedList::edit(const int &index, const std::string &input) {

    if ((index > 1 && head == nullptr) || index == 0) {       //case for is the list is empty or if the index is 0
        return;
    }

    node *itrNode = head;                   //itrNode is used for iterating through the list
    for (int i = 1; i < index; ++i) {       //the for loop stops at the given index
        if (itrNode->next == nullptr) {        //if statement exits the function if the given index does not exist
            return;
        }

        itrNode = itrNode->next;
    }

    itrNode->data = input;
}

//Function to print th whole linked list
void linkedList::print() {

    node *itrNode = head;
    int index = 1;
    while (itrNode != nullptr) {
        std::cout << index << " " << itrNode->data << std::endl;
        itrNode = itrNode->next;
        index++;
    }
}

//Function to search for a given input inside a the list
void linkedList::search(const std::string &input) {

    bool isFound = false;
    node *itrNode = head;
    int index = 1;
    while (itrNode != nullptr) {
        if (itrNode->data.find(input) != std::string::npos) {
            isFound = true;
            std::cout << index << " " << itrNode->data << std::endl;
        }
        itrNode = itrNode->next;
        index++;
    }
    if (!isFound) {
        std::cout << "not found" << std::endl;
    }
}

//Function that removes spaces and quotation marks from a string
bool cleanInput(std::string &input) {

    while (!input.empty() && input.front() == ' ') {
        input = input.substr(1);
    }
    while (!input.empty() && input.back() == ' ') {
        input = input.substr(0, input.length() - 1);
    }
    if (input.front() == '\"' && input.back() == '\"') {
        input = input.substr(1, input.length() - 2);
        return true;
    }
    //std::cout << "Error. Something Wrong with input" << std::endl;
    return false;
}

//Function that retruns an interger based in the command typed. Sends a 0 if no command is found.
int parseInput(std::string &input) {

    if (input == "insertEnd") { return 1; }
    if (input == "insert") { return 2; }
    if (input == "delete") { return 3; }
    if (input == "edit") { return 4; }
    if (input == "print") { return 5; }
    if (input == "search") { return 6; }
    if (input == "quit") { return 7; }
    return 0;
}

int main() {

    linkedList *list = new linkedList();

    bool running = true;
    std::string command;
    int index;
    std::string data;

    while (running) {
        //std::cout << "\nType a command" << std::endl;

        std::cin >> command;

        switch (parseInput(command)) {      //Switch statement get case number from the parse input

            case 0: //Error
                std::cin.ignore(10000, '\n');
                std::cin.clear();
                //std::cout << "Error. Something Wrong with command" << std::endl;
                break;

            case 1: //insertEnd
                std::getline(std::cin, data);
                if (!cleanInput(data)) {
                    break;
                }
                list->insertEnd(data);
                break;

            case 2: //insert
                std::cin >> index;
                if (std::cin.fail()) {
                    std::cin.ignore(10000, '\n');
                    std::cin.clear();
                    //std::cout << "Error. Something Wrong with index" << std::endl;
                    break;
                }
                std::getline(std::cin, data);
                if (!cleanInput(data)) {
                    break;
                }
                list->insert(index, data);
                break;

            case 3: //delete
                std::cin >> index;
                if (std::cin.fail()) {
                    std::cin.ignore(10000, '\n');
                    std::cin.clear();
                    //std::cout << "Error. Something Wrong with index" << std::endl;
                    break;
                }
                list->deleteLine(index);
                break;

            case 4: //edit
                std::cin >> index;
                if (std::cin.fail()) {
                    std::cin.ignore(10000, '\n');
                    std::cin.clear();
                    //std::cout << "Error. Something Wrong with index" << std::endl;
                    break;
                }
                std::getline(std::cin, data);
                if (!cleanInput(data)) {
                    break;
                }
                list->edit(index, data);
                break;

            case 5: //print
                list->print();
                break;

            case 6: //search
                std::getline(std::cin, data);
                if (!cleanInput(data)) {
                    break;
                }
                list->search(data);
                break;
            case 7: //quit
                running = false;
                break;
            default:
                running = false;
                break;
        }
    }
    return 0;
}