#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Node {
    string data;
    Node* next = nullptr;
};
Node* head;

void insertEnd(string text){ //insert text at end of linked list
    Node* temp = head;
    Node* tail = new Node();

    tail->data = text;
    tail->next = nullptr;
    //if the linked list is empty, then the last is the head
    if (head == nullptr){
        head = tail;
        head->next = nullptr;
        return;
    } else{
        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = tail; //establishes the actual last node
        return;
    }
}

void insertAtLine(int lineNum, string text){
    Node* temp = head;
    Node* prev = head;
    Node* lastOfMove = new Node();

    //count linked list size
    int listSize = 0;
    Node* counting = head;
    while(counting != nullptr){
        listSize++;
        counting = counting->next;
    }
    if(lineNum > listSize){
        if (lineNum == listSize + 1){
            insertEnd(text); //when the lineNum is the last node
            return;
        }
        else{
            return;
        }
    }
    lastOfMove->data = text;
    Node* tail = head;
    //looking for last node it is last node
    while(tail->next != nullptr){
        tail = tail->next;
    }
    //instantiate the begin of the list with 1 and iterate through to the wanted line number
    for (int i = 1; (temp != nullptr) && (i <= lineNum); i++) {
        if(i == lineNum){
            //do the moving nodes thing
            if(temp == head){
                lastOfMove->next = head;
                head = lastOfMove;
                return;
            } else if(temp->next == nullptr){ //if line is the tail
                Node* temp1 = new Node();

                temp1->data = tail->data;
                temp1->next = nullptr;
                tail->next = temp1;
                tail->data = text;
                return;
            }
            else{ //when the line is neither the head or tail
                Node* moveOver = new Node();
                moveOver->data = text;
                moveOver->next = prev->next;
                prev->next = moveOver;
            }
            return;
        } else{
            temp = temp->next;
            if(i >= 3) { //when there is a previous that exists aka when temp isn't head
                prev = prev->next;
            }
        }
    }
}

void deleteAtIndex(int lineNum){
    Node* curr = head;
    int listSize = 0;
    Node* counting = head;
    while(counting != nullptr){
        listSize++;
        counting = counting->next;
    }
    if(lineNum > listSize){
        //The line number does not currently exist in the list
        return;
    }
    if(lineNum == 1){ //if its the first line, then reassigned the head
        head = curr->next;
        free(curr);
        return;
    }
    for(int i = 0; i < lineNum - 2; i++){ //find the line
        curr = curr->next;
    }
    //remove the node
    Node* temp = curr->next;
    curr->next = temp->next;
    free(temp);
}

void edit(int lineNum, string text){
    Node* temp = head;
    //instantiate the begin of the list with 1 and iterate through to the wanted line number
    for (int i = 1; (temp != nullptr) && (i <= lineNum); i++) {
        if(i == lineNum){
            temp->data = text;
            return;
        } else{
            temp = temp->next;
        }
    }
}

void print(){
    Node* curr = head;
    int listSize = 1;
    while (curr != nullptr) {
        cout << listSize << " " << curr->data << endl;
        listSize++;
        if(curr->next == nullptr){
            return;
        }
        curr = curr->next;
    }
}

void search(string text){
    Node* curr = head;
    int size = 1;
    for(int i = 0; i < size; i++) {
        if(curr == nullptr){ //text not found
            cout << "not found" << endl;
            free(curr);
            return;
        } else if (curr->data.find(text) != string::npos) { //searches for multiple instances of text
            cout << size << " " << curr->data << endl;
            if(curr->next != nullptr) {
                curr = curr->next;
                size++;
            }
        } else{
            curr = curr->next;
            size++;
        }
    }
}

int main(){
    bool choice = false;
    head = nullptr;
    char space = ' ';
    char delimiter = '\"';
    while(!choice) {
        string command;
        string textEnd;

        getline(cin, command);

        unsigned int firstQuote = command.find(delimiter); //finds the first quotation mark
        unsigned int secondQuote = command.find(delimiter, firstQuote + 1); //finds the second quotation mark
        unsigned int commandLength = secondQuote - firstQuote - 1;
        string text = command.substr(firstQuote + 1, commandLength);

        if(text.length() > 80){
            //if greater than 80, ask for input again
        } else if (command.find("insert") != string::npos) {
            if (command.find("End") != string::npos) { //insert at end
                insertEnd(text);
            } else if (any_of(command.begin(), command.end(), ::isdigit)) { //insert at line
                string num;
                size_t pos = command.find(space);
                num = command.substr(0,pos);
                command.erase(0, pos + 1); //removes the command word
                num = command.substr(0,pos); //retrieves the line number
                int lineInt = stoi(num);

                insertAtLine(lineInt, text);
            }
        } else if (command.find("delete") != string::npos) {
            if (any_of(command.begin(), command.end(), ::isdigit)) { //any_of uses algorithm lib
                string num;
                size_t pos = command.find(space);
                num = command.substr(0,pos);
                command.erase(0, pos + 1); //removes the command word
                num = command.substr(0,pos); //retrieves the line number
                int lineInt = stoi(num);

                deleteAtIndex(lineInt);
            }
        } else if (command.find("edit") != string::npos) {
            string num;
            size_t pos = command.find(space);
            num = command.substr(0,pos);
            command.erase(0, pos + 1); //removes the command word
            num = command.substr(0,pos); //retrieves the line number
            int lineInt = stoi(num);

            edit(lineInt, text);
        } else if (command.find("print") != string::npos) {
            print();
        } else if (command.find("search") != string::npos) {
            search(text);
        } else if (command.find("quit") != string::npos) {
            choice = true;
        }
    }
    return 0;
}