
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>


using namespace std;


class linked_list {
	struct node {
		string item;
		node* next;
	};

private:
	node* head; 
	node* tail;

public:

	linked_list() {
		head = NULL;
		tail = NULL;
	}


	void push(string in) {
		node *temp = new node;
		temp->item = in;
		temp->next = NULL;

		if (head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}

	void insert(int line, string in)
	{
		node* p = new node;
		node* c = new node;
		node* temp = new node;
		temp->item = in;
		c = head;
		for (int i = 1; i < line; i++)
		{
			p = c;
			c = c->next;
		}
		
		p->next = temp;
		temp->next = c;
	}


	void del(int line) {
		node* p = new node;
		node* c = new node;
		c = head;

		for (int i = 1; i < line; i++) {
			p = c;
			c = c->next;
		}
		p->next = c->next;
	}

	void print() {
		node* temp = new node;
		temp = head;

		for (int i = 0; temp != NULL; i++) {
			cout << i << " " << temp->item << "\n";
			temp = temp->next;
		}

	}


	void search(string key) {
		node* temp = new node;
		temp = head;

		bool find = false;

		for (int i = 1; temp != NULL; i++) {
			if (temp->item.find(key) != string::npos) {
				cout << i << " " << temp->item << endl;
				find = true;
			}
			temp = temp->next;

		}

		if (!find) {
			cout << "not found" << endl;
		}
	}


	void edit(int line, string in) {
		insert(line, in);
		del(line + 1);

	}

	bool isEmpty() {
		return(head == NULL);
	}


};

int main() {
	linked_list lines;
	int count = 0;
	bool run = true;

	while (run) {
		string input;
		getline(cin, input);

		if (input == "quit") {
			break;
		}
		else if (input == "print") {
			lines.print();
		}
		else {
			string command;
			for (int i = 0; input[i] != ' ';) {
				command = command + input[i];
				input = input.substr(1);
			}

			if (command == "insertEnd") {
				bool r = true;
				while (r) {
					if (input[0] == '"') {
						r = false;
					}
					input = input.substr(1);
				}
				input = input.substr(0, (input.length() - 1));
				count++;
				lines.push(input);
			}
			else if (command == "insert") {
				while (input[0] == ' ') {
					input = input.substr(1);
				}
				string num;
				for (int i = 0; input[i] != ' ';) {
					num = num + input[i];
					input = input.substr(1);
				}
				int linNum;
				linNum = stoi(num);

				bool r = true;
				while (r) {
					if (input[0] == '"') {
						r = false;
					}
					input = input.substr(1);
				}
				input = input.substr(0, (input.length() - 1));
				
				if (linNum <= count + 1) {
					lines.insert(linNum, input);
					count++;
				}
				

			}
			else if (command == "delete") {
				while (input[0] == ' ') {
					input = input.substr(1);
				}
				int linNum;
				linNum = stoi(input);

				if (linNum <= count) {
					lines.del(linNum);
					count--;
				}

			}
			else if (command == "edit") {
				while (input[0] == ' ') {
					input = input.substr(1);
				}
				string num;
				for (int i = 0; input[i] != ' ';) {
					num = num + input[i];
					input = input.substr(1);
				}
				int linNum;
				linNum = stoi(num);

				bool r = true;
				while (r) {
					if (input[0] == '"') {
						r = false;
					}
					input = input.substr(1);
				}
				input = input.substr(0, (input.length() - 1));

				if (linNum <= count) {
					lines.edit(linNum, input);
				}
			}
			else if (command == "search") {
				bool r = true;
				while (r) {
					if (input[0] == '"') {
						r = false;
					}
					input = input.substr(1);
				}
				input = input.substr(0, (input.length() - 1));

				lines.search(input);
			}
		}

	}

}