#include <iostream>
#include <string> 
using namespace std;

//your linked list implementation here
struct List {
    string line = "";
    List* next=NULL;

};

//your line editor implementation here
void insertEnd (List* ln, string text) {
    if(ln->line == "")
        ln->line = text;
    else {
        List* newLn = new List();
        newLn->line = text;
        while(ln->next != NULL) {
            ln = ln->next;
        }
        ln->next = newLn;
    }
}

List* insert (List* ln, int i, string text) {
    List* hd = new List();
    if (i == 1) {
        hd->next = ln;
        hd->line = text;
    } else {
        hd = ln;
        while (i > 2) {
            if(ln->next == NULL) return hd; //out of bounds
            ln = ln->next;
            i--;
        }
        List* newln = new List();
        newln->line=text;
        newln->next = ln->next;
        ln->next = newln;
    }
    return hd;
}

List* deleteLn (List* ln, int i) {
    List* hd;
    if(i == 1) {
        hd = ln->next;
        delete ln;
    } else {
        hd = ln;
        int c = 1;
        while (c < i - 1) {
            if(ln->next->next == NULL) return hd;
            ln = ln->next;
            c++;
        } // reach right before target
        ln->next = ln->next->next;
    }
    return hd;
}

void edit (List* ln, int i, string text) {
    while (i > 1) {
        if(ln->next == NULL) return;
        ln = ln->next;
        i--;
    }
    ln->line = text;
}

void print (List* ln) {
    int i = 1;
    while (ln != NULL) {
        cout << i << " " << ln->line << endl;
        i++;
        ln = ln->next;
    }
}

void search (List* ln, string text) {
    int i = 1;
    bool found = false;
    while (ln != NULL) {
        if (ln->line.find(text) != string::npos) {
            cout << i << " " << ln->line << endl;
            found = true;
        }
        i++;
        ln = ln->next;
    }
    if (!found) cout << "not found" << endl;
}

int main() {
    // Input variables
    List* head = new List();
    string cmd; 
    bool quit = false;
    
    while(!quit) {
        cin >> cmd;
        if(cmd == "insertEnd") {
            string text;
            getline(cin, text);
            insertEnd(head, text.substr(2,text.size()-3));
        } else if(cmd == "insert") {
            int i;
            cin >> i;
            string text;
            getline(cin, text);
            head = insert(head, i, text.substr(2,text.size()-3));
        } else if(cmd == "delete") {
            int i;
            cin >> i;
            head = deleteLn(head, i);
        } else if(cmd == "edit") {
            int i;
            cin >> i;
            string text;
            getline(cin, text);
            edit(head, i, text.substr(2,text.size()-3));
        } else if(cmd == "print") {
            print(head);
        } else if(cmd == "search") {
            string text;
            getline(cin, text);
            search(head, text.substr(2,text.size()-3));
        } else if(cmd =="quit") {
            quit = true;
        } // else do nothing
    }
    return 0;
}