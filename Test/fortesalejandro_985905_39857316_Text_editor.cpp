/*
Alejandro Fortes
COP3530
Programming Assignment 1: Text Editor with Linked Lists

Note: Everything was written in the same file to avoid confusion on Stepik.
*/

#include <iostream>
#include <string>
#include <limits>


class List
{
private: //variables

    struct node
    {
        int index;
        std::string text;
        node* next;
    };
    typedef struct node* nodePtr;

    nodePtr head;
    nodePtr current;
    nodePtr temp;

public: //functions

    List()
    {
        head = NULL;
        current = NULL;
        temp = NULL;
    }
/////////////////////////////////////////////////////////

    //Insert the users Input at the end of the Linked List.
    void insertEnd(std::string addText, int pos)
    {
        nodePtr a = new node;
                a->next = NULL;
                a->text = addText;
                a->index = pos;

        //Checks if List is empty, if not go to the end and insert.
        if(head != NULL)
        {
            current = head;

            while(current->next != NULL)
            {
                current = current->next;
            }
            current->next = a;
        }
        else
        {
            head = a;
        }
    }
/////////////////////////////////////////////////////////

    //Insert in a specific position of the Linked List.
    void insertNum(std::string addText, int pos)
    {
        nodePtr a = new node;
                a->next = NULL;
                a->text = addText;
                a->index = pos;
        int listLength = 2;         //Equals to 2 because it is used to check if the user will input a value out of bounds.
                                    //Such as insert 7 in a list of length 4.

        if(pos == 1)
        {
            if(head == NULL)
                head = a;
            else
            {
                current = head;
                head = a;
                head->next = current;

                //Fixes the index
                int i = 1;
                current = head;
                while(current != NULL)
                {
                    current->index = i;
                    current=current->next;
                    i++;
                }
            }
        }
        else
        {
            if(head != NULL)
            {
                current = head;

                //Calculate Length of the linked List
                while(current != NULL)
                {
                    current=current->next;
                    listLength++;
                }
                current = head;

                //Find position to insert new node
                if(pos < listLength && pos > 0)
                {
                    int i = 1;
                    while(i != pos-1)
                    {
                        current = current->next;
                        i++;
                    }
                    a->next = current->next;
                    current->next = a;

                    current = head;

                    i = 1;
                    while(current != NULL)
                    {
                        current->index = i;
                        current=current->next;
                        i++;
                    }
                }

            }
        }
    }
/////////////////////////////////////////////////////////

    //Deletes selected value
    void deleteText(int pos)
    {
        nodePtr del = NULL;
        temp = head;
        current = head;
        int listLength = 1;

        //Calculate Length of the linked List
        while(current != NULL)
        {
            current=current->next;
            listLength++;
        }
        current = head;

        //If its within bounds
        if(pos < listLength && pos > 0)
        {

            //if its the head of the linked list.
            if(pos == 1)
            {
                head = head->next;
                current = head;

                //reassign numbers
                while(current != NULL)
                {
                    current->index = current->index - 1;
                    current = current->next;
                }
            }
            else
            {
                //Find the position
                int i = 1;
                while(current != NULL && i != pos)
                {
                    temp = current;
                    current = current->next;
                    i++;
                }

                if(i == pos)
                {
                    del = current;
                    current = current->next;
                    temp->next = current;

                    if(current != NULL)
                    {
                        //reassign numbers
                        while(current != NULL)
                        {
                            current->index = current->index - 1;
                            current = current->next;
                        }
                    }

                    delete del;
                }
                else
                    delete del;
            }
        }

    }
/////////////////////////////////////////////////////////

    //Replaces selected Node's data with user Input.
    void edit(int pos, std::string addText)
    {
        nodePtr a = new node;
                a->next = NULL;
                a->text = addText;
        int listLength = 2;

        current = head;
        int i = 1;

        //Calculate Length of the linked List
        while(current != NULL)
        {
            current=current->next;
            listLength++;
        }
        current = head;

        //If its within bounds
        if(pos < listLength && pos > 0)
        {
            //Find position.
            while(i != pos)
            {
                current = current->next;
                i++;
            }

            if(i == pos)
            {
                current->text = addText;
            }
        }
    }
/////////////////////////////////////////////////////////

    //Searches for value in the linked list.
    void searchText(std::string findText)
    {
        bool found = false;
        current = head;
        while(current != NULL)
        {
            //If the text is found in the linked list.
            if(current->text.find(findText) != std::string::npos)
            {
                std::cout << current->index << " " << current->text << std::endl;
                found = true;
            }

            current = current->next;
        }

        if(!found)
            std::cout << "not found" << std::endl;
    }
/////////////////////////////////////////////////////////

    //Outputs the linked list
    void print()
    {
        current = head;
        while(current != NULL)
        {
            std::cout << current->index << " " << current->text << std::endl;
            current = current->next;
        }
    }

};

/////////////////////////////////////////////////////////////////////////////////////
//Space saving / Repeated Functions

//Checks for quotes to approve input and removes them for proper printing
void quoteFix(std::string& userInput, bool& quotes)
{
    //If it has quotations at the beginning AND end
    if(userInput.at(1) == '"' && userInput.at(userInput.length()-1) == '"')
    {
        //Erase the "
        userInput.erase(1,1);
        userInput.erase(userInput.length() - 1);
        quotes = true;
    }
    else
        quotes = false;

}

int main()
{
    List textEditor;
    std::string userSelect;
    std::string userInput;
    int index = 1;
    int numInput = 0;
    bool quotes = false;

    while(userSelect.compare("quit") != 0)
    {
        std::cin >> userSelect;

        //Quit Function//////////////////////////////////////////////
        if(userSelect.compare("quit") == 0)
            return 0;

        //InsertEnd/////////////////////////////////////////////////
        if(userSelect.compare("insertEnd") == 0)
        {
           std::getline(std::cin,userInput);

           //Check if the input is empty or too small. (since quotations are required it has to be at least > 2)
           if(!userInput.empty() && userInput.length() > 2)
           {
                //Check if the input has "".
                quoteFix(userInput, quotes);
                if(quotes)
                {
                    textEditor.insertEnd(userInput, index);
                    index++;
                }
           }

        }

        //Insert Num/////////////////////////////////////////////////
        if(userSelect.compare("insert") == 0)
        {
            std::cin >> numInput;
            std::getline(std::cin,userInput);
            std::cin.clear();   //In case the user didnt input any number.

            //Check if the input is empty or too small. (since quotations are required it has to be at least > 2)
           if(!userInput.empty() && userInput.length() > 2)
           {
                //Check if the input has "".
                quoteFix(userInput, quotes);
                if(quotes)
                {
                    textEditor.insertNum(userInput, numInput);
                    index++;
                }
           }
        }

        //Edit Num//////////////////////////////////////////////////
        if(userSelect.compare("edit") == 0)
        {
            std::cin >> numInput;
            std::getline(std::cin,userInput);
            std::cin.clear();   //In case the user didnt input any number.

            //Check if the input is empty or too small. (since quotations are required it has to be at least > 2)
           if(!userInput.empty() && userInput.length() > 2)
           {
                //Check if the input has "".
                quoteFix(userInput, quotes);
                if(quotes)
                {
                    textEditor.edit(numInput, userInput);
                }
           }
        }

        ////Search Value/////////////////////////////////////////////////
        if(userSelect.compare("search") == 0)
        {
           std::getline(std::cin,userInput);

           //Check if the input is empty or too small. (since quotations are required it has to be at least > 2)
           if(!userInput.empty() && userInput.length() > 2)
           {
                //Check if the input has "".
                quoteFix(userInput, quotes);
                if(quotes)
                {
                    textEditor.searchText(userInput);
                }
           }
        }

        ////Delete Value/////////////////////////////////////////////////
        if(userSelect.compare("delete") == 0)
        {
            std::cin >> numInput;
            std::cin.clear();   //In case the user didnt input any number.
            textEditor.deleteText(numInput);
        }

        //Print Values/////////////////////////////////////////////////
        if(userSelect.compare("print") == 0)
           textEditor.print();

    }

    return 0;
}
