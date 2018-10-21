#include <iostream>
#include <sstream>
#import <string>

class Node {
public:
    std::string value;
    Node* next = nullptr;
};

Node* insertNode(Node* head, int index, std::string input){
    Node *addNode = new Node();
    addNode->value = input;
    if (index == 1){ //Special case for inserting at the first node of the list.
        addNode->next = head;
        return addNode;
    }
    int i = 2;
    Node *current = head;
    while (i<index){ //Loop through list to the specified index.
        current = current->next;
        if (current == nullptr) { //Return unchanged list if index out of bounds.
            return head;
        }
        i++;
    }
    Node *next = current->next;
    current->next = addNode;
    addNode->next = next;
    return head;
}
Node* insertEndNode(Node* head, std::string input)
{
    Node *addNode = new Node();
    addNode->value = input;
    if(head->value == "" && head->next == nullptr){ //Special case for empty list.
        return addNode;
    }
    Node *current = head;
    while (current != nullptr){ //Loop through list to the end.
        if (current->next == nullptr) {
            current->next = addNode;
            return head;
        }
        current = current->next;
    }
}
Node* removeNode(Node* head, int index){
    if (index == 1){ //Special case for removing the first node of the list.
        head = head->next;
    }
    int i = 2;
    Node *current = head;
    Node *previous = head;
    while (i <= index){ //Loop through list to the specified index.
        current = current->next;
        if (current == nullptr) {
            return head;
        }
        if (i == index) {
            previous->next = current->next;
        }
        previous = current;
        i++;
    }
    return head;
}
Node* editNode(Node* head, int index, std::string input){
    if (index == 1){ //Special case for editing the first node of the list.
        head->value = input;
    }
    int i = 2;
    Node *current = head;
    while (i<=index){ //Loop through list to the specified index.
        current = current->next;
        if (current == nullptr) {
            return head;
        }
        i++;
    }
    current->value = input; //Set the value to the input value at the specified index.
    return head;
}
void searchList(Node* head, std::string input){
    bool foundNode = false;
    int i = 1; //Set beginning index for the printed output.
    Node *current = head;
    while (current != nullptr){ //Loop through entire list, printing values that contain the search value.
        if (current->value.find(input) != std::string::npos) {
            std::cout << i << " " << current->value << "\n";
            foundNode = true;
        }
        i++;
        current = current->next;
    }
    if(!foundNode){ //Output to console if search finds no matches.
        std::cout << "not found\n";
    }
}
void printList(Node* head){
    int i = 1; //Set beginning index for the printed output.
    Node *current = head;
    while (current != nullptr){ //Loop through the entire list, printing each value.
        std::cout << i << " " << current->value << "\n";
        current = current->next;
        if (current == nullptr) {
            break;
        }
        i++;
    }
}

int main() {
    bool running = true;
    Node *main = new Node();
    while(running){
		//Retrieve user input from console.
        std::string userInput;
        std::getline(std::cin, userInput);

		//Capture first two parameters.
        std::istringstream iss(userInput);
        std::string param1, param2;
        iss >> param1 >> param2;

		//Capture input between "" in the input.
        unsigned open = userInput.find('\"') + 1;
        unsigned close = userInput.find('\"', open);
        std::string param3 = userInput.substr (open, close - open);

		//Perform operation based on user input.
        if(param1 == "quit"){
            running = false;
            break;
        }
        else if(param1 == "insertEnd"){
            main = insertEndNode(main, param3);
        }
        else if(param1 == "insert"){
            main = insertNode(main, std::stoi(param2), param3);
        }
        else if(param1 == "delete"){
            main = removeNode(main, std::stoi(param2));
        }
        else if(param1 == "edit"){
            main = editNode(main, std::stoi(param2), param3);
        }
        else if(param1 == "print"){
            printList(main);
        }
        else if(param1 == "search"){
            searchList(main, param3);
        }
        else{
            std::cout << "Command not recognized.";
        }
    }
    return 0;
}
