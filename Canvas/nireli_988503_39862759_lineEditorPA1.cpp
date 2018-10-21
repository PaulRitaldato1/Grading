//
//  lineEditorPA1.cpp
//  COP3530ProgrammingAssignment1Submission
//
//  Created by Eli Nir
//  Copyright © 2018 Eli Nir. All rights reserved.
//

#include <iostream>
#include <exception>
#include <limits>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstdlib>

class LinkedList{
private:
    
    struct node{
        std::string value;
        node* next;
        
    };
    node* head;
    node* tail;
    
public:
    
    LinkedList();
    void add(std::string text);
    void add(std::string text, int index);
    void edit(std::string text, int index);
    void deleteIndex(int index);
    void search(std::string text);
    void print();
};

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
}

void LinkedList::add(std::string text){
    node* newNode=new node;
    newNode->next=NULL;
    newNode->value=text;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }
}

void LinkedList::add(std::string text, int index){
    node* newNode=new node;
    newNode->value=text;
    int i=1;
    node* current=head;
    node* previous=head;
    while (current!=NULL){
        if(index == 1 && i == 1){
            newNode->next=head;
            head=newNode;
            return;
        }
        else if(i == index){
            previous->next=newNode;
            newNode->next=current;
            return;
        }
        previous=current;
        current=current->next;
        i++;
    }
    if (i == index)
        add(text);
    
}

void LinkedList::edit(std::string text, int index){
    int i=1;
    node* current=head;
    while (current!=NULL){
        if(i == index){
            current->value=text;
            return;
        }
        current=current->next;
        i++;
    }
    
}

void LinkedList::deleteIndex(int index){
    int i=1;
    node* current=head;
    node* previous=head;
    while (current != NULL){
        if (i==1 && index==1){
            if (head == tail)
                tail = NULL;
            head=head->next;
            return;
        }
        else if(i == index){
            previous->next = current->next;
            if (current->next == NULL){
                tail=previous;
            }
            return;
        }
        i++;
        previous = current;
        current = current->next;
    }
}

void LinkedList::search(std::string text){
    int i=1;
    node* current=head;
    bool found=false;
    while(current!=NULL){
        if (current->value.find(text) != std::string::npos){
            found=true;
            std::cout<<i<<" "<<current->value<<std::endl;
        }
        i++;
        current=current->next;
    }
    if(!found)
        std::cout<<"not found"<<std::endl;
}

void LinkedList::print(){
    int i=1;
    node* current=head;
    while(current!=NULL){
        std::cout<<i<<" "<<current->value<<std::endl;
        i++;
        current=current->next;
    }
}

void lineEditor(){
    LinkedList list;
    /*std::istringstream lineStream(line);
     std::vector<std::string> splitLine((std::istream_iterator<std::string>(lineStream)), std::istream_iterator<std::string>());*/
    std::string line;
    std::getline(std::cin, line);
    
    while(line != "quit"){
        std::string indicator = line.substr(0, line.find(" "));
        //line=line.substr(line.find(" ")+1);
        if(indicator ==  "insertEnd"){
            //std::cout<<"inserting end of "<<line.substr(line.find(" ")+1)<<std::endl;//dffgfdg
            if(line.find("\"") != std::string::npos){
                line=line.substr(line.find("\"")+1);
                if(line.find("\"") != std::string::npos){
                    line=line.substr(0, line.find("\""));
                    list.add(line);
                }
            }
            
            
        }
        else if(indicator == "search"){
            //std::cout<<"searching for "<<line.substr(line.find(" ")+1)<<std::endl;//dffgfdg
            if(line.find("\"") != std::string::npos){
                line=line.substr(line.find("\"")+1);
                if(line.find("\"") != std::string::npos){
                    line=line.substr(0, line.find("\""));
                    list.search(line);
                }
            }
        }
        else if(indicator == "edit"){
            //std::cout<<"editing "<<line.substr(line.find(" ")+3)<<" at position "<<atoi(line.substr(line.find(" ")+1, 1).c_str())<<std::endl;//dffgfdg
            int index=atoi(line.substr(line.find(" ")+1,1).c_str());
            if(line.find("\"") != std::string::npos){
                line=line.substr(line.find("\"")+1);
                if(line.find("\"") != std::string::npos){
                    line=line.substr(0, line.find("\""));
                    list.edit(line, index);
                }
            }
        }
        else if (indicator == "insert"){
            int index=atoi(line.substr(line.find(" ")+1,1).c_str());
            if(line.find("\"") != std::string::npos){
                line=line.substr(line.find("\"")+1);
                if(line.find("\"") != std::string::npos){
                    line=line.substr(0, line.find("\""));
                    //std::cout<<"inserting "<<line.substr(line.find(" ")+3)<<" at position "<<atoi(line.substr(line.find(" ")+1, 1).c_str())<<std::endl;//dffgfdg
                    list.add(line, index);
                }
            }
        }
        else if (indicator == "delete"){
            int index=atoi(line.substr(line.find(" ")+1,1).c_str());
            //std::cout<<"deleting "<<atoi(line.substr(line.find(" ")+1, 1).c_str())<<std::endl;//dffgfdg
            list.deleteIndex(index);
        }
        else if (indicator == "print"){
            //std::cout<<"printing..."<<std::endl;//dffgfdg
            list.print();
        }
        std::getline(std::cin, line);
    }
    
}

int main()
{
    lineEditor();
}


