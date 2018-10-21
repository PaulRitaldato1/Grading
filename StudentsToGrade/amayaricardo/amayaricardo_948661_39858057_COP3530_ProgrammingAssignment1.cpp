//============================================================================
// Name        : COP3530_ProgrammingAssignment1.cpp
// Author      : Ricardo L. Amaya
// Description : Programming Assignment 1
//============================================================================

#include <iostream>
using namespace std;

struct Node{
	string line = "";
	Node *next = NULL;
};

class LinkedList{
private:
	Node *head, *tail;
public:
	LinkedList(){
		head = NULL;
		tail = NULL;
	}
	int getSize(){
		if(head == NULL){
			return 0;
		} else {
			Node* current = head;
			int counter = 0;
			while (current != NULL){
				counter++;
				current = current->next;
			}
			return counter;
		}

	}
	void insertEnd(string line){
		if (line.length() > 80){
			cout<<"Line cannot be more than 80 characters. Please try again"<<endl;
			return;
		}
		Node *tempNode = new Node;
		tempNode->line = line;
		if (head == NULL){
			head = tempNode;
			tail = head;
		}
		else{
			tail->next = tempNode;
			tail = tempNode;
		}
	}
	void pushToIndex(string line, int index){
		if (line.length() > 80){
					cout<<"Line cannot be more than 80 characters. Please try again"<<endl;
					return;
		}
		int counter = 1;
		Node *tempNode = new Node;
		tempNode->line = line;
		if ((head == NULL) & (index == 1)){
			head = tempNode;
			tail = head;
			return;
		}
		Node* current = head;
		Node* previous = head;
		while(current!=NULL){
			if ((counter == index) & (counter == 1)){
				tempNode->next = head;
				head = tempNode;
				return;
			}
			else if (counter == index){
				previous->next = tempNode;
				tempNode->next = current;
				return;
			}

			counter++;
			previous = current;
			current = current->next;
		}
		if (index == counter)
			previous->next = tempNode;
	}
	void deleteAtIndex(int index){
		int counter = 1;
		Node* current = head;
		Node* previous = head;
		while(current!=NULL){
			if((counter == index) & (index == 1)){
				head = head->next;
				return;
			}
			else if (counter == index){
				previous->next = current->next;
				return;
			}

			counter++;
			previous = current;
			current = current->next;
		}
	}
	void editAtIndex(string newLine, int index){
		if (newLine.length() > 80){
					cout<<"Line cannot be more than 80 characters. Please try again"<<endl;
					return;
		}
		int counter = 1;
		Node* current = head;
		while(current!=NULL){
			if(counter == index){
				current->line = newLine;
				return;
			}

			counter++;
			current = current->next;
		}
	}
	void searchForText(string text){
		int counter = 1;
		bool found = false;
		Node* current = head;
		size_t check;
		while(current!=NULL){
			check = current->line.find(text);
			if(check != string::npos){
				cout<<counter<<" "<<current->line<<endl;
				found = true;
			}

			counter++;
			current = current->next;
		}
		if (found == false)
			cout<<"not found"<<endl;
	}
	void parseInstruction(string line){
		size_t check;
		check = line.find("insertEnd");
		if (check != string::npos){
			if ((line[10] != '"') || (line[line.length()-1] != '"')){
				return;
			}
			string text = line.substr(11);
			text = text.substr(0, text.length()-1);
			insertEnd(text);

			return;
		}
		check = line.find("insert");
		if (check != string::npos){
			string temp = line.substr(line.find(' ')+1);
			temp = temp.substr(0,temp.find(' '));
			int index = -1;
			try {
				index = stoi(temp);
			} catch(...){
				return;
			}
			temp = "";
			size_t check = line.find('\"');
			if (check != string::npos){
				temp = line.substr(check+1);
				check = temp.find('\"');
				if (check != string::npos){
					temp = temp.substr(0, check);
				}
				else
					return;
			}
			else
				return;
			pushToIndex(temp, index);
			return;

		}
		check = line.find("delete");
		if (check != string::npos){
			string temp = line.substr(line.find(' ')+1);
				temp = temp.substr(0,temp.find(' '));
				int index = -1;
				try {
					index = stoi(temp);
				}catch (...){
					return;
				}
				deleteAtIndex(index);
				return;
		}
		check = line.find("edit");
		if (check != string::npos){
			string temp = line.substr(line.find(' ')+1);
			temp = temp.substr(0,temp.find(' '));
			int index = -1;
			try {
				index = stoi(temp);
			}catch(...){
				return;
			}
			temp = "";
			size_t check = line.find('\"');
			if (check != string::npos){
				temp = line.substr(check+1);
				check = temp.find('\"');
				if (check != string::npos){
					temp = temp.substr(0, check);
				}
				else
					return;
			}
			else
				return;
			editAtIndex(temp, index);
			return;
		}
		check = line.find("print");
		if(check != string::npos){
			print();

			return;
		}
		check = line.find("search");
		if (check != string::npos){
			if ((line[7] != '"') || (line[line.length()-1] != '"')){
				return;
			}
			string text = line.substr(8);
			text = text.substr(0, text.length()-1);
			searchForText(text);

			return;
		}
		check = line.find("quit");
		if (check != string::npos){
			exit(0);
		}

	}
	void print(){
		Node* current = head;
		int counter = 1;
		while(current != NULL){
			cout<<counter++<<" "<<current->line<<endl;
			current = current->next;
		}
	}
};

int main() {

	LinkedList list;
	string input  = "";
	while(true){
		getline(cin, input);
		list.parseInstruction(input);
	}

	return 0;
}


