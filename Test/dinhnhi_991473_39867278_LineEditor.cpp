// Nhi Dinh
// COP3530
// Programming Assignment 1 - Line Editor

#include <iostream>
#include <string> 

struct Node {
	std::string line;
	Node*next;
};
class LinkedList {
private:
	Node * head;
	int size;
public:
	LinkedList() {
		head = NULL;
		size = 0;
	}
	void insertEnd(std::string inText) {
		if (head == NULL) {
			head = new Node();
			head->line = inText;
			size++;
			return;
		}
		Node*curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = new Node();
		curr->next->line = inText;
		size++;
	}
	void insert(std::string inText, int idx) {
		Node*temp = new Node();
		Node*prev = new Node();
		Node*curr = head;
		temp->line = inText;
		if (idx > size) {
			return;
		}
		else if (idx == 0) {
			temp->next = head;
			head = temp;
		}
		else {
			for (int i = 0; i < idx; i++) {
				prev = curr;
				curr = curr->next;
			}
			prev->next = temp;
			temp->next = curr;
		}
	}
	void deleteText(int idx) {
		Node*curr = head;
		Node*prev = new Node;
		if (idx > size) {
			return;
		}
		else if (idx == 0) {
			head = curr->next;
			delete(curr);
			return;
		}
		for (int i = 0; i < idx; i++) {
			if (curr->next == NULL)
				return;
			prev = curr;
			curr = curr->next;
		}
		prev->next = curr->next;
		delete(curr);
	}
	void edit(std::string newText, int idx) {
		if (idx + 1 > size) {
			return;
		}
		Node*curr = head;
		for (int i = 0; i < idx; i++) {
			curr = curr->next;
		}
		curr->line = newText;
	}
	void search(std::string inText) {
		Node*curr = head;
		int found = -1;
		int count = 0;
		while (curr != NULL) {
			count++;
			if (curr->line.find(inText) != std::string::npos) {
				std::cout << count << " " << curr->line << std::endl;
				found = 0;
			}
			curr = curr->next;
		}
		if (found == -1) {
			std::cout << "not found" << std::endl;
		}
	}
	void print() {
		Node*curr = head;
		int count = 0;
		while (curr != NULL) {
			count++;
			std::cout << count << " " << curr->line << std::endl;
			curr = curr->next;
		}
	}
};

int findIdx(std::string inText) {
	std::string intString = "";
	int idx = -1;
	for (int i = 0; i < inText.length(); i++) {
		if (inText.at(i) >= 48 && inText.at(i) <= 57) {
			intString += inText.at(i);
			idx = std::stoi(intString);
		}
	}
	return idx;
}

int main()
{
	LinkedList*editor = new LinkedList;
	std::string input = "", line = "", key = "";
	int idx, lineStart = 0;

	while (input != "quit") {
		std::getline(std::cin, input);
		lineStart = input.find_first_of("\"") + 1;
		line = input.substr(lineStart, input.length() - lineStart - 1);
		if (line.length() > 80)
			line = line.substr(0, 80);
		key = input.substr(0, lineStart - 1);
		idx = findIdx(key);

		if (key.find("insertEnd") != std::string::npos)
			editor->insertEnd(line);
		else if (key.find("insert") != std::string::npos)
			editor->insert(line, idx - 1);
		else if (key.find("delete") != std::string::npos)
			editor->deleteText(idx - 1);
		else if (key.find("edit") != std::string::npos) 
			editor->edit(line, idx - 1);
		else if (key.find("search") != std::string::npos) 
			editor->search(line);
		else if (key.find("print") != std::string::npos) 
			editor->print();
	}

	return 0;
}
