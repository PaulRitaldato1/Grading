#include <iostream>
using namespace std;

////////////////////////////////////////
/////////////LINKED LIST////////////////
////////////////////////////////////////

class Node {
  string data;
  Node* next;
public:
  Node(string a) {
    data = a;
    next = NULL;
  }
  void addData(string a) {
    this->data = a;
  }
  void addNext(Node* x) {
    this->next = x;
  }
  string getData() {
    return this->data;
  }
  Node* getNext() {
    return this->next;
  }
};

class LinkedList {
  Node* head;
  int size;
public:
  LinkedList () {
    Node* head = NULL;
    size = 0;
  }
  void addHead(Node* x) {
    this->head = x;
  }
  void gotBigger() {
    this->size++;
  }
  void gotSmaller() {
    this->size--;
  }
  Node* getHead(){
    return this->head;
  }
  int getSize() {
    return this->size;
  }
};

/////////////////////////////////////////
//////////////LINE EDITOR////////////////
/////////////////////////////////////////

static string getCommand(string a) {
  for (int i=0; i<a.length(); i++) {
    if (a[i] == '\"') {
      return a.substr(0, i-1);
    }
  }
  return a;
};
static string getText(string a) {
  int start = a.find("\"") + 1;
  int end = a.find("\"", start) - start;
  return a.substr(start, end);
};

static void executeCommand(string a, string b, LinkedList* x) {
  ///////////////////////////////////////
  //////////////INSERT END///////////////
  if (a.substr(0, 7) == "insertE") {
    if (x->getSize() == 0){
      x->addHead(new Node(b));
      x->gotBigger();
      return;
    }
    else {
      Node* temp = x->getHead();
      for (int i=1; i<(x->getSize());i++) {
        temp = temp->getNext();
      }
      temp->addNext(new Node(b));
      x->gotBigger();
      return;
    }
  }
  /////////////////////////////////////
  /////////////INSERT//////////////////
  else if (a.substr(0, 7) == "insert ") {
    int pos = stoi(a.substr(7, a.find("\"")));
    if (pos > x->getSize()+1) {
      return;
    }
    else if (pos == 1) {
      Node* temp = x->getHead();
      x->addHead(new Node(b));
      x->getHead()->addNext(temp);
      x->gotBigger();
      return;
    }
    else {
      Node* temp1 = x->getHead();
      Node* temp2;
      for (int i=2; i<pos; i++) {
        temp1 = temp1->getNext();
      }
      temp2 = temp1->getNext();
      temp1->addNext(new Node(b));
      temp1->getNext()->addNext(temp2);
      x->gotBigger();
      return;
    }
  }
  //////////////////////////////////////
  //////////////EDIT////////////////////
  else if (a.substr(0, 4) == "edit") {
    int pos = stoi(a.substr(5, a.find("\"")));
    if (pos > x->getSize()) {
      return;
    }
    else {
      Node* temp1 = x->getHead();
      for (int i=1; i<pos; i++) {
        temp1 = temp1->getNext();
      }
      temp1->addData(b);
      return;
    }
  }
  /////////////////////////////////////
  /////////////DELETE//////////////////
  else if (a.substr(0, 6) == "delete") {
    int pos = stoi(a.substr(7));
    if (pos > x->getSize()) {
      return;
    }
    else if (pos == 1) {
      x->addHead(x->getHead()->getNext());
      x->gotSmaller();
      return;
    }
    else {
      Node* temp = x->getHead();
      for (int i=2; i<pos; i++) {
        temp = temp->getNext();
      }
      temp->addNext(temp->getNext()->getNext());
      x->gotSmaller();
      return;
    }
  }
  //////////////////////////////////////
  //////////////SEARCH//////////////////
  else if (a.substr(0, 6) == "search") {
    Node* temp = x->getHead();
    bool wasFound = false;
    for (int i=1; i<(x->getSize() + 1); i++) {
      if ((temp->getData().find(b) + 1) != 0) {
        cout << i << " " + temp->getData() << endl;
        wasFound = true;
      }
      temp = temp->getNext();
    }
    if (wasFound == false) {
      cout << "not found" << endl;
    }
    return;
  }
  /////////////////////////////////////
  ///////////////PRINT/////////////////
  else if (a.substr(0, 5) == "print") {
    Node* temp = x->getHead();
    for (int i=1; i<(x->getSize() + 1); i++) {
      cout << i << " " + temp->getData() << endl;
      temp = temp->getNext();
    }
    return;
  }
  /////////////////////////////////////
  ///////////////QUIT//////////////////
  else if (a.substr(0, 4) == "quit") {
    exit(0);
  }
  /////////////////////////////////////
  ///////////INCORRECT INPUT///////////
  else {
    return;
  }

  return;
};

///////////////////////////////////////
///////////////MAIN////////////////////
///////////////////////////////////////

int main() {
  string input;
  string command;
  string text;
  LinkedList* LineEditor = new LinkedList;
  while(true){
    getline(cin, input);
    command = getCommand(input);
    text = getText(input);
    executeCommand(command, text, LineEditor);
  }
  return 0;
};
