// Data Structures, project 1
//1500-6494

#include <iostream>
#include <string>
using namespace std;

struct Node { //create node class
public:
    string str;
    Node* next = NULL;
};

class linkedList { //create linkedList class
public:
    Node* head; //initialize head and tail
    Node* tail;

    linkedList() {
        head = NULL;
        tail = NULL;
    }

    void createNode(string newStr) { //creates new node, adds to end
        Node* newNode = new Node;
        newNode->str = newStr;
        newNode->next = NULL;
        if (head == NULL) { //if there is no head, make one
            head = newNode;
            tail = newNode;
        }
        else if(head != NULL && tail != NULL) { //insert at tail end
            tail->next = newNode;
            tail = tail->next;
        }
    }

    void insertMe(int index, string ins){ //inserts node anywhere
        Node* addNode = new Node;
        addNode->str = ins;
        if(index == 1){ //if we want it to be inserted at the first spot
            addNode->next = head;
            head = addNode;
        } else if(validIndex(index)){ //check to make sure index is in bounds
            int count = 1;
            Node* curr = head;
            while(count < index - 1){ //runs through list until we get to correct spot
                curr = curr->next;
                count++;
            }
            Node* nextNode = curr->next; //when hits right spot, places node
            curr->next = addNode;
            addNode->next = nextNode;
        }

    }

    void deleteMe(int delIndex) { //delete node

            if (head == NULL) //does nothing if there is no node
                return;
            Node *temp = head;
            if (delIndex == 1){ //deletes first node
                head = temp->next;
                free(temp);
                return;
            }
            for (int i = 1; temp != NULL && i < delIndex - 1; i++) //iterates until correct node
                temp = temp->next;
            if (temp == NULL || temp->next == NULL)
                return;
            Node *next = temp->next->next;
            free(temp->next);
            temp->next = next;
        }

    void editMe(int line, string edit) { //edits any node already in list
        Node *curr = head;
        int i = 0;
        int valid = line - 1;
        if (line <= listSize()) { //makes sure list has node at given line
            if (line == 1) {
                head->str = edit;
            } else {
                while(line > 1) { //drives list to correct node

                    curr = curr->next;
                    line--;
                }
                curr->str = edit;
            }
        }
    }



    void searchMe(string findMe) {//it's like an amber alert for nodes
        Node* curr = head;
        bool search = false;
        int index = 1;

        while(curr){
            if(curr->str.find(findMe) != std::string::npos) { //finds out if string held in node contains substring we're looking for
                std::cout << index << " " << curr->str << endl;
                search = true;
            }
            index++; //iterates
            curr = curr->next;

        }

        if(search == false) {  //displays not found if we didn't find it
            cout << "not found" << endl;
        }
    }

    void printMe() { //SHOW ME WHAT YOU GOT
        int index = 1;
        Node* curr = head;
        while (curr) {
            cout << index << " " << curr->str << endl;
            index++;
            curr = curr->next;
        }

    }

    int listSize() {
        Node* curr = head;
        int length = 0;
        while (curr) {
            curr = curr->next;
            length++;
        }
        return length;
    }
    bool validIndex(int index){ //method used in several other methods to make sure we're not trying to go out of the scoop
        Node* curr = head;
        int length = 0;
        while(curr){
            curr = curr -> next;
            length++;
        }
        if(length+1 >= index) {
            return true;
        } else {
            return false;
        }
    }

};


int main() {

   bool run = true; //we use this to keep inside the while loop until the user prompts quit
   int index = 0; //initializing variables
   string newStr;
   string command;
   linkedList* newList = new linkedList();

   while(run){
       cin >> command; //user inputs full command,

       if(command == "insertEnd"){
           getline(cin, newStr); //machine reads input after the command
           newStr.erase(0,1); //gets rid of space
           if(newStr.at(0) == '"' && newStr.at(newStr.length()-1) == '"') { //makes sure we're in quotes, then deletes quotes
               newStr.erase(0, 1);
               newStr.erase(newStr.length() - 1);
               newList->createNode(newStr); //appends node
           } else {
               continue;
               }

       } else if (command == "insert"){ //inserts at any given node
           cin >> index ; //gains input of where we're going in list
           getline(cin, newStr);  //see insertEnd comments
           newStr.erase(0,1);
           if(newStr.at(0) == '"' && newStr.at(newStr.length()-1) == '"') {
               newStr.erase(0, 1);
               newStr.erase(newStr.length() - 1);
               newList->insertMe(index, newStr); //inserts node

           } else {
               continue;
           }

       } else if (command == "delete"){
           cin >> index;
           newList->deleteMe(index);

       } else if (command == "print"){

            newList->printMe();

       } else if (command == "edit"){
           cin >> index ;
           getline(cin, newStr);
           newStr.erase(0,1);
           if(newStr.at(0) == '"' && newStr.at(newStr.length()-1) == '"') {
               newStr.erase(0, 1);
               newStr.erase(newStr.length() - 1);
               if(newList->validIndex(index)) {
                   newList->editMe(index, newStr);
               } else {
                   continue;
               }
           } else {
               continue;
           }

       } else if(command == "search") {
           getline(cin, newStr);
           newStr.erase(0,1);
           if(newStr.at(0) == '"' && newStr.at(newStr.length()-1) == '"') {
               newStr.erase(0, 1);
               newStr.erase(newStr.length() - 1);
                newList->searchMe(newStr);
           } else {
               continue;
           }

       } else if(command == "quit"){ //allows user to exit while loop
           run = false;
           break;
       }
   }

}

