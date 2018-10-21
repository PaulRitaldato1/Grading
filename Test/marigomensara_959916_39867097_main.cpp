//Sara Marigomen
//COP 3530 - Programming Assignment 1
//Section - 12137

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//create Node class
//Nodes contain: string of text, int of line number, and pointer to next node
class Node {
    public:
        string str;
        int num;
        Node* next = NULL;

};

//Function: insertEnd - add line to the end of the document
Node* insertEnd( Node* head, string newStr ) {
    //create new node and set values of node equal to new information
    Node* add = new Node;
    add->str = newStr;

    //if the list is empty, set the head as the new node
    if(head->str == "") {
        head = add;
        add->num = 1;

        //if the list has nodes, add the new node to the end
    } else {
        Node* itr = head;

        //iterate through list to find end
        while(itr->next != NULL)
            itr = itr->next;

        //append to the end
        add->num = itr->num+1;
        itr->next = add;

    }

    //return pointer to list
    return head;

}

//Function: insert - insert line of text at specified line number
Node* insert(Node* head, string newStr, int newNum) {
    //create iterator pointer
    Node* itr = head;

    //create new node and set values of node equal to new information
    Node* add = new Node;
    add->str = newStr;
    add->num = newNum;

    //line is to be added at the beginning
    if(newNum == 0 || newNum == 1) {
        head = add;
        add->next = itr;
        add->num = 1;

        //line is to be added at some later point in the document
    } else {
        while (itr->num < newNum-1) {
            itr = itr->next;
        }

        //reorganize pointers
        add->next = itr->next;
        itr->next = add;
    }

    itr = add;

    //change the line numbers of the texts
    while (itr->next != nullptr) {
        itr = itr->next;
        ++itr->num;
    }

    //return pointer to list
    return head;

}

//Function: delete - delete line of text at indicated line number
Node* deleteNode(Node* head, int dNum) {
    //create iterator
    Node* itr = head;

    //iterate through the list to find desired node/line number
    while(itr->next->num != dNum) {
        itr = itr->next;
    }

    //reorganize pointers to move over "deleted" node
    //if the pointer of "deleted" node points to another node
    if(itr->next!= NULL)
        itr->next = itr->next->next;

    //if the pointer of "deleted" node had pointed to NULL
    else
        itr->next = NULL;

    //reassign line numbers
    while (itr->next != NULL) {
        --itr->next->num;
        itr = itr->next;
    }

    //return pointer to list
    return head;

}

//Function: edit - change the text of a line on the indicated line number
Node* edit(Node* head, string newStr, int eNum) {
    //create iterator
    Node* itr = head;

    //iterate through to find desired line
    if(itr->num != eNum)
        itr = itr->next;

    //change the text on the correct node
    itr->str = newStr;

    //return a pointer to the list
    return head;

}

//Function: print - print out the entire list/document
void print (Node* head) {
    //spacing for nice formatting
    cout << endl;

    //create iterator
    Node* itr = head;

    //iterate through the list and print each line
    while (itr != NULL) {
        cout << itr->num << " " << itr->str << endl;
        itr = itr->next;
    }

}

//Function: search - look for certain text within the lines and print line in which it is found
void search (Node* head, string searchStr) {
    //create iterator
    Node* itr = head;

    //check lines if they have the specified text
    while(itr != NULL) {
        if (itr->str.find(searchStr) != itr->str.npos) {
            //print line
            cout << itr->num << " " << itr->str << endl;
            break;
        }
        //iterate through the document to find the right line
        else
            itr = itr->next;
    }
}


int main() {

    //create variables to read lines and separate into necessary parts
    string line;
    int pos = 0;
    int length;
    string command;
    string text;
    string num;
    int val = 0;
    Node* list = new Node;

    //continue to run program until user input ends
    while (command != "quit") {

        //read in entire line to a string
        getline(cin, line);
        length = line.length();

        //break off first word and designate it as command string
            if(line.find(' ') != line.npos) {
                while (line.at(pos) != ' ' && pos < length) {
                    command = line.substr(0, pos + 1);
                    pos++;
                }

                //make new substring after extracting command
                line = line.substr(pos + 1, length - 1);
                length = line.length();
                pos = 0;

            } else {
                command = line;
            }

            //check if line includes number, detailing which line to look at
            if (isdigit(line.at(0))) {
                if(line.find(' ') != line.npos) {
                    num = line.substr(pos, ' ');
                }
                else
                    num = line;

                stringstream convert(num);
                convert >> val;
                pos++;

                if (pos < length - 1)
                    pos++;
            }

            //if there is left over, take text in and remove quotation marks
            if (pos < length - 1) {
                line = line.substr(pos + 1, length - 1);

                length = line.length();
                text = line.substr(0, length - 1);
            }

            //list of command switches
        if (command == "insertEnd")
            list = insertEnd(list, text);

        else if (command == "insert")
            list = insert(list, text, val);

        else if (command == "delete")
            list = deleteNode(list, val);

        else if (command == "edit")
            list = edit(list, text, val);

        else if (command == "print")
            print(list);

        else if (command == "search")
            search(list, text);

        else{
            if(command != "quit")
                cout << "Error: command " << command << " is not found" << endl;
        }

    }
    return 0;
}