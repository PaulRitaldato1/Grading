//
//  main.cpp
//  PA1DS
//
//  Created by Tikahari Khanal on 9/6/18.
//  Copyright © 2018 Tikahari Khanal. All rights reserved.
//

#include <iostream>
#include <string>

template <typename T>
class Line{
public:
    T line;
    Line<T>* next;
    Line<T>(T line){
        this->line=line;
        //otherwise next would not be intitialized
        this->next=NULL;
    }
    Line<T>(){
        this->next=NULL;
    }
};

template <typename T>

class Document{
public:
    Line<T>* start;
    int size;
    void insert(T, int lineNumber);
    void insertEnd(T l);
    void deleteLine(int lineNumber);
    void edit(T l, int lineNumber);
    void search(T l);
    void print();
    Document<T>(){
        this->start=NULL;
        this->size=0;
    }
};


template<typename T>
void Document<T>::insert(T l, int lineNumber){
    Line<T>* curr = this->start;
    //lineNumber must be in range
    if(lineNumber < 1 || lineNumber > size +1){
        return;
    }
    int index = 1;
    //if inserting at position 1, start of list must be changed
    if (lineNumber ==1){
        Line<T>* ins=new Line<T>(l);
        ins->next=this->start;
        this->start=ins;
        this->size=this->size+1;
        return;
    }
    for(index =1; curr != NULL && index <lineNumber-1; index++){
        curr = curr->next;
        
    }
    Line<T>* ins = new Line<T>(l);
    //next of inserted is next of original, next of original is inserted
    ins->next = curr->next;
    curr->next=ins;
    this->size=this->size+1;
}

template<typename T>
void Document<T>::insertEnd(T l){
    Line<T>* temp= this->start;
    int lineNumber=1;
    //add to begin if list empty
    if(temp == NULL){
        start=new Line<T>(l);
        this->size= this->size+1;
        return;
    }
    lineNumber++;
    //otherwise, add to next empty spot
    while(temp->next!=NULL){
        lineNumber++;
        temp=temp->next;
    }
    temp->next=new Line<T>(l);
    this->size=this->size+1;
}

template<typename T>
void Document<T>::deleteLine(int lineNumber){
    Line<T>* curr = this->start;
    //lineNumber must be in range
    if(lineNumber < 1 || lineNumber > size){
        return;
    }
    int index = 1;
    //if deleting at position 1, start of list must be changed
    if (lineNumber ==1){
        this->start=this->start->next;
        this->size=this->size-1;
        return;
    }
    for(index =1; curr != NULL && index <lineNumber-1; index++){
        curr = curr->next;
        
    }
    curr->next=curr->next->next;
    this->size=this->size-1;
}

template<typename T>
void Document<T>::edit(T l, int lineNumber){
    Line<T>* curr = this->start;
    //lineNumber must be in range
    if(lineNumber < 1 || lineNumber > size){
        return;
    }
    int index = 1;
    //if editing at position 1, start of list must be changed
    if (lineNumber ==1){
        this->start->line=l;
        return;
    }
    //different bound for for loop, want to change the element in list, not its relationship with previous and following elements
    for(index =1; curr != NULL && index <lineNumber; index++){
        curr = curr->next;
    }
    curr->line=l;
}

template<typename T>
void Document<T>::search(T l){
    Line<T>* curr = this->start;
    bool found =false;
    //different bound for for loop, want to change the element in list, not its relationship with previous and following elements
    int index =1;
    while(curr != NULL){
        std::string::size_type pos= curr->line.find(l);
        if (pos != std::string::npos){
            std::cout<<index<<" "<<curr->line<<std::endl;
            found =true;
        }
        curr = curr->next;
        index++;
    }
    if (!found){
        std::cout<<"not found"<<std::endl;
    }
}

template<typename T>
void Document<T>::print(){
    Line<T>* curr = this->start;
    int index =1;
    while(curr!=NULL){
        std::cout<<index<<" "<<curr->line<<std::endl;
        curr=curr->next;
        index++;
    }
}

void parse(std::string* command, std::string* text){
    std::string line;
    bool quote =false;
    std::getline(std::cin, line);
    for(int i = 0; i < line.length(); i++){
        if(line[i] != '"' && !quote){
            while(line[i] != '"' && i< line.length()){
                //change command
                *command+=line[i];
                i++;
            }
            i=i-1;
            quote = true;
        }
        
        if(line[i] == '"'){
            i++;
            while(line[i] != '"' && i< line.length()){
                //change text
                *text+=line[i];
                i++;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    Document<std::string>* doc = new Document<std::string>();
    
    std::string command;
    std::string text;
    int lineNumber;
    while(true){
        command="";
        text="";
        lineNumber=-1;
        parse(&command, &text);
        if(command.substr(0,9) == "insertEnd"){
            doc->insertEnd(text);
        }
        
        else if (command.substr(0,7) == "insert "){
            lineNumber=atoi(command.substr(7,command.length()).c_str());
            doc->insert(text, lineNumber);
        }
        
        else if(command.substr(0, 5)== "edit "){
            lineNumber=atoi(command.substr(5,command.length()).c_str());
            
            doc->edit(text, lineNumber);
        }
        
        else if(command.substr(0, 7)=="delete "){
            lineNumber=atoi(command.substr(7,command.length()).c_str());
            doc->deleteLine(lineNumber);
        }
        
        else if(command.substr(0, 7) == "search "){
            doc->search(text);
        }
        
        else if(command == "print"){
            doc->print();
        }
        else if (command == "quit"){
            exit(0);
        }
    }
    return 0;
}

