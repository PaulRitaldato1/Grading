#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;
//node creation
struct node{
string line;
struct node *next;
};
//linked list creation
class list
  {
    private:
    node *head, *tail;
    public:
    list()
    {
      head=NULL;
      tail=NULL;
    }
    //create node method that also inserts the node at the end of the list
    void createNode(string text)
    {
      node *temp=new node;
      temp->line=text;
      temp->next=NULL;
      if(head==NULL)
      {
        head=temp;
        tail=temp;
        temp=NULL;
      }
      else
      {
        tail->next=temp;
        tail=temp;
      }
    }
    //display method that displays the contents of the linked list with numbers by the lines
    void display()
    {
    node *temp=new node;
    temp=head;
    for(int i = 1; temp!=NULL; ++i)
    {
        cout<<i<<" ";
        cout<<temp->line<<"\n";
        temp=temp->next;
    }
    }
    //insert method that inserts a node at a given position in the linked list
    void insertPosition(int pos, string text)
    {
    node *pre=new node;
    node *cur=new node;
    node *temp=new node;
    cur=head;
    if(pos > 1){
    for(int i=1;i<pos;i++)
    {
      pre=cur;
      cur=cur->next;
    }
    temp->line=text;
    pre->next=temp;
    temp->next=cur;
    }
    if(pos == 1){
        temp->line=text;
        temp->next=head;
        head=temp;
    }
    }
    //insert method that replaces a node in a linked list given by its position with a new given node
    void editPosition(int pos, string text)
    {
    node *pre=new node;
    node *cur=new node;
    node *temp=new node;
    cur=head;
    for(int i=1;i<pos;i++)
    {
      pre=cur;
      cur=cur->next;
    }
    temp->line=text;
    pre->next=temp;
    if(cur->next != NULL){
        temp->next=cur->next;
        delete cur;
    }
    }
    //search method that searches the linked lists contents for a given phrase or word
    void search(string text)
    {
        node *tmp = new node;
        tmp = head;
        int check = 0;
        int j = 1;
        int i = 0;
        while(tmp->next != NULL){
            if(i > tmp->line.length() - text.length()){
                i = 0;
                tmp = tmp->next;
                ++j;
            }
            if(tmp->line.substr(i,text.length()) == text){
                cout << j << " " << tmp->line << endl;
                i = -1;
                tmp = tmp->next;
                ++j;
                check = 1;
            }
            ++i;
        }
        i = 0;
        while(i <= tmp->line.length() - text.length()){
            if(tmp->line.substr(i,text.length()) == text){
                cout << j << " " << tmp->line << endl;
                check = 1;
                break;
            }
        }
        if(check == 0){
            cout << "not found" << endl;
        }
    }
    //delete method that removes a node at a given position from a linked list
    void deletePosition(int pos)
    {
        node *current=new node;
        node *previous=new node;
        node *num=new node;
        current=head;
        num=head;
        int length = 1;
        while(num->next!=NULL)
        {
           ++length;
           num = num->next;
        }
        if(length == pos){
            while(current->next!=NULL)
            {
                previous=current;
                current=current->next;
            }
            tail=previous;
            previous->next=NULL;
            delete current;
        }
        else if(pos == 1){
            node *temp=new node;
            temp=head;
            head=head->next;
            delete temp;
        }
        else{
        for(int i=1;i<pos;i++)
        {
        previous=current;
        current=current->next;
        }
        previous->next=current->next;
        }
    }
  };
//main method mostly devoted to user interface and calls to linked list methods
  int main(){
    list thing;
    int x = 1;
    while(x == 1){
    cout << "\nPlease type what you would like to do:" << endl;
    cout << "insertEnd 'text here'" << endl;
    cout << "insert 'position number' 'text here'" << endl;
    cout << "delete 'position number'" << endl;
    cout << "edit 'position number' 'text here'" << endl;
    cout << "print" << endl;
    cout << "search 'text here'" << endl;
    cout << "quit" << endl;
    string input;
    getline(cin, input);
    if(input.substr(0,9) == "insertEnd"){
        input = input.substr(10);
        thing.createNode(input);
    }
    else if(input.substr(0,7) == "insert "){
        int i = 0;
        stringstream geek(input.substr(7,1));
        geek >> i;
        thing.insertPosition(i, input.substr(8));
    }
    else if(input.substr(0,6) == "delete"){
        int i = 0;
        stringstream geek(input.substr(7,1));
        geek >> i;
        thing.deletePosition(i);
    }
     else if(input.substr(0,4) == "edit"){
        int i = 0;
        stringstream geek(input.substr(5,1));
        geek >> i;
        thing.editPosition(i, input.substr(6));
    }
    else if(input.substr(0,5) == "print"){
        thing.display();
    }
    else if(input.substr(0,6) == "search"){
        thing.search(input.substr(7));
    }
    else if(input.substr(0,4) == "quit"){
        x = 0;
    }
    else{
        cout << "Please type your command again paying close attention to detail" << endl;
    }
    }
    return 0;
  }
