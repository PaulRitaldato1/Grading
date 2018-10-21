//
//  LinkedList_Class.cpp
//  Assignment1_DataStructures
//
//  Created by Edwin Carvajal on 9/14/18.
//  Copyright © 2018 Edwin Carvajal. All rights reserved.
//
#include <string>
#include <iostream>
#include "LinkedList_Class.hpp"

using namespace std;


LinkedList::LinkedList(){
    head = NULL;
    tail =  NULL;
};

void LinkedList::insertEnd(std::string data){
    Node* newNode = new Node;

    if (!head){
        newNode->data = data;
        newNode->next = tail;
        head = newNode;
        tail = newNode;
        
    }else{
        newNode->data = data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        
    }
    
}

void LinkedList::insertSpecific(int position, std::string data){
    int count = 1;
    Node* insertNode = new Node;
    insertNode->data = data;
    
    if (position == count){
        insertNode->next = head;
        head = insertNode;
        return;
    }
    
    Node* iter = head;
    Node* prevIter = iter;
    
    while (count != position && iter != NULL){
        prevIter = iter;
        iter = iter->next;
        count++;
    }
    
    if(count == position){
        prevIter->next = insertNode;
        insertNode->next = iter;
    }
    
    return;
}

void LinkedList::deleteSpecific(int position){
    int count = 1;
    Node* iter;
    
    if (position == count){
        iter = head;
        head = head->next;
        delete(iter);
        
        return;
    }
    
    iter = head;
    Node* prevIter = iter;
    
    while (count != position && iter != NULL){
        prevIter = iter;
        iter = iter->next;
        count++;
    }
    
    if(count == position && prevIter->next != NULL){
        prevIter->next = prevIter->next->next;
        delete(iter);
    }
    
    return;
}

void LinkedList::editSpecific(int position, std::string data){
    int count = 1;
    
    if (position == count){
        head->data = data;
        return;
    }
    
    Node* iter = head;
    
    while (count != position && iter != NULL){
        iter = iter->next;
        count++;
    }
    
    iter->data = data;
    
    return;
}

void LinkedList::printList(){
    Node* iter = head;
    int count = 1;
    
    while(iter != NULL){
        cout << count << " " << iter->data << endl;
        iter = iter->next;
        count++;
    }
    
    return;
}

void LinkedList::searchList(std::string data){
    Node* iter = head;
    int count = 1;
    bool checkStatement = false;
    
    while(iter != NULL){
        if (iter->data.find(data) != std::string::npos) {
            cout << count << " " << iter->data << endl;
            checkStatement = true;
        }
        iter = iter->next;
        count++;
    }
    
    if(!checkStatement){
        cout << "not found" << endl;
    }
    
    return;
}


