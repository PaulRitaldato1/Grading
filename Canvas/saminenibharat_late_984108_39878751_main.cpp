#include <iostream>
#include <cstring>
class LinkedList {
public:
    void InsertNode(std::string adding, int line);
    void InsertAtEnd(std::string adding);
    void DeleteNode(int index);
    void EditNode(std::string editing, int line);
    void PrintList();
    void SearchNode(std::string searching);
    LinkedList();
private:
    typedef struct Node {
        std::string data;
        Node *next;
    } *nodePtr;
    nodePtr head;

};


//your linked list implementation here
LinkedList::LinkedList(){
    head = nullptr;
}

void LinkedList::InsertAtEnd(std::string adding) {
    Node *curr = head;
    Node *addNode = new Node;
    addNode->data = adding;
    if (head == nullptr) {
        head = addNode;
        addNode->next = nullptr;
    } else {
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = addNode;
        addNode->next = nullptr;
    }


}


void LinkedList::InsertNode(std::string adding, int line) {
    Node *addingNode = new Node();
    addingNode->data = adding;
    Node *curr = head;
    int j = 1;
    while(curr->next != nullptr){
        curr = curr->next;
        j++;
    }

    if(line > j + 1) {

    }
    else if(line == 1){
        addingNode->next = head;
        head = addingNode;
    }
    else if(line == j + 1){
        InsertAtEnd(adding);
    }
    else{
        Node *temp = head;
        int i = 1;
        while(i < line - 1){
            temp = temp->next;
            i++;
        }
        Node *next = temp->next;
        temp->next = addingNode;
        addingNode->next = next;
    }


}


void LinkedList::PrintList() {
    Node *curr = head;
    int num = 1;
    while (curr->next != nullptr) {
        std::cout << num << " " << curr->data << std::endl;
        curr = curr->next;
        num++;
    }
    std::cout << num << " " << curr->data << std::endl;
}


void LinkedList::SearchNode(std::string searching) {
    int k = 1;
    Node *n = head;
    bool found = false;
    while (n->next != nullptr) {
        if (n->data.find(searching) != std::string::npos) {
            std::cout << k << " " << n->data << std::endl;
            found = true;
        }
        n = n->next;
        k++;
    }
    if (n->data.find(searching) != std::string::npos) {
        std::cout << k << " " << n->data << std::endl;
        found = true;
    }
    if (!found) {
        std::cout << "not found" << std::endl;
    }
}



void LinkedList::EditNode(std::string editing, int line) {
    Node *curr = head;
    int i = 1;
    while (curr->next != nullptr) {
        curr = curr->next;
        i++;
    }
    if (line > i) {
    } else if (line == 1) {
        head->data = editing;
    } else {
        Node *temp = head;
        int i = 1;
        while (i != line) {
            temp = temp->next;
            i++;
        }

        temp->data = editing;
    }

}

void LinkedList::DeleteNode(int index) {
    Node *curr = head;
    int i = 1;
    while (curr->next != nullptr) {
        curr = curr->next;
        i++;
    }
    if (index > i) {

    } else if (index == 1) {
        Node *t = head->next;
        head = t;
    } else {
        Node *temp = head;
        int j = 1;
        while (temp->next != nullptr) {
            if (j == index - 1) {
                temp->next = temp->next->next;
                break;
            } else {
                temp = temp->next;
                j++;
            }

        }
    }
}
int main() {
    LinkedList object;
    while (true) {
        std::string command;
        int position = 0;
        std::string text;
        std::cin >> command;
        std::string temp;
        if (command == "insertEnd") {
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            object.InsertAtEnd(text);
        } else if (command == "insert") {
            std::cin >> position;
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            object.InsertNode(text, position);

        } else if (command == "delete") {
            std::cin >> position;
            object.DeleteNode(position);
        } else if (command == "edit") {
            std::cin >> position;
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            object.EditNode(text, position);

        } else if (command == "print") {
            object.PrintList();
        } else if (command == "search") {
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            object.SearchNode(text);
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Check input" << std::endl;
        }
    }
    return 0;

}