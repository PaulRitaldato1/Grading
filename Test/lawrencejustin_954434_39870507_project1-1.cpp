//
//  main.cpp
//  Project1
//
//  Created by Justin Lawrence on 9/10/18.
//  Copyright © 2018 Justin Lawrence. All rights reserved.
//

#include <iostream>

struct node
{
    std::string line;
    node*next = NULL;
};

node* insertEnd(node* head, std::string text){
    node* addNode = new node();
    node* curr = head;
    addNode->line = text;
    if (head == NULL) { //if the first item is empty still, add the node to the head
        addNode->next = head;
        return addNode;
    }
    while (curr->next != NULL){ //otherwise, go though linked list and go until the next place is empty to find end of list
        //std::cout<<"\nwhile "+curr->line;
        curr = curr->next;
    }
    curr->next = addNode;
    return head;
}

node* insert(node* head, int index, std::string text){
    node* addNode = new node();
    addNode->line = text;
    node* curr = head;
    if (index == 1) { //head->line == "" //if you try to add to top of the list, insert it before the head
        addNode->next = head;
        //std::cout<<"adding at beginning";
        return addNode;
    }
    int i = 2;
    while (i<index){ //otherwise, check to see if it s in range by going through the list until you get to the index
        if (curr== NULL) {
         //   std::cout<<"ERROR! Out of range";
            return head;
        }
        curr = curr->next; //increment through list
        i++;
    }
    if (curr == NULL) {
       //  std::cout<<"ERROR! Out of range";
        return head;
    }
    node* next = curr->next; //add it to the list by making the order curr->add->next
    curr->next = addNode;
    addNode->next = next;
    return head;
}

node* deleteFrom(node* head, int index) {
    node* curr = head;
    if (head == NULL){ //check if head is empty
        return head;
    }
    node* tempNext = curr->next;
    if (index == 1) { //remove the first one?
        head = tempNext;
        return head;
    }
    int i = 2; //start with this part!
    while (i<index) {
        curr = curr->next;
        if (curr == NULL) {
      //      std::cout<<"ERROR! Out of range";
            return head;
        }
        tempNext = tempNext->next;
        i++;
    }
    if (tempNext == NULL) {
       // std::cout<<"ERROR! Out of range";
        return head;
    }
    curr->next = tempNext->next;
    return head;
}

node* edit(node* head, std::string text, int index) {
    node* curr = head;
    if (index == 1){
        head->line = text;
        //std::cout<<"edit 1";
        return head;
    }
    int i = 2;
    while (i < index) {
        curr = curr->next;
        if (curr == NULL) {
           // std::cout<<"ERROR! Out of range";
            return head;
        }
        i++;
    }
    if (curr->next == NULL) {
        // std::cout<<"ERROR! Out of range";
        return head;
    }
    curr->next->line = text; //edit by replacing what is the next at this line
    return head;
}

std::string search(node* head, std::string search){
    int count = 1;
    std::string output = "";
    while (head != NULL){
        if (head->line.find(search) != std::string::npos) { // head->line == search
            output += std::to_string(count)+" "+head->line+"\n";
            //return output;
        }
        head = head->next;
        count ++;
    }
    if (output == "") {
        output = "not found\n";
    }
    return output;
}

void print(node* head){
    int count = 1;
    while (head != NULL){ //goes through list and prints out line number and line
        std::cout<<std::to_string(count)+" "+head->line+"\n";
        head = head->next;
        count ++;
    }
}

int main() { //int argc, const char * argv[]
    // insert code here...
    node* head = new node();
    head = NULL;
    bool loopAgain = true;
    std::string userInput = "";
    std::string changeLine = "";
    int line = 0;
    std::string inputText = "";
    //std::cout << "Welcome. You can insertEnd, insert #, delete #, edit # 'text', search 'text', or print lines in the document";
    
    while (loopAgain) {
        inputText = "";
   // std::cout <<"\nPlease enter what you want to do\n";
   // std::getline(userInput, sizeof(userInput));
    std::getline(std::cin, userInput);  //get user input
    if (userInput.find(std::string("insertEnd")) != std::string::npos) {
        for (int i = 11; i<userInput.size()-1; i++){ //parse through to see what the line is
            inputText += userInput.at(i);
        }
        head = insertEnd(head, inputText);
    }
    
    else if (userInput.find(std::string("insert")) != std::string::npos){
        changeLine = userInput.at(7); //get the line to insert to
        line = atoi(changeLine.c_str());
        for (int i = 10; i<userInput.size()-1; i++){ //get the text to insert
            inputText += userInput.at(i);
        }
        head = insert(head, line, inputText);
    }
    else if (userInput.find(std::string("delete")) != std::string::npos) {
        changeLine = userInput.at(7); //get the line # to delete
        line = atoi(changeLine.c_str());
        head = deleteFrom(head, line);
    }
    else if (userInput.find(std::string("edit")) != std::string::npos){
        changeLine = userInput.at(5); //get line # to edit
        line = atoi(changeLine.c_str());
        for (int i = 8; i<userInput.size()-1; i++){ //parse through rest of user input to find text
            inputText += userInput.at(i);
        }
        head = edit(head, inputText, line);
    }
    else if (userInput == "print"){
        print(head);
    }
    else if (userInput.find(std::string("search")) != std::string::npos){
        std::string output = "";
        for (int i = 8; i<userInput.size()-1; i++){
            inputText += userInput.at(i);
        }
        output = search(head, inputText);
        std::cout<<output;
    }
    else if (userInput == "quit"){
        loopAgain = false;
    }
    else {
        //std::cout<<"invalid input, please try again";
        }
    }
    return 0;
}
