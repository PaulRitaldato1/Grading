#include <iostream>
#include <string>
/*
    Luis Medina (1158-1149)
    Programming Assignment 1
*/
using namespace std;
int w = 1;

struct Node
{
    string data;
    Node* next;
};
struct Node* head;

void insertEnd(string data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->next = NULL;

    Node *ptr = head;

    if(head == NULL)
    {

    head = temp;
    return;
    }
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    return;
}
void insertNth (string data, int n)
{
    Node* temp1 = new Node();
    temp1->data = data;
    temp1->next = NULL;
    if(n==1)
    {
        temp1->next = head;
        head = temp1;
        return;
    }
    Node * temp2 = head;
    for(int i = 0; i<n-2;i++)
    {
        temp2 = temp2->next;

    }
    temp1->next = temp2->next;
    temp2->next = temp1;
}
void Delete(int n)
{
    Node* temp1 = head;
    if(n==1)
    {
        head == temp1->next;
        delete(temp1);
        return;
    }

        int i;
        for(i=0; i<n-2; i++)
        {
            temp1 = temp1->next;

        }
        Node* temp2 = temp1->next;
            temp1->next = temp2->next;
            delete(temp2);
}

void replaceNode(string data, int n)
{
    Delete(n);
    insertNth(data, n);
}

void search(Node* head, string x)
{

    if (head == NULL)
        {
            cout << "not found" << endl;
            return;
        }
    else if(head->data.find(x) < 82)
        {
            cout << w << " " << head->data << "\n";
            return;
        }
        w++;
    return search(head->next, x);
}

void print()
{
    int i;
    i = 1;
    Node* temp = head;

    while(temp!= NULL)
    {
        cout << i << " " <<  temp->data <<endl;
        temp = temp->next;
        i++;
    }
}

void quit()
{
    cout << "\nProgram terminated." << endl;
    cout << "" << endl;
    exit(0);
}

int main()
{

    cout << "User commands: \n" << endl;
    cout << "insertEnd 'text'  -- insert given text at the end of the document" << endl;
    cout << "insert n 'text' -- insert given text at the line indicated by index given" << endl;
    cout << "delete n --- delete line at index given" << endl;
    cout << "edit n 'text' --- replace the line at the index given with the given text" << endl;
    cout << "print -- prints the entire document, with line numbers" << endl;
    cout << "search 'text' -- prints the line number and line that contains the given text." << endl;
    cout << "quit - quit/exit the program\n" << endl;

    string choice, text;
    getline(cin, choice);

    while(choice.find("q") != 0)
    {

        if(choice.find("End") == 6)//insertEnd
        {
            string text;
            int x, y, z;
            x = choice.find("\"");
            y = choice.rfind("\"");
            z = y - x - 1;
            text = choice.substr(x+1,z);
            insertEnd(text);
        }
        else if(choice.find("ns") == 1)//insert Nth
        {
            string text, one, two, three, four, five, six, seven, eight, nine, position;
            int x, y, z, n;
            x = choice.find("\"");
            y = choice.rfind("\"");
            z = y - x - 1;
            text = choice.substr(x+1,z);
            position = choice.substr(7,1);
            one = "1";
            two = "2";
            three = "3";
            four = "4";
            five = "5";
            six = "6";
            seven = "7";
            eight = "8";
            nine = "9";
            if(position == one)
            {
                insertNth(text, 1);
            }
            else if(position == two)
            {
                insertNth(text, 2);
            }
            else if(position == three)
            {
                insertNth(text, 3);
            }
            else if(position == four)
            {
                insertNth(text, 4);
            }
              else if(position == five)
            {
                insertNth(text, 5);
            }
              else if(position == six)
            {
                insertNth(text, 6);
            }
              else if(position == seven)
            {
                insertNth(text, 7);
            }
             else if(position == eight)
            {
                insertNth(text, 8);
            }
             else if(position == nine)
            {
                insertNth(text, 9);
            }


        }
        else if(choice.find("l")==2)//delete
        {
            string text, one, two, three, four, five, six, seven, eight, nine, position;;
            int x, y, z, n;
            x = choice.find("\"");
            y = choice.rfind("\"");
            z = y - x - 1;
            text = choice.substr(x+1,z);
            position = choice.substr(7,2);
            one = "1";
            two = "2";
            three = "3";
            four = "4";
            five = "5";
            six = "6";
            seven = "7";
            eight = "8";
            nine = "9";

            if(position == one)
            {
                Delete(1);
            }
            else if(position == two)
            {
                Delete(2);
            }
            else if(position == three)
            {
                Delete(3);
            }
            else if(position == four)
            {
                Delete(4);
            }
            else if(position == five)
            {
                Delete(5);
            }
            else if(position == six)
            {
                Delete(6);
            }
            else if(position == seven)
            {
                Delete(7);
            }
            else if(position == eight)
            {
                Delete(8);
            }
            else if(position == nine)
            {
                Delete(9);
            }
        }
          else if(choice.find("t")==3)//edit
        {
            string one, two, three, four, five, six, seven, eight, nine, position;;
            int x, y, z, n;
            x = choice.find("\"");
            y = choice.rfind("\"");
            z = y - x - 1;
            text = choice.substr(x+1,z);
            position = choice.substr(5,1);
            one = "1";
            two = "2";
            three = "3";
            four = "4";
            five = "5";
            six = "6";
            seven = "7";
            eight = "8";
            nine = "9";

            if(position == one)
            {
                replaceNode(text, 1);
            }
            else if(position == two)
            {
                replaceNode(text, 2);
            }
            else if(position == three)
            {
                replaceNode(text, 3);
            }
            else if(position == four)
            {
                replaceNode(text, 4);
            }
            else if(position == five)
            {
                replaceNode(text, 5);
            }
            else if(position == six)
            {
                replaceNode(text, 6);
            }
           else if(position == seven)
            {
                Delete(7);
            }
            else if(position == eight)
            {
                Delete(8);
            }
            else if(position == nine)
            {
                Delete(9);
            }

        }
          else if(choice.find("t")==4)//print
        {
            print();
        }
        else if(choice.find("h")==5)//search
        {
            string text;
            int x, y, z;
            x = choice.find("\"");
            y = choice.rfind("\"");
            z = y - x - 1;
            text = choice.substr(x+1,z);

            search(head, text);
        }
        cout<< "";
        getline(cin, choice);
    }

    return 0;
}

