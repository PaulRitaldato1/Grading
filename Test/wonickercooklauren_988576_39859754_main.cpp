#include <iostream>
#include <string.h>
#include <string>

class Node
{
public:
    std::string line;
    Node* next;
    Node();
    Node(std::string aLine);
};

class LinkedList
{
public:
    Node* head;
    void insertEnd(std::string line);
    void insertIndex(std::string line, int i);
    void deleteIndex(int i);
    void editIndex(std::string line, int i);
    void print();
    void searchText(std::string line);
    LinkedList();
};

Node::Node()
{
    line = "";
    next = nullptr;
}

Node::Node(std::string aLine)
{
    line = aLine;
    next = nullptr;
}

LinkedList::LinkedList()
{
    head = nullptr;
}

// insertEnd inserts a line at the end of the LinkedList
void LinkedList::insertEnd(std::string line)
{
    // If head is nullptr, then insert at head
    if (head==nullptr)
        head = new Node(line);

    // Otherwise, iterate through to end and insert
    else
    {
        Node* current = head;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        Node* newLine = new Node(line);

        // Insert newLine at the end of the LinkedList
        current->next = newLine;
    }
}

// insertIndex inserts a line at a specified index,
// moving the following nodes back an index
void LinkedList::insertIndex(std::string line, int i)
{
    // If trying to insert at an index greater than 1
    // in an empty list, return
    if((i > 1) && head==nullptr)
        return;

    // If trying to insert at index = 1 and the list
    // is empty, line is inserted at the head
    else if((i==1) && head==nullptr)
        head->line = line;

    // If trying to insert at index = 1 and the list
    // is not empty, the line is inserted at the head
    // and the rest of the nodes are moved back an index
    else if(i==1)
    {
        Node* nextNode = new Node(head->line);
        nextNode->next = head->next;
        head->next = nextNode;
        head->line = line;
    }

    // If inserting at an index > 1 and the list is not
    // empty, then line is inserted at index and the rest
    // of the nodes are moved back an index
    else
    {
        Node* previous = head;
        Node* current = head->next;
        int iter = 2;
        while(current != nullptr)
        {
            if(iter == i)
            {
                Node* nextNode = new Node(current->line);
                nextNode->next = current->next;
                current->next = nextNode;
                current->line = line;
                return;
            }
            iter++;
            previous = current;
            current = current->next;
        }

        // If the index is 1 greater than the last index,
        // then insert at the end
        if(iter == i)
        {
            Node* nextNode = new Node(line);
            nextNode->next = nullptr;
            previous->next = nextNode;
        }
    }
}

// deleteIndex deletes a node at a specified index
void LinkedList::deleteIndex(int i)
{
    // If index is 1, head is set equal to the
    // following node
    if(i == 1)
    {
        head = head->next;
        return;
    }

    // If the index is greater than 1, then the
    // next of the previous node is set equal to
    // the next of the current node
    else
    {
        Node* previous = head;
        Node* current = head->next;
        int iter = 2;
        while(current != nullptr)
        {
            if(iter == i)
            {
                previous->next = current->next;
                return;
            }
            iter++;
            previous = current;
            current = current->next;
        }
    }
}

// editIndex changes the line at a specific index
void LinkedList::editIndex(std::string line, int i)
{
    Node* current = head;
    int iter = 1;
    while(current != nullptr)
    {
        // If the iterator is equal to i, then the
        // line at that node is changed to the line
        // given as an argument in the method
        if (iter == i)
        {
            current->line = line;
            return;
        }
        iter++;
        current = current->next;
    }
}

// print prints all of the nodes in the LinkedList
void LinkedList::print()
{
    Node* current = head;
    int iter = 1;
    while(current != nullptr)
    {
        std::cout << iter << " " << current->line << "\n";
        iter++;
        current = current->next;
    }
}

// searchText searches through the LinkedList for
// a specific line, if found, then line is printed
void LinkedList::searchText(std::string line)
{
    bool check = false;
    Node* current = head;
    int iter = 1;
    while(current != nullptr)
    {
        std::size_t isFound = current->line.find(line);

        // If the line in the node is equal to the
        // line given, then the line is printed
        if(isFound != std::string::npos)
        {
            std::cout << iter << " " << current->line << "\n";
            check = true;
        }
        iter++;
        current = current->next;
    }
    if(!check)
        std::cout << "not found\n";
}

int main()
{
    // Create LinkedList object
    LinkedList * listy = new LinkedList();

    // Variables for the names of the commands
    std::string insEnd = "insertEnd";
    std::string ins = "insert";
    std::string del = "delete";
    std::string ed = "edit";
    std::string pr = "print";
    std::string sch = "search";
    std::string quitW = "quit";

    // Taking initial input
    std::string inString;
    std::cin >> inString;

    // Create string iterator
    std::string::iterator iter;

    while(quitW.compare(inString) != 0)
    {
        if(inString.empty()) {
        }
        // insertEnd
        else if(inString.compare(0,9,insEnd) == 0)
        {
            std::string line;
            getline(std::cin, line);

            if((line[0] == ' ') && (line[1] == '\"'))
            {
                iter = line.end() - 1;
                if(*iter == '\"') {
                    int lng = line.length() - 3;
                    line = line.substr(2, lng);
                    // call insertEnd
                    listy->insertEnd(line);
                }
            }
        }
        // insert
        else if(inString.compare(0,6,ins) == 0)
        {
            int ind;
            std::cin >> ind;
            std::string line;
            getline(std::cin, line);

            if((line[0] == ' ') && (line[1] == '\"'))
            {
                iter = line.end() - 1;
                if(*iter == '\"') {
                    int lng = line.length() - 3;
                    line = line.substr(2, lng);
                    // call insertIndex
                    listy->insertIndex(line, ind);
                }
            }
        }
        // delete
        else if(inString.compare(0,6,del) == 0)
        {
            int ind;
            std::cin >> ind;
            // call deleteIndex
            listy->deleteIndex(ind);
        }
        // edit
        else if(inString.compare(0,4,ed) == 0)
        {
            int ind;
            std::cin >> ind;
            std::string line;
            getline(std::cin, line);

            if((line[0] == ' ') && (line[1] == '\"'))
            {
                iter = line.end() - 1;
                if(*iter == '\"') {
                    int lng = line.length() - 3;
                    line = line.substr(2, lng);
                    // call editIndex
                    listy->editIndex(line, ind);
                }
            }
        }
        // print
        else if(inString.compare(0,5,pr) == 0)
        {
            // call print
            listy->print();
        }
        // search
        else if(inString.compare(0,6,sch) == 0)
        {
            std::string line;
            getline(std::cin, line);

            if((line[0] == ' ') && (line[1] == '\"'))
            {
                iter = line.end() - 1;
                if(*iter == '\"') {
                    int lng = line.length() - 3;
                    line = line.substr(2, lng);
                    // call searchText
                    listy->searchText(line);
                }
            }
        }
        else
        {
            // invalid, so it's ignored
        }
        std::cin >> inString;
    }
}