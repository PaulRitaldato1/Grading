#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct node{
	
	node *next=NULL;
	string data;	
};

class Mylist{

public:
	node* head;
Mylist(){
		head=NULL;

	
}//end of constructor

	//needed methods
	// inserts a node at a specified position
	void insert(int index,string Inputdata){
		node* temp=new node();
		temp->data=Inputdata;
		
		
		
		//if the list is empty
		if(index==1){
			temp->next=head;
			head=temp;
				
		}
		int i=2;   
		 node* cur = head;   
		 while (i<index && cur->next!=NULL){        
		 cur = cur->next;          
		 i++;   
		  }   
		  node* next = cur->next;    
		  cur->next = temp;    
		  temp->next = next;
			
	}//end of method 
	
	void edit(int index,string text){
		node* temp=new node();
		temp->data=text;
	
		
		if( index==0){
			head->data=text;
		
		}
		 int i=1;   
		 node* cur = head;   
		 while (i<index && cur->next!=NULL){        
		 cur = cur->next;          
		 i++;   
		  }  
		  cur->data=text; 
	}//end of method
	
	//delete at a specified position method 
	void deletenode(int position){
		
	// If linked list is empty 
   if ( head == NULL) 
      return; 
  
    node* temp=head;
  
    // If head needs to be removed 
    if (position == 1) 
    { 
        head= temp->next;   // Change head 
        delete(temp);               // free old head 
        return; 
    } 
  
    // Find previous node of the node to be deleted  so we can relink the list properly
    for (int i=2;temp!=NULL && i<position; i++) 
         temp = temp->next; 
  
    // If position is more than number of ndoes, out of bounds issue will occur 
    if (temp == NULL || temp->next == NULL) 
         return; 
  
    // Node temp->next is the node to be deleted 
    // Store pointer to the next of node to be deleted 
    node *next = temp->next->next; 
  
    // Unlink the node from the list 
    delete(temp->next);  
    temp->next = next;  
		
	}// end of method 
	
	
	
	
	void search(string text){
		
	node* cur = head;  // Initialize current 
	bool found=false;
	int lineNum=1;
        int checker=0;
    while (cur != NULL) 
    { 
        
        if (cur->data.find(text) != std::string::npos){
        	//if the the given text exists ssomewhere in the string data
        	cout<<lineNum<<" "<<cur->data<<endl;
            checker++;
        	
        	
		}//end of if
        lineNum++;
        cur = cur->next; 
    } 
	
	if(checker==0){
		std::cout<<"not found"<<endl;
	}
	
	
	}//end of search method
	
	
	
	
	void insertEnd(string text){
		
	node* newnode=new node();
    newnode->data=text;
    newnode->next=NULL;
    
    node* cur=new node();
    cur=head;
     

    if(head == NULL)
       head=newnode;
    else
    {
        while(cur->next!=NULL){
		
            cur=cur->next;
        }
        cur->next=newnode;///so this is what you need

    }
		
		
		
	}
	void print( ){
		
		node* cur=new node();
		cur=head;
		int lineNum=1;
		
		while(cur!=NULL){
		cout<<lineNum<<" "<<cur->data<<endl;
		cur=cur->next;
		lineNum++;
				
		}//end of loop
		
	}// end of method
	
	int length(){
		node* cur=new node();
		cur=head;
		int L=1;
		while(cur!=NULL){
			L++;
			cur=cur->next;
		}
		
		return L;
	}
	
	
	
	
	
};//end of class

// helps to analyze user input
int NumberExtractor(string s){

   stringstream ss;	 

	/* Storing the whole string into string stream */
	ss << s; 

	/* Running loop till the end of the stream */
	string temp; 
	int found=-2; 
	int k=-1;
	while (!ss.eof()) { 

		/* extracting word by word from stream */
		ss >> temp; 

		/* Checking the given word is integer or not */
		if (stringstream(temp) >> found) 
			k= found;
            temp="";
            
	
	} 
return k;
	
}//end of isnum function




// Function to remove all spaces from a given string
string removeQuotes(string s) 
{
    s.erase(
    remove( s.begin(), s.end(), '\"' ),
    s.end()
    );
    return s;
}

int main()
{
	//receives the input as a string
   string str=" "; 
    string text=" ";
    bool program=true;
    Mylist LineEditor;
    int number=0;
    while(program){
    	getline(cin,str);
    	//str=removeSpaces(str);
    	number=NumberExtractor(str);
    	int L=str.length();
	
    if(str.find("insertEnd") != std::string::npos && number<0){
    	int n=str.find('"');
        string txt=str.substr(n+1,L);
         txt=removeQuotes(txt);
        LineEditor.insertEnd(txt);
      
       
	}
	
	if(str.find("insert") != std::string::npos && number>=0){
        if(LineEditor.length()<number)
        { continue;
        }
        else{
		  	int n=str.find('"');
        string txt=str.substr(n+1,L);
        txt=removeQuotes(txt);
        LineEditor.insert(number,txt);
        }
		
	}
	
	if(str.find("search") != std::string::npos){
		int n=str.find('"');
        string txt=str.substr(n+1,L);
        txt=removeQuotes(txt);
        LineEditor.search(txt);
     
		
	}
	
	if (str.find("delete") != std::string::npos){
		if(LineEditor.length()<number)
        { continue;
        }
        else{
		
			int n=str.find('"');
        string txt=str.substr(n+1,L);
        txt=removeQuotes(txt);
        LineEditor.deletenode(number);
     
	}//end of else
		
	}
    if (str.find("edit") != std::string::npos){
    	
    	if(LineEditor.length()<number)
        { continue;
        }else{
		
    		int n=str.find('"');
        string txt=str.substr(n+1,L);
        txt=removeQuotes(txt);
		LineEditor.edit(number,txt);
           }//end of else
	}
	if (str.find("print") != std::string::npos && number==-1){
		LineEditor.print();
	
		
	}
	if (str.find("quit") != std::string::npos && number==-1){
		return 0; //exits the program 
		
	}
    

}//end of while

}
