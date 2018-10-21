#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Node {
public:
    std::string data;
    Node* next;
};

class LinkedList {
public:
    int length;
    Node* head;
    LinkedList(); //declaring LinkedList constructor
    void insertEnd(string data);
    void insertIndex(int index, string data);
    void deleteLine(int index);
    void editLine(int line, string data);
    void print();
    void search(string data);
};

LinkedList::LinkedList(){ //defining constructor
    this->length = 0;
    this->head = NULL;
}


void LinkedList::deleteLine(int index) { //FINISHED
    //errors if index is not in the list
    if(index > this->length){
       // std::cout << "Error: invalid index" << std::endl;
        return;
    }
    Node* curr = this->head;
    Node* prev = new Node();
    if(index == 1){ //if the first element is desired to delete
        this->head = curr->next;
        curr->next = NULL;
    }
    for(int i = 1; i < index; i++){
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    this->length--;

}



void LinkedList::print() {
    Node* node = this->head;
    for(int i = 1; node != NULL; i++){
        std::cout << i << " " << node->data << std::endl;
        node = node->next;
    }
}


void LinkedList::search(string data){
    int strLength = data.length();
    Node* node = this->head;
    string origString;
    std::size_t found;
    for(int i = 1; node != NULL; i++){
        origString = node->data;
        found = origString.find(data);
        if(found != std::string::npos){ //as long as it does not equal -1 it means it found the string
            std::cout << i << " " << node->data << endl;
        }
        node = node->next;
    }
    if (found == std::string::npos){
        cout << "not found" << endl;
    }
}


void LinkedList::editLine(int line, string data) {
    if (data.length() > 81){
        std::cout << "Error: strings can only be up to 80 characters." << std::endl;
        return;
    }
    Node* node = this->head;
    if(line-1 > this->length){
      //  std::cout << "Error: Line is out of range" << std::endl;
        return;
    }
    for(int i = 1; node != NULL; i++) {
        if(i == line){
            node->data = data;
        }
        node = node->next;
    }
}

void LinkedList::insertIndex(int index, string data){
    if (data.length() > 81){
        std::cout << "Error: strings can only be up to 80 characters." << std::endl;
        return;
    }
    Node* node = new Node();
    Node* curr = this->head;
    Node* prev;
    node->data = data;
    if(index-1 > this->length){
      //  std::cout << "Error: index out of range" << std::endl;
    }
    else {
        if (index == 1) {
            this->head = node;
            node->next = curr;
        }
        for (int i = 1; i < index; i++) {
            prev = curr;
            curr = curr->next;
            if (curr == NULL) {
                break;
            }
        }
        prev->next = node;
        node->next = curr;
        this->length++;
    }
}

void LinkedList::insertEnd(string data){ //TESTING METHODS
    if (data.length() > 81){
        std::cout << "Error: strings can only be up to 80 characters." << std::endl;
        return;
    }
    Node* node = new Node();
    node->data = data;
    node->next = NULL;
    if(this->head == NULL){ //if linked list is empty set head to node
        this->head = node;
    }
    else {
        Node* temp;
        temp = this->head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = node;
    }
    this->length++;
}


int main() {
    LinkedList* list = new LinkedList();
    string userInput = "";
    while(userInput != "quit") {
        getline(std::cin, userInput);

        //PRINT FUNCTION
        if(userInput == "print"){
            list->print();
        }

        //DELETE FUNCTION
        else if(userInput.substr(0,6) == "delete"){ //FINISHED
            int lineNum = stoi(userInput.substr(7));
            list->deleteLine(lineNum);
        }

        //INSERTEND FUNCTION
        else if(userInput.substr(0,9) == "insertEnd"){
            size_t found = userInput.find("\"");
            size_t foundSecond = userInput.find("\"", found+1);
            if(found != string::npos && foundSecond != string::npos) {
                string insert = userInput.substr(found + 1, foundSecond-found-1);
                list->insertEnd(insert);
            }
        }

        //EDIT LINE FUNCTION
        else if(userInput.substr(0,4) == "edit"){
            stringstream sstream(stringstream::in | stringstream::out);
            sstream << userInput;

            string insert;
            int index;
            string line;

            sstream >> insert >> index;
            getline(sstream, line);

            size_t foundQuote = line.find("\"");
            size_t foundSecondQuote = line.find("\"", foundQuote+1);

            if(foundQuote != string::npos && foundSecondQuote != string::npos) {
                string insertText = line.substr(foundQuote + 1, foundSecondQuote-foundQuote-1);
                list->editLine(index, insertText);
            }

        }

        //INSERT FUNCTION
        else if(userInput.substr(0,6) == "insert"){ //FINISHED
            stringstream sstream(stringstream::in | stringstream::out);
            sstream << userInput;

            string insert;
            int index;
            string line;

            sstream >> insert >> index;
            getline(sstream, line);

            size_t foundQuote = line.find("\"");
            size_t foundSecondQuote = line.find("\"", foundQuote+1);


            if(foundQuote != string::npos && foundSecondQuote != string::npos) {
                string insertText = line.substr(foundQuote + 1, foundSecondQuote-foundQuote-1);
                list->insertIndex(index, insertText);
            }

        }

        //SEARCH FUNCTION
        else if(userInput.substr(0,6) == "search"){
            size_t found = userInput.find("\"");
            size_t foundSecond = userInput.find("\"", found+1);
            if(found != string::npos && foundSecond != string::npos) {
                string searchData = userInput.substr(found + 1, foundSecond-found-1);
                list->search(searchData);
            }
        }

        else if (userInput == "quit"){
            return 0;
        }
        //If user input does not match with any function
        else{
           // cout << "Invalid input. Please try again." << endl;
        }
    }

}
