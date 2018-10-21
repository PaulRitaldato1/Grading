#ifndef LIST_H
#define LIST_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <valarray>

using namespace std;

class List{
    
private:

    struct node{
        string data;                                //stores the data of each node
        node* next;                                 //creates node pointer inside each node, points at another node in the list
    };
    typedef struct node* nodePtr;                   //typing nodePtr is the same as typing struct node*, creates node pointer
    
    nodePtr head; 
    nodePtr current; 
    nodePtr temp; 
    
public:
    
    List();                                         //tells program to set the initial values such as head, current, temp
    void insertEnd(string addData);                 //"insertEnd" "insert 3"
    void insert(int index, string addData);         
    void DeleteNode(int delData);                   //"delete 3"
    void EditNode(int index, string Data);          //"edit 3"
    void SearchList(string Data);                   //prints entire documents with line numbers 
    void PrintList();  
    
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
#endif 

string format(string data);

int main(int argc, char** argv) {
    
    List myList;
    
    string blah;  
    string text;                                    //put this reading input in loop until they hit quit
    int index;
    string insertEnd = "insertEnd";
    string quit = "quit";                           //stores user input in blah
    
    do{

    cin >> blah;
    if (blah == "insertEnd"){
        getline(cin, text);
        myList.insertEnd(format(text));
    }
    if (blah == "delete"){
        cin >> index;
        myList.DeleteNode(index);
    }
    if (blah == "insert"){
        cin >> index;
        getline(cin, text);
        myList.insert(index, format(text));
    }
    if (blah == "edit"){
        cin >> index;
        getline(cin, text);
        myList.EditNode(index, format(text));
    }
    if (blah == "search"){
        getline(cin, text);
        myList.SearchList(format(text));
    }
    if (blah == "print"){
        myList.PrintList();
    }


    }while (blah != "quit");

}


List::List(){                                                   //this is made for the constructor  //creating a List object in the main.cpp file makes all of these NULL
    
    head = NULL;
    current = NULL;
    temp = NULL;
    
}

void List::insertEnd(string addData){                           //this defines the insertEnd function
    
    nodePtr n = new node;                                       //creates node pointer called 'n' point to a new node
    n ->next = NULL;                                            //basically makes this the END of the list //finds the node that 'n' is pointing to and makes it point to NULL
    n ->data = addData; 
    
    if (head != NULL){
        current = head;                                         //makes the current pointer point to the front of the list 
        while (current ->next != NULL){                         //while not at the end of list
            current = current ->next;                           //advances the current pointer to the end of the list
        }
        current ->next = n;                                     //points to new node 'n' with data
    }
    else{                                                       //if there is no present list
        head  = n;
    } 
    
}

void List::insert(int index, string addData){
    nodePtr temp = new node();
    temp ->data = addData;
    current = head;

    if (index == 1){
        temp -> next = head; 
        head = temp; 
        return;
    }
    nodePtr prev = head; 
    for(int i = 1; i < index; i++){
        if (current == NULL) return;
        prev = current;                                         
        current = current ->next; 
    }
    temp ->next = current;
    prev ->next = temp;
}

void List::DeleteNode(int delData){

    temp = head; 
    current = head;

    if (delData == 1){
         head = head ->next;

         temp = NULL;
         return;
    }

    for (int i=1; i < delData; i++){
    if (current == NULL) return;
    temp = current;                                         
    current = current ->next; 
    }

    if (current == NULL) return;
    temp->next = temp->next->next;
    delete(current);
 
}

void List::SearchList(string data){


    temp = head;
    bool notfound = true; 
    int i = 1;
    while(temp != NULL){
        if(temp->data.find(data)!=string::npos){
            cout << i << " " << temp->data << endl; 
            notfound = false; 
        }
        temp = temp->next;
        i ++;  

    }
    if (notfound){
        cout << "not found" << endl;
    }




}

void List::EditNode(int index, string data){

    temp = head;
    for (int i = 1; i < index; i++){
        if (temp == NULL)return;
        temp = temp->next;
    }
    temp->data = data;




}

void List::PrintList(){                                         
    current = head; 
    int i = 1;
    while (current != NULL){
        cout << i << " " << current->data << endl; 
        current = current ->next;
        i ++;  
    }
    

}

string format(string data){
    while( isspace(data[0]))data = data.substr(1,data.size()-1);
    data = data.substr(1,data.size()-1);
    data.pop_back();

    return data;

}
