#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

class LinkedList{
    // Struct inside the class LinkedList
    // This is one node which is not needed by the caller. It is just
    // for internal work.
    struct Node {
        string data;
        Node * next;
    };

// public member
public:
    // constructor
    int size=0;
    LinkedList(){
        head = NULL; // set head to NULL
    }

    // destructor
    ~LinkedList(){
        Node *next = head;

        while(next) {              // iterate over all elements
            Node *deleteMe = next;
            next = next->next;     // save pointer to the next element
            delete deleteMe;       // delete the current entry
        }
    }
    void edit(string val, int position) {


        struct Node *c;
        int count=1;
        c=head;
        while(count!=position)
        {
            c=c->next;
            count++;
        }
        c->data = val;

        return;


    }
    void search(string val) {


        struct Node *c;
        int count=1;
        c=head;
        int x = 1;
        int k = 0;
        while(k == 0)
        {
            c=c->next;
            x++;
            if (c->data.find(val) != std::string::npos){
                k=1;
            }

        }
        cout << endl;
        cout << x << " " << c->data;

        return;


    }

    void remove(int position) {


        struct Node *c;
        int count=1;
        c=head;
        while(count!=position)
        {
            c=c->next;
            count++;
        }
        c->data = c->next->data;

        // stores address of next node
        struct Node *n = c->next;

        // Removes the link of next node
        c->next = c->next->next;

        // frees memory
        free(n);

        return;


    }

    // This prepends a new value at the beginning of the list
    bool addValue(string val){
        Node * newNode;

        newNode = new Node;  // creates new node
        newNode->data = val;             // sets value
        newNode->next = nullptr;

        head == nullptr;
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode; // inserts node at end of list
            tail = newNode;
        }// make the node point to next one.
        //  If the list is empty, this is NULL, so the end of the list --> OK

        return head;// makes head point to new node.
    }


    void insertNth(string val, int position) {

        struct Node *n=new struct Node;
        n->data=val;
        if(position==0)
        {// this will also cover insertion at head (if there is no problem with the input)

            n->next=head; // assigns head to n's next
            head=n; // assigns n to head
        }

        else
        {
            struct Node *c; // creates node pointer c
            int count=1; // count to keep track
            c=head; // asigns head to c node pointer
            while(count!=position) // while c does not equal the position passed on
            {
                c=c->next; // c equals c's next
                count++;
            }
            n->next=c->next;
            c->next=n;

        }
        return ;
    }


    void print() const
    {
        int k = 1; // creats int k
        Node * current; // creates current node

        current = head; // assigns head to current node

        while (current != nullptr) // while current is not null runs program
        {
            cout << endl;
            cout << k << " " << current->data;
            current = current->next;
            k++;
        }
    }

// private members
private:
    Node *head;// this is the private member variable. It is just a pointer to the first Node
    Node *tail;// this is the private member variable. It is just a pointer to the last Node
};

int main() {
    int x=0;
    LinkedList list;
    string s = "";



    while(s != "quit") {   // while user doesnt enter quit, program continues
        char input[80]; // string of 80 characters
        cin.getline(input,sizeof(input));

        string s1 = input; // creates user input string

        if (s1.find("print") != string::npos) // if user input contains print
                list.print(); // calls print method


        if (s1.find("insertEnd") != string::npos) { // if user input contains insertEnd
            list.addValue(s1.substr(11,s1.size()-12)); // calls addValue method, adding only part of input
            x++;
        }
        if (s1.find("insert ") != string::npos) { // if input contains insert
            string x = s1.substr(7,s1.size()-12); // makes string of desired input from user
            const char * c = x.c_str(); // converts to const char
            int i = atoi (c);


            list.insertNth(s1.substr(10,s1.size()-11) ,i-1); // calls insertNth method




        }
        if (s1.find("delete ") != string::npos) { // if user input contains "delete"
            string x = s1.substr(7,s1.size()-12); // makes string from desired substring
            const char * c = x.c_str(); // converts to const char
            int i = atoi (c);



            list.remove(i ); // calls remove method




        }
        if (s1.find("edit ") != string::npos) { // if inout contain edit
            string x = s1.substr(5,s1.size()-12); // creates string from desired substring
            const char * c = x.c_str(); // converts to const char
            int i = atoi (c);



            list.edit(s1.substr(8,s1.size()-9), i ); // calls edit method




        }

        if (s1.find("quit") != string::npos) { // if inout contains quit

            s = "quit"; // string s equals quit which terminates the program
        }
        if (s1.find("search") != string::npos) { // if input contains search
            list.search(s1.substr(8,s1.size()-12)); // calls search method
            x++;
        }


    }

    return 0;
}