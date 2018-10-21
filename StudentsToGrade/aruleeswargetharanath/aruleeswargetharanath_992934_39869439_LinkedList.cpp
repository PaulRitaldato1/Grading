//your linked list implementation here
#ifndef LinkedList_H
#define LinkedList_H
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

class LinkedList {
public:
    class Node {
    public:
        Node(){}
        ~Node(){
        }
        string data;
        Node * next = nullptr;
        Node * prev = nullptr;
    };
    LinkedList() {}
    LinkedList(const LinkedList &list) {
        this->count = list.count;
        Node * n = new Node;
        const Node * f  = list.head;
        n->data = list.head->data;
        head= n;
        f = f->next;
        while (f != nullptr){
            Node * o = new Node;
            o->data = f->data;
            o->prev = n;
            n->next = o;
            n = o;
            f = f->next;
        }
        tail = n->prev;
    }
    LinkedList &operator=(const LinkedList &rhs){
        Clear();
        this->count = rhs.count;
        Node * n = new Node;
        const Node * f  = rhs.head;
        n->data = rhs.head->data;
        head= n;
        f = f->next;
        while (f != nullptr){
            Node * o = new Node;
            o->data = f->data;
            o->prev = n;
            n->next = o;
            n = o;
            f = f->next;
        }
        tail = n->prev;
        return *this;
    }
    const string &operator[](unsigned int index) const{
        Node *f = head;
        if (index < 0 || index >= count)
            throw "Invalid Index";
        if (index != 0) {
            for (unsigned int i = 1; i <= index; i++) {
                f = f->next;
            }
        }
        return f->data;
    }
    string &operator[](unsigned int index) {
        Node *f = head;
        if (index < 0 || index >= count)
            throw "Invalid Index";
        if (index != 0) {
            for (unsigned int i = 1; i <= index; i++) {
                f = f->next;
            }
        }
        return f->data;
    }
    bool operator==(const LinkedList &rhs) {
        if (this->count == rhs.count) {
            Node *f = this->head;
            const Node *g = rhs.Head();
            while (f != nullptr) {
                if (f->data != g->data) {
                    cout << "false" << endl;
                    return false;
                }
                f = f->next;
                g = g->next;
                cout << "true";
            }
            cout << "true3";
            return true;
        } else {
            cout << "false1";
            return false;
        }
    }
    void print() const{
        Node * f = head;
        int i = 1;
        while (f != nullptr) {
            cout << i << " " << f->data << endl;
            f = f->next;
            i++;
        }
    }
    unsigned int NodeCount () const{
        return count;
    }
    void search(string data){
        int lineNum = 1;
        bool search = false;
        Node * node = head;

        while(node->next != nullptr){
            string text = node->data;

            if (text.find(data) != string::npos){
                cout << lineNum << " " << node->data << endl;
                search = true;}

            node = node->next;
            lineNum++; }

        string text = node->data;

        if (text.find(data) != string::npos){
            cout << lineNum << " " << node->data << endl;
            search = true; }

        if(!search){
            cout << "not found" << endl; }
    }
    void edit(string data, int position) {
        int index = 0;
        Node *n = head;

        while (index + 1 != position){
            n = n->next;
            index++;}
        n = n->next;
        n->data = data;
    }

    const Node * GetNode(unsigned int index) const{
        Node *f = head;
        for (unsigned int i = 1; i <= index; i++){
            if (f != nullptr)
                f = f->next;
        }
        return f;
    }
    Node * GetNode(unsigned int index) {
        Node *f = head;
        for (unsigned int i = 1; i <= index; i++){
            if (f != nullptr)
                f = f->next;
        }
        return f;
    }
    Node * Head(){
        return head;
    }
    const Node * Head() const{
        return head;
    }
    Node * Tail() {
        return tail;
    }
    const Node * Tail() const{
        return tail;
    }
    void AddHead(const string &data) {
        count++;
        Node *n = new Node;
        n->data = data;
        n->next = head;
        if (head != nullptr) {
            head->prev = n;
        } else {
            tail = n;
        }
        head = n;
        //delete n;
    }
    void insertEnd(const string &data) {
        count++;
        Node *n = new Node;
        n->data = data;
        n->prev = tail;
        if (tail != nullptr) {
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
    }
    void InsertAfter(Node *node, const string &data) {
        Node *f = head;
        count++;
        while (f != nullptr){
            if (f == node) {
                Node *g = new Node;
                g->data = data;
                g->prev = f;
                g->next = f->next;
                f->next = g;
                g->next->prev = g;
                break;

            }
            f = f->next;
        }
    }
    void insertAt(const string &data, unsigned int index){
        if (index >= 0 && index <= count){
            if (index == 0){
                AddHead(data);
            } else if (index == count) {
                insertEnd(data);
            } else {
                Node * f = head;
                for (unsigned int i = 1; i < index; i++){
                    f = f->next;
                }
                InsertAfter(f, data);
            }
        } else {
            throw "Invalid Index";
        }
    }
    bool RemoveHead(){
        if (head != nullptr) {
            //head->next->prev = nullptr;
            Node *f = head->next;
            delete head;
            head = f;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            count--;
            return true;
        } else {
            return false;
        }
    }
    bool RemoveTail(){
        if (tail != nullptr) {
            Node*f = tail->prev;
            delete tail;
            tail = f;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            count--;
            return true;
        } else {
            return false;
        }
    }
    bool deleteAt(int index) {
        if ((unsigned int)index < count && index >= 0) {
            if (index == 0) {
                RemoveHead();
            } else if ((unsigned int)index == count -1) {
                RemoveTail();
            } else {
                Node *f  =head;
                for (int i = 1; i <= index; i++) {
                    f = f->next;
                }
                Node *g = f;
                f->prev->next = f->next;
                f->next->prev = f->prev;
                g->next = nullptr;
                g->prev = nullptr;
                delete g;
                count--;
            }
            return true;
        } else {
            return false;
        }
    }
    void Clear(){
        while (RemoveHead()){}
        head= nullptr;
        tail = nullptr;
        count = 0;
    }
    ~LinkedList(){
        Node *f = head;
        while (f != nullptr){
            Node *g = f->next;
            delete f;
            f = g;
        }
    }
private:
    unsigned int count = 0;
    Node * head = nullptr;
    Node * tail = nullptr;
};
#endif

//your line editor implementation here

int main()
{
    LinkedList data;
    bool loop = true;
    int var;

    while (loop){
        string command = "";
        int index = 0;
        string text = "";

        cin >> command;
        if (command == "insertEnd") {
            cin >> text;

            while (text.at(text.length() - 1) != '"') {
                string text1 = "";
                cin >> text1;
                text += " " + text1;}

            string stext = text;
            text = stext.substr(1, stext.length() - 2);
            data.insertEnd(text); }

        else if (command == "insert") {
            cin >> index;
            cin >> text;
            while (text.at(text.length() - 1) != '"') {
                string temp = "";
                cin >> temp;
                text += " " + temp; }
            string stext = text;
            text = stext.substr(1, stext.length() - 2);


            if (index > var + 2) {}

            else {
                data.insertAt(text, index - 1); }
        }
        else if (command == "delete") {
            var = data.NodeCount();

            cin >> index;

            if (index > var) {}
            else {
                data.deleteAt(index - 1); }
        }
        else if (command == "edit") {
            cin >> index;
            cin >> text;
            while (text.at(text.length() - 1) != '"') {
                string temp = "";
                cin >> temp;
                text += " " + temp;
            }
            string stext = text;
            text = stext.substr(1, stext.length() - 2);
            data.edit(text, index - 1);
        }
        else if (command == "search") {
            cin >> text;
            while (text.at(text.length() - 1) != '"') {
                string temp = "";
                cin >> temp;
                text += " " + temp;
            }
            string stext = text;
            text = stext.substr(1, stext.length() - 2);
            data.search(text);
        }
        else if (command == "print") {
            data.print(); }

        else if (command == "quit") {
            loop = false; }
        else {
            cout << "Check input" << endl; }
    }
    return 0;
}