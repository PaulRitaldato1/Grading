#include <iostream>
#include <sstream>
#include <algorithm>
#include "linked_list.h"

/**
 * Read a string argument from a command string
 * @param commandPart A string to read from
 * @return the contents of the quotes, or an empty string if bad.
 */
std::string getStringArg(std::string& commandPart) {
    auto start = commandPart.find('\"') + 1; // Find first quote and move inwards 1
    auto stop = commandPart.find_last_of('\"'); // Find last quote (don't move in since we use for sizing)
    if(start >= commandPart.size() || stop - start < 0) // Make sure nothing is out of bounds
        return "";
    return commandPart.substr(start, stop - start); // Return the part inside quotes
}

/**
 * Read an integer argument from a command string
 * @param commandPart String to read from. The first part of this string must be the integer to read
 * @return the first integer found, or -1 if none found
 */
int getIntegerArg(std::string& commandPart) {
    if(commandPart.empty()) // Make sure it's not empty
        return -1;
    std::stringstream stream(commandPart);
    int iarg;
    if(!std::isdigit(commandPart[0])) // Make sure the first character is a digit
        return -1;
    stream >> iarg; // Read integer
    return iarg; // Return the integer
}

int main() {
    Linked_List<std::string> lines;

    while(true) {
        std::string command;
        std::getline(std::cin, command); // Read command
        std::transform(command.begin(), command.end(), command.begin(), ::tolower); // make it lower case (for case insensitivity)

        if(command.substr(0, 9) == "insertend") { // insertEnd command
            if(command.size() < 10) { // Make sure it's big enough to have parameters
                std::cout << "Bad syntax. Use \'insertEnd \"text\"\'" << std::endl;
                continue;
            }
            command = command.substr(10); // Trim command name off
            std::string text = getStringArg(command); // Fetch string argument
            if(text.empty()) { // Make sure string isn't empty
                std::cout << "Bad syntax. Use \'insertEnd \"text\"\'" << std::endl;
                continue;
            }
            if(text.size() > 80) // Cap string to 80 characters
                text = text.substr(0, 80);


            lines.push_back(text); // Adds text to end of line editor


        } else if(command.substr(0, 6) == "insert") { // insert command
            if(command.size() < 7) { // Make sure it's big enough to have parameters
                std::cout << "Bad syntax. Use \'insert # \"text\"\'" << std::endl;
                continue;
            }
            command = command.substr(7); // Trim command name off
            int line = getIntegerArg(command); // Fetch integer argument
            if(line < 0) { // Make sure nothing went wrong reading the line number
                std::cout << "Bad syntax. Use \'insert # \"text\"\'" << std::endl;
                continue;
            }
            std::string text = getStringArg(command); // Fetch string argument
            if(text.empty()) { // Make sure string isn't empty
                std::cout << "Bad syntax. Use \'insert # \"text\"\'" << std::endl;
                continue;
            }
            if(text.size() > 80) // Cap string to 80 characters
                text = text.substr(0, 80);


            lines.insert(line - 1, text); // Insert text at specified line number


        } else if(command.substr(0, 6) == "delete") {
            if(command.size() < 7) { // Make sure it's big enough to have parameters
                std::cout << "Bad syntax. Use \'delete #\'" << std::endl;
                continue;
            }
            command = command.substr(7); // Trim command name off
            int line = getIntegerArg(command); // Fetch integer argument
            if(line < 0) { // Make sure nothing went wrong reading the line number
                std::cout << "Bad syntax. Use \'delete #\'" << std::endl;
                continue;
            }


            lines.remove(line - 1); // Removes line at specified line number


        } else if(command.substr(0, 4) == "edit") {
            if(command.size() < 5) { // Make sure it's big enough to have parameters
                std::cout << "Bad syntax. Use \'edit # \"text\"\'" << std::endl;
                continue;
            }
            command = command.substr(5); // Trim command name off
            int line = getIntegerArg(command); // Fetch integer argument
            if(line < 0) { // Make sure nothing went wrong reading the line number
                std::cout << "Bad syntax. Use \'edit # \"text\"\'" << std::endl;
                continue;
            }
            std::string text = getStringArg(command); // Fetch string argument
            if(text.empty()) { // Make sure string isn't empty
                std::cout << "Bad syntax. Use \'edit # \"text\"\'" << std::endl;
                continue;
            }
            if(text.size() > 80) // Cap string to 80 characters
                text = text.substr(0, 80);


            lines.modify(line - 1, text); // Modify text at specified line number


        } else if(command.substr(0, 5) == "print") {


            int i = 1;
            for(std::string& line : lines) { // Print out each line
                std::cout << i++ << " " << line << std::endl;
            }


        } else if(command.substr(0, 6) == "search") {
            if(command.size() < 7) { // Make sure it's big enough to have parameters
                std::cout << "Bad syntax. Use \'search \"text\"\'" << std::endl;
                continue;
            }
            command = command.substr(7); // Trim command name off
            std::string text = getStringArg(command); // Fetch string argument
            if(text.empty()) {
                std::cout << "Bad syntax. Use \'search \"text\"\'" << std::endl;
                continue;
            }


            int i = 1;
            bool found = false;
            for(std::string& line : lines) { // Check each line for text
                if(line.find(text) != -1) {
                    std::cout << i << " " << line << std::endl; // Print it if we find it
                    found = true;
                }
                i++;
            }
            if(!found) // Didn't find it
                std::cout << "not found" << std::endl;


        } else if(command.substr(0, 4) == "quit") {
            exit(0);
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }
}