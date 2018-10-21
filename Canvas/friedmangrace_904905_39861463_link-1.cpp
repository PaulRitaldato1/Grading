#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class List{
    private:
        struct node{
            string data;
            node *next;
        };
        node *head, *tail;

    public:
        List(){
           head =NULL;
           tail=NULL;

        };
        void insertEnd(string text);
        void searchItem(string text);
        void insertItem(int num, string text);
        void deleteItem(int num);
        void editItem(int num, string text);
        void display();
};


void List::insertEnd(string text){ // "text"  -- insert given text at the end of the document
      node *temp=new node;
      temp->data=text;
      temp->next=NULL;
      if(head==NULL){ //if list is empty
        head=temp;
        tail=temp;
        temp=NULL;
      }
      else{ //add node to end of the list
        tail->next=temp;
        tail=temp;
      }
  }

  void List:: searchItem(string text){ //search "text" -- print the line number and line that contains the given text.  print "not found" if it is not found

    vector <int> nums;
    node *temp=new node;
    temp=head;
    int sum = 1;
        while(temp!=NULL){
            if (temp->data.find(text) != std::string::npos){
              cout<<sum <<" " << temp->data<<"\n" ;
              nums.push_back(sum);
            }
            sum++;
            temp=temp->next;
        }
        if (nums.empty()==true){
            cout<<"not found"<<"\n";
            return;
        }
        return;
}

  void List:: insertItem(int num, string text){//insert 3 "text" --insert given text at the line indicated by index given
    node* temp1  = new node;
    temp1->data = text;
    temp1->next = NULL;
    if(num == 1){
        temp1->next = head;
        head = temp1;
        return;
    }
    node* temp2 = head;
    for(int i=0;i<num-2;i++){
        temp2 = temp2->next;
    }
    if(temp2!=NULL){

        temp1->next = temp2->next;
        temp2->next = temp1;
    }
    else return;
  }


  void List:: deleteItem(int num){ //delete 3 --- delete line at index given
    node* temp1 = head;
    if(num == 1){
        head = temp1->next;
        free(temp1);
        return;
    }
    for(int i=0;i<num-2;i++){
        temp1 = temp1->next;
    }
    if (temp1->next!=NULL){
        node* temp2 = temp1->next;
        temp1->next = temp2->next;
        free(temp2);
    }
    else return;
  }

   void List:: editItem(int num, string text){//edit 3 "text" --- replace the line at the index given with the given text

        deleteItem(num);
        insertItem(num,text);
  }

  void List:: display(){  //print -- print the entire document, with line numbers
    node *temp=new node;
    temp=head;
    int sum = 1;
    while(temp!=NULL){
      cout<<sum <<" " << temp->data<<"\n" ;
      sum++;
      temp=temp->next;
    }
  }



int main() {
    List grace;
    string str;
    vector <string> newIn;
    string input;
    int found;
    string gay;
    string help;

    while (input != "quit"){ //quit - quit/exit the program

        getline (cin,input);
        newIn.push_back(input);

    }
    for (int i=0; i < newIn.size(); i++){
            help = newIn.at(i);



        if (help.find("insertEnd")!=string::npos){
           grace.insertEnd(str.assign(help.begin()+ 11, help.end()-1));

        }
        else if (help.find("print")!=string::npos){
            grace.display();
        }

        else if (help.find("search ")!=string::npos){
            grace.searchItem(str.assign(help.begin()+ 8, help.end()-1));

        }


        else if (help.find("insert ")!=string::npos){

            int len = (help.length()-10);
            gay = str.assign(help,10,len-1);
            stringstream ss(help);
            ss >> help>> found;
            grace.insertItem(found, gay);
        }

         else if (help.find("delete")!=string::npos){
            stringstream ss(help);
            ss >> help>> found;
            grace.deleteItem(found);
        }

        else if (help.find("edit ")!=string::npos){

            int len = (help.length()-8);
            gay = str.assign(help,8,len-1);
            stringstream ss(help);
            ss >> help>> found;
            grace.editItem(found, gay);

        }

    }
}

