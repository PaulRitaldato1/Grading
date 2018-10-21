#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "LineEditor.h"

LinkedList::LinkedList() //constructor to initialize empty linked list
{
    head = NULL;
}

bool LinkedList::isEmpty(){ //to check if linked list is empty

    if(head == NULL)
        return true;
    else
        return false;
}

void LinkedList::insertEnd(std::string line){ //insert at the end of the list

    Node* newNode = new Node;
    newNode->data = line;

    if(isEmpty()){
        head = newNode;
    }
    else{
        Node* current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::deleteLine(int index){ //delete line

    Node* current = head;
    Node* prev = head;

    if(index == 1){
        head = head->next;
    }

    else{
        int i = 1;

        while(current != NULL){

            if(i == index){
                prev->next = current->next;
                break;
            }
            else{
                i++;
                prev = current;
                current = current->next;
            }
        }
    }
}

void LinkedList::insertLine(std::string line, int index){ //insert line at given index

    Node* current = head;
    Node* prev = head;

    Node* newNode = new Node;
    newNode->data = line;

    int i = 1;

    if(index == 1){
        newNode->next = head;
        head = newNode;
        return;
    }
    else{
        while(current != NULL){
            if(i == index){
                prev->next = newNode;
                newNode->next = current;
                return;
            }
            else{
                prev = current;
                current = current->next;
                i++;
            }
        }
        if(index == i)
            insertEnd(line);
    }
}

std::string extractText(std::string line){ //extract text from within quotes

    std::stringstream ss(line);
    std::string temp = "";

    getline(ss, temp, '"');
    getline(ss, temp, '"');

    //cin.ignore();

    return temp;
}

int extractInteger(std::string userInput){ //obtain first numerical value from text

    std::stringstream ss;
    ss << userInput;
    std::string temp;
    int index;

    while (!ss.eof()) {
        ss >> temp;

        if (std::stringstream(temp) >> index)
            return index;
    }
}

void LinkedList::print(){ //print list

    Node* current = head;
    int i = 1;

    while(current != NULL){
        std::cout << i << " " << current->data << std::endl;
        current = current->next;
        i++;
    }
}
void LinkedList::searchLine(int index, std::string line){ //search for line that contains text given

    Node* current = head;
    int i = 1;
    bool notfound = true;

    while(current != NULL){
        if(current->data.find(line) != std::string::npos){
            std::cout << i << " " << current->data << std::endl;
            current = current->next;
            i++;
            notfound = false;
            continue;
        }
        else{
            current = current->next;
            i++;
        }
    }
    if(notfound)
        std::cout << "not found" << std::endl;
}


int main(){

    std::string userInput;
    LinkedList linkedlist;

    while(userInput != "quit"){

        getline(std::cin, userInput);

        if(userInput.find("insertEnd") != std::string::npos){

            std::string line = extractText(userInput);
            linkedlist.insertEnd(line);
        }
        else if(userInput.find("insert") != std::string::npos){

            int index = extractInteger(userInput);
            std::string line = extractText(userInput);
            linkedlist.insertLine(line, index);
        }
        else if(userInput.find("delete") != std::string::npos){

            int index = extractInteger(userInput);
            linkedlist.deleteLine(index);
        }
        else if(userInput.find("edit") != std::string::npos){

            int index = extractInteger(userInput);
            std::string line = extractText(userInput);
            linkedlist.deleteLine(index);
            linkedlist.insertLine(line, index);
        }
        else if(userInput.find("print") != std::string::npos){

            linkedlist.print();
        }
        else if(userInput.find("search") != std::string::npos){

            int index = extractInteger(userInput);
            std::string line = extractText(userInput);
            linkedlist.searchLine(index, line);
        }
    }
}
