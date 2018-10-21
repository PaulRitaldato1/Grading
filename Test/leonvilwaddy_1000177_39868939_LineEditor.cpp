using namespace std;
#include <string>

#include <iostream>
struct Node {
    string value;
    Node* next = NULL;
};
Node* insertEnd(Node* head, string text);
Node* insert(Node* head, int index, string text);
Node* del(Node* head, int line);
Node* edit(Node* head, int line, string text);
void print(Node* head);
void search(Node* head, string text);
void quit();



int main() {
    Node *head = new Node;
    head->value = "TEST";
    string a, b, c;
    while (a != "quit") {
        cin >> a;
        if (a != "print" && a != "quit") {
            if (a != "insertEnd" && a != "search") {
                cin >> b;
            }
            else {
                getline(cin, b);
            }
        }
        if (a == "insert" || a == "edit") {
            getline(cin, c);
        }
        if (a == "insertEnd") {
            if (b.find("\"", 0) != std::string::npos && b.find("\"", b.find("\"", 0) + 1) != std::string::npos) {
                head = insertEnd(head, b.substr(b.find("\"", 0) + 1, b.find("\"", b.find("\"", 0) + 1) - 2));
            }
        }
        else if (a == "insert") {
            if (c.find("\"", 0) != std::string::npos && c.find("\"", c.find("\"", 0) + 1) != std::string::npos) {
                head = insert(head, stoi(b), c.substr(c.find("\"", 0) + 1, c.find("\"", c.find("\"", 0) + 1) - 2));
            }
        }
        else if (a == "delete") {
            head = del(head, stoi(b));
        }
        else if (a == "edit") {
            if (c.find("\"", 0) != std::string::npos && c.find("\"", c.find("\"", 0) + 1) != std::string::npos) {
                head = edit(head, stoi(b), c.substr(c.find("\"", 0) + 1, c.find("\"", c.find("\"", 0) + 1) - 2));
            }
        }
        else if (a == "print") {
            print(head);
        }
        else if (a == "search") {
            if (b.find("\"", 0) != std::string::npos && b.find("\"", b.find("\"", 0) + 1) != std::string::npos) {
                search(head, b.substr(b.find("\"", 0) + 1, b.find("\"", b.find("\"", 0) + 1) - 2));
            }
        }
    }
    
    return 0;
}
Node* insertEnd(Node* head, string text) {
    Node *node = head;
    Node *nextNode = new Node;
    if(head->value == "TEST") {
        head->value = text;
        return head;
    }
    
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = nextNode;
    nextNode->value = text;
    return head;
}

Node* insert(Node* head, int index, string text) {
    Node *node = head;
    Node *newNode = new Node;
    newNode->value = text;
    int line = 1;
    if (index == 1) {
        if (head->value == "TEST") {
            head->value = text;
            return head;
        }
        newNode-> next = head;
        head = newNode;
    }
    
    while (node->next != NULL) {
        if (line + 1 == index) {
            newNode->next = node->next;
            node->next = newNode;
        }
        line++;
        node = node->next;
    }
    if (line + 1 == index) {
            newNode->next = node->next;
            node->next = newNode;
        }
    
    return head;
}

Node* del(Node* head, int line) {
    Node *node = head;
    Node *temp;
    int currLine = 1;
    if (line == 1) {
        temp = head;
        node = node->next;
        delete(temp);
        head = node;
    }
    while (currLine + 1 != line && node->next != NULL) {
        currLine++;
        node = node->next;
    }
    if (node->next == NULL) {
        return head;
    }
    temp = node->next;
    node->next = node->next->next;
    
    delete(temp);
    return head;
}

Node* edit(Node* head, int line, string text) {
    Node *node = head;
    for (int i = 1; i < line; i++) {
        node = node->next;
    }
    node->value = text;
    return head;
}

void print(Node* head) {
    Node *node = head;
    int line = 1;
    while (node != NULL) {
        if (head->value != "TEST") {
            cout << line << " " << node->value << endl;
            line++;
        }
        node = node->next;
    }
}

void search(Node* head, string text) {
    Node *node = head;
    int line = 1;
    int found = 0;
    while (node != NULL) {
        if (node->value.find(text, 0) != std::string::npos) {
            cout << line << " " << node->value << endl;
            found++;
        }
        line++;
        node = node->next;
    }
    if (found == 0) {
        cout << "not found" << endl;
    }
    return;
}