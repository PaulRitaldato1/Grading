#include <iostream>
#include <string>

using namespace std;

//Node and linked list implementation
class Node{
  public:
    string data;
    Node* next;
};
class LinkedList{
  private:
    int size;
    Node* head;
  public:
    void appendNode(string text);
    void insertNode(string text, int lineNumber);
    void deleteNode(int lineNumber);
    void print();
    void editNode(string text, int lineNumber);
    void searchText(string text);
};

//Handles inserting a new line at the end of the list
void LinkedList::appendNode(string text){
  if(head == NULL){
    Node* newNode = new Node();
    newNode -> data = text;
    head = newNode;
    newNode -> next = NULL;
    size++;
    return;
  }
  Node* newNode = head;
  while(newNode -> next != NULL){
    newNode = newNode -> next;
  }
  newNode -> next = new Node();
  newNode -> next -> data = text;
  size++;
}

//Handles inserting a new line at a certain index
void LinkedList::insertNode(string text, int lineNumber){
  if(lineNumber > size + 1 || lineNumber <= 0){
    return;
  }
  Node* currentNode = head;
  for(int i = 1; i < lineNumber - 1; i++){
    currentNode = currentNode -> next;
  }
  Node* insertedNode = new Node();
  insertedNode -> data = text;
  insertedNode -> next = currentNode -> next;
  currentNode -> next = insertedNode;
  size++;
}

//Handles deleting a certain line
void LinkedList::deleteNode(int lineNumber){
  if(lineNumber > size || lineNumber <= 0){
    return;
  }
  Node* currentNode = head;
  if(lineNumber == 1){
    head = head -> next;
    delete currentNode;
    size--;
    return;
  }
  for(int i = 1; i < lineNumber-1; i++){
    currentNode = currentNode -> next;
  }
  Node* temp = currentNode -> next;
  currentNode -> next = temp -> next;
  delete temp;
  size--;
}

//Edits a node with a new string at a specific index
void LinkedList::editNode(string text, int lineNumber){
  if(text.length() > 80){
    cout << "Invalid string length.\nKeep string length at or below 80 characters." << endl;
    return;
  }
  if(lineNumber > size || lineNumber <= 0){
    cout << "No line found" << endl;
    return;
  }
  Node* currentNode = head;
  for(int i = 1; i < lineNumber; i++){
    currentNode = currentNode -> next;
  }
  currentNode -> data = text;
}

//Prints the current list
void LinkedList::print(){
  Node* currentNode = head;
  for(int i = 0; i < size; i++){
    cout << i+1 << " " << currentNode -> data << endl;
    currentNode = currentNode -> next;
  }
}

//Searches for a substring within the different lines and returns the line if found
void LinkedList::searchText(string text){
  Node* currentNode = head;
  bool foundText = false;
  for(int i = 1; i < size+1; i++){
    string nodeData = currentNode -> data;
    for(int j = 0; j < nodeData.length() - text.length()+1; j++){
      if(nodeData.substr(j, text.length()) == text){
        cout << i << " " << currentNode -> data << endl;
        foundText = true;
      }
    }
    currentNode = currentNode -> next;
  }
  if(foundText != true){
    cout << "not found" << endl;
  }
}

//Removes extra spaces before the string occurs and removes quotations and returns it
string updatedString(string text){
  string updatedString;
  for(int i = 0; i < text.length(); i++){
    if(text[i] == '"'){
      updatedString = text.substr(i+1, text.length()-3);
      break;
    }
  }
  return updatedString;
}

//Main method
int main(){
  LinkedList* linkedlist = new LinkedList();
  string inpCommand;
  bool quit = false;
  while(!quit){
    cin >> inpCommand;

    //Each if statement handles a different command
    if(inpCommand == "insertEnd"){
      string text;
      getline(cin, text);
      string newString = updatedString(text);
      linkedlist -> appendNode(newString);
    }
    else if(inpCommand == "insert"){
      int nodeNum;
      cin >> nodeNum;
      string text;
      getline(cin, text);
      string newString = updatedString(text);
      linkedlist -> insertNode(newString,nodeNum);
    }
    else if(inpCommand == "delete"){
      int nodeNum;
      cin >> nodeNum;
      linkedlist -> deleteNode(nodeNum);
    }
    else if(inpCommand == "edit"){
      int nodeNum;
      cin >> nodeNum;
      string newText;
      getline(cin, newText);
      string newString = updatedString(newText);
      linkedlist -> editNode(newString,nodeNum);
    }
    else if(inpCommand == "print"){
      linkedlist -> print();
    }
    else if(inpCommand == "search"){
      string text;
      getline(cin, text);
      string newString = updatedString(text);
      linkedlist -> searchText(newString);
    }
    else if(inpCommand == "quit"){
      quit = true;
    }
    else{
      cout << "Invalid command" << endl;
      cin.clear();
    }
  }
  return 0;
}
