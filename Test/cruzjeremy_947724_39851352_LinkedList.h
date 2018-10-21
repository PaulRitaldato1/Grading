//
// Created by Jeremy Cruz on 9/12/18.
//

#ifndef LINEEDITOR_LINKEDLIST_H
#define LINEEDITOR_LINKEDLIST_H
#include <iostream>
#include "stdio.h"

using namespace std;

int totalNode=0;

class LinkedList {
private:
    typedef struct node { // creates the node structure
        string data;
        node *next;

    } *nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;


// Public functions below used to modify linked list objects

public:
    LinkedList();

    void insert(string data, int index);
    void insertEnd(string data);
    void search(string find);
    void deleteNode(int nodeNum);
    void printList();
    void edit(int index, string newString);

};

LinkedList::LinkedList(){ // Constructor for  LinkedList object which is actually a linked list
    head = NULL;
    curr = NULL;
    temp = NULL;
}

/*
 * insertEnd method attaches the string/line to a node to the end of the linked list
 * It creates a new node to be attached to the end of the linkedList
 * */
void LinkedList:: insertEnd(string data){

    nodePtr n = new node;
    n->data = data;
    n->next = NULL;
    if (head != NULL){
        curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
        cout << "Line successfully added\n" << endl;
        totalNode++;
    }
    else{
        head = n;
        cout << "Line successfully added\n" << endl;
        totalNode++;
    }

}

/*
 * insert function works to create a new node and
 * place the line within the node at the chosen
 * index
 */
void LinkedList:: insert(string data, int index){

    nodePtr n = new node;
    n->data = data;
    if(head==NULL){
        head = n;
        cout << "Line successfully added\n" << endl;
        totalNode++;
        return;
    }
    if(index == 1){
        n->next=head;
        totalNode++;

    }

    int i=1;
    curr = head;

    while(i<index-1){

        curr=curr->next;
        if(curr==NULL){
            return;
        }

        i++;
    }
    nodePtr next1 =curr->next;
    curr->next=n;
    n->next=next1;
    cout << "Line successfully inserted\n" << endl;
    totalNode++;
}

/*
 * deleteNode functions to delete the node at the given index/nodeNumber
 * Method frees the node from memory to avoid future fragmentation issues
 */
void LinkedList::deleteNode(int nodeNum){

    if(totalNode==0){
       cout <<  "This line does not exist" << endl;
        return;
    }
    nodePtr temp1 = head;
    if(nodeNum==1){
        head=temp1->next;
        free(temp1);
        return;
    }
    int i;
    for(i = 0; i<nodeNum-2;i++){
        temp1=temp1->next;
    }
    nodePtr temp2 = temp1->next;
    temp1->next=temp2->next;
    free(temp2);
    cout << "Line successfully deleted" << endl;

}

/*
 * search Function works to look for a node by userInput
 * It looks through the string in each node in order to find a match
 * to the user input. If there is no string then the user will be prompted that the search
 * was unsuccessful
 */
void LinkedList::search(string check){
    int lineNum = 1;
    curr=head;
    bool found = false;

    while(curr!=NULL){

        if(curr->data.find(check)!=-1){

            cout << lineNum;
            cout << " "+ curr->data + "\n" << endl;
            found = true;
            break;

        }
        else{
            curr=curr->next;
            lineNum++;

        }
    }
    if(found==false){
        cout << "search unsuccessful" << endl;
    }
}

/*
 * Edit method works to replace the contents in the node of the given index
 * The contents will be replaced by editedString
 */
void LinkedList::edit(int index, string newString){

    nodePtr temp1 = head;
    if(index==1){
        temp1->data=newString;
        cout << "Line successfully edited\n" << endl;
        return;
    }
    int i;
    for(i = 0; i<index-1;i++){
        temp1=temp1->next;
    }
    if (temp1!=NULL){
        temp1->data = newString;
        cout << "Line successfully edited\n" << endl;
    }
    else{
        cout << "Line does not exist\n" << endl;
    }

}

// This function prints contents of linked list from the beginning/head node
void LinkedList::printList(){
    curr = head;
    cout << "\n";

    int lineNum =1;

    cout << lineNum;
    cout << " " + curr->data << endl;

    while(curr->next!=NULL){
        curr = curr->next;
        lineNum++;
        cout << lineNum;
        cout << " " + curr->data << endl;

    }
    cout << "\n";
}

#endif //LINEEDITOR_LINKEDLIST_H
