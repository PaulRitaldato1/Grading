#include<bits/stdc++.h>

//Function declarations
struct node *createNode(std::string value);
void insertNodeEnd(struct node *, std::string);
void insertNodeSelected(struct node *, int, std::string);
void deleteNode(struct node *, int);
void editNode(struct node *, int, std::string);
void printList(struct node *);
void searchList(struct node *, std::string);

//node structure
struct node {
    std::string data;
    struct node *next;
};

//Makes sure the first node/line is NULL
struct node *start = NULL;

int main() {

    std::string command; //stores input
    std::string temp; //stores text
    std::string str_index; //index stored as string
    int index, p; //temp storage
    std::stringstream ss; //for creating string streams

    while (true) //Infinite loop until user quits
    {
        getline(std::cin, command);
        if (command == "quit") {       //ends program
            break; //exit from loop
        } else if (command == "print") {     // prints current list
            printList(start);
        } else if (command.substr(0, 6) == "search") {      //searches list for text
            temp = command.substr(8);
            temp.pop_back();
            searchList(start, temp);
        } else if (command.substr(0, 4) == "edit") {     // edits node in list
            p = command.find(" ", 5);
            str_index = command.substr(5, p - 5);

            ss << str_index;
            ss >> index;
            ss.clear();

            temp = command.substr(p + 1);
            temp.pop_back();
            editNode(start, index, temp);
        } else if (command.substr(0, 6) == "delete") {    //deletes node in list
            str_index = command.substr(7);

            ss << str_index;
            ss >> index;
            ss.clear();

            deleteNode(start, index);
        } else if (command.substr(0, 9) == "insertEnd") {   //insert text into new node at the end of the list
            temp = command.substr(11);
            temp.pop_back();
            insertNodeEnd(start, temp);
        } else  {                          //insert node where chosen
            p = command.find(" ", 7);

            str_index = command.substr(7, p - 7);

            ss << str_index;
            ss >> index;
            ss.clear();

            temp = command.substr(p + 2);
            temp.pop_back();
            insertNodeSelected(start, index, temp);
        }
    }
    return 0;
}

//creates new node/line
struct node *createNode(std::string value) {
    struct node *n = new node;
    n->data = value;
    n->next = NULL;
    return (n);
}

//inserts a new node/line at the end of the list
void insertNodeEnd(struct node *p, std::string temp) {
    struct node *n;
    n = createNode(temp);

    if (start == NULL)
        start = n;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = n;
    }
}

//inserts a new node/line where specified
void insertNodeSelected(struct node *p, int index, std::string temp) {
    struct node *prev = NULL;
    struct node *n = createNode(temp);
    int i;

    for (i = 1; i < index; i++) {
        prev = p;
        p = p->next;
    }

    if (prev == NULL) {
        n->next = start;
        start = n;
    } else {
        n->next = p;
        prev->next = n;
    }
}

//delete node/line where specified
void deleteNode(struct node *p, int index) {
    struct node *q;
    struct node *prev = NULL;
    int i;
    for (i = 1; i < index; i++) {
        prev = p;
        p = p->next;
    }
    if (prev == NULL) {
        q = p;
        start = start->next;
    } else {
        q = p;
        prev->next = p->next;
    }
    delete q;
}

//edit node/line where specified
void editNode(struct node *p, int index, std::string temp) {
    int i;

    for (i = 1; i < index; i++) {
        p = p->next;
    }
    p->data = temp;
}

//searches for specified string and prints out the location
void searchList(struct node *p, std::string temp) {
    int i = 1;
    while (p) {
        if (p->data.find(temp) != -1) {       //found
            std::cout << i << " " << p->data << std::endl;
            break;
        }
        p = p->next;
        i++;
    }
    if (p == NULL) //not found
        std::cout << "not found" << std::endl;
}

void printList(struct node *p) {
    if (p == NULL)
        printf("Document is empty\n");
    else {
        int i = 1;
        while (p) {
            std::cout << i << " " << p->data << std::endl;
            p = p->next;
            i++;
        }
    }
}