#include <iostream>

class proj1 {
private:
    typedef struct Node {
        std::string data;
        Node *next;
    } *nodePtr;
    nodePtr head;

public:
    proj1();
    void insertEnd(std::string data);
    void insertAt(std::string data, int position);
    void deleteAt(int position);
    void print();
    void edit(std::string data, int position);
    void search(std::string data);
};

proj1::proj1() {
    head = nullptr;
}

int main() {
    proj1 object;
    int c = 0;
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
            object.insertEnd(text);
            c++;
        } else if (command == "insert") {
            std::cin >> position;
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            if (position > c + 1) {
            } else {
                object.insertAt(text, position - 1);
                c++;
            }
        } else if (command == "delete") {

            std::cin >> position;
            if (position > c) {
            } else {
                object.deleteAt(position - 1);
                c--;
            }
        } else if (command == "edit") {
            std::cin >> position;
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            if (position > c) {
            } else {
                object.edit(text, position - 1);
            }
        } else if (command == "print") {
            object.print();
        } else if (command == "search") {
            std::cin >> text;
            while (text.at(text.length() - 1) != '"') {
                std::cin >> temp;
                text += " " + temp;
            }
            text = text.substr(1, text.length() - 2);
            object.search(text);
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Check input" << std::endl;
        }
    }
    return 0;
}

void proj1::insertEnd(std::string data) {
    Node *nod = new Node();
    nod->next = nullptr;
    nod->data = data;
    if (head == nullptr) {
        head = nod;
    } else {
        Node *n = head;
        while (n->next != nullptr) {
            n = n->next;
        }
        n->next = nod;
    }
}

void proj1::insertAt(std::string data, int position) {
    Node *nod = new Node();
    nod->data = data;
    Node *n = head;
    Node *m;
    int i = 0;
    while (i + 1 != position) {
        n = n->next;
        i++;
    }
    m = n->next;
    n->next = nod;
    nod->next = m;
}

void proj1::deleteAt(int position) {
    int i = 0;
    Node *n = head;
    while (i + 1 != position) {
        n = n->next;
        i++;
    }
    n->next = n->next->next;
}

void proj1::print() {
    Node *n = head;
    int ii = 1;
    while (n->next != nullptr) {
        std::cout << ii << " " << (n->data) << std::endl;
        n = n->next;
        ii++;
    }
    std::cout << ii << " " << (n->data) << std::endl;
}

void proj1::edit(std::string data, int position) {
    int i = 0;
    Node *n = head;
    while (i + 1 != position) {
        n = n->next;
        i++;
    }
    n = n->next;
    n->data = data;
}

void proj1::search(std::string data) {
    int k = 1;
    Node *n = head;
    bool found = false;
    while (n->next != nullptr) {
        if (n->data.find(data) != std::string::npos) {
            std::cout << k << " " << n->data << std::endl;
            found = true;
        }
        n = n->next;
        k++;
    }
    if (n->data.find(data) != std::string::npos) {
        std::cout << k << " " << n->data << std::endl;
        found = true;
    }
    if (!found) {
        std::cout << "not found" << std::endl;
    }
}