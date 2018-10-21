#ifndef LINEEDITOR_LINEEDITOR_H
#define LINEEDITOR_LINEEDITOR_H

#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class LinkedList {
private:
    struct nodeObj {
        string data;
        int index = 1;
        nodeObj *next = nullptr;

    };
    typedef struct nodeObj * nodePtr;
    nodePtr head;
    nodePtr tail;

public:
    LinkedList();
    int lines; //total number of lines in linked list
    void insertEnd(string text);
    void insert(int index, string text);
    void del(int index);
    void edit(int index, string text);
    void print();
    void search(string text);
};



#endif //LINEEDITOR_LINEEDITOR_H
