#include <cstdlib>
#include <iostream>
#include <string> 


using namespace std;

bool is_number(const std::string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

typedef struct node{
    string data;
    node* next;

}* nodePtr;

class List{
    
    private:
        nodePtr head;
        nodePtr tail;
        nodePtr curr;
        nodePtr temp;
        
        int length; 


    public:
    List(){
        head = NULL;
        tail = NULL;
        curr = NULL;
        temp = NULL;
        length = 0;
    }

    //add a node a given index
    void addNode(int index, const string addData){
        if(index <= length+1 && index > 0){
            length += 1;
            node* addNode = new node();
            addNode->data = addData;
            if(index == 1){
                if(head == NULL){
                    addNode->next = head;
                    head = addNode;
                    tail = head;
                }
                else{
                    addNode->next = head;
                    head = addNode;
                }
                
            }
            else{
                node* currNode;
                currNode = head;
                for(int i = 2; i<index; i++){
                    currNode = currNode->next;
                }
                addNode->next = currNode->next;
                currNode->next = addNode;
                if(addNode->next == NULL){
                    tail = addNode;
                }
            }
        }
    }

    //add node at the end of the linked list
    void addNodeEnd(const string addData){
        length += 1; 
        node* addNode = new node();
        addNode->data = addData;
        if(head == NULL){
            head = addNode;
            tail = addNode;
        }
        else{
            tail->next = addNode;
            tail = addNode;
        }
    }
    
    //deletes the node at a given index
    void deleteNode(int index){
        node* currNode;
        node* nNode;
        currNode = head;
        if(head != NULL){
            if(index == 1){
                head = head->next;
            }   
            else{
                for(int i = 2; i < index; i++){
                    currNode = currNode->next;
                }
                if(!(currNode->next == NULL)){
                    nNode = currNode->next;
                    currNode->next = nNode->next;
                    if(currNode->next == NULL){
                        tail = currNode;
                    }
                }
            }
        }
    }
    

    //prints the data of each node in the linked
    void printList(){
        node* currNode;
        currNode = head; 
        int number = 1;
        while(currNode != NULL){
            cout<<to_string(number) +  currNode->data<<endl;
            currNode = currNode->next;
            number++;
        }      
    }

    //prints a specific comment from the linked list
    void findEntry(string myString){
        node* currNode;
        currNode = head; 
        int i = 1;
        bool found = false;
        while(currNode != NULL){
            if (currNode->data.find(myString) != string::npos) {
                cout<< to_string(i) + currNode->data<<endl;
                found = true;
            }
            currNode = currNode->next;
            i++;
        }
        if(!found){
            cout<<"not found"<<endl;
        }
        
        
        
    }
    
    
};
 
/*function to process strings (comments) so they do not include the 
quotation marks given with the command*/
 string processString(string myString){
        for(string::iterator it=myString.begin(); it!=myString.end(); it++){
        
            if(*it == '"'){
                myString.erase(it);
                break;
            }
        }
        for(string::iterator it=myString.end(); it!=myString.begin(); it--){
            if(*it == '"'){
                myString.erase(it);
                break;
            }
        }
        return myString;
}

//Takes in user command and calls appropriate functions
void promptUser(List myList){
    
    string command;
    string firstInput;
    string secondInput;
    while(command.compare("quit")!=0){
        cin>>command;
        
        if(command.compare("delete")==0){
            cin>>firstInput;
            if(is_number(firstInput)){
                myList.deleteNode(stoi(firstInput));
            }
        }
        else if(command.compare("insert")==0){
            cin>>firstInput;
            if(is_number(firstInput)){
                getline(cin, secondInput);
                secondInput = processString(secondInput);
                if(secondInput.length() <= 81){
                    myList.addNode(stoi(firstInput), secondInput);
                }
    
            }
                   
        }
        else if(command.compare("print")==0){ 
            myList.printList();
        }
        else if(command.compare("insertEnd")==0){
            getline(cin, secondInput);
                secondInput = processString(secondInput);
                if(secondInput.length() <= 81){
                    myList.addNodeEnd(secondInput);
                }
        }
        else if(command.compare("edit")==0){
            cin>>firstInput;
            if(is_number(firstInput)){
                getline(cin, secondInput);
                secondInput = processString(secondInput);
                if(secondInput.length() <= 81){
                    myList.deleteNode(stoi(firstInput));
                    myList.addNode(stoi(firstInput), secondInput);
                }
            }
        }
        else if(command.compare("search")==0){
            getline(cin, firstInput);
            firstInput = processString(firstInput);
            myList.findEntry(firstInput);

        }
        else{
        }
    }
}

int main(){
    List myList;
    promptUser(myList);
    
    
    return 1;
}