#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "List.h"

using namespace std;

//Default constructor for initialization, no overloading necessary
List::List()
{

    head = NULL;
    temp = NULL;
}
// Method to insert node at the end of the linked templist
//Essentially a push method
void List::InsertEnd(std::string input)
{
    nodePtr n = new node;
    n->next = NULL;
    n->data = input;
    nodePtr curr;

    if (head != NULL)
    {
        curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = n;
    }
    else
    {
        head = n;
    }
}
void List::InsertLine(int lineNum, std::string input)
{
    nodePtr n = new node;
    n->next = NULL;
    n->data = input;
    int count = 1;
    nodePtr curr = head;

    if (head == NULL)
    {
        while (count < lineNum)
        {
            InsertEnd("");

            if (count == 1)
                curr = head;
            else
                curr = curr->next;

            ++count;
        }
    }
    else
    {
        while (count < lineNum)
        {
            if (curr->next == NULL)
            {
                InsertEnd("");
                curr = curr->next;
                ++count;
            }
            else
            {
                curr = curr->next;
                ++count;
            }
        }
    }

    if (count == lineNum)
    {
        if (curr->next == NULL)
        {
            curr->next = n;
        }
        else
        {
            nodePtr temp = curr->next;
            curr->next = n;
            n->next = temp;
        }
    }
}

void List::DeleteLine(int lineNum)
{
    nodePtr curr = head;

    if (head == NULL)
    {
        return;
    }

    nodePtr temp;
    int count = 1;

    while (count < lineNum - 1)
    {
        if (curr->next == NULL)
        {
            cout << "Line does not exist.\n";
            return;
        }

        curr = curr->next;
        ++count;
    }
    if (count == lineNum - 1)
    {
        if (curr->next->next != NULL)
            temp = curr->next->next;
        else
            temp = NULL;
        delete curr->next;
        curr->next = temp;
    }
}

void List::Search(std::string input)
{
    nodePtr curr = head;
    int count = 1;

    if (head == NULL)
    {
        return;
    }
    while (curr != NULL)
    {
        if (curr->data.find(input) != curr->data.npos)
        {
            cout << count << " " << curr->data << '\n';
        }
        curr = curr->next;
        count++;
    }
}

void List::EditLine(int lineNum, std::string input)
{
    nodePtr curr = head;
    int count = 1;

    if (head == NULL)
    {
        return;
    }
    while (count < lineNum)
    {
        curr = curr->next;
        count++;
    }
    if (count == lineNum)
    {
        curr->data = input;
    }
}

void List::PrintList()
{
    nodePtr curr;
    int count = 1;
    curr = head;
    if (curr == NULL)
    {
        cout << "No lines in list.\n";
        return;
    }

    cout << count << " " << curr->data << endl;
    while (curr->next != NULL)
    {
        curr = curr->next;
        count++;
        cout << count << " " << curr->data << endl;
    }
}