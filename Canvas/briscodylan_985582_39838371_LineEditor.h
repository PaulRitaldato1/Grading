#ifndef LineEditor_H
#define LineEditor_H
#include<stddef.h>
#include<string>
#include <cstdlib>
#include <iostream>

using namespace std;

/* Contains data and links to prev and next node */
class Node {
  public:
    string line; // generic data type
    Node* left; // node to left of current node
    Node* right; // node to right of current node
    Node() {
      left = NULL;
      right = NULL;
    }
  };

/*Collection of nodes */
class LinkedList {
  public: //functions
    Node* head; // first node in list
    Node* tail; // last node in list
    LinkedList();
    void addNodeLeft(string line); // add a node to the left
    void addNodeRight(string line); // add a node to the right
    void deleteNode(int pos); // removes a node with the given data
    void insertNode(int pos, string line);
    void replaceNode(int pos, string line);
    void printList();
    void search(string text);
    int getSize();
  };


LinkedList::LinkedList() {
  head = NULL;
  tail = NULL;
}

/*Adds a node to the leftmost portion of the list*/
void LinkedList::addNodeLeft(string line) {
  Node* n = new Node;
  n->line = line; //data in node n
  n->right = head; // right to the node
  n->left = NULL; // set node left of n to null

  if(head == NULL) { // if head is null nothing is in list, so set head and tail to n
    head = n;
    tail = n;
  }
  else { // if list contains nodes
    head->left = n; // set left
    head = n; // reset the head
  }
}

/*Adds a node to the rightmost portion of the list*/
void LinkedList::addNodeRight(string line) {
  Node* n = new Node;
  n->line = line; // node data
  n->left = tail; // left of node
  n->right = NULL; // right of

  if(tail == NULL) { // nothing in list set head and tail
    head = n;
    tail = n;
  }
  else {
    tail->right = n; // set tail
    tail = n; // reset new tail
  }
}

void LinkedList::insertNode(int pos, string line) {
    Node* curr = head;
    Node* prev = NULL;
    int i = 1;
    while (i <= pos) {
      prev = curr;
      curr = curr->right;
      i++;
    }
    Node* addNode = new Node;
    addNode->line = line;
    addNode->right = curr;
    addNode->left = prev;
    curr->left = addNode;
    if(prev != NULL) {
      prev->right = addNode;
    }
    if(i==1) {
      head = addNode;
    }
  }

/*Removes a node*/
void LinkedList::deleteNode(int pos) {
  Node* node = head;
  int counter = 0;
  while(node != NULL && pos != counter) { // iterates through the list until reaches desired node
    node = node->right;
    counter++;
  }
if(node == NULL) {
  return; // nothing removed
}
  Node* rem = node; // node to be removed
  Node* left = rem->left; // left of to be removed node
  Node* right = rem->right; // right of to be removed node

  rem->left  = NULL;
  rem->right = NULL; //in order to reset the links

  if(left != NULL) {
    left->right = right; // node to left of removed node points to node to right of removed node
  }
  else {
    head = right; //sets new head
  }

  if(right != NULL) { // opposite of prev. if statement
    right->left = left;
  }

  else {
    tail = left; // sets new tail
  }
}

void LinkedList::replaceNode(int pos, string line) {
  Node* h = head;
  int i=0;
  Node* current = h;
  while (i < pos) {
    current = current->right;
    i++;
  }
  if(i == pos) {
    current->line = line;
  }
}

void LinkedList::printList() {
  Node* curr = head;
  int count = 1;
  while(curr != NULL) {
    cout << count << " " << curr->line << endl;
    curr = curr->right;
    count++;
  }
}

void LinkedList::search(string text) {
  Node* curr = head;
  int count = 1;
  bool found = false;
  while(curr != NULL) {
    if(strstr(curr->line.c_str(), text.c_str())) {
      cout << count << " " << curr->line << endl;
      found = true;
      curr = curr -> right;
      count++;
    }
    else {
      count++;
      curr = curr -> right;
    }
  }
  if(!found) {
    cout << "not found" << endl;
  }
}

int LinkedList::getSize() {
  Node* curr = head;
  int size = 0;
  while(curr != NULL) {
    size++;
    curr = curr->right;
  }
  return size;
}

int stringToInt(string str);

#endif
