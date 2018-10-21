#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct Node {
    string text;
    Node *next;
};

class LinkedList {
public:
    Node *head, *tail;
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void insertEnd(string text){
        Node *temp = new Node;
        temp->text = text;
        temp->next = NULL;
        if (head == NULL){
            head = temp;
            tail = temp;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
        return;
    }

    void insert(int position, string text) {
        Node *newOne = new Node;
        newOne->text = text;
        if (position == 1) {
            newOne->next = head;
            head = newOne;
        } else {
            Node *temp = head;
            int lengthList = 0;
            while(temp != NULL) {
                temp = temp->next;
                lengthList++;
            }

            // Make sure insert is at a valid point
            if (lengthList + 1 >= position) {
                int i = 1;
                Node *now = head;
                while (i < position - 1) {
                    now = now->next;
                    i++;
                }

                Node *next = now->next;
                now->next = newOne;
                newOne->next = next;
            }
        }

        return;
    }

    void edit(int lineNum, string text) {
        remove(lineNum);
        insert(lineNum, text);
    }

    void remove(int position) {
        if (head != NULL) {
            Node *temp = head;
            if (position == 1) {
                head = temp->next;
                free(temp);
            } else {
                int i = 1;
                while(temp != NULL && i < position - 1) {
                    temp = temp->next;
                    i++;
                }
                if (temp == NULL || temp->next == NULL)
                    return;
                Node *next = temp->next->next;
                free(temp->next);
                temp->next = next;
            }
        }

        return;
    }

    void print() {
        Node *temp;
        temp = head;
        int numLine = 1;
        while (temp != NULL) {
            cout << numLine << " " << temp->text << endl;
            temp = temp->next;
            numLine++;
        }
        return;
    }

    void search(string searchText) {
        Node *temp = head;
        int numLine = 1;
        bool found = false;
        while (temp != NULL) {
            if(temp->text.find(searchText) <= temp->text.length()) {
                cout << numLine << " " << temp->text << endl;
                found = true;
            }
            numLine++;
            temp = temp->next;
        }
        if (found == false) {
            cout << "not found" << endl;
        }

        return;
    }
};


int main() {
    LinkedList linkedList;
    string choice = "";

    while (1 == 1) {
        getline(cin, choice);

        if (choice.substr(0,11) == "insertEnd \"") {
            //Case if inserting text at end

            if (choice.substr(choice.length()-1) == "\"") {
                choice.pop_back();
                linkedList.insertEnd(choice.substr(11));
            }

            continue;
        }

        if (choice.substr(0,6) == "insert") {
            //Case if inserting text at position

            if (isdigit(choice.at(7))) {
                int lineNum = choice.at(7);
                if (choice.substr(choice.length() - 1) == "\"") {
                    if (choice.at(9) == '"') {
                        choice.pop_back();
                        linkedList.insert(stoi(choice.substr(7,1)), choice.substr(10));
                    }
                }
            }

            continue;
        }

        if (choice.substr(0, 5) == "edit ") {
            if (isdigit(choice.at(5))) {
                if (choice.at(7) == '"') {
                    if (choice.substr(choice.length() - 1) == "\"") {
                        choice.pop_back();
                        linkedList.edit(stoi(choice.substr(5,1)), choice.substr(8));
                    }
                }
            }

            continue;
        }

        if (choice.substr(0,7) == "delete ") {
            if (isdigit(choice.at(7)) && choice.length() == 8) {
                linkedList.remove(stoi(choice.substr(7,1)));
            }

            continue;
        }

        if (choice.substr(0,8) == "search \"") {
            if (choice.substr(choice.length() - 1) == "\"") {
                choice.pop_back();
                linkedList.search(choice.substr(8, choice.length() - 1));
            }

            continue;
        }

        if (choice.substr(0,7) == "print") {
            linkedList.print();

            continue;
        }

        if (choice.substr(0,4) == "quit") {
            return 0;
        }
    }
}