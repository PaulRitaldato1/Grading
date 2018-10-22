#include "main.hh"

#include <iostream>
#include <sstream>
#include <climits>
#include <fstream>

#include "LinkedList.cc"

using namespace std;

bool verbose;
LinkedList<string> lines;

int main() noexcept {
    while (true) {
        string str;
        queue<string> arguments;
        getline(cin, str);
        stringstream stream(str);
        while (stream >> str) {
            arguments.push(str);
        }
        if (!processCommand(arguments)) {
            return 0;
        }
    }
}

int parseInt(const string &arg, int min, int max) throw(invalid_argument) {
    errno = 0;
    char *end;
    long num = strtol(arg.c_str(), &end, 10);
    if (*arg.c_str() == '\0' || *end != '\0') {
        throw invalid_argument("Input " + arg + " is not an integer.");
    } else if (errno == ERANGE && (num == LONG_MAX || num == LONG_MIN) || num > max || num < min) {
        throw invalid_argument("Input " + arg + " must be in range [" + to_string(min) + "," + to_string(max) + "]");
    }
    return num;
}

string parseString(queue<string> &arguments) throw(invalid_argument) {
    if (arguments.empty()) {
        throw invalid_argument("Not enough arguments.");
    }
    string str = arguments.front();
    arguments.pop();
    return str;
}

string parseQuotedString(queue<string> &arguments) throw(invalid_argument) {
    string str = parseString(arguments);
    if (str.front() != '"') {
        throw invalid_argument("Expected string to begin with \".");
    }
    str = str.substr(1);
    while (!arguments.empty()) {
        str += " " + arguments.front();
        arguments.pop();
    }
    if (str.empty() || str.back() != '"') {
        throw invalid_argument("Expected string to terminate with \".");
    }
    str.pop_back();
    return str;
}

bool processCommand(queue<string> &arguments) noexcept {
    try {
        string str = parseString(arguments);
        if (str == "file") {
            str = parseString(arguments);
            ifstream file("tests/" + str + ".txt");
            if (file.is_open()) {
                lines.clear();
                cout << str << ":" << endl << endl;
                while (getline(file, str)) {
                    queue<string> command;
                    stringstream stream(str);
                    while (stream >> str) {
                        command.push(str);
                    }
                    processCommand(command);
                }
                cout << endl;
            } else if (verbose) {
                cout << "Invalid file name '" << str << "'." << endl;
            }
        } else if (str == "insertEnd") {
            lines.add(parseQuotedString(arguments));
        } else if (str == "insert") {
            int index = parseInt(parseString(arguments), 1, lines.getSize() + 1);
            lines.insert(index - 1, parseQuotedString(arguments));
        } else if (str == "delete") {
            if (!lines.isEmpty()) {
                lines.remove(parseInt(parseString(arguments), 1, lines.getSize()) - 1);
            } else if (verbose) {
                cout << "No lines to delete." << endl;
            }
        } else if (str == "edit") {
            if (!lines.isEmpty()) {
                int index = parseInt(parseString(arguments), 1, lines.getSize());
                lines.set(index - 1, parseQuotedString(arguments));
            } else if (verbose) {
                cout << "No lines to delete." << endl;
            }
        } else if (str == "print") {
            for (auto entry : lines) {
                cout << entry.first + 1 << " " << entry.second << endl;
            }
        } else if (str == "search") {
            string search = parseQuotedString(arguments);
            bool found = false;
            for (auto entry : lines) {
                if (entry.second.find(search) != -1) {
                    cout << entry.first + 1 << " " << entry.second << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "not found" << endl;
            }
        } else if (str == "clear") {
            lines.clear();
        } else if (str == "verbose") {
            if (verbose = !verbose) {
                cout << "Enabled verbose mode; errors will now be reported." << endl;
            }
        }else if (str == "quit") {
            return false;
        } else if (verbose) {
            cout << "Invalid command '" << str << "'." << endl;
        }
    } catch (invalid_argument &e) {
        if (verbose) {
            cout << e.what() << endl;
        }
    }
    return true;
}