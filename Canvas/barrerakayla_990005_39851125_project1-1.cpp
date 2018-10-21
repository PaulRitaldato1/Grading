#include <stddef.h>
#include <iostream>

using namespace std;

struct Node {
  string value;
  Node *next;
};

class LinkedList {
  public:
  //methods
    void insertEnd(string input);
    void insert(int index, string input);
    void deleteNode(int index);
    void edit(int index, string newText);
    void print();
    void search(string query);


  private:
    Node *head;
};



void LinkedList::insertEnd(string input) {
    Node* curr = new Node();
    Node* newNode = new Node();
    newNode->value = input;

    curr = head;

    if (head == NULL) {
      curr = newNode;
      head = newNode;
      curr->next = NULL;
    }

    else {
      while (curr->next != NULL) {
        curr = curr->next;
      }
      curr->next = newNode;
    }

}

void LinkedList::insert(int index, string input) {
    Node* curr = new Node();
    Node* newNode = new Node();
    Node* next = new Node();
    curr = head;
    newNode->value = input;

      if (index == 0) { //insert at head node
        head = newNode;
        newNode->next = curr;
      }
      else {
        for (int i = 0; i < index - 1; i++) {
          if (curr->next == NULL) {
            //cout<<"Index out of range"<<endl;
            return;
          }

          if (head == NULL) {
            curr = newNode;
            head = newNode;
            curr->next = NULL;
            return;
          }

          else {
            curr = curr->next;
          }
        }

        next = curr->next;
        curr->next = newNode;
        newNode->next = next;


      }
}

void LinkedList::deleteNode(int index) {

  Node* curr = new Node();
  Node* prev = new Node();

  curr = head;
  prev = head;

  for (int i = 0; i < index; i++) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      //cout<<"Index out of range"<<endl;
      return;
    }
  }

  if (curr->next != NULL) { //in the middle
    prev->next = curr->next;
  }

  if (curr->next == NULL) { //at the end
    prev->next = NULL;
  }

  if (curr == head) { //at the head
    head = head->next;
  }
}

void LinkedList::edit(int index, string newText) {
    deleteNode(index);
    insert(index, newText);
}

void LinkedList::print() {
    Node* curr = new Node();
    curr = head;
    int counter = 1;

    while (curr != NULL) {
        cout<<counter<<" "<<curr->value<<endl;
        curr = curr->next;
        counter++;
    }
}

void LinkedList::search(string query) {
    bool found = false;
    Node* curr = new Node();
    curr = head;
    int counter = 1;

    while (curr != NULL) {
        if (curr->value.find(query) != -1) {
            found = true;
            cout<<counter<<" "<<curr->value<<endl;
        }
        curr = curr->next;
        counter++;
    }

    if (!found) {
      cout<<"not found"<<endl;
    }
}

string stringAfterSpace(string word){
  for(unsigned int i = 0; i < word.size(); i++) {// Returns the string found after a space
    if (isspace(word[i])) {
      return word.substr(i+1);
    }
  }
    return "";

}

string stringBeforeSpace(string word){
    for (unsigned int i = 0; i < word.size(); i++) {// Returns the string before space is encountered
        if (isspace(word[i]))
        return word.substr(0,i);
    }
    return word;
}

string removeQuotes(string word) {
  return word.substr(1,word.size()-2);
  // Removes quotes from input
}

int main()
{
    LinkedList *linkedList = new LinkedList();

    string userInput = "";
    string command = "";
    string input = "";
    int index;

    while (command != "quit") {

      getline(cin,userInput);

      command = stringBeforeSpace(userInput);

      //InsertEnd
      if (command == "insertEnd") {

        input = stringAfterSpace(userInput);
        input = removeQuotes(input);

        if (input.length() > 80) {
          cout<<"Line too long. Maximum limit is 80 characters."<<endl;
          continue;
        }
        linkedList->insertEnd(input);
        continue;

      }


      //Print
      if (command == "print") {
        linkedList->print();
        continue;
      }


      //Insert
      if (command == "insert") { 
        index = stoi(userInput.substr(7)) - 1;
        input = removeQuotes(stringAfterSpace(stringAfterSpace(userInput)));

        if (index < 0) {
          cout<<"Please enter a valid line number"<<endl;
          continue;
        }

        if (input.length() > 80) {
          cout<<"Line too long. Maximum limit is 80 characters."<<endl;
          continue;
        }
        linkedList->insert(index,input);
        continue;
      }

      //Delete
      if (command == "delete") { //TODO: Catch invalid input that is not an int for index
        index = stoi(userInput.substr(7)) - 1;

        if (index < 0) {
          cout<<"Please enter a valid line number"<<endl;
          continue;
        }

        linkedList->deleteNode(index);
        continue;
      }

      //Edit
      if (command == "edit") {
          index = stoi(userInput.substr(5)) - 1;
          input = removeQuotes(stringAfterSpace(stringAfterSpace(userInput)));

          if (index < 0) {
            cout<<"Please enter a valid line number"<<endl;
            continue;
          }

          if (input.length() > 80) {
            cout<<"Line too long. Maximum limit is 80 characters."<<endl;
            continue;
          }

          linkedList->edit(index,input);
          continue;
      }

      //Search
      if (command == "search") {
        input = stringAfterSpace(userInput);
        input = removeQuotes(input);
        linkedList->search(input);
        continue;
      }

      else if (command != "quit") {
        cout<<"Invalid input, please enter a command"<<endl;
        continue;
      }


    }



    return 0;

}
