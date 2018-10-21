#include <iostream>
using namespace std;
#include <string>
#include <sstream>

struct Node{

public:
    string data;                            //node struct for each node's data and
    Node* next;                             //a pointer to the next node.

};

class LinkedList{
public:

    Node* head;

    LinkedList(){
        head = nullptr;

    }

    void insertEnd(string message){

        Node* temp = new Node;              //insertEnd takes in a string and immediately sets a newly made node's
        temp->data = message;               //data equal to the string.
        temp->next= nullptr;

        if(head == nullptr){                //first checks for an empty list
            head = temp;
        }
        else {
            Node *temp2 = head;             //if the list is not empty, temp2 will traverse the list until null is hit,
            while (temp2->next != nullptr) {//then the string is placed.
                temp2 = temp2->next;
            }

            temp2->next = temp;
        }
    }

    void insertNode(int index, string message){

        if (index >= getSize() + 2){        //first checks to see if the index is larger than the size of the list.
            return;
        }
        Node* temp = new Node;
        temp->data = message;
        if(index == 1){                     //creates new node and places the inputted string as it's data.
            temp->next = head;
            head = temp;                    //first step checks the head of the list if the index is 1.
        }
        else {
            Node *nextTemp = head;
            int count = 2;                  //next step sets up a while loop to run until the counter is equal to the
            while (count!= index){          //desired index.
                nextTemp=nextTemp->next;
                count++;                    //once the desired index is found, the temp node is then linked to the
            }                               //correct node.
            temp->next=nextTemp->next;
            nextTemp->next=temp;
        }
    }

    void search(string message) {

        Node *temp = head;
        int count = 1;

        if (temp->data.find(message) != std::string::npos) {        //uses string.find in order to search for a substring
            cout << count << " " << temp->data << endl;             //within the given string at the head first.
        }
        while (temp->next != nullptr) {
            count++;                                                //traverses the node throughout the list, checking
            temp = temp->next;                                      //each index for the desired substring.

            if (temp->data.find(message) != std::string::npos) {
                cout << count << " " << temp->data;
                return;
            }
        }
        if (temp->data.find(message) == std::string::npos){         //if substring isn't found, print "not found" to user.
            cout << "not found" << endl;
        }
    }

    void deleteNode(int index){

        if (index > getSize()){             //checks to see if the desired index is larger than the size of the list.
            return;
        }

        Node* temp = head;
        if (index == 0){
            head = temp-> next;             //goes to head node if index is 0 and deletes it.
            free(temp);
            return;
        }
        for(int i = 0; i < index-2; i++){   //for loop to reach the desired index.
            temp = temp->next;
        }
        Node* nextTemp = temp->next;        //links nextTemp with the node I traversed to and deletes it.
        temp->next = nextTemp->next;
        free(nextTemp);
    }

    void edit(int index, string message){

        Node* temp = head;
        if (index == 0){                    //checks index for 0 to edit the head of the list.
            temp -> data = message;
        }
        else {
            for (int i = 0; i <= index - 2 ; i++) {               //traverses the list for desired node index.
                temp = temp->next;
            }
            temp->data = message;                                //sets the desired node's data equal to the inputted string.
        }
    }

    void printDocument(){

        Node* temp = head;
        int count = 1;
        while (temp !=nullptr){
            cout << count << " " << temp->data << endl;     //creates a new node and after each print statement,
            temp=temp->next;                                //points the node to the new node.
            count++;
        }
    };

    int getSize() {

        Node *temp = head;                  //getSize creates a node and each time the node's -> next != null,
        int counter = 1;                    //the counter is incremented by 1.
        if (head == nullptr) {
            return 0;
        } else {
            while (temp->next != nullptr) {
                counter++;
                temp = temp->next;
            }                               //once the end of the list is reached and ->next = null,
            return counter;                 //it will return the size.
        }
    }
};

int getNumber(string input){

    stringstream stream1;
    stream1 << input;
    //getNumber utilizes a 'stringstream' to extract the integer values
    string word;                            //from the user's input.
    int number;

    while(!stream1.eof()){
        stream1 >> word;

        if (stringstream(word) >> number){
            return number;
        }
        word = "";
    }
}

int main() {

    LinkedList *newList = new LinkedList;
    string userInput;
    while (userInput != "quit") {

        getline(cin, userInput);

        auto firstWord = userInput.substr(0, userInput.find(' '));      //these few lines have the job of searching for the words
        auto secondWord = userInput.substr(userInput.find('"') + 1);    //in between the quotations using string.find and manipulating
        secondWord = secondWord.substr(0, secondWord.find('"'));        //multiple substrings of the input.

        if (userInput.substr(0, 9) == "insertEnd") {
            newList->insertEnd(secondWord);
        }
        else if (userInput.substr(0,6) == "insert"){
            newList->insertNode(getNumber(userInput), secondWord);      //each if statement checks for a different user input
        }                                                               //using the substrings from the above block, and acts
            // on the list accordingly
        else if (userInput.substr(0,4) == "edit"){
            newList->edit(getNumber(userInput), secondWord);
        }
        else if (userInput.substr(0,6) == "search"){
            newList->search(secondWord);
        }
        else if (userInput.substr(0, 5) == "print") {
            newList->printDocument();
        }
        else if( userInput.substr(0,6) == "delete"){

            newList->deleteNode(getNumber(userInput));
        }
        else if (userInput.substr(0, 4) == "quit") {
            exit(0);
        }
    }
}