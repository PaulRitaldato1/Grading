#include <iostream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* next = NULL;

    public:
        Node(){}
        Node(string line){ value = line; }
};

class LinkedList {
    public:
        Node* head;
        LinkedList(){
            head = new Node();
        }

    void push(string line){
        Node* current = this->head;
        if( current->value.empty() ){
            current->value = line;
        }else{
            while(current->next != NULL){
                current = current->next;
            }
            current->next = new Node(line);
        }
    }

    void insertNode(string line, int index){
        Node* current = this->head;
        int count = 1;

        // Move to the index prior to the correct index
        while( count < index-1 && current->next != NULL ){
            current = current->next;
            count+=1;
        }

        // Special case when inserting to the front of the linked list.
        if( index == 1 ){
            Node* insert = new Node(line);
            if( !current->value.empty() ){
                insert->next = current;
            }
            this->head = insert;
        } else {
            if( count == index -1 ){
                // Insert Node
                Node* temp = current->next;
                current->next = new Node(line);
                current = current->next;
                current->next = temp;
            }
        }
    }

    void deleteNode(int index){
        Node* current = this->head;
        int count = 1;

        // Check if the head is being deleted.
        if( index == 1 ){
            Node* temp = head;
            this->head = head->next;
            temp->next = NULL;
        }else{
            // Move to the index prior to the correct index.
            while( count < index-1 && current->next != NULL ){
                current = current->next;
                count+=1;
            }
            // Delete the node after the current one.
            Node* toDelete = current->next;
            if( toDelete == NULL ){
                // Index was invalid
            }else if( toDelete->next == NULL ){
                current->next = NULL;
            }else{
                current->next = toDelete->next;
            }
        }
    }

    void editNode(string line, int index){
        Node* current = this->head;
        int count = 1;
        // Move to the correct index
        while( count < index && current != NULL ){
            count+=1;
            current = current->next;
        }
        if( current != NULL ){
            current->value = line;
        }
    }

    void printNodes(){
        Node* current = this->head;
        int count = 1;
        // Iterate through Nodes and print line# + value
        while( current != NULL ){
            cout<<count<<" "<<current->value<<endl;
            count+=1;
            current = current->next;
        }
    }

    void search(string phrase){
        Node* current = this->head;
        int count = 1;
        bool found = false;
        // Iterate through Nodes and print line# + value
        while( current != NULL ){
            string sentence = current->value;
            if( sentence.find(phrase) != std::string::npos ){
                found = true;
                cout<<count<<" "<<current->value<<endl;
            }
            count+=1;
            current = current->next;
        }
        if( !found ){
            cout<<"not found"<<endl;
        }
    }
};

class LineEditor {
    private:
        LinkedList* lines;

    public:
        bool quit = false;
        LineEditor(){
            lines = new LinkedList();
        }

        void readCommand(string line){
            string command;
            // Determine which command to execute.
            int endOfCommand = line.find(" ");
            if( endOfCommand != std::string::npos ){
                command = line.substr(0, endOfCommand);
            }else{
                command = line;
            }

            int index;
            string sentence;
            int sentenceLength = line.length() - endOfCommand;
            // Execute the proper command.
            if( command == "insertEnd" ){
                //Extract the sentence, without the quotes.
                sentence = line.substr(endOfCommand + 2, sentenceLength-3);
                lines->push(sentence);
            } else if( command == "insert" ){
                string newLine = line.substr(endOfCommand+1);
                int indexOfSpace = newLine.find(" ");
                string indexStr = newLine.substr(0, indexOfSpace);
                index = std::stoi(indexStr);
                newLine = newLine.substr(indexOfSpace+1);
                sentence = newLine.substr(1, newLine.length()-2);
                lines->insertNode(sentence, index);
            } else if( command == "delete" ){
                string indexStr = line.substr(endOfCommand+1);
                index = std::stoi(indexStr);
                lines->deleteNode(index);
            } else if( command == "edit" ){
                string newLine = line.substr(endOfCommand+1);
                int indexOfSpace = newLine.find(" ");
                string indexStr = newLine.substr(0, indexOfSpace);
                index = std::stoi(indexStr);
                newLine = newLine.substr(indexOfSpace+1);
                sentence = newLine.substr(1, newLine.length()-2);
                lines->editNode(sentence, index);
            } else if( command == "print" ){
                lines->printNodes();
            } else if( command == "search" ){
                string newLine = line.substr(endOfCommand+1);
                sentence = newLine.substr(1, newLine.length() - 2);
                lines->search(sentence);
            } else if( command == "quit" ){
                this->quit = true;
            }
        }
};

int main()
{
    LineEditor* editor = new LineEditor();
    string line;

    while(std::getline(cin, line) && editor->quit == false) {
        editor->readCommand(line);
    }
}
