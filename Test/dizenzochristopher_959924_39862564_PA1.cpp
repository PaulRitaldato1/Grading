//============================================================================
// Name        : PA1.cpp
// Author      : ChrisD
// Version     :
// Copyright   : Your copyright notice
// Description : Linked list of Strings
//============================================================================

#include <iostream>
using namespace std;

struct Node {
	public:
		std::string text;
		Node* next;
};

class StringedList{
private:
	Node *head,*tail;
	public:
		StringedList(){
			head = NULL;
			tail = NULL;
		}
		void insertEnd(string text){
			// Inserts text at the end of linked list
			Node* newNodie = new Node;
			newNodie->text = text;
			newNodie->next = NULL;
			// Made new Node, filled with values
			if (!tail){
				// If the Linked list is empty
				head = newNodie;
				tail = head;
				return;
			}
			// If the linked list isn't empty, add after tail
			tail->next = newNodie;
			tail = tail->next;
		}
		void insert(int index, string text){
			// Inserts Node at defined index
			Node* currentNode = head;
			Node* newNode = new Node;
			newNode->text = text;
			newNode->next = NULL;
			// Made a new Node, filled with values. Also made a pointer to iterate through to the right index
			for(int i = 2; i < index; i++){
				if (currentNode->next){
					// Check if there is a next node to jump to, if so then move until correct index is found
					currentNode = currentNode->next;
				}
			}
			// Insert new Node after the currentNode
			newNode->next = currentNode->next;
			currentNode->next = newNode;
		}
		void edit(int index, string text){
			// Finds the node at index, changes the text
			Node* currentNode = head;
			for (int i = 1; i < index ; i++){
				// Iterates through til found correct index
					currentNode = currentNode->next;
			}
			// Change text
			currentNode->text = text;
		}
		void deleteIndex(int index){
			// Finds node at correct index, and removes it
			if (index == 1){
				// if deleting the head
				Node* headNode = head;
				head = head->next;
				delete &headNode;
			}else{
				Node* previousNode = head;
				for (int i = 2; i < index;i++){
					// iterate through until correct Node is found at index
					previousNode = previousNode->next;
				}
				Node* currentNode = previousNode->next;
				previousNode->next = currentNode->next;
				delete &currentNode;
			}
		}
		void print(){
			// Prints all Nodes
			Node* currentNode = head;
			for (int i = 1; currentNode ; i++){
				cout <<  i << " " << currentNode->text << std::endl;
				currentNode = currentNode->next;
			}
		}
		void search(string text){
			// Searches each Node for substring
			Node* currentNode = head;
			bool found = false;
			for (int i = 1; currentNode; i++){
				if (currentNode->text.find(text) != string::npos){
					// If the substring doesn't exist in the currentNode text, then the find function returns npos
					cout << i << " " << currentNode->text << endl;
					found = true;
					// found is a boolean to hold whether a node was found or not
				}
				currentNode = currentNode->next;
			}
			if (!found){
				cout << "not found" << endl;
			}
		}
};

int main() {
	StringedList c;
	while(true){
		// Loop that only ends once "quit" is called and returns 0
		int temp,intIndex;
		string input,method,index,text;
		getline(cin, input);
		// Using get line to pull entire lines, then breaking them into parts
		method = input.substr(0,input.find(" "));
		// First part is the method, so breaks into substring that ends at the index of the first space
		if (method.compare("insertEnd") == 0){
		// Would use switch but c++ doesn't support switch statement for strings
			temp = input.find("\"");
			// temp hold value of first "
			text = input.substr(temp+1,input.find("\"",temp+1,input.length()));
			// Then breaks input into substring from the first " to the last "
			text.erase(text.end()-1);
			c.insertEnd(text);
		}else if (method.compare("insert") == 0){
			temp = input.find("\"");
			text = input.substr(temp+1,input.find("\"",temp+1,input.length()));
			text.erase(text.end()-1);
			// Same text methods as InsertEnd
			temp = input.find(" ");
			// for index, temp holds the first space
			index = input.substr(temp+1,input.length());
			// Then breaks into substring from the first space to the end
			index.erase(index.find(" "));
			// Then erases everything after the first space in the index string
			intIndex = stoi(index);
			// I used stoi to convert into an int for input in the insert function
			c.insert(intIndex,text);
		}else if (method.compare("delete") == 0){
			// split input into index, call function
			temp = input.find(" ");
			index = input.substr(temp+1,input.length());
			intIndex = stoi(index);
			c.deleteIndex(intIndex);
		}else if (method.compare("edit") == 0){
			// split input into index and text, then call function
			temp = input.find(" ");
			index = input.substr(temp+1,input.length());
			index.erase(index.find(" "));
			intIndex = stoi(index);
			temp = input.find("\"");
			text = input.substr(temp+1,input.find("\"",temp+1,input.length()));
			text.erase(text.end()-1);
			c.edit(intIndex,text);
		}else if (method.compare("print") == 0){
			c.print();
		}else if (method.compare("search") == 0){
			// Split input into text, then call function
			temp = input.find("\"");
			text = input.substr(temp+1,input.find("\"",temp+1,input.length()));
			text.erase(text.end()-1);
			c.search(text);
		}else if (method.compare("quit") == 0){
			// returns 0 to break loop
			return 0;
		}else{
			// if method wasn't understood then i messed up the typing so these were for error checking
			cout << "method is: " << method << endl ;
			cout << "beep-boop, does not compute" << endl;
		}
	}
}
