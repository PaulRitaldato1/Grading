#include "project1.hpp"

class LineEditor {
private:
    LinkedList<std::string> list;
public:
    LineEditor() = default;
    const int getSize() {
        return list.getSize();
    }
    void insertEnd(std::string str) {
        list.append(std::move(str));
    }
    void insert(const int& index, std::string str) {
        if(index <= list.getSize()) {
            list.insert(index, std::move(str));
        }
    }
    void remove(const int& index) {
        list.remove(index);
    }
    void edit(const int& index, std::string str) {
        list.set(index, std::move(str));
    }
    void search(const std::string& str) {
        bool found = false;
        for(int i = 0; i < list.getSize(); ++i) {
            if(list.get(i).find(str) != std::string::npos) {
                found = true;
                std::cout << i + 1 << ' ' << list.get(i) << std::endl;
            }
        }
        if(!found) {
            std::cout << "not found" << std::endl;
        }
    }
    void print() {
        for(int i = 0; i < list.getSize(); ++i) {
            std::cout << i + 1 << ' ' << list.get(i) << std::endl;
        }
    }
};

// convert numeric character to its actual integer
int charToInt(const char& c) {
    return (c - 48);
}

// check if character is not letter
bool isLegalChar(const char& c) {
    return c >= 32 && c <= 126;
}

void run() {
    LineEditor editor;
    std::string input;
    while(true) {
        while(std::getline(std::cin, input)) {
            // get rid of potential garbage characters at line end
            if(!isLegalChar(input.at(input.length() - 1))) {
                input.pop_back();
            }

            if (input.substr(0, 9) == "insertEnd") {
                std::string substring = input.substr(11, input.length() - 12);
                editor.insertEnd(substring);
            } else if (input.substr(0, 6) == "insert") {
                std::string substring = input.substr(10, input.length() - 11);
                int line = charToInt(input.at(7));
                editor.insert(line - 1, substring);
            } else if (input.substr(0, 6) == "delete") {
                int line = charToInt(input.at(7));
                if (line <= editor.getSize()) {
                    editor.remove(line - 1);
                }
            } else if (input.substr(0, 4) == "edit") {
                std::string substring = input.substr(8, input.length() - 9);
                int line = charToInt(input.at(5));
                if (line <= editor.getSize()) {
                    editor.edit(line - 1, substring);
                }
            } else if (input.substr(0, 5) == "print") {
                editor.print();
            } else if (input.substr(0, 6) == "search") {
                std::string substring = input.substr(8, input.length() - 9);
                editor.search(substring);
            } else if (input.substr(0, 4) == "quit") {
                return;
            } else {
                std::cout << "invalid command" << std::endl;
            }
        }
    }
}

int main() {
    run();
    return 0;
}
