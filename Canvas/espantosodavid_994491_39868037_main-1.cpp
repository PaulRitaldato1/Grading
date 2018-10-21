#include <iostream>
//#include "LinkedList.h"
#include <list>
#include <iterator>

#include <string>

using namespace std;

struct Node{                                                            //Node struct implementation

public:                                                                 //Making Node's variables public

    string lineTextValue;                                               //Each node will have a value of a string type
    Node* next;                                                         //A node pointer pointing to the next node

};

class LinkedList {                                                      //Creating a LinkedList class that will create the template for my Linked List

public:
    Node *head;                                                         //head pointer to the Linked List
    Node *tail;                                                         //tail pointer to the Linked List

public:

    LinkedList() {                                                      //Public constructor for my LinkedList class
        head = NULL;                                                    //head pointing to null
        tail = NULL;                                                    //tail pointing to null
    }

    void insertEnd(string userInput) {                                  //insertEnd method which allows the user to insert a line to the linked list at the tail
        Node *newNode = new Node;                                       //newNode
        newNode->lineTextValue = userInput;                             //newNode holds the value of the user input
        newNode->next = NULL;                                           //newNode's next is null

        if (head == NULL) {                                             //If the linked list is empty, make the newNode equal to the head and tail
            head = newNode;
            tail = newNode;
        }
        else {                                                          //Else, meaning linked list is not empty, then make the tail's next the newNode
            tail->next = newNode;
            tail = newNode;                                             //Set the tail to the newNode
        }
    }

    void insertAtIndex(string userInput, int indexOfInsertion) {        //insertAtIndex method which allows the user to insert a line at a specified index, essentially inserting a node to the linked list
        Node *newNode = new Node;
        Node *currentNode = head;                                       //currentNode is equal to the head of the linked list
        Node *currentNext = NULL;
        newNode->lineTextValue = userInput;
        int counter = 1;                                                //Counter variable used to count where counterNode is in linked list and compares it to the indexOfInsertion

        while (true) {                                                  //Using this outer while loop in order to break out of the loop while my currentNode is NULL
            if (indexOfInsertion == 1) {
                head = newNode;
                newNode->next = currentNode;
            } else {
                while (counter < (indexOfInsertion - 1)) {              //While the currentNode is not before the index that we want to insert, make the counterNode the next one
                    currentNode = currentNode->next;
                    if(currentNode == NULL){                            //If counterNode is NULL, hence at the end of the linked list, then break out of the while loop
                        break;
                    }
                    counter++;
                }
                if(currentNode == NULL){                                //Break out of the outer while loop
                    break;
                }
                currentNext = currentNode->next;                        //currentNode's next is where we want to insert. Make currentNext equal to currentNode's next
                currentNode->next = newNode;                            //currentNode's next is points to the newNode
                newNode->next = currentNext;                            //newNode's next is pointing to currentNext
                break;
            }
        }
    }


    void deleteAtIndex(int indexOfDeletion){                            //deleteAtIndex method which allows the user to delete a line at a specific index, essentially deleting a node from the linked list
        Node *currentNode = head;                                       //currentNode is points to the head of the linked list
        Node *prevNode = head;                                          //prevNode points the head of the linked list
        int counter = 1;                                                //A counter variable that guides where we are in the linked list, used to compare if we are at the index of deletion

        while(true) {                                                   //Using this outer while loop in order to break out of the loop while my currentNode is NULL
            if (indexOfDeletion == 1) {                                 //If user is trying to delete the head, make the new head point to the currentNode's next
                head = currentNode->next;
                delete (currentNode);                                   //Delete currentNode from the linked list
            } else {
                while (counter < indexOfDeletion) {                     //While the currentNode is not before the index that we want to delete, make the counterNode the next one
                    prevNode = currentNode;                             //Making prevNode point to the currentNode before currentNode points to the next node in order to maintain prevNode as the previous node from currentNode
                    currentNode = currentNode->next;
                    if(currentNode == NULL){                            //If counterNode is NULL, hence at the end of the linked list, then break out of the while loop
                        break;
                    }
                    counter++;

                }
                if(currentNode == NULL){                                //Break out of the outer while loop
                    break;
                }
                prevNode->next = currentNode->next;                     //currentNode is where we want to make the deletion, hence make prevNode's next point to currentNode's next
                delete (currentNode);                                   //Delete currentNode from the linked list
                break;
            }
        }

    }

    void editAtIndex(string userInput, int indexOfEdit){                //editAtIndex method that allows the user to edit a particular line, essentially editing the lineTextValue of a node in the linked list
        Node *currentNode = head;                                       //Make currentNode point to the head of the linked list
        int counter = 1;                                                //A counter variable that tracks where we are in the linked list

        if(indexOfEdit == 1){                                           //If user wants to edit the first value, then change the head's lineTextValue to the user input
            head->lineTextValue = userInput;
        }
        else{
            while(counter < indexOfEdit){                               //While we are not where we want to edit, then make the currentNode point to the next node in the linked list
                currentNode = currentNode->next;
                counter++;
            }
            currentNode->lineTextValue = userInput;                     //At the node where user wants to edit, hence  currentNode's value to the user input
        }
    }

    void searchText(string userLine, string searchWord) {               //searchText method that allows the user to search for a particular line, essentially finding a node in the linked list
        Node *iterator = head;                                          //Iterator node that points to the head of the linked list. Used to iterate through the linked list
        int index = 1;                                                  //Index used to print what line user is searching for
        bool foundSearchWord = false;                                   //Boolean variable that is used to see if the word was found in the linked list

        while(iterator != NULL){                                        //While the iterator is not pointing to null
            int foundIndex = iterator->lineTextValue.find(searchWord);  //Int variable used to see if the word is found, hence giving the index of the word, and not a -1
            if(foundIndex >= 0) {
                cout << index << " " << iterator->lineTextValue << endl;    //Print the index and the line value of what the user is searching for
                foundSearchWord = true;                                 //Make foundSearchWord true, hence it will not print out "not found"
            }
            iterator = iterator->next;                                  //Change the iterator to point to the next node in order to search through the whole list
            index++;
        }
        if(foundSearchWord == false){                                   //If the search word is not found, then print "not found"
            cout << "not found" << endl;
        }

    }

    void printList() {                                                  //printList method that prints each line, essentially printing each node in the linked list
        Node *iterator = head;                                          //Iterator node that points to the head and is used for iterating through the linked list
        int index = 1;                                                  //Index used to print what line

        while (iterator != NULL) {                                      //While the iterator is not pointing to null
            cout << index << " " << iterator->lineTextValue << endl;    //Print the index and the line value of the linked list
            iterator = iterator->next;                                  //Change the iterator to point to the next node in order to search through the whole list
            index++;
        }
    }

};;



int main() {

string line;                                                                            //String variable used for the line that user is inserting
string userInput;                                                                       //String variable used for user input in quotations
LinkedList linkedList;                                                                  //Creation of an object from the LinkedList class


while((getline(cin,line))) {                                                            //While the program is receiving commands through cin, select which function to call

    if (line.find("insertEnd") == 0) {                                                  //If the user types insertEnd at the beginning of the line

        int firstIndex = line.find("\"");                                               //Int variable called firstIndex that finds the index of the first quotations
        int secondIndex = line.length()-2;                                              //Int variable called secondIndex that finds the index of the last letter in the line


        userInput = line.substr(firstIndex + 1, (secondIndex - firstIndex));            //UserInput is equal to the substring from the first letter after the first quotation to the difference between the last letter and the first letter that gets the user's text value
        linkedList.insertEnd(userInput);                                                //Call the insertEnd method
        continue;
    }

    if (line.find("insert") == 0) {                                                     //If the user types insert at the beginning of the line

        int firstIndex = line.find("\"");                                               //Int variable called firstIndex that finds index of the first quotations
        int secondIndex = line.length()-2;                                              //Int variable called secondIndex that finds the index of the last letter in the line
        int index = stoi(line.substr(7));                                               //Int variable called index that is equal to the number of the line where the user wants to insert. Stoi() casts a string to an int in C++

        userInput = line.substr(firstIndex + 1, (secondIndex - firstIndex));            //UserInput is equal to the substring from the first letter after the first quotation to the difference between the last letter and the first letter that gets the user's text value
        linkedList.insertAtIndex(userInput,index);                                      //Call the insertAtIndex method
        continue;
    }

    if(line.find("delete") == 0){                                                       //If the user types delete at the beginning of the line

        int index = stoi(line.substr(7));                                               //Int variable called index that is equal to the number of the line where the user wants to delete. Stoi() casts a string to an int in C++
        linkedList.deleteAtIndex(index);                                                //Call the deleteAtIndex method
        continue;

    }

    if(line.find("edit") == 0){                                                         //If the user types edit at the beginning of the line

        int firstIndex = line.find("\"");                                               //Int variable called firstIndex that finds the index of the first quotations
        int secondIndex = line.length()-2;                                              //Int variable called secondIndex that finds the index of the last letter in the line
        int index = stoi(line.substr(5));                                               //Int variable called index that is equal to the number of the line where the user wants to edit. Stoi() casts a string to an int in C++

        userInput = line.substr(firstIndex + 1, (secondIndex - firstIndex));            //UserInput is equal to the substring from the first letter after the first quotation to the difference between the last letter and the first letter that gets the user's text value
        linkedList.editAtIndex(userInput,index);                                        //Call the editAtIndex method
        continue;
    }

    if(line.find("search") == 0){                                                       //If the user types search at the beginning of the line

        int firstIndex = line.find("\"");                                               //Int variable called firstIndex that finds the index of the first quotations
        int secondIndex = line.length()-2;                                              //Int variable called secondIndex that finds the index of the last letter in the line

        userInput = line.substr(firstIndex + 1, (secondIndex - firstIndex));            //UserInput is equal to the substring from the first letter after the first quotation to the difference between the last letter and the first letter that gets the user's text value
        linkedList.searchText(line,userInput);                                          //Call the searchText method
        continue;
    }

    if (line.find("print") == 0) {                                                      //If the user types print at the beginning of the line
        linkedList.printList();                                                         //Call the printList method
        continue;
    }

    if (line.find("quit") == 0) {                                                       //If the user types quit, then quit the program
        break;
    }

}

    return 0;
}