#include <iostream>
#include <cstring>
#include <sstream>
#include "lineEditor.h"

using namespace std;

int main(){

    // initialize list object
    list obj;
    // string user will pass input to
    string command = "";

    // strings that will be compared against user input
    // to implement methods
    string insertAt = "insert";
    string insertEnd = "insertEnd";
    string deleteLine = "delete";
    string edit = "edit";
    string search = "search";
    string print = "print";

    // print a new line for readability
    cout << endl;

    // menu loop
    // if user types "quit", program terminates
    while(command != "quit"){

        // take command as input from user
        getline(cin,command);

        // if user types in "insertEnd", implement "insertEnd" method
        if(command.find(insertEnd) != string::npos){
            string strToPass = command.substr(11);
            strToPass = strToPass.substr(0, strToPass.size()-1);
            obj.insertEnd(strToPass);
            cout << endl;
        }

        // if user types in "insert", but NOT "insertEnd", implement
        // "insert" method
        else if(command.find(insertAt) != string::npos){
            cout << endl;
            string stringToInt;

            // loop to find line number
            for(int i = 0; i < command.size()-1; i++){
                if(isdigit(command[i])){
                    stringToInt += command[i];
                }
            }

            int indexToSubStr = command.find("\"");
            indexToSubStr++;
            int pos = stoi(stringToInt);
            pos--;
            string strToPass = command.substr(indexToSubStr);
            strToPass = strToPass.substr(0, strToPass.size()-1);
            obj.insert(pos, strToPass);
        }

        // if user types in "delete", implement "deleteAtPosition" method
        if(command.find(deleteLine) != string::npos){
            cout << endl;
            string stringToInt;

            // loop to find line number
            for(int i = 0; i < command.size(); i++){
                if(isdigit(command[i])){
                    stringToInt += command[i];
                }
            }

            int pos = stoi(stringToInt);

            // subtract position to go from human indexes "1, 2, 3..." to
            // computer index "0, 1, 2..."
            pos--;
            obj.deleteAtPosition(pos);
        }

        // edit method
        if(command.find(edit) != string::npos){
            cout << endl;
            string stringToInt;

            // loop to find line number
            for(int i = 0; i < command.size()-1; i++){
                if(isdigit(command[i])){
                    stringToInt += command[i];
                }
            }
            int pos = stoi(stringToInt);
            int indexToSubStr = command.find("\"");

            // add one to index to go one past the double quote
            indexToSubStr++;
            string strToPass = command.substr(indexToSubStr);
            strToPass = strToPass.substr(0, strToPass.size()-1);
            obj.edit(pos, strToPass);
        }

        // if user types in "search", implement "search" method
        if(command.find(search) != string::npos){
            cout << endl;
            int indexToSubStr = command.find("\"");

            // add one to index to go one past the double quote
            indexToSubStr++;
            string input = command.substr(indexToSubStr);
            input = input.substr(0, input.size()-1);
            obj.search(input);
        }
     
        // if user types in "print", implement "print" method
        if(command.find(print) != string::npos){
           cout << endl;
           obj.print();
           
        }

    }
	return 0;
}

// insertEnd method
node* list::insertEnd(string l) {

    node *temp = new node;
    temp->line = l;
    temp->next = NULL;
    if(head == NULL) {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else {	
        tail->next = temp;
        tail = temp;
    }
    return head;
}

// insert method
node* list::insert(int index, string l) {
    node* addNode = new node();
    addNode->line = l;

    if (index <= 0) {
        addNode->next = head;
        head = addNode;
        return addNode;
    }

    int i = 0;
    node* curr = head;
    
    // loop to get curr node to point where we want
    while (i < index -1) {
        curr = curr->next;
        if(curr == NULL){
            return NULL;
        }
        i++;
    }

    node* next = curr->next;
    curr->next = addNode;
    addNode->next = next;
    return head;
}

void list::deleteAtPosition(int pos) {

   if (head == NULL) 
      return; 
  
   node* temp = new node();
   temp = head; 
  
    if (pos== 0) { 
        head = temp->next; 
        delete(temp);               
        return; 
    } 
   
    for (int i = 0; temp ! =NULL && i < pos-1; i++) {
         temp = temp->next; 
    }
  
    if (temp == NULL || temp->next == NULL) 
         return; 
  
    node *next = new node();
    next = temp->next->next; 
    delete(temp->next);  
    temp->next = next;  
}

void list::edit(int pos, string l) {

    node *current=new node();
    current=head;

    for(int i = 1; i< pos; i++) {
        current = current->next;
    }

    current->line = l;
}

void list::print() {

    node *temp=new node();
    temp=head;
    int counter = 1;

    // loop through list and print node data
    while(temp != NULL) {
      cout << counter << " ";
      cout << temp->line <<endl << endl;
      counter++;
      temp = temp->next;
    }
}

void list::search(string l) {

    node *temp=new node();
    temp = head;
    int counter = 1;

    // loop through list to find line where passed string
    // is located
    while(temp != NULL) {

      if(temp->line.find(l) != string::npos){
        cout << counter << " ";
        cout<< temp->line << endl << endl;
        return;
      }

      counter++;
      temp = temp->next;
      
    }
      cout << "not found"; 
}

