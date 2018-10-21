#include <iostream>
#include <string>
#include <stdexcept>

#ifndef UNTITLED_PA1_H
#define UNTITLED_PA1_H

#include <iostream>

using namespace std;
//creates a class for the nodes to be used in the linked list
class node
{
public:
    string data;
    node *next;
};
//create a class for linked list
class linkedList {
private:
    node *head;
public:
    // creates the variables and methods that can be called in linked list class
    int length;

    linkedList();

    void insert(int index, string text);

    void insertEnd(string text);

    void deleteAtIndex(int index);

    void edit(int index, string text);

    void print();

    void search(string text);

};
//linked list constructor
linkedList::linkedList(){
    length = 0;
    head = NULL;
}
//adds a node to a linked list at a given position
void linkedList::insert(int index,string text){

    node *a = new node();
    node *b = new node();
    node *c = new node();

    if (index == 0){

        a-> data = text;
        a -> next = head;
        head = a;
    }
    else {

        c = head;
        for(int i = 0;i < index ; i++){
            b = c;
            c = c-> next;
        }
        a->data = text;
        a->next = c;
        b->next = a;
    }
    length++;
}
//adds a node to a linked at the end
void linkedList::insertEnd(string text){

    insert(length, text);
}
//deletes a node at any position in the linked list
void linkedList::deleteAtIndex(int index){

    node *a = new node();
    node *b = new node();
    a = head;

    if (index ==0){

        b = head;
        head = head->next;
    }
    else{
        for(int i =0;i<index;i++){
            b = a;
            a = a->next;
        }
        b->next = a->next;
    }
    length--;
}
//replaces the contents of a specific node
void linkedList::edit(int index,string text){

node *a = head;

    for(int i =0;i<index;i++){
    a = a->next;
}
    a->data = text;
};
//prints out the contents of every node in the linked list
void linkedList::print(){

node *a = head;
int i =1;

while(a != nullptr){

    cout<< i  << " " << a->data<< "\n";
    a = a->next;
    i++;
}
}
//searches the contents of every node to see if that string is a part of one. It then prints out the line number and string it was found.
void linkedList::search(string text){
    node *a = head;
    bool found = false;
    for(int i =0;i<length;i++){
        if(a->data.find(text) != std::string::npos){
        cout<<i+1<<" "<<a->data<<'\n';
        found = true;

        }
      a = a->next;
    }
        if(!found){
            cout<<"not found\n";
        }
}
#endif //UNTITLED_PA1_H


int main() {
    // Initializes strings to be used for input and the linked list
    string input;
    linkedList fullText;
    int index = 0;
    string text;
    bool exit = false;
    //creates a while loop to get user to call the methods that they want
    while(!exit) {
        cin >> input;
        //executes the insertEnd method with the user input
        if (input == "insertEnd") {
            getline(std::cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            fullText.insertEnd(text);
        }
        //executes the insert method with the user input
        else if (input == "insert") {
            cin >> index;
            getline(cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            if (index <= fullText.length +1 )
            {
                fullText.insert(index - 1, text);
            }

        }
        //executes the delete method with the user input
        else if (input == "delete") {
            cin >> index;
            if (index <= fullText.length )
            {
                fullText.deleteAtIndex(index - 1);
            }
        }
        //executes the edit method with the user input
        else if (input == "edit") {
            cin >> index;
            getline(cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            if (index <= fullText.length )
            {
                fullText.edit(index - 1, text);
            }

        }
        //executes the print method with the user input
        else if (input == "print") {
            fullText.print();
        }
        //executes the search method with the user input
        else if (input == "search") {
            getline(std::cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            fullText.search(text);
        }
        // terminates the program
        else if (input == "quit") {
            exit = true;
        }
        else {
        }

    }


    return 0;
}
