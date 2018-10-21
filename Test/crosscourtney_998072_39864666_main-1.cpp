#include <iostream>
using namespace std;

//implement linked list

class LinkedList{
    public:
struct node{
    string line;
    int lineNum;
    node *next = nullptr;
};
private:
    node *head;
public:
    LinkedList(){
        head =NULL;
    }

void insertEnd(string quote, int count);
void insertInd(int index, string quote, int count);
void deleteLine(int index, int count);
void edit(int index, string quote);
void print();
void search(string quote);
string findQuotes(string command);

};


void LinkedList::insertEnd(string quote, int count){

    if(head==NULL){
        head = new node();
        node *temp = head;
        head->line=quote;
        head->lineNum=count;
    }
    else{
        node * curNode = head;

        while(curNode->next!=NULL){
            curNode = curNode->next;
        }

        node *temp = new node;
        temp->line = quote;
        temp->lineNum=count;
        curNode->next = temp;
    }


}

void LinkedList::insertInd(int index, string quote, int count){


    node * curNode = head;
    node *temp = new node;

    while(curNode!=NULL){
        if(curNode->lineNum==index-1) {

            temp->line = quote;
            temp->lineNum=index;
            node* nextTemp= curNode->next;

            curNode->next = temp;
            temp->next = nextTemp;
            break;
        }
        else{
            curNode = curNode->next;
        }
    }



    while(temp->next!=NULL){
        temp->next->lineNum++;
        temp=temp->next;
    }

}

void LinkedList::deleteLine(int index, int count){
    node * curNode = head;
    node *temp = new node;


    if(index<=count) {
        while (curNode != NULL) {
            if(index==1){
                curNode=NULL;
                free(curNode);
            }
            if (curNode->next->lineNum == index) {
                if (curNode->next->next != NULL) {
                    temp = curNode->next;
                    curNode->next = curNode->next->next;

                    delete (temp);

                    break;
                } else {
                    curNode->next = NULL;
                    free(curNode->next);
                    break;

                }
            } else {
                curNode = curNode->next;
            }
        }


        while (temp->next != NULL) {
            temp->next->lineNum--;
            temp = temp->next;
        }
    }

}

void LinkedList::edit(int index, string quote){
        node* temp = head;
    while(temp!=NULL){
        if(temp->lineNum==index){
            temp->line=quote;
        }
        temp=temp->next;
    }

}

void LinkedList::print(){
    node* temp = head;
    while(temp!=NULL){
            cout<<temp->lineNum;
            cout<<" ";
            cout<<temp->line;
            temp = temp->next;
            cout<<endl;

    }
}

void LinkedList::search(string quote){
     node* temp = head;

    bool found = false;
    while(temp!=NULL){

        size_t present = temp->line.find(quote);
    if(present!=string::npos) {
        found=true;
        cout<<temp->lineNum;
        cout<<" ";
        cout<<temp->line<<endl;

    }

        temp = temp->next;
    }

    if(!found){
        cout<<"not found"<<endl;
    }
}


string LinkedList::findQuotes(string command){
    int start = command.find("\"");
    int end = command.find("\"", start+1);
    string quote = command.substr(start+1, end);
    quote.pop_back();
    return quote;
}


int main(){
    string command;

    LinkedList* document = new LinkedList;
    int count=0;

    while(getline(cin, command)){

        string quote ="";


        string option = command.substr(0,command.find(' '));
        int index;
        quote=document->findQuotes(command);

        if(option.compare("insertEnd")==0){
            count++;
            document->insertEnd(quote, count);
        }
        else if(option.compare("insert")==0){
            count++;
            string number = command.substr(command.find(' ')+1, command.find("\""));
            index=stoi(number);
            document->insertInd(index, quote, count);
        }
        else if(option.compare("delete")==0){
            string number = command.substr(command.find(' ')+1);
            index=stoi(number);
            document->deleteLine(index, count);
            count--;
        }
        else if(option.compare("edit")==0){
            string number = command.substr(command.find(' ')+1, command.find("\""));
            index=stoi(number);
            document->edit(index, quote);
        }
        else if(option.compare("print")==0){
            document->print();
        }
        else if(option.compare("search")==0){
            document->search(quote);
        }
        else if(option.compare("quit")==0){
            return 0;
        }

    }

}