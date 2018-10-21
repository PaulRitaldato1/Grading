//
//  main.cpp
//  LineEditor
//
//  Created by Matt Hannan on 9/21/18.
//  Copyright © 2018 Matthew Hannan. All rights reserved.
//

#include <cstddef>
#include <string>
#include <iostream>
//your linked list implementation here
struct ListNode
{
    std::string data;
    ListNode *next;
};

ListNode *head = NULL;

ListNode* findLastNode(){
    ListNode *lastNode = head;
    if(head != NULL){
        while(lastNode->next != NULL) lastNode = lastNode->next;
    }
    return lastNode;
}

void insertAtEnd(std::string line)
{
    ListNode *tempNode = new ListNode();
    tempNode->data = line;
    tempNode->next = NULL;
    ListNode *last = findLastNode();
    
    if(head == NULL)
    {
        head = tempNode;
        last = tempNode;
    }
    else
    {
        last->next = tempNode;
    }
    
}

void insertAtPosition(int position, std::string insertStrang) {
    
    if(head != NULL){
        ListNode *specificInsertNodeSpot = head;
        bool doesKeyExist = true;
        int counter = 1;
        
        while(doesKeyExist) {
            
            if(specificInsertNodeSpot->next == NULL && counter != position - 1){
                doesKeyExist = false;
                break;
            }
            else if(specificInsertNodeSpot->next == NULL && counter == position - 1){
                insertAtEnd(insertStrang);
                break;
            }
            else if(specificInsertNodeSpot->next != NULL && counter == position - 1) {
                ListNode *insertNode = new ListNode();
                insertNode->data = insertStrang;
                insertNode->next = specificInsertNodeSpot->next;
                specificInsertNodeSpot->next = insertNode;
                doesKeyExist = true;
                break;
            }
            else {
                specificInsertNodeSpot = specificInsertNodeSpot->next;
                counter++;
            }
            
        }
        
    }
    else {
        insertAtEnd(insertStrang);
    }
}

void deleteIt(int position)
{
    bool chill = false;
    if(head == NULL) {
        chill = true;
    }
    if(!chill){
        if(head->next == NULL && position == 1){
            ListNode *tempDelete = head;
            head = NULL;
            delete tempDelete;
        }
        if(head->next != NULL && position == 1){
            ListNode *tempDelete = head;
            head = head->next;
            delete tempDelete;
        }
        ListNode *myNode = head, *previous = head;
        int nodeCounter = 1;
        bool doesntExist = false;
        
        while(nodeCounter != position){
            if(myNode->next != NULL){
                myNode = myNode->next;
                nodeCounter++;
            }
            else{
                doesntExist = true;
                break;
            }
        }
        if(previous->next != NULL){
            while(previous->next != myNode) previous = previous->next;
        }
        else{
            doesntExist = true;
        }
        if(!doesntExist){
            previous->next = myNode->next;
            delete myNode;
        }
    }
}


void search(std::string searchedLine)
{
    ListNode *searchNode = head;
    int counter = 1;
    bool flag = false;
    
    while(searchNode != NULL)
    {
        if(searchNode->data.find(searchedLine) != std::string::npos)
        {
            std::cout << std::to_string(counter) + " " + searchNode->data + "\n";
            flag = true;
            if(searchNode->next != NULL){
                searchNode = searchNode->next;
                counter++;
            }
            else{
                break;
            }
        }
        else if (searchNode->next != NULL && searchNode->data.find(searchedLine) == std::string::npos){
            searchNode = searchNode->next;
            counter++;
        }
        else{
            break;
        }
    }
    
    if(flag == false)
        std::cout << "not found\n";
    
}

void print()
{
    int counter = 1;
    ListNode *myList;
    myList = head;
    
    while(myList != NULL)
    {
        std::cout << std::to_string(counter) + " " + myList->data + "\n";
        counter++;
        myList = myList->next;
    }
}

void edit(int position, std::string line){
    deleteIt(position);
    insertAtPosition(position, line);
}

int main()
{
    std::string command = "";
    int position = 0;
    std::string inputString;
    int lengthOfUncutString;
    
    while(position != -1){
        std::cin >> command;
        if(command == "quit") break;
        if(command == "insert" || command == "edit" || command == "delete"){
            std::cin >> position;
        }
        if (!(command == "delete" || command == "print")){
            getline (std::cin, inputString);
            lengthOfUncutString = inputString.length();
            inputString = inputString.substr(2, lengthOfUncutString - 3);
            if(inputString.length() > 80){
                std::cout << "String is too long, 80 char max";
            }
        }
        
        if(command == "insert"){
            insertAtPosition(position, inputString);
        }
        if(command == "edit"){
            edit(position, inputString);
        }
        if(command == "delete"){
            deleteIt(position);
        }
        if(command == "insertEnd"){
            insertAtEnd(inputString);
        }
        if(command == "print"){
            print();
        }
        if(command == "search"){
            search(inputString);
        }
    }
}
