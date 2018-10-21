#include <iostream>
using namespace std;

class LinkedList { //Created LinkedList class to initialize Node struct and methods/objects
public:
    struct Node {
        string line = "";
        Node *next = NULL;
    };
    LinkedList();
    void insert(int index, string input);
    void insertEnd(string input);
    void delNode(int index);
    void edit(int index, string input);
    void print();
    void search(string input);
private:
    Node* head;
    Node* temp;
    Node* prev;
    Node* tail;
};

LinkedList::LinkedList() { //Node constructor
    head = NULL;
    temp = NULL;
    prev = NULL;
    tail = NULL;
}

void LinkedList::insertEnd(string input) { //Inserts node at tail of LL
    Node* newNode = new Node();
    newNode->line = input;
    if (head != NULL) { //Checks if head exists, iterates through till the end of the list, otherwise add node at head
        tail->next = newNode;
        tail = newNode;
        tail->next = NULL;
    } else {
        head = newNode;
        tail = newNode;
    }
}

void LinkedList::insert(int index, string input) { //Inserts node at index
    Node* newNode = new Node();
    newNode->line = input;
    int pos = 1;
    temp = head;
    if (head != NULL) { //If head exists, iterates through until index is hit or the end of LL
        while(temp->next != NULL && pos != index) {
            prev = temp;
            temp = temp->next;
            pos++;
        }
        if(temp->next == NULL && pos == index - 1) { //If at end of LL, adds node at end
            insertEnd(input);
        }
        if(pos != index) { //If index is out of bounds, do nothing
            return;
        }
        prev->next = newNode;
        newNode->next = temp;
    }
}

void LinkedList::print() { //Iterates through and prints each node
    temp = head;
    int pos = 1;
    while(temp != NULL) {
        cout << pos << " " << temp->line << endl;
        temp = temp->next;
        pos++;
    }
}

void LinkedList::edit(int index, string input) { //Finds the node index and edits the line
    temp = head;
    int pos = 1;
    while(temp != NULL && pos != index) { //Iterates through until index is reached or end is reached
        temp = temp->next;
        pos++;
    }
    if (pos == index) {
        if (temp == NULL) { //If the node at the index doesn't exist, don't do anything
            return;
        } else {
            temp->line = input;
        }
    } else {
        return;
    }
}

void LinkedList::delNode(int index) { //Deletes node at given index
    temp = head;
    int pos = 1;
    while(temp->next != NULL && pos != index) { //Iterates through until index is reached or end of list
        prev = temp;
        temp = temp->next;
        pos++;
    }
    if(pos != index) { //If node doesn't exist, do nothing
        return;
    }
    if(pos == 1) { //If index is 1, deletes the head node
        head = head->next;
        free(temp);
    }
    prev->next = temp->next;
    free(temp);
}

void LinkedList::search(string input) { //Searches for nodes containing the given strings
    temp = head;
    int pos = 1;
    bool found = false;
    while(temp != NULL) {
        if(temp->line.find(input) != string::npos) { //Compares the node string to the input string and tests if it contains the input string
            cout << pos << " " << temp->line << endl;
            found = true;
        }
        temp = temp->next;
        pos++;
    }
    if (found == false) { //Checks for out of bounds index
        cout << "not found" << endl;
    }
}

int main() {
    LinkedList list;
    string input = "";
    string function = "";
    string line = "";
    string index = "";
    string space = " "; //Delimiter for the node index
    string quote = "\""; //Delimiter for the node string

    while(true) {
        getline(cin, input);
        function = input.substr(0, input.find(space)); //Takes in the first entry as the function command
        if(function == "quit") { //Quits program
            break;
        }
        if(function == "insert") { //Insert at index function
            input = input.substr(input.find(space) + space.length()); //Iterates through input and finds the index, and then converts it to an int
            index = input.substr(0, input.find(space));
            int pos = stoi(index, nullptr, 10);

            input = input.substr(input.find(quote) + quote.length()); //Iterates through input and finds the string to be assigned to a node
            line = input.substr(0, input.find(quote));
            if(line.front() == '"') { //Deletes the quotes
                line.erase(0,1);
                line.erase(line.size()-1);
            }
            list.insert(pos, line); //Calls insert function

        } else if(function == "insertEnd") { //Inserts at end of list
            input = input.substr(input.find(quote) + quote.length()); //Iterates through input and finds the string to be assigned to a node
            line = input.substr(0, input.find(quote));
            if(line.front() == '"') {
                line.erase(0,1);
                line.erase(line.size()-1);
            }
            list.insertEnd(line); //Calls insertEnd function

        } else if(function == "delete") { //Deletes node
            input = input.substr(input.find(space) + space.length()); //Iterates through input and finds the index, and then converts it to an int
            index = input.substr(0, input.find(space));
            int pos = stoi(index, nullptr, 10);
            list.delNode(pos); //Calls delete function

        } else if(function == "print") { //Prints list
            list.print(); //Calls print function

        } else if (function == "search") { //Searches for nodes containing string
            input = input.substr(input.find(quote) + quote.length());
            line = input.substr(0, input.find(quote));
            if(line.front() == '"') {
                line.erase(0,1);
                line.erase(line.size()-1);
            }
            list.search(line); //Calls search function

        } else if(function == "edit") { //Edits the node at given index
            input = input.substr(input.find(space) + space.length()); //Iterates through input and finds the index, and then converts it to an int
            index = input.substr(0, input.find(space));
            int pos = stoi(index, nullptr, 10);

            input = input.substr(input.find(quote) + quote.length()); //Iterates through input and finds the string to be assigned to a node
            line = input.substr(0, input.find(quote));
            if(line.front() == '"') {
                line.erase(0,1);
                line.erase(line.size()-1);
            }
            list.edit(pos, line); //Calls edit function
        }
    }
}