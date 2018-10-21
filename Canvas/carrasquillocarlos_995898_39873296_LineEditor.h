#ifndef LineEditor
#define LineEditor

#include <iostream>
#include <string>
#include <utility>

struct Node {

public:
    std::string data;
    Node* next;
    Node* prev;

    Node(){
        next = nullptr;
        prev = nullptr;
        data = "";
    }
};

class LinkedList {

public:
    int size;
    Node *head, *tail;

    LinkedList(){
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    void insertEnd(std::string newLine)
    {
        auto * newNode = new Node;
        newNode->data = std::move(newLine);

        if(tail == nullptr)
        {
            tail = newNode;
            head = tail;
            size = 1;
        } else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            size++;
        }
    }


    void insertFront(std::string newLine){
        auto * newNode = new Node;
        newNode->data = std::move(newLine);

        if(head == nullptr){
            head = newNode;
            tail = head;
            size = 1;
        } else{
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            size++;
        }
    }

    Node* nodeAt(int index){
        Node* current = head;
        if (index > size / 2){
            current = tail;
            for (int i = 0; i < size - index; i++) {
                current = current->prev;
            }
        } else{
            for (int i = 0; i < index - 1; i++){
                current = current->next;
            }
        }
        return current;
    }

    void insertAt(int index, std::string newLine){
        if((!index < 1) && index <= size){
            Node* current = nodeAt(index);

            if (current != nullptr){
                auto * newNode = new Node;
                newNode->data = std::move(newLine);
                newNode->prev = current->prev;
                newNode-> next = current;

                current->prev->next = newNode;
                current->prev = newNode;

                size++;
            }
        }
    }

    void search(const std::string &toSearch){
        Node* current = head;
        int counter = 1;
        std::string output = "?";
        while(current != nullptr) {
            if (current->data == toSearch){
                output = toSearch;
                break;
            }
            current = current->next;
            counter++;
        }
        if(output != "?"){
            std::cout << "(" << counter << ") " << output <<std::endl;
        }
        else{
            std::cout << "not found"<< std::endl;
        }
        delete(current);
    }

    void edit(int index, std::string newLine){
        if((!index < 1) && index <= size){
            Node* current = nodeAt(index);

            if(current != nullptr){
                current->data = std::move(newLine);
            }
        }
    }

    void deleteNode(int index){
        Node* temp = nodeAt(index);

        if (index == 1){
            head = head->next;
            head->prev = nullptr;
        }

        if (temp != nullptr){
            temp->prev->next = temp->next;
            temp->next = temp->prev;
            size--;
            delete(temp);
        }
        else {
            std::cout << "Node not deleted" << std::endl;
        }
    }

    void printList(){
        Node* temp = head;
        int i = 1;
        while(temp != nullptr){
            std::cout << "(" << i << ") " << temp->data << std::endl;
            temp = temp->next;
            i++;
        }
    }
};

#endif