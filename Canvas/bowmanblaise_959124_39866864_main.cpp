#include <iostream>
#include <string>
#include <sstream>
#include <w32api/mmcobj.h>
#include <vector>
#include <bits/forward_list.h>

using std::string;
using namespace std;

//your linked list implementation here
class ListNode
{
public:
    ListNode () ;
    ListNode (const int data, const ListNode *next) ;
    ~ListNode () ;


private:
    int data ;
    ListNode *next ;
    ListNode *previous ; // Optional
};

class LinkedList
{
public:

private:
    ListNode *head ;
    ListNode *tail ; // Optional
};
struct node {
    string data;
    node* next;
    node* datas;
    node(std::string & val, node* n = 0) : data(val), next(n) {}
    node(node* n = 0) : next(n) {}
};

struct node *head;
struct node *tail;

node insertEnd(node &first, string text) { // insert given text at the end of the document
    node *tmp = new node;
    tmp->data = text;
    tmp->next = NULL;

    if(head == NULL)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
    return head;

}

void insert(node &n, string data, int pos) { //insert given text at the line indicated by index given
    node* temp;
    node* prev;
    node* curr;
    node* newNode;
    newNode->data = data;
    int tempPos = 0;
    curr = head;
    if(head != NULL)
    {
        while(curr->next != NULL && tempPos != pos)
        {
            prev = curr;
            curr = curr->next;
            tempPos++;
        }
        if(pos==0)
        {
            temp->next=head;
            head=temp;
            return;
        }
        else if(curr->next == NULL && pos == tempPos+1)
        {
            node* temp1;
            temp1->data = data;
            temp1->next = head;
            head = temp1;
        }

        else
        {
            prev->next = newNode;
            newNode->next = curr;
        }
    }
    else
    {
        head = newNode;
        newNode->next=NULL;
    }
}

void del(node &n, int pos) //deletes the given line of the linked list
{
    node *current=new node;
    node *previous=new node;
    current=head;
    for(int i=1;i<pos;i++)
    {
        previous=current;
        current=current->next;
    }
    previous->next=current->next;
}

void edit(node &n, int pos, string text){ //replace the line at the index given with the given text

    node *current=new node;
    node *previous=new node;
    current=head;
    for(int i=1;i<pos;i++)
    {
        previous=current;
        current=current->next;
    }
    previous->next=current->next;
    node* newNode;
    newNode -> data = text;
}

void print(node* head) {
    void print(node* n) {
        cout << n -> data << endl;
        if(n -> next) print(n -> next);
    }
}

void search(std:: vector <string> a, string text) { //print the line number and line that contains the given text.  print "not found" if it is not found
    for(int i=0; i < a.size(); i++){
        string content = a[i];
        if(text == text){
            std::string s = std::to_string(i);
            cout << s + content;
        }
        else {
            //
        }
    }
}

std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
    std::vector<std::string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;
    while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
    {
        std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
        splittedString.push_back(val);
        startIndex = endIndex + delimeter.size();
    }
    if(startIndex < stringToBeSplitted.size())
    {
        std::string val = stringToBeSplitted.substr(startIndex);
        splittedString.push_back(val);
    }
    return splittedString;
}


std::vector <string> textSc () { //used to scan the user input and format into multiple lines
    string input;
    std :: string a;
    vector<string> lines;
    while (std::getline(std::cin >> std::ws, a))
    {
        if (!a.empty())
            lines.push_back(a);
    }
    while (std::getline(std::cin, input)) {
        getline(cin, input);
        std::vector<std::string> splittedStrings = split(input, "\n");

        for (int i = 0; i < splittedStrings.size(); i++) {
            std::cout << splittedStrings[i] << std::endl;
        }
    }
    while (std::getline(std::cin >> std::ws, a))
    {
        if (!a.empty())
            lines.push_back(a);
    }
}



int main() {
    node a = new node;
    node g = new node;
    ListNode *b;
    struct node head = NULL;
textSc();
    //vector <string> content = textSc();    //textSc();
    string textBlock;
    string input;
    vector<string> lines = textSc();
    while (std::getline(std::cin, input)) {
        unsigned long first = 0;
        unsigned long last = 0;
        textBlock = input + "\n";
            first = input.find('"');
            last = input.find_last_of('"');
            string strNew = input.substr(first + 1, last - first - 1); //gets the text in between the qoutes
            std::cin.ignore();
            lines.push_back(strNew);
            if (input.find("insertEnd") == std :: string :: npos) {
                g = insertEnd(a, strNew);
            }
            else if (input.find("insert") != std :: string :: npos && input.find("End") == std :: string :: npos){
                string posi = input.substr(6, first);
                int pos = stoi(posi);
                insert(a,strNew,pos);
            }
            else if (textBlock.find("delete") == std :: string :: npos){
                string posi = input.substr(6, first);
                int pos = stoi(posi);
                del(a,pos);
            }
            else if(textBlock.find("edit") == std :: string :: npos){
                string posi = input.substr(4, first);
                int pos = stoi(posi);
                edit (a, pos, strNew);
            }
            else if(input.find("search") == std :: string :: npos){
                search(lines,strNew);
            }
            else if (input.find("print") != std:: string :: npos)
            {
                print(g.datas);
            }
            else if(input.find("quit") == std :: string :: npos){
                break;
            }
        else {
               continue;
        };
        }
    }


