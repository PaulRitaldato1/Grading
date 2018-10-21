#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "List.h"

using namespace std;

// Initialize list
LinkedList::LinkedList() {
    head = NULL;
    curr = NULL;
    temp = NULL;
}

// Add an item to the end of the list
void LinkedList::insertEnd(string input) {
    
    Node* newNode = new Node;
    newNode->value = input;
    
    curr = head;
    
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    while (curr->next != NULL) {
        curr = curr->next;
    }
    
    curr->next = newNode;
    
}

// Add an item to a specified index in the list
void LinkedList::insertLine(int lineNum, string input) {
    
    Node* newNode = new Node;
    newNode->value = input;
    
    int count = 1;
    if (head != NULL) {
        curr = head;
    } else {
        return;
    }
    
    if (lineNum == 1) {
        Node* temp = head;
        head = newNode;
        newNode->next = temp;
        return;
    }
    
    while (count < lineNum - 1) {
        curr = curr->next;
        count++;
    }
    
    if (curr->next == NULL) {
        curr->next = newNode;
    } else {
        Node* temp = curr->next;
        curr->next = newNode;
        newNode->next = temp;
    }
    
}

// Delete an item in a specified index in the list
void LinkedList::deleteLine(int lineNum) {
    
    curr = head;
    Node* temp = new Node;
    
    int count = 1;
    while (count != lineNum) {
        curr = curr->next;
        count++;
    }
    
    if (count == lineNum) {
        temp = curr->next;
        delete curr->next;
        curr->next = temp;
    }
    
}

// Search for an item in the list by value
void LinkedList::search(string input) {
    
    int count = 1;
    curr = head;
    
    while (curr != NULL) {
        
        if (curr->value.find(input) != -1) {
            cout << count << " " << curr->value << "\n";
        }
        
        curr = curr->next;
        count++;
        
    }
    
}

// Edits an item in the list by value at an index
void LinkedList::edit(int lineNum, string input) {
    
    int count = 1;
    curr = head;
    
    while (count != lineNum) {
        curr = curr->next;
        count++;
    }
    
    if (count == lineNum) {
        curr->value = input;
    }
    
}

// Prints the whole list
void LinkedList::print() {
    
    int count = 1;
    curr = head;
    
    while (curr != NULL) {
        
        cout << count << " " << curr->value << "\n";
        curr = curr->next;
        count++;
        
    }
    
}

// Finds int in string
int findInt(string str) {
    
    std::stringstream ss;
    ss << str;
    
    int found = -1;
    std::string temp;
    
    while (std::getline(ss, temp,' ')) {
        if (std::stringstream(temp)>>found) {
            return found;
        }
    }
    
    return found;
    
}

int main(int argc, const char * argv[]) {
    
    LinkedList list = LinkedList();
    
    string inputCommand;
    string inputString;
    
    while (inputString != "quit") {
        
        getline(cin, inputCommand);
        if (inputCommand.find("quit") != -1) {
            inputString = "quit ";
        } else if (inputCommand.find("insertEnd") != -1) {
            inputString = "insertEnd ";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            list.insertEnd(toAppend);
        } else if (inputCommand.find("insert") != -1) {
            inputString = "insert ";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            int pos = findInt(toAppend);
            string posStr = to_string(pos) + " ";
            toAppend = toAppend.erase(inputCommand.find(posStr), posStr.length());
            list.insertLine(pos, toAppend);
        } else if (inputCommand.find("delete") != -1) {
            inputString = "delete ";
            int pos = findInt(inputCommand);
            list.deleteLine(pos);
        } else if (inputCommand.find("edit") != -1) {
            inputString = "edit ";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            int pos = findInt(toAppend);
            string posStr = to_string(pos) + " ";
            toAppend = toAppend.erase(inputCommand.find(posStr), posStr.length());
            list.edit(pos, toAppend);
        } else if (inputCommand.find("print") != -1) {
            inputString = "print ";
            list.print();
        } else if (inputCommand.find("search") != -1) {
            inputString = "search ";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            list.search(toAppend);
        }
        
    }
    
    return 0;
    
}
