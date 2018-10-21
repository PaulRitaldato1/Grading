// 80 char max
// include index when printing
//
//
//  main.cpp
//  Line Editor
//
//  Created by Oliver Hodge on 9/19/18.
//  Copyright © 2018 Oliver Hodge. All rights reserved.
//
#include <iostream>
#include <string>
struct node{
    std::string data;
    node *next;
};
class linked_list{
private:
    node *head, *tail;
    int counter = 0;
public:
    linked_list(){
        head = NULL;
        tail = NULL;
    }
    //adds node to end
    void addNodeEnd(std::string n){
        node* temp = new node;
        temp->data = n;
        temp->next = NULL;
        if(head==NULL){
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
        counter++;
    }
    // adds node to index n
    void addIndex(std::string data, int n){
        node* temp= new node();
        temp->data= data;
        temp->next= NULL;
        if((n==1)&&(head==NULL)){
            head = temp;
            tail = temp;
            counter++;
            return;
        }
        if(n>(counter+1)){
            return;
        }
        if(n>counter){
            counter++;
            tail->next = temp;
            tail = temp;
            return;
        }
        if (n==1){
            counter++;
            temp->next = head;
            head= temp;
            return;
        }
        node* temp2 = head;
        for(int i=0; i <n-2; i++){
            temp2= temp2->next;
        }
        temp->next = temp2->next;
        temp2->next= temp;
        counter++;
    }
    void deleteNth(int n){
        struct node* temp=head;
        if(n==1){
            head = temp->next;
            free(temp);
            counter--;
            return;
        }
        if(n>counter){
            return;
        }
        int i;
        for(i=0; i<n-2; i++){
            temp=temp->next;
        }
        struct node* temp2= temp->next;
        temp->next = temp2->next;
        free(temp2);
        counter--;
    }
    static void display(node *head){
        node* temp = new node();
        temp = head;
        int k = 0;
        if (temp == NULL){
            return;
        }
        while(temp != NULL){
            k++;
            std::cout<< k << " " << temp->data << std::endl;
            temp = temp->next;
        }
    }
    void edit(std::string data, int k){
        node* temp = new node();
        temp = head;
        int n = k+1;
        if (n==1){
            head->data = data;
        }
        else{
            for(int i=0; i < n-2; i++){
                temp= temp->next;
            }
            temp->data = data;
        }
    }
    void search(std::string str){
        node* temmp = new node();
        temmp = head;
        int line_num = 0;
        bool found_str = false;
        bool any_match = false;
        while (found_str == false){
            line_num++;
            std::string longshit = temmp->data;
            if (longshit.find(str) != std::string::npos) {
                std::cout<<line_num<<" ";
                std::cout<<temmp->data<<std::endl;
                any_match = true;
            }
            if(temmp->next == NULL){
                found_str = true;
            }
            temmp = temmp->next;
        }
        if(any_match==false){std::cout<<"not found"<<std::endl;}
    }
    node* gethead(){
        return head;
    }
};
int main(int argc, char const *argv[]){
    linked_list* list = new linked_list();
    bool restart = true;
    int input_num = 0;
    while(true){
    while (restart == true){
        std::string option_command;
        //std::string text;
        std::string option_string;
        
        bool quote = false;
        std::cin>>option_command;
        if(option_command=="insert"||option_command=="delete"||option_command=="edit"){
            std::cin>>input_num;
        }
        getline(std::cin, option_string);
        int last_char;
        last_char = option_string.size()-1;
        if(option_string[1]=='"' && option_string[last_char]=='"'){
            quote=true;
        }
        if(quote==true){
            option_string=option_string.substr(2,last_char-2);
            //std::cout<<option_string.size()<<std::endl;
            if (option_string.size()>80){
                restart = false;
            }
        }
        if(restart==true){
            
            if(option_command == "insertEnd"){
                list->addNodeEnd(option_string);
            }
            if(option_command == "insert"){
                list->addIndex(option_string, input_num);
                
            }
            if(option_command == "delete"){
                
                list->deleteNth(input_num);
            }
            if(option_command == "edit"){
                
                list->edit(option_string, input_num);
                
            }
            if(option_command == "print"){
                list->display(list->gethead());
            }
            if(option_command == "search"){
                list->search(option_string);
            }
            if(option_command == "quit"){
                return 0;
            }
        }
    }
    restart = true;
    }
}
