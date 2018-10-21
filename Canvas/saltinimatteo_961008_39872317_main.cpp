#include <string>
#include <iostream>
#include <sstream>

class Node {
public:
    int num;
    std::string data;
    Node* next = nullptr;
};
class linkedList{
public:
    Node* head = nullptr;

    linkedList()
    {
        head = nullptr;
    }


    Node* addNodeEnd(int pos, std::string line)
    {
        Node* curr = head;
        Node* node = new Node;
        node->num = pos;
        node->data = line;
        int i = 2;
        if(head == nullptr)
        {
            head = node;
            head->num = 1;
            head->next = nullptr;
        }
        else
        {
            while(curr->next != nullptr)
            {
                curr = curr->next;
                i++;
            }
            curr->next = node;
            node->num = i;
            node->next = nullptr;
        }
        return head;
    }

    Node* addNode(int pos, std::string line)
    {
        Node* curr = head;
        Node* node = new Node;
        node->num = pos;
        node->data = line;
        for(int i = 1; i < pos - 1; i++)
        {
            if(curr->next == nullptr)
                return nullptr;
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
        while(node->next != nullptr)
        {
            node->next->num++;
            node = node->next;
        }
        return head;
    }

    Node* deleteNode(int index)
    {
        Node* curr = head;
        for(int i = 1; i < index - 1; i++)
        {
            curr = curr->next;
            if(curr->next == nullptr) {
                return nullptr;
            }
        }
        Node* temp = curr->next;
        curr->next = temp->next;
        free(temp);
        while(curr->next != nullptr)
        {
            curr->next->num--;
            curr = curr->next;
        }
        return head;
    }

    Node* print ()
    {
        Node* curr = head;
        while(curr != nullptr)
        {
            std::cout<< curr->num << " " << curr->data << std::endl;
            curr = curr->next;
        }
    }

    void search(std::string s1)
    {
        Node* curr = head;
        while(curr != nullptr)
        {
            std::size_t found = curr->data.find(s1);
            if(found != std::string::npos)
                std::cout << curr->num << " " << curr->data << std::endl;
            if(found == std::string::npos && curr->next == nullptr)
                std::cout << "not found" << std::endl;
            curr = curr->next;
        }
    }

    void edit(int index, std::string text)
    {
        Node* curr = head;
        for(int i = 1; i < index -1; i++)
        {
            if(curr->next ==nullptr)
                return;
            curr = curr->next;
        }
        curr->next->data = text;
        return;
    }
};

void lineEditor (linkedList* lines, int pos, std::string s, std::string action)
{
    if(action.compare("insertEnd ") == 0)
        lines->addNodeEnd(pos, s);
    else if(action.compare("insert") == 0)
        lines->addNode(pos, s);
    else if(action.compare("delete") == 0)
        lines->deleteNode(pos);
    else if(action.compare("print") == 0)
        lines->print();
    else if(action.compare("search ") == 0)
        lines->search(s);
    else if(action.compare("edit") == 0)
        lines->edit(pos, s);
    return;
}


int main()
{
    linkedList lines;// = linkedList();
    std::string input;
    while(input.compare("quit") != 0)
    {
        std::getline(std::cin, input);
        std::stringstream line(input);
        std::string divlines;
        while(std::getline(line,divlines))
        {
            std::size_t f1 = divlines.find("edit");
            std::size_t f2 = divlines.find("insert");
            std::size_t f3 = divlines.find("delete");
            if(divlines == "print")
                lineEditor(&lines, 0, "", divlines);
            else if(divlines == "quit")
                return 0;

            else
            {

                if(f1 != std::string::npos || f2 !=std::string::npos || f3 != std::string::npos)
                {
                    std::stringstream v(divlines);
                    std::string command;
                    std::getline(v, command, ' ');
                    std::string num;
                    std::getline(v, num, '"');
                    std::string num2 = num.substr(0,1);
                    int val = atoi(num2.c_str());
                    std::string text;
                    std::getline(v, text, '"');
                    if(command == "insert")
                        lineEditor(&lines, val, text, command);
                    if(command == "delete")
                        lineEditor(&lines, val, "", command);
                    if(command == "edit")
                        lineEditor(&lines, val, text, command);

                }
                std::stringstream v(divlines);
                std::string command;
                std::getline(v, command, '"');
                std::string text;
                std::getline(v, text, '"');
                if(command == "insertEnd ")
                    lineEditor(&lines, 0, text, command);
                if(command == "search " )
                    lineEditor(&lines, 0, text, command);

            }
        }
    }
}
