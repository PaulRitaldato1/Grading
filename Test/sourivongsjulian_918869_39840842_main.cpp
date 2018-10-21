#include <stddef.h>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

//DEFINES
#define getText getline(cin,text); formatString(text, valid);

//LINKED LIST IMPLEMENTATION
class LinkedList
{
    private:
    struct Node
    {
        std::string data;
        Node * next;

        Node ()
        {
            next = nullptr;
            data = "";
        }
        Node (string d)
        {
            next = nullptr;
            data = d;
        }
    };
    Node * head;
    Node * tail;
    int size;

    public:
    //default constructor
    LinkedList()
    {
        head = new Node();
        tail = head;
        size = 0;
    }

    //print function
    void print()
    {
        int lineNum = 1;
        Node * current = head->next;
        while (current != nullptr)
        {
            cout << lineNum++ << " " << current->data << endl;
            current = current->next;
        }
    };

    //add function
    void add(string text, int index)
    {
        if (index < 1 || index > size +1) return;
        if (size == 0)
        {
            head->next = new Node(text);
            tail = head->next;
            size++;
            return;
        }
        if (index == size + 1)
        {
            addToEnd(text);
            return;
        }

        Node * current = head;
        
        for(int i = 0; i < index-1; i++)
        {
            current = current->next;
        }
        Node * temp = new Node(text);
        temp->next = current->next;
        current->next = temp;
        size++;
        
    };

    //add to end function
    void addToEnd(string text)
    {
        if (size == 0)
        {
            head->next = new Node(text);
            tail = head->next;
        }else
        {
            tail->next = new Node(text);
            tail = tail->next;
        }
        size++;
    };

    //delete function
    void del(int index)
    {
        //make sure it is in bounds
        if (index > size || index < 1) return;
        if (index == 1)
        {
            Node * temp = head->next;
            head->next = head->next->next;
            delete(temp);
            if (size == 1) tail = head;
            size--;
            return;
        }

        Node * current = head;
        
        for(int i = 0; i < index-1; i++)
        {
            current = current->next;
        }
        if (index == size) tail = current;
        Node * temp = current->next;
        current->next = current->next->next;
        delete(temp);
        size--;
    };

    //edit function
    void edit(string text, int index)
    {
        if (index < 1 || index > size) return;
        Node * current = head;
        for(int i = 0; i < index; i++)
        {
            current = current->next;
        }
        current->data = text;
    };

    //search function
    void search(string text)
    {
        Node * current = head->next;
        int lineNum = 1;
        bool found = false;
        while(current != nullptr)
        {
            if (current->data.find(text)!=std::string::npos)
            {
                found = true;
                cout << lineNum << " " << current->data << endl;
            }
            current = current->next;
            lineNum++;
        }
        if (!found)
        {
            cout << "not found" << endl;
        }
    }
};

//FUNCTIONS
void formatString(std::string & s, bool & valid)
{
    //trims white space at beginning and end
    while (s[0] == ' ')
    {
        s.erase(0,1);
    }
    while (s[s.size()-1] != '"')
    {
        s.pop_back();
    }

    //checks size
    if (s.length() > 82 || s.length()<2) valid = false;

    //check if string if wrapped in quotes correctly
    if (s[0] != '"' || s[s.size()-1] != '"') valid = false;

    //pops off the quotes
    s.pop_back();
    s.erase(0,1);
}

//takes valid line number input
void getLineNum (int & lineNum, bool & valid)
{ 
    if (cin >> lineNum) {
        return;
    } else {
        valid = false;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
}

//MAIN
int main()
{
    //create the linked list here
    LinkedList ll;

    //User Inputs
    string command;
    int lineNum;
    string text;

    //only runs command if valid is true
    bool valid;

    do
    {
        //takes in command
        cin >> command;

        //input are valid by default
        valid = true;

        //commands
        if (command == "insertEnd"){
            getText
            if(valid) ll.addToEnd(text);
            continue;
        }
        if (command == "insert"){
            getLineNum(lineNum, valid);
            if(valid) {getText}
            if(valid) ll.add(text, lineNum);
            continue;
        }
        if (command == "delete"){
            getLineNum(lineNum, valid);
            if(valid) ll.del(lineNum);
            continue;
        }
        if (command == "edit"){
            getLineNum(lineNum, valid);
            if(valid) {getText}
            if(valid) ll.edit(text, lineNum);
            continue;
        }
        if (command == "print"){
            ll.print();
            continue;
        }
        if (command == "search"){
            getText
            if(valid) ll.search(text);
            continue;
        }
        //clear input before next input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (command != "quit");
    return 0;
}
