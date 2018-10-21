#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

class Node
{
public:
    string words;
    Node* next = NULL;
};

//returns number of nodes in linked list
int ListLength(Node *head)
{
    int counter = 0;
    Node* newNode = new Node;
    newNode->next = head;
    while (newNode->next != NULL)
    {
        counter++;
        newNode = newNode->next;
    }
    return counter;
}

//searches linked list is the string is located anywhere in list
void SearchLines(Node *head, string text)
{
    Node *probe = new Node;
    probe->next = head;
    int counter = 1;
    bool foundSomething = false;
    while (probe->next != NULL)
    {
        string temp = probe->next->words;
        size_t found = temp.find(text);
        if (found != string::npos)
        {
            cout << counter << " " << temp.data() << endl;
            foundSomething = true;
        }
        counter++;
        probe->next = probe->next->next;
    }
    if (!foundSomething)
    {
        cout << "not found" << endl;
    }
    return;
}

//deletes a specific line in the linked list
Node* DeleteLine(Node *head, int position)
{
    int numberOfNodes = ListLength(head);
    if (position > numberOfNodes)
    {
        return head;
    }
    //if deleting head
    if (position == 1)
    {
        return head->next;
    }
    //if deleting 2nd
    else if (position == 2)
    {
        head->next = head->next->next;
        return head;
    }
    //if deleting middle
    else if (position > 1)
    {
      Node* probe = new Node;
      probe->next = head;
      bool keepGoing = true;
      while (keepGoing)
      {
          if (position == 2)
          {
              probe->next->next = probe->next->next->next;
              keepGoing = false;
          }
          position--;
          probe->next = probe->next->next;
      }
      return head;
    }
}

//edits a specific line
Node* EditLine(Node *head, string text, int position)
{
    //if first
    if (position == 1)
    {
        head->words = text;
    }
    //if not first
    else
    {
        int currentPosition = 1;
        Node *newNode = new Node;
        newNode->next = head;
        while (position != -1)
        {
            newNode->next = newNode->next->next;
            currentPosition++;
            if (currentPosition == position)
            {
                newNode->next->words = text;
                position = -1;
            }
            if (newNode->next == NULL)
            {
                position = -1;
            }
        }
    }
    return head;
}

//inserts node at end of linked list
Node* InsertEnd(Node *head, string text)
{
    Node* newNode = new Node;
    //inserting first element
    if (head->next == head)
    {
        head->words = text;
        head->next = NULL;
    }
    //inserting second element
    else if (head->next == NULL)
    {
        head->next = newNode;
        newNode->next = NULL;
        newNode->words = text;
    }
    //inserting element at the end
    else
    {
        string holder;

        Node* temp = new Node;
        temp->words = text;
        temp->next = head->next;
        head->next = temp;

        newNode = temp;

        while (newNode->next != NULL)
        {
            holder = newNode->words;
            newNode->words = newNode->next->words;
            newNode->next->words = holder;
            newNode = newNode->next;
        }
    }
    return head;
}

//inserts node in specific position of linked list
Node* specificInsert(Node *head, string text, int position)
{

    int counter = ListLength(head) + 1;

    //error checking
    if (position < 1)
    {
        return head;
    }
    //insert at head
    else if (position == 1)
    {
        Node* begin = new Node;
        begin->words = text;
        begin->next = head;
        return begin;
    }
    //insert in middle
    else if (position < counter)
    {
        Node* middle = new Node;
        middle->words = text;
        middle->next = head->next;
        head->next = middle;
        if (position == 2)
        {
            return head;
        }
        else if (position > 2)
        {
            Node* probe = new Node;
            probe->next = middle;
            for (int i = 2; i < position; i++)
            {
                string holder = probe->next->words;
                probe->next->words = probe->next->next->words;
                probe->next->next->words = holder;
                probe = probe->next;
            }
            return head;
        }

    }
    //insert at end
    else if (position == counter)
    {
        return InsertEnd(head, text);
        //return head;
    }
    //insert over the amount possible
    else if (position > counter)
    {
        return head;
    }
    else
    {
        return head;
    }
}

//prints all lines in the linked list
void PrintAll(Node *head)
{
    Node* temp = new Node;
    temp = head;
    int counter = 1;
    cout <<counter << " " << temp->words << endl;;
    counter++;
    while (temp->next != NULL)
    {
        temp = temp->next;
        cout << counter << " " <<temp->words << endl;
        counter++;
    }
    return;
}

void LineEditor(Node* head)
{
    string userInput;
    bool keepGoing = true;
    while (keepGoing)
    {
        getline(cin, userInput);

        //Edit a line in a specific spot
        string input0 = userInput.data();
        input0 = input0.substr(0,4);
        if (strcmp(input0.data(), "edit") == 0)
        {
            if ((int) userInput[6] >= '0' && (int) userInput[6] <= '9')
            {
                head = EditLine(head, userInput.substr(9, userInput.length() - 10), stoi(userInput.substr(5, 2)));
            }
            else
            {
                head = EditLine(head, userInput.substr(8, userInput.length() - 9), (int) userInput[5] - 48);
            }

        }

        //Insert at end
        string input1 = userInput.data();
        input1 = input1.substr(0,9);
        if (strcmp(input1.data(), "insertEnd") == 0)
        {
            head = InsertEnd(head, userInput.substr(11, userInput.length() - 12));
        }

        //Print all lines
        if (strcmp(userInput.data(), "print") == 0)
        {
            PrintAll(head);
        }

        //Insert a line in specific spot
        string input2 = userInput.data();
        input2 = input2.substr(0,7);
        if (strcmp(input2.data(), "insert ") == 0)
        {
          if ((int) userInput[8] >= '0' && (int) userInput[8] <= '9')
          {
              head = specificInsert(head, userInput.substr(11, userInput.length() - 12), stoi(userInput.substr(7, 2)));
          }
          else
          {
              head = specificInsert(head, userInput.substr(10, userInput.length() - 11), userInput[7]-48);
          }

        }

        //Delete a specific line
        string input3 = userInput.data();
        input3 = input3.substr(0,6);
        if (strcmp(input3.data(), "delete") == 0)
        {
            if ((int) userInput[8] >= '0' && (int) userInput[8] <= '9')
            {
                head = DeleteLine(head, stoi(userInput.substr(7, 2)));
            }
            else
            {
                head = DeleteLine(head, (int)userInput[7]-48);
            }
        }

        //Search through line
        //search "text" -- print the line number and line that contains the given text.  print "not found" if it is not found
        string input4 = userInput.data();
        input4 = input4.substr(0,6);
        if (strcmp(input4.data(), "search") == 0)
        {
            SearchLines(head, userInput.substr(8, userInput.length() - 9));
        }

        //Quit the program
        if (strcmp(userInput.data(), "quit") == 0)
        {
            return;
        }
    }
}

int main (void)
{
    Node* head = new Node;
    head->next = head;
    LineEditor(head);
    return 0;
}
