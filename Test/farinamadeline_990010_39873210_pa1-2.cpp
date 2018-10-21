#include <iostream>
#include <sstream>
#include <regex>
#include <iterator>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cctype>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <tuple>
//you know it's a data structures project when you need 13 include statements...

using namespace std;

typedef tuple<int, string> line;

struct Node
{
    string value;
    Node *next;
};

class LinkedList
{

  public:
    Node *head;
    int listLength;

    Node *insert(int index, string text) //inserts text at specific index
    {
        if (index < 0 || index > listLength)
        {
            return nullptr;
        }

        Node *newNode = new Node();

        if (index == 0)
        {
            newNode->value = to_string(index+1) + " " + text;
            if (head != nullptr)
            {
                newNode->next = head;
            }
            head = newNode;
        }
        else
        {
            newNode->value = to_string(index+1) + " " + text;
            Node *prevNode = head;
            Node *currNode = head;
            for (int i = 0; i < index; i++)
            {
                prevNode = currNode;
                currNode = currNode->next;
            }

            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }

        listLength++; //keeps track of list length

        return newNode;
    }

    void remove(int index) //deletes nodes from list
    {
        if (index < 0 || index >= listLength)
        {
            return;
        }

        if (index == 0)
        {
            head = head->next;
        }
        else
        {
            Node *prevNode = head;
            Node *currNode = head;
            for (int i = 0; i < index; i++)
            {
                prevNode = currNode;
                currNode = currNode->next;
            }
            prevNode->next = currNode->next;
        }

        listLength--;
    }

    vector<line> search(string text)
    {
        vector<line> matchingLines; //container for all instances of lines with searched-for text
        Node *currNode = head;
        for (int i = 0; i < listLength; i++)
        {
            if (currNode->value.find(text) != string::npos)
            {
                matchingLines.emplace_back(i + 1, currNode->value); //pushes every instance of searched line to vector
            }
            currNode = currNode->next;
        }

        if (matchingLines.size() == 0) { cout << "not found" << endl; }

        for (auto element : matchingLines) { //prints every instance of searched line with number
            cout << get<1>(element) << endl;
        }

        return matchingLines;
    }

    LinkedList(vector<string> vecStrs) //Linked List Constructor
    {
        if (vecStrs.empty()) //if list empty
        {
            return;
        }

        Node *localHead = new Node();
        localHead->value = vecStrs[0];

        Node *prevNode = localHead;

        for (int i = 1; i < vecStrs.size(); i++)
        {
            Node *currentNode = new Node();
            prevNode->next = currentNode;
            currentNode->value = vecStrs[i];
            prevNode = currentNode;
        }

        head = localHead;
        listLength = vecStrs.size();
    }

    friend ostream &operator<<(ostream &os, const LinkedList &list) //prints private attributes of Linked List class
    {
        auto currentNode = list.head;
        for (int i = 0; i < list.listLength; i++)
        {
            os << currentNode->value << endl;
            currentNode = currentNode->next;
        }

        return os;
    }
};

int main()
{
    string userCommand = "";
    vector<string> strs = {};
    LinkedList *ll = new LinkedList(strs);

    while (true) {
        getline(cin, userCommand);

        auto first_space_idx = userCommand.find(' ');
        auto userCommand2 = userCommand.substr(0, first_space_idx);

        if (userCommand2 == "insertEnd") {

            if (userCommand.length() > 89) { //to account for insertEnd, checks for max line size
            cout << endl;
            cout << "Error, line length too long" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            continue;
            }
            else {
            //uses regular expression to seperate each chunk of text
            auto textToInsert = regex_replace(userCommand.substr(first_space_idx+1),regex("\""), "");
            ll->insert(ll->listLength, textToInsert); //inserts just text, not command
            }
      }
      
      else if (userCommand2 == "insert" && (isdigit(userCommand.at(7)) != 0)) {
        auto restOfText = userCommand.substr(first_space_idx+1);
        auto second_space_idx = restOfText.find(' ');
        string lineNumber = userCommand.substr(first_space_idx+1, second_space_idx);
        auto textToInsert = regex_replace(restOfText.substr(second_space_idx+1), regex("\""), "");
        ll->insert(stoi(lineNumber)-1, textToInsert);
      }

      else if (userCommand.substr(0,6) == "delete" && (isdigit(userCommand.at(7)) != 0)) {
        auto restOfText = userCommand.substr(first_space_idx+1);
        auto second_space_idx = restOfText.find(' ');
        string lineNumber = userCommand.substr(first_space_idx+1, second_space_idx);
        ll->remove(stoi(lineNumber)-1);
      }

      else if (userCommand.substr(0,4) == "edit" && (isdigit(userCommand.at(5)) != 0)) {
        auto restOfText = userCommand.substr(first_space_idx+1);
        auto second_space_idx = restOfText.find(' ');
        string lineNumber = userCommand.substr(first_space_idx+1, second_space_idx);
        auto textToInsert = regex_replace(restOfText.substr(second_space_idx+1), regex("\""), "");
        ll->remove(stoi(lineNumber)-1); //changes string to int
        ll->insert(stoi(lineNumber)-1, textToInsert);
      }

      else if (userCommand == "print") {
        //ll->numFixer(*ll);
        cout << (*ll);
      }

      else if (userCommand2 == "search") {
        auto textToSearch = regex_replace(userCommand.substr(first_space_idx+1),regex("\""), "");
        ll->search(string(textToSearch));
      }
        
      else if (userCommand == "quit") {
        return 0;
      }

      else {
        continue;
      } 
    }
    return 0;
}
