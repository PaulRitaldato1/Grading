// Learning.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
using namespace std;

struct Node {

    Node* next = NULL;
    Node* prev = NULL; //node struct
    string text = ""; //this is really all you need for this project

};


class LinkedList{
    Node* head; //making this because we are supposed to
public:
    LinkedList(){
        head = new Node; //LinkedList just holds a head and functions
    }
    ~LinkedList();
    void insertEnd(string input);
    void insert(int index, string input);
    void edit(int index, string input);
    void search(string input);
    void deleteNode(int index);
    void print(int count);
};

void LinkedList::insertEnd(string input) {

    if(head -> text.empty()){
        head->text = input; //if the head doesn't hold anything, put it there.
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next; //iterate
    }
    Node* current = new Node;
    temp->next = current;
    current->prev = temp; //insert at the end
    current->text = input;

}

void LinkedList::insert(int index, string input) {

    Node* temp = head;
    Node* current = new Node;
    current->text = input;

    if(head -> text.empty() && index == 1){
        head->text = input; //if you're inserting for the head
        return;
    }

    if(index == 1){
        current->next = head;
        head->prev = current; //if you're inserting in front of the already existing head
        head = current;
        return;
    }



    for (int i = 1; i < index; i++) {
        if ((i + 1 == index) && temp->next == nullptr) {
            temp->next = current;
            current->prev = temp; //if you're inserting at the end
            return;
        }
        temp = temp->next; //iterate
    }
    current->prev = temp->prev;
    temp->prev->next = current; //move nodes around for insertion
    temp->prev = current;
    current->next = temp;
}

void LinkedList::edit(int index, string input) {
    Node* temp = head;
    for (int i = 1; i < index; i++) {
        temp = temp->next; //iterate
    }
    temp->text = input; //edit
}

void LinkedList::search(string input){
    Node* temp = head;
    int count = 1;
    bool check = false;
    while (temp != nullptr) {
        if (temp->text.find(input) != string::npos) { //check if string exists
            cout << to_string(count) << " " << temp->text << endl; //find & print the string you want
            check = true;
        }
        temp = temp->next; //iterate through nodes
        count++;
    }
    if (!check) { cout << "not found" << endl; }
}

void LinkedList::print(int count){
    Node* temp = head;
    for (int i = 0; i < count; i++) {
        cout << to_string(i + 1) << " " << temp->text << endl; //print all strings from nodes
        temp = temp->next;
    }
}

void LinkedList::deleteNode(int index) {
    Node* temp = head;

    if(index == 1){
        if(head->next == nullptr){head->text = ""; return;} //if you delete the last node, keep it, reset the text.
        head = head->next; //delete the head.
        delete temp;
        return;
    }

    for (int i = 1; i < index; i++) {
        temp = temp->next; //iterates
        if (temp == nullptr) { return; } //if you iterate to the end (extra error checking)
    }


    temp->prev->next = temp->next; //deleting temp
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev; //deleting temp if it's not the last node
    }
    delete temp; //goodbye
}

string spaceRemover(string bump){

//trimming solution I found online to get rid of extra spaces and tabs on ends of words
    string whitespace = " \t";
    if(bump.length() > 82){
        return bump;
    } //if it's too long, just return the full string
    //this will get caught by my error checker after the fact.


    int first = bump.find_first_not_of(whitespace);
    if (first == string::npos)
        return ""; //if there's no whitespace
    int last = bump.find_last_not_of(whitespace);
    int range = last - first + 1; //range between first and last letters in between the whitespace

    return bump.substr(first, range);


}

string quoteRemover(string bump) {

    string newString;

    if (bump[0] == bump[bump.length() - 1] && bump[0] == '"') { //if the string's first and last characters are quotes
        for (int i = 1; i < bump.length() - 1; i++) {
            newString += bump[i]; //make a new string without the quotes
        }
    }
    return newString;
}

bool errorChecker(string bump){

    if(bump.length() > 82){return false;}


    if(bump[0] != bump[bump.length()-1]){
        return false; //only continues if first and last characters are the same
    }

    return bump[0] == '"';


}

LinkedList::~LinkedList(){

    while(head!=nullptr){
        Node*temp = head;
        head=head->next;
        delete temp;

    }

}

int main()
{
    LinkedList List;
    int count = 0;
    unsigned int tempNum = 0;
    string userInput;
    string text;
    bool ok;  //for testing if input is incorrect
    start: //labelled the while loop
    while (cin) { //while there is further user input
        cin >> userInput;
        if (userInput == "insertEnd") {
            getline(cin, text); //get all text after "insertEnd"
            text = spaceRemover(text); //remove spaces before or after the string around the "s
            ok = errorChecker(text); //check if the remaining string breaks any rules
            if(ok) {
                text = quoteRemover(text); //remove the quotes, set new string
                if(text.empty()){text = " ";} //because now apparently empty string needs to display (space)
                List.insertEnd(text); //put text into new node
                count++; //increment count for how many nodes
            }
        }
        else if (userInput == "insert"){

            cin >> tempNum; //get number after insert
            if(!cin || tempNum == 0){ //if num >= 0 (because unsigned int) or if input a string
                cin.clear(); //clear cin
                cin.ignore(1000, '\n');
                tempNum = 0;
                goto start; //go to start (as opposed to putting the "real" code in an else loop)
            }
            getline(cin, text);
            text = spaceRemover(text);
            ok = errorChecker(text);
            if(tempNum > count+1){ok = false;} //if you try to add something past the last node + 1 (last is ok)
            if(ok) {
                text = quoteRemover(text);
                if(text.empty()){text = " ";}
                List.insert(tempNum, text);
                count++;
            }
        }
        else if (userInput == "edit") {
            cin >> tempNum;
            if(!cin || tempNum == 0){
                cin.clear();
                cin.ignore(1000, '\n');
                tempNum = 0;
                goto start;
            }
            if(tempNum>count){
                goto start;
            }
            getline(cin, text);
            text = spaceRemover(text);
            ok = errorChecker(text);
            if(ok){
                text = quoteRemover(text); //edit node's text
                if(text.empty()){text = " ";}
                List.edit(tempNum, text);
            }
        }
        else if (userInput == "print") {
            List.print(count);
        }
        else if (userInput == "search") {
            getline(cin, text);
            text = spaceRemover(text);
            ok = errorChecker(text);
            if (ok) {
                text = quoteRemover(text);
                List.search(text);
            }
        }
        else if (userInput == "delete") {
            cin >> tempNum;
            if(!cin || tempNum == 0){ //can't delete something that can't exist
                cin.clear();
                cin.ignore(1000, '\n');
                tempNum = 0;
                goto start;
            }
            if (tempNum <= count) { List.deleteNode(tempNum); count--; } //delete and decrement
        }
        else if (userInput == "quit") {
            return 0;
        }
    }


    return 0;
}

