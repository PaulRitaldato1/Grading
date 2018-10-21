#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Node {
    public:
        string value;
        Node* next = NULL;
        Node* prev = NULL;
};

class List
{  
    private:
        int size;
        Node *head;
        Node *tail;
    
    public:
        List()
        {
            init();
        }
    
    void init()
    {
	size = 0;
        head = new Node;
        tail = new Node;
        head = NULL;
        tail = NULL;
    }
     
    void insertEnd(string textToAdd)
    {
        Node *addNode = new Node;
        addNode->value = textToAdd;
        
        if(head == NULL){
            head=addNode;
        } else if(tail == NULL){
            tail=addNode;
            tail->prev=head;
            head->next=tail;
        } else{
            addNode->prev=tail;
            tail->next=addNode;
            tail=addNode;
        }
        size++;
    }
    
    void insert(int index, string textToAdd)
    {
        //check if input valid
        if(index < 1 || index > size+1){
            return;
        } else if (index == size+1){ //if index to insert is actually at end of it then just use insertEnd function
            insertEnd(textToAdd);
            return;
        }
        Node *currNode = head;
        Node *addNode = new Node;
        addNode->value = textToAdd;
        index--;

        if(index==0){
            addNode->next=head;
            head->prev=addNode;
            head=addNode;
        } else{
            int i = 1;
            while(i < index){
                currNode=currNode->next;
                i++;
            }

            Node *nextNode = currNode->next;
            currNode->next=addNode;
            addNode->prev=currNode;
            addNode->next=nextNode;
            nextNode->prev=addNode;
        }
        size++;
    }
    
    void edit(int index, string editText){
        //check input valid
        if(index < 1 || index > size){
            return;
        }
        index--;
        Node *currNode = head;
        int i = 1;
        while(i <= index){
            currNode=currNode->next;
            i++;
        }
        currNode->value=editText;
    }
    
    void search(string toFind){
        bool found = false;
        Node *currNode = head;
        int index = 1;
        
        while( currNode != NULL ){
            string currString=currNode->value;
            if(currString.find(toFind) != string::npos){
                cout << index;
                cout << " ";
                cout << currString << endl;
                found=true;
            }
            currNode=currNode->next;
            index++;
        }
        
        if(!found){
            cout << "not found" << endl;
        }
    }
    
    void delete_this(int index){
        //check input valid
        if(index < 1 || index > size){
            return;
        }
        Node *currNode = head;
        index--;
        int i = 1;
        
        //if the index to delete is the head
        if(index == 0){
            Node *tempNode = new Node;
            head=head->next;
            head->prev=NULL;
            delete tempNode;
        } else {
            while(i <= index){
                currNode=currNode->next;
                i++;
            }
            //if index turns out to be the tail
            if(currNode->next==NULL){
                tail=currNode->prev;
                tail->next=NULL;
                currNode=NULL;
                delete currNode;
            } else { //if the node is inbetween two nodes
                Node *before = new Node;
                Node *after = new Node;
                before=currNode->prev;
                after=currNode->next;
                before->next=after;
                after->prev=before;
                currNode=NULL;
                delete currNode;
            }
        }
        size--;
    }
    
    void print()
    {
        int index=1;
        Node *currNode = head;
        while( currNode != NULL ){
            cout << index;
            cout << " ";
            cout << currNode->value << endl;
            currNode=currNode->next;
            index++;
        }
    }
};

string parseVector(vector<std::string> result){
    string text="";
    for (vector<string>::iterator t=result.begin(); t!=result.end(); ++t) 
    {
        text+=*t;
        text+=" ";
    }
    text=text.substr(text.find_first_of('"')+1,text.find_last_of('"')-1);
    return text;
}

int main() {
    List myList;

    while(true) {
        string input;
        vector<std::string> result;
        getline(cin,input);
        istringstream iss(input);
        for(std::string s; iss >> s; )
            result.push_back(s);
           
        if(result[0] == "quit"){
            break;
        } else if(result[0].find("insertEnd") != string::npos){
            result.erase(result.begin());   
            string text = parseVector(result);
            myList.insertEnd(text);
        } else if(result[0].find("insert") != string::npos){ 
            stringstream ss(result[1]);
            int index;
            ss >> index;
            result.erase(result.begin());
            result.erase(result.begin());
            string text = parseVector(result);
            myList.insert(index,text);
        } else if(result[0].find("delete") != string::npos){
            stringstream ss(result[1]);
            int index;
            ss >> index;
            result.erase(result.begin());
            result.erase(result.begin());
            myList.delete_this(index);
        } else if(result[0].find("edit") != string::npos){
            stringstream ss(result[1]);
            int index;
            ss >> index;
            result.erase(result.begin());
            result.erase(result.begin());
            string text = parseVector(result);
            myList.edit(index,text);
        } else if(result[0].find("search") != string::npos){
            result.erase(result.begin());
            string text = parseVector(result);
            myList.search(text);
        } else if(result[0].find("print") != string::npos){
           myList.print();
        } else {
        
        }
    }
}
