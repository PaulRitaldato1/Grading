#ifndef LINEEDITOR_H
#define LINEEDITOR_H

struct Node{
    std::string data;
    Node* next = NULL;
};

class LinkedList{

    private:
        Node *head;

    public:
        LinkedList(); //constructor to set up empty stack

        bool isEmpty(); //determine if the Linked list is empty
		void insertEnd(std::string line);//adds string to LinkedList
        void deleteLine(int index); //delete a node
        void insertLine(std::string line, int index);
        void print();
        void searchLine(int index, std::string line);
};

#endif // LINEEDITOR_H
