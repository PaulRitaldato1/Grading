/*
 * Name: Anthony Voong
 * Description: Created our own Linked List class that has a couple of functions such as inserting,
 * deleting, editing, searching, and printing. This is to form a simple line editor.
 */

#include <iostream>
#include <string>
using namespace std;

struct node{
    string line;
    struct node *next;
};

class LinkedList{
private:
    node *head;
public:
    LinkedList(){
        head = NULL;
    }
    void insertEnd(string sentence){
        node *tmp = new node;
        node *hold = new node;
        hold = head;
        tmp->line = sentence;
        tmp->next = NULL;

        if(head == NULL){       //Start the list by making the first node.
            head = tmp;
        }
        else{                   //After making a starting node, have the place holder always point to the newest node.
           for(int count = 1; hold->next != NULL; count++){
               hold = hold->next;
           }
           hold->next = tmp;
        }

    }
    void insert(int num, string sentence) {

        node *tmp = new node;
        tmp->line = sentence;
        tmp->next = NULL;
        node *curr = new node;
        curr = head;
        node *prev = new node;
        prev = head;

        if(head == NULL){       //If there is no linked list then no function should work.
            cout << "There is nothing to insert to" << "\n";
        }
        for(int count = 1; count < num; count++){   //Traverse the length of the list.
            if (curr->next == NULL) {       //If the instruction is not within bounds, create a node to prevent errors.
                if (count == num - 1) {
                    curr->next = tmp;
                }
                return;
            }

            curr = curr->next;  //Continue traversing the linked list.
        }
        tmp->next = curr;   //Once the location has been found, insert at location and move the other node down.
        prev->next = tmp;
    }
    void del(int num){
        node *tmp = new node;
        tmp = head;
        node *curr = new node;
        curr = head;
        node *prev = new node;
        prev = head;

        if(head == NULL){       //If there is no linked list then no function should work.
            cout << "There is nothing to delete." << "\n";
        }

        for(int count = 1; count < num; count++){
            if(tmp->next == NULL){  //If the location of deletion does not exist, ignore it.
                return;
            }else {
                prev = curr;
                curr = curr->next;
                tmp = prev->next; //Keep trvaersing the list while moving the pointers.
            }
        }

        delete tmp; //Delete the node.
        prev->next = curr->next;    //Adjust the list.

    }
    void edit(int num, string sentence) {
        node *tmp = new node;
        tmp->line = sentence;
        tmp->next = NULL;
        node *curr = new node;
        curr = head;
        node *prev = new node;
        prev = head;

        if (head == NULL) {      //If there is no linked list then no function should work.
            cout << "There is nothing to edit." << "\n";
        } else {
            for (int count = 1; count < num; count++) {
                curr = curr->next;      //Traverse the list.
                tmp->next = curr->next;
            }                           //Change the value in the node tmp points to.
            prev->next = tmp;
        }
    }
    void search(string sentence) {

        node *tmp = new node;
        tmp = head;
        node *curr = new node;
        curr = head;
        node *prev = new node;
        prev = head;

        int num = 0;

        if (head == NULL) {      //If there is no linked list then no function should work.
            cout << "There is nothing to search for." << "\n";
        }
        if (head->line == sentence || head->line.find(sentence) != -1) { //If the user searches for a value that is
                                                                        //equal to the head, print the following line.
            cout << "1" << " " << tmp->line << "\n";
        }
        if (tmp->next != NULL){
            for (int count = 2; tmp->next != NULL; count++) {   //traverse the linked list until a match is found.
                curr = curr->next;
                tmp = curr;

                if (tmp->line == sentence || tmp->line.find(sentence) != -1) {  //Once a match is found, print it and
                                                                                //increment the counter.
                    num++;
                    cout << count << " " << tmp->line << "\n";

                }
            }
         }
         if(num == 0){      //If the counter was not incremented, then such a sentence does not exist in the list.
            cout << "not found " << "\n";

        }
    }

    void print(){
        node *tmp = new node;
        tmp = head;
        if(head == NULL){        //Check if there is a node to print.
            cout << "There is nothing to print." << "\n";
        }
        else{
            for(int count = 1; tmp != NULL; count++){       //As long as there are nodes, print each line with a number
                                                            //to designate each line.
                cout << count << " " << tmp->line << "\n";
                tmp = tmp->next;

            }
        }
    }


};

int main() {

    LinkedList lineEditor;
    string instruction = "";

    int loc;
    do{
        std::getline(std::cin, instruction);
        if(instruction.find("quit") != -1){ //If quit is inputted, break out of the loop.
            break;
        }
        else if(instruction.find("insertEnd") != -1){ //If insertEnd is inputted, call the function after
                                                 //removing the insertEnd text and the quotations.
            instruction.erase(0,11);
            instruction.erase(instruction.size() -1);
            lineEditor.insertEnd(instruction);
        }
        else if(instruction.find("insert") != -1){  //If insert is inputted, call the function and grab the integer
                                                    //from the input for printing and remove the quotes and instruction.
            int grab = instruction[7];
            loc = grab - 48;

            instruction.erase(0,10);
            instruction.erase(instruction.size() -1);
            lineEditor.insert(loc, instruction);
        }
        else if(instruction.find("delete") != -1){  //If delete is inputted, call the function and grab the integer
                                                    //from the input to print it.
            int grab = instruction[7];
            loc = grab - 48;

            lineEditor.del(loc);
        }
        else if(instruction.find("edit") != -1){    //If edit is inputted, call the function, grab the integer, change
                                                    //the value to an int and erase the unneccessary text.
            int grab = instruction[5];
            loc = grab - 48;

            instruction.erase(0,8);
            instruction.erase(instruction.size() -1);
            lineEditor.edit(loc, instruction);
        }
        else if(instruction.find("search") != -1){  //If search is inputted, erase the unneeded text and call the function.
            instruction.erase(0,8);
            instruction.erase(instruction.size() -1);
            lineEditor.search(instruction);
        }
        else if(instruction.find("print") != -1){   //if print is inputted, print the current list.
            lineEditor.print();
        }
    }while(1); //Keep going until the input "quit" breaks the loop.

    return 1;
}