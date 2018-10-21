/*
 * Created by Zahin Ibnat
 * COP3530: Data Structures and Algorithms
 * Programming Assignment 1: Line Editor
 */

#include <iostream>

using namespace std;

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//node struct for the linked list
struct node{
	string data;
	struct node *next;
};

/*
 * linked list class that will contain all of the methods with what they do instead of being separated out.
 * this prevents the need to write LinkedList::(method).
 */
class LinkedList{
	//doubly linked list mainly for the addEnd method
	//private variables
private:
	node*head,*tail;
public:
	//constructor is listed after the class's methods
	LinkedList();
	//Method to add a node to the end of the linked list
	void addEnd(string dataInput){
		node *end = new node;
		end->data = dataInput;
		end->next = NULL;

		// If the linked list is empty then set head and tail to end
		if (head == NULL) {
			head = end;
			tail = end;
		} else {
			tail->next = end;
			tail = tail->next;
		}
	}
	//Method to add a node to a specific index within the linked list
	void addAtIndex(string dataInput, int index){
		node* temp = head;
		int count = 1;
		node* curr = new node;
		curr->data = dataInput;

		//If the index is that of the head
		if(index == 1){
			curr->next = temp;
		}else{
			while(temp!=nullptr){
				if(count==(index-1)){
					curr->next = temp->next;
					temp->next = curr;
				}
				temp = temp->next;
				count++;
			}
		}
	}
	//Method to delete node with given index from the linked list
	void deleteAtIndex(int index){
		node*temp = head;
		//If the linked list does not contain anything
		if(head==nullptr){
			return;
		}
		//If the index matches that of the head
		if (index == 1){
			head = temp->next;
			delete(temp);
			return;
		}
		//shifts all the items of the list to isolate the item needing to be deleted
		for(int i = 1; temp!=nullptr && i<index-1; i++){
			temp = temp->next;
		}
		//once the list runs out of nodes to pass
		if(temp==nullptr|| temp->next == nullptr){
			return;
		}
		//deleting the node
		node*next = temp->next->next;
		delete(temp->next);
		temp->next = next;
	}

	//Method to print the linked list
	void printList(){
		node * curr;
		curr = head;
		curr->data = head -> data;
		int count = 1;
		//prints the entire linked list to the end
		while (curr != nullptr){
			cout <<count<<' '<<curr->data << endl;
			curr = curr->next;
			count++;
		}
	}

	//Method to search for the specific string within the linked list
	void search(string dataInput){
		node*temp = head;
		int count = 1;
		bool success = false;
		//if there does not exist any data within the linked list
		if(head == nullptr){
			cout<<"not found";
		}
		while(temp!=nullptr){
			//retrieves the strings within the linked list
			string fullSentence = temp->data;
			//if the text fragment exists in the string retrieved from the linked list
			if(strstr(fullSentence.c_str(),dataInput.c_str())){
				cout<<count<<' '<<fullSentence<<endl;
				success = true;
			}
			temp = temp->next;
			count++;
		}
		//when the method reaches the end of the list and no string was found to contain the text fragment passed into the method
		if(temp==nullptr && success == false){
			cout<<"not found"<<endl;
		}
	}
};

//constructor for the linked list
LinkedList::LinkedList(){
	head = NULL;
	tail = NULL;

}

int main(){
	//linked list is initialized
	LinkedList editor;
	//the "option" is the keyword for which method the user wants the data to use/access
	string option = "";
	//the loop will go through all of the lines of the input
	while (getline(cin,option)){
		//these strings represent all the keywords for the methods
		string insertEnd("insertEnd");
		string insert("insert");
		string deleteNum("delete");
		string edit("edit");
		string print("print");
		string search("search");
		string quit("quit");
		//checks for the quotation marks
		string delimiter("\"");


		//if the option contains keyword "insertEnd"
		if(strstr(option.c_str(),insertEnd.c_str())){
			//checks if the quotation marks are in the input
			if(strstr(option.c_str(),delimiter.c_str())){
				//cuts the ending quotes
				string optionCut = option.substr(0,option.length()-1);
				//place: the index of the first character in quotations
				int place = option.find(delimiter) + 1;
				//isolates the sentence in quotations
				string text = optionCut.substr(place,(option.length())-1);
				editor.addEnd(text);
			}
		}

		//if the option contains keyword "insert"
		if(strstr(option.c_str(),insert.c_str())){
			//finds the integer indicating the index
			string integer = option.substr(7);
			//makes the number within the string an integer
			int value = atoi(integer.c_str());
			//follows the same system as before
			if(strstr(option.c_str(),delimiter.c_str())){
				string optionCut = option.substr(0,option.length()-1);
				int place = option.find(delimiter) + 1;
				string text = optionCut.substr(place,(option.length())-1);
				editor.addAtIndex(text,value);
			}
		}

		//if the option contains keyword "delete"
		if(strstr(option.c_str(),deleteNum.c_str())){
			string integer = option.substr(7);
			int value = atoi(integer.c_str());
			editor.deleteAtIndex(value);
		}

		//if the option contains keyword "edit"
		if(strstr(option.c_str(),edit.c_str())){
			string integer = option.substr(5);
			int value = atoi(integer.c_str());
			if(strstr(option.c_str(),delimiter.c_str())){
				string optionCut = option.substr(0,option.length()-1);
				int place = option.find(delimiter) + 1;
				string text = optionCut.substr(place,(option.length())-1);
				//passes the index to the delete method, and then passes the new text and the same index to the addAtIndex method
				editor.deleteAtIndex(value);
				editor.addAtIndex(text,value);
			}
		}

		//if option contains keyword "print"
		if(strstr(option.c_str(),print.c_str())){
			editor.printList();
		}

		//if option contains keyword "search"
		if(strstr(option.c_str(),search.c_str())){
			if(strstr(option.c_str(),delimiter.c_str())){
				string optionCut = option.substr(0,option.length()-1);
				int place = option.find(delimiter) + 1;
				string text = optionCut.substr(place,(option.length())-1);
				editor.search(text);
			}
		}
		//if option contains keyword "quit"
		if(strstr(option.c_str(), quit.c_str())){
			exit(EXIT_SUCCESS);
		}
	}
}

