//============================================================================
// Name        : LIneEditor.cpp
// Author      : Elton Jacob
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

struct node {
	string line;
	node* next;
};

class list {
private:
	node *head, *tail;
public:
list(){
		head=NULL;
		tail=NULL;
	}

void insertEnd(string value){
	node *temp=new node;
	temp->line=value;
	temp->next=NULL;
	//Checking if the header is empty
	if(head==NULL){
		head=temp;
		tail=temp;
	}else {
		tail->next=temp;
		tail=temp;
	}
}
void print(){
	node *temp=new node;
	int counter=1;
	temp=head;
	while(temp!=NULL){
		cout<<counter<<" "<<temp->line<<"\n";
		counter++;
		temp=temp->next;
	}
}

void insertAtLocation(int position, string value){
	node *before=new node;
		node *current=new node;
		node *temp=new node;
		current=head;
		int numbernodes=numberNodes();
		if(numbernodes>=position){
			for(int i=1;i<position;i++){
					before=current;
					current=current->next;
				}
				temp->line=value;
				before->next=temp;
				temp->next=current;
		}else if(numbernodes+1==position) {
			insertEnd(value);

		}



}
void deleteAtLocation(int position){
	int numbernodes=numberNodes();
	node *current=new node;
	node *before=new node;
	current=head;
	if(position>numbernodes){
		return;
	}


	for(int i=1;i<position;i++){
		before=current;
		current=current->next;
	}
	before->next=current->next;
}

void editAtLocation(int position,string value){
	node *current=new node;
	node *before=new node;
	current=head;
	for(int i=1;i<position;i++){
		before=current;
		current=current->next;
	}
	current->line=value;

}
void searchText(string value){
	node *temp=new node;
	int counter=1;
	temp=head;
	int numbernode=numberNodes();
		while(temp!=NULL){
				if(counter==numbernode && temp->line.find(value) > temp->line.length()){
					cout<<"not found"<<endl;

				}else if(temp->line.find(value) <= temp->line.length()){
					cout<<counter<<" "<<temp->line<<"\n";

				}
				counter++;
				temp=temp->next;

			}

}

void quit(){
	head=NULL;
	tail=NULL;
}

int numberNodes(){
	int number=0;
	node *temp=new node;
	temp=head;
	while(temp!=NULL){
		temp=temp->next;
		number++;
	}

	return number;
}

};

int main() {
	list lineEditor;


			lineEditor.insertEnd("now is the time");
			lineEditor.insertEnd("for all good men");
			lineEditor.insertEnd("to come to the aid of their country");
			lineEditor.print();
			lineEditor.searchText("come to the aid");
			lineEditor.quit();
			cout<<" "<<endl;


			lineEditor.insertEnd("now is the time");
					    lineEditor.insertEnd("for all good men");
					    lineEditor.insertEnd("to come to the aid of their country");
				        lineEditor.print();
				        lineEditor.editAtLocation(2,"for all good people");
				        lineEditor.print();

				        lineEditor.quit();
			        			cout<<" "<<endl;

			lineEditor.insertEnd("now is the time");
					    lineEditor.insertEnd("for all good people");
					    lineEditor.insertEnd("to come to the aid of their country");
				        lineEditor.deleteAtLocation(2);
				        lineEditor.print();
				        lineEditor.insertAtLocation(2, "for all good people");
				        lineEditor.print();

				        lineEditor.quit();
				        			cout<<" "<<endl;


			lineEditor.insertEnd("hello world");
					    lineEditor.insertEnd("how are you doing");
				        lineEditor.insertEnd("hello world");
				        lineEditor.searchText("hello world");

				        lineEditor.quit();
				        	cout<<" "<<endl;
			lineEditor.insertEnd("hello world");
					    lineEditor.insertEnd("how are you doing");
				        lineEditor.insertEnd("hello world");
				        lineEditor.searchText("hello pluto");
				        lineEditor.print();

				        lineEditor.quit();
				        	cout<<" "<<endl;
			lineEditor.insertEnd("Hello world");
					    lineEditor.insertEnd("how are you doing");
				        lineEditor.insertAtLocation(2,"hello pluto");
				        lineEditor.print();
				        lineEditor.deleteAtLocation(2);
				        lineEditor.print();

				        lineEditor.quit();
				        	cout<<" "<<endl;


			lineEditor.insertEnd("now is the time");
					    lineEditor.insertEnd("for all good men");
					    lineEditor.insertEnd("to come to the aid of their country");
				        lineEditor.deleteAtLocation(4);
				        lineEditor.print();

				        lineEditor.insertAtLocation(4,"Patrick Henry or Charles Weller");
				        lineEditor.print();
				        lineEditor.insertAtLocation(6,"it was neither");
				        lineEditor.print();

				        lineEditor.quit();
				        cout<<" "<<endl;





}
