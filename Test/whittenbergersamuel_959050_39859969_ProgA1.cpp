#include <iostream>
#include <string>
#include <vector>
#include <memory>

//////////////////////////////
//LINKED LIST IMPLEMENTATION//
//////////////////////////////

//doubly linked list using shared_ptr and templates
template <class T>
struct node {
    T data;
    std::shared_ptr<node<T>> prev;
    std::shared_ptr<node<T>> next;
};

template <class T>
class linked_list {
    private:
        int size = 0;
        std::shared_ptr<node<T>> start;
        std::shared_ptr<node<T>> end;
    
    public:
        linked_list();
        void insert(int in, T data);
        void insert_start(T data);
        void insert_end(T data);
        void search(T data);
        void edit_at(int in, T data);
        void remove_at(int in);
        void print();
        int get_size();
};

//linked_list constructor
template <class T>
linked_list<T>::linked_list() {
    start = nullptr;
    end = nullptr;
}

//inserts node with given data at given index
template <class T>
void linked_list<T>::insert(int in, T data) {
    if (in > size+1) {
        return;
    }
    if (in == size+1) {
        insert_end(data);
        return;
    }

    auto new_node = std::make_shared<node<T>>();

    new_node->data = data;
    
    auto inc = start;

    for (int i = 1; inc != nullptr && i < in; i++) {
        inc = inc->next;
    }

    if (inc == start) {
        start->prev = new_node;
        new_node->next = start;
        start = new_node;
    }
    if (inc == end) {
        end->prev->next = new_node;
        new_node->prev = end->prev;
        new_node->next = end;
        end->prev = new_node;
    }
    if (inc->prev != nullptr && inc->next != nullptr) {
        inc->prev->next = new_node;
        new_node->prev = inc->prev;
        new_node->next = inc;
        inc->prev = new_node;
    }
    size++;
}

//inserts node with given data at start of list
template <class T>
void linked_list<T>::insert_start(T data) {
    auto new_node = std::make_shared<node<T>>();
    new_node->data = data;
    new_node->prev = nullptr;

    if (start == nullptr) {
        start = new_node;
        end = new_node;
        new_node = nullptr;
    
    }
    else {
        new_node->next = start;
        start->prev = new_node;
        start = new_node;
    }
    size++;
}

//inserts node with given data at end of list
template <class T>
void linked_list<T>::insert_end(T data) {
    auto new_node = std::make_shared<node<T>>();
    new_node->data = data;
    new_node->next = nullptr;

    if (end == nullptr) {
        start = new_node;
        end = new_node;
        new_node = nullptr;
    }
    else {
        end->next = new_node;
        new_node->prev = end;
        end = new_node;
    }
    size++;
}

//searches for and prints any occurrence of given string
template <class T>
void linked_list<T>::search(T data) {
    if (size == 0) {
        return;
    }
    bool found = false;
    auto new_node = std::make_shared<node<T>>();
    new_node = start;

    for (int i = 1; i <= size && new_node != nullptr; i++) {
        if (new_node->data.find(data, 0) >= 0 && new_node->data.find(data, 0) <= new_node->data.length()) {
            std::cout << i << " " << new_node->data << std::endl;
            found = true;
        }
        new_node = new_node->next;
    }
    if (!found) std::cout << "not found" << std::endl;
} 

//edits node data at given index
template <class T>
void linked_list<T>::edit_at(int in, T data) {
    if (in > size || in < 1) {
        return;
    }
    auto new_node = std::make_shared<node<T>>();
    new_node = start;

    for (int i = 1; new_node != nullptr && i < in; i++) {
        new_node = new_node->next;
    }
    if (new_node != nullptr) new_node->data = data;
}

//removes node at given index
template <class T>
void linked_list<T>::remove_at(int in) {
    if (in > size || in < 1) {
        return;
    }
    auto removed_node = start;

    for (int i = 1; removed_node != nullptr && i < in; i++) {
        removed_node = removed_node->next;
    }

    if (removed_node == start) {
        start = removed_node->next;
    }
    if (removed_node->next != nullptr) removed_node->next->prev = removed_node->prev;
    if (removed_node->prev != nullptr) removed_node->prev->next = removed_node->next;
    size--;
}

//returns the size of the list
template <class T>
int linked_list<T>::get_size() {
    return size;
}

//prints entire list with line numbers
template<class T>
void linked_list<T>::print() {
    if (size == 0) return;
    auto new_node = std::make_shared<node<T>>();
    new_node = start;
    for (int i = 1; i <= size; i++) {
        std::cout << i << " " << new_node->data << std::endl;
        if (new_node->next != nullptr) new_node = new_node->next;
    }
}

//////////////////////////
//LINE EDITOR/USER INPUT//
//////////////////////////

//2 helper functions used to parse user input, while loop in main keeps program runnnig until user termination
std::vector<std::string> receive_input(std::string command);
void run_commands(std::vector<std::string> args, linked_list<std::string> *list);

bool running = true;
int char_limit = 80;

//takes in user input as argument, returns vector of possible arguments
std::vector<std::string> receive_input(std::string command) {
    std::vector<std::string> args;
    std::string given_command = "";
    std::string given_index = "";
    std::string given_string = "";

    given_command = command.substr(0, command.find(" ", 0));
    given_index = command.substr(command.find(" ", 0)+1);
    given_index = given_index.substr(0, given_index.find(" ", 0));
    if (command.find("\"", 0) > command.length()) {
        given_string = "";
    }
    else {
        given_string = command.substr(command.find("\"", 0)+1);
        given_string = given_string.substr(0, given_string.find("\"", 0));
    }
    args.push_back(given_command);
    args.push_back(given_index);
    args.push_back(given_string);
    
    return args;
}

//parses vector of possible commands and runs the appropriate linked list functions if input is valid
void run_commands(std::vector<std::string> args, linked_list<std::string> *list) {
    if (args.at(2).length() > char_limit) return;
    if (args.at(0) == "quit") running = false;
    else if (args.at(0) == "print" && args.at(2) == "") {
        list->print();
    }
    else if (args.at(0) == "insertEnd" && args.at(1).find("\"", 0) <= args.at(1).length() && args.at(2) != "") {
        list->insert_end(args.at(2));
    }
    else if (args.at(0) == "insert" && args.at(1).find("\"", 0) > args.at(1).length() && args.at(2) != "") {
        try {
            list->insert(std::stoi(args.at(1)), args.at(2));
        }
        catch(std::invalid_argument e) {
            std::cout << "error: invalid argument" << std::endl;
        }
    }
    else if (args.at(0) == "edit" && args.at(1).find("\"", 0) > args.at(1).length() && args.at(2) != "") {
        try {
            list->edit_at(std::stoi(args.at(1)), args.at(2));
        }
        catch(std::invalid_argument e) {
            std::cout << "error: invalid argument" << std::endl;
        }
    }
    else if (args.at(0) == "delete" && args.at(1).find("\"", 0) > args.at(1).length() && args.at(2) == "") {
        try {
            list->remove_at(std::stoi(args.at(1)));
        }
        catch(std::invalid_argument e) {
            std::cout << "error: invalid argument" << std::endl;
        }
    }
    else if (args.at(0) == "search" && args.at(1).find("\"", 0) < args.at(1).length() && args.at(2) != "") {
        list->search(args.at(2));
    }
}

//main function, loop keeps program running until user quits
int main()
{
    linked_list<std::string> *list = new linked_list<std::string>();
    std::string input = "";

    while (running) {
        std::getline(std::cin, input);
        run_commands(receive_input(input), list);
    }
    delete list;

    return 0;
}
