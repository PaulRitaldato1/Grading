#include<string>
#include<iostream>
using namespace std;

//Linked list implementation:
struct Node {
	string value;
        Node* next;
};

class LinkedList {
    private: 
        Node* head;
	    Node* tail;
    public: 
        LinkedList();
        int size = 0;
        int getSize();
        void printList();
	void searchList(string searchString);
	void editNode(string editString, int index);
        void insert(string inputString, int index);
        void deleteNode(int index);
};
    
LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;
}

//Line editor implemenation
int LinkedList::getSize() {
    return size;
}

void LinkedList::printList() {
	Node* iterator = head;
	int index = 0;
    	while (iterator != NULL) {
		cout << index + 1 << " " << iterator->value <<endl;
		iterator = iterator->next;
		index++;
	}
}

void LinkedList::searchList(string searchString) {
	Node* iterator = head;
	int index = 0;
    	bool isInList = false;
	while (iterator != NULL) {
		string strInNode = iterator->value;
		string strToFind = searchString;
		if (strInNode.find(strToFind) != string::npos) { //found instance of string
			cout << index + 1 << " " << iterator->value << endl;
            		isInList = true;
        	}
		iterator = iterator->next;
		index++;
	}
    if (!isInList) 
        cout << "not found" << endl;
}

void LinkedList::editNode(string editString, int index) {
	Node* iterator = head;
	int listIndex = index - 1;
	for (int i = 0; i < listIndex; i++) { //iterate up to the index
		iterator = iterator->next;
	}
	iterator->value = editString;
}

void LinkedList::insert(string inputString, int index) {
    Node* nodeToAdd = new Node;
    nodeToAdd->value = inputString;
    Node* end = tail;
    if (index-1 == 0) { //add at head
        nodeToAdd->next = head;
        head = nodeToAdd;
        size++;
    }
    else {
        Node* curr = head;
        for (int i = 1; i < index-1; i++) {
            curr = curr->next;
        }
        Node* next = curr->next;
        curr->next = nodeToAdd;
        nodeToAdd->next = next;
        size++;
    }
}

void LinkedList::deleteNode(int index) {
    Node* temp = head;
    Node* prev = head;
    Node* curr = prev->next;
    if (index-1 == 0) { //delete first node
        head = head->next;
        delete(temp);
        size--;
    }
    else {
        for (int i = 0; i <= index - 3; i++) {
             prev = curr;
             curr = curr->next;
        }
        prev->next = curr->next;
        delete(curr);
        size--;
    }
}

//Code to implement and invoke line editor:
int main()
{
    LinkedList testList;
    string line;
    string inputLine;
    while(getline(cin, line)) {
        inputLine = line.substr(line.find("\"") + 1, line.length()-line.find("\"")-2);
        if (inputLine.length() > 80) { //line over 80 characters
            cout << "";
        }
        else { //line length acceptable
        	if (line.find("insertEnd") != string::npos) {
            		testList.insert(inputLine, testList.getSize()+1);
        	}
        	else if (line.find("insert") != string::npos) {
            		string index;
            		for (int i = 0; i < line.find("\""); i++)
                	if (isdigit(line.at(i))) //find all integers in line and concatenate into string index
                    		index += line.at(i);
            		int numIndex = stoi(index); //cast string as integer
            		if (numIndex > testList.getSize()+1) { //Inserting at index past one node after the end of the list
                		cout << ""; //do nothing
            		}
            		else 
                		testList.insert(inputLine, numIndex);
        	}
        	else if (line.find("print") != string::npos) {
            		testList.printList();
        	}
        	else if (line.find("search") != string::npos) {
            		testList.searchList(inputLine);
        	}
        	else if (line.find("delete") != string::npos) {
            		string index = line.substr(line.find(" ")+1); //looking for index after "delete" keyword
            		int numIndex = stoi(index);
            		if (numIndex > testList.getSize()) //deleting index that is out of bounds
                		cout << "";
            		else
                		testList.deleteNode(numIndex);
        	}
        	else if (line.find("edit") != string::npos) {
            		string index;
            		for (int i = 0; i < line.find("\""); i++)
                		if (isdigit(line.at(i))) //find all integers in line and concatenate into string index
                    			index += line.at(i);
            		int numIndex = stoi(index); //cast string as integer
            		if (numIndex > testList.getSize())
                		cout << "";
            		else
                		testList.editNode(inputLine, numIndex);
        	}
        	else if (line.find("quit") != string::npos) {
            		return 0;
        	}
        }
    }
}