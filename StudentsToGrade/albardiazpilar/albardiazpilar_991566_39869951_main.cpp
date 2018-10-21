//
//  main.cpp
//  Project 1 COP3503
//
//  Created by Pilar Albar-Diaz on 9/19/18.
//  Copyright © 2018 Pilar Albar-Diaz. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

struct node {
    string data;
    node *next;
};

class linked_list{
private:
    node *head, *tail;
public:
    int count = 0;
    linked_list(){
        head = NULL;
        tail = NULL;
    }
   
    void insertEnd(string n){  //inserts line to end
        node*temp = new node;
        temp->data = n;
        temp->next = NULL;
        
        if(head==NULL){
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = tail->next;
        }
        count++;
    }
    
    void insertIndex(string data, int n){ //inserts line to nth index
        node* temp= new node();
        temp->data= data;
        temp->next= NULL;
        
        if ((head==NULL)&&(n==1)){
            head= temp;
            tail= temp;
            count++;
            return;
        }
        if(n>(count+1)){
            return;
        }
        if (n>count){
            count++;
            tail->next = temp;
            tail = temp;
            return;
        }
        if(n==1){
            count++;
            temp->next = head;
            head = temp;
            return;
        }
        
        node* temp2 = head;
        for(int i=0; i <n-2; i++){
            temp2= temp2->next;
        }
        
        temp->next = temp2->next;
        temp2->next= temp;
        count++;
    }
    
    
    void removeIndex(int n){     // removes line in nth index
        struct node* temp=head;
        if(n==1){
            head = temp->next;
            count--;
            free(temp);
            return;
        }
        if (n>count){
            return;
        }
        for(int i=0; i<n-2; i++){
            temp=temp->next;
        }
        struct node* temp2= temp->next;
        temp->next = temp2->next;
        count --;
        free(temp2);
    }
    
    
    void editLine(string data, int n){       //Edits nth line
        node*temp= new node();
        temp= head;
        int p = n+1;
        if (p==1){
            head->data= data;
        }
        else{
            for(int i=0; i<p-2; i++){
                temp=temp-> next;
            }
            temp->data=data;
        }
    }
    
    void searchLine(string str){           // Searches for phrase/word
        node* temp1 = new node();
        temp1 = head;
        bool yas_found = false;
        bool exists= false;
        int counter= 0;
       
        while (yas_found == false){
            string line = temp1->data;
            counter++;
            if (line.find(str) != std::string::npos) {
                cout<< counter << " ";
                cout<<temp1->data<<endl;
                exists= true;
            }
            if (temp1->next==NULL){
                yas_found = true;
            }
            temp1=temp1->next;
        }
        if(exists==false){
            cout<<"not found"<<endl;
        }
    }
  
    void print(node *head){         //Prints list
        int tracker= 0;
        node* current = new node();
        current = head;
        if (current == NULL){
            return;
        }
        while(current!= NULL){
            tracker++;
            cout << tracker<< " " <<current->data << endl;
            //cout << count+1<< endl;
           // print(head->next);
            current = current->next; 
        }
    }
    node* gethead(){
        return head;
    }
};
    
    int main(int argc, const char * argv[]) {
        
        linked_list editor;
        string input;
        string operation;
        string blop;
        
        while (true){
            int index=0;
            bool patty= false;
            int begin= 0;
            int end= 0;
           
            getline(cin, input);
            for(int i = 0; input[i] != ' '; i++){
                index++;
            }
            for(int i=0; i<input.length(); i++){
                if(input[i] =='"'){
                    begin = i;
                    patty = true;
                    break;
                }
            }
            for(int i=begin+1; i<input.length(); i++){
                if (input[i]== '"'){
                   end = i;
                    break;
                }
            }
            operation= input.substr(0,index);
            blop= input.substr(begin+1, end-begin-1);
            if (blop.length()>80){
                blop = blop.substr(0,79);
            }
            
            if(operation == "insertEnd"){
                editor.insertEnd(blop);}
            if(operation == "insert"){
                int i = input.at(7)-'0';
                editor.insertIndex(blop, i);
            }
            if(operation == "delete"){
                int i = input.at(7)-'0';
                editor.removeIndex(i);
            }
            if(operation == "edit"){
                int i = input.at(5)-'0';
                editor.editLine(blop, i);
            }
            if(operation == "print"){
                editor.print(editor.gethead());
            }
            if(operation == "search"){
                editor.searchLine(blop);
            }
            if(operation == "quit"){
                return 0;
            }
        }
    }




    


