#include <iostream>
using namespace std;
class LinkedList{
private:
    struct node{
        string line;
        node *next;
    };
    node *head;
    node *tail;
public:
    LinkedList(){
        head=NULL;
        tail=NULL;
    }
    //confusion over what do if line is over 80 char for insertEnd, insert, and edit.
    //my last submission had it so it would add first 80, move to next line and add next 80 and so forth.
    //professor resch then said in slack to cut the text after 80 char so that we only use the first 80 char
    //this is what i have done in this submission so that it simply only uses the first 80 char if it's over 80
    void insertEnd(string text){
        if(text.length()>80)
            text=text.substr(0,80);
        node *add=new node;
        add->line=text;
        add->next=NULL;
        if(head==NULL)
            head=add;
        else
            tail->next=add;
        tail=add;
    }
    void insert(int lineNum, string text){
        if(text.length()>80)
            text=text.substr(0,80);
        node *add=new node;
        add->line=text;
        if(lineNum<=checkLines()+1&&lineNum>=1) {
            int count = 1;
            node *current = head;
            if (lineNum == 1) {
                add->next = head;
                head = add;
                if(tail==NULL)
                    tail=add;
            } else {
                while (count != lineNum - 1) {
                    current = current->next;
                    count++;
                }
                if(current==tail)
                    tail=add;
                add->next = current->next;
                current->next = add;
            }
        }
    }
    void deleteLine(int lineNum){
        if(lineNum<=checkLines()&&lineNum>=1) {
            if(lineNum==1){
                if(tail==head)
                    tail=NULL;
                head=head->next;
            }
            else {
                int count = 1;
                node *current = head;
                while (count != lineNum - 1) {
                    current = current->next;
                    count++;
                }
                if(current->next==tail)
                    tail=current;
                current->next = current->next->next;
            }
        }
    }
    void edit(int lineNum,string text){
        if(text.length()>80)
            text=text.substr(0,80);
        if(lineNum<=checkLines()&&lineNum>=1) {
            if(lineNum==1){
                node *add = new node;
                add->line = text;
                add->next = head->next;
                if(head==tail)
                    tail=add;
                head = add;
            }
            else {
                int count = 1;
                node *current = head;
                while (count != lineNum - 1) {
                    current = current->next;
                    count++;
                }
                node *add = new node;
                add->line = text;
                add->next = current->next->next;
                if(current->next==tail)
                    tail=add;
                current->next = add;
            }
        }
    }
    void print(){
        if(head!=NULL) {
            node *current = head;
            int count = 1;
            while (current != tail) {
                cout << count << " " << current->line << endl;
                current = current->next;
                count++;
            }
            cout << count << " " << current->line << endl;
        }
    }
    void search(string text){
        int count=1;
        bool found=false;
        node *current=head;
        while(current!=tail){
            if(current->line.find(text)!=-1) {
                cout << count << " " << current->line << endl;
                found=true;
            }
            current=current->next;
            count++;
        }
        if(current!=NULL&&current->line.find(text)!=-1) {
            cout << count << " " << current->line << endl;
            found=true;
        }
        if(!found)
            cout<<"not found"<<endl;
    }
    int checkLines(){
        node *current=head;
        int count=1;
        if(head==NULL)
            count=0;
        else if(head!=tail){
            while(current!=tail){
                count++;
                current=current->next;
            }
        }
        return count;
    }
};
int main() {
    LinkedList gg;
    string command;
    getline(cin,command);
    string first=command.substr(0,command.find(" "));
    while(first!="quit"){
        if(first=="insertEnd"){
            string text=command.substr(command.find("\"")+1,command.length()-(command.find("\"")+2));
            gg.insertEnd(text);
        }
        if(first=="insert"){
            command=command.substr(7);
            string num="";
            while(isdigit(command[0])){
                num+=command[0];
                command=command.substr(1);
            }
            int lineNum=stoi(num);
            string text=command.substr(command.find("\"")+1,command.length()-(command.find("\"")+2));
            gg.insert(lineNum,text);
        }
        if(first=="delete"){
            int lineNum=stoi(command.substr(command.find("delete")+7));
            gg.deleteLine(lineNum);
        }
        if(first=="edit"){
            command=command.substr(5);
            string num="";
            while(isdigit(command[0])){
                num+=command[0];
                command=command.substr(1);
            }
            int lineNum=stoi(num);
            string text=command.substr(2,command.length()-(command.find("\"")+2));
            gg.edit(lineNum,text);
        }
        if(first=="print") {
            gg.print();
        }
        if(first=="search"){
            string text=command.substr(8,command.length()-(command.find("\"")+2));
            gg.search(text);
        }
        getline(cin,command);
        first=command.substr(0,command.find(" "));
    }
    return 0;
}