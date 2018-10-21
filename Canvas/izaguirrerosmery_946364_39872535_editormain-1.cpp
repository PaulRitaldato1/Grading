#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
using std::string;

class linkedlist
{
    private:
        struct node{
            string line;
            node* next;
        };

        node* head;
        node* tail;
        node* curr;

    public: //functions
        linkedlist();
        void insertEnd(std::string newLine);
        void insertAt(int index, std::string newLine);
        void deleteAt(int index);
        void edit(int index, std::string newLine);
        void print();
        void searchLine(std::string userLine);
};


linkedlist::linkedlist()
{
    head = NULL;
    tail = NULL;
    curr = NULL;

}

void linkedlist::insertEnd(string newLine){
    node* n = new node();
    n->next = NULL;
    n->line = newLine;

    if (head==NULL){ //if list is empty
        head = n;
        tail = n;
    }
    else {
        node* curr = head;

        while (curr->next!=NULL){ //insert at the end of the list
            curr = curr->next;
        }

        curr->next = n;
        tail = n;
    }
}

void linkedlist::insertAt(int index, string newLine){
    node* n = new node;
    n->next = NULL;
    n->line = newLine;
    node* curr = head;
    int i = 1;

    if (head==NULL){ //if list is empty
        head = n;
    }
    else{
        while (curr->next!=NULL && i<index){
            curr = curr->next;
            i++;
        }

        if (i == 1){ //replace the head
            head = n->next;
            n->next = curr->next;
        }
        else { //replace any other node in the list
            n->next = curr->next;
            curr->next = n; //reverse for some reason
        }
    }
}

void linkedlist::deleteAt(int index){
    node* temp = head;
    node* prev = head;
    int i = 1;

    while (temp!=NULL && i<index){
        prev = temp;
        temp = temp->next;
        i++;
    }

    if (temp==NULL){ //if the index is not valid
        return;
    }
    else if (i == 1){ //delete the head
        head = temp->next;
        delete(temp);
    }
    else { //delete any other node
        prev->next = temp->next;
        delete(temp);
    }

}

void linkedlist::edit(int index, string newLine){
    node* curr = head;
    int i = 1;

    while (i<index){
        curr = curr->next;
        i++;
    }

        if (curr->next==NULL) //invalid index
            return;

        else{ //replace line
            curr->line = newLine;
        }
}

void linkedlist::print(){
    node* curr = head;
    int i = 1;

    while (curr!=NULL){ //while there is something to print
        cout << i << " " << curr->line << endl;
        curr = curr->next;
        i++;
    }
        return;
}

void linkedlist::searchLine(string userLine){
    node* curr = head;
    int i = 1;

    while (curr->next!=NULL && curr->line.compare(userLine)!=0){
        curr->next = curr;
        i++;
    }

    if (curr->next==NULL){
        cout << "not found" << endl;
        return;
    }
    else {
        cout << i << " " << curr->line << endl;
    }
}

int main()
{
    linkedlist editor;
    string userInput;
    cin >> userInput;

    while(userInput!="quit"){
        int spaceIndex = userInput.find(" ");
        int lineIndex = userInput.find("""");

        string command = userInput.substr(0, spaceIndex-1);
        string numIndex = userInput.substr(spaceIndex+1);
        int indexVal = stoi(numIndex);
        string lineVal = userInput.substr(lineIndex+1);

        if (command.compare("insertEnd")==0)
            editor.insertEnd(lineVal);
        else if(command.compare("insert")==0)
            editor.insertAt(indexVal, lineVal);
        else if(command.compare("delete")==0)
            editor.deleteAt(indexVal);
        else if(command.compare("edit")==0)
            editor.edit(indexVal, lineVal);
        else if (command.compare("print")==0)
            editor.print();
        else if (command.compare("search")==0)
            editor.searchLine(lineVal);
        else
            exit(0);

    }

    exit(0);
    return 0;
}
