#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <stdlib.h>
using namespace std;
//linked list implementation here
struct Node
{
    char data[80];
    Node *next;
};
class LinkedList
{
private:
            Node *head, *tail;
public:
    LinkedList()
    {
        head=NULL;
        tail=NULL;
    }
    ~LinkedList(){
        Node* temp = head;
        Node* prev=temp;
        while(temp){
            prev=temp;
            temp=temp->next;
            delete prev;

        }
    }
    Node* insertEnd(char *text);
    void print();
    void deleteLine(char *text);
    Node* insert(char *text);
    Node* edit(char *text);
    void search(char *text);
};
Node* LinkedList::insertEnd(char *text)
{
    Node *temp=new Node;
    char *firstQuote= strstr (text,"\"");
    char *secondQuote = NULL;
    if(firstQuote != NULL)
    {
        firstQuote += 1;
        secondQuote = strstr(firstQuote, "\"");
        if(secondQuote != NULL)
        {
            *secondQuote = '\0';
        }
    }
    else
    {
        return head;
    }
    strcpy(temp->data, firstQuote );
    temp->next=NULL;
    if(head==NULL)
    {
        head=temp;
        tail=temp;
    }
    else
    {
        tail->next=temp;
        tail=temp;
    }
    return head;

};

void LinkedList::deleteLine(char* text) {
    int specIndex=0;
    int dist = strlen(text)-7;
    char indexArray[5] ={};
    strncpy(indexArray,&text[7],5);
    indexArray[dist]='\0';
    specIndex=stoi(indexArray);
    Node *temp = NULL;
    int count = 1;
    Node *prev = head;
    for(temp = head; temp != NULL; temp = temp->next)
    {
        if (count == specIndex)
        {
            if(count == 1)
            { // delete head
                head = temp->next;
            }
            else
            {
                prev->next = temp->next; //bypass temp
            }
            delete temp; //free memory
            break;
        }
        prev = temp;
        count++;
    }

};

Node* LinkedList::insert(char *text) {
        int specIndex=0;
        char* quote=strstr(text,"\"");
        int dist = quote-text-8;
        char indexArray[5] ={};
        strncpy(indexArray,&text[7],5);
        indexArray[dist]='\0';
        specIndex=stoi(indexArray);
        Node* previous=NULL;
        Node* current=NULL;
        Node* temp=NULL;
        current=head;
        previous = current;
        for(int i=1;i<specIndex;i++)
        {
            previous=current;
            if(current==NULL){
                break;
            }
            current=current->next;
        }
    char *secondQuote = NULL;
    if(quote != NULL)
    {
        quote += 1;
        secondQuote = strstr(quote, "\"");
        if(secondQuote != NULL)
        {
            *secondQuote = '\0';
        }
    }
    else
    {
        return temp;
    }
    if(previous != NULL)
    {
        temp=new Node;
        strcpy(temp->data,quote);
        previous->next=temp;
        temp->next=current;
    }
    return temp;

};

Node* LinkedList::edit(char *text) {
    Node* temp=NULL;
    int specIndex=0;
    char* quote=strstr(text,"\"");
    int dist = quote-text-6;
    char indexArray[5] ={};
    strncpy(indexArray,&text[5],5);
    indexArray[dist]='\0';
    specIndex=stoi(indexArray);
    char *secondQuote = NULL;
    if(quote != NULL)
    {
        quote += 1;
        secondQuote = strstr(quote, "\"");
        if(secondQuote != NULL)
        {
            *secondQuote = '\0';
        }
    }
    else
    {
        return temp;
    }
    int count = 1;
    for(temp = head; temp != NULL; temp = temp->next)
    {
        if(count == specIndex)
        {
            strcpy(temp->data,quote);
            break;
        }
        count++;
    }
    return temp;
};

void LinkedList::search(char *text) {
    Node *temp = NULL; //new Node;
    int count = 1;
    temp = head;
    int found = 0;
    char* quote=strstr(text,"\"");
    char *secondQuote = NULL;
    if(quote != NULL)
    {
        quote += 1;
        secondQuote = strstr(quote, "\"");
        if(secondQuote != NULL)
        {
            *secondQuote = '\0';
        }
    }
    while(temp){
        if (strstr(temp->data, quote)) {
            std:: cout<< count<<" " << temp->data << endl;
            found = 1;
        }
        temp=temp->next;
        count++;
    }
    if(found == 0)
    {
        cout<< "not found" <<endl;
    }

};



void LinkedList::print()
{
    int index = 1;
    Node *tempP = NULL;
    tempP=head;
    while(tempP!=NULL)
    {
        std:: cout<<index<<" "<<tempP->data<<"\n";
        tempP=tempP->next;
        index++;
    }

};

//your line editor implementation here
int main() {
LinkedList list1;

//your code to invoke line editor here'
    string input;
    char data[80]={};
    //char keywords;
    char * token;
    char dataSentence[80]={};
    int firstQuote = 0;
    int secondQuote = 0;
  while (1) {
      getline(cin,input);
      strncpy(data,input.data(),80);
      if(strstr(data, "quit")){
                break;
  }
      else if(strstr(data, "insertEnd")){
          list1.insertEnd(data);
      }
      else if(strstr(data,"insert")){
          list1.insert(data);
      }
      else if(strstr(data,"delete")){
          list1.deleteLine(data);
      }
      else if (strstr(data,"edit")){
          list1.edit(data);
      }
      else if(strstr(data,"search")){
          list1.search(data);
      }
      else if(strstr(data,"print")){
          list1.print();
      }
  }
    return 0;
}