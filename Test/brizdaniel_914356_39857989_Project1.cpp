#include <vector>
#include <iostream>
#include <string>
using namespace std;

class LinkedList
{
public:
    class Node {
    public:
        string text;
        Node* next;
        Node* prev;
        Node(Node* previous, Node* nxt, string value) {
            this->next = nxt;
            this->prev= previous;
            this->text = value;
        }
    };

private:
    Node* head;
    Node* tail;
    unsigned int nodeCount;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
    }

    void insertEnd(string value){
        if(tail == NULL){
            tail = new Node(NULL, NULL, value);
            head = tail;
        }
        else{
            Node* oldTail = tail;
            tail = new Node(oldTail, NULL, value);
            oldTail->next = tail;
        }
        nodeCount++;
    }

    void insert(int index, string value){
        if(index <= nodeCount) {
            Node *iterator = head;
            if (index == 0) {
                if (head = NULL) {
                    head = new Node(NULL, NULL, value);
                    tail = head;
                } else {
                    Node *oldHead = head;
                    head = new Node(NULL, oldHead, value);
                    oldHead->prev = head;
                }
                nodeCount++;
            } else if (index == nodeCount) {
                insertEnd(value);
            } else {
                for (int i = 0; i < index; i++) {
                    iterator = iterator->next;
                }
                Node *oldPrev = iterator->prev;
                Node *n = new Node(oldPrev, iterator, value);
                iterator->prev = n;
                oldPrev->next = n;
                nodeCount++;
            }
        }
    }

    void deleteAt(int index){
        if(index < nodeCount) {
            Node *iterator = head;
            for (int i = 0; i < index; i++) {
                iterator = iterator->next;
            }
            if (iterator == head) {
                head = head->next;
            } else if (iterator == tail) {
                tail = tail->prev;
            }
            Node *oldNode = iterator;
            Node *nextNode = iterator->next;
            Node *prevNode = iterator->prev;
            if (nextNode != nullptr)
                nextNode->prev = prevNode;
            if (prevNode != nullptr)
                prevNode->next = nextNode;
            delete oldNode;
            nodeCount--;
        }
    }

    void edit(int index, string value){
        deleteAt(index);
        insert(index, value);
    }

    void print(){
        Node* iterator = head;
        for(unsigned int i = 0; i < nodeCount; i++) {
            cout << i+1 << " ";
            cout << iterator->text << endl;
            iterator = iterator->next;
        }
    }

    void search(string value){
        Node* iterator = head;
        bool found = false;
        for(unsigned int i = 0; i < nodeCount; i++){
            if(iterator->text.find(value) != string::npos){
                cout << i+1 << " " << iterator->text << endl;
                found = true;
            }
            iterator=iterator->next;
        }
        if(!found) {
            cout << "not found" << endl;
        }
    }
};
int main()
{
    string choice;
    int line;
    LinkedList LL;

    while(choice != "quit"){
        getline(cin, choice);
        if(choice.find("insertEnd") != string::npos){
            if(choice.find('"') == string::npos){
                break;
            }
                choice = choice.substr(choice.find('"'), choice.length());
                choice = choice.substr(1, choice.length()-2);
                LL.insertEnd(choice);
        }
        else if(choice.find("print") != string::npos){
            LL.print();
        }
        else if(choice.find("insert") != string::npos){
            if(choice.find('"') == string::npos){
            break;
        }
        string index = choice;
        index = index.substr(index.find(' ')+1, index.length());
        index = index.substr(0, index.find(" "));
        choice = choice.substr(choice.find('"'), choice.length());
        choice = choice.substr(1, choice.length()-2);
        int i = stoi(index);
        LL.insert(i-1, choice);
    }
        else if(choice.find("delete") != string::npos){
            string index = choice;
            index = index.substr(index.find(' ')+1, index.length());
            index = index.substr(0, index.find(" "));
            int i = stoi(index);
            LL.deleteAt(i-1);
        }
        else if(choice.find("edit") != string::npos){
            if(choice.find('"') == string::npos){
                break;
            }
            string index = choice;
            index = index.substr(index.find(' ')+1, index.length());
            index = index.substr(0, index.find(" "));
            choice = choice.substr(choice.find('"'), choice.length());
            choice = choice.substr(1, choice.length()-2);
            int i = stoi(index);
            LL.edit(i-1, choice);
        }
        else if(choice.find("search") != string::npos){
            if(choice.find('"') == string::npos){
                break;
            }
            choice = choice.substr(choice.find('"'), choice.length());
            choice = choice.substr(1, choice.length()-2);
            LL.search(choice);
        }
    }
}