/* Name: Gregory DeCanio
 * Project: Implement a Line Editor Using Linked Lists
 * Course: COP 3530
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

//Node class that will hold the lines of data
class Node
{
  //@param: line = holds the line of text
  //@param: prev = points to the previous node in the list
  //@param: next = points to the next node in the list
public:
    std::string line;
    Node* prev;
    Node* next;

    Node()
    {
      line = "";
      prev = NULL;
      next = NULL;
    }
    //searchLine searches the text in the node for matching text that was passed through
    //@param: searchLine = text that we are looking for in node
    bool searchLine(std::string searchLine)
    {
      if(line.find(searchLine) != std::string::npos)
        return true;
      else
        return false;
    }
};

//LinkedList class holds the nodes, and performs insertions, deletions, edits
//printing, and searching
class LinkedList
{
  //@param: size = holds the size of the list
  //@param: head = node with no data that holds the head of the list
  //@param: tail = node with no data that holds the tail of the list
public:
    int size;
    Node* head;
    Node* tail;

public:
    LinkedList();
    void insertEnd(std::string lineWords);
    void insertIndex(int lineIndex, std::string lineWords);
    void deleteIndex(int lineIndex);
    void editIndex(int lineIndex, std::string lineWords);
    void printDoc();
    void searchDoc(std::string lineWords);
};

//Constructor that points head and tail to each other, as well as sets size to 0
LinkedList::LinkedList()
{
  size = 0;
  head = new Node();
  tail = new Node();
  head->next = tail;
  tail->prev = head;
}
//insertEnd inserts user text to the bottom of the list
//@param: lineWords = input from the user that will be used as the text for the node
void LinkedList::insertEnd(std::string lineWords)
{
  Node* newNode = new Node();   //creates new node for the line that has been input
  newNode->line = lineWords;    //assigns the input into the node's string data
  Node* oldPrev = tail->prev;   //creates a temporary node that is the initial node before tail
  tail->prev = newNode;         //the tail's prev points to the new node
  oldPrev->next = newNode;      //the old node before tail now points forward to the new node
  newNode->prev = oldPrev;      //the new node now points behind it correctly
  newNode->next = tail;         //the new node now points in front of it towards the tail
  ++size;                       //increase the size of the list
  return;
}
//insertIndex inserts user text to a specified index/spot in the list
//@param: lineIndex = index user wants their text to be inserted at in the list
//@param: lineWords = input from the user that will be used as the text for the node
void LinkedList::insertIndex(int lineIndex, std::string lineWords)
{
  if(lineIndex == (size + 1))         //takes into account fringe where the index is one larger than the list
  {
    insertEnd(lineWords);      //performs function where string is inserted into end of list
    return;
  }
  Node* current = head->next;         //creates a node used to iterate through list
  int indexCounter = 1;               //creates index counter used for iterating
  while(current != tail)
  {
    if(indexCounter == lineIndex)
    {
      Node* newNode = new Node();
      newNode->line = lineWords;
      Node* oldPrev = current->prev;
      oldPrev->next = newNode;
      current->prev = newNode;
      newNode->prev = oldPrev;
      newNode->next = current;
      ++size;
      return;
    }
    ++indexCounter;                 //increases index counter by one
    current = current->next;        //points to next node
  }
  return;                           //returns if index is out of bounds
}
//deleteIndex deltes a line of text at a user selected node
//@param: lineIndex = index user wants their text to be inserted at in the list
void LinkedList::deleteIndex(int lineIndex)
{
  if(size == 0)
    return;
  if(size == 1)
  {
    head->next = tail;
    tail->prev = head;
    return;
  }
  Node* current = head->next;         //creates a node used to iterate through list
  int indexCounter = 1;               //creates index counter used for iterating
  while(current != tail)
  {
    if(indexCounter == lineIndex)
    {
      Node* newPrev = current->prev;
      Node* newNext = current->next;
      newPrev->next = newNext;
      newNext->prev = newPrev;
      --size;
      return;
    }
    ++indexCounter;                 //increases index counter by one
    current = current->next;        //points to next node
  }
  return;                           //returns if index is out of bounds
}
//editIndex changes the line of text at a user specified index in the list
//@param: lineIndex = index user wants their text to be inserted at in the list
//@param: lineWords = input from the user that will be used as the text for the node
void LinkedList::editIndex(int lineIndex, std::string lineWords)
{
  Node* current = head->next;         //creates a node used to iterate through list
  int indexCounter = 1;               //creates index counter used for iterating
  while(current != tail)
  {
    if(indexCounter == lineIndex)
    {
      current->line = lineWords;
      return;
    }
    ++indexCounter;                 //increases index counter by one
    current = current->next;        //points to next node
  }
  return;                           //returns if index is out of bounds
}
//printDoc prints everything in the list, printing out the index, then the line of text
void LinkedList::printDoc()
{
  Node* current = head->next;         //creates a node used to iterate through list
  int indexCounter = 1;               //creates index counter used for iterating
  while(current != tail)
  {
    std::cout << indexCounter << " " << current->line << std::endl;
    ++indexCounter;                 //increases index counter by one
    current = current->next;        //points to next node
  }
  return;                           //returns when last node is reached
}
//searchDoc prints everything in the list that matches the string that is passed through
//@param: lineWords = input from the user that is searched for
void LinkedList::searchDoc(std::string lineWords)
{
  Node* current = head->next;         //creates a node used to iterate through list
  int indexCounter = 1;               //creates index counter used for iterating
  bool searchFound = false;
  while(current != tail)
  {
    if(current->searchLine(lineWords))
    {
      std::cout << indexCounter << " " << current->line << std::endl;
      searchFound = true;
    }
    ++indexCounter;                 //increases index counter by one
    current = current->next;        //points to next node
  }
  if(!searchFound)
    std::cout << "not found" << std::endl;
  return;                           //returns when last node is reached
}
//CharLimit checks that the 80 char limit for lines of text is not invalidated
//@param: inputLine = line user inputs
bool CharLimit(std::string inputLine)
{
  if(inputLine.length() > 80)
    return false;
  else
    return true;
}
//StripString takes the quotations off of the string when it is input by the user
//@param: theSting = text the user inputs, which has quotations around it
std::string StripString(std::string theString)
{
  theString.erase(0,2);
  theString.erase(theString.end()-1,theString.end());
  return theString;
}

enum enumInputs
{eInsertEnd, eInsert, eDelete, eEdit, ePrint, eSearch, eQuit};

int main()
{
  std::map<std::string, enumInputs> mappy;
  mappy["insertEnd"] = eInsertEnd;
  mappy["insert"] = eInsert;
  mappy["delete"] = eDelete;
  mappy["edit"] = eEdit;
  mappy["print"] = ePrint;
  mappy["search"] = eSearch;
  mappy["quit"] = eQuit;
  std::map<std::string, enumInputs>::iterator it;

  LinkedList* listy = new LinkedList();
  bool quitToggle = false;
  int inputIndex;
  std::string input;
  std::string inputInd;
  std::string inputCmnd;
  std::string inputLine;
  while(!quitToggle)
  {
    std::cin >> input;
    it = mappy.find(input);
    switch(it->second)
    {
      case eInsertEnd:
      {
        std::getline (std::cin, inputLine);
        inputLine = StripString(inputLine);
        if(CharLimit(inputLine))
        {
          listy->insertEnd(inputLine);
        }
        break;
      }
      case eInsert:
      {
        std::cin >> inputIndex;
        if(inputIndex <= listy->size + 1)
        {
          std::getline (std::cin, inputLine);
          inputLine = StripString(inputLine);
          if(CharLimit(inputLine))
          {
            listy->insertIndex(inputIndex, inputLine);
          }
        }
        break;
      }
      case eDelete:
      {
        std::cin >> inputIndex;
        if(inputIndex <= listy->size)
        {
          listy->deleteIndex(inputIndex);
        }
        break;
      }
      case eEdit:
      {
        std::cin >> inputIndex;
        if(inputIndex <= listy->size)
        {
          std::getline (std::cin, inputLine);
          inputLine = StripString(inputLine);
          if(CharLimit(inputLine))
          {
            listy->editIndex(inputIndex, inputLine);
          }
        }
        break;
      }
      case ePrint:
      {
        listy->printDoc();
        break;
      }
      case eSearch:
      {
        std::getline (std::cin, inputLine);
        inputLine = StripString(inputLine);
        if(CharLimit(inputLine))
        {
          listy->searchDoc(inputLine);
        }
        break;
      }
      case eQuit:
      {
        quitToggle = true;
        return 0;
      }
      default:
      {
        break;
      }
    }
  }
}
