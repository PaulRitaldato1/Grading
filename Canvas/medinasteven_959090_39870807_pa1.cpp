#include <iostream>
#include <string>
using namespace std;

// Node class implemented: hold line variable for text and nextLine pointer for next node. constructor
// initializes line variable with text and sets pointer to NULL
class Node {
    public:
    string line;
    Node * nextLine;

    Node(string text) {
        line = text;
        nextLine = NULL;
    }
};

// Linked List class implement: has head and tail variables to make insertEnd command O(1) instead of O(n).
// It also has node count for looping through the list. Constructor initializes head & tail to NULL and count to 0.
class LinkedList {
    public:
    Node * head;
    Node * tail;
    int nodeCount;

    LinkedList() {
        head = NULL;
        tail = NULL;
        nodeCount = 0;
    }

    void insertEnd(string text) {
        Node * addNode = new Node(text); //constructs new Node
        
        if (head == NULL) { // if there is no Node in the list
            head = addNode; // add to list and set head andd tail equal to this
            tail = addNode;
        } else { // else set tail to this new Node
            tail -> nextLine = addNode;
            tail = tail -> nextLine;
        }
        nodeCount++;
    }

    void insert(string text, int index) {
        if (index == nodeCount + 1) { // if add Node to end of list, go to insertEnd()
            insertEnd(text);
        } else if (index > nodeCount || index < 1) { // if add Node out of bounds of list, do nothing
            return;
        } else if (index == 1) {                // if add Node at beginning of list, change head to this node
            Node * addNode = new Node(text);    // and set its pointer to previous head
            Node * temp = head;

            head = addNode;
            addNode -> nextLine = temp;
            nodeCount++;
        } else {
            Node * addNode = new Node(text); // otherwise loop through the list to the node before the selected
            Node * temp = head;              // node and add this Node to the next Node and change pointers

            for (int i = 1; i < index - 1; i++) {
                temp = temp -> nextLine;
            }

            addNode -> nextLine = temp -> nextLine;
            temp -> nextLine = addNode;
            nodeCount++;
        }
    }

    void deleteNode(int index) {
        if (index > nodeCount || index < 1) { // if Node to delete out of index, do nothing
            return;

        } else if (index == nodeCount) { // if delete last Node, set tail to Node before current tail and delete
            Node * temp = head;
            
            for (int i = 1; i < index - 1; i++) {
                temp = temp -> nextLine;
            }

            tail = temp;
            temp = temp -> nextLine;
            tail -> nextLine = NULL;
            delete temp;
            nodeCount--;

        } else if (index == 1) { // if delete first Node, set head to next Node and delete first Node
            Node * temp = head;

            if (nodeCount == 1) {
                head = NULL;
                tail = NULL;
                delete temp;
                nodeCount--;
            } else {
                head = head -> nextLine;
                temp -> nextLine = NULL;
                delete temp;
                nodeCount--;
            }

        } else { // otherwise loop through list to selected index and delete Node, while switching pointers
            Node * temp = head;     // to adjust
            Node * deleteThis;

            for (int i = 1; i < index - 1; i++) {
                temp = temp -> nextLine;
            }

            deleteThis = temp -> nextLine;
            temp -> nextLine = temp -> nextLine -> nextLine;
            delete deleteThis;
            nodeCount--;
        }  
    }

    void edit(string text, int index) { // go to selected Node in List and change its line variable
        if (index > nodeCount || index < 1) {
            return;
        }

        Node * temp = head;

        for (int i = 1; i < index; i++) {
            temp = temp -> nextLine;
        }

        temp -> line = text;
    }

    void print() { // loop through each Node in list and print with loop number; i starts at 1
        Node * temp = head;
        for (int i = 1; i < nodeCount + 1; i++) {
            cout << i << " " << temp -> line << endl;
            if (i < nodeCount) {
                temp = temp -> nextLine;
            }
        }
    }

    void search(string text) { // Uses find() to search for part of string. Loops through list and prints correctly
        Node * temp = head;
        std::size_t findText;
        bool found = false;

        for (int i = 1; i < nodeCount + 1; i++) {
            findText = temp->line.find(text);
            if (findText != string::npos) {
                cout << i << " " << temp -> line << endl;
                found = true;
                temp = temp -> nextLine;
            } else if (i == nodeCount && !found) {
                cout << "not found" << endl;
            } else {
                temp = temp -> nextLine;
            }
        }
    }
};

// Line Editor class: passes line that was typed by user this class and is parsed into an array of size 3
// the first data in array holds command (insert, insertEnd, etc.); second holds index or text if no index required
// third data holds text if index is required
class LineEditor {
    public:
    string parsedCommandArray[3];
    string parseMe;

    LineEditor(string command) {
        parseMe = command;
    }

    void parse() { // this method parses the line inputted by user and parses it into array
        bool incrementCounter = true;
        int counter = 0;
        int quoteCount = 0;
        
        for (int i = 0; i < parseMe.length(); i++) {
            if (parseMe.at(i) == ' ' && incrementCounter) { // if space encountered, add char of line into new
                counter++;                                  // index of array
            } else if (parseMe.at(i) == '"') {              // if quotations found, do not increment index of array
                incrementCounter = false;                   // and add rest of line to current index
                quoteCount++;
            } else if (quoteCount == 2) {                   // if closing quotations found, stop parsing
                break;
            } else {                                        // add to current index of array the chars of line
                parsedCommandArray[counter] += parseMe.at(i);
            }
        }
    }
};

int main() {
    bool quit = false;                      // create quit variable to quit program
    LineEditor * le;                        // declare Line Editor
    LinkedList * ll = new LinkedList();     // declare and initialize Linked List
    string command;

    while (!quit) {
        getline(cin, command);              // method to user input entire line into variable
        
        if (command == "quit") {            // if input is quit or print, call appropriate function/change variable
            quit = true;
        } else if (command == "print") {
            ll -> print();
        } else {                            // otherwise initialize Line Editor and parse user input
            le = new LineEditor(command);
            le -> parse();
            
            if (le->parsedCommandArray[1] == "") {      // if no text, do nothing
                continue;
            }
            
            string option = le -> parsedCommandArray[0];        // take user command and call appropriate function

            if (option == "insertEnd") {
                ll -> insertEnd(le -> parsedCommandArray[1]);
            } else if (option == "insert") {
                if (le->parsedCommandArray[2] == "") {
                    continue;
                }
                ll -> insert(le -> parsedCommandArray[2], stoi(le->parsedCommandArray[1]));
            } else if (option == "delete") {
                ll -> deleteNode(stoi(le->parsedCommandArray[1]));
            } else if (option == "edit") {
                if (le->parsedCommandArray[2] == "") {
                    continue;
                }
                ll -> edit(le->parsedCommandArray[2], stoi(le->parsedCommandArray[1]));
            } else if (option == "search") {
                ll -> search(le->parsedCommandArray[1]);
            } else {
                continue;
            }
        }

        command = "";       // clear user input for new input
        cin.clear();
        delete & le;
    }
    return 0;
}