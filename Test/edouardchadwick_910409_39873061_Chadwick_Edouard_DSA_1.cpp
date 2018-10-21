//your linked list implementation here
#include <cstddef>
#include <string>
#include <iostream>

        //your line editor implementation here

struct Node{
        public:
        Node* next = NULL;
        std::string sent;};

class LinkedList{
    private:
        Node* head;
    public:
        Node* insertEnd();
        Node* insert_();
        Node* print();
        Node* edit();
        Node* deleteV();
        Node* search_();
        //Node* quit();


        };

   Node* insertEnd(Node* head, std::string value){
    Node* temp=head;
    while(temp->next!=NULL){
    temp=temp->next;}
    Node* addn = new Node();
    temp->next = addn;
    addn->sent = value;
    return head;}

   // Node* insert()
    void print(Node* head){
    int i = 1;
    Node* curr=head;
    while(curr!=NULL){
    std::cout<< i << " "<< curr->sent<<std::endl;
    i++;
    curr=curr->next;
    }
}

    Node* insert_(Node* head, int index, std::string value){
    Node* add = new Node();
    add->sent = value;
        if(index==1){
        add->next=head;
        return add;}
    Node* curr = head;
        for(int i=2;i<index;i++){
        curr=curr->next;
        if (curr ==NULL)
            return NULL;
        }
    Node* next = curr->next;
    curr->next = add;
    add->next = next;
    return head;
    }

  Node* deleteV(Node* head, int index){
    Node* prev = head;
    Node* curr = head->next;
    Node* temp;
    int i=2;
    if(index==1){
        temp = head;
        head=curr;
        delete(temp);}

    while(i!=index && curr!=NULL){
            i++;
        prev=prev->next;
        curr=curr->next;}
        temp=prev->next;
       prev->next=curr->next;
       curr=curr->next;
        delete(temp);

   return head;
  }
    Node* edit(Node* head, std::string value, int index){
        int i=1;
        Node* curr=head;
        while(i!=index){
        curr=curr->next;
        i++;}
        curr->sent=value;
        head =curr;
        return head;
}

    void search_(Node* head, std::string value){
        Node* curr =head;
        int i=0;
        while(curr!=NULL){
                i++;
        if(curr->sent==value){
            std::cout << i <<" " << curr->sent<<std::endl;
            curr = curr->next;
        }
       else if(curr->sent.find(value)<std::string::npos){
               std::cout << i <<" " << curr->sent<<std::endl;
            curr = curr->next;
      }
        else curr = curr->next;
        }
        }
int main()
{
    Node* x = new Node();
    x->sent="the cow";
    insertEnd(x, "the pig");
    insertEnd(x, "the pi");
    insert_(x, 3, " corn");
    print(x);
    std::cout<<"\n";
    deleteV(x,2);
    print(x);
    std::cout<<"\n";
    edit(x,"come here",2);
    std::cout<<"\n";
    print(x);
    std::cout<<"\n";
    search_(x, "pi" );
    //your code to invoke line editor here
}
