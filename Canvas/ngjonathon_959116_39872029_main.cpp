#include <iostream>
#include <string>

class Node
{
public:
    std::string content;
    Node *next = NULL;
};

class LinkedList
{
public:
    Node *head = new Node;

    Node* insertEnd(LinkedList *lineEditor, std::string newContent);
    Node* insert(LinkedList *lineEditor, int index, std::string newContent);
    Node* deleteNode(LinkedList *lineEditor, int index);
    Node* edit(LinkedList *lineEditor, int index, std::string newContent);
    Node* search(LinkedList *lineEditor, std::string searchText);
    void print(LinkedList *lineEditor);
};

Node* goToIndex(LinkedList *lineEditor, int index)
{
    //Helper function. Goes to the node before the node at index.
    //Index starts counting at 0, which is the sentinel head node.
    index--;
    Node *temp = lineEditor->head;
    while (index > 0)       //Iterate through list for index - 1 times.
    {
        if (temp == NULL)   //End iteration if NULL is reached.
            return temp;
        temp = temp->next;
        index--;
    }
    return temp;
}

Node* LinkedList::insertEnd(LinkedList *lineEditor, std::string newContent)
{
    Node *curr = lineEditor->head;

    //Create "temp" as the node to be added to the linked list.
    Node *temp = new Node;
    temp->content = newContent;

    while (curr->next != NULL)  //Iterates through list until last non-null node is reached.
    {
        curr = curr->next;
    }

    //Link node into the rest of the linked list
    curr->next = temp;
    temp->next = NULL;

    return head;
}

Node* LinkedList::insert(LinkedList *lineEditor, int index, std::string newContent)
{
    Node *curr = goToIndex(lineEditor, index);
    if (curr == NULL)    //Ignore cases where the passed index is greater than the linked list's size.
        return head;
    Node *temp = new Node;      //Create new node under "temp"
    temp->content = newContent;

    temp->next = curr->next;    //Link "temp" to the rest of the linked list.
    curr->next = temp;

    return head;
}

Node* LinkedList::deleteNode(LinkedList *lineEditor, int index)
{
    Node *curr;
    Node *temp = goToIndex(lineEditor, index);

    if (temp == NULL)   //Ignore cases where the passed index is greater than the linked list's size.
        return head;

    curr = temp;        //"curr" is set to the node before the one to be deleted.
    temp = temp->next;  //"temp" becomes the node to be deleted.
    //If "temp" is the last non-null node in the list, make curr->next be NULL.
    if (temp == NULL)
        curr->next = NULL;
    //Otherwise, remove the connections of "temp" and the rest of the list, then delete.
    else
    {
        curr->next = temp->next;
        temp->next = NULL;
    }

    delete temp;
    return head;
}

Node* LinkedList::edit(LinkedList *lineEditor, int index, std::string newContent)
{
    Node *curr = goToIndex(lineEditor, index)->next;
    if (curr == NULL)   //Ignore cases where the passed index is greater than the linked list's size.
        return head;
    curr->content = newContent; //Update content of "curr"

    return head;
}

Node* LinkedList::search(LinkedList *lineEditor, std::string searchText)
{
    Node *curr = head->next;
    int index = 1;
    bool isFound = false;
    while (curr != NULL)    //Iterate through entire list
    {
        if (curr->content.find(searchText) != std::string::npos)
        {
            std::cout << index << " " << curr->content << "\n";
            isFound = true; //Becomes true the first time the text is found, but will continue looking.
        }

        curr = curr->next;
        index++;
    }
    if (!isFound)   //If text is not found, state that it is not found.
        std::cout << "not found\n";
    return head;
}

void LinkedList::print(LinkedList *lineEditor)
{
    Node *curr = lineEditor->head->next;
    int index = 1;
    while (curr != NULL)    //Iterate through entire list
    {
        std::cout << index << " " << curr->content <<"\n";
        curr = curr->next;
        index++;
    }
    return;
}

int main()
{
    //Initialize LinkedList object. Set object's head->next to NULL.
    LinkedList *lineEditor = new LinkedList;
    lineEditor->head->next = NULL;

    std::string cmd;     //Saves the command (insertEnd, edit, delete, etc.)
    int index;           //Save the specified index in the command if needed.

    while (cmd != "quit")
    {
        //Save the command (insertEnd, edit, etc.) in cmd.
        std::cin >> cmd;

        //"inputs" is the string to be used in the functions.
        std::string inputs;

        //Match the command to the proper function.
        if (cmd == "insertEnd")
        {
            //Save the rest of the inputted command in "in" to be further parsed for function parameters.
            std::string in;
            getline(std::cin, in);

            //Removes quotations from "in".
            for (std::string::iterator itr = in.begin(); itr != in.end(); itr++)
            {
                if (*itr != '"')
                    inputs.push_back(*itr);
            }
            //Remove leading space if needed for formatting consistency.
            if (inputs.at(0) == ' ')
                inputs = inputs.substr(1);

            lineEditor->insertEnd(lineEditor, inputs);
            continue;
        }
        else if (cmd == "insert")
        {
            //Pass in first number from "in" into index.
            std::cin >> index;

            //Save the rest of the inputted command in "in" to be further parsed for function parameters.
            std::string in;
            getline(std::cin, in);

            //Removes quotations from "in".
            for (std::string::iterator itr = in.begin(); itr != in.end(); itr++)
            {
                if (*itr != '"')
                    inputs.push_back(*itr);
            }
            //Remove leading space if needed for formatting consistency.
            if (inputs.at(0) == ' ')
                inputs = inputs.substr(1);

            lineEditor->insert(lineEditor, index, inputs);
            continue;
        }
        else if (cmd == "delete")
        {
            //Note: Only other parameter should be a number to be stored in "index"
            std::cin >> index;
            lineEditor->deleteNode(lineEditor, index);
            continue;
        }
        else if (cmd == "edit")
        {
            //Pass in first number from "in" into index.
            std::cin >> index;

            //Save the rest of the inputted command in "in" to be further parsed for function parameters.
            std::string in;
            getline(std::cin, in);

            //Removes quotations from "in".
            for (std::string::iterator itr = in.begin(); itr != in.end(); itr++)
            {
                if (*itr != '"')
                    inputs.push_back(*itr);
            }
            //Remove leading space if needed for formatting consistency.
            if (inputs.at(0) == ' ')
                inputs = inputs.substr(1);

            lineEditor->edit(lineEditor, index, inputs);
            continue;
        }
        else if (cmd == "search")
        {
            //Save the rest of the inputted command in "in" to be further parsed for function parameters.
            std::string in;
            getline(std::cin, in);

            //Removes quotations from "in".
            for (std::string::iterator itr = in.begin(); itr != in.end(); itr++)
            {
                if (*itr != '"')
                    inputs.push_back(*itr);
            }
            //Remove leading space if needed for formatting consistency.
            if (inputs.at(0) == ' ')
                inputs = inputs.substr(1);

            lineEditor->search(lineEditor, inputs);
            continue;
        }
        else if (cmd == "print")
        {
            lineEditor->print(lineEditor);
            continue;
        }

        //Any other commands or invalid input will be ignored.
        else
        {
            continue;
        }
    }

    return 0;
}