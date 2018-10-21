
#include <stddef.h>
#include <stdbool.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <limits>

//LinkedList class that contains Node objects
class LinkedList {
private:
    struct Node {
        std::string text;
        Node *next;
    };
    Node * head;
    int lineCount; //used to determine max amount of lines for insert, delete, and edit commands
public:
    LinkedList();
    ~LinkedList();
    void insert(int index, std::string textToBeAdded);
    void deleteLine(int indexToDelete);
    void insertEnd(std::string textToBeAdded);
    void print();
    void search(std::string textToCompare);
    void edit(int indexToEdit, std::string textToReplace);
};

//LinkedList constructor
LinkedList::LinkedList() {
    head = NULL;
    lineCount = 0;
}

//LinkedList destructor (needed to prevent memory leaks)
//deallocates each node in list
LinkedList::~LinkedList()
{
    Node * current = head;
    while (current != NULL)
    {
        Node * next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}

void LinkedList::print() {
  int index = 1;
  Node *current = head;
  if (!head)
    return;
  while (current) { //while the pointer is not pointing to null 
        std::cout << index << " " << current->text << std::endl; //the "->" means dereference the pointer and give me its data
        current = current -> next; // next is another pointer, this basically moves to the next node on the list
        index++;
  }
}

void LinkedList::insertEnd(std::string textToBeAdded)
{
   Node *current = head;
   Node * nodeToAdd = new Node();
   nodeToAdd->next = NULL;
   nodeToAdd->text = textToBeAdded;
   if(current)
   {
      while(current->next)
      {
         current = current->next;
      }
      current->next = nodeToAdd;
   }
   else
   {
      head = nodeToAdd;
   }
   lineCount++; // when a node is added, increment the count of number of lines
   return;
}

void LinkedList::insert(int index, std::string text)
{
    Node* addNode = new Node();
    addNode->text = text;
    addNode->next = NULL;
    Node* current = head;
    Node * prev = NULL;

    int i=2;
    //if index is out of bounds, return
    if (index == 0 || index > (lineCount+1))
        return;
    if (index ==1)
    {
        if (head == NULL)
        {
            head = addNode;
            lineCount++;
            return;
        }
        addNode->next = head;
        head = addNode;
        lineCount++; // when node is added, increment line count
        return;
    }
    while (i<index) //traverse the list until desired index is reached
    {
        current = current->next;
        if (current == NULL)
            return;
        i++;
    }
    Node* next = current->next;
    current->next = addNode;
    addNode->next = next;
    lineCount++; //when a node is added, increment count of lines
    
}

void LinkedList::search(std::string textToCompare)
{
    Node* current = head;
    int found = 0;
    int index = 1; //keeps track of line number 
    while (current)
    {
        if (current->text.find(textToCompare) != std::string::npos)
        {
            std::cout << index << " " << current->text << std::endl;
            found++; 
        }
        current=current->next;
        index++;
    }
    if (found == 0) //only print "not found" if no nodes are found (aka found count == 0)
        std::cout << "not found" << std::endl;
    return ;
    
}

void LinkedList::deleteLine(int indexToDelete)
{
   Node *previous = NULL;
   Node *current = head;
   
   //if linked list is empty or index is out of bounds, return
   if (head == NULL || indexToDelete == 0 || indexToDelete > lineCount)
        {
            return;
        }
   if (indexToDelete == 1)
   {
       delete head; // deallocate memory of head node
       head = head->next;
       lineCount--;
       return;
   }
   for(int i = 1; i < indexToDelete; i++)
   {
      previous = current;
      current = current->next;
   }
   if(previous)
   {
      previous->next = current->next;
      delete current;
      current = current->next;
   }
   lineCount--;
   return;
}

void LinkedList::edit(int indexToEdit, std::string textToReplace)
{
   Node *previous = NULL;
   Node *current = head;

   //if linked list is empty or index is out of bounds, return
   if (head == NULL || indexToEdit == 0 || indexToEdit > lineCount)
        {
            return;
        }
   if (indexToEdit == 1)
   {
       head->text = textToReplace;
       return;
   }
   for(int i = 1; i < indexToEdit; i++)
   {
      current = current->next;
   }
   current->text = textToReplace;
   return;
}

//this method checks to see if cin is returning false due to malformed/wrongly typed input and clears the buffer
void checkValidType()
{
    if(!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
    return;
}
///////////////////////////////////////////////////////////////////////////////
int main() {
    std::string command, desiredText, temp;
    int desiredIndex;
    LinkedList * document = new LinkedList(); // create new linked list
    
    TAKEINPUT:
    desiredText = "";
    desiredIndex = 0;
    std::cin >> command;
    checkValidType();
    if (command == "insertEnd")
    {
            //parses quotes out from beginning and end of passed string
            std::getline(std::getline(std::cin, temp, '"'), desiredText, '"');
            //checks to see that user passed in right type of input to the variables with cin (e.g. sting -> string)
            checkValidType();
            //if length of string is greater than 80 characters, clear variable and don't call function
            if(desiredText.length() > 80 || desiredText.find('\n') != std::string::npos)
            {
                desiredText = ""; 
            }
            else 
            {
                document->insertEnd(desiredText);
            }
    }
    else if (command == "insert")
    {
            std::cin >> desiredIndex;
            std::getline(std::getline(std::cin, temp, '"'), desiredText, '"');
            checkValidType();
            if(desiredText.length() > 80 || desiredText.find('\n') != std::string::npos)
            {
                desiredText = "";
            }
            else 
            {
                document->insert(desiredIndex, desiredText);
            }
    }
    else if (command == "delete")
    {
            std::cin >> desiredIndex;
            checkValidType();
            document->deleteLine(desiredIndex);
    }
    else if (command == "edit")
    {
            std::cin >> desiredIndex;
            std::getline(std::getline(std::cin, temp, '"'), desiredText, '"');
            checkValidType();
            if(desiredText.length() > 80 || desiredText.find('\n') != std::string::npos)
            {
                desiredText = "";
            }
            else
            {
                document->edit(desiredIndex, desiredText);
            }
    }
    else if (command == "print")
    {
            document->print();
    }
    else if (command == "search")
    {
            std::getline(std::getline(std::cin, temp, '"'), desiredText, '"');
            checkValidType();
            if(desiredText.length() > 80 || desiredText.find('\n') != std::string::npos)
            {
                desiredText = "";
            }
            else 
            {
                document->search(desiredText);
            }
    }
    else if (command == "quit")
    {
        delete document; // to prevent memory leaks, deallocate all memory from nodes in linked list    
        return 0;
    }
    else 
    {
        //do nothing
    }
    goto TAKEINPUT; // use labels and goto jumps to essentially act as a while loop 
}