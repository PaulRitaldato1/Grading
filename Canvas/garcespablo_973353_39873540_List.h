
#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

class Node {
    
    public:
        Node* next = NULL;
        string value;
    
};

class LinkedList {
    
    Node* head;
    Node* curr;
    Node* temp;

    public:
        LinkedList();
        void insertEnd(string input);
        void insertLine(int lineNum, string input);
        void deleteLine(int lineNum);
        void print();
        void edit(int lineNum, string data);
        void search(string input);
};

#endif
