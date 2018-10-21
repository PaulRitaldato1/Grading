#include<bits/stdc++.h>
using namespace std;
//Alvin Guo
//COP3530 Project 1

//Creating Node struct
struct Node {
	string value;
	Node *next;
}*head;

//Declaration
struct Node* create(void);
void insertEnd(Node*, string);
void insert(Node*, int, string);
void edit(Node*, int, string);
void deleteNode(Node*, int);
void search(Node*, string);
void print(Node*);

class linkedList {
public:
	//The function needed for creatng new nodes.
	Node * create(string data) {
		Node *list = new Node;
		list->value = data;
		list->next = NULL;
		return(list);
	}

	//Inserting the new line at the end.
	void insertEnd(Node* list, string data) {
		Node* temp;
		temp = create(data);
		if (head == NULL) {//For the begining case
			head = temp;
		}
		else {
			while (list->next != NULL) {//Transverse the list to get to the end
				list = list->next;
			}
			list->next = temp;
		}
	}

	//Inserting a new line at any position
	void insert(Node* list, int pos, string data) {
		Node* temp = create(data);
		Node* previous = NULL;
		int k = 1;
		for (int i = 1; i < pos; i++) {//Transverse the list to get to the end
			previous = list;
			list = list->next;
		}
		if (previous == NULL) {//Base case
			temp->next = head;
			head = temp;
		}
		else {
			temp->next = list;
			previous->next = temp;
		}
	}

	//Deleting a node at a given position
	void deleteNode(Node* list, int pos) {
		Node* previous = NULL;
		Node *temp;
		for (int i = 1; i < pos; i++) {//Transverse the list to get to the end
			previous = list;
			list = list->next;
		}
		if (previous == NULL) {
			temp = list;
			head = head->next;
		}
		else {
			temp = list;
			previous->next = list->next;
		}
		int k = 1;//Used to see if the value is inbound
		while (list != NULL) {
			k++;
		}
		if (k == pos) {
			delete temp;
		}
	}

	//Replacing a node with a new value
	void edit(Node* list, int pos, string data) {
		for (int i = 1; i < pos; i++) {
			list = list->next; //Transverse the list to get to the end
		}
		list->value = data; //Entering data into the list data space
	}

	//Used to search a node given the data
	void search(Node* list, string data)
	{
		int i = 0;
		int pos = 1;
		while (list != NULL)
		{
			if (list->value.find(data) != -1) //Used to find if the data is in the list
			{
				cout << pos << " " << list->value << endl;
				i++;
			}
			list = list->next;
			pos++;
		}
		if (i == 0) { //Means that no node value was equal to the data
			cout << "not found" << endl;
		}
	}

	//Prints the node
	void print(Node* list) {
		int pos = 1;
		while (list) {
			cout << pos << " " << list->value << endl;
			list = list->next;
			pos++;
		}
	}
};

int main() {
	//Variables to store text, input, index, and position
	string input;
	string index;
	string temp;
	stringstream str;
	int i;
	int pos;
	linkedList link;
	while (1) {
		getline(cin, input);
		if (input == "quit") {
			break;
		}
		else if (input.substr(0, 9) == "insertEnd") { //Checking what command is inputted
			temp = input.substr(11); //Finds the text inside the quotes for data
			temp.pop_back();
			link.insertEnd(head, temp);//Calling the function
		}
		else if (input.substr(0, 6) == "insert") { //Checking what command is inputted
			pos = input.find(" ", 7); //Finds the position that is wanted
			index = input.substr(7, pos - 7); // The substring that is equal to data
			str << index;
			str >> i;
			str.clear();
			temp = input.substr(pos + 2);
			temp.pop_back();
			link.insert(head, i, temp);//Calling the function
		}
		else if (input.substr(0, 4) == "edit") { //Checking what command is inputted
			pos = input.find(" ", 5); //Finds the position that is wanted
			index = input.substr(5, pos - 5); //The substring that is equal to data
			str << index;
			str >> i;
			str.clear();

			temp = input.substr(pos + 2);
			temp.pop_back();
			link.edit(head, i, temp); //Calling the function
		}
		else if (input.substr(0, 6) == "delete") { //Checking what command is inputted
			index = input.substr(7);
			str << index;
			str >> i;
			str.clear();
			link.deleteNode(head, i);//Calling the function
		}
		else if (input.substr(0, 6) == "search") { //Checking what command is inputted
			temp = input.substr(8);  //Finds the text inside the quotes for data
			temp.pop_back();
			link.search(head, temp);//Calling the function
		}
		else if (input == "print") { //Checking what command is inputted
			link.print(head);//Calling the function
		}
	}
	return 0;
}
