#include <iostream>
#include "LineEditor.h"

//trims leading and trailing spaces
std::string trimInput(std::string toTrim, const std::string& chars = " ")
{
    toTrim.erase(0, toTrim.find_first_not_of(chars));
    return toTrim;
}
//running input loop
void inputLoop(LinkedList* list) {

    bool quit = false;
    int index = 0;
    std::string input;

    std::cout << "Enter 'quit' at any time to quit." << std::endl;

    while (!quit) {

        std::cout << ">>  ";
        std::getline(std::cin, input);
        input = trimInput(input);

        if (input.substr(0, 9) == "insertEnd") {
            if ((trimInput(input.substr(9))).empty()){
                std::cerr << "Incorrect Syntax" << std::endl;
                continue;
            }
            if (input.substr(9).length() > 80){
                input = input.substr(9, 89);
                std::cout << "Line has been adjusted for exceeding 80 characters." << std::endl;
            }
            list->insertEnd(trimInput(input.substr(9)));
        }
        else if (input.substr(0, 6) == "insert") {
            unsigned long firstSpace = input.substr(6).find_first_not_of(' ');
            unsigned long secondSpace = input.substr(firstSpace + 6).find_first_of(' ');

            try{
                index = stoi(input.substr(6+ firstSpace));
            } catch (...){
                std::cerr << "Invalid Syntax" <<std::endl;
                continue;
            }
            std::string newLine = trimInput(input.substr(6 + firstSpace + secondSpace));
            if(index == 1){
                list->insertFront(newLine);
            }
            else if (index == list->size + 1){
                list->insertEnd(newLine);
            }
            else{
                list->insertAt(index, newLine);
            }
        }
        else if (input.substr(0, 6) == "delete") {
            unsigned long firstSpace = input.substr(6).find_first_not_of(' ');

            try{
                index = stoi(input.substr(6 + firstSpace));
            } catch (...){
                std::cerr << "Invalid Syntax" <<std::endl;
                continue;
            }
            if (index > list->size){
                std::cout << "The line you have entered does not exist in the file." << std::endl;
            } else{
                list->deleteNode(index);
            }
        }
        else if (input.substr(0, 4) == "edit") {
            unsigned long firstSpace = input.substr(4).find_first_not_of(' ');
            unsigned long secondSpace = input.substr(firstSpace + 4).find_first_of(' ');

            try{
                index = stoi(input.substr(4 + firstSpace));
            } catch (...){
                std::cerr << "Invalid Syntax" <<std::endl;
                continue;
            }
            std::string newLine = trimInput(input.substr(4 + firstSpace + secondSpace));
            if(index == 1){
                list->insertFront(newLine);
            }
            else if (index == list->size + 1){
                list->insertEnd(newLine);
            }
            else{
                list->edit(index, newLine);
            }
        }
        else if (input.substr(0, 5) == "print") {
            list->printList();
        }
        else if (input.substr(0, 6) == "search") {
            if (trimInput(input.substr(6)).empty()){
                std::cerr << "Incorrect Syntax" << std::endl;
                continue;
            }
            if (input.substr(6).length() > 80){
                input = input.substr(6, 86);
                std::cout << "Line has been adjusted for exceeding 80 characters." << std::endl;
            }
            list->search(trimInput(input.substr(6)));
        }
        else if (input.substr(0, 4) == "quit") {
            quit = true;
        }
        else {
            std::cerr << "Error: not a valid command." << std::endl;
        }
    }
}

int main() {
    auto* list = new LinkedList;

    inputLoop(list);
    return 0;
};

