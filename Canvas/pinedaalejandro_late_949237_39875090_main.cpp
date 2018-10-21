//
//  main.cpp
//  LinkedListLineEditor
//
//  Created by Alejandro Pineda on 9/18/18.
//  Copyright © 2018 Alejandro Pineda. All rights reserved.
//

#include <iostream>
#include <vector>

class Node{
public:
    Node *next;
    std:: string stringValue;
    Node();
};
Node::Node(){
    stringValue="";
}

class LinkedList{
private:
    Node * head;
    
public:
    void insertEnd(std::string text);
    void insert (int index ,std:: string text);
    void deleteLine (int index);
    void edit (int index, std:: string text);
    void print ();
    void search (std:: string text);
    void quit ();
    LinkedList();
};

LinkedList:: LinkedList(){
    head= new Node();
}
void LinkedList::insertEnd(std::string text){
    // if the head's stringValue still equals "" it means the linkedlist has not been initialized so I add it there
    // else I transverse through the linkedlist to the last element and add it right after.
    Node*current=head;
    if(head->stringValue == "")
       head->stringValue = text;
    else{
     Node* nodeToAdd= new Node();
    nodeToAdd->stringValue= text;
    while(current->next!=NULL)
        current= current->next;
    current->next=nodeToAdd;
    }
}
void LinkedList::insert (int index ,std:: string text){
    // inserts method at head if index =1 else tranverses to specified index and adds it there
    Node*current=head;
    Node* nodeToAdd= new Node();
    nodeToAdd->stringValue=text;
    int i =1;
    while (current != NULL) {
        if(index ==1){
            head = nodeToAdd;
        }
        if (i == index - 1) {
            Node *next = current->next;
            current->next = nodeToAdd;
            nodeToAdd->next = next ;
            break;
        }
        current = current->next;
        i++;
    }
}
void LinkedList:: deleteLine (int index){
     Node*current= head;
     //remlink will always be one node ahead of current in order to find theValue
     Node*remLink= current->next;
    //bool del will determine if anything has been erased
    bool del =false;
    int i =1;
    //if index is at the head delete the head
    if (i == index){
        head =current -> next;
        del =true;
    }
    //
    while (remLink->next!=NULL){
        //deletes in the middle
        if (i +1 == index){
            current->next=remLink->next;
            remLink=remLink->next;
            i++;
           del = true;
           break;
       }
        else
        {
            current=current-> next;
            remLink= current->next;
            i++;
        }
    }
    // if its at the last one delete else if its out of range just have remlink->next = NULL
        if (del==false && i+2>index)
            current->next=NULL;
        else
            if (del ==false)
                remLink->next=NULL;
    
}

void LinkedList:: edit (int index, std:: string text){
    //edits string by transversing to the specified inex and changing its stringValue
    Node * current = head;
    int i =1;
    while( current != NULL && i< index ){
        current= current->next;
        i++;
    }
        current->stringValue = text;
}

void LinkedList:: print (){
    //prints nodes with their indexes
    Node * current= head;
    int count =1;
    while(current!= NULL){
        std::cout<<count<<" "<<current->stringValue<<'\n';
        current=current->next;
        count ++;
    }
   // std::cout<<'\n';
}

void LinkedList:: search (std:: string text){
    //checks if the the text is contained in the head's strigValue or if it contained in any of the node's stringValue
    Node* current = head;
    int index=1;
    bool found = false;
    if (current->stringValue.find(text) != std::string::npos) {
        std::cout<<index<<" "<< head->stringValue<<'\n';
        found =true;
        current= current->next;
        index=index+1;
    }
    while(current!=NULL){
        if (current->stringValue.find(text) != std::string::npos) {
           std::cout<<index<<" "<< current->stringValue<< '\n';
            found =true;
        }
        current=current->next;
        index=index+1;
    }
    if(found== false)
        std::cout<< "not found"<<'\n';
}

int main(int argc, const char * argv[]) {
    LinkedList * a = new LinkedList();
    bool quitProgram = false;
   
    while(quitProgram == false){
        std::string allText;
        std::getline(std::cin, allText);
        //find first space and anything before is the command
    int index = allText.find(" ");
        if(allText=="print")
            a->print();
        if(index!=-1){
            std:: string command= allText.substr(0,index);
            // numcheck is the substring past the first "
            std::string numCheck=  allText.substr(index+1);
            std::string text ="";
            // for delete since its the only one with a number and no quotes I implemented a method to get the number by basically constructing and stirng of everything thats past command and is not a space
            if(command == "delete"){
                std:: string numFinal ="";
                int numDelete = allText.find(' ');
                numDelete++;
                while(allText[numDelete]!= ' ' && allText[numDelete]!= NULL){
                numFinal = numFinal + allText[numDelete];
                numDelete++;
                }
                a->deleteLine(stoi(numFinal));
            }
            // uses btext which the first quote and then atext which is the second quote and the text is what is in between
            int bText = allText.find('"');
            if(bText!=-1){
                std:: string inputText = allText.substr(bText+1);
                int aText = inputText.find('"');
                int textSize= allText.size();
                text = allText.substr(bText+1,aText);
            std:: string numBetween = allText.substr(index,bText-index);
            std::string num="";
      for(int i = 0; i< numBetween.size();i++){
         if(numBetween[i] != ' ')
             num = num + numBetween[i];
                   }
            //std::cout<<num<< "numfinal";
            if(command == "insertEnd")
                a->insertEnd(text);
            else
                if(command == "insert")
                    a->insert(stoi(num),text);
            else
                if(command == "edit")
                    a->edit(stoi(num), text);
            else
                if(command== "search")
                    a->search(text);
            std::cin.clear();
        }
        }
        if( allText == "quit"){
            quitProgram = true;
        }
    }
}
