#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Node{

public:
    Node* next = NULL;
    Node* previous;
    int lineNum;
    string text;

public :
    Node(int lineNumber, string line){
        lineNum = lineNumber;
        text = line;
    }
};

class LinkedList{
    Node*head = NULL;

    public:
        void insertEnd(string insertText){
            int lineCounter = 1;

            Node* current = head;
            if(head == NULL){
                head = new Node(lineCounter, insertText);
            }
            else {
                while (current->next != NULL) {
                    lineCounter++;
                    current = current->next;
                }
                //Create new Node
                lineCounter++;
                Node *newNode = new Node(lineCounter, insertText);
                current->next = newNode;
            }
        }

        void insert (int insertAt, string insertSpecific){
            int insertCounter = 1;
            Node* current = head;
            if(head == NULL){
                head = new Node(insertCounter, insertSpecific);
            }

            while(current != NULL){
                //knows that current is before of the node we want to insert at
                current->lineNum = insertCounter;
                if(insertCounter+1 == insertAt){
                    Node*temp = current->next;
                    Node *newNode = new Node(insertAt, insertSpecific);
                    current->next = newNode;
                    newNode->next = temp;
                }
                insertCounter++;
                current = current->next;
            }
        }

        void deleteAt (int deleteNum){
            int deleteCounter = 1;
            Node* current = head;

            if(deleteNum == 1){
                head = current->next;
            }

            for(int i = 0; current != NULL && i < deleteNum-2; i++){
                current = current->next;
            }

            if(current == NULL || current->next == NULL){
                return;
            }

            current->next = current->next->next;

            current = head;
            while(current != NULL){

                current->lineNum = deleteCounter;
                deleteCounter++;
                current = current->next;
            }
        }

        void edit (int editNum, string editText){
            int lineCounter = 0;
            Node* current = head;
            while(current != NULL){
                lineCounter++;
                if(lineCounter == editNum){
                    current->text = editText;
                }
                current = current->next;
            }
        }

        void print(){
            Node* current = head;
            while(current != NULL){
                std::cout << current->lineNum <<" "<< current-> text<< std::endl;
                current = current->next;
            }
        }

        void search(string searchText){
            Node* current = head;
            int boolean = 0;
            while(current != NULL) {

                //if string is found
                if (current->text.find(searchText)!= std::string::npos) {
                    std::cout<<current->lineNum<<" "<<current->text<<std::endl;
                    boolean = 1;
                }
                current = current->next;
            }
            if(boolean == 0){
                cout<<"not found"<<endl;
            }
        }

};

int main() {

    LinkedList a;

    string input;

    while(input != "quit") {
        std::cin>>input;

        if(input == "insertEnd"){
            getline(cin, input);
            input = (input.substr(2, input.length() - (input.find(" ")+3)));
            a.insertEnd(input);
        }
        else if (input == "insert"){
            int number;
            std::cin>>number;
            getline(cin, input);
            input = input.substr(2,input.length() - (input.find(" ")+3));
            a.insert(number, input);
        }
        else if(input == "delete"){
            int number;
            std::cin>>number;
            a.deleteAt(number);
        }
        else if(input == "edit"){
            int number;
            std::cin>>number;
            getline(cin, input);
            input = input.substr(2,input.length() - (input.find(" ")+3));
            a.edit(number, input);
        }
        else if(input == "print"){
            a.print();

        }
        else if(input == "search"){
            getline(cin, input);
            input = (input.substr(2, input.length() - (input.find(" ")+3)));
            a.search(input);
        }

  }
    return 0;
}

