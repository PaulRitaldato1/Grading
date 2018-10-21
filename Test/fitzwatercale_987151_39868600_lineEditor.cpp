#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node{
	string data;
	Node* next;

	//Node Constructor
	Node(string dataToAdd){
		data = dataToAdd;
	}
};

//LinkedList class
class linkedList{
private:
	Node* head;
	Node* current;

public:
	linkedList(){
		head = NULL;
		current = NULL;
	}

	Node* traverseToIndex(Node* head, int index);
	void InsertAtIndex(int index, string dataToAdd);
	void InsertAtEnd(string dataToAdd);
	void Delete(int index);
	void Replace(int index, string newData);
	void Search(string dataToFind);
	void Print();
};


//Function to traverse through a list
Node* linkedList::traverseToIndex(Node* start, int index){
	if(index == 0)
		return start;

	//If index is larger than the list's max index
	if(start->next == NULL)
		return NULL;

	//Recursively traverse the list
	return traverseToIndex(start->next, index - 1);
}

//insert Function
void linkedList::InsertAtIndex(int index, string dataToAdd){
	current = head;

	Node* newNode = new Node(dataToAdd);
	
	//If there is no head yet and the index is 0
	if(head == NULL && index == 0){
		head = newNode;
		return;
	}
	
	//Set current to the node before the index
	current = traverseToIndex(head, index - 1);

	//If the index is larger than the list return
	if(current == NULL)
		return;
	

	//Replace the node
	newNode->next = current->next;
	current->next = newNode;
}


//insertEnd Function
void linkedList::InsertAtEnd(string dataToAdd){
	current = head;

	Node* newNode = new Node(dataToAdd);
	
	//If head is there is no head yet create one
	if(head == NULL){
		head = newNode;
		return;
	}

	//Traverse the list
	while(current->next != NULL){
		current = current->next;
	}

	//Add node at end
	current->next = newNode;
}

//delete function
void linkedList::Delete(int index){
	//If deleting the head
	if(index == 0){
		if(head != NULL)
			head = head->next;
		return;
	}

	//If head is null
	if(head == NULL)
		return;

	//Set current to node before the node that will be deleted
	current = traverseToIndex(head, index - 1);

	//If the index is larger than the maxx list index
	if(current->next == NULL)
		return;
	
	//Delete the node
	current->next = current->next->next;
}


//replace Function
void linkedList::Replace(int index, string newData){
	current = traverseToIndex(head, index);
	
	current->data = newData;
}

//edit Function
void linkedList::Search(string dataToFind){
	current = head;

	//Set a flag for if match was found
	bool flag = false;

	//Go through each node and search for substring
	for(int lineNumber = 1; current != NULL; current = current->next, lineNumber++){

		if(current->data.find(dataToFind) != -1){
			cout << lineNumber << " " << current->data << endl;
			flag = true;
		}
	}

	if(!flag)
		cout << "not found" << endl;
}


//print Function
void linkedList::Print(){
	current = head;

	//go through each node printing them out and keeping a count
	for(int lineNumber = 1; current != NULL; current = current->next, lineNumber++){
		cout << lineNumber << " " << current->data << endl;
	}
}


int main(){
	linkedList doc;

	string input = " ";

	bool progRun = true;

	while(progRun){
		//Get the input line
		getline(cin, input);
		
		//get the command from the string
		string command = input.substr(0, input.find(' '));

		if(command == "insertEnd"){
			//Get the string between the quotes
			string dataToAdd = input.substr(input.find('\"') + 1);
			dataToAdd = dataToAdd.substr(0, dataToAdd.length() - 1);

			doc.InsertAtEnd(dataToAdd);
		}

		else if(command == "insert"){

			//Get the index number
			string index = input.substr(input.find(' '));

			//Get the string between the quotes
			string dataToAdd = input.substr(input.find('\"') + 1);
			dataToAdd = dataToAdd.substr(0, dataToAdd.length() - 1);

			doc.InsertAtIndex(stoi(index) - 1, dataToAdd);
		}

		else if(command == "print"){
			doc.Print();
		}

		else if(command == "search"){
			//Get the string between the quotes
			string dataToAdd = input.substr(input.find('\"') + 1);
			dataToAdd = dataToAdd.substr(0, dataToAdd.length() - 1);

			doc.Search(dataToAdd);
		}

		else if(command == "delete"){
			doc.Delete(stoi(input.substr(input.find(' ') + 1)) - 1);
		}

		else if(command == "edit"){
			//Get the index number
			string index = input.substr(input.find(' '), input.find(' '));

			//Get the string between the quotes
			string dataToAdd = input.substr(input.find('\"') + 1);
			dataToAdd = dataToAdd.substr(0, dataToAdd.length() - 1);

			doc.Replace(stoi(index) - 1, dataToAdd);
		}

		else if(command == "quit")
			progRun = false;
	}	

	return 0;
}