#include <iostream>
#include <string>


using namespace std;

class Node {
    public:
        string value;
        Node* next = NULL;

};

int findPos(string str)
{

    int start = 0;
    int end = 1;

    while(isdigit(str.at(start)) && start<str.length())
    {
        start++;
    }
    end = start + 1;
    while (!isdigit(str.at(end)) && end<=str.length())
    {
        end++;
    }
    return stoi(str.substr(start, (end-start)));
}

string findText(string str)
{
    
    int start = 0;
    int end = 1;

    while(str.at(start)!='"' && start<str.length())
    {
        start++;
    }
    end = start + 1;
    while (str.at(end)!='"' && end<str.length())
    {
        end++;
    }
    return str.substr(start+1, end-(start+1));
    

}

void insert(Node* head, string str)
{
    
    int pos = findPos(str);
    int count = 0;
    Node* curr = head;
    bool done = false;
    if (pos==0)
    {
        Node* insert;
        insert->value.assign(findText(str));
        string temp;
        temp.assign(head->value);
        head = insert;
        Node* add;
        head->next = add;
        add->value.assign(temp);
    }
    else
    {
        while (curr!=NULL && !done)
        {
            curr=curr->next;
            if (count==pos)
            {
                done = true;
            }
        }
        if (done)
        {
            Node* insert;
            insert->value.assign(findText(str));
            Node* temp = curr->next;
            curr->next = insert;
            insert->next = temp;
        }
        else
        {
            cout<<"Invalid index"<<endl;
        }
    }
}

void insertEnd(Node* head, string str)
{

    Node* curr = head;
    while (curr!=NULL)
    {
        curr=curr->next;
    }
    Node* insert;
    insert->value.assign(findText(str));
    cout << "success" << endl;
    curr->next = insert;
}

void remove(Node* head, string str)
{
    int pos = findPos(str);
    if (pos==0)
    {
        if (head->next!=NULL)
        {
            Node* temp = head->next;
            head->value.assign(head->next->value);
            head->next = head->next->next;
            delete temp;
        }
        else
        {
            head = NULL; 
        }
    }
    else
    {
        int count = 1;
        Node* curr = head;
        Node* temp = head->next;
        while (count!=pos)
        {
            curr = curr->next;
            temp = temp->next;
            count++;
        }
        curr->next = temp->next;
        delete temp;
    }
}

void replace(Node* head, string str)
{
    int pos = findPos(str);
    int count = 0;
    Node* curr = head;
    while (count!=pos)
    {
        curr = curr->next;
        count++;
    }
    curr->value.assign(findText(str));

}

void print(Node* head)
{
    int count = 0;
    Node* curr = head;
    while (curr!=NULL)
    {
        cout<<count << " " << curr->value<<endl;
        curr = curr->next;
    }
}

void search(Node* head, string str)
{
    int count = 0;
    Node* curr = head;
    bool found = false;
    while (curr!=NULL && !found)
    {
        if (curr->value.find(str)!=-1)
        {
            found = true;
        }
        else
        {
            count++;
            curr = curr->next;
        }
        
    }
    if (found)
    {
        cout << count << " " << curr->value << endl;
    }
    else
    {
        cout << "Error: phrase not found" << endl;
    }

}

bool read(string str, Node* head)
{
    bool match = false;
    bool end = false;
    int count = 1;
    string command;
    while (count<10 && !match && count<=str.length())
    {
        
        command.assign(str.substr(0, count));
        if (command.compare("insert ")==0)
        {
          insert(head, str);
          match = true;
        }
        else if (command.compare("insertEnd")==0)
        {
            match = true;
            insertEnd(head, str);
        }
        else if (command.compare("delete")==0)
        {
            match = true;
            remove(head, str);
        }
        else if (command.compare("edit")==0)
        {
            match = true;
            replace(head, str);
        }
        else if (command.compare("print")==0)
        {
            match = true;
            print(head);
        }
        else if (command.compare("search")==0)
        {
            match = true;
            search(head, str);
        }
        else if (command.compare("quit")==0)
        {
          match = true;
          end = true;
        }
        count++;
    }
    if (!match)
    {
        cout<<"Invalid command"<<endl;
    }
    return end;
}

int main()
{   

  Node* head;
  bool end = false;
  string str;

  while(!end)
  {
      str = "";
      cout<<"Type a command:"<<endl;
      getline(cin,str);
      end = read(str, head);
  }

  return -1;
}