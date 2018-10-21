#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std


//Basic node class
; class Node {
public:
	string data;
	Node * next;
};


//Linked list class with size for later use
class LinkedList {
private:
	int size;
	Node * head = NULL;
	Node * tail = NULL;
public:
	void append(string value);
	void add(int index, string value);
	void remove(int index);
	void quickAppend(string value);
	string get(int index);
	void print();
	int edit(int index, std::string value);
	std::string search(std::string value);
	int sizeList();
};


int LinkedList::sizeList() {
	return size;
}

//Useless for this project, but a basic add to the end of the list
void LinkedList::append(string value) {
	if (head == NULL) {
		head = new Node();
		head->data = value;
		size++;
		return;
	}
	Node * temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new Node();
	temp->next->data = value;
	size++;
}



//Uses the tail to add things to the end of the list
void LinkedList::quickAppend(string value) {
	if (head == NULL) {
		head = new Node();
		head->data = value;
		tail = head;
		size++;
		return;
	}
	tail->next = new Node();
	tail->next->data = value;
	tail = tail->next;
	size++;
}

//Gets whatever value in the list, basic functionality for the list
string LinkedList::get(int index) {
	if (index > size) {
		return "";
	}
	Node * temp = head;
	for (int i = 0; i<index; i++) {
		temp = temp->next;
	}
	return temp->data;
}


//Adds whatever value at the particular index
void LinkedList::add(int index, string value) {
	//Adds the the beginning of the list
	if (index == 0) {
		Node * newNode = new Node();
		newNode->data = value;
		newNode->next = head;
		head = newNode;
		size++;
		return;
	}
	//Checks to see if its at the end of the index
	if (index == size) {
		Node * newNode = new Node();
		newNode->data = value;
		tail->next = newNode;
		tail = newNode;
		size++;
		return;
	}
	//Otherwise adds it normally
	Node * current = head;
	for (int i = 0; i<index - 1; i++) {
		current = current->next;
	}
	//Checks to see if out of bounds
    if (current == NULL) {
		return;
	}
	Node * newNode = new Node();
	newNode->data = value;
	newNode->next = current->next;
	current->next = newNode;
	size++;

}

//This method gave me way too much trouble on Stepik
void LinkedList::remove(int index) {
	//Checks the beginning stuff
	if (head == NULL)
		return;
	if (head->next == NULL && index == 0) {
		head == NULL;
	}

	//Removes the begining node
	if (index == 0) {
		Node * temp = head->next;
		delete head;
		head = temp;
		size--;
		return;
	}

	//Iterates through the list to the index
	Node * current = head;
	int i = 0;
	while ( i<index-1) {
		current = current->next;
		i++;
	}
	//Checks to see if out of bounds
	if (current->next== NULL)
		return;

	//Removes at what the index is
	Node * temp = current->next;
	if (temp == tail) {
		tail = current;
	}
	//Checks if out of bounds
    if(temp==NULL)
        return;
	current->next = temp->next;
	delete temp;
	size--;
}


//Simple print out 
void LinkedList::print() {
	if (head == NULL) {
		cout << "Head is NUll" << endl;
		return;
	}
	Node * temp = head;
	int i = 1;
	while (temp != NULL) {
		std::cout << i << " " << temp->data << endl;
		i++;
		temp = temp->next;
	}
}


//Edits the line at the index
int LinkedList::edit(int index, string value) {
	if (index > size) {
		return -1;
	}
	Node * temp = head;
	int i = -1;
	//Goes to the right index otherwise edits 
	while (temp->next != NULL && i != index) {
		i++;
		if (index == i) {
			temp->data = value;
			return 0;
		}
		temp = temp->next;

	}
	return -1;
}


//Searches through 
string LinkedList::search(string value) {
	Node*temp = head;
    bool flag = false;
	int i = 1;
	while (temp != NULL) {
		if (temp->data.find(value) != -1) {
			cout << i << " " << temp->data << endl;
            flag = true;
		}
		temp = temp->next;
		i++;
	}
    if(!flag)
        cout<<"not found"<<endl;
	return "";
}





vector<std::string> parseCommand(string command) {
	//Creates the positions points to make substrings
	int quotationLocation;
	int whiteSpaceIndex;
	int lastQuotationLocation;
	vector<string> commandList;
	quotationLocation = command.find("\"");
	lastQuotationLocation = command.find_last_of("\"");
	whiteSpaceIndex = command.find(" ");
	
	//Checks to see if blank statement
	if (command.length() == 0) {
		commandList.push_back("quit");
	}
	//Checks to see if the command is a single line
	if (quotationLocation == -1 && whiteSpaceIndex == -1 && command.length() != 0) {
		commandList.push_back(command);
		return commandList;
	}

	//Checks to see if missing quotations
	if (quotationLocation == lastQuotationLocation && quotationLocation != -1) {
		commandList.push_back("ERROR");
		return commandList;
	}

	//Sees the command is two arguments without a value
	if (quotationLocation == -1 && whiteSpaceIndex != -1) {
		commandList.push_back(command.substr(0, whiteSpaceIndex));
		commandList.push_back(command.substr(whiteSpaceIndex + 1, command.length() - 1));
	}
	else {
		//Parses the rest of the command by whitespace
		while (quotationLocation>whiteSpaceIndex && whiteSpaceIndex != -1) {
			commandList.push_back(command.substr(0, whiteSpaceIndex));
			command = command.substr(whiteSpaceIndex + 1, command.size());
			whiteSpaceIndex = command.find(" ");
			quotationLocation = command.find("\"");
			lastQuotationLocation = command.find_last_of("\"");
		}
		command = command.substr(quotationLocation + 1, lastQuotationLocation - 1);
		commandList.push_back(command);
	}

	return commandList;
}

int main() {
	int index;
	string command = "initialized";
	vector<string> commandList;
	LinkedList linkedList;
	int caseNumber = -1;
	//I make a switch statement to assign a number to each command a bit redundant yes I realize
	while (command != "quit") {
		getline(cin, command);
		//The command list is made so that the commandlist works depending on the command
		commandList = parseCommand(command);
		if (commandList[0].compare("insertEnd") == 0) {
			if (commandList.size() == 2)
				caseNumber = 1;
		}
		if (commandList[0].compare("insert") == 0) {
			if (commandList.size() == 3)
				caseNumber = 2;
		}
		if (commandList[0].compare("delete") == 0) {
			if (commandList.size() == 2)
				caseNumber = 3;
		}
		if (commandList[0].compare("edit") == 0) {
			if (commandList.size() == 3)
				caseNumber = 4;
		}
		if (commandList[0].compare("print") == 0) {
			caseNumber = 5;
		}
		if (commandList[0].compare("search") == 0) {
			if (commandList.size() == 2)
				caseNumber = 6;
		}
		if (commandList[0].compare("quit") == 0) {
			caseNumber = 7;
		}
		switch (caseNumber) {
		case 1:
			linkedList.quickAppend(commandList[1]);
			break;
		case 2:
            if(stoi(commandList[1])<=linkedList.sizeList())
			linkedList.add(stoi(commandList[1]) - 1, commandList[2]);
			break;
		case 3:
			if (stoi(commandList[1]) <= linkedList.sizeList())
				linkedList.remove(stoi(commandList[1]) - 1);
			break;
		case 4:
			if (commandList[1].size() == 1)
				int found = linkedList.edit(stoi(commandList[1]) - 1, commandList[2]);
			break;
		case 5:
			linkedList.print();
			break;
		case 6:
			linkedList.search(commandList[1]);
			break;
		case 7:
			command = "quit";
			break;
		default:
			std::cout << "Sorry this command is not recognized" << endl;
			break;
		}
		caseNumber = -1;
	}
	return 0;
}