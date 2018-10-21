#include <iostream>
#include <string>
using namespace std;

class Node{
    private:
        string line;
        int number;
        Node* next;
    public:
        Node(string l, int num,Node* n) {
            line = l;
            number = num;
            next = n;
        }
        string getLine(){return line;}
        int getNumber(){return number;}
        Node* getNext(){return next;}
        string setLine(string l){line=l;}
        int setNumber(int num){number=num;}
        Node* setNext(Node* n){next=n;}
        void print(){
            cout<<number<<" "<<line<<endl;
        }
};
class LinkedList{
    private:
        Node* head;
        int size;
    public:
        LinkedList(Node* h){
            head=h;
            size=1;
        }
        LinkedList(){
            head=NULL;
            size=0;
        }
        int getSize(){return size;}
        void insertEnd(string line){
            Node* n=new Node(line,-1,NULL);
            if(head==NULL){
                head=n;
                n->setNumber(1);
                size++;
                return;
            }
            Node* curr=head;
            while(curr->getNext()!=NULL){
                curr=curr->getNext();
            }
            n->setNumber(curr->getNumber()+1);
            curr->setNext(n);
            size++;

        }
        void insert(int num, string line){
            if(num>size+1||num<1){
                //cout<<"INVALID INPUT: OUT OF BOUNDS"<<endl;
                return;
            }
            if(num==size+1){

                insertEnd(line);
                return;
            }
            if(num==1){
                size++;
                Node* temp=head;
                head=new Node(line,num,temp);
                return;
            }
            size++;
            Node* curr=head;
            while(curr->getNext()->getNumber()!=num){
                curr=curr->getNext();
            }
            Node* temp=curr->getNext();
            Node* add=new Node(line,num,temp);
            curr->setNext(add);
            while(temp->getNext()!=NULL){
                temp->setNumber(temp->getNumber()+1);
                temp=temp->getNext();
            }
            temp->setNumber(temp->getNumber()+1);
        }
        void deleteNum(int num){

            if(num>size||num<1){
                //cout<<"INVALID INPUT: OUT OF BOUNDS"<<endl;
                return;
            }

            if(num==1){
                head=head->getNext();
                Node* temp=head;
                while(temp->getNext()!=NULL){
                    temp->setNumber(temp->getNumber()+1);
                    temp=temp->getNext();
                }
                temp->setNumber(temp->getNumber()+1);
                size--;
                return;
            }
            if(num==size){
                size--;
                Node* curr=head;
                while(curr->getNext()->getNumber()!=num) {
                    curr = curr->getNext();
                }


                curr->setNext(NULL);
                return;
            }
            Node* curr=head;
            while(curr->getNext()->getNumber()!=num){
                curr=curr->getNext();

            }
            curr->setNext(curr->getNext()->getNext());
            while(curr->getNext()!=NULL){
                curr->getNext()->setNumber(curr->getNext()->getNumber()-1);
                curr=curr->getNext();

            }
            size--;
            return;

        }
        void edit(int num,string line){
            if(num<1||num>size){
                //cout<<"INVALID INPUT: OUT OF BOUNDS"<<endl;
                return;
            }
            Node* curr=head;
            while(curr->getNumber()!=num){
                curr=curr->getNext();
            }
            curr->setLine(line);
        }
        void search(string line) {
            Node *curr = head;
            bool b=false;
            while (curr != NULL) {
                if(curr->getLine().find(line) != string::npos){
                    curr->print();
                    b=true;
                }
                curr = curr->getNext();
            }
            if (!b) {
                cout<<"not found"<<endl;
            }
            return;

        }
        void print(){
            Node *curr = head;
            while (curr != NULL) {
                curr->print();
                curr = curr->getNext();
            }
            return;
        }
};

int main() {
    LinkedList* list=new LinkedList();
    string input;
    cin>>input;
    while(input!="quit"){
        if(input=="insertEnd"){
            string line;
            cin>>line;
            while(line.find_last_of('"')!=line.length()-1){
                string add;
                cin>>add;
                line+=" "+add;
            }
            if(line.length()<83)
                list->insertEnd(line.substr(1,line.length()-2));
        }
        else if(input=="insert"){
            int index;
            cin>>index;
            string line;
            cin>>line;
            while(line.find_last_of('"')!=line.length()-1){
                string add;
                cin>>add;
                line+=" "+add;
            }
            if(line.length()<83)
                list->insert(index, line.substr(1,line.length()-2));
        }
        else if(input=="delete"){
            int index;
            cin>>index;
            list->deleteNum(index);
        }
        else if(input=="edit"){
            int index;
            cin>>index;
            string line;
            cin>>line;
            while(line.find_last_of('"')!=line.length()-1){
                string add;
                cin>>add;
                line+=" "+add;
            }
            if(line.length()<83)
                list->edit(index,line.substr(1,line.length()-2));
        }
        else if(input=="print"){
            list->print();
        }
        else if(input=="search") {
            string line;
            cin >> line;
            while (line.find_last_of('"') != line.length() - 1) {
                string add;
                cin >> add;
                line += " " + add;
            }
            if (line.length() < 83)
                list->search(line.substr(1, line.length() - 2));
        }
        cin>>input;

    }
    return 0;
}