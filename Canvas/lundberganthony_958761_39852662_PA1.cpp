#include <iostream>
#include <string>
#include <stdexcept>

// start of header/linked list file

#ifndef UNTITLED_PA1_H
#define UNTITLED_PA1_H

// create class node

class node
{
    //declare public variables
public:
    std::string data;
    node *next;
};
// linked list as a class
class linkedList
        {
    //declare private variables
private:
    node *head;
    // declare public variables and methods
public:
    int length;

    linkedList();

    void insert(int index, std::string docLine);

    void insertEnd(std::string text);

    void deleteAtIndex(int index);

    void edit(int index, std::string newText);

    void print();

    void search(std::string find);

};

linkedList::linkedList()
{
    length = 0;
    head = nullptr;
}
// insert at desired index
// if index is 0, replace head with new node
// otherwise, walk the list until you get to index and insert a node at that point
// increment the length
void linkedList::insert(int index, std::string docLine)
{

    node *p = new node();
    node *q = new node();
    node *r;

    if (index == 0)
    {

        p-> data = docLine;
        p -> next = head;
        head = p;
    }
    else
        {
        r = head;
        for(int i = 0;i < index ; i++)
        {
            q = r;
            r = r-> next;
        }
        p->data = docLine;
        p->next = r;
        q->next = p;
        }
    length++;
}
// insert at end
//call insert method with index of length
void linkedList::insertEnd(std::string text)
{
    insert(length, text);
}
// delete at given index
// if index is 0, move the head up by one
// otherwise, walk the list until you get to index and remove that node, connecting the previous one to the next
// increment length by -1
void linkedList::deleteAtIndex(int index)
{

    node *p;
    node *q = new node();
    p = head;

    if (index == 0)
    {
        head = head->next;
    }
    else
        {
        for(int i =0;i<index;i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
    }
    length--;
}
// edit line at index
// walk the list until you reach the index
// replace data at that node to new text
void linkedList::edit(int index, std::string newText)
{

    node *p = head;

    for(int i =0;i<index;i++)
    {
        p = p->next;
    }
    p->data = newText;
};
// print list
// cout the list while walking it
void linkedList::print()
{

    node *p = head;
    int i = 1;

    while(p != nullptr)
    {

        std::cout<< i  << " " << p->data << "\n";
        p = p->next;
        i++;
    }
}
// search for given string
// walk list
// if wanted string is found, cout the line number and whole line each time its found and make found = true
// otherwise cout that it was not found
void linkedList::search(std::string find)
{
    node *p = head;
    bool found = false;
    for(int i =0;i<length;i++)
    {
        if(p->data.find(find) != std::string::npos)
        {
            std::cout << i + 1 << " " << p->data << "\n";
            found = true;

        }
        p = p->next;
    }
    if(!found)
    {
        std::cout << "not found\n";
    }
}

#endif //UNTITLED_PA1_H
// end of header file

// beginning of main

int main()
{
    // initialize input variables and bool for while loop
    std::string instruction;
    linkedList docList;
    int index;
    std::string text;
    bool quit = false;
    // while loop to take in inputs until quit is written
    while(!quit)
    {
        // take in input up until first space
        std::cin >> instruction;
        // case of insertEnd
        // take in rest of line as input text for doc line, remove quotations and spaces at ends
        // call insertEnd method
        if (instruction == "insertEnd")
        {
            getline(std::cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            docList.insertEnd(text);
        }
        // case of insert
        // take in input until next space
        // take in rest of line as input text for doc line, remove quotations and spaces at ends
        // do nothing if index is greater than length + 1
        // otherwise call insert method
        else if (instruction == "insert")
        {
            std::cin >> index;
            getline(std::cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            if (index > docList.length + 1 )
            {
            }
            else
                {
                docList.insert(index - 1, text);
                }

        }
        // case of delete
        // take in int
        // if index is greater than length, do nothing
        // otherwise call delete method
        else if (instruction == "delete")
        {
            std::cin >> index;
            if (index > docList.length)
            {
            }
            else
                {
                docList.deleteAtIndex(index - 1);
                }
        }
        // case of edit
        // take in input up to next space as int
        // take in rest of line as input text for doc line, remove quotations and spaces at end
        // if index is greater than length, do nothing
        // otherwise call edit method
        else if (instruction == "edit")
        {
            std::cin >> index;
            getline(std::cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            if (index > docList.length )
            {
            }
            else
                {
                docList.edit(index - 1, text);
                }

        }
        // case of print
        // call print method
        else if (instruction == "print")
        {
            docList.print();
        }
        // case of search
        // take in rest of line as input text for doc line, remove quotations and spaces at ends
        // call search method
        else if (instruction == "search")
        {
            getline(std::cin, text);
            text = text.substr(text.find_first_of('"') + 1, text.find_last_of('"') -2);
            docList.search(text);
        }
        // case of quit
        // make quit = true and exit loop
        else if (instruction == "quit")
        {
            quit = true;
        }
    }
    return 0;
}
