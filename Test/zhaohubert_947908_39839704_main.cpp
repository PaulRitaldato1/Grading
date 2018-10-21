#include <iostream>
#include "LinkedList.h"


void runProgram() { //runs line editor program
    std::LinkedList list;

    bool on = true;

    while (on) {

        std::string instruction;
        std::cin >> instruction; //takes in instruction
        if (instruction == "insertEnd") { //if insertEnd
            std::string text;
            std::cin >> text;
            if (text.at(0) == '"' && text.at(text.size() - 1) == '"') //makes sure there are quotes around text
                list.insertEnd(text.substr(1, text.length() - 2));
        }
        else if (instruction == "insert") { //insert
            std::string text;
            int position;
            std::cin >> position >> text;
            if (text.at(0) == '"' && text.at(text.size() - 1) == '"')
                list.insert(position, text.substr(1, text.length() - 2));

        }
        else if (instruction == "delete") { //delete
            int position;
            std::cin >> position;
            list.deleteNode(position);


        }
        else if (instruction == "edit") { //edit
            int position;
            std::string text;
            std::cin>>position >> text;
            if (text.at(0) == '"' && text.at(text.size() - 1) == '"')
                list.edit(position, text.substr(1, text.length() - 2));

        }
        else if (instruction == "print") { //print
            list.print();

        }
        else if (instruction == "search") { //search
            std::string text;
            std::cin >> text;
            if (text.at(0) == '"' && text.at(text.size() - 1) == '"')
                list.search(text.substr(1, text.length() - 2));
        }
        else if (instruction == "quit") { //exit
            on = false;
        }



    }
}

int main() {

    runProgram(); //runs program


    return 0;
}
