//
//  LinkedList.cpp
//  Project1
//
//  Created by Trevor Vente on 9/15/18.
//  Copyright © 2018 Trevor Vente. All rights reserved.
//
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include "LinkedList.hpp"

Node::Node() {
    next = nullptr;
}

Node::~Node() {
}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList() {
}

void LinkedList::insert(int index, std::string valueInput) {
    if(valueInput.length() > 80) {
        std::cout << "requested string is too long! lines are limited to 80 characters!" << std::endl;
        return;
    }
    
    if(index < 1) {
        return;
    }
    else if(index == 1) {
        if(head == nullptr) {
            initList(valueInput);
        }
        else {
            Node* nNode = new Node();
            nNode->value = valueInput;
            nNode->index = index;
            nNode->next = head;
            
            head = nNode;
            incrementIndex(nNode);
        }
    }
    else {
        Node* current = head;
        while(current->next != nullptr) {
            if(current->next->index == index) {
                Node* nNode = new Node();
                nNode->index = index;
                nNode->value = valueInput;
                
                Node* dummy = current->next;
                if(dummy->next == nullptr) {
                    tail = dummy;
                }
                current->next = nNode;
                nNode->next = dummy;
                
                incrementIndex(nNode);
                return;
            }
            else {
                current = current->next;
            }
        }
        
        if(current->index + 1 == index) {
            insertEnd(valueInput);
        }
    }
}

void LinkedList::insertEnd(std::string valueInput) {
    if(head == nullptr) {
        initList(valueInput);
    }
    else {
        Node* nNode = new Node();
        nNode->value = valueInput;
        nNode->index = tail->index + 1;
        
        tail->next = nNode;
        tail = nNode;
    }
}

void LinkedList::edit(int index, std::string value) {
    Node* current = head;
    while(current != nullptr) {
        if(current->index == index) {
            current->value = value;
            return;
        }
        else {
            current = current->next;
        }
    }
}

void LinkedList::search(std::string value) {
    Node* current = head;
    int counter = 0;
    while(current != nullptr) {
        if(strstr(current->value.c_str(), value.c_str())) {
            std::cout << current->index << " " << current->value << std::endl;
            counter++;
        }
        current = current->next;
    }
    
    if(counter == 0) {
        std::cout << "not found" << std::endl;
    }
}

void LinkedList::del(int index) {
    Node* saved = new Node();
    saved->next = head;
    Node* current = saved;
    
    while(current->next != nullptr) {
        if(current->next->index == index) {
            Node* bridge = current->next;
            current->next = bridge->next;
            
            if(current->next == nullptr && head->index == tail->index) {
                tail = nullptr;
                head = nullptr;
            }
            else if(current->next == nullptr) {
                tail = current;
            }
            else {
                head = saved->next;
            }
            delete bridge;
            
            decrementIndex(current);
            return;
        }
        else {
            current = current->next;
        }
    }
}

void LinkedList::print() {
    Node* current = head;
    while(current != nullptr) {
        std::cout << current->index << " " << current->value << std::endl;
        current = current->next;
    }
}

void LinkedList::initList(std::string valueInput) {
    head = new Node();
    head->value = valueInput;
    head->index = 1;
    tail = head;
}

void LinkedList::incrementIndex(Node* current) {
    while(current->next != nullptr) {
        current->next->index++;
        current = current->next;
    }
}

void LinkedList::decrementIndex(Node* current) {
    while(current->next != nullptr) {
        current->next->index--;
        current = current->next;
    }
}
