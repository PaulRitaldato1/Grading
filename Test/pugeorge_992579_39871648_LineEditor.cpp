#include "iostream"
#include "string"

class Node {
public:
std::string line;
Node* next;

Node(std::string line) {
	this->line = line;
	this->next = NULL;
}

bool hasNext() {
    if (this->next == NULL) {
		return false;
	} else {
		return true;
	}
}

bool hasSubstring(std::string s) {
	if (line.find(s) != std::string::npos) {
		return true;
	} else {
		return false;
	}
}
};

class LinkedList {
private:
Node* head;

public:
LinkedList() {
	this->head = NULL;
}

void insert(int n, std::string s) {
    Node* node = this->head;
    Node* newNode = new Node(s);
    bool nLtLen = true;  // n < len
    n--;  // adjust to 0 indexing
    if (n == 0) {
        if (this->head != NULL) {
            Node* temp = node->next;
            this->head = newNode;
            newNode->next = temp;
        } else {
            this->head = newNode;
        }
    } else {
        for (int i = 0; i < n - 1; i++) {
            if (node->hasNext()) {
                node = node->next;
            } else {
                nLtLen = false;
                break;
            }
        }
        if (nLtLen) {
            Node* temp = node->next;
            node->next = newNode;
            newNode->next = temp;
        }
    }
}

void insertEnd(std::string s) {
    Node* newNode = new Node(s);
    if (this->head == NULL) {
        this->head = newNode;
    } else {
        Node* node = this->head;
    	while (node->hasNext()) {
    		node = node->next;
    	}
    	node->next = newNode;
    }
}

void remove(int n) {  // delete is a reserved keyword
    Node* node = this->head;
    Node* prev = NULL;
    bool nLtLen = true;  // n < len
    n--;  // adjust to 0 indexing
    if (n == 0) {
        this->head = node->next;
    } else {
        for (int i = 0; i < n; i++) {
            if (node->hasNext()) {
                prev = node;
                node = node->next;
            } else {
                nLtLen = false;
                break;
            }
        }
        if (nLtLen) {
            if (node == NULL) {
                prev->next = NULL;
            } else {
                prev->next = node->next;
            }
        }
    }
}

void edit(int n, std::string s) {
	Node* node = this->head;
	bool reached = true;
    n--;  // adjust to 0 indexing
	for (int i = 0; i < n; i++) {
		if (node->hasNext()) {
			node = node->next;
		} else {
			reached = false;
			break;
		}
	}
	if (reached) {
		node->line = s;
	}
}

void print() {
	Node* node = this->head;
	int n = 1;
    if (node != NULL) {
        std::cout << n << ' ' << node->line << '\n';
    	while (node->hasNext()) {
            n++;
    		node = node->next;
    		std::cout << n << ' ' << node->line << '\n';
    	}
    }
}

void search(std::string s) {
	Node* node = this->head;
	int n = 1;
	bool found = false;
	while (node->hasNext()) {
		if (node->hasSubstring(s)) {
			std::cout << n << ' ' << node->line << '\n';
			found = true;
        }
		node = node->next;
		n++;
	}
    // one more time to cover last node
    if (node->hasSubstring(s)) {
        std::cout << n << ' ' << node->line << '\n';
        found = true;
    }
	if (!found) {
		std::cout << "not found" << '\n';
	}
}
};

std::string GetLine(std::string input) {
	int startstop = 0;
	std::string line = "";
	for (unsigned i = 0; i < input.length(); i++) {
		if (input[i] == '"') {
			startstop++;
		} else if (startstop == 1) {
			line += input[i];
		} else if (startstop > 1) {
			line.pop_back();
			break;
		}
	}
	return line;
}

int main() {
	LinkedList list = LinkedList();
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::string cmd = "";
		int C = 0;
		for (unsigned i = 0; i < input.length(); i++) {
			if (input[i] == ' ') {
				break;
			} else {
				cmd += input[i];
				C++;
			}
		}

		if (cmd == "insertEnd") {
			std::string line = GetLine(input.substr(C));
			list.insertEnd(line);
		} else if (cmd == "insert") {
            int line_no = std::stoi(input.substr(C));
			std::string line = GetLine(input.substr(C));
			list.insert(line_no, line);
		} else if (cmd == "delete") {
            int line_no = std::stoi(input.substr(C));
			list.remove(line_no);
		} else if (cmd == "edit") {
			int line_no = std::stoi(input.substr(C));
			std::string new_line = GetLine(input.substr(C));
			list.edit(line_no, new_line);
		} else if (cmd == "print") {
			list.print();
		} else if (cmd == "search") {
			std::string snip = GetLine(input.substr(C));
			list.search(snip);
		} else if (cmd == "quit") {
			break;
		} else {
			std::cout << "invalid command" << '\n';
		}
	}
	return 0;
};
