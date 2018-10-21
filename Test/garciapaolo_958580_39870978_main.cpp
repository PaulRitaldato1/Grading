#include <iostream>
#include <string>
#include <istream>

class Node
{
public:
  std::string line = "";
  int length = 0;
  int docLength = 1; //used to get rid of bug in insertEnd
  Node* next = NULL;
};

void Print(Node* head); // for printing command (Seems to work)

bool Insert(Node* head, std::string newLine, int indexInsert); // for insert command (Seems to work)

bool InsertEnd(Node* head, std::string newLine); // for insertEnd command (Seems to work, check for first ever insert)

bool Delete(Node* head, int indexDelete); // for delete command (Seems to work needs more testing)

bool Edit(Node* head, std::string newLine, int indexInsert); // for edit command (seems to work, glitch with delete before edit)

bool InDocument(Node* head, std::string lineToFind); // for the search command (Needs work in comparing/printing, needs to contain not 100% match)

std::string CommandToLine(std::string Command); // for getting the line from the command line

int CommandToIndex(std::string Command); // for getting the index from the command line


int main()
{
  Node head;
  char command[85];
  std::string Command;
  std::string newLine;
  int index;

  do
  {
    std::cin.getline (command, 85);
    Command = command;

    if(Command.find("insert") != std::string::npos && Command.find("insertEnd") == std::string::npos)
    {
      index = CommandToIndex(Command);
      newLine = CommandToLine(Command);
      Insert(&head, newLine, index);
    }

    if(Command.find("insertEnd") != std::string::npos)
    {
      newLine = CommandToLine(Command);
      InsertEnd(&head, newLine);
    }

    if(Command.find("delete") != std::string::npos)
    {
      index = CommandToIndex(Command);
      Delete(&head, index);
    }

    if(Command.find("edit") != std::string::npos)
    {
      newLine = CommandToLine(Command);
      index = CommandToIndex(Command);
      Edit(&head, newLine, index);
    }

    if(Command.find("print") != std::string::npos)
    {
      Print(&head);
    }

    if(Command.find("search") != std::string::npos)
    {
      newLine = CommandToLine(Command);
      InDocument(&head, newLine);
    }
  }
  while(Command != "quit");
  return 0;
}

void Print(Node* head) // goes through the linked list and prints out the line
{
  Node* current = head;
  int index = 1;
  while(current != NULL)
  {
    std::cout << index << " " << current->line << std::endl;
    current = current->next;
    index++;
  }
}

bool Insert(Node* head, std::string newLine, int indexInsert) // inserts at the index given
{
  Node* Line = new Node();
  Line->line = newLine;

  if(indexInsert == 1) // checks if we are trying to insert line at the beginning
  {
    head->line = Line->line;
    return true;
  }

  int i = 2;
  Node* current = head;
  while(i < indexInsert) // checks the rest of the list to find the index we are trying to insert into
  {
    current = current->next;
    if(current == NULL){
      std::cout << "Out of Bounds" << std::endl;
      return false;
    }
    i++;
  }
  Node* next = current->next; // carrys out the actual insertion
  current->next = Line;
  Line->next = next;
  return true;
}

bool InsertEnd(Node* head, std::string newLine) // inserts at the end
{
  Node* current = head;

  Node* Line = new Node();
  Line->line = newLine;
  int doclength = head->docLength;

  if(doclength == 1) // checks if we are trying to insert line at the beginning
    {
      head->line = Line->line;
      head->docLength++;
      return true;
    }

  while(current->next != NULL) // checks the rest of the list to find the index we are trying to insert into
  {
    current = current->next;
  }

  Node* next = current->next; // carrys out the actual insertion
  current->next = Line;
  Line->next = next;
  return true;
}

bool Edit(Node* head, std::string newLine, int indexInsert) // replaces a line
{
  int index = 1;
  Node* current = head;

  while(current != NULL) // basically go through the list and if the index matches replace old line value with new one
  {
    if(index == indexInsert)
    {
      current->line = newLine;
      return true;
    }
    current = current->next;
    index++;
  }
  return false;
}

bool Delete(Node* head, int indexDelete) // gets rid of a line
{
  Node* current = head;
  Node* previous = head;
  Node* temp;
  int index = 1;

  if(indexDelete == 1) // if the line we want to delete is at the beginning
  {
    temp = head;
    current = current->next;
    head = current;
    delete(temp);
    return true;
  }

  while(current->next != NULL) // if the line we want to delete is in the middle
  {
    if(index == indexDelete)
    {
      previous->next = current->next;
      temp = current;
      current = current->next;
      delete(temp);
      return true;
    }
    current = current->next;
    index++;
  }

  if(current->next == NULL) //&& index == indexDelete) // if the line we want to delete is at the end
  {
    temp = current;
    previous->next = NULL;
    current = NULL;
    delete(temp);
    return true;
  }

  else
  {
    return false;
  }
}

bool InDocument(Node* head, std::string lineToFind) // searches all the lines for the line asked for
{
  Node* current = head;
  int index = 1;
  int count = 0;
  while(current != NULL)
  {
    if(current->line.find(lineToFind) != std::string::npos)
    {
      std::cout << index << " " << current->line << std::endl;
      count++;
    }
    current = current->next;
    index++;
  }
  if(count > 0)
  {
      return true;
  }
  std::cout << "not found" << std::endl;
  return false;
}

std::string CommandToLine(std::string Command)
{
  int pos, pos2;
  std::string newLine;

  pos = Command.find("\"")+1; // to skip the first quote
  pos2 = Command.find("\"", pos+2); // to find the next quote but skip the first one
  newLine = Command.substr(pos, pos2-pos); // find the substring between the two quotes

  return newLine;
}

int CommandToIndex(std::string Command)
{
  int poS, poS2, index;
  std::string indexS;

  poS = Command.find(" ")+1; // to skip the fist space sign
  poS2 = Command.find(" ", poS+1); // to find the next space not including the one we just found
  indexS = Command.substr(poS, poS2-poS); // to find the substring inbetween the the two spaces
  index = atoi(indexS.c_str()); // convert the string index into an int

  return index;
}
