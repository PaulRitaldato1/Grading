//
//  LinkedList_Class.hpp
//  Assignment1_DataStructures
//
//  Created by Edwin Carvajal on 9/14/18.
//  Copyright © 2018 Edwin Carvajal. All rights reserved.
//
#include <stdio.h>
#include <string>

#ifndef LinkedList_Class_hpp
#define LinkedList_Class_hpp

using namespace std;

struct Node{
    Node* next;
    string data;
};

class LinkedList{
    Node* head;
    Node* tail;
    
public:
    LinkedList();
    void insertEnd(string data);
    void insertSpecific(int position, string data);
    void deleteSpecific(int position);
    void editSpecific(int position, string data);
    void printList();
    void searchList(string data);
    
};

#endif /* LinkedList_Class_hpp */
