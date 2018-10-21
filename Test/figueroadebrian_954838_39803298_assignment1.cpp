#include <iostream>
#include <string>
using namespace std;

struct Node {
    string lineText = "";
    Node* next = NULL;
};

class LinkedList {
    Node* root;
    Node* tail;

public:
    LinkedList() {
        root = new Node();
        tail = root;
    }
    // add new node to end of list
    void push(string text) {
        Node* newNode = new Node();
        newNode->lineText = text;
        // add new node to the end
        tail->next = newNode;
        // change tail to new last node
        tail = tail->next;
    }

    bool insert(int lineIndex, string text) {
        Node* currentNode = root->next;
        Node* previousNode = NULL;
        for (int i = 0; i < lineIndex - 1; i++) {
            previousNode = currentNode;
            currentNode = currentNode == NULL ? NULL : currentNode->next;
        }
        Node* newNode = new Node();
        newNode->lineText = text;
        if (currentNode == NULL && previousNode == NULL) {
            // index out of bounds
            return false;
        } else if (currentNode == NULL) {
            // inserting to end of list
            previousNode->next = newNode;
            // update tail
            tail = previousNode->next;
        } else if (previousNode == NULL) {
            // inserting at the start of the list
            newNode->next = currentNode;
            // update root of the list
            root->next = newNode;
        } else {
            // insertion in list
            previousNode->next = newNode;
            newNode->next = currentNode;
        }
        return true;
    }

    bool deleteLine(int lineIndex) {
        Node* currentNode = root->next;
        Node* previousNode = NULL;
        for (int i = 0; i < lineIndex - 1; i++) {
            previousNode = currentNode;
            currentNode = currentNode == NULL ? NULL : currentNode->next;
        }
        if (currentNode == NULL) {
            // index out of bounds
            return false;
        } else if (previousNode == NULL) {
            // delete at the start of the list
            // update root of the list
            root->next = currentNode->next;
            // delete from memory
            delete currentNode;
            currentNode = NULL;
        } else {
            // delete node from list
            previousNode->next = currentNode->next;
            // delete from memory
            delete currentNode;
            currentNode = NULL;
        }
        return true;
    }

    Node* getIterator() { return root->next; }
};

class LineEditor {
    LinkedList* list;

    bool isContained(string text, string sentence) {
        return sentence.find(text) != std::string::npos;
    }
public:
    LineEditor() {
        list = new LinkedList();
    }

    bool edit(int lineIndex, string text) {
        Node* currentNode = list->getIterator();
        for (int i = 0; i < lineIndex - 1; i++) {
            currentNode = currentNode == NULL ? NULL : currentNode->next;
        }

        if (currentNode == NULL) {
            // out of bounds
            return false;
        }
        currentNode->lineText = text;
        return true;
    }

    string search(string text) {
        string result = "";
        // find first occurrence of text in list
        int lineNumber = 1;
        // search each node and check if text is contained within lineText
        Node* currentNode = list->getIterator();
        while (currentNode != NULL) {
            if (isContained(text, currentNode->lineText)) {
                result += std::to_string(lineNumber) + " " + currentNode->lineText + "\n";
            }
            lineNumber++;
            currentNode = currentNode->next;
        }
        if (result.empty()) {
            return "not found";
        } else {
            return result;
        }
    }

    void print() {
        Node* currentNode = list->getIterator();
        int lineNumber = 1;
        while (currentNode != NULL) {
            cout << std::to_string(lineNumber) << " ";
            cout << currentNode->lineText << endl;
            lineNumber++;
            currentNode = currentNode->next;
        }
    }

    void insertEnd(string text) {
        list->push(text);
    }

    bool insert(int index, string text) {
        return list->insert(index, text);
    }

    bool deleteLine(int index) {
        return list->deleteLine(index);
    }
};
// define command constants
#define INSERT_END "insertEnd"
#define INSERT "insert"
#define DELETE "delete"
#define EDIT "edit"
#define PRINT "print"
#define SEARCH "search"
#define QUIT "quit"

// helper methods
string getCommand(string line) {
    string result = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            break;
        }
        result += line[i];
    }
    return result;
}

string getValue(string line) {
    int spaceIndex = line.find_first_of(' ');
    return line.substr(spaceIndex + 1);
}

int getIndexFromValue(string value) {
    int spaceIndex = value.find_first_of(' ');
    return std::stoi(value.substr(0, spaceIndex));
}

string getTextValue(string value) {
    int openQuoteIndex = value.find_first_of('"');
    int closedQuoteIndex = value.find_last_of('"');
    return value.substr(openQuoteIndex + 1, (closedQuoteIndex) - (openQuoteIndex + 1));
}

int main()
{
    LineEditor editor;
    string line;
    bool quit = false;
    //get all commands
    while (std::getline(cin, line) && !quit)
    {
        string command = getCommand(line);
        string commandValue = getValue(line);

        if (command == INSERT_END) {
            commandValue = getTextValue(commandValue);
            editor.insertEnd(commandValue);
        } else if (command == INSERT) {
            int index = getIndexFromValue(commandValue);
            commandValue = getTextValue(commandValue);
            editor.insert(index, commandValue);
        } else if (command == DELETE) {
            int index = getIndexFromValue(commandValue);
            editor.deleteLine(index);
        } else if (command == EDIT) {
            int index = getIndexFromValue(commandValue);
            commandValue = getTextValue(commandValue);
            editor.edit(index, commandValue);
        } else if (command == PRINT) {
            editor.print();
        } else if (command == SEARCH) {
            commandValue = getTextValue(commandValue);
            cout << editor.search(commandValue) << endl;
        } else if (command == QUIT) {
            quit = true;
        }
    }
    return 0;
}
