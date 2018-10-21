#include <string>
#include <iostream>
using namespace std;

class LinkedList
{
public:
    
    struct Node
    {
        string value;
        Node * next;
    };
    
    void Insert(int index, string value_)
    {
        if (index > nodeCount || index < 0)
        {
            return;
        }
        Node *temp = new Node();
        temp->value = value_;
        if (index == 0)
        {
            temp->next = head;
            head = temp;
            nodeCount++;
        }
        else
        {
            Node *curr = head;
            for (int i = 0; i < index - 1; i++)
            {
                curr = curr->next;
            }
            Node * nextNode = curr->next;
            temp->next = nextNode;
            curr->next = temp;
            nodeCount++;
        }
    }
    void deleteNode (int index)
    {
        if (index >= nodeCount || index < 0)
        {
            return;
        }
        if (index == 0)
        {
            nodeCount--;
            Node * tempHead = head->next;
            delete head;
            head = tempHead;
            return;
        }
        Node * curr = head;
        for (int i = 0; i < index -1 ; i++)
        {
            curr = curr->next;
        }
        Node * nodeBefore = curr;
        curr = curr->next;
        Node * nodeAfter = curr->next;
        delete curr;
        nodeBefore->next = nodeAfter;
        nodeCount--;
    }
    void Edit (int index, string value_)
    {
        if (index >= nodeCount || index < 0)
        {
            return;
        }
        Node * temp = head;
        for (int i = 0; i < index; i ++)
        {
            temp = temp->next;
        }
        temp->value = value_;
    }
    
    void Print()
    {
        Node * curr = head;
        int i = 1;
        while (curr != nullptr)
        {
            cout<<i << " ";
            cout<<curr->value<<endl;
            curr = curr->next;
            i++;
        }
    }

    bool checkSame(string a, string b)
    {
        if (a.size() != b.size())
        {
            return false;
        }
        else
        {
            for (unsigned int i = 0; i < a.size(); i++)
            {
                if (a[i] != b[i])
                {
                    return false;
                }
            }
            return true;
        }
    }
    
    void Search(string input)
    {
        Node * curr = head;
        int k = 0;
        bool found = false;
        while (curr != NULL)
        {
            k++;
            string atCurr = curr->value;
            if (atCurr.size() < input.size())
            {
                curr = curr->next;
            }
            else if (atCurr.size() >= input.size())
            {
                for (unsigned int i = 0; i < atCurr.size() - input.size() + 1; i++)
                {
                    string portion = atCurr.substr(i, input.size());
                    if (checkSame(portion, input))
                    {
                        cout<<k<<" "<<atCurr<<endl;
                        found = true;
                        break;
                    }
                }
                curr = curr->next;
            }
        }
        if (!found)
        {
            cout<<"not found"<<endl;
        }
    }
    
    void lineEditor(string line)
    {
        string command = line.substr(0, line.find_first_of(" "));
        if (command == "print")
        {
            Print();
            return;
        }
 
        string data = line.substr(line.find_first_of("\"") + 1, line.find_last_of("\"") - line.find_first_of("\"") - 1);
        if (data.size() > 80)
        {
            return;
        }
        line = line.substr(line.find_first_of(" ") + 1);
        if (command == "insertEnd")
        {
            Insert(nodeCount, data);
        }
        else if (command == "insert")
        {
            string indexStr = line.substr(0, line.find_first_of("\"") - 1);
            int index = stoi(indexStr);
            index--;
            Insert(index,data);
        }
        else if (command == "edit")
        {
            string indexStr = line.substr(0, line.find_first_of("\"") - 1);
            int index = stoi(indexStr);
            index--;
            Edit(index, data);
        }
        else if (command == "delete")
         {
             string indexStr = line.substr(0, line.find_first_of("\"") - 1);
             int index = stoi(indexStr);
             index--;
             deleteNode(index);
         }
        
         else if (command == "search")
         {
             Search(data);
         }
         
        else if (command == "quit")
            return;
        
        else
        {
            cout<<"Please enter other"<<endl;
        }
        
        
    }
    
    
private:
    Node * head = nullptr;
    int nodeCount = 0;
    
};


//your line editor implementation here

int main()
{
    LinkedList ls;
    bool keep = true;
    string line;
    while (getline(cin, line))
    {
        ls.lineEditor(line);
    }
    //your code to invoke line editor here
}
