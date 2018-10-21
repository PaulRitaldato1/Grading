#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>


using namespace std;
class List{
    public:
List():
head ( nullptr),
curr(nullptr),
temp(nullptr){
}



//Size of List
int sizeOfList(){
    int sizeOfListVal =0;
    node* p = head;
while (p != NULL)
{
  ++sizeOfListVal;
  p = p->next;
}
return sizeOfListVal;
}
//Add node
void addNode(string addData){
node* n = new node;
n->next = nullptr;
n-> data = addData;

if(head !=NULL){
    curr= head;

    while(curr->next!= NULL){
        curr = curr->next;
    }
    curr->next = n;
}
else{
    head = n;
}
}

//deleteNode

void deleteNode(int index){
node* delPtr = NULL;
temp = head;
curr = head;
int count =1;

while(curr !=NULL && count !=index){
    temp = curr;
    curr = curr->next;
    count++;


}
if(curr == NULL){
    cout<<"was not in list"<<endl;
    delete delPtr;
}else{
delPtr = curr;
curr= curr->next;
temp->next = curr;
if(delPtr == head){
    head=head->next;
    temp =NULL;
}
delete delPtr;
}




}


//edit Function
void editNode(string text, int index){

node* delPtr = NULL;
temp = head;
curr = head;
int count =1;

while(curr !=NULL && count !=index){
    temp = curr;
    curr = curr->next;
    count++;


}
if(curr == NULL){
    cout<<"was not in list"<<endl;
    //put return later;
}
if(count == index){

curr->data = text;

}
}

void insertNth( string data, int position) {
position = position-1;

node* temp = new node();

temp->data = data;

node* cur =head;

if(position == 0){

temp->next = head;

return;

}

int i=1;

while(cur != NULL){

if(i == position){

temp->next=cur->next;

cur->next=temp;

return;

}else{

cur =cur->next;

i++;

}

}

return;

}




//Search Function
void searchList(string text){
    curr=head;

int count =1;
bool truth = false;
while(curr!=NULL){
        string g = curr->data;
//Looks for position of text entered
     if( g.find(text) != std::string::npos){
//Removes Quotes
         g.erase(
   remove( g.begin(), g.end(), '\"' ),
    g.end()
    );

        cout<<count<<" " << g<<endl;
      truth = true;
     }
count++;

curr= curr->next;


}if(truth) return;


cout<<"not found"<<endl;

}

//Print List
void printList(){
curr=head;
int count =1;
while(curr!=NULL){
    string v = curr->data;
    //Removes Quotes
     v.erase(
    remove( v.begin(), v.end(), '\"' ),
    v.end()
    );
        cout<<count<<" "<< v<<endl;
        count++;
curr= curr->next;

}

}

private:

    struct node{
string data;
node* next;
};
node* head;
node* curr;
node* temp;





};

int main()
{
  List n;
 string choice;
 string val;
   int val1=0;

while (choice != "quit"){


           std::getline(cin,choice);

          int length = choice.length();



//Edit
              if(choice.find("edit")==0){
                    int pos = choice.find("edit");
                  val1 =stoi(choice.substr(pos+5,6));
                  //Checks to see if the user is asking for an edit thats far from the size
              if(val1 > n.sizeOfList()){
                  continue;
                    }
                    string data = choice.substr(7,length);

                   n.editNode(data,val1);
                    }
//Insert
                if(choice.find("insert ")==0){
                    int pos = choice.find("insert ");
                  val1 =stoi(choice.substr(pos+7,8));
                //Checks to see if the user is asking for an insert thats far from the size
              try {

                    string data = choice.substr(9,length);
                   n.insertNth(data,val1);
                }
                catch (std::out_of_range& exception) {

                    }

                    }

//Search
if(choice.find("search")==0){
                    int pos = choice.find("search");


                    string data = choice.substr(8,length);
   data.erase(
    remove( data.begin(), data.end(), '\"' ),
    data.end()
    );



                  n.searchList(data);
                    }
//Delete
                   if(choice.find("delete")==0){
                    int pos = choice.find("delete");
                  val1 =stoi(choice.substr(pos+7,8));
                  //Compares the value vasked by the user tp the size of the list, if to big then ignores it
              if(val1 > n.sizeOfList()){
                  continue;
                    }
                    string data = choice.substr(8,length);

                   n.deleteNode(val1);
                    }
            //insertEnd

                   if(choice.find("insertEnd")==0){
                    int pos = choice.find("insertEnd");
                    //Error Handling for out of range wants by the user
try {

 string data = choice.substr(10,length);
 n.addNode(data);
    }
    catch (std::out_of_range& exception) {

                    }


}

    //Print
    if(choice == "print"){
    n.printList();
    }
    //Quit
    if(choice== "quit"){

        return 0;


    }

}
    return 0;
}

