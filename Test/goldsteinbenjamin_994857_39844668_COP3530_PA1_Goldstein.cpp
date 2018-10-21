//
//  pa1.cpp
//
//  Created by Ben Goldstein on 9/12/18.

#include <iostream>
#include <string>
#include <sstream>

#ifndef pa1_h
#define pa1_h

class Node {
private:
    std::string line;
    //stores the line of text
    Node * nextNode;
    //stores next node
public:
    Node(std::string line);
    //constructor
    ~Node();
    //destructor
    Node * getNextNode();
    //returns next node
    void setNextNode(Node * node);
    //sets next node
    std::string getLine();
    //returns line
    void setLine(std::string line);
    //sets line
};

class LinkedList {
private:
    Node * head;
    Node * tail;
    int size;
public:
    LinkedList();
    //constructor
    ~LinkedList();
    //destructor
    void addEnd(std::string line);
    //adds node to end
    void insert(int index, std::string line);
    //adds node in middle
    void remove(int index);
    //removes node
    void edit(int index, std::string newline);
    //edits a node
    void search(std::string line);
    //searches for node with line == line, prints results
    void display();
    //print the list
    
};


#endif /* pa1_h */

Node::Node(std::string line) {
//Constructor
    this->line = line;
    nextNode = NULL;
}

Node::~Node() {
//Deconstructor
    delete nextNode;
}

Node * Node::getNextNode() {
//Gets the next node of a node
    return nextNode;
}

void Node::setNextNode(Node * node) {
//Sets the next node of a node
    this->nextNode = node;
}

std::string Node::getLine() {
//Gets the line of a node
    return line;
}

void Node::setLine(std::string line) {
//Sets the line of a node
    this->line = line;
}

LinkedList::LinkedList() {
//Constructor
    size = 0;
    head = NULL;
    tail = NULL;
}

LinkedList::~LinkedList() {
//Destructor
    delete head;
    delete tail;
}

void LinkedList::addEnd(std::string line) {
//Adds a node to the list's end
    Node * newNode = new Node(line);
    if (head == NULL) {
        //create new list
        head = newNode;
        head->setNextNode(NULL);
        tail = NULL;
    } else if (size == 1) {
        //add to single node list
        tail = newNode;
        head->setNextNode(tail);
        tail->setNextNode(NULL);
    } else {
        //add new node's reference in middle of the list
        tail->setNextNode(newNode);
        tail = tail->getNextNode();
        tail->setNextNode(NULL);
    }
    size++;
}

void LinkedList::insert(int index, std::string line) {
//Inserts a node at the end of the list
    Node * temp = head;
    Node * newNode = new Node(line);
    int counter = 0;
    if (index >= size + 2 || index == 0) {
        return;
        //handles bad input
    }
    if (index == 1) {
        //adds node to beginning
        newNode->setNextNode(head);
        head = newNode;
    }
    else if (index == 2) {
        //handles adding node to 2nd index
        newNode->setNextNode(head->getNextNode());
        head->setNextNode(newNode);
    }
    else {
        while (temp != NULL && counter != index - 2) {
            counter++;
            temp = temp->getNextNode();
        }
        newNode->setNextNode(temp->getNextNode());
        temp->setNextNode(newNode);
    }
    size++;
}

void LinkedList::remove(int index) {
//Removes a node of given index from the list
    Node * temp = head;
    int counter = 0;
    if (index >= size + 1) {
        return;
        //handles bad input
    }
    if (index == 1) {
        head = head->getNextNode();
    }
    else if (index == size && index > 1) {
        //handles removing node at end of list
        while(counter != index - 2) {
            counter++;
            temp = temp->getNextNode();
        }
        tail = temp;
        tail->setNextNode(NULL);
    }
    else {
        while(counter != index - 2) {
            counter++;
            temp = temp->getNextNode();
        }
        //skip node to be removed
        temp->setNextNode(temp->getNextNode()->getNextNode());
    }
    size--;
    
}

void LinkedList::edit(int index, std::string value) {
//Edits a node of given index with new value of value
    Node * temp = head;
    int counter = 0;
    if (index > size) {
        return;
    }
    while(temp != NULL && counter != index - 1) {
        counter++;
        temp = temp->getNextNode();
    }
    temp->setLine(value);
}

void LinkedList::search(std::string line) {
//Searches for a given text line in the list
    Node * temp = head;
    bool flag = false;
    int counter = 1;
    while(temp != NULL) {
        if(temp->getLine().find(line) != std::string::npos) {
            flag = true;
            std::cout << counter;
            std::cout << " ";
            std::cout << temp->getLine();
            std::cout << "\n";
        }
        counter++;
        temp = temp->getNextNode();
    }
    if (!flag) {
        std::cout << "not found\n";
    }
    
}

void LinkedList::display() {
//Displays the list
    Node * temp = head;
    int counter = 1;
    while(temp != NULL) {
        std::cout << counter;
        std::cout << " ";
        std::cout << temp->getLine();
        std::cout << "\n";
        temp = temp->getNextNode();
        counter++;
    }
}

bool checkForQuotes(std::string s) {
//Returns true if quotes are paired properly, false otherwise.
    
    int count = 0;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '"') {
            count++; //increase count of quotes
        }
    if(count < 2) {
        return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    LinkedList * list = new LinkedList();
    
    std::string choice = "";
    
   while(choice.substr(0, 5) != "quit") {
        //Options:
        //insertEnd - print - search - quit - insert
        std::getline (std::cin,choice);
        try {
       
            if (choice.substr(0, 5) == "print") {
                list->display();
                //display output
            }
            else if (choice.substr(0, 9) == "insertEnd") {
                if(!checkForQuotes(choice)) {
                    throw std::exception();
                    //if quotes are not paired reject the command
                }
                list->addEnd(choice.substr(11, choice.find_last_of("\"") - choice.find_first_of("\"") - 1));
                //add node with line equal to quoted portion to the list
            }
            else if (choice.substr(0, 6) == "delete") {
                int index = std::stoi (choice.substr(7,1));
                //extract & convert index
                list->remove(index);
                //remove the node
            }
            else if (choice.substr(0, 6) == "insert" && choice.substr(0, 9) != "insertEnd") {
                if(!checkForQuotes(choice)) {
                    throw std::exception();
                    //if quotes are not paired reject the command
                }
                int index = std::stoi (choice.substr(7,1));
                //convert string index to integer
                list->insert(index, choice.substr(10, choice.find_last_of("\"") - choice.find_first_of("\"") - 1));
                //insert node at given index with quoted text
            }
            else if (choice.substr(0, 4) == "edit") {
                if(!checkForQuotes(choice)) {
                    throw std::exception();
                    //if quotes are not paired reject the command
                }
                int index = std::stoi (choice.substr(5, 1));
                //convert string index to integer
                list->edit(index, choice.substr(8, choice.find_last_of("\"") - choice.find_first_of("\"") - 1));
                //edit node with given index and using new text in quotes
            }
            else if (choice.substr(0, 6) == "search") {
                list->search(choice.substr(8, choice.find_last_of("\"") - choice.find_first_of("\"") - 1));
                //seach for portion in quotes
            }
       }
        catch (std::exception) {
            //take no action aside from resuming loop if error is encountered
        }
    }
    

    
}



