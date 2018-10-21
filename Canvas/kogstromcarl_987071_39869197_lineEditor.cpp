using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

struct node {
	string data;
	node* next;
};

class list
{
	struct node {
		string data;
		node* next = NULL;
	};

private:
	node *head, *tail;

public:
	list() {
		head = NULL;
		tail = NULL;
	}

	void insertEnd(string newData) {
		node *temp = new node;
		temp->data = newData;
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

	void insert(int pos, string newData)
	{
		node *prev = new node;
		node *curr = new node;
		node *temp = new node;
		curr = head;
		for (int i = 1; i < pos; i++)
		{
			prev = curr;
			curr = curr->next;
		}
		temp->data = newData;
		prev->next = temp;
		temp->next = curr;
	}

	void deleteNode(int pos) {
		node *curr = new node;
		node *prev = new node;
		curr = head;

		for (int i = 1; i < pos; i++) {
			prev = curr;
			curr = curr->next;
		}
		prev->next = curr->next;
	}

	void print() {
		node *temp = new node;
		temp = head;
		int i = 1;
		while (temp != NULL) {
			cout << i << " " << temp->data << "\n";
			temp = temp->next;
			i++;
		}
	}

	void search(string input) {
		node* curr = new node;
		node* prev = new node;
		curr = head;
		int index = 1;
		bool found = false;

		while (curr != NULL) {
			if (curr->data.find(input) != string::npos) {
				cout << index << " " << curr->data << endl;
				found = true;
			}

			prev = curr;
			curr = curr->next;
			index++;

		}

		if (!found) {
			cout << "not found" << endl;
		}
	}

	void edit(int pos, string newData) {
		node *curr = new node;
		node *prev = new node;
		curr = head;

		for (int i = 1; i < pos; i++) {
			prev = curr;
			curr = curr->next;
		}

		curr->data = newData;
	}
};

int main() {
	list obj;
	bool loop1 = true;
	int lineCount = 0;

	while (loop1) {
		string command;
		string line;
		cin >> command;
		for (int i = 0; i < command.size(); i++) {
			command[i] = tolower(command[i]);
		}

		if (command.compare("quit") == 0) break;
		else if (command.compare("print") == 0) {
			obj.print();
		}
		else if (command.compare("insertend") == 0) {
			getline(cin, line);
			int i = 0;
			while (line[i] == ' ') {
				line = line.substr(1);
				i++;
			}

			line.pop_back();
			line.erase(0, 1);

			obj.insertEnd(line);
			lineCount++;
		}
		else if (command.compare("insert") == 0) {
			int position;
			cin >> position;
			if ((position <= lineCount + 1) && (position > 0)) {
				getline(cin, line);
				int i = 0;
				while (line[i] == ' ') {
					line = line.substr(1);
					i++;
				}

				line.pop_back();
				line.erase(0, 1);

				obj.insert(position, line);
				lineCount++;
			}

		}
		else if (command.compare("delete") == 0) {
			int position;
			cin >> position;
			if (!(position > lineCount)) {
				;
				obj.deleteNode(position);
				lineCount--;
			}
		}
		else if (command.compare("edit") == 0) {
			int position;
			cin >> position;
			if ((position <= lineCount) && (position > 0)) {
				int i = 0;
				getline(cin, line);
				while (line[i] == ' ' || line[i] == '"') {
					line = line.substr(1);
					i++;
				}

				line.pop_back();
				line.erase(0, 1);

				obj.edit(position, line);
			}
		}
		else if (command.compare("search") == 0) {
			getline(cin, line);
			int i = 0;
			while (line[i] == ' ' || line[i] == '"') {
				line = line.substr(1);
				i++;
			}

			line.pop_back();
			line.erase(0, 1);

			obj.search(line);
		}
	}
}
