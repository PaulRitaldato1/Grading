#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "List.h"

using namespace std;

//Default constructor for initialization, no overloading necessary
List::List()
{
    char ch;
    head = NULL;
    curr = NULL;
    temp = NULL;
}
// Method to insert node at the end of the linked list
//Essentially a push method
void List::InsertEnd(std::string input)
{
    nodePtr n = new node;
    n->next = NULL;
    n->data = input;
    //int count = 1;

    if (head != NULL)
    {
        curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = n;
    }
    else
    {
        head = n;
    }
}
void List::InsertLine(int lineNum, std::string input)
{
    nodePtr n = new node;
    n->next = NULL;
    n->data = input;
    int count = 1;
    if(head != NULL){
        curr = head; 
    }
    else{
        exit; 
    }
    while (count < lineNum)
    {
        curr = curr->next;
        //next=next->next;
        count++;
        if (count == lineNum)
        {
            if (curr->next == NULL)
            {
                curr->next = n;
            }
            else
            {
                nodePtr temp = curr->next;
                curr->next = n;
                n->next = temp;
            }
        }
    }
}
void List::DeleteLine(int lineNum)
{
    if(head != NULL ){
        curr = head; 
    }
    nodePtr temp = new node; 
    int count = 1;
    while (count < lineNum)
    {
        curr = curr->next;
        count++;
        if (count == lineNum)
        {
            temp = curr->next->next;
            delete curr->next;
            curr->next = temp; 
        }
    }
}

void List::Search(std::string input){

}