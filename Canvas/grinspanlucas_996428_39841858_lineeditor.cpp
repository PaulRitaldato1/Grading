#include <string>
#include <iostream>
#include <regex>
struct Node {
    Node* next;
    std::string data;
};
struct List {
    List() {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    int size;

    void push(std::string data);
    void insert(std::string data, unsigned int index);
    void remove(unsigned int index);
    void replace(std::string data, unsigned int index);
    
    std::vector<int> search(std::string searchItem);
    
    std::string get(unsigned int index);
    
    // For debugging
    void printList();

private:
    Node* head;
    Node* tail;
};
void List::push(std::string data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;

    // Check if the list is empty
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}
void List::insert(std::string data, unsigned int index) {
    Node* newNode  = new Node;
    newNode->data = data;
    
    size++;

    // If size is 0
    if (head == NULL) {
        if (index == 0) {
            newNode->next = NULL;
            head = newNode;
            tail = newNode;
        } else {
            // Error, incorrect index
            size--;
            return;
        }
    // If size is 1
    } else if (head->next == NULL) {
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else if (index == 1) {
            head->next = newNode;
            tail = newNode;
        } else {
            // Error, incorrect index
            size--;
            return;
        }
    } else {
        Node* prevNode = head;
        Node* nextNode = head->next;
        prevNode = head;
        
        // If inserting at beginning
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }
        for (unsigned int i = 1; i < index; i++) {
            if (nextNode->next == NULL) {
                if (i != index - 1) {
                    // Error, index out of bounds
                    size--;
                    return;
                } else {
                    // Index is last possible index
                    tail->next = newNode;
                    tail = newNode;
                    return;
                }
            }
            prevNode = prevNode->next;
            nextNode = nextNode->next;
        }
        prevNode->next = newNode;
        newNode->next = nextNode;
    }
}
void List::remove(unsigned int index) {
    Node* temp = head;
    size--;
    if (index == 0) {
        head = head->next;
        delete temp;
    } else {
        for (unsigned int i = 1; i < index; i++) {
            temp = temp->next;
            if (temp->next == NULL) {
                // Error, index out of range
                size++;
                return;
            }
        }
        Node* deleteNode = temp->next;
        // If the node is not the last in the list
        if (deleteNode->next != NULL) {
            temp->next = deleteNode->next;
        } else {
            temp->next = NULL;
        }
        delete deleteNode;
    }
}
void List::replace(std::string data, unsigned int index) {
    Node* iterator = head;
    unsigned int counter = 0;
    while (iterator != NULL) {
        if (counter == index) {
            iterator->data = data;
            break;
        }
        iterator = iterator->next;
        counter++;
    }
}
std::vector<int> List::search(std::string searchItem) {
    std::vector<int> indices;
    Node* iterator = head;
    unsigned int counter = 0;
    while (iterator != NULL) {
        if (iterator->data.find(searchItem) != std::string::npos) {
            indices.push_back(counter);
        } 
        iterator = iterator->next;
        counter++;
    }
    return indices;
}
std::string List::get(unsigned int index) {
    Node* iterator = head;
    unsigned int counter = 0;
    while (iterator != NULL) {
        if (counter == index) {
            return iterator->data;
        }
        iterator = iterator->next;
        counter++;
    }
    return "";
}
void List::printList() {
    Node* iterator = head;
    while (iterator != NULL) {
        std::cout << iterator->data << std::endl;
        iterator = iterator->next;
    }
}

struct Instruction {
    Instruction() {
        command = "";
        arg0 = "";
        arg1 = "";
    }
    std::string command;
    std::string arg0;
    std::string arg1;
};

Instruction* parseInstruction(std::string input) {
    Instruction* instruction = new Instruction();

    // Sanitize input
    // input = std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1");

    std::string command = "";
    std::string arg0    = "";
    std::string arg1    = "";
    
    int tokenCounter = 0;
    bool readingStringArg = false;
    for (char x : input) {
        if (x == ' ' && !readingStringArg) {
            tokenCounter++;
        } else {
            switch(tokenCounter) {
                case 0: {
                    command += x;
                    break;
                }
                case 1: {
                    if (x == '"') {
                        readingStringArg = !readingStringArg;
                        break;
                    }
                    arg0 += x;
                    break;
                }
                case 2: {
                    if (x == '"') {
                        readingStringArg = !readingStringArg;
                        break;
                    }
                    arg1 += x;
                    break;
                }
            }
        }
    }

    instruction->command = command;
    instruction->arg0    = arg0;
    instruction->arg1    = arg1;

    return instruction;
}

int main() {
    List* editor = new List();
    // std::cout << "Enter a command:" << std::endl;
    
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        
        Instruction* instruction = parseInstruction(input);
        std::string command = instruction->command;
        std::string arg0    = instruction->arg0;
        std::string arg1    = instruction->arg1;

        if (command == "insertEnd") {
            editor->push(arg0);
        } else if (command == "insert") {
            int index = std::stoi(arg0) - 1;
            editor->insert(arg1, index);
        } else if (command == "delete") {
            int index = std::stoi(arg0) - 1;
            editor->remove(index);
        } else if (command == "edit") {
            int index = std::stoi(arg0) - 1;
            editor->replace(arg1, index);
        } else if (command == "print") {
            int length = editor->size;
            for (int i = 0; i < length; i++) {
                std::cout << (i + 1) << " " << editor->get(i) << std::endl;
            }
        } else if (command == "search") {
            std::vector<int> indices = editor->search(arg0);
            if (indices.empty()) {
                std::cout << "not found" << std::endl;
            } else {
                for (int index : indices) {
                    std::cout << (index + 1) << " " << editor->get(index) << std::endl;
                }
            }
        } else if (command == "quit") {
            break;
        } 
    }
}