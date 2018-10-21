//main.cpp
//Created by Fang Liu on 9/21/18
//Title: Project Assignment 1- Line Editor
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

struct Node
{
    string data;
    struct Node *next;
};

//add new node at the end
void insertEnd(Node** head_ref, string newText)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    Node *last = *head_ref;
    
    new_node->data  = newText;
    new_node->next = NULL;
    
    //check if the Linked List is empty, if true--> make the new node the head
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    
    while (last->next != NULL)
        last = last->next;
    
    last->next = new_node;
    return;
}

//create a new node at the current the curret position
void insert(Node *node, int position, string newText)
{
    int index = 1;
    while(node != NULL){
        if(index == position){
            Node* newNode =(Node*) malloc(sizeof(Node));
            
            newNode->data = newText; //the new node have the data
            newNode-> next = node->next;
            node->next = newNode;
            break;
        }
        else{
            index++;
            node = node-> next;
        }
    }
}

//delete the node at the specified line
void deleteNode(Node **head_ref, int lineNum)
{
    // check for empty list
    if (*head_ref == NULL)
        return;
    Node* temp = *head_ref;

    if (lineNum == 0)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
 
    for (int i=0; temp!=NULL && i<lineNum-1; i++)
        temp = temp->next;
    
    // if we are asked to delete a node that doesn't exist
    if (temp == NULL || temp->next == NULL)
        return;
     
    Node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

//replace the text at the given line
void edit(Node *node, int position, string newText)
{
    int index = 1;
    while(node != NULL)
    {
        if(index == position){
            node->data = newText;
            break;
        }
        else{
            index++;
            node = node->next;
        }
    }
}

//print the contents of linked list
void print(Node *node)
{
    int i = 1;
    while (node != NULL)
    {
        cout << i << " "<< (node->data)<<endl;
        node = node->next;
        i++;
    }
}

//search the linked list for the target string
void search(Node *node, string target)
{
    int i = 1;
    while(node != NULL)
    {
        if((node -> data).find(target) != string::npos){
            cout << i << " " << (node -> data) <<endl;
        }
        node = node->next;
        i++;
    }
}

int main()
{
    Node* head = NULL; //start off with a empty linked list

    int i;
    string line;
    string command = "";
    string text;
    
    cout<< "Enter input: "<<endl;
    
    //takes and parses user input; terminate program once "quit" is entered
    while (getline(cin, line))
    {
        if (line.find("insertEnd") != string::npos) {
            for(i = 11; i < line.size() -1; i++)
            {
                command += line[i];
            }
            insertEnd(&head, command);
            command = "";
        }
        
        else if(line.find("insert") != string::npos){
            command = line.substr(7);
            
            //find the given text to be inserted
            for(int i = 0; i< command.size(); i++){
                if(command[i] == '"'){
                    text = command.substr(i+1, command.size()-4);
                    break;
                }
            }
            
            //find the given index
            string delimiter = " ";
            command = command.substr(0, command.find(delimiter));
            int lineNumber = stoi(command);
            insert(head,lineNumber -1,text);
        }
        
        else if(line.find("delete") != string::npos){
            command = line.substr(7);
            int lineNumber = stoi(command); //the stoi function parses the string
            deleteNode(&head, lineNumber - 1);
        }
        
        else if(line.find("edit") != string::npos){
            command = line.substr(5);
            //find the replace text from the command
            for(i = 0; i< command.size(); i++){
                if(command[i] == '"'){
                    text = command.substr(i+1,command.size()-4);
                    break;
                }
            }
            //find the line number
            string delimiter = " ";
            command = command.substr(0, command.find(delimiter));
            int num = stoi(command);
            edit(head, num, text);
        }
        
        else if (line == "print"){
                 print(head);
                 
        }
        
        else if(line.find("search")!= string::npos){
            for (int i = 8; i< line.size()-1; i++)
            {
                command += line[i];
            }
            search(head, command);
            command = "";
            
        }
        
        else if (line == "quit") //break out of while loop and terminate the program
            break;
        
    }
    
    return 0;
}
