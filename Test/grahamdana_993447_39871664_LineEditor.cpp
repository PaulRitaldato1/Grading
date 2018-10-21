#include <iostream>
#include <string>
#include <cstdlib>
#include <iostream>
#include "LineEditor.h"

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
};

void LinkedList::insertEnd(string text) { //inserts node at end of linked list
    auto newNode = new nodeObj;
    newNode->data = text;

    if (head == nullptr) { //insert first node
        head = newNode;
    }
        //go to end of linked list and insert node
    else {
        auto temp = new nodeObj;
        temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
            newNode->index++;
        }
        newNode->index++;
        temp->next = newNode;
    }
    lines++;
}

void LinkedList::insert(int index, string text) { //inserts node at given index in linked list
    auto newNode = new nodeObj;
    newNode->data = text;
    newNode->index = index;
    if (index == 0) {
        cout << " " << endl;
        return;
    }

    else if (index < lines + 1) {
        if (index == 1) { //insert at beginning of linked list
            newNode->next = head;
            head = newNode;
            nodePtr temp = head->next;
            while (temp != nullptr) {
                temp->index++;
                temp = temp->next;
            }
        }
        else { //insert in the middle of linked list
            nodePtr prev = head;
            nodePtr curr = head->next;
            for (int i = 1; i < index - 1; i++) { //iterate through the list to find desired index
                prev = curr;
                curr = curr->next;
            }

            prev->next = newNode;
            newNode->next = curr;
            nodePtr temp = curr;
            while (temp != nullptr) {
                temp->index++;
                temp = temp->next;
            }

        }
        lines++;


    }
    else if (index == lines + 1) { //insert at end of linked list
        insertEnd(text);
        return;
    }

}

void LinkedList::del(int index) { //deletes node at given index in linked list

    nodePtr prev = head;
    nodePtr curr = head->next;
    if (index < 1 | index > lines) { //error; ignore input
        return;
    }
    else if (index == 1) { //delete first node
        nodePtr toDelete = head;
        head = head->next; //reassign head to next node
        delete toDelete;
        nodePtr temp = head;
        while (temp != nullptr) { //adjust following indicies
            temp->index--;
            temp = temp->next;
        }
    }
    else if (index < lines){ //delete node in the middle of list
        for (int i = 1; i < index - 1; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        delete curr;
        prev = prev->next;
        while (prev != nullptr) {
            prev->index--;
            prev = prev->next;
        }

    }
    else if (index == lines) {
        for (int i = 1; i < index - 1; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = nullptr;
        delete curr;

    }
    lines--;
}

void LinkedList::edit(int index, string text) { //changes text of node at given index of linked list
    auto temp = new nodeObj;
    bool isFound = false;
    temp = head;

    while (temp != nullptr) { //search for a node that has the same text as the input
        if (temp->index == index) {
            isFound = true;
            temp->data = text; //change text here
            break;
        }
        else {
            temp = temp->next;
        }
    }
    if (!isFound) { //if no text matches the input
        cout << "not found" << endl;
    }
}

void LinkedList::print() { //prints contents of linked list
    auto temp = new nodeObj;
    temp = head;
    while (temp != nullptr) {
        cout << temp->index << " " << temp->data << endl;
        temp = temp->next;
    }
}

void LinkedList::search(string text) { //search for node using text
    auto temp = new nodeObj;
    bool isFound = false;
    temp = head;
    while (temp != nullptr) {
        if (temp->data == text | temp->data.find(text) != string::npos) {
            isFound = true;
            cout << temp->index << " " << temp->data << endl;
            if (temp->next != nullptr) {
                temp = temp->next;
                isFound = false;
            }
            else {
                break;
            }
        }
        else {
            temp = temp->next;
        }
    }
    if (!isFound) { //item couldn't be found
        cout <<"not found" << endl;
    }
}


int main() {

    string input;
    LinkedList lineEditor;
    lineEditor.lines = 0;

    while (true) {
        getline(cin, input); //gets input

        /* PARSING INPUT */
        string inp1; //first word (command)
        string inp2; //second "word" (either index number or text)
        string inp3; //third "word" (text only)

        int spaceCounter = 0;

        int start1 = 0; //first starting index
        int start2 = 0; //second starting index
        int start3 = 0; //third starting index

        int length1 = 0; //length of first word
        int length2 = 0; //length of second "word"
        int length3 = 0; //length of third word

        for (int i = 0; i < input.length(); i++) {
            if (input[i] == ' ') { //if char is a space

                spaceCounter++;
                i++;
                if (spaceCounter == 1) {
                    if (input[i] == '"') { //keep adding characters into a single string until the final quotation marks
                        i++;
                        start2 = i;
                        while (input[i] != '"') {
                            length2++;
                            i++;
                        }
                        inp2 = input.substr(start2, length2);
                    } else if (input[i] != '"') {
                        start2 = i;
                        length2++;
                    }
                    inp1 = input.substr(start1, length1);
                }
                if (spaceCounter == 2) {
                    if (input[i] == '"') {//keep adding characters into a single string until the final quotation marks
                        i++;
                        start3 = i;
                        while (input[i] != '"') {
                            length3++;
                            i++;
                        }
                        inp3 = input.substr(start3, length3);
                    } else if (input[i] != '"') {
                        start3 = i;
                        length3++;
                    }
                    if (inp2.empty()) {
                        inp2 = input.substr(start2, length2);
                    }
                }
            } else { //char is not a space, no new strings added yet
                if (spaceCounter == 0) {
                    length1++;

                } else if (spaceCounter == 1) {
                    length2++;

                } else if (spaceCounter == 2) {
                    length3++;

                }
            }
        }
        if (spaceCounter == 0 & inp1.empty()) {
            inp1 = input.substr(start1, length1);
        }

        if (spaceCounter == 1 & inp2.empty()) {
            inp2 = input.substr(start2, length2);
        }

        if (spaceCounter == 2 & inp3.empty()) {
            inp3 = input.substr(start3, length3);
        }

        /* COMMANDS */
        if (inp1 == "insertEnd") { //insertEnd
            if (inp2.length() <= 80) {
                lineEditor.insertEnd(inp2);
            }
            else if (inp2.length() > 80) {
                cout << "Line is too long. Please try again." << endl;
            }

        }
        else if (inp1 == "insert") { //insert
            bool isNumber = true;
            for (int i = 0; i < inp2.length(); i++) {
                if (!isdigit(inp2[i])) {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber & inp3.length() <= 80) {
                int insertIndex = stoi(inp2);
                lineEditor.insert(insertIndex, inp3);
            }
            else {
                if (inp3.length() > 80) {
                    cout << "Line is too long. Please try again." << endl;
                }
                else {
                    cout << "Error, please try again." << endl;
                }
            }


        }
        else if (inp1 == "delete") { //delete
            bool isNumber = true;
            for (int i = 0; i < inp2.length(); i++) {
                if (!isdigit(inp2[i])) {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber) {
                int deleteIndex = stoi(inp2);
                lineEditor.del(deleteIndex);
            }
            else {
                cout << "Error, please try again." << endl;
            }
        }
        else if (inp1 == "edit") {//edit
            bool isNumber = true;
            for (int i = 0; i < inp2.length(); i++) {
                if (!isdigit(inp2[i])) {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber) {
                int editIndex = stoi(inp2);
                lineEditor.edit(editIndex, inp3);
            }
            else {
                cout << "Error, please try again." << endl;
            }

        }
        else if (inp1 == "print") { //print
            lineEditor.print();
        }
        else if (inp1 == "search") { //search
            lineEditor.search(inp2);
        }
        else if (inp1 == "quit") { //quit
            return 0;
        }
        else { //error
            continue;
        }
    }
}