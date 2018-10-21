
#include <iostream>

class LinkedList
{
private:

    struct Node
    {
        std::string data;
        Node* next;

    };
    Node* head;
    Node* tail;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void insertEnd(std::string str);
    void indexInsert(std::string str, int index);
    void edit(std::string, int index);
    void print();
    void deleteNode(int index);
    void search(std::string);
};

void LinkedList::insertEnd(std::string str)
{
    Node* newNode = new Node;
    newNode->data = str;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::indexInsert(std::string str, int index)
{
    int position = index;
    int counter = 1;
    Node* newNode = new Node;
    newNode->data = str;
    Node* pointer;
    pointer = head;
    if (position == 1)
    {
        Node* temp;
        temp = head;
        head = newNode;
        head->next = temp;

    }
    else
    {
        while(pointer)
        {
            if (counter == index - 1)
            {
                Node* temp;
                temp = pointer->next;
                pointer->next = newNode;
                newNode->next = temp;
                break;
            }
            else
            {
                counter++;
                pointer = pointer->next;
            }

        }
    }

}

void LinkedList::print()
{
    int counter = 1;
    Node* pointer;
    pointer = head;
    while(pointer)
    {
        std::cout << counter << " " <<  pointer->data << std::endl;
        counter++;
        pointer = pointer->next;
    }
}

void LinkedList::edit(std::string str, int index)
{
    int counter = 1;
    Node* pointer;
    pointer = head;
    while(pointer)
    {
        if (counter == index)
        {
            pointer->data = str;
            break;
        }
        else
        {
            counter++;
            pointer = pointer->next;
        }
    }
}

void LinkedList::deleteNode(int index)
{
    int counter = 1;
    Node* pointer;
    pointer = head;
    if (counter == index)
    {
        head = pointer->next;
    }
    else
    {
        while(pointer)
        {
            if (counter == index - 1)
            {
                //std::cout << "!!!!!" <<tail->data << std::endl;
                Node* temp;
                temp = pointer->next->next;
                delete pointer->next;
                pointer->next = temp;
                break;
            }
            if (pointer->next == tail && counter == index - 2)
            {
                tail = pointer;
                break;
            }
            else
            {
                counter++;
                pointer = pointer->next;
            }
        }
    }
}

void LinkedList::search(std::string str)
{
    Node* pointer = head;
    int counter = 1;
    bool foundData = false;
    while(pointer)
    {
        std::string listString = pointer->data;
        int i;
        for (i = 0; i < listString.size(); i++)
        {
            if (str.compare(listString.substr(i, str.size())) == 0)
            {
                std::cout << counter << " " << pointer->data  << std::endl;
                foundData = true;
                break;
            }
        }
        counter++;
        pointer = pointer->next;
    }
    if (!foundData)
    {
        std::cout << "not found" << std::endl;
    }
}

int main()
{

    bool inLoop = true;
    LinkedList list = LinkedList();
    std::string input;
    while (inLoop)
    {
        std::string str;
        getline(std::cin, str);

        std::string::size_type partLength = str.find(' ');
        std::string command = str.substr(0, partLength);

        if (command.compare("delete") == 0)
        {
            std::string cutString = str.substr(partLength + 1, str.size());

            std::string::size_type numeral = cutString.find(' ');
            std::string deletePos = cutString.substr(0, numeral);
            try
            {
                int index = std::stoi(deletePos);
                list.deleteNode(index);
            }
            catch (std::invalid_argument)
            {
                //Continue the code
            }

        }
        else if(command.compare("insert") == 0)
        {
            std::string cutString = str.substr(partLength + 1, str.size());
            std::string::size_type numeral =  cutString.find(' ');
            std::string insertPos = cutString.substr(0, numeral);
            try
            {
                int index = std::stoi(insertPos);
                std::string input = str.substr(partLength + numeral + 2, str.size());
                if (input.at(0) == '\"' && input.at(input.size() - 1) == '\"' && input.substr(1, input.size() - 2).size() <= 80)
                {
                    std::string newInput = input.substr(1, input.size() - 2);

                    list.indexInsert(newInput, index);
                }
            }
            catch (std::invalid_argument) {
                //Nothing happens, continue the code
            }

        }
        else if (command.compare("edit") == 0)
        {
            std::string cutString = str.substr(partLength + 1, str.size());
            std::string::size_type numeral =  cutString.find(' ');
            std::string insertPos = cutString.substr(0, numeral);
            int index = std::stoi(insertPos);
            std::string input = str.substr(partLength + numeral + 2, str.size());
            if (input.at(0) == '\"' && input.at(input.size() - 1) == '\"' && input.substr(1, input.size() - 2).size() <= 80)
            {
                std::string newInput = input.substr(1, input.size() - 2);
                list.edit(newInput, index);
            }

        }
        else if (command.compare("insertEnd") == 0)
        {
            std::string input = str.substr(partLength + 1, str.size());
            if (input.at(0) == '\"' && input.at(input.size() - 1) == '\"' && input.substr(1, input.size() - 2).size() <= 80)
            {
                std::string newInput = input.substr(1, input.size() - 2);
                list.insertEnd(newInput);
            }


        }
        else if (command.compare("search") == 0)
        {
            std::string input = str.substr(partLength + 1, str.size());
            if (input.at(0) == '\"' && input.at(input.size() - 1) == '\"' && input.substr(1, input.size() - 2).size() <= 80)
            {
                std::string newInput = input.substr(1, input.size() - 2);
                list.search(newInput);
            }


        }
        else if (command.compare("print") == 0)
        {
            list.print();
        }
        else if(command.compare("quit") == 0)
        {
            inLoop = false;
        }
        else
        {
            //Nothing
        }


    }



}