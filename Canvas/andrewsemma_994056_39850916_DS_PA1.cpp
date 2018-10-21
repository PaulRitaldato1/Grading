#include <string>
#include <iostream>
#include <sstream>

class List {
public:
	struct Node {
		//creates a node structure inside of the linked list object, as the list contains these nodes
		//next node starts as null until pointed to the correct next node
		Node* next = nullptr;
		//initializes the string that contains the line string of each node
		std::string lineVal = "";
	};
	List();
	//functions utilized
	void insertAtEnd(std::string text);
	void insertAtLine(std::string text, int index);
	void deleteLine(int index);
	void replaceLine(std::string, int index);
	void print();
	void search(std::string text);

private:
	//nodes used throughout to keep track in the linked list
	Node* head;
	Node* cur;
	Node* tail;
	Node* prev;
};

List::List() {
	//Initializes the head, cur, and tail nodes to null
	head = nullptr;
	cur = nullptr;
	tail = nullptr;
	prev = nullptr;
}

void List::insertAtEnd(std::string text) {
	//Inserts given text at the end of the document
	//Starts by checking if the line contains less than or equal to 80 characters
	if (text.length() > 80) {
		//substrings text to ignore characters after the 80th one
		text = text.substr(0, 80);
	}
	//creates a new node which will be inserted at the end depending on the size of the linked list currently
	Node* newNode = new Node();
	newNode->lineVal = text;
	if (head != nullptr) {
		//if there is already a list started with nodes, new node becomes the next node from the tail
		tail->next = newNode;
		//and the tail is now the new node
		tail = newNode;
		//tail->next becomes null as it is not pointing to anything
		tail->next = nullptr;
	}
	else {
		//else if there is no nodes to begin with, both the head and the tail are equal to the new node
		head = newNode;
		tail = newNode;
	}
}

void List::insertAtLine(std::string text, int index) {
	//Inserts given text at the specific index
	//creates a new node that will be inserted into the linked list at the specified index
	if (text.length() > 80) {
		//substrings text to ignore characters after the 80th one
		text = text.substr(0, 80);
	}
	Node* insert = new Node();
	insert->lineVal = text;
	cur = head;
	int position = 1;
	if (index == 1) {
		//if the new node is to be added in the first spot, the head becomes the new node and head->next equals the previous head
		head = insert;
		//cur = head at this statement
		head->next = cur;
	}
	else {
		while (cur->next != nullptr && position != index) {
			//find the spot in the list where the new node is to be inserted
			prev = cur;
			cur = cur->next;
			position++;
		}
		if (position == index) {
			//if the list is at the correct index to be inserted at, make prev->next point to the new node and have the new node's next point to the cur node
			prev->next = insert;
			insert->next = cur;
		}
		else if (position + 1 == index) {
			//otherwise it is being inserted at the end of the list, so cur->next is now pointing to the new node and the new node's next points to null
			cur->next = insert;
			insert->next = nullptr;
		}
	}

}

void List::deleteLine(int index) {
	//Deletes line at given index
	//creates a temporary node that will be used to delete the memory of the line being deleted
	Node* temp = head;
	for (int i = 1; temp != nullptr; i++) {
		if (index == 1) {
			//if the line being deleted is the head of the linked list, assign temp the value of head
			temp = head;
			//point head to head's next node
			head = head->next;
			//delete temp node to free up the memory it was using
			delete temp;
			break;
		}
		else if (i == index && temp->next != nullptr) {
			//prev->next now points to temp->next, removing temp from the list
			prev->next = temp->next;
			//delete temp node to free up the memory it was using
			delete temp;
			break;
		}
		else if (i == index && temp->next == nullptr) {
			//delete the tail by making the tail the prev node, and tail->next becomes null
			tail = prev;
			tail->next = nullptr;
			//delete temp node to free up the memory it was using
			delete temp;
			break;
		}
		//iterates over the list by moving both prev and temp
		prev = temp;
		temp = temp->next;
	}
}

void List::replaceLine(std::string text, int index) {
	//Replaces the line at the given index with the given text
	if (text.length() > 80) {
		//substrings text to ignore characters after the 80th one
		text = text.substr(0, 80);
	}
	cur = head;
	for (int i = 1; cur != nullptr; i++) {
		if (i == index) {
			//if at the correct node, replace its text with the new text
			cur->lineVal = text;
			break;
		}
		cur = cur->next;
	}
}

void List::print() {
	//Prints the entire document, with line numbers
	cur = head;
	int index = 1;//counts the line numbers so that they can be printed
	while (cur != nullptr) {
		//traverses the entire list, printing the value of each node
		std::cout << index << " " << cur->lineVal << std::endl;
		index++;
		cur = cur->next;
	}

}

void List::search(std::string text) {
	//Prints the line number and line containing given text
	cur = head;
	int index = 1;
	bool found = false;
	while (cur != nullptr) {
		if (cur->lineVal.find(text) != std::string::npos) {
			//checks if the entireity of the string can be found in one of the lines in the list
			std::cout << index << " " << cur->lineVal << std::endl;
			found = true;
		}
		cur = cur->next;
		index++;
	}
	if (!found) {
		std::cout << "not found" << std::endl;
	}

}

int main(int argc, char* argv[]) {
	List document;//Creates the linked list
	std::string userInput;
	std::string option = "";
	std::string lineString;
	std::string lineNumber;
	int line = 0;
	
	//if the beginning of the statement inputted is equal to one of the keywords, call the corresponding function
	while (option != "quit") {
		//takes input from the user and assign it to the string userInput
		std::getline(std::cin, userInput);
		//creates a substring of userInput taking only the command at the beginning, looking for the first space
		option = userInput.substr(0, userInput.find(' '));

		//compares the string of option to the possible commands
		if (option == "insertEnd") {
			//Calls the insetAtEnd function
			//Creates a substring of the text that appears inside parentheses after the command
			lineString = userInput.substr(userInput.find('\"') + 1);
			lineString = lineString.substr(0, lineString.find('\"'));
			document.insertAtEnd(lineString);
		}
		else if (option == "insert") {
			//Calls the insertAtLine function
			//Creates a substring of the text that appears inside parentheses after the command
			lineString = userInput.substr(userInput.find('\"') + 1);
			lineString = lineString.substr(0, lineString.find('\"'));

			//Creates a substring of the line number that appears in the command
			lineNumber = userInput.substr(userInput.find(' ') + 1);
			lineNumber = lineNumber.substr(0, lineNumber.find(' '));
			//Creates a stringstream to convert the string into its integer value
			std::stringstream s(lineNumber);
			s >> line;

			document.insertAtLine(lineString, line);

		}
		else if (option == "delete") {
			//Calls the deleteLine function
			lineNumber = userInput.substr(userInput.find(' ') + 1);
			//Creates a stringstream to convert the string into its integer value
			std::stringstream s(lineNumber);
			s >> line;
			document.deleteLine(line);
		}
		else if (option == "edit") {
			//Calls the replaceLine function
			//Creates a substring of the text that appears inside parentheses after the command
			lineString = userInput.substr(userInput.find('\"') + 1);
			lineString = lineString.substr(0, lineString.find('\"'));

			//Creates a substring of the line number that appears in the command
			lineNumber = userInput.substr(userInput.find(' ') + 1);
			lineNumber = lineNumber.substr(0, lineNumber.find(' '));
			//Creates a stringstream to convert the string into its integer value
			std::stringstream s(lineNumber);
			s >> line;
			
			document.replaceLine(lineString, line);
		}
		else if (option == "print") {
			//Calls the print function
			document.print();
		}
		else if (option == "search") {
			//Calls the search function
			lineString = userInput.substr(userInput.find('\"') + 1);
			lineString = lineString.substr(0, lineString.find('\"'));
			document.search(lineString);

		}
		else if (option == "quit") {
			//Exits the program
			return 0;
		}
	}
	return 0;
}