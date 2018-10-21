#include <iostream>
#include <string>
#include <vector>
#include <iostream>



using namespace std;

// my LinkedList class with all the nescessarry methods

class LinkedList{
 
private:
	
 struct node{
	string data;
	node* next;
 };
	typedef struct node* nodePtr;
	
	nodePtr head;
	nodePtr tail;

	
public:
	LinkedList();
	void addNode(string str);
	void print();
	void addNode(string str, int pos);
	void deleteNode(int pos);
	void editNode(string str, int pos);
	void search(string str);
	void lineEditor();
	};

	

LinkedList::LinkedList(){
	head = NULL;
	tail = NULL;
}

//adds a node to the list with the given string

void LinkedList::addNode(string str){
	nodePtr t1 = new node;
	t1->next = NULL;
	t1->data = str;
	
	if( head != NULL){
		tail->next = t1;
		tail = t1;
	}
	
	else{
		head = t1;
		tail = t1;
	}
}

// prints the list


void LinkedList::print(){
nodePtr t1 = head;
int c=1;
while(t1 != NULL){
		cout<<c<<" "<<t1->data<<"\n";
		t1 = t1->next;
		c++;
	}
}

// add a node with the given string in the given position

void LinkedList::addNode(string str, int pos){
	bool out = false;
	nodePtr t1 = head;
	
	nodePtr t2 = new node;
	t2->data = str;
	
	if(pos == 0){
		t2->next = head;
		head = t2;
	}
	
	else{
	for(int i=0;i<pos-1;i++){
		if(t1->next != NULL){
				t1 = t1->next;
			}
		else{
			out = true;
		}
	
			
	}
	
	if(!out){ 

	t2->next = t1->next;
	t1->next = t2;
		}
	}
}

// deletes the node at the given position

void LinkedList::deleteNode(int pos){
	nodePtr t1 = head;
	bool out = pos < 0;
	
	if(pos == 0){
		head = t1->next;
		delete t1;
		return;
	}
	for(int i=0;i<pos-1;i++){
		if(t1->next != NULL){
				t1 = t1->next;
			}
		else{
			out = true;
		}
	}
	
			if(t1->next == NULL){
				out = true;
			}
		if(!out){
			nodePtr t2 = t1->next;
			t1->next = t2->next;
			delete t2;
	}
}

// edits the node at the given position

void LinkedList::editNode(string str, int pos){
	nodePtr t1 = head;
	
	bool out = pos < 0;
	
	for(int i=0;i<pos;i++){
		if(t1 != NULL){
			t1 = t1->next;
		}
		else{
			out = true;
		}
	}
	
	if(!out){
		t1->data = str;
	}
}

// searches all nodes in the list for the given string

void LinkedList::search(string str){
	nodePtr t1 = head;
	int c = 1;
	bool found = false;
	while(t1 != NULL){
		if((t1->data).find(str) != string::npos){
			cout<<c<<" "<<t1->data<<"\n";
			found = true;
		}
		t1 = t1->next;
		c++;
	}
	
	if(!found)
	cout<<"not found\n";
}

// takes in input from the user and calls certain methods depending on the user command

void lineEditor(){
	LinkedList list;
	
	string str;
	getline(cin,str);
	//cout<<str<<"\n";
	while(str.compare("quit")!=0){
		
		string::size_type pos = str.find(' ',0);
		string comm = str.substr(0,pos);
		string text;
		//cout<< comm<<"\n";
		string::size_type pos1 = str.find('"',0);
		string::size_type pos2 = str.find('"',pos1+1);
		text = str.substr(pos1+1,pos2-pos1-1);
		//cout<<text;
		if(comm.compare("insertEnd")==0 && pos2!=string::npos){
			list.addNode(text);
		}
		
		if((comm.compare("insert")==0 || comm.compare("edit")==0)&& pos2!=string::npos){
			string::size_type pos3 = str.find(' ',0);
			string::size_type pos4 = str.find(' ',pos1+1);
			int val = stoi(str.substr(pos3+1,pos4-pos3-1));
			
			if(comm.compare("insert")==0){
				list.addNode(text,val-1);
			}
			if(comm.compare("edit")==0){
				list.editNode(text,val-1);
			}
		}
		
		if(comm.compare("delete")==0){
			string::size_type pos5 = str.find(' ',0);
			int val = stoi(str.substr(pos5+1,str.length()-pos5-1));
			list.deleteNode(val-1);
		}
		
		if(str.compare("print")==0){
			list.print();
		}
		
		if(comm.compare("search")==0 && pos2!=string::npos){
			list.search(text);
		}
		
		getline(cin,str);
	}
	
	
	
}

// simply calls the lineEditor method to start the program

int main(){
	lineEditor();
	
	return 0;
}
