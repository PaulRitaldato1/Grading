#include <iostream>
#include <string>
using namespace std;

class Node{
	public:
	string text;
	Node* next;
};


int main(){
	Node* head = new Node();
	Node* tail = new Node();
	tail=head;
	string input;
	int listSize = 0;
  while(input!="quit"){
	getline(cin, input);
	if(input=="quit")
		return 0;
	else if(input=="print"){
		Node* temp = head;
		int nodeNum = 1;
		while(temp!=NULL){
			cout<< nodeNum<<" " <<temp->text<< "\n";
			temp=temp->next;
			nodeNum++;
		}
	}
	else{
	int inputNum = 0;
	string command = "";
	string command2 = "";
	string command3 = "";
	for(auto x : input){
		if(x=='\"'){

		}
		else if(x==' '){
			if(inputNum>=1 && (command == "insertEnd" || command == "search")){
				command2=command2+x;
			}
			else if(inputNum>1){
					command3=command3+x;
			}
				inputNum++; 
		}
		else if(inputNum==0){
			command=command+x;
		}
		else if(inputNum==1 || command == "insertEnd" || command == "search"){
			command2=command2+x;
		}
		else{
			command3=command3+x;
		}
	
	}

	if(command == "insert"){
		int position = 0;
		try{
			position = stoi(command2);
		}
		catch(...){
			continue;
		}
		Node* insertion = new Node();
		insertion->text=command3;
		if(position == 1){
			insertion->next=head;
			head=insertion;
			listSize++;
		}
		else if (position>listSize+1)
		{
			
		}
		else if(position==listSize+1){
			Node* temp = head;
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=insertion;
			tail=insertion;
			listSize++;
		}
		else{
		Node* temp = head;
		int nodeNum = 1;
		while(temp->next!=NULL && nodeNum<position-1){
			temp=temp->next;
			nodeNum++;
		}

			insertion->next=temp->next;
			temp->next=insertion;
			listSize++;
		}
		}

	else if(command == "edit"){
		int position = stoi(command2);
		if(position>listSize & position>1){

		}
		else if(position==1){
			head->text=command3;
		}
		else if(position==listSize){
			Node* temp = head;
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->text=command3;
		}
		else{
		Node* temp = head;
		int nodeNum = 1;
		while(temp->next!=NULL & nodeNum<position-1){
			temp=temp->next;
			nodeNum++;
		}

		if(position==1){
		head->text=command3;
		}
		else{
		temp=temp->next; 
		temp->text=command3;
		}
		}
	}
	else if(command == "insertEnd"){
		if(listSize==0){
			head->text=command2;
			listSize++;
		}
		else{
		Node* insertion = new Node();
		insertion->text=command2;
		Node* temp = head;
		tail->next=insertion;
		tail = insertion;
		listSize++;
	}
			}


	else if(command == "delete"){
		int deletePosition = stoi(command2);
		int nodeNum = 1;
		nodeNum++;
		Node* temp = head;
		Node* current = head;
		if (deletePosition==1)
		{
			if(head->next!=NULL){
				Node * deleteNode = head;
				head = head->next;
				delete deleteNode;
				listSize--;
			}
			else{
				head->text="";
				listSize--;
			}
		}
		else if(deletePosition>listSize){

		}
		else if(deletePosition==listSize){
			bool begin = false;
			while(temp->next!=NULL){
				if(begin){
					current=temp;
				}
				else{
					begin = true;
				}
				temp=temp->next;
			}
			current->next=NULL;
			delete temp;
			listSize--;
		}
		else{
		while(temp->next!=NULL & nodeNum<deletePosition){
			temp=temp->next;
		}
		Node * deleteNode = temp->next;
		temp->next=temp->next->next;
		listSize--;
		delete deleteNode;
	}
	}
	else if(command == "search"){
		bool textSearch = false;
		int nodeNum = 1;
		int textFinder = -1;
		Node* temp = head;
		textFinder = temp->text.find(command2);
		if(textFinder>-1){
			cout<< nodeNum << " " << temp->text << "\n";
			textSearch = true;
		}
		textFinder = -1;
		while(temp->next!=NULL){
			temp=temp->next;
			textFinder = temp->text.find(command2);
			nodeNum++;
			if(textFinder>-1){
			cout<< nodeNum << " " << temp->text << "\n";
			textSearch = true;
			}
			textFinder = -1;
		}
		if(textSearch==false){
			cout<<"not found"<< "\n";
		}
		
	}
	}
  }
}