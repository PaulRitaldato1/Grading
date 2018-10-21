#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <sstream>

struct Node {
	std::string line;
	Node *next = NULL;
};

class list {
private:
	Node *head, *tail;
public:
	list() {
		head = NULL;
		tail = NULL;
	}

	// function insertEnd updates the tail to be the new node
	// if list does not exist yet, new node is both head and tail
	void insertEnd(std::string text) {
		Node *temp = new Node;
		temp->line = text;
		temp->next = NULL;

		if (head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {
			tail->next = temp;
			tail = tail->next;
		}
				
	}

	// function insert inserts new node at specific location
	// if location is the head, new head is the new node
	void insert(int location, std::string text) {
		Node *temp = new Node;
		temp->line = text;

		if (location == 1) {
			temp->next = head;
			head = temp;
		}

		int index = 2;
		Node *current = new Node;
		Node *previous = new Node;
		previous = head;
		current = head->next;
		while (index < location) {
			previous = current;
			current = current->next;
			index++;
		}

		previous->next = temp;
		temp->next = current;
	}

	// function deleteLine deletes node at specific location
	// if location is the head, relink head with what's next after old head
	// if tail is deleted, update new tail as the previous node
	void deleteLine(int location) {
		Node *previous = new Node;
		Node *current = new Node;

		if (location == 1) {
			head = head->next;
		}
		if (location > 1) {
			int index = 2;
			previous = head;
			current = head->next;
			while (index < location) {
				previous = current;
				current = current->next;
				index++;
			}
			previous->next = current->next;
			if (previous->next == NULL) {
				tail = previous;
			}
		}
	}

	// function edit replaces the node at specific location with new node and relink
	void edit(int location, std::string text) {
		Node *temp = new Node;
		temp->line = text;

		if (location == 1) {
			temp->next = head->next;
			head = temp;
		}

		Node *current = new Node;
		Node *previous = new Node;
		previous = head;
		current = head->next;
		
		int index = 2;
		while (index < location) {
			previous = current;
			current = current->next;
			index++;
		}
		previous->next = temp;
		temp->next = current->next;
		if (current->next == NULL) {
			tail = temp;
		}
		
	}

	// function search looks for matching text in each line
	// appends each find to a string and return the string
	// if no matching text was found, return not found
	std::string search(std::string text) {
		Node *current = new Node;
		current = head;
		std::string finalstring;
		int usercounter = 1;
		while (current != NULL) {
			if (current->line.find(text) != std::string::npos) {
				std::string stringindex = std::to_string(usercounter);
				std::string foundline = current->line;
				finalstring.append(stringindex + " " + foundline + "\n");
			}
			current = current->next;
			usercounter++;
		}
		if (!finalstring.empty()) {
			return finalstring;
		}
		else {
			return "not found\n";
		}

	}

	// print function iterate through the list and print each line
	void print() {
		Node *temp = new Node;
		temp = head;
		int counter = 0;
		while (temp != NULL) {
			std::cout << counter + 1 << " " << temp->line << "\n";
			temp = temp->next;
			counter++;
		}
	}

	// removes quotations from text and put into a string
	// checks size of text and only return string within 80 char
	std::string textReader(std::string command) {
		std::string newText;
		for (unsigned int i = 0; i < command.length(); i++) {
			if (command[i] == '"') {
				++i;
				while (command[i] != '"') {
					newText += command[i];
					i++;
					
				}
				++i;
			}
		}
		if (newText.length() > 80) {
			std::string cutstring = newText.erase(80, newText.length());
			return cutstring;
		}
		else {
			return newText;
		}
	}

	// return true or false depending on if the number is out of range of existing list
	// if the whichcommand is insert then the number will not be out of range if
	// number - 1 > range is false so if number was 4 and range is 3, inserting 
	// new text at line 4 is ok so return false
	bool isOutOfRange(int number, std::string whichcommand) {
		Node *current = new Node;
		current = head;
		int range = 0;
		while (current != NULL) {
			current = current->next;
			range++;
		}
		if (whichcommand == "insert") {
			if (number - 1 > range) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (whichcommand != "insert" && number > range) {
			return true;
		}
		else {
			return false;
		}
	}
};


int main() {
	std::string command;
	std::string mytext;
	list list;

	// do while used to check the command if it contains quit
	// if it contains quit, program exits
	do{

		std::getline(std::cin, command);
		
		// command is to delete
		// command.find(text) looks for the specific text in command
		// std::string::npos is to check if it found something
		// so std::string::npos means not found
		// when isOutOfRange returns true, ignore user input
		if (command.find("delete") != std::string::npos) {
			std::string number = command.erase(0, 7);
			int locnum = stoi(number);
			bool isnumbad = list.isOutOfRange(locnum, "delete");
			if (isnumbad) {
				// do nothing
			}
			else if (!isnumbad) {
				list.deleteLine(locnum);
			}
		}

		// command is insertEnd
		if (command.find("insertEnd") != std::string::npos) {
			mytext = list.textReader(command);
			list.insertEnd(mytext);
		}

		// command is insert
		// since I know command is insert, I can erase the text insert including the whitespace
		// then take the remaining text and convert to integer to
		// send it to isOutOfRange
		if (command.find("insert ") != std::string::npos) {
			mytext = list.textReader(command);
			std::string number = command.erase(0, 7);
			int newNum = std::stoi(number);
			bool isnumbad = list.isOutOfRange(newNum, "insert");
			if (isnumbad) {
				// do nothing
			}
			else if (!isnumbad) {
				list.insert(newNum, mytext);
			}
		}

		// command is edit
		// I do the same thing with erasing the command so that
		// I only get the number to use
		else if (command.find("edit") != std::string::npos) {
			mytext = list.textReader(command);
			std::string number = command.erase(0, 5);
			int newNum = std::stoi(number);
			bool isnumbad = list.isOutOfRange(newNum, "edit");
			if (isnumbad) {
				// do nothing
			}
			else if (!isnumbad) {
				list.edit(newNum, mytext);
			}
		}

		// command is search
		if (command.find("search") != std::string::npos) {
			std::string texttosearch = list.textReader(command);
			std::string foundstring = list.search(texttosearch);
			std::cout << foundstring;
		}

		if (command.find("print") != std::string::npos) {
			list.print();
		}

		//notice that == std::string::npos which means that if find could
		// not find anything then it does equal to std::string::npos
		// which checks if find found anything or not.
		// so in this case, command.find("quit") was detected
	} while (command.find("quit") == std::string::npos);
	// system("PAUSE");
}