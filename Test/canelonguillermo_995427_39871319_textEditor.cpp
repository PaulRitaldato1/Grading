#include<iostream> 
#include<string> 
using namespace std;

struct Node{
	std::string lines;
	Node * next;
	Node(){
		lines = "";
		next = NULL;
	}
	~Node(){
		delete next;	
	}
};

class LinkList{
	
	Node *head, *tail;
	int size;
	
	public:
	
	LinkList();
	~LinkList();
	void insertEnd(std::string s);
	void insert(string s, int i);
	void deleteS(int i);
	void edit(string s, int i);
	void print();
	void search(string s);
	void useTextEditor(string s);
	int getSize(){return size;}

};

LinkList::LinkList(){
	head = NULL;
	tail = NULL;
	size = 0;
}

LinkList::~LinkList(){
	delete head;
	delete tail;
}

void LinkList::insertEnd(string s){
	Node *text = new Node;
	text->lines = s;
	text->next = NULL;
	
	if(head == NULL){
		head = text;
        tail=text;
	}
	else{
		tail->next=text;
        tail=text;
	}
	
	text = NULL;
	delete text;
	size++;
}

void LinkList::insert(string s, int i){
	if(size+1<i){
		return;
	}

	Node *temp = new Node;
	temp->lines= s;
	
	if(i == 1){
		temp->next = head;
		head = temp;
	}
	else{
		Node *curr = new Node;
		Node *prev = new Node;
		curr = head;
	
		for(int j = 1; j<i; j++){
			prev = curr;
			curr = curr->next;
		}
		
		prev->next = temp;
		temp->next = curr;
		curr = NULL;
		prev = NULL;
		delete curr;
		delete prev;
	}
	
	temp = NULL;
	delete temp;
	size++;
}

void LinkList::deleteS(int i){
	if(size<i){
		return;
	}
	
	Node *curr = new Node;
	curr = head;
	
	if(i == 1){
		head = head->next;
	}
	else{
		Node *prev = new Node;
	
		for(int j = 1; j<i; j++){
			prev = curr;
			curr = curr->next;
		}
		
		if(i == size){
			prev->next = NULL;
			tail = prev;	
		}
		else{
			prev->next = curr->next;
		}
		
		prev = NULL;
		delete prev;
	}
	
    curr = NULL;
	delete curr;
	size--;
	
}

void LinkList::edit(string s, int i){
	if(i>size){
		return;
	}
	
	Node *temp = new Node;
	temp = head;
	
	for(int j = 1; j<i; j++){
		temp = temp->next;
	}
	
	temp->lines = s;
	
	temp = NULL;
	delete temp;
}

void LinkList::print(){
	Node *rhs = head;
	int index = 1;
	while(rhs!=NULL){
		cout<<index++<<" "<<rhs->lines<<endl;
		rhs = rhs->next;
	}
	rhs = NULL;
	delete rhs;
}

void LinkList::search(string s){
	Node *curr = new Node;
	int index = 1;
	curr = head;
	size_t found=0;
	while(curr != NULL){
        found = curr->lines.find(s);
		
        if(found != std::string::npos){
			cout<<index<<" "<<curr->lines<<endl;
		}
		else if(curr->next == NULL){
			cout<<"not found"<<endl;
			break;
		}
		index++;
		curr = curr->next;
	}
	curr = NULL;
	delete curr;
}

void LinkList::useTextEditor(string s){
	
	string command = "";
	string text = "";
	size_t found = s.find_first_of(" ");
	command = s.substr(0,found);
	
	if(command == "insert" || command == "edit"){
		int i = 0;
		text = s.at(found+1);
        
		text = s.substr(found,s.find(" ",found));
		i = stoi(text);
		text = "";
		
		found = s.find("\"");
		
		if(found != std::string::npos){
			text = s.substr(found+1);
			text.pop_back();
		}
		
		if(command == "insert"){
			insert(text,i);
		}
		
		else if(command == "edit"){
			edit(text,i);
		}	
	}
	
	else if(command == "insertEnd" || command == "search"){
		found = s.find("\"");
		
		if(found != std::string::npos){
			text = s.substr(found+1);
			text.pop_back();
		}
		
		if(command == "insertEnd"){
			insertEnd(text);
		}
		else if(command == "search"){
			search(text);
		}
	}
	
	else if(command == "delete"){
		int i = 0;
		text = s.at(found + 1);
		text = s.substr(found);
		i = stoi(text);
		deleteS(i);
	}
	
	else{
		if(command == "print"){
			print();
		}
		else{
			return;
		}
	}
	
}

int main(){
	string s = "";
	LinkList *editor = new LinkList();
	while(s!="quit"){
		getline(cin,s);
		editor->useTextEditor(s);
	}
	return 0;
}