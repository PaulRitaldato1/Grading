#include <iostream>
#include <string>

using namespace std;

class LineEditor
{
private:
    struct Node
    {
        string data;
        Node* Next=nullptr;
    };
    int total=0;
    Node* head=nullptr;
    Node* tail=nullptr;
    Node* temp=nullptr;

public:
    void InsertEnd(string text);
    void Insert(int n,string text);
    void Delete(int n);
    void Edit(int n,string text);
    void Print();
    void Search(string text);

};

void LineEditor::InsertEnd(string text)
{
    text=text.substr(1,text.length()-2);
    if(text.length()>80)
        return;
    Node* NewNode=new Node;
    NewNode->data=text;
    if(tail!=nullptr)
        tail->Next=NewNode;
    if(head==nullptr)
        head=NewNode;
    tail=NewNode;
    total++;
}
void LineEditor::Insert(int n,string text)
{
    text=text.substr(1,text.length()-2);
    if(text.length()>80)
        return;
    Node* NewNode=new Node;
    NewNode->data=text;
    int position=1;

    if(n==0||n>(total+1))
        return;
    if(total==0)
    {
        head=NewNode;

    }
    temp=head;
    if(n==1)
    {
        NewNode->Next=head;
        head=NewNode;
        total++;
        return;
    }
    else
    {

        while(position<n-1)
        {
            temp=temp->Next;
            position++;
        }
        NewNode->Next=temp->Next;
        temp->Next=NewNode;
        if(n==total+1)
            tail=NewNode;
        total++;
    }
}
void LineEditor::Delete(int n)
{
    if(n>total)
        return;
    temp=head;
    int position=1;
    if(n==1)
    {
        head=head->Next;
        delete(temp);
        total--;
        return;
    }

    else
    {
    Node* prev;
        while(position<n)
        {
            if(position==n-1)
            {
                prev=temp;
            }
            temp=temp->Next;
            position++;
        }
        prev->Next=temp->Next;
        if(n==total)
            tail=prev;
        delete(temp);
        total--;
    }
}

void LineEditor::Edit(int n,string text)
{
    temp=head;
    text=text.substr(1,text.length()-2);
    if(text.length()>80)
        return;
    if(n>total)
        return;
    else
    {
        if(n==1)
            head->data=text;
        else
        {
            int position=1;
            while(position<n)
            {
                temp=temp->Next;
                position++;
            }
            temp->data=text;
        }

    }
}

void LineEditor::Print()
{
    int position=1;
    temp=head;
    while(position<=total)
    {
        cout<<position<<" "<<temp->data<<endl;
        temp=temp->Next;
        position++;
    }
}

void LineEditor::Search(string text)
{
    text=text.substr(1,text.length()-2);
    int position=1;
    bool found=false;
    temp=head;
    while(position<=total)
    {
        if(temp->data.find(text)!=string::npos)
        {
            cout<<position<<" "<<temp->data<<endl;
            found=true;
        }
        temp=temp->Next;
        position++;
    }
    if(!found)
        cout<<"not found"<<endl;

}

int main()
{
    string command,text;
    int num;
    LineEditor TextEditor;


    while(command!="quit")
    {

        cin>>command;
        if(command=="insertEnd")
        {
            cin.ignore(100,' ');
            getline(cin,text);
            TextEditor.InsertEnd(text);

        }
        else if(command=="insert")
        {
            cin>>num;
            cin.ignore(100,' ');
            getline(cin,text);
            TextEditor.Insert(num,text);
        }
        else if(command=="delete")
        {
            cin>>num;
            TextEditor.Delete(num);
        }
        else if(command=="edit")
        {
            cin>>num;
            cin.ignore(100,' ');
            getline(cin,text);
            TextEditor.Edit(num,text);
        }
        else if(command=="print")
            TextEditor.Print();
        else if(command=="search")
        {
            cin.ignore(100,' ');
            getline(cin,text);
            TextEditor.Search(text);
        }

    }
}
