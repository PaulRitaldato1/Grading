#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

struct node{
	string data;
	node *next;
};
class linkedList{
public:
	node *head, *tail;
	linkedList(){
		head = NULL;//declare head and tail
		tail = NULL;
	}
	void insertEnd(string str){//inserts statement at end of list
		node *temp = new node;
		temp->data = str;
		temp->next = NULL;
		if (head == NULL){//if its empty put in front and set both head and tail equal to the new node
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else{
			tail->next = temp;//puts statement in tail spot
			tail = temp;
		}
	}
	void print(){//iterates through list and prints
		node *temp = new node;
		temp = head;
		int c = 1;
		while (temp != NULL){
			cout << c << " " << temp->data << "\n";
			temp = temp->next;
			c++;
		}
	}
	void search(string input) {//finds statement in the list
		node *temp = new node;
		temp = head;
		bool flag = false;
		int c = 1;
		while (temp != NULL) {//iterating through list
			if (temp->data.find(input) != string::npos) {
				cout << c << " " << temp->data << "\n";
				flag = true;//shows that the statement is actually in the list
			}
			temp = temp->next;
			c++;
		}
		if (flag==false)cout << "not found" << endl;//if not found in list
	}
	void edit(int pos, string str){//just calls to the delete and insert functions because thats all edit really does
		deletePos(pos);
		insert(pos, str);
	}
	bool validIndex(int index) {//checks if index is valid
		node *curr = head;
		int length = 0;
		while (curr) {
			curr = curr->next;
			length++;
		}
		if (length + 1 >= index) {
			return true;
		}
		else {
			return false;
		}
	}
	void insert(int index, string ins) {//inserts node at any point in the list
		node *addNode = new node;
		addNode->data = ins;
		if (index == 1) {//puts in front if user requests
			addNode->next = head;
			head = addNode;
		}
		else if (validIndex(index)) {
			int count = 1;
			node *curr = head;
			while (count < index - 1) {
				curr = curr->next;
				count++;
			}
			node *nextNode = curr->next;
			curr->next = addNode;
			addNode->next = nextNode;
		}

	}
	void deletePos(int pos){//deletes position of user request
		if (head == NULL)return;
		node *temp = head;
		if (pos == 1){
			head = temp->next;
			free(temp);
			return;
		}
		for (int i = 1; temp != NULL && i < pos - 1; i++)temp = temp->next;
		if (temp == NULL || temp->next == NULL)return;
		node *next = temp->next->next;
		free(temp->next);
		temp->next = next;
	}
};

int main() {
	linkedList doc;//declare list
	string command;
	bool flag = true;
	while (flag == true) {//iterates until quit
		getline(cin,command);
		if (command.substr(0,11)=="insertEnd \""&&command.substr(command.length()-1)=="\"") {//checks that ONLY insertEnd is put in
			int pos = command.find("\"");//finds first instance of quote
			command.pop_back();//gets rid of last quoattion mark
			doc.insertEnd(command.substr(pos + 1));
		}
		else if (command.substr(0, 6) == "insert"&&isdigit(command.at(7))&&command.substr(command.length() - 1) == "\""&&command.at(9)=='"') {//finds the number for insert and the statement
			int pos = command.find("\"");
			command.pop_back();
			doc.insert(stoi(command.substr(7,1)),command.substr(pos + 1));
		}
		else if (command.substr(0, 8) == "search \""&&command.substr(command.length() - 1) == "\"") {//searches
			int pos = command.find("\"");
			command.pop_back();
			doc.search(command.substr(pos + 1));
		}
		else if (command.substr(0, 5) == "print"&&command.length() < 6) {//prints
			doc.print();
		}
		else if (command.substr(0, 6) == "delete"&&isdigit(command.at(7))) {//delets at pt but if double didgit is put in, it accounts for it
			if (command.length()>6)doc.deletePos(stoi(command.substr(7, 2)));
			else {
				doc.deletePos(stoi(command.substr(7, 1)));
			}
		}
		else if (command.substr(0, 4) == "edit"&&isdigit(command.at(5)) && command.substr(command.length() - 1) == "\""&&command.at(7) == '"') {//calls to edit
			int pos = command.find("\"");
			command.pop_back();
			doc.edit(stoi(command.substr(5, 1)), command.substr(pos + 1));
		}
		else if (command.substr(0, 4) == "quit"&&command.length() < 5) {//ends program
			flag = false;
		}
	}
}