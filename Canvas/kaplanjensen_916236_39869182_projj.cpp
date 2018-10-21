#include <iostream>
#include <string>

using namespace std;

//node struct containing a string data field and a next pointer
struct Node{
	string data;
	Node *next;
};
//class for linked list
class linkedList{
	//private data being head node
	private:
	Node *head;
	//public functions and default constructor
	public:
	linkedList(){
		head = NULL;
	}
	//returns pointer to end node
	Node* getEnd(){
		//if no head/linked list, returns null
		if(head == NULL){
			return NULL;
		}
		//traverses to the last node then returns it
		Node* tmp = this->head;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		return tmp;
	}
	//returns pointer to head node, NULL if none
	Node* getHead(){
		if(head == NULL)
			return NULL;
		return head;
	}
	//setter method for head node
	void setHead(Node* newHead){
		this->head = newHead;
	}
};

//inserts input at end
void insertEnd(linkedList &doc, string s){
	Node* end = doc.getEnd(); //gets end node
	Node* newEnd = new Node; //creates new node to be placed at end of linked list
	newEnd->data = s;
	newEnd->next = NULL;
	if(end == NULL){//if there's no list then set this new node as head
		doc.setHead(newEnd);
		return;
	}
	else//if there is a list then make last node point to new node
	end->next = newEnd;
	return;
	
}

//iterates through list to print all items
void print(linkedList &doc){
	int line = 1;//starts with line 1
	Node* tmp = doc.getHead();//temp node used for traversal
	
	while(tmp != NULL){//while statement to iterate through whole list
		cout << line << " " << tmp->data << endl;//properly print lines
		line++;//increment line number
		tmp = tmp->next;
	}
	
}

//inserts at desired line 
void insert(linkedList &doc, int pos, string s){
	Node* tmp = doc.getHead();//temp node for traversal
	Node* newNode = new Node();//create new node to be inserted
	newNode->data = s;
    
    
	
	if(tmp == NULL){//edge case, if there's no list then set newNode as head
		newNode->next = NULL;
		doc.setHead(newNode);
		return;
	}
	//iterate through to node that will be before the newNode
	for (int i = 1; i < pos - 1; i++){
		if(tmp == NULL)//if we iterate out of bounds quit this function
            return;
        tmp = tmp->next;
        
	}
    
    if(tmp == NULL) //if out of bounds quit function
        return;
	
    
	newNode->next = tmp->next;//point the new node to the next node in list
	tmp->next = newNode;//make previous node point to the new node
	
}

//deletes desired line
void deletes(linkedList &doc, int pos){
	Node* bef = doc.getHead();//temporary node for traversal
	if(bef->next == NULL){//if there is only a head node to delete then set head as NULL
		doc.setHead(NULL);
		return;
	}
	
	
	Node* aft = bef->next;//temporary node used to contain list after the node we will delete
	
	for (int i = 1; i < pos - 1; i++){//iterate to desired node
        if(bef == NULL)
            return;//if out of bounds quit program
		bef = bef->next;//iterate
		aft = bef->next;//iterate
	}
    if(aft == NULL)
        return;//if out of bounds, quit function
	bef->next = aft->next;//make the previous node point to the next next node, effectively deleting a line in the list
	
}


//edits desired line by calling delete then insert
void edit(linkedList &doc, int pos, string s){

	deletes(doc, pos);
	insert(doc, pos, s);
	
	
}



//iterates through list until the desired string is found
void search(linkedList &doc, string s){
	Node* tmp = doc.getHead();//temporary node for traversal
	int line = 1;//keep track of line
    bool none = true; //variable keeping track of whether or not a match has been found
	while(tmp != NULL){//iterate through list
		string p = tmp->data;//temporary string of current line to compare with desired string
		if(p.find(s) != -1){//if there's a match properly print the line
			cout << line << " " << tmp->data << endl;
            none = false;//since at least one match has been found, change none to false
		}
		
		line++;//increment line number
		tmp = tmp->next;//traverse
	}
    if(none)//if no matches are found, print not found
	cout << "not found" << endl;
	return;
}

int main(){
	//creates linkedList 
	linkedList doc2;
	//to keep while loop going until "quit" is entered
	bool quit = false;
	
	while(quit == false){
		//two strings that are used to store the input command and string
		string inp;
		string cmd;
		int opt;
		int ind;
		
		getline(cin, inp); //stores entire input into inp
		int pos = inp.find(' '); //position of first space
		cmd = inp.substr(0,pos); //cmd stores the command to be used
		inp = inp.substr(pos+1); //inp now stores the remaining part of input (possibly a number and string or just a string)
		//conditional statements to call proper functions based on specified command
		if(cmd.compare("insertEnd") == 0){
			inp.pop_back(); //gets rid of last quotation mark
			inp = inp.substr(1); //gets rid of first quotation
			insertEnd(doc2, inp);
			continue;
			
		}
		else if(cmd.compare("insert") == 0){
			pos = inp.find(' ');//since insert also requires an index, finds position of the next space before the index
			cmd = inp.substr(0, pos);//stores the index as string
			inp = inp.substr(pos+2); //the string to be inputted, gets rid of first qupte
			inp.pop_back();//gets rid of last quoe
			ind = stoi(cmd);//converts index to int
			insert(doc2, ind, inp);
			continue;
		}
		
		else if(cmd.compare("delete") == 0){
			pos = inp.find(' ');//delete requires index so find position of space before index
			cmd = inp.substr(0, pos);//stores index as string
			ind = stoi(inp);//converts index to int
			deletes(doc2, ind);
			continue;
		}
		
		else if(cmd.compare("edit") == 0){
			pos = inp.find(' ');//edit requires index, gets position of space before index
			cmd = inp.substr(0, pos);//stores index as string
			inp = inp.substr(pos+2);//the string we wish to replace original with, gets rid of quote
			inp.pop_back();//get rid of last quote
			ind = stoi(cmd);//converts index to int
			edit(doc2, ind, inp);
			continue;
		}
			
		else if (cmd.compare("print") == 0){//prints whole list
			print(doc2);
			continue;
		}
			
		else if(cmd.compare("search") == 0){
			pos = inp.find(' ');//gets position of space before string
			inp = inp.substr(pos+2);//the line to search for, excluding first quote
			inp.pop_back();//delete last quote
			search(doc2, inp);
			continue;
		} 
		else if(cmd.compare("quit") == 0){//quits program
			break;
		}
			
		else{
			cout << "Error: input valid syntax." <<endl;//in case of invalid input
			continue;
		}
		

	}
}