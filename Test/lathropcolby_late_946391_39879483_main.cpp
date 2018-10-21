
#include <iostream>
#include <string>
using namespace std;


class list {
    struct Node {
        string data;
        Node* next;
    };

private:

    Node* head;
    Node* tail;

public:

    list() {

        head = NULL;
        tail = NULL;
    }

    Node* makeNode(string phrase) {

        Node *temp = new Node;
        temp->data = phrase;
        temp->next = NULL;
        return temp;

    }

    void insertEnd(string line) {

        Node *temp = makeNode(line);

        if (head == NULL) {
            head = temp;
            tail = temp;
        }

        else {
            tail->next = temp;
            tail = temp;
        }
    }

    void insertPosition(int pos, string message)

    {
        Node* old = new Node;
        Node* updated = head;
        Node* temp = makeNode(message);

        for (int i = 1; i < pos; i++)
        {
            old = updated;
            updated = updated->next;
        }

        old->next = temp;
        temp->next = updated;
    }


    void deleteNode(int pos) {

        Node* old = new Node;
        Node* updated = head;

        for (int i = 1; i < pos; i++) {
            old = updated;
            updated = updated->next;
        }

        old->next = updated->next;

    }


    void editNode(int pos, string message) {

        Node *temp = head;
        for (int i = 1; i != pos; i++) {
            temp = temp->next;
        }
        temp->data = message;

    }

    void printList(int nodeCount) {

        Node *temp = head;

        for (int i = 1; i <= nodeCount; i++) {
            cout << i << " " << temp->data << "\n";
            temp = temp->next;
        }

    }


    void search(string key, int nodeCount) {

        Node* temp = head;

        for (int i = 1; i <= nodeCount; i++) {
            if (temp->data.find(key) != string::npos) {
                cout << i << " " << temp->data << endl;
                return;
            }
            temp = temp->next;

        }

        cout << "not found" << endl;
    }

};

int main() {

    list doc;
    int nodeCount = 0;
    int lineNum = 0;
    string input;
    string numString;

    cout << "Enter commands below: " << endl;
    while(true) {

        getline(cin, input);

        if (input == "quit") {
            break;
        }

        else if (input == "print") {
            doc.printList(nodeCount);
        }

        else {

            string command;

            //Get which command to use
            for (int i = 0; input[i] != ' ';) {
                command = command + input[i];
                input = input.substr(1);
            }

            if (command == "insertEnd") {

                //Get the message and insert it.
                while (true) {
                    if (input[0] == '"') {
                        break;
                    }
                    input = input.substr(1);
                }
                input = input.substr(0, (input.length()));

                if (input.length() < 80) {
                    nodeCount++;
                    doc.insertEnd(input);
                }
            }

            else if (command == "insert") {

                while (input[0] == ' ') {
                    input = input.substr(1);
                }

                //Get which line number to insert at as an int
                for (int i = 0; input[i] != ' ';) {
                    numString = numString + input[i];
                    input = input.substr(1);
                }
                lineNum = stoi(numString);

                //get message and insert node
                while (true) {
                    if (input[0] == '"') {
                        break;
                    }
                    input = input.substr(1);
                }
                input = input.substr(0, (input.length()));

                if (lineNum <= nodeCount + 1 && input.length() < 80) {
                    doc.insertPosition(lineNum, input);
                    nodeCount++;
                }

            }

            else if (command == "delete") {

                //get line number to delete and delete
                while (input[0] == ' ') {
                    input = input.substr(1);
                }

                lineNum = stoi(input);

                if (lineNum <= nodeCount) {
                    doc.deleteNode(lineNum);
                    nodeCount--;
                }

            }

            else if (command == "edit") {
                while (input[0] == ' ') {
                    input = input.substr(1);
                }

                //Get which line number to insert at as an int
                for (int i = 0; input[i] != ' ';) {
                    numString = numString + input[i];
                    input = input.substr(1);
                }
                lineNum = stoi(numString);

                //get message and insert node
                while (true) {
                    if (input[0] == '"') {
                        break;
                    }
                    input = input.substr(1);
                }
                input = input.substr(0, (input.length()));

                if (lineNum <= nodeCount && input.length() < 80) {
                    doc.editNode(lineNum, input);
                }
            }

            else if (command == "search") {

                //get message and search
                while (true) {
                    if (input[0] == '"') {
                        break;
                    }
                    input = input.substr(1);
                }
                input = input.substr(0, (input.length()));

                doc.search(input, nodeCount);
            }

            //else give error message
            else {
                cout << "Invalid Output" << endl;
            }
        }

    }

}