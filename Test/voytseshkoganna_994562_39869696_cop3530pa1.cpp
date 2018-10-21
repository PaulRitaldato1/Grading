/*
 * Ganna Voytseshko
 * 21 September 2019
 * COP3530 Project 1
 */

#include <iostream>
#include <string>

class LinkedList
{
public:

    //Node struct to contain line and pointer to next node
    struct Node
    {
        std::string line;
        Node* next;
    };
    Node* head = NULL;

    //insert function
    //inserts the given line at given index (index starts at 1)
    void insert(int index, std::string newLine)
    {
        //std::string newLine = convert(newLineS);
        //std::string newLine = newLineS;
        Node* current = head;
        Node* temp = new Node;
        bool notNull = true;
        temp->line = newLine;

        //if inserting at head
        if (index == 1)
        {
            if (head == NULL)
            {
                temp->next = NULL;
                head = temp;
            }
            else{
                temp->next = head;
                head = temp;
            }
        } else
        {
            //else, iterate through list and use temp node to insert a node
            for (int i = 2; i < index; i++)
            {
                if (current->next == NULL)
                {
                    notNull = false;
                    break;
                }
                current = current->next;
            }
            if (notNull)
            {
                temp->next = current->next;
                current->next = temp;
            }
        }
    }

    //insertEnd function
    //iterates through the list and inserts a node with given line at the end
    void insertEnd(std::string newLine)
    {
        //std::string newLine = convert(newLineS);
        //std::string newLine = newLineS;
        Node* temp = new Node;
        Node* current = head;
        temp->line = newLine;
        temp->next = NULL;

        //if list is empty
        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            while (current->next != NULL)
            {
                //std::cout<<current->line<<std::endl;
                current = current->next;
            }
            current->next = temp;
        }
    }

    //delete function - called remove in my implementation
    //deletes the node at given index
    void remove(int index)
    {
        bool notNull = true;
        Node* current = head;

        //if head needs to be removed
        if (index == 1)
        {
            head = current->next;
        }
        //else iterate through list until index is found
        for (int i = 2; i < index; i++)
        {
            if (current->next == NULL)
            {
                notNull = false;
                break;
            }
            current = current->next;
        }
        if (notNull)
        {
            if (current->next != NULL)
                current->next = current->next->next;
        }
    }

    //edit function
    //changes the line at given index
    void edit(int index, std::string newLine)
    {
        bool notNull = true;
        //std::string newLine = convert(newLineS);
        //std::string newLine = newLineS;
        Node* current = head;
        for (int i = 1; i < index; i++)
        {
            if (current == NULL)
            {
                notNull = false;
                break;
            }
            current = current->next;
        }
        if (notNull && current != NULL)
        {
            current->line = newLine;
        }
    }

    //print function
    //iterates through the list and prints each line, along with its index 
    void print()
    {
        Node* current = head;
        int index = 1;

        while (current != NULL)
        {
            std::cout<<index<<" "<<current->line<<std::endl;
            current = current->next;
            index++;
        }
    }

    //search function
    //iterates through the list and searches for the given text within each line
    void search(std::string text)
    {
        Node* current = head;
        int index = 1;
        int found = 0;
        int location = 0;

        while (current != NULL)
        {
            location = current->line.find(text);
            if (location != -1)
            {
                found++;
                std::cout<<index<<" "<<current->line<<std::endl;
            }
            current = current->next;
            index++;
        }
        if (found == 0)
            std::cout<<"not found"<<std::endl;
    }

};


int main()
{
    LinkedList list;
    std::string input = " ";
    std::string command;
    std::string index;
    std::string line;
    int firstSpace = 0;
    int firstQuote = 0;
    int lastQuote = 0;
    int quoteNum = 0;
    int indexNum = 0;

    while(input.compare("quit") != 0)
    {
        quoteNum = 0;
        getline (std::cin, input);
        firstSpace = input.find_first_of(' ');
        command = input.substr(0, firstSpace);
        input = input.substr(firstSpace+1);

        firstQuote = input.find_first_of('\"') + 1;
        //quoteNum ensures there are 2 " per every line given
        //if there are less than 2 ", the command is ignored
        if (firstQuote > 0)
        {
            quoteNum++;
        }
        lastQuote = input.find_last_of('\"') - firstQuote;
        if (lastQuote > 0)
        {
            quoteNum++;
        }

        index = input.substr(0, input.find_first_of(' '));
        line = input.substr(firstQuote , lastQuote);

        //if line is more than 80 chars, take the substring of only 80 chars
        if (line.size() > 80)
        {
            line = line.substr(0, 80);
        }

        if (command.compare("insert") == 0)
        {
            if (quoteNum != 2)
            {
                continue;
            }
            try{
                indexNum = std::stoi(index);
            }
            catch(const std::invalid_argument ai)
            {
                //catches invalid arguments thrown if std::stoi does not produce an int
                continue;
            }
            list.insert(indexNum, line);
        }
        else if (command.compare("insertEnd") == 0)
        {
            if (quoteNum != 2)
            {
                continue;
            }
            list.insertEnd(line);
        }else if (command.compare("print") == 0)
        {
            list.print();
        }else if (command.compare("search") == 0)
        {
            if (quoteNum != 2)
            {
                continue;
            }
            list.search(line);
        }else if (command.compare("edit") == 0)
        {
            if (quoteNum != 2)
            {
                continue;
            }
            try{
                indexNum = std::stoi(index);
            }
            catch(const std::invalid_argument ai)
            {
                //catches invalid arguments thrown if std::stoi does not produce an int
                continue;
            }
            list.edit(indexNum, line);
        }else if (command.compare("delete") == 0)
        {
            try{
                indexNum = std::stoi(index);
            }
            catch(const std::invalid_argument ai)
            {
                //catches invalid arguments thrown if std::stoi does not produce an int
                continue;
            }
            list.remove(indexNum);
        }else if (command.compare("quit") == 0)
        {
            //quit
        }else
        {
            //command wasn't recognized
        }
    }
};