//Andrew Ortega
//COP3530
//LinkedList Line Editor
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node{	//initialize signly linked list
	string text;
	struct node *next;
};
struct node *head=NULL; 		//set head to null
struct node* createnode(string line){ //helper method for insert node
	struct node *newnode=new node; 		//initalizes new nodes line text and sets next null
	newnode->text=line;
	newnode->next=NULL;
	return(newnode);
}
void insert(struct node *line,int index,string temp){
	if(index == -1){		//-1 indicates insert end
 	//	cout << "insertend reached" <<endl; //debug
		struct node *newnode; //creates new node and loads data
		newnode=createnode(temp);  
		if(head==NULL)
			head=newnode; //if head null set to new
		else{
			while(line->next!=NULL) //else traverse to end and insert at end 
				line=line->next;
				line->next=newnode; 
		}
	}
	else{ //insert position
		//cout << "insertposition complete << endl; //debug
		struct node *prev=NULL; 	
		struct node* newnode=createnode(temp);
		int i;
		for(i=1;i<index;i++){ //traverse list to position 
			prev=line;		
			line=line->next;
		}
		if(prev==NULL){ 
			newnode->next=head;
			head=newnode;  //if head is null link to end 
		}
		else{
			newnode->next=line; //link previous to new node
			prev->next=newnode;
		}
	}
}
void deletenode(struct node *line,int index){
	struct node *trash;  //node to be deleted
	struct node *prev=NULL;
	int i;
	for(i=1;i<index;i++){ //traverse to node
		prev=line;
		line=line->next;
	}
	if(prev==NULL){ //if prev=null 
		trash=line;  //delete node
		head=head->next;
	}
	else{
		trash=line; //store line
		prev->next=line->next; //set previous next to next of node to be deleted
	}
	delete trash; //clears memory allocated
}
void editlist(struct node *line,int index,string replace){
	int i;
	for(i=1;i<index;i++){	//traverse list to position
		line=line->next;
	}
	line->text=replace; //replace data
}
void search(struct node *line,string temp){
	int linecount=1;
	while(line){ //while list isnt to the end
		if(line->text.find(temp)!=-1){  //search line for data
			cout<<linecount<<" "<<line->text<<endl; 
		break;
		}	
		line=line->next; //iterate
		linecount++; //increment line count 
	}
	if(line==NULL) 
		cout<< "not found" <<endl;
}
void print(struct node *line){
	if(line==NULL)
		cout << "List Empty" << endl; 
	else{
		int linecount=1;
		while(line){ //traverse list until end
			cout<<linecount<<" "<<line->text<<endl; //print line
			line=line->next; //iterate list
			linecount++;
		}
	}
}
int main(){
	string input; //user input
	string text; //parsed line text
	string str_index; //string index number
	int index;	//parsed input number
	int space;	//line space 
	int nodecount = 1;

do{
	input = " "; //clear input
	getline(cin,input);
	if(input=="print"){
		print(head);
	}
	else if(input=="quit")
		break; 
	else if(input.substr(0,9)=="insertEnd"){
		text=input.substr(11);
		text.pop_back(); 
		insert(head,-1,text);
		nodecount++;
		// cout << nodecount << endl; //debug
	}
	else if(input.substr(0,6)=="insert"){ //insert at specified position 
		// cout << "Insert Pos Reached" << endl;		//debug
		space=input.find(" ",7);  
		str_index=input.substr(7,space-7);
		index = stoi (str_index);		//string to int
		text=input.substr(space+2);		
		text.pop_back();				
		if(index<nodecount+1){		//bound check
			insert(head,index,text);
			nodecount++;
			// cout << nodecount << endl; // debug
		}
		}
	else if(input.substr(0,6)=="delete"){
		//cout <<"delete reached" << endl;  //debug
		str_index=input.substr(7);
		index = stoi (str_index);
		if(index<nodecount){ //bound check
			deletenode(head,index);
			nodecount --;
		}
		// cout << nodecount << endl; //debug
	}
	else if(input.substr(0,4)=="edit"){
		space=input.find(" ",5);
		str_index=input.substr(5,space-5);
		index = stoi (str_index);  //string to int
		text=input.substr(space+2);
		text.pop_back(); 
		if(index<nodecount+1){ //bound check
		editlist(head,index,text);
		}
	}
	else if(input.substr(0,6)=="search"){
		text=input.substr(8);
		text.pop_back(); 
		search(head,text);
	}	
	else{
		cout << "Command not found" << endl;
	}
}while(true);
return 0;
}