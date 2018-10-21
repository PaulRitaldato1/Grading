#include <iostream>
#include <string>
#include "List.cpp"

int main()
{

    List templist = List();

    std::string inputCommand;
    std::string inputString;
    int inputLine;

    while (inputString != "quit")
    {
        std::cout << "Enter command: ";
        std::cin >> inputCommand;
        if (inputCommand == "quit")
        {
            inputString = "quit";
        }
        else if (inputCommand == "insertEnd")
        {
            std::getline(std::cin, inputString);
            if(inputString.length() > 80){
                cout << "Size over 80 characters. Setting to null, use edit to fix.";
                inputString = "";}
            templist.InsertEnd(inputString);
        }
        else if (inputCommand == "insert")
        {
            std::cin >> inputLine;
            std::getline(std::cin, inputString);
            if(inputString.length()>80)
                cout << "Size over 80 characters. Setting to null, use edit to fix.";
                inputString = "";
            templist.InsertLine(inputLine, inputString);
        }
        else if (inputCommand == "delete")
        {
            std::cin >> inputLine;
            templist.DeleteLine(inputLine);
        }
        else if (inputCommand == "edit")
        {
            std::cin >> inputLine;
            std::getline(std::cin, inputString);
            if(inputString.length() > 80)
                cout<< "Size over 80 characters. Setting to null, use edit to fix.";
                inputString = "";
            templist.EditLine(inputLine, inputString);
        }
        else if (inputCommand == "print")
        {
            templist.PrintList();
        }
        else if (inputCommand == "search")
        {
            std::getline(std::cin, inputString);
            templist.Search(inputString);
        }
    }

    return 0;
}