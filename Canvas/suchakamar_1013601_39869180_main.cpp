//your linked list implementation here
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct LinkedList
{
    struct Node
    {
        string line;
        Node *next;

        Node(string str)
        {
            this->line = str;
            this->next = NULL;
        }
    };

    LinkedList()
    {
        this->numLines = 0;
        head = NULL;
        tail = NULL;
    }

    ~LinkedList()
    {
        Node *temp = this->head, *next = NULL;

        while (temp != NULL)
        {
            next = temp->next;
            delete temp;
            temp = next;
        }

        this->head = NULL;
        this->tail = NULL;

    }

    void InsertEnd(string line)
    {
        if (this->head == NULL)
            this->head = this->tail = new Node(line);
        else
        {
            this->tail->next = new Node(line);
            this->tail = this->tail->next;
        }
    }

    void Print()
    {
        Node *temp = this->head;
        int counter = 0;

        for (int i = 1; temp != NULL; i++, temp = temp->next)
            cout << i << " " << temp->line << endl;

    }

    int GetNumberOfLines()
    {
        Node *temp = this->head;
        int counter = 0;

        while (temp != NULL)
        {
            temp = temp->next;
            counter++;
        }
        return counter;
    }

    Node *Delete(int lineNumber)
    {
        Node *temp = head, *next = NULL, *prev = head;
        int counter = 1;

        if (lineNumber > GetNumberOfLines() || lineNumber <= 0)
            return head;

        if (lineNumber == 1)
        {
            temp = head->next;
            delete head;
            if (temp == NULL)
                head = tail = NULL;
            else
                head = temp;
            return head;
        }
        while (counter != lineNumber)
        {
            prev = temp;
            temp = temp->next;
            counter++;
        }
        next = temp->next;
        delete temp;
        prev->next = next;
        if (next == NULL)
            tail = prev;
        return head;
    }

    void Search(string searchWords)
    {
        Node *temp = head;
        int counter = 1;
        bool foundVariable = false;

        while (temp != NULL)
        {
            size_t found = temp->line.find(searchWords);
            // If string is found:
            if (found != std::string::npos)
            {
                cout << counter << " " << temp->line << endl;
                foundVariable = true;
            }
            temp = temp->next;
            counter++;
        }
        if (foundVariable == false)
            cout << "not found" << endl;
    }

    void Edit(int lineNumber, string text)
    {
        int counter = 1;
        Node *temp = head;

        while (temp != NULL)
        {
            if (counter == lineNumber)
            {
                temp->line = text;
                break;
            }

            counter++;
            temp = temp->next;
        }
    }

    void Insert(int lineNumber, string inputString)
    {
        int counter = 1;
        Node *temp = head, *next, *prev = head;

        if (lineNumber > GetNumberOfLines() + 1 || lineNumber <= 0)
            return;

        if (lineNumber == 1)
        {
            temp = head;
            head = new Node(inputString);
            head->next = temp;
            if (tail == NULL)
                tail = head;
            return;
        }
        while (counter != lineNumber)
        {
            counter++;
            prev = temp;
            temp = temp->next;
        }

        prev->next = new Node(inputString);
        prev->next->next = temp;
        if (temp == NULL)
            tail = prev->next;
    }

    Node *head;
    Node *tail;
    int numLines;
};

bool StringIsGood(string menuInput, string command)
{
    if (command == "insertEnd")
    {
        if (menuInput[command.length() + 1] != '\"' ||
            menuInput[menuInput.length() - 1] != '\"')
            return false;
    }
    if (command == "search")
    {
        if (menuInput[command.length() + 1] != '\"' ||
            menuInput[menuInput.length() - 1] != '\"')
            return false;
    }
    return true;
}

int GetLineNumberAndLine(string input, string *lineContent, string functionName)
{
    int lineNumber = 0, lengthOfNumbers = 0, numCharacters = 0;
    string tempBuffer, stringToPut;

    istringstream iss(input);
    iss >> tempBuffer;
    iss >> tempBuffer;

    try
    {
        lengthOfNumbers = tempBuffer.length();
        lineNumber = stoi(tempBuffer);
        if (functionName == "delete")
            return lineNumber;
    } catch (exception e)
    {
        *lineContent = false;
        return -1;
    }


    // Read all the words
    if (input[input.length() - 1] != '\"')
    {
        *lineContent = false;
        return -1;
    }

    iss >> tempBuffer;
    stringToPut += tempBuffer;
    while (tempBuffer[tempBuffer.length() - 1] != '\"')
    {
        iss >> tempBuffer;
        stringToPut += " ";
        stringToPut += tempBuffer;
    }

    *lineContent = stringToPut.substr(1, stringToPut.length() - 2);

    return lineNumber;

}

int main()
{
   string menuInput;
    LinkedList myList;

    while (true)
    {
        // menu();
        getline(cin, menuInput);

        if (menuInput.substr(0, menuInput.find(" ")) == "insertEnd")
        {
            if (StringIsGood(menuInput, "insertEnd"))
                myList.InsertEnd(menuInput.substr(11, (menuInput.length() - 12)));
        }

        else if (menuInput.substr(0, menuInput.find(" ")) == "insert")
        {
            string lineContent;
            int lineNumber = GetLineNumberAndLine(menuInput, &lineContent, "insert");
            if (lineContent != "invalid")
                myList.Insert(lineNumber, lineContent);

        }

        else if (menuInput.substr(0, menuInput.find(" ")) == "edit")
        {
            string lineContent;
            int lineNumber = GetLineNumberAndLine(menuInput, &lineContent, "edit");
            if (lineContent != "invalid")
                myList.Edit(lineNumber, lineContent);
        }

        else if (menuInput.substr(0, menuInput.find(" ")) == "print")
            myList.Print();

        else if (menuInput.substr(0, menuInput.find(" ")) == "search")
        {
            if (StringIsGood(menuInput, "search"))
                myList.Search(menuInput.substr(8, menuInput.length() - 9));
        }

        else if (menuInput.substr(0, menuInput.find(" ")) == "delete")
        {
            int lineNumber = GetLineNumberAndLine(menuInput, NULL, "delete");
            myList.head = myList.Delete(lineNumber);

        }

        else if (menuInput.substr(0, menuInput.find(" ")) == "quit" ||
                    menuInput.substr(0, menuInput.find(" ")) == "Quit")
            break;

    }
}
