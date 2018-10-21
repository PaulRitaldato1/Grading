#include <iostream>
#include <string>
#include "List.cpp"
#include <sstream>
using namespace std;

// Finds int in string
int findInt(string str)
{

    std::stringstream ss;
    ss << str;

    int found = -1;
    std::string temp;

    while (std::getline(ss, temp, ' '))
    {
        if (std::stringstream(temp) >> found)
        {
            return found;
        }
    }

    return found;
}

int main(int argc, const char *argv[])
{

    List templist = List();

    string inputCommand;
    string inputString;

    while (inputString != "quit")
    {

        getline(cin, inputCommand);
        if (inputCommand.find("quit") != -1)
        {
            inputString = "quit";
        }
        else if (inputCommand.find("insertEnd") != -1)
        {
            inputString = "insertEnd";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            templist.InsertEnd(toAppend);
        }
        else if (inputCommand.find("insert") != -1)
        {
            inputString = "insert";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            int pos = findInt(toAppend);
            string posStr = to_string(pos);
            toAppend = toAppend.erase(inputCommand.find(posStr), posStr.length());
            templist.InsertLine(pos, toAppend);
        }
        else if (inputCommand.find("delete") != -1)
        {
            inputString = "delete";
            int pos = findInt(inputCommand);
            templist.DeleteLine(pos);
        }
        else if (inputCommand.find("edit") != -1)
        {
            inputString = "edit";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            int pos = findInt(toAppend);
            string posStr = to_string(pos);
            toAppend = toAppend.erase(inputCommand.find(posStr), posStr.length());
            templist.EditLine(pos, toAppend);
        }
        else if (inputCommand.find("print") != -1)
        {
            inputString = "print";
            templist.PrintList();
        }
        else if (inputCommand.find("search") != -1)
        {
            inputString = "search";
            string toAppend = inputCommand.erase(inputCommand.find(inputString), inputString.length());
            templist.Search(toAppend);
        }
    }

    return 0;
}