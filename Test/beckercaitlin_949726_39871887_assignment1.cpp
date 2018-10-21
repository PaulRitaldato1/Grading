#include <string>
#include <iostream>
#include <sstream>
using namespace std;

struct Node {
  string value;
  Node* next;
};

class LinkedList {
private:
  Node* head;
  Node* tail;
public:
  LinkedList() {
    head = NULL;
    tail = NULL;
  }

  void insertEnd(string valueInput) {
      Node* newNode = new Node();
      newNode->value = valueInput;
      if(head == NULL) {
          head = newNode;
          head->next = tail;
          return;
      }
      Node* iterNode = head;
      while(iterNode->next != NULL) {
          iterNode = iterNode->next;
      }
      iterNode->next = newNode;
  }

  void print() {
      int index = 1;
      Node* iterNode = head;
      while(iterNode->next != NULL) {
          std::cout << index << " " << iterNode->value << std::endl;
          index++;
          iterNode = iterNode->next;
      }
      cout << index << " " << iterNode->value << endl;
  }

  void search(string toSearch) {
    int index = 1;
    Node* iterNode = head;
    bool found = false;
    while(iterNode != NULL) {
        if ((iterNode->value).find(toSearch) != string::npos) {
            cout << index << " " << iterNode->value << endl;
            found = true;
        }
        index++;
        iterNode = iterNode->next;
    }
    if(!found) {
        cout << "not found" << endl;
    }
  }

  void edit(int index, string toEdit) {
    Node* iterNode = head;
    for(int i = 1; i < index; i++) {
        if(iterNode->next == NULL) {
            cout << "not found" << endl;
            return;
        }
        iterNode = iterNode->next;
    }
    iterNode->value = toEdit;
  }

  void deleteLine(int index) {
    Node* iterNode = head;
    for(int i = 0; i < index - 2; i++) {
        if(iterNode == NULL) {
            return;
        }
        iterNode = iterNode->next;
    }
    if(iterNode->next == NULL) {
        iterNode->next = NULL;
        return;
    }
    iterNode->next = iterNode->next->next;
    return;
  }

  void insert(int index, string valueInput)
{
    Node* newNode = new Node();
    newNode->value = valueInput;
    Node* iterNode = head;
    if(index == 0) {
        head->next = head;
        head->value = valueInput;
        return;
    }
    for(int i = 1; i < index - 1; i++) {
        if(iterNode->next == NULL) {
            return;
        }
        iterNode = iterNode->next;
    }
    newNode->next = iterNode->next;
    iterNode->next = newNode;
    return;
  }
};

  int stringToInt(string toConvert) {
    stringstream ss;
    ss << toConvert;

    string temp;
    int found;
    while(!ss.eof()) {
      ss >> temp;
      if (stringstream(temp) >> found)  {
        return found;
      }
      temp = "";
    }
    return -1;
  }

  int main() {
    string userInput = "";
    LinkedList* lList = new LinkedList();
    while(userInput != "quit") {
        getline(cin, userInput);
        if(userInput.find("insertEnd") != string::npos) {
            int found = userInput.find("\"");
            if(found != string::npos) {
              string substring = userInput.substr(found + 1);
              lList->insertEnd(substring.substr(0, substring.length() - 1));
            }
        } else if(userInput.find("insert") != string::npos) {
            int index = stringToInt(userInput);
            if(index != -1) {
              int found = userInput.find("\"");
              if(found != string::npos) {
                string substring = userInput.substr(found + 1);
                lList->insert(index, substring.substr(0, substring.length() - 1));
              }
            }
        } else if(userInput.find("print") != string::npos) {
            lList->print();
        } else if(userInput.find("search") != string::npos) {
          int found = userInput.find("\"");
          if(found != string::npos) {
            string substring = userInput.substr(found + 1);
            lList->search(substring.substr(0, substring.length() - 1));
          }
        } else if(userInput.find("edit") != string::npos) {
            int index = stringToInt(userInput);
            if(index != -1) {
              int found = userInput.find("\"");
              if(found != string::npos) {
                string substring = userInput.substr(found + 1);
                lList->edit(index, substring.substr(0, substring.length() - 1));
              }
            }
        } else if(userInput.find("delete") != string::npos) {
            int index = stringToInt(userInput);
            if(index != -1) {
              lList->deleteLine(index);
            }
        } else if(userInput.find("quit") != string::npos) {
            break;
        }
    }
    return 0;
}
