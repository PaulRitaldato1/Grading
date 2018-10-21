#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string data;
    Node *next;  // Next pointer allows forward traversal through the list.
};

class LinkedList {

public:
    Node *head;

    // Constructor method: sets both head and tail to point to NULL by default.
    LinkedList() {
        head = nullptr;
    }

    // Destructor method: delete each node in the list to release any allocated memory taken up by the list.
    ~LinkedList() {
        Node* current = head;
        while(current){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    /* INPUT:  Head of list, string of 80 characters
     * OUTPUT: Updated list
     * DESCRIPTION: Inserts the given text at the end of the document, and returns the head of the updated list. */
    Node* insertEnd(Node* head, string lineToAdd, int listSize) {
        Node* tmp = new Node;
        tmp->data = lineToAdd;


        // If list is empty, save the newly created node as the new head
        if (listSize == 0) {
            head = tmp;
            return head;
        }

        // If the list isn't empty, traverse to the end of the list and insert the new line
        Node* ptr = head;
        int currentIndex = 0;
        while ( currentIndex++ < (listSize - 1))
            ptr = ptr->next;

        tmp->next = ptr->next;
        ptr->next = tmp;

        return head;
    }

    /* INPUT:  Head of list, size of list, line index, string of 80 characters
     * OUTPUT: Updated list
     * DESCRIPTION: Inserts the given text at the specified index, and returns the head of the updated list. */
    Node* insertLine(Node* head, string lineToAdd, int requestedIndex, int listSize) {
        Node* tmp = new Node;
        tmp->data = lineToAdd;
        Node* ptr = head;

        // If inserting node at beginning of list:
        if (requestedIndex == 1) {
            tmp->next = ptr;            // set "next" to point to the head of the current list
            this->head = tmp;           // save the newly created node as the new head of the list
        } else {
            // If not inserting at beginning of list, insert at requested index.
            int currentIndex = 0;

            while ( currentIndex++ < (requestedIndex - 2) )
                ptr = ptr->next;

            tmp->next = ptr->next;
            ptr->next = tmp;
        }

        return head;
    }

    /* INPUT:  Head of list, line index
     * OUTPUT: Updated list
     * DESCRIPTION: Deletes the line at the specified index and returns the head of the updated list. */
    Node* deleteLine(Node* head, int requestedIndex) {
        Node *currPtr = head;
        Node *prevPtr = nullptr;

        // If the node to be deleted is the first node, set the second node as the new head
        if (requestedIndex == 1)
            this->head = head->next;
        else {
            int currIndex;
            for (currIndex = 1; currIndex < requestedIndex; currIndex++) {
                // Advance the current and previous node pointers until the requested index is found
                prevPtr = currPtr;
                currPtr = currPtr->next;
            }

            // If the node to be deleted is the last node:
            if (currPtr->next == nullptr)
                // Break the link to the last node, and set the previous node as the new last node
                prevPtr->next = nullptr;
            // If the node to be deleted is somewhere in the middle of the list:
            else
                // Break the link to the node that needs to be deleted, and have the prevPtr point to the node just past it.
                prevPtr->next = currPtr->next;
        }

        return head;
    }

    /* INPUT:  Head of list, string of 80 characters, line index
     * OUTPUT: Updated list
     * DESCRIPTION: Replaces the the line at the given index with the new text, and returns the head of the updated list. */
    Node* editLine(Node* head, int requestedIndex, string lineToAdd) {
        Node* currPtr = head;

        for (int currIndex = 1; currIndex < requestedIndex; currIndex++)
            currPtr = currPtr->next;

        currPtr->data = lineToAdd;
        return head;
    }

    /* INPUT: Head of list
     * DESCRIPTION: Prints each line of the document one-by-one, each labeled with line numbers. */
    void printList(Node* head) {
        Node* ptr = head;
        int lineCount = 1;
        while (ptr != nullptr) {
            cout << lineCount << " " << ptr->data << endl;
            ptr = ptr->next;
            lineCount++;
        }
    }

    /* INPUT: Head of list, string of 80 characters
     * DESCRIPTION: Prints the line number and line that contains the given text if found in the document, or prints "not found" otherwise. */
    void searchLine(Node* head, string textToSearch) {
        Node* currPtr;
        int lineCount, foundPos;
        bool textFound = false;
        string currentLine;

        lineCount = 1;
        // Traverse through entire list searching for the text
        for (currPtr = head; currPtr != nullptr; currPtr = currPtr->next) {
            currentLine = currPtr->data;
            foundPos = currentLine.find(textToSearch);
            // If the text was found in the list, print the line number and line where it resides, and return to the input prompt
            if (foundPos != string::npos) {
                textFound = true;
                cout << lineCount << " " << currPtr->data << endl;
            }
            lineCount++;
        }

        if (!textFound)
            cout << "not found" << endl;
    }

    // Takes in the head of the list and returns the current size of the list.
    int findListSize(Node* head) {
        int nodeCount = 0;
        Node* p = head;
        while (p != nullptr) {
            ++nodeCount;
            p = p->next;
        }

        return nodeCount;
    }
};


// Takes in the entire line entered by the user, and breaks it up into words separated by a space.
vector<string> inputFilter(string str) {
    string inputArg;
    vector<string> inputArgs;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've reached the first quotation mark of the input text, store all characters (including quotation marks
        //      and spaces) within the quotes as the final element of the argument vector, and return the vector.
        if (*it == '"') {
            while (it != str.end() - 1) {
                if ( *(it + 1) == '"' )
                    break;
                inputArg += *(it + 1);  // Removes quotation marks from the input text
                it++;
            }

            inputArgs.push_back(inputArg);
            return inputArgs;
        }
        // If we've hit the terminal character (a space)
        if (*it == ' ') {
            // If we have some characters accumulated
            if (!inputArg.empty()) {
                // Add them to the result vector
                inputArgs.push_back(inputArg);
                inputArg.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            inputArg += *it;
        }
    }
    if (!inputArg.empty())
        inputArgs.push_back(inputArg);
    return inputArgs;
}


int main() {
    LinkedList list;
    string userInput, inputArg, newLine, commandWord;
    vector<string> inputArgs;

    // This loop continuously runs and grabs the user's input until they end the program with the "quit" command.
    while (cin) {
        getline(cin, userInput);

        // Safely quit the program when the user enters "quit".
        if (userInput == "quit") {
            return 0;
        }

        std::vector<std::string> inputArgs = inputFilter(userInput);
        commandWord = inputArgs[0];

        int listSize = list.findListSize(list.head);

        // The following 'if statements' determine which operation the user would like to perform.
        if (inputArgs[0] == "insertEnd")
            list.head = list.insertEnd(list.head, inputArgs[1], listSize);
        else if (inputArgs[0] == "insert") {
            string indexStr = inputArgs[1];
            string::size_type sz;                   // alias of size_t
            int indexInt = stoi(indexStr, &sz);     // Convert string to int
            if (indexInt > listSize) {
                continue;   // Proceed to the input prompt to read in the next line from the user.
            }
            list.insertLine(list.head, inputArgs[2], indexInt, listSize);
        }
        else if (inputArgs[0] == "delete") {
            string indexStr = inputArgs[1];
            string::size_type sz;                   // alias of size_t
            int indexInt = stoi(indexStr, &sz);     // Convert string to int
            if (indexInt > listSize) {
                continue;   // Proceed to the input prompt to read in the next line from the user.
            }
            list.deleteLine(list.head, indexInt);
        }
        else if (inputArgs[0] == "edit") {
            string indexStr = inputArgs[1];
            string::size_type sz;                   // alias of size_t
            int indexInt = stoi(indexStr, &sz);     // Convert string to int
            if (indexInt > listSize) {
                continue;   // Proceed to the input prompt to read in the next line from the user.
            }
            list.editLine(list.head, indexInt, inputArgs[2]);
        }
        else if (inputArgs[0] == "print")
            list.printList(list.head);
        else if (inputArgs[0] == "search")
            list.searchLine(list.head, inputArgs[1]);
    }

    return 0;
}
