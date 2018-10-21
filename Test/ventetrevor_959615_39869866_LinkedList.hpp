//
//  LinkedList.hpp
//  Project1
//
//  Created by Trevor Vente on 9/15/18.
//  Copyright © 2018 Trevor Vente. All rights reserved.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp
#include <stdio.h>

struct Node {
    Node();
    int index;
    std::string value;
    Node* next;
    ~Node();
};

class LinkedList {
private:
    Node* head;
    Node* tail;
public:
    LinkedList();
    void insert(int index, std::string valueInput);
    void insertEnd(std::string valueInput);
    void edit(int index, std::string valueInput);
    void search(std::string valueInput);
    void del(int index);
    void initList(std::string valueInput);
    void incrementIndex(Node* current);
    void decrementIndex(Node* current);
    void print();
    ~LinkedList();
};
#endif /* LinkedList_hpp */
