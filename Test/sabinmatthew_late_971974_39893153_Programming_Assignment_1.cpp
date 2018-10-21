#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

class List {
   private:
    typedef struct node {
        std::string line;
        int index;
        node* next;
    }* nodePtr;

    node* head;
    node* curr;
    node* temp;

   public:
    List();
    void insertEnd(std::string statements);
    void insert(int insNum, std::string statements);
    void deleteNode(int delNum);
    void edit(int editNum, std::string statements);
    void search(std::string statements);
    void print();
};

List::List() {
    head = NULL;
    curr = NULL;
    temp = NULL;
}

void List::insertEnd(std::string statements) {
    nodePtr n = new node;
    n->next = NULL;
    n->line = statements;

    if (head != NULL) {
        curr = head;
        while (curr->next != NULL) {
            temp = curr;
            curr = curr->next;
            curr->index = temp->index+1;
            temp = curr;
        }
        curr->next = n;
        n->index = curr->index+1;
    }
    else {
        head = n;
        n->index = 1;
    }
}

void List::insert(int insNum, std::string statements) { //insert function does not work, creates
    nodePtr n = NULL;									//output "segmentation fault (core dumped)"
    n->line = statements;
    temp = head;
    curr = head;
    while (curr->index != insNum){
        temp = curr;
        curr = curr->next;
    }
    temp->next = n;
    n->next = curr;
    n->index = curr->index;
}

void List::deleteNode(int num) {
    nodePtr delPtr = NULL;
    temp = head;
    curr = head;
    while (curr != NULL && curr->index != num) {
        temp = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        std::cout << "not found" << std::endl;
    }
    else {
        delPtr = curr;
        curr = curr->next;
        temp->next = curr;
        curr->index = curr->index-1;
        delete delPtr;
    }
}

void List::edit(int num, std::string statements) {
    if (head != NULL) {
        curr = head;
        while (curr->index != num) {
            curr = curr->next;
        }
        curr->line = statements;
    }
    else {
        std::cout << "list is empty" << std::endl;
    }
}

void List::search(std::string statements) {
    if (head != NULL) {
        curr = head;
        bool contains = false;
        while (curr->next != NULL) {
            std::string compLine = curr->line;
            std::size_t num = compLine.find(statements);
            if (num > 80) {
                curr = curr->next;
            }
            else {
                std::cout << curr->index << " " << curr->line << std::endl;
                curr = curr->next;
                contains = true;
            }
        }
        std::string compLine = curr->line;
        std::size_t num = compLine.find(statements);
        if (num > 80) {
        curr = curr->next;
        }
        else {
            std::cout << curr->index << " " << curr->line << std::endl;
            contains = true;
        }
        if (!contains) {
            std::cout << "not found" << std::endl;
        }
    }
    else {
        std::cout << "list is empty" << std::endl;
    }
}

void List::print() {
    curr = head;
    while (curr != NULL) {
        std::cout << curr->index << " " << curr->line << std::endl;
        curr = curr->next;
    }
}

int main()
{
    List linkedList;
    std::string statements;
    std::string tempStatement;
    std::string command;

    while (getline(std::cin, statements)) {
        tempStatement = statements;

        command = tempStatement.substr(0, tempStatement.find(" "));
        if (command == "insertEnd") {
            std::string toIns = tempStatement.substr(11, tempStatement.length() - 12);
            if (toIns.length() <= 80) {
                linkedList.insertEnd(toIns);
            }
        }
        else if (command == "insert") {
            std::string indexString = tempStatement.substr(6, tempStatement.find(" ")-1);
            std::stringstream index(indexString);
            int indexNum;
            index >> indexNum;
            std::string toIns = tempStatement.substr(10, tempStatement.length() - 11);
            if (toIns.length() <= 80) {
                linkedList.insert(indexNum, toIns);
            }
        }
        else if (command == "edit") {
            std::string indexString = tempStatement.substr(4, tempStatement.find(" ")-1);
            std::stringstream index(indexString);
            int indexNum;
            index >> indexNum;
            std::string toEdit = tempStatement.substr(8, tempStatement.length() - 9);
            if (toEdit.length() <= 80) {
                linkedList.edit(indexNum, toEdit);
            }
        }
        else if (command == "search") {
            std::string toSearch = tempStatement.substr(8, tempStatement.length() - 9);
            if (toSearch.length() <= 80) {
                linkedList.search(toSearch);
            }
        }
        else if (command == "delete") {
            std::string indexString = tempStatement.substr(6, tempStatement.find(" ")-1);
            std::stringstream index(indexString);
            int indexNum;
            index >> indexNum;
            linkedList.deleteNode(indexNum);
        }
        else if (command == "print") {
            linkedList.print();
        }
        else if (statements == "") {
            break;
        }
    }
}
