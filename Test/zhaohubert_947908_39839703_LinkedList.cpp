//
// Created by Hubert Zhao on 9/9/2018.
//

#include "LinkedList.h"
#include <iostream>
namespace std {
    LinkedList::LinkedList() { //constructor with head, tail and size
        head = 0;
        tail = 0;
        size = 0;
    }

    LinkedList::~LinkedList() { //destructor to delete all nodes
        node *current = head;
        while (current != 0) {
            node *deleteNext = current->next;
            delete current;
            current = deleteNext;

        }
        head = 0;


    }

    void LinkedList::insertEnd(string value) {//insert node to the end
        node *temp = new node; //create new node
        temp->value = value; //set value
        temp->next = 0; //null after node
        if (head == 0) { //if list has no size, node that is inserted will become head
            head = temp;
            tail = temp;
        } else { //otherwise, the previous tail will point to the new node, and new tail will be the new node
            tail->next = temp;
            tail = temp;
        }
        size++; //increment size of list

    }

    void LinkedList::insert(int position, string value) {//insert to specific position
        node *temp = new node;
        temp->value = value;

        if (position == 1) { //if inserting to front, set previous head after new node, set current head to new node
            temp->next = head;
            head = temp;
            size++;
        } else if (position <= size && position > 0) { //if inserting to middle, loop to position before insert position
            node *current = head; //then connect previous node to new node, and new node to the node that was after previous node


            for (int i = 1; i < position - 1; i++) {
                current = current->next;
            }
            node *after = current->next;
            current->next = temp;
            temp->next = after;
            size++;
        } else if (position == size + 1) {//inserting to end
            tail->next = temp;
            tail = temp;
            size++;
        }
    }


    void LinkedList::deleteNode(int position) { //deletes node at position
        if (position == 1) { //delete head

            node *temp;
            temp = head;
            head = head->next;
            delete temp;
            size--;

        } else if (position < size && position > 0) { // delete from middle, link up nodes surrounding deleted node
            node *current = head;
            for (int i = 1; i < position - 1; i++) {
                current = current->next;
            }
            node *todelete = current->next; //delete this node called "todelete"
            current->next = current->next->next; //connect node behind "todelete" to node after "todelete"
            delete todelete; //delete node
            size--;
        } else if (position == size) { //delete end node, same as above but have to change tail
            node *current = head;
            for (int i = 1; i < size; i++) {
                current = current->next;
            }
            node *todelete = current->next;
            current->next = 0;
            delete todelete;
            tail = current;

            size--;

        }
    }

    void LinkedList::edit(int position, string value) {//edits node at position
        node *temp = head;
        if (position <= size && position > 0) { //loops to position if position is reasonable
            for (int i = 1; i < position; i++) {
                temp = temp->next;
            }
            temp->value = value; //changes value
        }
    }


    void LinkedList::print() {//prints node values with line numbers
        node *temp = head;
        for (int i = 1; i <= size; i++) {
            cout << i << " " << temp->value << endl;
            temp = temp->next;
        }

    }

    void LinkedList::search(string value) { //searches for nodes with specific value
        node *temp = head;
        bool foundString = false;

        for (int i = 1; i <= size; i++) {
            if (temp->value.find(value) != string::npos) { //if value searched for is contained in node value
                cout << i << " " << temp->value << endl; //print that line, allows for multiple finds
                foundString = true;

            }
            temp = temp->next;
        }
        if (!foundString) { //otherwise print not found
            cout << "not found" << endl;
        }

    }

}

