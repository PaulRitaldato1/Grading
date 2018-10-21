#include <string>
#include <iostream>
using namespace std;

class Node {
public:
    string text;
    Node* next;
};

class LinkedList {
public:			//declarations for linked list
    int len;
    Node* head;
    Node* tail;
    LinkedList();
    void insertEnd(string text);
    void insert(string text, int index);
    void remove(int index);
    void edit(string text, int index);
    string print();
    string search(string text);
};

LinkedList::LinkedList() {	//constructor
    this->len = 0;
    this->head = NULL;
}

void LinkedList::insertEnd(string text) {
    if(head == NULL) {	//inserting if list is empty
        head = new Node;
        head->text = text;
        tail = head;
    }
    else {				//otherwise becomes new tail
        tail->next = new Node;
        tail->next->text = text;
        tail = tail->next;
    }
}
void LinkedList::insert(string text, int index) {
    Node* insert = new Node;
    insert->text = text;
    index -= 1;	//decrement since user input is now 0 indexed
    if (index == 0){ //if inserting to the first element make new head
        insert->next = head;
        head = insert;
    }
    else {
        Node* temp = head;
        for (int i = 0; i < index - 1; i++) { //iterate through list
            temp = temp->next;
        }
        if (temp ==NULL) //make sure the index does not exceed list size
            return;
        if (temp -> next == NULL) { //logic if it is the last element
            temp->next = insert;
            tail = insert;
        }
        else {
            insert->next = temp->next; 
            temp->next = insert;
        }
    }

}
void LinkedList::remove(int index) {
   Node* temp = head;
    index -= 1;
    if (index == 0){//delete logic if first element
        head = temp->next;
        free(temp);
    }
    else{
        for (int i = 0; temp!= NULL && i < index - 1; i++){//iterate to get to required index
            temp = temp->next;
        }
        if (temp ==NULL || temp->next == NULL)//ensure index doesnt exceed size
            return;

        Node* next = temp->next->next; //skip over node to be deleted
       
        free(temp->next); //free node deleted
        temp->next=next; //make previous node connect to two nodes away
         if (temp->next == NULL)
            tail = temp;
        else
            tail = next;
    
    }
        
}
void LinkedList::edit(string text, int index) {
    Node* temp = head;
    if (index == 0){//if the index is the first element
        head->text = text;
    }
    else{//iterate through list to find specified index
        for (int i = 0; temp!= NULL && i < index - 1; i++){
            temp = temp->next;
        }
        if (temp ==NULL )
            return;
        temp->text = text;
    }
}
string LinkedList::print() {
    string output;
    int count = 1;
    Node* temp = head;
    if (temp != NULL) { //if list is not empty
        while (temp != NULL) { //iterate through and print each
            output = output  + to_string(count) + " " + temp->text + "\n";
            temp=temp->next;
            count++;
        }
    }
    return output;
}
string LinkedList::search(string text) {
    Node* temp = head;
    string output;
    int count = 1;
    bool found = false;
    while (temp!= NULL){ //iterate through each to find match
        if (temp->text.find(text) != string::npos) {
            output = output + to_string(count) + " " + temp->text + "\n";
            found = true;
        }
        temp=temp->next;
        count++;
    }
    if (!found) //if match is not found output not found
        output = "not found\n";
    return output;
}



string getCommandText(string userInput){
	//splits string to get the text
    return userInput.substr(userInput.find(" ") + 1);
}

string trimQuotation(string commandText) {
	//trims quotes
    return commandText.substr(1, commandText.length() - 2);
}



int main() {
    bool loop = true;
    LinkedList* myLinkedList = new LinkedList;
    string input;
    while (loop) {
        getline(cin, input);

        //insertEnd
        if (input.substr(0,9) == "insertEnd") {
			if (trimQuotation(getCommandText(input)).size() <= 80)
				myLinkedList->insertEnd(trimQuotation(getCommandText(input)));
        }
        //insert
        else if ((input.substr(0,6) == "insert") && (input.substr(0,9) != "insertEnd")) {
            string command = getCommandText(input);
            int index = stoi(command.substr(0,1));
            command = command.substr(2,command.length() - 2);
			if (trimQuotation(command).size() <= 80)
				myLinkedList->insert(trimQuotation(command), index);
        }
        //delete
        else if (input.substr(0,6) == "delete") {
            int index = stoi(input.substr(7, 1));
            myLinkedList->remove(index);
        }
        //print
        else if (input.substr(0,5) == "print") {
            cout << myLinkedList->print();
        }
        //search
        else if (input.substr(0,6) == "search") {
            string searchText = getCommandText(input);
            cout << myLinkedList->search(trimQuotation(searchText));
        }
        //edit
        else if (input.substr(0,4) == "edit") {
            string replaceText = getCommandText(input);
            int index = stoi(replaceText.substr(0,1));
            replaceText = replaceText.substr(2,replaceText.length() - 2);
			if (trimQuotation(replaceText).size() <= 80)
				myLinkedList->edit(trimQuotation(replaceText), index);
        }
        else if (input.substr(0,4) == "quit") {
            loop = false;
        }
        else
            cout<< "please check your spelling";
    }
    return 0;
}