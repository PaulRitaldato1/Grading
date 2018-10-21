#include <iostream>
#include <string.h>
using namespace std;

struct Node{
    Node* next;
    string value;
};
Node* head;
Node* tail;

void insertEnd(string value){
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        Node* current = tail;
        current->next = newNode;
        tail = current->next;
    }
}
void insertIndex(string value, int index) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    int count = 1;

    Node *current = head;
    Node *temp = head;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        while (current != nullptr) {
            temp = current;
            current = current->next;
            count++;
            if (count == index) {
                temp->next = newNode;
                newNode->next = current;
            }
        }
    }
    if (newNode->next == nullptr){
        tail = newNode;
    }
}
void print(){
    Node* temp = head;
    int count = 1;
    while (temp != nullptr){
        cout << count << " " << temp->value << endl;
        count ++;
        temp = temp->next;
    }
}
void search(string searchTerm){
    bool found = false;
    Node* temp = head;
    int count = 1;
    while (temp != nullptr){
        if(temp->value.find(searchTerm) != string::npos){
            cout << count << " " << temp->value << endl;
            found = true;
        }
        count ++;
        temp = temp->next;
    }
    if (!found){
        cout << "not found" <<  endl;
    }
}
void edit(int index, string newText){
    Node* current = head;
    int count = 1;
    while (current != nullptr) {
        if (count == index) {
            current->value = newText;
            break;
        }
        current = current->next;
        count ++;
    }
}
void deleteValue(int index){
    Node* temp = head;
    Node* current = head;
    int count = 1;
    if(index == 1){
        head = head->next;
    }
    else {
        while (current != nullptr) {
            if (count == index) {
                temp->next = current->next;
            } else {
                temp = current;
            }
            current = current->next;
            count ++;
        }
    }
}

int main() {
    string option;
    cin >> option;
    while(option != "quit"){
        if(option == "insertEnd"){
            string text;
            getline(cin,text);
            text = text.substr(2,text.length()-3);
            insertEnd(text);
        }
        else if(option == "insert"){
            int index;
            string text;
            cin >> index;
            getline(cin,text);
            text = text.substr(2,text.length()-3);
            insertIndex(text,index);
        }
        else if(option == "search"){
            string text;
            getline(cin,text);
            text = text.substr(2,text.length()-3);
            search(text);
        }
        else if(option == "edit"){
            int index;
            string text;
            cin >> index;
            getline(cin,text);
            text = text.substr(2,text.length()-3);
            edit(index,text);
        }
        else if(option == "delete"){
            int index;
            cin >> index;
            deleteValue(index);
        }
        else if(option == "print"){
            print();
        }
        cin >> option;
    }
    return 0;
}