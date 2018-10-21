#include <iostream>
#include <string>
using namespace std;

class LinkedList{

  public:

  struct Node{
    Node* next;
    Node* prev;
    string data;
  };

  Node* head;
  Node* tail;
  unsigned int size;

  LinkedList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  void AddTail (string Data ){

    size++;
    Node *n = new Node;
    n->data = Data;
    if (tail == nullptr)
    {
        head = tail = n;
    }
    else
    {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
  }

  void AddHead (string Data){

    size++;
    Node *n = new Node;
    n->data = Data;
    if (head == nullptr)
    {
        head = tail = n;
    }
    else
    {
        n->next = head;
        head->prev = n;
        head = n;
    }    
  }

  void RemoveHead(){
    if (head == nullptr){
      cout<< "Index Errror!" << endl;
    }

    else
    if (size == 1) {
      delete head;
      head = tail = nullptr;
    }

    else 
    if (size > 1) {
      Node *temp = head->next;
      delete head;
      head = temp;
      head->prev = nullptr;
    }
    
    size--;
  }

  void RemoveTail(){
    if (head == nullptr){
      cout<< "Index Errror!" << endl;
    }
    else
    {
      if (size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
      }
      
    else {
      if  (size > 1){
            Node *temp = tail->prev;
            tail->next = nullptr;
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        
        size--;
    }
    }
  }

  void InsertAt(unsigned int index, string Data){
      
    if (index > size)
      return;

    if (index == 0){
        AddHead(Data);
    }
    else if (index >= size){
      AddTail(Data);
    }
    else{

      Node *n = head;

      for (unsigned int i = 0; i < index; i++){
        n = n->next;
      }

       size++;
        Node *backwards = n->prev;
        Node *temp = new Node;
        temp->data = Data;
        temp->next = n;
        temp->prev = n->prev;
        n->prev = temp;
        backwards->next = temp;
      }

  }

  void RemoveAt(unsigned int index){

    if (index+1 > size)
    {
      //cerr << "Index error!";
    }
    else
    {
        if (index == 0)
        {
            RemoveHead();
        }
        else if ((unsigned int) index == size - 1)
        {
            RemoveTail();
        }
        else
        {
            Node *n = head;
            for (unsigned int i = 0; i < (index); i++)
            {
                n = n->next;
            }
            Node *nodeAfter = n->next;
            Node *nodeBefore = n->prev;
            nodeAfter->prev = nodeBefore;
            nodeBefore->next = nodeAfter;
            delete n;
            n = nodeAfter;
        }
        size--;
    }
  }

  void PrintForward() const{
    Node *n;
    n = head;
    int i = 1;
    while (n != nullptr)
    {
        cout << i << " " << n->data << endl;
        n = n->next;
        i++;
    }
  }

  void PrintAll(string Data) const{
    int place = 1;
    Node *n;
    n = head;
    bool wasFound = false; 
    while (n != nullptr)
    {
      if(n->data.find(Data) != string::npos){
        cout << place << " " << n->data << endl;
        wasFound = true;
      }

      n = n->next;
      place++;
    }
      
    if (wasFound == false){
        cout << "not found" << endl; 
    }
  }

  void editNode(int index, string Data){
    //cout << index << endl; 
    Node* n = head; 
    for (int i = 1; i < index ; i++){
      n = n->next;
    }
    n->data = Data; 
  }

};

int main() {

  LinkedList List; 

  bool run = true;
  string input;
  string opString;
  string stoi; 
  int opInt; 

  while (run == true){

    getline(cin, input);

    // quit - quit/exit the program
    if (input == "quit"){
      run = false; 
      return 0; 
    }    
    
    // print -- print the entire document, with line numbers
    if (input == "print"){
      List.PrintForward(); 
    }

    //insertEnd "text"  -- insert given text at the end of the document
    if (input.find("insertEnd ") != string::npos){
      opString = input.substr(11);
      opString.erase(opString.length()-1, 1);
      List.AddTail(opString);
    }

    // insert 3 "text" --insert given text at the line indicated by index given
    if (input.find("insert ") != string::npos){
      opString = input.substr(10);
      opString.erase(opString.length()-1, 1);
      stoi = input[7];
      opInt = std::stoi(stoi);

      List.InsertAt(opInt-1, opString);
    }

    // delete 3 --- delete line at index given
    if (input.find("delete ") != string::npos){
      stoi = input[7];
      opInt = std::stoi(stoi);
      List.RemoveAt(opInt - 1);
    }

    // edit 3 "text" --- replace the line at the index given with the given text
    if (input.find("edit ") != string::npos){
      stoi = input[5];
      opInt = std::stoi(stoi);
      opString = input.substr(8);
      opString.erase(opString.length()-1, 1);
      List.editNode(opInt, opString);
      // List.RemoveAt(opInt);
      // List.InsertAt( opInt, opString);
    }

    // search "text" -- print the line number and line that contains the given text.  print "not found" if it is not found
    if ((input.find("search ") != string::npos)){
      opString = input.substr(8);
      opString.erase(opString.length()-1, 1);
      List.PrintAll(opString);
    }

  }

}