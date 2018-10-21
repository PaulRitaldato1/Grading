#include <iostream>
#include <string>

using namespace std;

struct node
{
	string line;
	int num;
	struct node *next;
};

class linked_list {
private:
	node *head, *tail;
public:
	linked_list() {
		head = NULL;
		tail = NULL;
	}

	void insertEnd(string new_line) {
		node *temp = new node;
		temp->line = new_line;
		temp->next = NULL;
		temp->num = 1;
		if (head == NULL) {
			head = temp;
			tail = temp;
		} else {
			tail->next = temp;
			tail->next->num = tail->num + 1;
			tail = tail->next;
		}
	}

	void insert(int line_num, string new_line) {
		node *temp = head;
		bool found = false;
		if (head == NULL && line_num == 1) {
			insertEnd(new_line);
		} else if (head == NULL && line_num != 1) {
            return;
        } else {
			while (temp->next != NULL) {
				if (line_num == 1) {
					node *temp1 = new node;
					temp1->line = new_line;
					temp1->num = line_num;
					temp1->next = head;
					head = temp1;
					found = true;
					line_num = 0;
				}  
				if (found) {
					if (temp->next->next == NULL) {
						temp->num = temp->next->num;
						temp->next->num = temp->num + 1;
					} else {
						temp->num = temp->next->num;
					} 
				} else if (temp->next->num == line_num) {
					found = true;
					node *temp1 = new node;
					temp1->line = new_line;
					temp1->num = temp->next->num;
					temp1->next = temp->next;
					temp->next = temp1;
					if (temp->next->next->next != NULL) {
						temp = temp->next;
					}
				} else if (temp->next->num + 1 == line_num) {
                    insertEnd(new_line);
                    return;
                }
				temp = temp->next; 
			}
		}
	}

	void delete_line(int line_num) {
		node *temp = head;
		bool found = false;
		while (temp != NULL) {
			if (temp->next != NULL && temp->next->num == line_num) {
				temp->next = temp->next->next;
				found = true;
			} else if (found) {
				temp->num = temp->num - 1;
			}
			temp = temp->next;
		}
	}

	void edit(int line_num, string new_line) {
		node *temp = head;
		while (temp != NULL) {
			if (temp->num == line_num) {
				temp->line = new_line;
				return;
			}
			temp = temp->next;
		}
	}

	void print() {
		node *temp = head;
		while (temp != NULL) {
			cout << temp->num << " " << temp->line << endl;
			temp = temp->next;
		}
	}

	void search(string text) {
		node *temp = head;
		bool found = false;
		while (temp != NULL) {
			if (temp->line.find(text) != -1) {
				found = true;
				cout << temp->num << " " << temp->line << endl;
			}
			temp = temp->next;
		}
		if (!found) {
			cout << "not found" << endl;
		}
	}
};

int main()
{
    linked_list text;
    bool quit = false;
    while (!quit) {
        string command, line_num, line, word;
        cin >> command;
        if (command == "insertEnd") {
            while (word[word.length()-1] != '\"') {
                cin >> word;
                line += " " + word;
            }
            line = line.substr(2, line.length()-3);
            text.insertEnd(line);
        } else if (command == "insert") {
            cin >> line_num;
            while (word[word.length()-1] != '\"') {
                cin >> word;
                line += " " + word;
            }
            line = line.substr(2, line.length()-3);
            text.insert(stoi(line_num), line);
        } else if (command == "delete") {
            cin >> line_num;
            text.delete_line(stoi(line_num));
        } else if (command == "edit") {
            cin >> line_num;
            while (word[word.length()-1] != '\"') {
                cin >> word;
                line += " " + word;
            }
            line = line.substr(2, line.length()-3);
            text.edit(stoi(line_num), line);
        } else if (command == "print") {
            text.print();
        } else if (command == "search") {
            while (word[word.length()-1] != '\"') {
                cin >> word;
                line += " " + word;
            }
            line = line.substr(2, line.length()-3);
            text.search(line);
        } else if (command == "quit") {
            quit = true;
        } else {
            cout << "Invalid command" << endl;
        }
    }
            
}