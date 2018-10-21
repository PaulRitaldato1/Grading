#include <iostream>




//your linked list implementation here

class Node {
    public:
        std::string value;
        Node* next;
};

class list
  {
    public:
    Node *head = NULL, *tail = NULL;
    ~list(){Node *currNode=head;


        while(currNode!=NULL)
        { Node* temp=currNode;
            currNode=currNode->next;
            delete(temp);
        }
    }




        //your line editor implementation here
void insertEnd(std::string value)
    {
      Node *temp=new Node;
      temp->value=value;
      temp->next=NULL;
      if(head==NULL) //if list is empty
      {
        head=temp;
        tail=temp;

      }
      else
      {
        tail->next=temp;
        tail=temp;
      }
    }

void insertLine(Node* &head, int index,std::string valueInput) {
    Node *newNode = new Node;   //create new node
    newNode->value = valueInput;
    if (index == 1)                  //if inserting at beginning
    {
        newNode->next = head;
        head = newNode;
    } else {                      //if inserting middle or end
        int count = 1;           //current index position
        Node *currNode = head;
        while (currNode->next != NULL) {
            if (count == (index - 1)) {      //if current position is one before the index to insert
                newNode->next = currNode->next;
                currNode->next = newNode;
               break;
            }
            currNode = currNode->next;       //iterate through list
            count++;                         //increment position count
        }
        if (index > count + 1) {         //if out of bounds, return
            return;
        }
        if(count == (index - 1) && currNode->next == NULL){  //adding to end of list
            currNode->next= newNode;
            newNode->next=NULL;
        }
    }

}




void search(Node* node,std::string valueInput)      //head is passed as node
{
int index =1;
    bool found= false;
    while (node!=NULL){
    if (node->value.find(valueInput) !=-1) {   //if not equal to -1 found
        found = true;
        std::cout << index << " " << node->value << "\n";
    }
            node=node->next;
    index++;
    }
    if(found==false){
        std::cout<<"not found"<<"\n";}

}





void editLine(Node* node, int target,std::string change)            //iterate to find, then change
{
int index =1;
    while (node!=NULL){
    if (index==target){
    node->value=change;
    return;}

        node=node->next;
    index++;
    }
}





    void print()
  {
    Node *temp=head;

    int index=1;
    while(temp!=NULL)
    {
      std::cout<<index<<" "<<temp->value<<"\n";
      temp=temp->next;
        index++;
    }

  }



    void deleteLine(Node*& head,int valueInput)
    {   if (valueInput ==1)                  //if deleting beginning node
        {delete(head) ;
            head=head->next;

        }

        else{                      //if deleting at middle or end
            int count=1;
            Node* currNode = head;
            while(currNode->next!=NULL){
                if(count==valueInput-1){       //if current position is one before index to delete
                    currNode->next=currNode->next->next;
                    return;
                }
                currNode= currNode->next;

                count++;}

        }
    }




};


//your code to invoke line editor here
int main() {
    std::string input;
    char delimiter = '"';
    list myList;


    while (input.substr(0, 4) != "quit") {   //exit when user input is quit

        std::getline(std::cin, input);      //get input



        if (input.substr(0, 9) == "insertEnd") {
            int indexstart = input.find("\"");
            int indexend = input.length() - 2;


           int count=0;
            for (int i=0; i<input.length(); i++){  //checks to see if there are 2 paranthesis
                                                   //ignore if there isn't
                if (input.at(i)== delimiter){
                    count++;}
            }

            std::string string1 = input.substr(indexstart + 1, indexend - indexstart);

            if(string1.length()> 80){string1=string1.substr(0,80);} //check if >80


            if(count ==2 ){
                myList.insertEnd(string1);}

        }


        if (input.substr(0, 7) == "insert ") {

            int count=0;
            for (int i=0; i<input.length(); i++){  //checks to see if there are 2 paranthesis

                if (input.at(i)== delimiter){
                    count++;}
            }


            int indexstart = input.find("\"");
            int indexend = input.length() - 2;



            std::string string = input.substr(indexstart + 1, indexend - indexstart);

            if(string.length()> 80){string=string.substr(0,80);} //cut string off at length 80

             if(count==2){
                 myList.insertLine(myList.head,input.at(7) - '0',string);} //only calls method if 2 parenthesis
        }




        if (input.substr(0, 5) == "print") { myList.print(); }



        if (input.substr(0, 4) == "edit") {
             int count =0;
            for (int i=0; i<input.length(); i++){  //checks to see if there are 2 paranthesis

                if (input.at(i)== delimiter){
                    count++;}
            }

            int indexstart = input.find("\"");
            int indexend = input.length() - 2;

            std::string string = input.substr(indexstart + 1, indexend - indexstart);
            if(string.length()> 80){string=string.substr(0,80);} //check if >80, cut off at 80

           if(count ==2){
               myList.editLine(myList.head, input.at(5) - '0', string);}
        }


        if (input.substr(0, 6) == "delete") {
            myList.deleteLine(myList.head,input.at(7) - '0' );
        }





        if (input.substr(0, 6) == "search") {

            int count=0;
            for (int i=0; i<input.length(); i++){  //checks to see if there are 2 paranthesis

                if (input.at(i)== delimiter){
                    count++;}
            }

            int indexstart = input.find("\"");
            int indexend = input.length() - 2;

            std::string string = input.substr(indexstart + 1, indexend - indexstart);

            if(count==2){
                myList.search(myList.head, string);}
        }




        }

}

