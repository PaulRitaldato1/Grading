//
//  main.cpp
//  LinkedList Project
//
//  Created by Andres Pineda on 9/18/18.
//  Copyright © 2018 Andres Pineda. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
class Node{
public:
    Node *next;
    std::string text;
    Node();
};
class LinkedList{
private:
    Node * head;
public:
    void insertEnd(std::string text);//adds line to the end of the document
    void insert(int index, std::string text);//inserts line at the end of the document
    void delet(int index);//deletes line at given index
    void edit(int index, std::string text);//edits line at given index
    void print();//prints document
    void search(std::string text);//prints the index of the document where that line is found
    Node* getHead(){
        return head;
    }
    LinkedList();
};
//Node constructor
Node::Node(){
    next=NULL;
    text="";
}
// Constructor for linkedList with a size and command line argument as paramete
LinkedList::LinkedList(){
    head= new Node();

}
void LinkedList :: insertEnd(std::string text){
    if(head->next==NULL && head->text == ""){
        head->text=text;
    }
    else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        Node *inser = new Node;
        current->next = inser;
        inser->text = text;
    }
}
void LinkedList :: insert(int index, std::string text){
    int i=1;
    Node*current=head;
    Node* addNode= new Node();
    addNode->text=text;
        while (current != NULL) {
            if (i == index - 1) {
                Node *ne = current->next;
                current->next = addNode;
                addNode->next = ne;
                break;
            }
            if(index ==1){
                head = addNode;
            }
            current = current->next;
            i++;
        }
    }
void LinkedList :: delet(int index){
   Node*current=head;
    Node*temp=current->next;
    int i=2;
    bool deleted =false;
if(index==1){
    head=current->next;
}
    while(temp->next!=NULL){
        if(i==index){
            current->next=temp->next;
            temp=temp->next;
            deleted =true;
            break;
        }
        else{
            current=current->next;
            temp=temp->next;
            i++;
        }
    }
    if(i==index && deleted ==false){
        current->next =NULL;
    }
}
void LinkedList :: edit(int index, std::string text){
    int i=1;
    Node*current=head;
    while(current->next!=NULL){
        if(i==index){
            current->text=text;
        }
        current=current->next;
        i++;
    }
    if(i==index){
        current->text=text;
    }
}
void LinkedList ::print(){
    Node*current =head;
    int lineCounter=1;
    while (current->next!=NULL){
        std::cout<< lineCounter<<" "<<current->text;
        std::cout<<'\n';
        lineCounter++;
        current=current->next;
    }
    std::cout<< lineCounter<<" "<<current->text;
    std:: cout<<'\n';
}
void LinkedList :: search(std::string text){
    int i=1;
    Node*current=head;
    bool found=false;

    while(current->next!=NULL){
        if(current->text.find(text) != std::string::npos){
            std::cout<< i<<" "<<current->text<<'\n';
            found=true;
        }
        current=current->next;
        i++;
    }

    if(current->text.find(text) != std::string::npos){
        std::cout<< i<<" "<<current->text;
        found = true;
        current = current -> next;
        i++;
    }

    if(found==false){
        std::cout<<"not found";
    }
}
int main(int argc, const char * argv[]) {
    LinkedList *text= new LinkedList();
    bool gameOver=false;
    while(gameOver==false){
        std::string input;
        std::getline(std::cin, input);
        int i=0;
        std:: string command;
        while(input[i]!=' '&& input[i]!=NULL){
            command=command+input[i];
            i++;
        }
        if(command=="quit"||command=="insertEnd"||command=="insert"||command=="delete"||command=="search"||command=="edit"||command=="print") {
            if (command == "quit") {
                gameOver = true;
            }
            if (command == "insertEnd") {
                std::string lin;
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == '"') {
                        ind++;
                        while (input[ind] != '"') {
                            lin = lin + input[ind];
                            ind++;
                        }
                        ind = input.length();
                    }

                }
                text->insertEnd(lin);
            }
            if (command == "insert") {
                std::string num="";
                std::string lin;
                int pos;
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == ' ') {
                        ind++;
                        while (input[ind] != ' ' && input[ind] != NULL) {
                            num = num + input[ind];
                            ind++;
                        }
                        if (num.length() > 1) {
                            pos = stoi(num);
                        }
                        if (num.length() == 1) {
                            pos = stoi(num);
                        }
                      break;
                    }
                }
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == '"') {
                        ind++;
                        while (input[ind] != '"') {
                            lin = lin + input[ind];
                            ind++;
                        }
                        break;
                    }

                }
                if (pos != NULL)
                    text->insert(pos, lin);
            }
            if (command == "delete") {
                std::string num="";
                int pos;
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == ' ') {
                        ind++;
                        while (input[ind] != ' ' && input[ind] != NULL) {
                            num = num + input[ind];
                            ind++;
                        }
                        if (num.length() > 1) {
                            pos = stoi(num);
                        }
                        if (num.length() == 1) {
                            pos = stoi(num);
                        }
                        break;
                    }
                }
                text->delet(pos);
            }
            if (command == "print") {
                text->print();
            }
            if (command == "edit") {
                std::string num="";
                std::string lin;
                int pos;
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == ' ') {
                        ind++;
                        while (input[ind] != ' ' && input[ind] != NULL) {
                            num = num + input[ind];
                            ind++;
                        }
                        if (num.length() > 1) {
                            pos = stoi(num);
                        }
                        if (num.length() == 1) {
                            pos = stoi(num);
                        }
                        break;
                    }
                }
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == '"') {
                        ind++;
                        while (input[ind] != '"') {
                            lin = lin + input[ind];
                            ind++;
                        }
                        break;
                    }

                }
                if (pos != NULL)
                    text->edit(pos, lin);
            }
            if (command == "search") {
                std::string lin;
                for (int ind = 0; ind < input.length(); ind++) {
                    if (input[ind] == '"') {
                        ind++;
                        while (input[ind] != '"') {
                            lin = lin + input[ind];
                            ind++;
                        }
                        ind = input.length();
                    }

                }
                text->search(lin);
            }
        }
        else{
            std:: cin.clear();
        }
    }
}
