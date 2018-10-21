#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct node {
    string data;
    node *next;
};

class list {
    private:
        node *head;
        node *tail;
    public:
        list() {
            head=NULL;
            tail=NULL;
        }
        void insertEnd(string text) {
            node *temp = new node;
            temp->data = text;
            temp->next = NULL;
            if(head == NULL) {
                head = temp;
                tail = temp;
                temp = NULL;
            }
            else {
                tail->next = temp;
                tail = temp;
            }
        };

        void insertAt(int position, string text) {
            if (position == 1) {
                node *temp = new node;
                temp->data = text;
                temp->next = head;
                head = temp;
            }
            node *temp = new node;
            node *current = new node;
            node * previous = new node;
            current = head;
            for (int i = 1; i < position; i++) {
                previous = current;
                current = current->next;
            }
            temp-> data = text;
            previous->next = temp;
            temp->next = current;
        }

        void deleteAt(int position) {
            node *temp = new node;
            if (position == 1) {
                temp = head;
                head = head->next;
                delete temp;
                return;
            }

            node *current = head;

            for (int i = 1; i < position; i++) {
                if (current->next == NULL) {
                    tail == temp;
                    temp->next == NULL;
                    delete current;
                }
                temp = current;
                current = current-> next;
            }
            temp->next = current->next;

        }

        void edit (int position, string text) {
            node *current = head;
            for (int i = 1; i < position; i++) {
                current = current->next;
            }
            current->data = text;
        }

        string searchLine(string text) {
        node *current = head;
        int counter = 0;
        text = text.substr(1, text.size() - 2);

        while (current != NULL) {
            if (((current->data).find(text))!=string::npos) {
                stringstream ss;
                ss << counter+1;
                return ss.str() + " " + current->data;
            }
            counter++;
            current = current->next;
        }
        return "error not in document";
        }

        void printList() {
            node *temp = new node;
            temp = head;
            int counter = 1;
            while (temp!=NULL) {
                cout << counter;
                cout << " " <<temp->data << endl;
                temp = temp->next;
                counter++;
            }
        }
};



int main() {
    cout << "User commands:" << endl;
    cout << "insertEnd \"text\"" << endl;
    cout << "insert (line) \"text\"" << endl;
    cout << "delete (line)" << endl;
    cout << "edit (line) \"text\"" << endl;
    cout << "print" << endl;
    cout << "search \"text\"" << endl;
    cout << "quit\n" << endl;

    string option;
    string dataAdd;
    int dataAt;
    list editor;
    while (option != "quit") {
        cin >> option;
        while (option != "insertEnd" && option != "insert" && option!= "delete" && option != "edit" && option !="print" && option != "search" &&option != "quit") {
            cout << "error that is not a valid choice, please enter again" <<endl;
            cin >> option;
        }
        if (option == "quit") {
            break;
        }
        if (option != "insertEnd" && option != "print" && option != "search" ) {
            cin >> dataAt;
        }
        if (option != "print" && option != "delete") {
            cin.ignore();
            getline(cin,dataAdd);
        }


        if (option == "insertEnd") {
            editor.insertEnd(dataAdd);
        }
        else if (option == "insert"){
            editor.insertAt(dataAt,dataAdd);
        }
        else if (option == "delete") {
            editor.deleteAt(dataAt);
        }
        else if (option == "edit") {
            editor.edit(dataAt,dataAdd);
        }
        else if (option == "search") {
            cout << editor.searchLine(dataAdd) <<endl;
        }
        else if (option == "print") {
            editor.printList();
        }
    }

    return 0;
}
