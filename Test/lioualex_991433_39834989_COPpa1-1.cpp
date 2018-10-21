#include <string>
#include <iostream>
using namespace std;

//Copy Pasted from Stepik
// Alex Liou
// COP3530
// Programming Assignment 1: Implementing a Line Editor with a Linked List
class Node{
    public:
        string text;
        Node *next;  
};

class LinkedList{
    //Head Node, kept private so it can remain untouched by accidental outside influences.
    private:
        Node * head;
    public:
        //Constructor, just to shut up errors.
        LinkedList();

        void insertEnd(string t);

        void insertAt(int index, string t);

        void deleteLine(int index);

        void edit(int index, string t);

        void print();

        void search(string t);

        void quit();

};

LinkedList :: LinkedList()
{
    Node* head = NULL;
}

//Append a node to the end of the list with String t
void LinkedList :: insertEnd(string t)
{
    if (head == NULL)
    {
        head = new Node();
        head->text = t;
        head->next = NULL;
    } else {
        Node* start = head;
        while (head->next != NULL)
        {
            head = head->next;
        }
        Node* n = new Node();
        n->text = t;
        head->next = n;
        n->next = NULL;
        head = start;
        
    }
}

//Iterates through Linked List nodes until string t is found
void LinkedList :: search(string t)
{
    Node* temp = head;
    int i = 1;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->text.find(t) != string::npos)
        {
            cout << i << ' ' << temp->text << "\n";
            if (found == false)
            {
                found = true;
            }
        }
        i++;
        temp = temp->next;
    }
    if (found != true)
    {
        //cout << "not found - search" << "\n";
    }
}

//Iterates through Linked List nodes, printing each string t within each node
void LinkedList :: print()
{
    Node* temp = head;
    int i = 1;
    while (temp != NULL)
    {
        cout << i << ' ' << temp->text << "\n";
        temp = temp->next;
        i++;
    }
}

//Iterates through Linked List until reaching index n and assigning string t to the node at index n.
void LinkedList :: edit(int n, string t)
{
    Node* temp = head;
    int i = 1;
    while (temp != NULL)
    {
        if (i == n)
        {
            temp->text = t;
            return;
        }
        temp = temp->next;
        i++;
    }
    //cout << "not found - edit" << "\n";
}


//Iterates through list until reaching index n then unlinked current node and deletes it.
void LinkedList :: deleteLine(int n)
{
    if (head == NULL)
    {
        return;
    }
    else if (n == 1)
    {
        Node *temp = head;
        head = head->next;
        delete(temp);
        return;
    } else {
        Node *temp = head->next;
        Node *prev = head;
        int i = 2;
        while (temp != NULL)
        {
            if (i == n)
            {
                prev->next = temp->next;
                delete(temp);
                return;
            }
            temp = temp->next;
            prev = prev->next;
            i++;
        }
    }
    //cout << "not found - deleteLine";
}

//Iterates through Linked List until index n is reached then insert new node with string t into list.
void LinkedList :: insertAt(int n, string t)
{   int i;
    if (n == 1)
    {
        Node *temp = new Node();
        temp->text = t;
        temp->next = head;
        head = temp;
        return;
    } else {
        Node *temp = head->next;
        Node *prev = head;
        i = 2;
        while (temp != NULL)
        {
            if (i == n)
            {
                Node* N = new Node();
                N->text = t;
                prev->next = N;
                N->next = temp;
                return;
            }
            temp = temp->next;
            prev = prev->next;
            i++;
        }
        if (i == n)
        {
            Node* N = new Node();
            N->text = t;
            prev->next = N;
            N->next = temp;
            return;
        } else {
            //cout << "not found - insertAt" << "\n";
        }
    }
}

        //your line editor implementation here

int main()
{
    LinkedList* LL = new LinkedList();
    bool exit = false;
    while (exit == false)
    {
        string line;
        getline(cin, line);
        string delimiter = " ";
        string command = line.substr(0, line.find(delimiter));
        if (command.compare("insertEnd") == 0)
        {
            size_t begin = line.find("\"");
            size_t end = line.find("\"", begin+1);
            int b = static_cast<int>(begin);
            int e = static_cast<int>(end);
            string text = line.substr(b+1, e-1);
            string t = text.substr(0,e-b-1);
            LL->insertEnd(t);
        } else if (command.compare("insert") == 0){
            size_t begin = line.find(" ");
            size_t end = line.find(" ", begin+1);
            int b = static_cast<int>(begin);
            int e = static_cast<int>(end);
            string num = line.substr(b+1, e-3);
            string n = num.substr(0,e-b-1);
            int number = stoi(n);
            
            begin = line.find("\"");
            end = line.find("\"", begin+1);
            b = static_cast<int>(begin);
            e = static_cast<int>(end);
            string text = line.substr(b+1, e-3);
            string t = text.substr(0,e-b-1);
            LL->insertAt(number, t);
        } else if (command.compare("print") == 0){
            LL->print();
        } else if (command.compare("search") == 0){
            size_t begin = line.find("\"");
            size_t end = line.find("\"", begin+1);
            int b = static_cast<int>(begin);
            int e = static_cast<int>(end);
            string text = line.substr(b+1, e-3);
            string t = text.substr(0,e-b-1);
            LL->search(t);
        } else if (command.compare("quit") == 0){
            exit = true;
        } else if (command.compare("edit") == 0){
            size_t begin = line.find(" ");
            size_t end = line.find(" ", begin+1);
            int b = static_cast<int>(begin);
            int e = static_cast<int>(end);
            string num = line.substr(b+1, e-3);
            string n = num.substr(0,e-b-1);
            int number = stoi(n);
            
            begin = line.find("\"");
            end = line.find("\"", begin+1);
            b = static_cast<int>(begin);
            e = static_cast<int>(end);
            string text = line.substr(b+1, e-3);
            string t = text.substr(0,e-b-1);
            LL->edit(number, t);
        } else if (command.compare("delete") == 0){
            size_t begin = line.find(" ");
            size_t end = line.find(" ", begin+1);
            int b = static_cast<int>(begin);
            int e = static_cast<int>(end);
            string num = line.substr(b+1, e-3);
            string n = num.substr(0,e-b-1);
            int number = stoi(n);
            LL->deleteLine(number);
        }
        
    }
    
}