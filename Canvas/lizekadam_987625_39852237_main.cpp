#include <iostream>
#include <string>

using namespace std;

struct Node{
    string data;
    Node* next;

};

class LinkedList{
public:
    Node* head = NULL;
    int length;
    void addNodeEnd(string data);
    void addNodeIndex(int index, string data);
    void printOut(Node* head);
    void deleteNode(int index);
    void editNode(int index, string data);
    void searchNode(string data);

};

Node *first;

int main() {
    bool flag = true;
    string command;
    int index;
    string data;
    LinkedList* newList = new LinkedList();


    while(flag == true){
        cin >> command;

        if(command == "insertEnd"){
            getline(cin, data);
            data.erase(0, 1);
            if(data.front() != '"' || data.back() != '"') continue;
            data.erase(0, 1);
            data.erase( data.size() - 1 );
            newList->addNodeEnd(data);

        } else if(command == "insert") {
            cin >> index;
            getline(cin, data);
            data.erase(0, 1);
            if(data.front() != '"' || data.back() != '"') continue;
            data.erase(0, 1);
            data.erase( data.size() - 1 );
            if(cin.fail()){
                cin.ignore();
                cin.clear();
                continue;
            }
            if(newList->length == 0 && index == 1){
                newList->addNodeEnd(data);
                continue;
            }
            if(index-1 == newList->length){
                newList->addNodeEnd(data);
                continue;
            }
            if(index > newList->length || index < 1) continue;
            newList->addNodeIndex(index, data);
        } else if(command == "delete") {
            cin >> index;
            if(cin.fail()){
                cin.ignore();
                cin.clear();
                continue;
            }
            newList->deleteNode(index);
        } else if(command == "print") {
            newList->printOut(newList->head);
        } else if(command == "edit") {
            cin >> index;
            getline(cin, data);
            data.erase(0, 1);
            if(data.front() != '"' || data.back() != '"') continue;
            data.erase(0, 1);
            data.erase( data.size() - 1 );
            if(cin.fail()){
                cin.ignore();
                cin.clear();
                continue;
            }
            newList->editNode(index, data);
        } else if(command == "search") {
            getline(cin, data);
            data.erase(0, 1);
            if(data.front() != '"' || data.back() != '"') continue;
            data.erase(0, 1);
            data.erase( data.size() - 1 );
            newList->searchNode(data);
        } else if(command == "quit") {
            flag = false;
        }
    }
    return 0;
}
void LinkedList::addNodeIndex(int index, string data){
    index = index - 1;
    Node* freshNode = new Node();
    freshNode->data = data;
    if(index == 0){
        freshNode->next = this->head;
        head = freshNode;
    } else {
        int i = 1;
        Node *iterator = this->head;
        while (i < index) {
            iterator = iterator->next;
            if (iterator == NULL) {
                break;
            }
            i++;
        }
        Node *nextNode = iterator->next;
        iterator->next = freshNode;
        freshNode->next = nextNode;
    }
    length++;
}

void LinkedList::addNodeEnd(string data){
      Node* freshNode = new Node();
      freshNode->data = data;
      freshNode->next = NULL;
      if(this->head==NULL){
          this->head = freshNode;
          first = freshNode;
      }
      else{
           while(this->head->next != NULL){
               this->head = this->head->next;
           }
           this->head->next = freshNode;
      }
      this->head = first;
      length++;
}

void LinkedList::searchNode(string data) {
    Node* iterator = this->head;
    int x = 1;
    bool found = false;
    while(iterator != NULL){
        if(iterator->data.find(data) != std::string::npos){
            cout << x << " " << iterator->data << endl;
            found = true;
        }
        iterator = iterator->next;
        x++;
    }
    if(found == false){
        cout <<"not found" << endl;
    }
}

void LinkedList::deleteNode(int index) {
    Node* iterator = head;
    Node* start = NULL;
    if(index > length || index < 1){
        return;
    }
    else if(index == 1){
        this->head = iterator->next;
        iterator = NULL;
        delete(iterator);
        return;
    }
    int x = 1;
    while(x < index){
        start = iterator;
        iterator = iterator->next;
        x++;
    }
    if(index == length){
        start->next = NULL;
    } else start->next = iterator->next;
    delete(iterator);
}

void LinkedList::editNode(int index, string data) {
    Node* iterator = this->head;
    int x = 1;
    while(iterator != NULL){
        if(x == index){
            iterator->data = data;
        }
        iterator = iterator->next;
        x++;
    }
}

void LinkedList::printOut(Node* head){
    head = this->head;
    int x = 1;
    while(head){
        cout << x << " " << head->data << endl;
        head = head->next;
        x++;
    }
}



