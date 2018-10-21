#include<iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
};

Node* head;

void Print()
{
    //cout << "The List is: \n";
    Node* temp = head;
    cout << "\n";
    int count = 0;
    while (temp != NULL)
    {
        count = count + 1;
        cout << count << " " << temp->data << "\n" <<endl;
        temp = temp->next;
    }

}

void Delete(int n)
{
    if ( n == 1 )
    {
        Node* temp = head;
        head = temp -> next;
        delete temp;
        return;
    }

    Node* temp1 = head;

    for(int i = 0; i < n-2; i++)
    {
        temp1 = temp1 -> next;
    }

    Node* temp2 = temp1 -> next;
    temp1 -> next = temp2 -> next;
    delete temp2;
}

void Insert(string x, int position)
{
    Node* temp = new Node();
    temp -> data = x;
    temp -> next = NULL;

    if ( position == 1 )
    {
        temp -> next = head;
        head = temp;
        return;
    }

    Node* temp1 = head;

    for (int i = 0; i < position-2; i++)
    {
        temp1 = temp1 -> next;
    }


    temp -> next = temp1 -> next;
    temp1 -> next = temp;
}
void insertEnd(string data) {

    Node* temp = new Node();

    temp = head;
    while (temp->next!=NULL) {
        temp = temp->next;
    }
    Node* end=new Node();
    end->data=data;
    end->next=NULL;
    temp->next=end;
};
void search(string d)
{
    Node* searchedNode = nullptr;
    Node*  temp = head;
    Node* current = head;

    int count = 1;
    while (current != NULL && (current->data).find(d)==  std::string::npos)
    {
        count = count + 1;
        temp = current;
        current = current->next;
    }
    if (current != NULL)
    {
        searchedNode = current;
        current = current->next;
        cout << count << " " << searchedNode->data << "\n\n";
    }
    else
    {
        cout << "N/A \n";
    }
};
void edit( int position, string text) {
    Node* temp = head;
    int count = 1;
    while (count != position) {
        count = count + 1;
        temp = temp->next;
    }
    temp->data = text;

};
void quit() {
    return;
};

int main() {
    head = NULL;


    //command example: insert 2 "now is the time"

    string temp1;

    do {
        string input;
        getline(cin, input);

        string temp2;
        string temp3;
        if (input == "quit") {
            temp1 = "quit";
            break;
        } else if (input == "print") {
            temp3 = 5;
            temp1 = "print";
        } else {
            for (size_t i = 0; i < input.length(); i++) {
                char c = input[i];
                if (c == ' ') {
                    temp1.append(input.substr(0, i));
                    i++;
                    if (isdigit(input[i])) {
                        temp3 = (input[i]);
                        i++;
                        if (input[i] == ' ') i++;
                    }
                    if (input[i] == '\"') {
                        i++;
                        while (input[i] != '\"') {
                            temp2 += input[i];
                            i++;
                        }
                        break;
                    }

                }

            }

        }


        if (temp1 == "insert") {  //insert 2 "now is the time"
            Insert(temp2, stoi(temp3));
            temp1.clear();
        } else if (temp1 == "insertEnd" && head == NULL) {
            Insert(temp2, 1);
            temp1.clear();
        } else if (temp1 == "insertEnd") {  //insertEnd "now is the time"
            //if(temp3.length==0) temp3=1;
            insertEnd(temp2);
            temp1.clear();
        } else if (temp1 == "print") {  //print
            Print();
            temp1.clear();
        } else if (temp1 == "delete") { //delete 3
            Delete(stoi(temp3));
        } else if (temp1 == "search") { //search "time"
            search(temp2);
            temp1.clear();
        } else if (temp1 == "edit") {  //edit "time" 2
            edit(stoi(temp3), temp2);
            temp1.clear();
        } else if (temp1 == "quit") { //quit
            quit();
        } else {
            cout << temp1 << "Not valid input" << "\n";
        }

    } while (temp1 != "quit");


    return 0;
}