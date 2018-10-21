//
//  main.cpp
//  PA1
//
//  Created by Jason Tufenkdjian on 9/13/18.
//  Copyright © 2018 Jason Tufenkdjian. All rights reserved.
//

#include <iostream>
using namespace std;
string mainMenu();


//my linked list implementation here
struct Line{
    string contents; // data of the node
    Line* next = NULL; // pointer to the next node
};

//my line editor (a linked list of sorts) implementation here
class LineEditor{
private:
    Line* head; // the head of the list
    bool exists(int at){ // simply returns whether the node exists at the position at
        Line* temp = head;
        bool rs = true;
        for(int i = 0; i < at; i ++){
            if(temp==NULL){
                rs = false;
                break;
            }
            temp = temp->next;
        }
        return rs;
    };
    
public:
    LineEditor(){ // constructor
        head = NULL;
    }
    
    // works insertEnd functionality
    int insertEnd(string s){
        if(s.size()>80){
            return -1; // error code for if the program wants to handle a user input error
        }else{
            Line* newLine = new Line(); // create a new line with contents s
            newLine->contents = s;
            Line* temp = head; // temp node for traversing the list;
            
            if(head == NULL){
                head = newLine; // if the list is empty then just set head to the new node
            }else{ // traverse through the list
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = newLine; // add the new node at the end
            }
            return 0;
        }
        
        
    };
    
    // works deleteLine functionality
    int deleteLine(int at){
        int rs = 0;
        
        if(exists(at)){ // if the node exists to begin with
            if(at==0){ // if the node is at the beginning of the list then just delete the head and set the new head to be the next of the current head
                Line* temp = head;
                head = head->next;
                temp = NULL;
            }else{ // else traverse through the list
                Line* prev = head;
                Line* curr = head->next;
                
                for(int i = 0; i < at - 1; i ++){ // track both current and previous nodes
                    prev = prev->next;
                    curr = curr->next;
                }
                if(curr == NULL){
                    
                }else if(curr->next==NULL){ // if the curr->next is null then delete the current node to make prev the end of the list (no need to reconnect the list)
                    prev->next = NULL;
                    curr = NULL;
                }else{ // else change the pointer of prev next to be current next and delete current
                    prev->next = curr->next;
                    curr = NULL;
                }
                
            }
        }else{
            rs = -1; // error code meant for troubleshooting
        }
        return rs;
    };
    
    // works insertLine functionality
    int insertLine(int at, string s){
        int rs = 0;
        Line* newLine = new Line(); // create a new line with contents s
        newLine->contents = s;
        
        if(s.length()>80){
            // string is too long, error code
            return rs = -1;
        }else{
            if(at == 0){ // if inserting at the beginning of the list then simply make newline's referenece to next head, and make the head newline
                newLine->next = head;
                head = newLine;
                return 0;
            }else{ // else traverse through the list keeping track as to whether it is out of bounds
                int index = 1;
                Line* curr = head;
                bool insert = false;
                
                while(curr!=NULL){
                    if(index==at){
                        insert = true;
                        break;
                    }
                    curr = curr->next;
                    index++;
                }
                
                if(insert){
                    if(curr==NULL){
                        
                    }else if(curr->next==NULL){ // inserting at the end of the list
                        curr->next = newLine;
                    }else{ // inserting in the middle of the list
                        newLine->next = curr->next;
                        curr->next = newLine;
                    }
                }
            }
        }
        return rs;
    };
    
    // works edit functionality
    int edit(int at, string s){
        int rs = 0;
        
        if(!exists(at)){ // line does not exist
            rs = -1; // error code
        }else if(s.length()>80){ // line is too long for this doc
            rs = -2; // error code
        }else{ // traverse through the list and change contents to the provided string s
            Line* temp = head;
            for(int i = 0 ; i < at ; i ++ ){
                temp = temp->next;
            }
            if(temp!=NULL){
                temp->contents = s;
            }
            
        }
        
        return rs;
    };
    
    // works string search functionality
    bool search(string s){
        int lineNo = 1; // keep track of line number
        Line* temp = head; // temp node for head
        bool found = false; // boolean as to whether the function has found the text
        
        while(temp!=NULL){ // while the program is still traversing through the list
            size_t foundSize = temp->contents.find(s);
            if(foundSize!=string::npos){ // if the string is found then print and set the boolean found equal to true
                found = true;
                cout << lineNo << " " << temp->contents << endl;
            }
            temp = temp->next;
            lineNo++;
        }
        return found;
    }
    
    // works print functionality
    void print(){
        int line = 1; // int to keep track of line number
        Line* temp = head;
        while(temp!=NULL){ // while still traversing through the list (temp == null means you have finished traversing)
            if(temp->next == NULL){
                cout << line << " " << temp->contents; // if not at the end of the list, just print contents of the line
            }else{
                cout << line << " " << temp->contents << endl; // else, also put an endl;
            }
            temp = temp->next; // iterate through
            line++; // increment the int line
        }
        cout << endl;
    };
    
};

int main(int argc, const char * argv[]) {
    
    LineEditor lineEd = LineEditor(); // lineEd will be our linked list wrapper
    bool quit = false; // self-explanatory, for the while loop that runs while not quit is true
    string input; // string for the input
    cin.clear(); // clear cin for good measure
    
    while(!quit){
        string input = mainMenu(); // returns the next line, functionality can be added later to display a main menu
        char delimeter = ' '; // the delimeter for the command
        string command = input.substr(0,input.find_first_of(delimeter)); // parse out the string based on where the first space is to find the command
        
        if(command=="print"){ // if command = print
            lineEd.print(); // print
        }else if(command=="insertEnd"){ // if command = insertEnd
            string toInput = input.substr(input.find_first_of('"')+1,(input.rfind("\"")-input.find_first_of("\"")-1));
            lineEd.insertEnd(toInput); // insert at the end
        }else if(command=="insert"){ // if command = insert
            string toInput = input.substr(input.find_first_of('"')+1,(input.rfind("\"")-input.find_first_of("\"")-1));
            input = input.substr(input.find_first_of(' '));
            input = input.substr(0,input.find(" \""));
            int at = atoi(input.c_str());
            lineEd.insertLine(at-1, toInput); // insert at the specified line (this program indexes starting at zero)
        }else if(command=="search"){ // if command = search
            string searchString = input.substr(input.find_first_of('"')+1,(input.rfind("\"")-input.find_first_of("\"")-1));
            if(!lineEd.search(searchString)){ // search the string, if not found
                cout << "not found" << endl; // print out 'not found'
            };
        }else if(command=="edit"){ // if command = edit
            string toInput = input.substr(input.find_first_of('"')+1,(input.rfind("\"")-input.find_first_of("\"")-1));
            int at  = stoi(input.substr(input.find_first_of(" "),(input.find_first_of(("\"")-1))));
            lineEd.edit(at - 1,toInput); // edit at the position given -1 (this program indexes starting at zero) with the string toInput
        }else if(command == "delete"){
            try{
                int toDel = stoi(input.substr(input.find_first_of(" "),input.length()));
                lineEd.deleteLine(toDel-1);
            }catch(exception e){
                
            }
            
        }else if(command=="quit"){ // if command = quit
            quit = true; // reset the boolean and break out of the loop anyways?
            break;
        }else{ // if an improper input is given
            quit = true; // just exit out of the program by resetting quit to true
        }
    }
    return 0;
}

string mainMenu(){ // takes in the from cin and returns it, exits the program if this fails to happen for some reason
    string input;
    if(getline(cin,input)){
    }else{
        input =  "quit";
    }
    cin.clear();
    return input;
};





