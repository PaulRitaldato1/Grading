#include <iostream> 
#include <string>
using namespace std;

struct node
  {
    string data;  
    node * next;
	node(){
        next = NULL;
        data = "";
    }
    ~node(){   //node destructure
        delete next;
    }
  };	
  
  class list
  {
    
    node *head, *tail;
	int count;
	
    public:
      
    list();
	~list();
	void insertEnd(string s);  
	void insert(string s, int i);
	void deleteNode(int i);
	void edit(string s, int i);
	void print();
	void search(string s);
	void quit();
    	void useMethods(string jojo);
    	int getCount(){return count;};  
    	node * getTail(){return tail;};
  };
  
list::list(){            //const O(1)
	  head = nullptr;
	  tail = nullptr;
	  count = 0;
  }

  
list::~list(){         //destructure O(1)
	  delete head;
	  delete tail;
  }


void list::insertEnd(string s){
		node *curr = new node;
		
		curr->data=s;       //element of the data equal to string
		curr->next=NULL;    //last box
		if(tail==NULL && head==NULL){
			head = curr;
		}
		else{
			tail->next=curr;
		}
		
		tail=curr;       // tail is what the curr was
		count++;
        	curr = NULL;             
		delete curr;       
	}

void list::insert(string s, int i){
    if(i>count+1){  //O(1)
        return;
    }
	node *curr = new node;  //O(1)
	node *insert = new node; 
	node *before = new node;
	curr=head;
    	insert->data=s;
        
    if(i==1){                  //O(1)
        insert->next=head;
        head = insert;
        }
	else{
		for(int j=1; j<i; j++){  //O(n)
			before=curr;
			curr=curr->next;
	    }

		before->next=insert;
		insert->next=curr;
  	}

        insert=NULL;
        before=NULL;
        curr = NULL;
	delete insert;
	delete before;
	delete curr;
        count++;
}
	
void list::deleteNode (int i){
       
        if(i>count){  //O(1)
			return;
		}
	    
        if(i==1){     //O(1)
            head=head->next;
        }
        
        else{         //O(1)
           node *curr = new node;
	       node *before = new node;
	       curr=head;
	       int num=1;
	
	        while(num<i){   //O(n)
		        before=curr;
			    curr=curr->next;    
	            num++;
            }
            
            if(i == count){   //O(1)
                before->next = nullptr;
                tail = before;
            }
            else{
                before->next = curr->next; 
            }
        }  
    }
	
void list::edit(string s, int i){
	node *curr = new node;
	curr=head;
	for(int j=1; j<i; j++){  //O(n)
		curr=curr->next;
	}
		curr->data=s;
        curr = NULL;
		delete curr;
	}
	
	void list::print(){
        node *prnt=head;  
        int j=1;
        while(prnt!=NULL){   //O(n)
            cout<<j++<<" "<<prnt->data<<endl; 
            prnt=prnt->next;           
        }
        prnt = NULL;
        delete prnt;
    }
		
void list::search (string s){
		if(head==NULL){ //O(1)
			return;
		}
	
		node *curr = new node;
		curr=head;
		int num=1; 
        size_t found = 0;
	
		while(curr!=NULL){   //O(n)
		    found = curr->data.find(s);
			if(found != std::string::npos){
				cout<<num<<" "<<curr->data<<endl;
			} 
			else if (curr->next==NULL && curr->data!=s) {  //O(1)
				cout<<"not found"<<endl;
				break;
			}
			num++;
			curr=curr->next;
		}
	
		curr=NULL;
		delete curr;
	
	}
	
	void list::quit(){
		return;
	}
void list::useMethods(string jojo){
        std::size_t found = jojo.find_first_of(" ");
        string name = "";
        name=jojo.substr(0,found);
        if(name=="insertEnd"){  //O(1)
            string insertion="";
            found = jojo.find_first_of("\"");
            insertion=jojo.substr(found+1);
            insertion.pop_back();
            insertEnd(insertion);
        } 
        else if(name=="search"){   //O(1)
            string insertion="";
            found = jojo.find_first_of("\"");
            insertion=jojo.substr(found+1);
            insertion.pop_back();
            search(insertion);
         }
        else if(name=="insert"){    //O(1)
            int number=0;
            string insertion="";
            insertion=jojo.substr(found+1,found+2);
            number = stoi(insertion);
            
            found = jojo.find_first_of("\"");
            insertion=jojo.substr(found+1);
            insertion.pop_back();
            insert(insertion,number);
        }
        else if(name=="edit"){      //O(1)
            int number=0;
            string insertion="";
            insertion=jojo.substr(found+1,found+2);
            number = stoi(insertion);
            found = jojo.find_first_of("\"");
            insertion=jojo.substr(found+1);
            insertion.pop_back();
            edit(insertion,number);
        }
        else if(name=="delete"){    //O(1)
            string insertion="";
            int number=0;
            insertion=jojo.substr(found+1);
            number = stoi(insertion);
             deleteNode(number);
        }
        else if(name=="print"){     //O(1)
            print();
        }
        else if(name=="quit"){      //O(1)
            quit();
        }
        else{            
	return;
        }            
}
    
int main(){ 
    list *a = new list;
    string jojo = "";
        while(jojo!="quit"){       //O(n)
            getline(cin,jojo);
            a->useMethods(jojo);
        }
}