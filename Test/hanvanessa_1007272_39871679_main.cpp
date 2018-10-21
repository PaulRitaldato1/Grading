#include <string>
#include <iostream>
#include <vector>
using namespace std;

class LinkedList    {
public:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string input)    {
            data = input;
            prev = nullptr;
            next = nullptr;
        }
    };

    // constructor, destructor
    LinkedList();
    ~LinkedList();

    bool insertEnd(string input);
    bool insert(string input, int index);
    bool deletes(int index);
    bool edit(string input, int index);
    void print();
    void search(string input);
    Node* getNode(int input);
    void addHead(string input);

private:
    Node* head;
    Node* tail;
    int size;
};

LinkedList::LinkedList() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList()    {   }

bool LinkedList::insertEnd(string input)  {
    if (size == 0)  {
        head = new Node(input);
        tail = head;
        size++;
        return true;
    } else  {
        Node* newest = new Node(input);
        tail->next = newest;
        newest->prev = tail;
        tail = tail->next;
        size++;
        return true;
    }
}

bool LinkedList::insert(string input, int index)  {
    if (index < 0 || index > size)  {
        return false;
    } else  {
        if (index == 0) {
            this->addHead(input);
        } else if (index == size) {
            insertEnd(input);
        } else  {
            Node* newNode = new Node(input);

            Node* after = this->getNode(index);
            Node* before = after->prev;

            newNode->prev = before;
            newNode->next = after;

            before->next = newNode;
            after->prev = newNode;
            size++;
        }
        return true;
    }
}

void LinkedList::addHead(string input)   {
    if (head == nullptr)    {
        head = new Node(input);
        tail = head;
        size++;
    } else  {
        Node* newNode = new Node(input);
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
        size++;
    }
}

LinkedList::Node* LinkedList::getNode(int index)    {
    if (index > size || index < 0)  {
        return nullptr;
    } else  {
        Node* current = head;
        unsigned int  count = 0;
        while (count != index)  {
            current = current->next;
            count += 1;
        } return current;
    }
}


bool LinkedList::deletes(int index) {
    bool returnBool = false;
    if ( index < 0 || index >= size)  {
        return returnBool;
    } else  {
        if (index == 0 && head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            returnBool = true;
            return returnBool;
        } else if ( index == size-1) {
            Node* temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete temp;
            size--;
            returnBool = true;
            return returnBool;
        } else  {
            Node* deleted = getNode(index);
            deleted->prev->next = deleted->next;
            deleted->next->prev = deleted->prev;
            delete deleted;
            size--;
            returnBool = true;
            return returnBool;
        }
    }
}

bool LinkedList::edit(string input, int index)   {
    if (index>size || index < 0) {
        return false;
    } else  {
        Node* front = getNode(index);
        front->data = input;
        return true;
    }
}

void LinkedList::search(string input)    {
    vector<string> founds;
    Node* check = head;
    int i;
    int foundVal;
    for (i = 0; i < size; i++)  {
        foundVal = check->data.find(input);
        if (foundVal != -1)   {
            string val = to_string(i+1) + " " + check->data;
            founds.push_back(val);
        } check = check->next;
    }

    if (founds.size() != 0)    {
        for (int i =0; i < founds.size(); i++)    {
            cout << founds[i] << endl;
        }
    } else    {
        cout << "not found" << endl;
    }
}

void LinkedList::print()   {
    Node* temp = head;
    for (int i = 0; i < size; i++)    {
        cout << i+1 << " " << temp->data << endl;
        temp = temp->next;
    }
}

int main()
{
    LinkedList list;
    string command;


    while(command.compare("quit") != 0)    {
        cin >> command;
        string line;
        int index;

        if (command.compare("insertEnd") == 0)   {
            getline(cin, line);
            line = line.substr(2, line.length()-3);
            list.insertEnd(line);
        } else if (command.compare("insert") == 0)   {
            cin >> index;
            getline(cin, line);
            line = line.substr(2, line.length()-3);
            list.insert(line, index-1);
        } else if (command.compare("edit") == 0)   {
            cin >> index;
            getline(cin, line);
            line = line.substr(2, line.length()-3);
            list.edit(line, index-1);
        } else if (command.compare("print") == 0)   {
            list.print();
        } else if (command.compare("search") == 0)    {
            getline(cin, line);
            line = line.substr(2, line.length()-3);
            list.search(line);
        } else if (command.compare("delete") == 0)    {
            cin >> index;
            list.deletes(index-1);
        }

    }
    return 0;
}