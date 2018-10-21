//
//  main.cpp
//  LineEditor
//
//  Created by Isabella Castro on 9/20/18.
//  Copyright © 2018 Isabella Castro. All rights reserved.
//

#include <iostream>
using namespace std;

struct node
{
    string data;
    node *next;
};

class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }
    
    void createnode(string value)
    {
        node *temp=new node;
        temp->data=value;
        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;
            tail=temp;
            temp=NULL;
        }
        else
        {
            tail->next=temp;
            tail=temp;
        }
    }
    void display()
    {
        node *temp=new node;
        temp=head;
        while(temp!=NULL)
        {
            cout<<temp->data<<"\t";
            temp=temp->next;
        }
    }
    void insertPos(int pos, string value)
    {
        node *pre=new node;
        node *cur=new node;
        node *temp=new node;
        cur=head;
        for(int i=1;i<pos;i++)
        {
            pre=cur;
            cur=cur->next;
        }
        temp->data=value;
        pre->next=temp;
        temp->next=cur;
    }
    void deletePos(int pos)
    {
        node *current=new node;
        node *previous=new node;
        current=head;
        for(int i=1;i<pos;i++)
        {
            previous=current;
            current=current->next;
        }
        previous->next=current->next;
    }

};



int main()
{
    linked_list a;
    
    
    
    string y="insertEnd";
    string b="insert";
    string c="delete";
    string d="edit";
    string e="print";
    string f="search";
    string x="";
    getline(cin,x);
    cout<<x<<"\n"<<x.length();
    string n=x;
    while(x!="quit"){
        //insert
        if(x.find(b)!=std::string::npos){
            char par=34;
            int count=1;

            for(char& c : n) {

                if(c==par){
                    break;
                }
                
                count++;
            }

            string sub= n.substr(count);
            string temp="";
            for(char& c : sub) {
                
                if(c!=par){
                    temp=temp+c;
                }
            }
            sub=temp;
            //a.createnode(sub);
            
            a.display();
            //insertEnd
            if(x.find(y)!=std::string::npos){
                
                
            }
            else{
                int g=n.at(7);
                a.insertPos(g,sub);
            }
        }
        //delete
        if(x.find(c)!=std::string::npos){
            //string h=n.substr(7,9);
            int g=n.at(7);
            a.deletePos(g);
        }
        //edit
        if(x.find(d)!=std::string::npos){
            int g=n.at(7);
            
        }
        //print
        if(x.find(e)!=std::string::npos){
            int g=n.at(7);
            
        }
        //search
        if(x.find(f)!=std::string::npos){
            
        }
        
        
        cin>>x;
        
    }
    
    
    
}


