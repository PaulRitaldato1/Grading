//
// Created by Hubert Zhao on 9/9/2018.
// This is the header file for the String Singly Linked List that the text editor uses
#include<string>
#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

namespace std {
    class LinkedList {
    private:
        struct node { //node for linked list
            string value;
            node *next = 0;
        };
        node *head, *tail;
        int size;
    public:
        LinkedList(); //constructor

        ~LinkedList(); //destructor

        void insertEnd(string value); //insert value to end of list

        void insert(int position, string value); //insert value to position on list

        void deleteNode(int position); //delete value from position

        void edit( int position, string value); //edit value at position

        void print(); //display all values

        void search(string value); //search for instances of value


    };
}


#endif //LINKEDLIST_LINKEDLIST_H
