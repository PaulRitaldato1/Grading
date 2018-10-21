#include <iostream>

class Node
{
    std::string data;
  public:
    Node(std::string s);
    Node* next;
    void setData(std::string newData); // changes the data in node, but checks to make sure that it has a max 80 chars
    std::string getData();
};

Node::Node(std::string s)
{
  this->next = nullptr;
  this->setData(s);
}

void Node::setData(std::string newData)
{
  if (newData.length() > 80)
    this->data = newData.substr(80); // only save the first 80 chars
  else
    this->data = newData;
}

std::string Node::getData()
{
  return this->data;
}

class LinkedList // the linked list acts as our line editor
{
    Node* first;
    Node* last; // keep track of the last node to make appends O(1)
    Node* get(int index); // returns the node at a particular index
    int length;
  public:
    LinkedList(); // the list starts empty
    ~LinkedList(); // this needs to delete all of the nodes in the list
    void insert(int index, std::string data); // insert a new node at a particular index
    void insertEnd(std::string data); // adds a new node at the end of the list
    void search(std::string findMe); // prints every line where a string is found
    void edit(int index, std::string newString); // changes the data at an index to the new string
    void print(); // prints out the data of the linked list (in other words, the text in the editor)
    void deleteLine(int index); // deletes the node at a given line number

};

LinkedList::LinkedList()
{
  this->first = nullptr;
  this->last = nullptr;
  this->length = 0;
}

LinkedList::~LinkedList()
{
  Node* temp = this->first;
  while(temp->next != nullptr)
  {
    Node* next = temp->next;
    delete temp;
    temp = next;
  }
}

void LinkedList::insertEnd(std::string data)
{
  if (this->length == 0)
  {
    this->first = new Node(data);
    this->last = this->first;
  }
  else
  {
    this->last->next = new Node(data);
    this->last = this->last->next;
  }
  this->length++;
}

void LinkedList::insert(int index, std::string data)
{
  if (index == 1)
  {
    Node* temp = this->first;
    this->first = new Node(data);
    this->first->next = temp;
  }
  else if(index == this->length + 1)
  {
    this->insertEnd(data);
    return;
  }
  else if(index > this->length + 1) // we ignore any insertions that are out of bounds
  {
    return;
  }
  else
  {
    Node* prev = this->get(index - 1);
    Node* after = this->get(index);
    Node* newNode = new Node(data);
    prev->next = newNode;
    newNode->next = after;

  }
  this->length++;
}

void LinkedList::search(std::string data)
{
    Node* temp = this->first;
    bool found = false;
    for (int i = 1; i <= this->length; i++)
    {
      if (temp->getData().find(data) != std::string::npos)
      {
        std::cout << i << temp->getData() << std::endl;
        found = true;
      }
      temp = temp->next;
    }

    if (!found)
      std::cout << "not found" << std::endl;

}

void LinkedList::print()
{
  Node* temp = this->first;
  for (int i = 1; i <= this->length && temp != nullptr; i++)
  {
    std::cout << i << temp->getData() << std::endl;
    temp = temp->next;
  }
}

void LinkedList::edit(int index, std::string newString)
{
  this->get(index)->setData(newString);
}

void LinkedList::deleteLine(int index)
{
  if (index > this->length) return;
  Node* toDelete = this->get(index);
  if (toDelete == this->first)
  {
    this->first = this->first->next;
    delete toDelete;
  }
  else if (toDelete == this->last)
  {
      this->last = this->get(index - 1);
      this->last->next = nullptr;
      delete toDelete;
  }
  else
  {
    Node* prev = this->get(index - 1);
    Node* after = this->get(index + 1);
    delete toDelete;
    prev->next = after;
  }
  this->length--;
}

Node* LinkedList::get(int index)
{
  Node* temp = this->first;
  for (int i = 1; i < index; i++)
  {
    temp = temp->next;
  }
  return temp;
}

class Editor
{
    LinkedList* doc;
    bool running;
    std::string getRestOfInput();
    std::string cleanString(std::string toClean);
  public:
    Editor();
    ~Editor();
    void interact();
};

Editor::Editor()
{
  this->running = false;
  this->doc = new LinkedList();
}
Editor::~Editor()
{
  delete this->doc;
}

std::string Editor::getRestOfInput()
{
  std::string s;
  std::getline(std::cin, s);
  return s;
}

std::string Editor::cleanString(std::string toClean)
{
  std::string cleaned = "";

  for (char c : toClean)
  {
    if (c != '\"') cleaned.push_back(c);
  }

  return cleaned;
}

void Editor::interact()
{
  this->running = true;
  while(this->running)
  {
    std::string input = "";
    std::cin >> input;
    if (input == "print")
    {
      this->doc->print();
    }
    else if(input == "insert")
    {
      int index;
      std::cin >> index;
      std::string rest = cleanString(getRestOfInput());
      this->doc->insert(index, rest);
    }
    else if(input == "insertEnd")
    {
      std::string rest = cleanString(getRestOfInput());
      this->doc->insertEnd(rest);
    }
    else if(input == "search")
    {
      std::string rest = cleanString(getRestOfInput());
      this->doc->search(rest);
    }
    else if (input == "edit")
    {
      int index;
      std::cin >> index;
      std::string rest = cleanString(getRestOfInput());
      this->doc->edit(index, rest);
    }
    else if (input == "delete")
    {
      int index;
      std::cin >> index;
      this->doc->deleteLine(index);
    }
    else if (input == "quit")
    {
      this->running = false;
    }
    else
    {
      std::cout << "Error: command not recognized." << std::endl;
      std::cin.ignore(10000, '\n');
    }

  }
}

int main()
{
  Editor* e = new Editor();
  e->interact();
  delete e;
  return 0;
}
