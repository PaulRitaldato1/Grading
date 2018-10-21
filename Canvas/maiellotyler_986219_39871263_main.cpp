#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <sstream>
/*
* Struct Node, typical structure, ran into some programs so I made
* a constructor, so that I could set the temp node to contain the string input.
*/
struct Node
{
    std::string data;
    Node *next;
    Node(std::string data, Node* next)
    {
        this->data = data;
        this->next = next;
    }
};
/*
* Linked_list Class, for creating a new list.
* A few getter/setter methods that had some use.
*/
class Linked_list
{
    private:
        Node *head,*tail;
    public:
        Linked_list()
        {
            head = nullptr;
            tail = nullptr;
        }
        Node* get_head()
        {
            return head;
        }
        void set_head(Node* head)
        {
            this->head = head;
        }
};
/*
* count_list keeps track of the list size so the user
* cannot request something out of range and cause a segfault.
*/
int count_list(Node* head)
{
    Node* curr = head;
    int count = 0;
    while(curr!=nullptr) //iterates through the whole list.
    {
        curr = curr->next;
        count++;
    }
    return count;
}
/*
* Inserts a node at the end of a the Linked list.
*/
Node* insert_end(Node* head, std::string userInput)
{
    Node* temp = new Node(userInput, nullptr);
    Node *curr = head;
    if(head==nullptr) //if list is empty, will set curr = temp;
    {                 //note: temp is constructed with userInput
        curr = temp;
        return curr;
    }
    while(curr->next != nullptr) //iterates through list
    {
        curr = curr->next;
    }
    curr->next = temp; //next node set to temp
    return head;
}
/*
* Inserts a node at any index of a Linked list.
*/
Node* insert_node(Node* head, int index, std::string userInput)
{
    Node* curr = head;
    Node* temp = new Node(userInput,nullptr);
    int listSize = count_list(head); //this checks to make sure call is in range
    if(listSize<index-1)             //prevents out of range calls (segfaults)
    {
        return head;
    }
    if(index==1) //if first index, will have to shift head node.
    {
        temp->next = head;
        head = temp;
        return head;
    }
    int count = 0;
    while(count < (index-2)) //iterates to the point we need to be at.
    {                        //since curr->next is being used we want to be at index-2
        curr=curr->next;
        count++;
    }
    temp->next = curr->next;
    curr->next = temp;
}
/*
* Deletes a node an any index in a Linked List.
*/
Node* delete_node(Node* head, int index)
{
    int listSize = count_list(head); //this checks to make sure call is in range
    if(listSize<index)               //prevents out of range calls (segfaults)
    {
        return head;
    }
    Node* curr = head;
    Node* prev = new Node("",nullptr);
    int count = 1;
    while(curr!=nullptr && count < (index-1)) //iterates to the point of deletion
    {
        curr=curr->next;
        count++;
    }
    if(curr==nullptr) //one check to make sure that we haven't left range
    {
        return head;
    }
    if(curr->next!=nullptr) //checks if we are out of range again
    {
        prev = curr->next;  //relinks the nodes around deletion.
        curr->next = curr->next->next; //curr->next = cur->next->next;
        free(prev);                    //causes us to shift around deleted node
    }
}
/*
* Edits the contents of a node at a given index in a Linked list
*/
Node* edit_node(Node* head, int index, std::string userInput)
{
    Node* curr = head;
    Node* temp = new Node("",nullptr);
    if(index==1 && curr->next!=nullptr) //checks if the first input is to be edited
    {                                   //also checks if list is empty as to not cause error
        temp = curr->next;
        curr = temp;
        return head;
    }
    int count = 0;
     while(curr->next!=nullptr && count < (index-1)) //iterates list to index
    {
        curr=curr->next;
        count++;
    }
    curr->data = userInput; //changes the value of the indexed node to userInput
}
/*
* Prints the Linked List
*/
Node* print_list(Node* head)
{
    int countLine = 1;
    while(head!=nullptr) //iterates through the list
    {
        std::cout << countLine << ' ' << head->data << "\n"; //prints with the line number
        head = head->next;                                   //each time, and then moves to the next
        countLine++;
    }
}
/*
* Searches the linked list for a random substr value
*/
Node* search_list(Node* head, std::string userInput)
{
    Node* curr = head;
    int count =1;
    std::string mInput(userInput); //sets a string = to userInput
    if(curr->data.find(mInput)!=std::string::npos) //if the substr is found, print the node!
    {                                              //this one specifically checks the head.
        std::cout << count << " " << curr->data << "\n";
    }
    while(curr->next!=nullptr) //iterates through the list looking for more 
    {                          //nodes that include the substr.
        count++;
        curr = curr->next;
        if(curr->data.find(mInput)!=std::string::npos) //if the substr is found, print the node!
        {
            std::cout << count << " " << curr->data << "\n";
            return head;
        }
    }
    std::cout << "not found" << "\n"; //if nothing is found!
}
/*
* Controls all user input
*/
int controller_method()
{
    Linked_list *obj = new Linked_list();
    Node* head = obj->get_head();
    int userNumber = 0;
    while(true)
    {
        std::string userInput;
        std::getline(std::cin, userInput); //gets input
        auto userToken = userInput.substr(0, userInput.find(' ')); //tokenizes the keyword
        auto cutInput = userInput.substr(userInput.find('"')+1); //cuts the rest of the input
        cutInput = cutInput.substr(0,cutInput.find('"')); //down to be readable by the methods
        if(userToken == "insertEnd")
        {
            head = insert_end(head, cutInput);
        }
        else if(userToken == "insert")
        {
            std::stringstream nukedFinal(userInput.substr(userInput.find(' ')));
            nukedFinal >> userNumber; //extracts the number from a string
            insert_node(head, userNumber, cutInput);
        }
        else if(userToken == "delete")
        {
            std::stringstream nukedFinal(userInput.substr(userInput.find(' ')));
            nukedFinal >> userNumber; //extracts the number from a string
            delete_node(head, userNumber);
        }
        else if(userToken == "edit")
        {
            std::stringstream nukedFinal(userInput.substr(userInput.find(' ')));
            nukedFinal >> userNumber; //extracts the number from a string
            edit_node(head, userNumber, cutInput);
        }
        else if(userToken == "print")
        {
            print_list(head);
        }
        else if(userToken == "search")
        {
            search_list(head, cutInput);
        }
        else if(userToken == "quit")
        {
            return 0;
            break;
        }
    }
}
int main() 
{
    int programStatus = controller_method();
    if(programStatus == 0)
    {
        return 0;
    }
}