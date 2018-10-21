//
//  main.cpp
//  Assignment1
//  Line editor using a Linked List.
//  Created by Vivian Garcia.
//  Stepik time complexity: 196.75

#include <iostream>
#include <string>


struct Node {
    std::string line = "";
    Node *next = NULL;
};

class List {
    
private:
    int size;
    Node *head;
    Node *tail;
public:
    void init() {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    void insertEnd();
    void insert();
    void remove();
    void edit();
    void print();
    void search();
};



int main(int argc, const char * argv[]) {
    
    //Declare string for command.
    std::string option;
    
    //Initialize linked list
    List list;
    list.init();
    
    
        while(option!="quit"){
            
            //Store user command.
            std::cin>>option;
            
            //Perform desired command.
            if(option == "insertEnd"){
                list.insertEnd();
            }
            else if(option == "insert"){
                list.insert();
            }
            else  if(option == "delete"){
                list.remove();
            }
            else  if(option == "edit"){
                list.edit();
            }
            else if(option == "print"){
                list.print();
            }
            else if(option == "search"){
                list.search();
            }
            else if(option == "quit"){
                break;
            }
        }
    return 0;
}




//Inserts line at the end of the linked list.
void List::insertEnd(){
    Node* newLine = new Node;
    std::string text = "";
    
    //Get line from user command.
    std::getline(std::cin, text);
    
    //Delete quotations
    text.erase(text.begin()+1);
    text.erase(text.begin() + text.length()-1);
    
    //Insert line into the new node.
    newLine->line = text;
    
    //Make new node the head and tail of list if it is the first item.
    if(head==NULL){
        head=newLine;
        tail=newLine;
        size++;
        return;
    }
    
    //Add node to the end of linked list.
    tail->next = newLine;
    tail = newLine;
    size++;
    return;
};


//Inserts new line at any index of linked list.
void List::insert(){
    Node* newLine = new Node;
    Node* current = head;
    std::string text = "";
    int index;
    
    //Get index from user command.
    std::cin>>index;
    //Get line from user command.
    std::getline(std::cin, text);
    
    //Delete quotations
    text.erase(text.begin()+1);
    text.erase(text.begin() + text.length()-1);
    
    //Insert line into the new node.
    newLine->line = text;
    
    //Return if index is out of bounds.
    if(index>size+1){
        return;
    }
    
    //Make new node the head and tail of list if it is the first item.
    if(size==0){
        head=newLine;
        tail=newLine;
        size++;
        return;
    }
    
    //Make new node the head of list if it will be the first item.
    if(index == 1){
        newLine->next = head;
        head = newLine;
        size++;
        return;
    }
    
    //Iterate through list until the index before desired insert.
    for(int i=0; i<index-2; i++){
        current = current->next;
    }
    
    //Insert node at index.
    newLine->next = current->next;
    current->next = newLine;
    
    //Update tail if node is inserted at the end.
    if(index == size+1){
        tail = newLine;
    }
    size++;
    
    return;
}

//Deletes node at desired index.
void List::remove(){
    int index;
    Node* current = head;
    
    //Get index from user command
    std::cin>>index;
    
    //Return if index out of bounds.
    if(index > size){
        return;
    }
    
    //Update head if deleted node is current head.
    if(index == 1){
        head = head->next;
        size--;
        return;
    }
    
    //Iterate through list until the index before desired deletion.
    for(int i=0; i<index-2; i++){
        current = head->next;
    }
    
    //Update tail if node removed is current tail.
    if(index == size){
        tail = current;
    }
    
    //Delete desired node, i.e. dereference it from list.
    current->next = current->next->next;
    
    size--;
    return;
}

//Edits line at desired index.
void List::edit(){
    int index;
    std::string text = "";
    Node* current = head;
    
    //Gets index from user command.
    std::cin>>index;
    //Gets line from user command.
    std::getline(std::cin, text);
    
    //Delete quotations
    text.erase(text.begin()+1);
    text.erase(text.begin() + text.length()-1);
    
    //Edit line at head if desired index.
    if(index == 1){
        head->line = text;
        return;
    }
    
    //Return if index out of bounds.
    else if(index>size){
        return;
    }
    
    //Iterate through list until the index before desired edit.
    for(int i=0; i<index-2; i++){
        current = head->next;
    }
    
    //Make edit.
    current->next->line = text;
    return;
}

//Prints list.
void List::print(){
    Node* current = head;
    
    //Iterates through list and prints each line.
    for(int i=0; i<size; i++){
        std::cout<< i+1 << current->line << "\n";
        current = current -> next;
    }
    
    return;
}

//Searches list for given text and prints the line it is found in.
void List::search(){
    Node* current = head;
    std::string text = "";
    bool isTrue = false;
    
    //Gets text to find from user command.
    std::getline(std::cin, text);
    
    //Delete quotations
    text.erase(text.begin()+1);
    text.erase(text.begin() + text.length()-1);
    
    //Iterates through list.
    int i = 0;
    while(current != NULL){
        i++;
        
        //Print line if text is found.
        if((current->line).find(text) != (current->line).npos){
            std::cout << i << current->line << "\n";
            isTrue = true;
        }
        current = current->next;
    }
    
    //Prints "not found" if text not in list.
    if (isTrue == false){
        std::cout << "not found\n";
    }
    
    return;
}

