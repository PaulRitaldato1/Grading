#include <iostream>
#include <string>

//your linked list implementation here
struct Node{                        //Node struct
    std:: string value;
    struct Node* next = NULL;
    
};
class LinkedList{                    //LinkedListClass
    private:
    Node* head;
    Node* tail;
    public:
    LinkedList(){
        head=NULL;
        tail=NULL;
    }
     void insertAtEnd(std::string newLine){                //inserts at end of list
        Node* temp= new Node;
        temp->value= newLine;
        temp->next=NULL;                            //creates new node to insert at end
        
        if(head==NULL){        //case when list is empty
            head=temp;
            tail=temp;
              
        }
        else{
            tail->next=temp;            //adds node behind tail
            tail=temp;            //makes new node tail
        }
    };
    void insertLineAt(int index, std::string newLine){
        Node* temp = new Node;
        Node* previous = head;
         temp->value= newLine;
            temp->next = head;                //makes new node that points to head
        if(index==1){
           
            head = temp;                //case where you want to insert at front of list
        }
        else{
           for(int i = 2; i<index; i++){        //iterates to index before desired
              previous=previous->next; 
               if(previous==NULL){            //if insert at index out of bounds of list
                   return;
               }
           }
            temp->next=previous->next;        //points new node to the next node
            previous->next=temp;                //points previous node to new node
            if(temp->next==NULL){
             tail=temp;                       //if insert at end of list make new node tail
            }
        } 
    }
    void deleteLineAt(int index){
        Node* temp = head;
        Node* previous=head;                
        if(index==1){                    //when deleting head
            head=head->next;
            delete(temp);
            return;
        }
        temp=temp->next;
        for(int i=1; i<index-1;i++){        //iterates to desired index
            previous=temp;
            temp=temp->next;
            if(temp==NULL){                //if desired index is out of bounds
                return;
            }
        }
        previous->next=temp->next;
        temp->next=NULL;                //deletes node and reassigns pointers
        delete(temp);
        
    }
    void print(){                        //prints list
        Node* temp= head;
        int lineNumber = 1;
        while(temp !=NULL){
            std:: cout<<lineNumber<<" "<<temp->value<<"\n";
            temp=temp->next;
            lineNumber++;     
        }
    }
    void editLine(int index, std::string newLine){
        Node* temp = head;
        for(int i=1; i<index;i++){            //iterates to desired line
         temp=temp->next; 
            if(temp==NULL){            //if index is out of bounds
                return;
            }
        }
        temp->value=newLine;        //assigns to value to node
    } 
    void findLine(std::string line){        
        Node* temp =head;
        std::string currentLine;
        int lineNumber=1;                
        bool found =false;        //whether string is found or not
        while(temp != NULL){            //goes through entire list
            for(int i=0; i<=temp->value.length()-line.length();i++){     //goes through current string and compares
                currentLine=temp->value.substr(i,line.length());         //each substring of equal length to the
               if(line.compare(currentLine)==0){                            //string being searched 
               std:: cout<<lineNumber<<" "<<temp->value<<"\n";
               found=true;
               break;
               }
            }
            lineNumber++;            
            temp=temp->next;
            
        }
        if (!found){                            //if text is not found in list
        std::cout<<"not found\n";
        }
    }
 
};


int main()
{
    LinkedList myLinkedList = LinkedList();
    bool run = true;
    std::string commandLine;
    std::string text1;
    std::string text2;
    std::string text3;
    std::size_t found;
    int index =0;
    
    while(std::getline(std::cin, commandLine)){        //runs until no input left
        found=commandLine.find(' ');                //finds index of first space in string
        if(found ==std::string::npos){                //if the space does not exist i.e. for print and quit
            if(commandLine.compare("print")==0){
              myLinkedList.print();   
            }
            else if(commandLine.compare("quit")==0){
            exit(0);
            }
            else{                                        //if there is no space input has to be print or quit
                std::cout<<"not valid user input\n";
                    exit(0);
            }
        }
        else{                                        //if space does exist in string
           text1=commandLine.substr(0,found);            //substring up to space but not including it
            if(text1.compare("insertEnd")==0){
             text2=commandLine.substr(found+1);            //substring from space index plus 1 to end of string
                text2=text2.substr(1, text2.length()-2);        //gets rid of quotes
                myLinkedList.insertAtEnd(text2);    
            }
            else if(text1.compare("search")==0){
                text2=commandLine.substr(found+1);            //substring from space index plus 1 to end of string
                text2=text2.substr(1, text2.length()-2);        //gets rid of quotes
                myLinkedList.findLine(text2);
            }
            else{
               text2=commandLine.substr(found+1,1);        //takes in line number
                index=atoi(text2.c_str());                //converts line number to int
                if(text1.compare("delete")==0){            
                 myLinkedList.deleteLineAt(index); 
                }
                else if(text1.compare("insert")==0){
                    text3=commandLine.substr(found+3);        //gets text with quotes
                    text3=text3.substr(1,text3.length()-2);        //gets rid of quotes
                    myLinkedList.insertLineAt(index,text3);
                }
                else if(text1.compare("edit")==0){
                    text3=commandLine.substr(found+3);            //gets text with quotes
                    text3=text3.substr(1,text3.length()-2);        //gets rid of quotes
                    myLinkedList.editLine(index,text3);
                }
            }
        }
            
      
    }
           
    
   
    
    //your code to invoke line editor here
}