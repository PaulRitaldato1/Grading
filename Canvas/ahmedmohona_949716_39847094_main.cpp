#include <string>
#include <iostream>
#include <string.h>
using namespace std;

//your linked list implementation here

struct Node {
public:
    string line;
    Node *next = NULL;
};

//your line editor implementation here
void insertEnd(string txt, Node * head){
    //insert given text at the end of the document

    //base case if page is just being created
    if (head->line == ""){
        head->line = txt;
        return;
    }

    else{
        Node * current;
        Node * newNode = new Node();

        current = head;
        newNode -> line = txt;
        while(current != nullptr){
            if(current->next == nullptr){
                current->next = newNode;
                newNode->next = nullptr;
                return;
            }
            else{
                current = current->next;
            }
        }

    }

}

void insert(int index, string txt, Node* head){
//insert given text at the line indicated by index given
    Node * newNode = new Node();
    Node * current = head;
    int count = 1;

    newNode->line = txt;

    //base case

    if (index == 1){
        newNode->next = current;
    }

    else{
        while(current != nullptr){

            if(index - 1 == count){
                newNode->next = current->next;
                current->next = newNode;
            }

            current = current->next;
            count++;
        }

        return;
    }
}

void Delete(int index,Node* head) {
//delete line at index given
//THIS WORKS
    Node *current;
    Node *temp;
    int count = 1;

    current = head;

    //base case
    if (index == 0) {
        temp = current->next;
        *head = *temp;
        delete temp;
        return;
    }

    while (count != index) {

        if (current == nullptr) {
            return;
        }
        //If the next node is the node to delete
        if (count == index - 1) {
            if (current-> next == nullptr){
                return;
            }
            current->next = current->next->next;
            return;
        }
        current = current->next;
        count++;
    }
}
void edit(int index,string txt, Node* head){
//replace the line at the index given with the given text
    Node * current = head;
    int count = 1;

    //base case
    if(index == 0){
        head->line = txt;
    }

    while(count != index){
        if (current == nullptr){
            return;
        }
        //If the node is the node to replace text
        current = current->next;
        count++;
    }
    if (count == index){
        current->line = txt;
        return;
    }
}

void print(Node * head){
    Node * current;
    int count = 1;

    current = head;

    while(current != nullptr){
        cout<<count<< " " <<current->line<<endl;
        current = current->next;
        count++;
    }
}

void search(string txt, Node* head){
//print the line number and line that contains the given text.  print "not found" if it is not found

    Node * current = head;
    int count = 1;
    bool found = false;

    if(head == nullptr){
        cout<<"not found"<<endl;
    }

    while(current != nullptr){
        string theString = current->line;
        if (strstr(theString.c_str(), txt.c_str())){
            cout<<count<<" "<<theString<<endl;
            found = true;
        }
        current = current->next;
        count++;
    }
    if (found == false){
        cout<<"not found"<<endl;
    }

}

void quit(){
    exit(0);
}



int main() {

    Node * head = new Node();

    string addEnd("insertEnd");
    //change above
    string insertAtIndex("insert");
    string editText("edit");
    string deleteLine("delete");
    string printOutput("print");
    string searchText("search");
    string end("quit");
    string delim("\"");
    string space(" ");

    string input;
    string methodInput;
    int index = 0;
    int methodInputIntIndex = 0;
    int position;

    while (getline(cin, input)) {
        if (strstr(input.c_str(), addEnd.c_str())) {
            //find first \ which indicates "
            index = input.find(delim) + 1;
            //remove method call
            methodInput = input.substr(index, input.length() - 1);
            index = methodInput.find(delim);
            //extract string inside quotation marks
            methodInput = methodInput.substr(0, index);
            insertEnd(methodInput, head);
        } else if (strstr(input.c_str(), insertAtIndex.c_str())) {
            //find the position of the index the node will be added to
            methodInputIntIndex = input.find(space) + 1;
            //convert the string to an integer
            position = atoi((input.substr(methodInputIntIndex)).c_str());
            //remove the part of the input that contains the position the node will be added to
            input = input.substr(methodInputIntIndex + 1, input.length());


            //find first \ which indicates "
            index = input.find(delim) + 1;
            //remove method call
            methodInput = input.substr(index, input.length() - 1);
            index = methodInput.find(delim);
            //extract string inside quotation marks
            methodInput = methodInput.substr(0, index);
            insert(position, methodInput, head);
        } else if (strstr(input.c_str(), editText.c_str())) {
            //find the position of the index the node will be added to
            methodInputIntIndex = input.find(space) + 1;
            //convert the string to an integer
            position = atoi((input.substr(methodInputIntIndex)).c_str());
            //remove the part of the input that contains the position the node will be added to
            input = input.substr(methodInputIntIndex + 1, input.length());


            //find first \ which indicates "
            index = input.find(delim) + 1;
            //remove method call
            methodInput = input.substr(index, input.length() - 1);
            index = methodInput.find(delim);
            //extract string inside quotation marks
            methodInput = methodInput.substr(0, index);
            edit(position, methodInput, head);
        } else if (strstr(input.c_str(), deleteLine.c_str())) {
            //find the position of the index the node will be added to
            methodInputIntIndex = input.find(space) + 1;
            //convert the string to an integer
            position = atoi((input.substr(methodInputIntIndex)).c_str());
            //remove the part of the input that contains the position the node will be added to
            input = input.substr(methodInputIntIndex + 1, input.length());

            Delete(position, head);
        } else if (strstr(input.c_str(), printOutput.c_str())) {
            print(head);
        } else if (strstr(input.c_str(), searchText.c_str())) {
            //find first \ which indicates "
            index = input.find(delim) + 1;
            //remove method call
            methodInput = input.substr(index, input.length() - 1);
            index = methodInput.find(delim);
            //extract string inside quotation marks
            methodInput = methodInput.substr(0, index);
            search(methodInput, head);
        } else if (strstr(input.c_str(), end.c_str())) {
            quit();
        }
    }

    return 0;
}