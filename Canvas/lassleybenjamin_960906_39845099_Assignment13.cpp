#include <iostream>
#include <string>
using namespace std;
struct node {
	string text;
	node *next;
};

class list {
private:
	node *head, *tail;
public:
	list() {
		head = NULL;
		tail = NULL;
	}

	void insertEnd(string phrase) {
		node *add = new node;
		add->text = phrase;
		add->next = NULL;
		//edge case for if there are no nodes
		if (head == NULL) {
			head = add;
			tail = add;
			return;
		}
		node *current = head;
		//go to the end of the list, then add the node there
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = add;
	}

	void insertAtIndex(int index, string phrase) {
		int i = 0;
		node *add = new node;
		node *previous = new node;
		node *current = head;
		add->text = phrase;
		add->next = NULL;

		//if head is null, insert there, but only if the index is 1
		if (head == NULL) {
			if (index == 1) {
				head = add;
				tail = add;
			}
			return;
		}
		//if index is 1, replace head with added node
		if (index == 1) {
			add->next = head;
			head = add;
			return;
		}
		//go through to the wanted index, then add node there
		while (i < index - 1) {
			//if the end of the list is reached, add node there, but only if index is correct
			if (current->next == NULL) {
				if (i == index - 2) {
					current->next = add;
				}
				return;
			}
			previous = current;
			current = current->next;
			i++;
		}
		add->next = current;
		previous->next = add;
	}

	void deleteAtIndex(int index) {
		int i = 0;
		node *current = head;
		node *previous = new node();
		//if index is 1, replace head with its next
		if (index == 1) {
			head = head->next;
			return;
		}
		//look for desired index and delete node there
		while (i < index - 1) {
			if (current->next == NULL) {
				return;
			}
			previous = current;
			current = current->next;
			i++;
		}
		//make sure delete doesnt go out of bounds
		previous->next = current->next;
	}

	void edit(int index, string phrase) {
		int i = 0;
		node *current = head;
		node *add = new node;
		add->text = phrase;
		node *previous = new node();
		//if index is 1, edit the head into new node
		if (index == 1) {
			add->next = head->next;
			head = add;
			return;
		}
		//go to desired index and replace that node
		while (i < index - 1) {
			previous = current;
			current = current->next;
			i++;
		}
		add->next = current->next;
		previous->next = add;
	}

	void search(string phrase) {
		int i = 2;
		int search = 0;
		node *current = head;
		//edge case for head
		if (head->text.find(phrase) != std::string::npos) {
			cout << 1 << " " << head->text << endl;
			search = 1;
		}
		//look through all the nodes and print all with phrase in them
		while (current->next != NULL) {
			current = current->next;
			if (current->text.find(phrase) != std::string::npos) {
				cout << i << " " << current->text << endl;
				search = 1;
			}
			i++;
		}
		//if no nodes are found, print "not found"
		if (search == 0) {
			cout << "not found" << endl;
		}
	}

	void print() {
		int i = 1;
		node *current = head;
		if (current == NULL) {
			return;
		}
		//go through all nodes and print each
		while (current != NULL) {
			cout << i << " " << current->text << endl;
			current = current->next;
			i++;
		}
	}
};

int main()
{
	list newList;
	string input = "";
	int index;
	string phrase;
	//while loop to get next input and follow its instructions
	while (input != "quit") {
		getline(cin, input);
		if (input.length() > 80) {
			cout << "error: line too long" << endl;
		}
		else {
			if (input.find("insertEnd") != std::string::npos) {
				phrase = input.substr(11, input.length() - 12);
				newList.insertEnd(phrase);
			}

			else if (input.find("insert ") != std::string::npos) {
				phrase = input.substr(10, input.length() - 11);
				char ind = input[7];
				index = ind - '0';
				newList.insertAtIndex(index, phrase);
			}

			else if (input.find("delete") != std::string::npos) {
				char ind = input[7];
				index = ind - '0';
				newList.deleteAtIndex(index);
			}
			else if (input.find("edit") != std::string::npos) {
				phrase = input.substr(8, input.length() - 9);
				char ind = input[5];
				index = ind - '0';
				newList.edit(index, phrase);
			}
			else if (input.find("print") != std::string::npos) {
				newList.print();
			}
			else if (input.find("search") != std::string::npos) {
				phrase = input.substr(8, input.length() - 9);
				newList.search(phrase);
			}
		}
	}
}