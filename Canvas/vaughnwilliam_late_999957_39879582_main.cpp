#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

class Node {
    public:
        Node* next = nullptr;
        string data;
        Node(string s) {
            data = s;
        }
};

class LinkedList {
    // This is a singly linked list with the methods corresponding with the
    // commands given by the user.

    public:
        Node* head = nullptr;
        int size = 0;
        void insertEnd(string s);
        void insertAt(int line, string s);
        void deleteLine(int line);
        void editLine(int line, string s);
        void print();
        void search(string s);
        bool isInBounds(int line);
};

bool LinkedList::isInBounds(int line) {
    // This checks if a line chosen for insertion is within insertion bounds.
    if (line < 1 || line > size + 1) {
        return false;
    }
    return true;
}

bool isLessThan80Char(string s) {
    // This method confirms that a string isn't too long for a given line.
    if (s.length() <= 80) {
        return true;
    }
    return false;
}

void LinkedList::insertEnd(string s) {
    // Inserts line at the end of the list.
    if (isLessThan80Char(s)) {
        if (head != nullptr) {
            Node* cursor = head;
            while (cursor->next != nullptr) {
                // iterating until we find the tail node.
                cursor = cursor->next;
            }
            // appending to tail
            cursor->next = new Node(s);
         }
         else {
             // if the head doesn't exist, we add the node there.
             head = new Node(s);
         }
         size++;
     }
}

void LinkedList::print() {
    // loops over all nodes until tail, printing the data at every node in order
    int lineCount = 1;

    Node* cursor = head;
    if (cursor != nullptr) {
        while (cursor !=nullptr) {
            cout << lineCount << " " << cursor->data << endl;
            cursor = cursor->next;
            lineCount++;
        }
    }
}

void LinkedList::insertAt(int line, string s) {
    // inserts string at index
    if (isLessThan80Char(s)) {
        if (isInBounds(line)) {
            Node* n = new Node(s);

            if (head == nullptr && line == 1) {
                // if we're trying to add to the beginning of list and there's
                // no head, we just set the new node to the head.
                head = n;
            }
            else {
                // here we iterate over the nodes until we find the node before
                // our target line node, then do the proper setup.
                Node* cursor = head;

                for (int i = 1; i < line - 1; i++) {
                    cursor = cursor->next;
                }

                if (cursor->next != nullptr) {
                    n->next = cursor->next;
                }
                cursor->next = n;
            }
            size++;
        }
    }
}

void LinkedList::deleteLine(int line) {
    // deletes line at line number 'line'
    if (isInBounds(line) && line <= size) {
        Node* cursor = head;

        for (int i = 1; i < line - 1;  i++) {
            cursor = head->next;
        }

        if (line == 1) {
            // if we're trying to delete the head, we need to make sure it exists
            // and if so, we need to make sure we link things up right
            if (head->next != nullptr) {
                head = head->next;
            }
            else {
                head = nullptr;
            }
        }
        else if (cursor->next != nullptr && cursor->next->next != nullptr) {
            // if we're deleting somewhere in the middle, we need to make sure
            // we link everything up
            cursor->next = cursor->next->next;
        }
        else {
            cursor->next = nullptr;
        }
    }
}

void LinkedList::editLine(int line, string s) {
    deleteLine(line);
    insertAt(line, s);

}

void LinkedList::search(string s) {
    // performs search using string.find()

    Node* cursor = head;

    int line = 1;
    vector<int> foundAt;
    vector<Node*> locations;

    if (head != nullptr && head->next == nullptr) {
        if ((head->data).find(s) != std::string::npos) {
            foundAt.push_back(1);
            locations.push_back(head);
        }
    }
    else if (head != nullptr) {
        while (cursor != nullptr) {

            if ((cursor->data).find(s) != std::string::npos) {
                foundAt.push_back(line);
                locations.push_back(cursor);
            }

            cursor = cursor->next;
            line++;
        }
    }


    if (foundAt.size() > 0) {
        for (int i = 0; i < foundAt.size(); i++) {
            cout << foundAt.at(i) << " " << locations.at(i)->data
 << endl;
        }
    }
    else {
        cout << "not found" << endl;
    }
}

class Command {
    // this class allows us to conveniently pass around arguments when a command
    // is parsed!
    public:
        enum Name { InsertEnd, Insert, Delete, Edit, Print, Search, Quit, NotFound };
        int lineNumber = -1;
        string str;
        Name name;

        Command(Name n) {
            name = n;
        }
        Command(Name n, int line) {
            name = n;
            lineNumber = line;
        }
        Command(Name n, int line, string s) {
            name = n;
            lineNumber = line;
            str = s;
        }
        Command(Name n, string s) {
            name = n;
            str = s;
        }
};

bool isInteger(string s) {
    // confirms a whole string is an integer before conversion
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool isString(string s) {
    // a string in a command is only valid if it is enclosed in quotes!
    if (s[0] == '\"' && s[s.length() - 1] == '\"') {
        return true;
    }

    return false;
}

string cleanQuotes(string s) {
    // removes quotes from valid strings for actual storing in node->data!
    return s.substr(1, s.length() - 2);
}

Command* parseCommand(string cmd) {

    // parses user input into commands

    vector<string> words;

    string currentWord = "";
    bool quoteStart = false;

    // iterates over user input string, tokenizing words to convert into commands

    for (int i = 0; i < cmd.length(); i++) {
        if (cmd[i] == '"') {
          if (quoteStart && i == cmd.length() - 1) {
            quoteStart = false;
          }
          else {
            quoteStart = true;
          }
        }
        if (cmd[i] == ' ' && !quoteStart) {
            words.push_back(currentWord);
            currentWord = "";
        }
        else if (i == cmd.length() - 1) {
            currentWord += cmd[i];
            words.push_back(currentWord);
            currentWord = "";
        }
        else {
            currentWord += cmd[i];
        }
    }


    string command = words.at(0);
    // in these blocks, we do some validation of  input (making sure args are
    // correct types, or in range, etc.)

    if (command == "insertEnd") {
        if (words.size() == 2) {
            string textToInsert = words.at(1);

            if (textToInsert[0] == '\"' && textToInsert[textToInsert.length() - 1] == '\"') {
                return new Command(Command::Name::InsertEnd, cleanQuotes(textToInsert));
            }
        }
    }
    else if (command == "insert") {
        if (words.size() == 3) {
            if (isInteger(words.at(1)) && isString(words.at(2))) {
                 return new Command(Command::Name::Insert, stoi(words.at(1)), cleanQuotes(words.at(2)));
            }
        }
    }
    else if (command == "delete") {
        if (isInteger(words.at(1))) {
            return new Command(Command::Name::Delete, stoi(words.at(1)));
        }
    }
    else if (command == "edit") {
        if (isInteger(words.at(1)) && isString(words.at(2))) {
            return new Command(Command::Name::Edit, stoi(words.at(1)), cleanQuotes(words.at(2)));
        }
    }
    else if (command == "print") {
        return new Command(Command::Name::Print);
    }
    else if (command == "search") {
        if (isString(words.at(1))) {
            return new Command(Command::Name::Search, cleanQuotes(words.at(1)));
        }
    }
    else if (command == "quit") {
        return new Command(Command::Name::Quit);
    }

    // if any cases fail within these conditionals, we just return a command not found
    return new Command(Command::Name::NotFound);
}


int main() {
    LinkedList lines;

    while (true) {
        string input;
        getline(cin, input);
        if (input.length() > 0) {
            Command* command = parseCommand(input);

            if (command->name == Command::Name::Quit) {
                return 0;
            }
            else if (command->name == Command::Name::InsertEnd) {
                lines.insertEnd(command->str);
            }
            else if (command->name == Command::Name::Insert) {
                lines.insertAt(command->lineNumber, command->str);
            }
            else if (command->name == Command::Name::Print) {
                lines.print();
            }
            else if (command->name == Command::Name::Delete) {
                lines.deleteLine(command->lineNumber);
            }
            else if (command->name == Command::Name::Edit) {
                lines.editLine(command->lineNumber, command->str);
            }
            else if (command->name == Command::Name::Search) {
                lines.search(command->str);
            }

            else if (command->name == Command::Name::NotFound) {
            }
        }
    }
}
