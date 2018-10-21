//
//  main.cpp
//  Project 1
//
//  Created by Mark Lawrence on 9/20/18.
//  Copyright © 2018 Mark Lawrence. All rights reserved.
//

#include <iostream>
#include <string>

class Node {
public:
    std::string value;
    Node* next = NULL;
};

Node* addAtIndex(Node* head, int index, std::string newData);
Node* addAtEnd(Node* head, std::string newData);
void print(Node* head);
Node* deleteAtIndex(Node* head, int index);
void searchForText(Node* head, std::string searchedValue);
Node* editLine(Node* head, int lineToEdit, std::string newText);

int main(int argc, const char * argv[]) {
    // insert code here...
    Node* lineEditor = new Node();
    
    bool exit = false;
    do {                                //Continues to loop, allowing users to input commands
        
        std::string userInput = "";
        std::getline (std::cin, userInput);
        
        std::string delimiter = " ";
        size_t pos = 0;
        pos = userInput.find(delimiter);
        std::string command;
        command = userInput.substr(0, pos);        //Separates the first word into a separate command string
        
        //Compares the command string with the various commands the program can run
        if (command.compare("insertEnd") == 0){
            
            std::string phrase;
            int i = 11;                        //
            do {
                phrase += userInput.at(i);           //Loops through the rest of the input string, starting at the 11th character (character after the ")
                i++;
            } while (userInput.at(i) != '"');        //Stops looping when the next character in userInput is a "
            lineEditor = addAtEnd(lineEditor, phrase);
        }
        
        else if (command.compare("insert") == 0){
            char indexChar = 0;
            std::string phrase;
            indexChar = userInput.at(7);            //Saves the 7th character as the index the user is trying to access
            int i = 10;
            do {
                phrase += userInput.at(i);           //Save the rest of the characters to the phrase string
                i++;
            } while (userInput.at(i) != '"');
            int index = indexChar - '0';
            lineEditor = addAtIndex(lineEditor, index, phrase);
        }
        else if (command.compare("delete") == 0){
            char indexChar;
            indexChar = userInput.at(7);
            int index = indexChar - '0';
            lineEditor = deleteAtIndex(lineEditor, index);
        }
        else if (command.compare("edit") == 0){
            char indexChar = 0;
            std::string phrase;
            indexChar = userInput.at(5);
            int i = 8;
            do {
                phrase += userInput.at(i);
                i++;
            } while (userInput.at(i) != '"');
            int index = indexChar - '0';
            lineEditor = editLine(lineEditor, index, phrase);
        }
        else if (command.compare("print") == 0){
            print(lineEditor);                        //prints the contents in lineEditor
        }
        else if (command.compare("search") == 0){
            std::string phrase;
            int i = 8;
            do {
                phrase += userInput.at(i);
                i++;
            } while (userInput.at(i) != '"');
            searchForText(lineEditor, phrase);
        }
        else if(command.compare("quit") == 0){
            exit = true;                            //Sets exit equal to true, ending the loop
        }
        else{
            std::cout<<"Invalid command."<<std::endl;        //If the user enters an invalid command
        }
        
    } while (!exit);
    
    return 0;
}


Node* addAtIndex(Node* head, int index, std::string newData){
    Node* addNode = new Node();
    addNode->value = newData;
    if (index == 1){                //If you are trying to insert at the beginning of the list
        addNode->next = head;
        return addNode;
    }
    int i = 2;                      //Else, iterate through the list to find the node at the wanted index
    Node* current = head;
    while (i<index){                //Loop until the iteratior is at the desiered index
        current = current->next;
        if (current == NULL){
            return head;
        }
        i++;
    }
    if (current != NULL){
        Node* next = current->next;     //Bu this point, the current node is set at the correct location to insert
        current->next = addNode;
        addNode->next = next;
    }
    return head;
}

Node* addAtEnd(Node* head, std::string newData){
    Node* current = head;
    Node* addNode = new Node();
    addNode->value = newData;
    
    
    while (current != NULL) {                            //Find the end of the linked list
        if (current->next == NULL){                     //When the end has been reached, the next entry is NULL
            if (current->value.compare("") == 0){       //Special case for the first node added
                current->value = newData;               //For the first node, set the value of the head to newData
            }
            else{
                Node* next = current->next;         //This is where you need to add the new entry
                current->next = addNode;
                addNode->next = next;
            }
        }
        current = current->next;
    }
    return head;
}



Node* deleteAtIndex(Node* head, int index){        //Needs to be modified, remove at specific index
    Node* current = head;
    Node* previous = head;
    Node* temp;
    
    if (index == 1){        //If you want to remove the first entry
        temp = head;
        current = current->next;
        head = current;
        delete (temp);
    }
    else{                       //Else, iterate through the list to find the node at the wanted index
        int i=2;
        while (i<index){                //Loop until the iteratior is at the desiered index
            current = current->next;
            if (current == NULL){
                return NULL;
            }
            i++;
        }
        previous = current;
        current = current->next;
        
        if (current != NULL){           //Not able to delete an index longer than the list
            
            
            if (current->next != NULL){             //If the delete index is the middle of the list
                previous->next = current->next;
                temp = current;
                current = current->next;
                delete (temp);
            }
            else {                              //If the deleted entry is at the end of the list
                temp = current;
                previous->next = NULL;
                current = NULL;
            }
        }
    }
    return head;
}

void searchForText(Node* head, std::string searchedValue){
    Node* current = head;
    int index = 1;
    bool found = false;
    while (current != NULL) {
        std::size_t locationCheck = current->value.find(searchedValue);
        if (locationCheck < 100){
            std::cout<<index<<" "<<current->value<<std::endl;
            found = true;
        }
        
        current = current->next;
        index++;
    }
    if (!found){
        std::cout<<"not found"<<std::endl;
    }
}

Node* editLine(Node* head, int lineToEdit, std::string newText){
    Node* current = head;
    
    int i=1;
    while (i<lineToEdit){                //Loop until the iteratior is at the desiered index
        current = current->next;
        i++;
    }
    current->value = newText;
    
    return head;
}

void print(Node* head){
    Node* current = head;
    int index = 1;
    while (current != NULL) {
        std::cout << index <<" "<<current->value<< std::endl;
        index++;
        current = current->next;
    }
}
