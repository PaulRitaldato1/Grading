#include <iostream>
#include <sstream>


struct Node//create nodes in linked list
{
    std::string data;
    Node *next;//standard node values
};

Node *head = NULL;//global variable head used throughout oode, first node in linked list

Node* init(std::string);//declaring methods, this is initialize node method
void insertEnd(Node*,std::string);
void insert(Node*,std::string, int);
void delet(Node*, int);
void edit(Node*,std::string, int);
void print(Node*);
void search(Node*, std::string);


int main() {
    std::string input;//store input
    std::string value;//data stored in node
    std::stringstream s;//stringstream object to turn strings into integers
    std::string lineNumStr; //store linenumbers as a string from input
    int lineNum;//store linenumber as int

    while(input != "quit"){//loop until user types in quit
        getline(std::cin, input);//store user input

        if(input == "print")//check input
            print(head);//call method
        else if(input.substr(0,6) == "search"){
            value = input.substr(8);//remove "search" and first quote
            value.pop_back();//remove other quotation mark
            search(head,value);//call search method

        }
        else if(input.substr(0,9) == "insertEnd"){
            value = input.substr(11);//stores everything after" insertEnd ""
            value.pop_back();//remove quote
            insertEnd(head,value);
        }
        else if(input.substr(0,6) == "insert" && input.substr(6,1) == " "){
            int lengthNum = input.find(" ",7) - 7;//find index of space after number, starts search after first space, subtract 7(length of "insert ") from index to get length of number

            lineNumStr = input.substr(7,lengthNum);//store linenumber as string

            s<<lineNumStr;s>>lineNum;//convert string to int
            s.clear();//clear stringstream

            value = input.substr(9+lengthNum);//7(index after first space) + length of number + 2(for the space and first quotation mark
            value.pop_back();//remove second quotation mark
            insert(head,value,lineNum);//insert method

        }
        else if(input.substr(0,6) == "delete"){
            lineNumStr = input.substr(7); //save number from input

            s<<lineNumStr;
            s>>lineNum;
            s.clear();//conv string linenumber to int linenumber

            delet(head,lineNum);//delete node
        }
        else if(input.substr(0,4) == "edit"){
            int lengthNum = input.find(" ",5) - 5;//stores how many digits in number,saves everything in between first and second space
            lineNumStr = input.substr(5,lengthNum);//remove linenumber from input


            s<<lineNumStr;
            s>>lineNum;
            s.clear();//conv string num to int

            value = input.substr(7+lengthNum);//5(index where linenum starts) + lengthNum(# of digits in linenum) + 2(space and quote) = index where string to be added starts
            value.pop_back();//remove other quotation mark
            edit(head,value,lineNum);
        }


    }
    return 0;
}

Node* init(std::string value){//initialize node
    Node *n = new Node;//create node in memory
    n->data = value;//set string value to data of node
    n->next = NULL;//initialize next
    return(n);//return node just created
}

void insertEnd(Node* itr, std::string value){//insert end method
    Node *n ;//declare new node to be added
    n =init(value);//create node using input value string

    if(head==NULL)//if head doesn't exist then first item is being created
        head = n;//set head to new node
    else
    {
        while(itr->next!=NULL)//iterate until last value
            itr = itr->next;

        itr->next = n;//once reach end of list, add new node
    }


}

void insert(Node* itr,std::string value, int line){//insert specific line method
    Node *placeholder = NULL;//pointer holds value of node right before node to be added
    Node *n = init(value);//new node created

    for(int i=1;i < line; ++i){//loops until line number is reached
        placeholder = itr;//points to current node
        itr = itr->next;//points to next node
    }

    if(placeholder ==NULL){//node added to line 1, have to change head
        n->next = head;//new node next value now points to old head
        head = n;//head now points to new node
    }
    else{
        n->next = itr;//new node next value points to old node at that line
        placeholder->next=n;//line -1 node next value now points to new node
    }

}

void delet(Node *itr, int line){
    Node *d; //node to be deleted
    Node *placeholder = NULL;//hold place of node to be deleted

    for(int i = 1; i<line;++i){
        placeholder = itr;
        itr = itr->next;
    }

    if(placeholder == NULL){//user wants to delete first node
        head=head->next;//head now points to next node
        d=itr;//itr points to old head, node will get deleted
    }
    else{
        placeholder->next = itr->next;//links nodes in between element to be removed
        d = itr;//node to be deleted
    }
    delete d;
}

void edit(Node *itr, std::string value, int line ){
    for(int i =1; i < line; ++i)//iterate to line #
        itr = itr->next;//crawl down list
    itr->data =value;//replace data with new data
}

void print(Node *itr){
    if(itr==NULL) //head is empty, list is empty
        std::cout << "empty" << std::endl;

    else{
        int lineNum = 1; //keeps track of current line number
        while(itr){
            std::cout<<lineNum<<" "<<itr->data<<std::endl;
            itr=itr->next;//increment
            lineNum++;
        }
    }

}

void search(Node *itr, std::string find){
    int lineNum = 1; //keep track of index of current node pointed at
    int counter = 0; //counts how many times the substring is found

    while(itr)//loop as long as not null
    {
        if(itr->data.find(find) != -1)//returns -1 if nothing found,
        {
            std::cout<<lineNum << " " << itr->data<<std::endl;//print linenum and data
            counter++;//increment counter

        }
        itr=itr->next;//increment iterator
        lineNum++;//increment line number
    }
    if(counter == 0)//nothing found
        std::cout<<"not found"<<std::endl;
}

