#include <iostream>
#include "LineEditor.h"
using namespace std;

int stringToInt(string str) {
  int total = 0;
  for(int i = 0; i < str.length(); i++) { // iterates through string
    if(!isdigit(str[i])) {
      return -1; // in case user does not enter valid int
    }
    else {
      int num = (int) str[i] - (int) '0'; // gets int value by ascii code subtraction
      total = 10 * total + num; // calculates total in case of more than 1 digit
    }
  }
  return total;
}

int main() {
  LinkedList* lines = new LinkedList();

  bool hasExited = false;
  while(!hasExited) {
    string userInput;
    int lineNum;
    string lineNumStr;
    //cout << "Enter Input: ";
    getline(cin, userInput);
    int firstIndex = userInput.find(" ");
    string firstWord = userInput.substr(0,firstIndex);

    if(firstWord.compare("insertEnd") == 0) {
      userInput = userInput.substr(10);
      if(userInput.front() == '"' && userInput.back() == '"') {
        userInput = userInput.substr(1,userInput.size()-2);
        if(userInput.size() <= 80) {
          lines->addNodeRight(userInput);
        }
        //else {
          //cout << "80 Character Limit" << endl;
        }
      }
      //else {
        //cout << "Incorrect Format, include quotes" << endl;

    else if(firstWord.compare("insert") == 0) {
      lineNumStr = userInput.substr(7,1);
      lineNum = stringToInt(lineNumStr);
      userInput = userInput.substr(9);
      if(userInput.front() == '"' && userInput.back() == '"') {
        userInput = userInput.substr(1,userInput.size()-2);
        if(userInput.size() <= 80) {
          lineNum--;
          int len = lines->getSize();
          if(lineNum > 0 && lineNum <= len) {
            if(lineNum == 0) {
              lines->addNodeLeft(userInput);
            }
            if(lineNum == len) {
              lines->addNodeRight(userInput);
            }
            else {
              lines->insertNode(lineNum, userInput);
            }
          }
        }
      }
    }

    else if(firstWord.compare("delete") == 0) {
      lineNumStr = userInput.substr(7,1);
      int lineNum = stringToInt(lineNumStr);
      lineNum--;
      if(lineNum >= 0 && lineNum < lines->getSize()) {
        lines->deleteNode(lineNum);
      }
    }

    else if(firstWord.compare("edit") == 0) {
      lineNumStr = userInput.substr(5,1);
      int lineNum = stringToInt(lineNumStr);
      userInput = userInput.substr(7);
      if(userInput.front() == '"' && userInput.back() == '"') {
        userInput = userInput.substr(1,userInput.size()-2);
        if(userInput.size() <= 80) {
          lineNum--;
          if(lineNum >= 0 && lineNum < lines->getSize()) {
            lines->replaceNode(lineNum, userInput);
          }
        }
      }
    }

    else if(firstWord.compare("print") == 0) {
      lines->printList();
    }

    else if(firstWord.compare("search") == 0) {
      userInput = userInput.substr(7);
      if(userInput.front() == '"' && userInput.back() == '"') {
          userInput = userInput.substr(1,userInput.size()-2);
          lines->search(userInput);
        }
      }

    else if(firstWord.compare("quit") == 0) {
      hasExited = true;
    }
  }
}
