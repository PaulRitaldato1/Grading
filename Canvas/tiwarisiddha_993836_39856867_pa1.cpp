
#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>

using namespace std;

class LineNode {
public:
	LineNode* next;
	string line;
};

class LineEditor {
public:
	int length;
	LineNode* head;
	LineEditor();
	~LineEditor();
	void add(string line);
	void insert(int i, string line);
	void remove(int i);
	void search(string s);
	void edit(int i, string line);
	void outputEditor();
};

int main() {
	LineEditor* editor = new LineEditor;
	string input = "";
	vector<string> tokens;
	while (input != "quit") {
		getline(cin, input);
		std::string s = input;
		std::string delimiter = " ";
		size_t last = 0; 
		size_t next = 0; 
		while ((next = s.find(delimiter, last)) != string::npos) { 
			tokens.push_back(s.substr(last, next-last));
			last = next + 1; 
		} 
		tokens.push_back(s.substr(last));

		string cmd = tokens.at(0);
		if (cmd == "insertEnd") {
			editor->add(input.substr(input.find("\"") + 1, input.length() - 2 - input.find("\"")));	
		} else if (cmd == "insert") {
			editor->insert(stoi(tokens.at(1)), input.substr(input.find("\"") + 1, input.length() - 2 - input.find("\"")));
		} else if (cmd == "print") {
			editor->outputEditor();
		} else if (cmd == "search") {
			editor->search(input.substr(input.find("\"") + 1, input.length() - 2 - input.find("\"")));
		} else if (cmd == "delete") {
			editor->remove(stoi(tokens.at(1)));
		} else if (cmd == "edit") {
			editor->edit(stoi(tokens.at(1)), input.substr(input.find("\"") + 1, input.length() - 2 - input.find("\"")));
		}

		tokens.clear();
	}

	return 0;
}

LineEditor::LineEditor() {
	this->length = 0;
	this->head = NULL;
}

LineEditor::~LineEditor() { }

void LineEditor::add(string line) {
	LineNode* node = new LineNode();
	node->line = line;
	if (this->head == NULL) {
		this->head = node;
		this->length++;
		return;
	}
	LineNode* temp = this->head;
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = node;
	this->length++;
}

void LineEditor::insert(int i, string line) {
	i = i - 1;
	if (i == this->length) {
		add(line);
		return;
	}
	if (i < 0 || i > this->length - 1) { return; }
	//if (i == this->length - 1)
	LineNode* node = new LineNode();
	node->line = line;
	if (i == 0) {
		node->next = this->head;
		this->head = node;
		this->length++;
		return;
	}
	LineNode* temp = this->head;
	int c = 0;
	while(c != i - 1) {
		temp = temp->next;
		c++;
	}
	if (temp->next != NULL) {
		node->next = temp->next;
	}
	temp->next = node;
	this->length++;
}

void LineEditor::remove(int i) {
	i = i - 1;
	if (i < 0 || i > this->length - 1) { return; }
	if (i == 0) { 
		this->head = this->head->next; 
		this->length--;
		return;
	}
	LineNode* temp = this->head;
	int c = 0;
	while(c != i - 1) {
		temp = temp->next;
		c++;
	}
	if (c == this->length - 2) { 
		temp->next = NULL;
	} else {
		temp->next = temp->next->next;
	}
	this->length--;
}

void LineEditor::search(string s) {
	LineNode* temp = this->head;
	int c = 0;
	int found = 0 ;
	while(temp != NULL) {
		string line = temp->line;
		if (strstr(line.c_str(), s.c_str())) {
			cout << c + 1 << " " << line << "\n";
			found++;
		}
		temp = temp->next;
		c++;
	}
	if (found == 0) { cout << "not found\n"; }
}

void LineEditor::edit(int i, string s) {
	i = i - 1;
	if (i < 0 || i > this->length - 1) { return; }
	LineNode* temp = this->head;
	int c = 0;
	while(c != i) {
		temp = temp->next;
		c++;
	}
	temp->line = s;
}

void LineEditor::outputEditor() {
	LineNode* temp = this->head;
	int i = 1;
	while(temp != NULL) {
		cout << i << " " << temp->line << "\n";
		temp = temp->next;
		i++;
	}
}

