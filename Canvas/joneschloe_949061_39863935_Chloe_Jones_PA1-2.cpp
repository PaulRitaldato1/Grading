#include <iostream>
#include <string>
#include <sstream> 

/*
 Chloe Jones
 Programming Assignment #1 for COP3530

 Purpose of assignment: to create a line editor using a LinkedList implementation

 Must haves:

 insertEnd "text"  -- insert given text at the end of the document 

insert 3 "text" --insert given text at the line indicated by index given reg insert()

delete 3 --- delete line at index given 

edit 3 "text" --- replace the line at the index given with the given text (std::string::str.replace(begin, end, str2)

print -- print the entire document, with line numbers 

search "text" -- print the line number and line that contains the given text.  print "not found" if it is not found
//the find thing 

quit - quit/exit the program, quit()
*/

//the h file, for the classies
//#include "PA1.h"


//Node class, put const on 80 chars, have string 

struct Node
{   
    public:
        const int size = 80;
        int line = 0;
        int count;
        Node* next;
        std::string text;
        Node();
        ~Node();
};

/*Linked List
My weird plan is to only use the head node as a bookmark, rather than as a doc line.
It won't be printed, but this should make things easier for me logic wise.
*/

class LinkedList
{      
    private:
        Node* head;
    public:
       void init();
       LinkedList();
       Node* getHead();
       ~LinkedList();
    
};

class UserComm
{
    private:
        int x;
        std::string c;
        std::string n;
        bool run;

    public:
        void input(LinkedList *l);
        Node* insertEnd(std::string s,int c, Node* head); //inserts line at end
        Node* insert(std::string s, int x, Node* head); //inserts a line 
        Node* del(int x, Node* head); //deletes a line
        Node* edit(std::string s, int x, Node* head); //replaces a line with another
        void print(Node* head); //print doc
        void search(std::string s, Node* head); //prints # and line at given point
        void q(LinkedList *l); //quiting/looping purposes
        int numGrab(std::string s); //convert substring to integer
        std::string textGrab(std::string s); //grab text to be done something with
        UserComm();
        ~UserComm();
};

//constructors/deconstructors, I feel like these should be here, just to clarify what happens when an obj is created
UserComm::UserComm(){
}

UserComm::~UserComm(){}

Node::Node(){}

Node::~Node(){}

LinkedList::LinkedList(){
    init();
}

LinkedList::~LinkedList(){}

//creation of the head/tail nodes
void LinkedList::init(){
        head = new Node;
        head->next = nullptr;
}

//I feel like theres a better way to do this since these are pointers, but it allows UserComm access directly

Node* LinkedList::getHead(){
    return head;
}

void UserComm::input(LinkedList *l){
    std::string in;
    //std::cout << "What would you like to do? You can insertEnd, insert, delete, edit, print, search or quit!"<< "\n";
    std::getline(std::cin, in);
    //put these into variables to make things a little neater
    //int num = numGrab(in); messes with insertEnd
    std::string text = textGrab(in);
    int c = text.size();
    //end important variables
    //found find() on Stack overflow https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
    //wished I could have used a switch statement
     if(in.find("End") != std::string::npos){ //goes to insertEnd method
         insertEnd(text, c, l->getHead()); //accessing head/tail like this to make sure the right one is being used
     }
     else if(in.find("quit") != std::string::npos){ //Quit.
        run = false;
     }
      else if(in.find("insert") != std::string::npos && !(in.find("End") != std::string::npos)){
          insert(text, numGrab(in), l->getHead());
     }
     else if(in.find("delete") != std::string::npos){
          del(numGrab(in), l->getHead());
     }
      else if(in.find("search") != std::string::npos){
        search(text, l->getHead());
     }
      else if(in.find("print") != std::string::npos){ //just a reg print 
          print(l->getHead());
     }
     else if(in.find("edit") != std::string::npos){ //just a reg print 
          edit(text, numGrab(in), l->getHead());
     }
     else {
         //std::cout << "Not proper, please try again" << "\n";
         q(l);
     }
}

//inserts line at end
 Node* UserComm::insertEnd(std::string s, int c, Node* head){
    // std::cout << "running End" << "\n";
     /*
        cases:
        1.No other text, put inbetween head and tail.
        2. If other text present, make it the next to tail prev, make it's next tail.
     */
    //can just do the text/count field assignments here
    Node* n = new Node;
    n->text = s;
    n->count = c;
    if(c <= n->size){ //check for text size
        if(head->next == nullptr){ //first case
            head->next = n;
            n->next = nullptr;
            n->line++;
        }
        //the second case, make sure to handle lines
        else {
            Node* curr = new Node;
            curr = head;
            while(curr->next != nullptr) {
            curr=curr->next;
        }
        curr->next = n;
        n->next = nullptr;
        n->line = curr->line;
        n->line++;
        //std::cout << n->text << " " << n->line << "\n";
        } //must add a return to home base kind of thing here, or just quit
    }
    else {std::cout << "Text is too large" << "\n";}
    return head;
    }

    Node* UserComm::insert(std::string s, int x, Node* head){ //inserts a line 
        //cases : insert at 1, middle, and end
        //std::cout << "running insert" << "\n";
        int e = 0;
        Node* curr = new Node;
        Node* n = new Node;
        n->text = s;
        n->line = x;
        curr = head;
        if(s.size() < n->size && x > 0){
            while(curr != nullptr){
                //first, head without other nodes
                if(head->next == nullptr && x == 1){
                    head->next = n;
                    n->next = nullptr;
                    break;
                }
                //second, head with other nodes
                else if(head->next != nullptr && x == 1){
                    n->next = head->next;
                    head->next = n;
                    curr = curr->next; //curr is at n
                    while(curr->next != nullptr){
                        curr->next->line++;
                        curr = curr->next;
                    }
                    break;
                }
                else if(curr->next == nullptr && curr->line == x-1){
                    curr->next = n;
                    n->next = nullptr;
                    break;
                }
                else if(curr->next == nullptr && curr->line +2 <= x){ //catch out of range 
                    e = 1;
                    break;
                }
                    //  in the middle somewhere
                else if(curr != head && curr->next->line == x){
                    n->next = curr->next;
                    curr->next = n;
                    curr = curr->next->next; //curr is at the one after n
                    while(curr != nullptr){
                        curr->line++;
                        curr = curr->next;
                    }
                    break;
                }
                else{
                    curr = curr->next;
                }
            }
            if(e == 0){ //return head without issue
            return head;
            }
            else{ //tell user they entered an errant line number
                //std::cout << "No such line found" << "\n";
                return head;
            }
        }
       // else{
       //     std::cout << "Input error! " << "\n"; //for all other cases
        //}
    }

    Node* UserComm::del(int x, Node* head) {//deletes a line
        //cycle through lines of nodes
        //cases:beginning, middle and end, breaks if it finds node and deletes it
        Node* curr = new Node;
        curr = head;
        //only runs if there is at least one node
        while(curr != nullptr && head->next != nullptr){
            //for any node in the middle, where the second node isnt a nullptr
             if(curr->next == nullptr && curr->line < x){
                break;
            }
            else if(curr->next->line == x && curr->next->next != nullptr){
                curr->next = curr->next->next;
                while(curr->next != nullptr){
                    curr->next->line--;
                    curr = curr->next;
                }
                break;
            }//if the node being deleted is the first one, and there are others behind it
            else if(head->next->line == x && head->next->next != nullptr){
                head->next = head->next->next;
                while(curr->next != nullptr){
                    curr->next->line--;
                    curr = curr->next;
                }
                break;
            }
            //if there is only one node, and that node is being deleted
             else if(head->next->line == x && head->next->next == nullptr){
                head->next = nullptr;
                break;
            
            }//if there are mult nodes and the last one is being deleted
            else if(curr->next->next == nullptr && curr->next->line == x){
                curr->next = nullptr;
                break;
            }
           
            else{
            curr = curr->next;
            }
        }
        return head;
    }

    void UserComm::search(std::string s, Node* head){ //prints # and line at given point
        Node* curr = new Node;
        curr = head;
        int count = 0;
        while(curr != nullptr){
            if(curr->text.find(s) != std::string::npos){ 
                std::cout << curr->line << " " << curr->text << "\n";
                count++;
            }
                curr = curr->next;
            }   
        if(count == 0){
            std::cout << "not found" << "\n";
        }
    } 

    Node* UserComm::edit(std::string s, int x, Node* head){ //replaces a line with another
        Node* curr = new Node;
        curr = head;
        //std::cout << "edit method go" << "\n";
        if(s.size() <= curr->size){
            while(curr != nullptr){
                if(curr->line == x){
                    curr->text = s;
                   // std::cout << "replaced" << "\n";
                    break;
                }
                else {
                    curr=curr->next;
                    //std::cout << "going" << "\n";
                }
            }
        }
        //std::cout << "done" << "\n";
        return head;

    }

//print out list, skip over printing head and tail, since theyre only bookmarks
 void UserComm::print(Node* head){
     Node* curr = new Node;
     curr = head->next;
     while(curr != nullptr){
         //std::cout << "printing" << "\n";
         std::cout << curr->line << " " <<  curr->text << "\n";
         curr = curr->next;
     }
    // std::cout << "out of while" << "\n";
 }

//looked up stringstream on geeksforgeeks

int UserComm::numGrab(std::string s){
    int x = 0;
    std::string temmie;
    /*got iterator code from stack overflow, I really like it, I think Ill use a char iterator like this when 
    I parse out the text as well */
     for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        if (isdigit(*it)){ 
            temmie.push_back(*it);
        }
    }
    //std::cout << s << "\n";
    //std::cout << temmie << "\n";
    if(!temmie.empty()){
        std::stringstream go(temmie); 
        go >> x;
        //std::cout << x << "\n";
        return x;
    }
    //if insert came with no location
  //  else {
   //     std::cout << "No number provided" << "\n";
   // }
}

std::string UserComm::textGrab(std::string s){ //grab text to be done something with
    std::string innie;
    int count = 0;
    for(std::string::iterator it = s.begin(); it != s.end(); ++it){ //used same iterator from numGrab(), I am in love
        //plan is to push all text within quotation marks to a separate string
        if(*it == '\"'){
            count++;     
        }
        else if(count > 0 && count < 2){  //continue to push until second mark
                innie.push_back(*it);
            }
       else continue;
    }
    //std::cout << innie << "\n"; 
    return innie;
} 

void UserComm::q(LinkedList *l){ //passing in objs was my solution to get the gethead/getTail methods
    run = true;
    while(run){
        input(l); 
    }
}


int main()
{
    LinkedList l;
    UserComm c;
    c.q(&l);
   // l.~LinkedList();
    
}