#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

struct node {
    string data;
    node *next;
};
class linkedList {
    private:
        node *head;
        node *tail;
    public:
        linkedList(){
            head = nullptr;
            tail = nullptr;
        }
        int lineNumber = 1;

        void insertEnd (string newLine){
            if(newLine.length() > 80){
                return;
            }
            string lineNumberString = std::to_string(lineNumber);
            node *temp = new node;
            temp->data = lineNumberString + " " + newLine;
            temp->next = nullptr;

            if (head == nullptr){
                head = temp;
                tail = temp;
            }
            else{
                tail->next = temp;
                tail = tail->next;
            }
            lineNumber++;
        }

        void print(){
            node *tmp;
            tmp = head;
            while(tmp != nullptr){
                cout << tmp->data << endl;
                tmp = tmp->next;
            }

        }

        void edit(int ln, string replaceText){
            node *tmp;
            tmp = head;
            string theLine;
            replaceText = std::to_string(ln) + " " + replaceText;
            while(tmp != nullptr){
                theLine = tmp->data;
                long endNumber = theLine.find(" ");
                if(std::to_string(ln) == theLine.substr(0,endNumber)){
                    tmp->data = replaceText;
                    tmp = tmp->next;
                }
                else{
                    tmp = tmp->next;
                }
            }

        }

        void insert(int ln, string newLine){
            if(ln > 0) {
                node *tmp;
                tmp = head;
                node *p = new node;
                string prevLine;
                string theOldLine;
                string thisLine;
                newLine = std::to_string(ln) + " " + newLine;
                p->data = newLine;
                int newLineNumbers = ln + 1;
                if (ln == 1) {
                    p->data = newLine;
                    p->next = head;
                    head = p;
                    while (tmp != nullptr) {
                        thisLine = tmp->data;
                        long endNumber = thisLine.find(" ");
                        thisLine = std::to_string(newLineNumbers) + thisLine.substr(endNumber);
                        tmp->data = thisLine;
                        newLineNumbers++;
                        tmp = tmp->next;
                        lineNumber = newLineNumbers;
                    }
                } else {
                    for (int i = 1; i < ln - 1; i++) {
                        if (tmp != nullptr) {
                            prevLine = tmp->data;
                            tmp = tmp->next;
                        }
                    }
                    if (tmp != nullptr) {
                        p->next = tmp->next;
                        tmp->next = p;
                        tmp = tmp->next;
                    }


                    while (tmp != nullptr && tmp->next != nullptr) {
                        tmp = tmp->next;
                        thisLine = tmp->data;
                        long endNumber = thisLine.find(" ");
                        thisLine = std::to_string(newLineNumbers) + thisLine.substr(endNumber);
                        tmp->data = thisLine;
                        newLineNumbers++;
                        lineNumber = newLineNumbers;
                    }
                }
            }
        }

        void deleteNode(int ln){
            if(ln > 0) {
                node *tmp;
                node *before = new node;
                string thisLine;
                int newLineNumbers = ln;
                tmp = head;
                if (ln == 1) {
                    newLineNumbers = 1;
                    head = tmp->next;
                    delete tmp;
                    while (tmp->next != nullptr) {
                        tmp = tmp->next;
                        thisLine = tmp->data;
                        long endNumber = thisLine.find(" ");
                        thisLine = std::to_string(newLineNumbers) + thisLine.substr(endNumber);
                        tmp->data = thisLine;
                        newLineNumbers++;
                        lineNumber = newLineNumbers;

                    }
                } else {
                    for (int i = 1; i < ln; i++) {
                        if (tmp != nullptr) {
                            before = tmp;
                            tmp = tmp->next;
                        }
                    }
                    if (tmp != nullptr) {
                        tmp = before->next;
                        before->next = tmp->next;
                        delete tmp;
                    }
                    while (tmp != nullptr && tmp->next != nullptr) {
                        tmp = tmp->next;
                        thisLine = tmp->data;
                        long endNumber = thisLine.find(" ");
                        thisLine = std::to_string(newLineNumbers) + thisLine.substr(endNumber);
                        tmp->data = thisLine;
                        newLineNumbers++;
                        lineNumber = newLineNumbers;
                    }
                }
            }
        }

        void search(string phrase){
            node *tmp;
            tmp = head;
            string theLine;
            long isFound;
            bool isOutputted = false;
            while(tmp != nullptr){
                theLine = tmp->data;
                isFound = theLine.find(phrase);
                if(isFound != string::npos){
                    cout << tmp->data << endl;
                    isOutputted = true;
                    tmp = tmp->next;
                }
                else{
                    tmp = tmp->next;
                }
            }
            if(isOutputted == false) {
                cout << "not found" << endl;
            }

        }


};
int main() {
    linkedList a;
    bool isExit = false;
    string text;
    int lineNumb;
    int command;
    int loopCounter = 0;

    while (isExit != true){
        cout << "\n";
        cout << "type the number of a command" << endl;
        cout << "1. insertEnd" << endl << "2. insert" << endl << "3. delete" << endl << "4. edit" << endl;
        cout << "5. print" << endl << "6. search" << endl << "7. quit" << endl;
        //if(loopCounter > 0) {
          //  cin.clear();
            //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //}
        cin >> command;
        loopCounter++;
        if(command == 1){
            cout << "Type what you'd like to insertEnd" << endl;
            cin.ignore();
            std::getline(std::cin, text);
            a.insertEnd(text);
        }
        else if(command == 2){
            cout << "Type what you'd like to insert" << endl;
            cin.ignore();
            std::getline(std::cin, text);
            cout << "Type which line number you'd like to insert at" << endl;
            cin >> lineNumb;
            a.insert(lineNumb,text);
        }
        else if(command == 3){
            cout << "Type which line number you'd like to delete" << endl;
            cin >> lineNumb;
            a.deleteNode(lineNumb);
        }
        else if(command == 4){
            cout << "Type the text that you wish to swap in" << endl;
            cin.ignore();
            std::getline(std::cin, text);
            cout << "Type which line number you'd like to edit" << endl;
            cin >> lineNumb;
            a.edit(lineNumb,text);
        }
        else if(command == 5){
            a.print();
        }
        else if(command == 6){
            cout << "Type the text that you wish to search for" << endl;
            cin.ignore();
            std::getline(std::cin, text);
            a.search(text);
        }
        else if(command == 7){
            isExit = true;
        }
        else{
            cout << "Command not recognized" << endl;
        }
    }
    return 0;
}