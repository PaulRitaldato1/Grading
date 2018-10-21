#include <string>
#include <iostream>
#include <regex>

struct Node {
  std::string value;
  struct Node *next;
	struct Node *prev;
};

class list {
	private:
  	struct Node *head, *tail;
		int size;
    
  public:
		list() {
			head = NULL;
			tail = NULL;
			size = 0;
		}

		void insert(int index, std::string data) {
			Node *new_node = new Node();
			Node *curr = head;
			new_node->value = data;

			if((index > size + 1) || (index == 0)) {
				std::cout << "Out of bounds insertion" << std::endl;
				delete(new_node);	
				return;
			} else if(index == 1) {
				new_node->next = head;
				head->prev = new_node;
				head = new_node;
			} else if(index == size + 1) {
				tail->next = new_node;
				new_node->prev = tail;
				tail = new_node;
			} else {
				for(int i = 1; i < index; i++) {curr = curr->next;}
				Node* prev = curr->prev;
				curr->prev = new_node;
				prev->next = new_node;
				new_node->next = curr;
				new_node->prev = prev;
				
				while(curr->next != NULL) {curr = curr->next;}
				tail = curr;
			}

			size++;
		}

		void insert_end(std::string data) {
			Node *new_node = new Node();
			new_node->value = data;

			if(head == NULL) {
				head = new_node;
				tail = new_node;
			} else {
				tail->next = new_node;
				new_node->prev = tail;
				tail = new_node;
			}

			size++;
		}

		void delete_node(int index) {
			if(index < 1 || index > size) {
				std::cout << "Index is out of bound" << std::endl;
			} else {
				Node *curr = head;
				Node *prev;
				Node *next;

				if(index == 1) {
					head = head->next;
					head->prev = NULL;
				} else if(index == size) {
					curr = tail;
					tail = curr->prev;
					tail->next = curr->next;
				} else {
					for(int i = 1; i < index; i++) {curr = curr->next;}
					prev = curr->prev;
					next = curr->next;
					prev->next = next;
					next->prev = prev;
				}

				size--;
				delete(curr);
			}
		}

		void edit_node(int index, std::string data) {
        if(index < 1 || index > size) {
          std::cout << "Index is out of bound" << std::endl;
        } else {
          Node *curr = head;
 
          if(index == 1) {
            head->value = data;
          } else if(index == size) {
            tail->value = data;
          } else {
            for(int i = 1; i < index; i++) {curr = curr->next;}
						curr->value = data;
          }
        }
      }

		void search(std::string input) {
			Node *curr = head;
			int line = 1;

			while(curr != NULL) {
				size_t found = curr->value.find(input);
				if(found != std::string::npos) {std::cout << line << " " << curr->value << std::endl;}
				line++;
				curr = curr->next;
			}
		}

		void print_list() {
			Node *curr = head;
			int line = 1;

			while(curr != NULL) {
				std::cout << line << " " << curr->value << std::endl;
				curr = curr->next;
				line++;
			}
		}

		void print_list_rev() {
			Node *curr = tail;
			int line = size;

			while(curr != NULL) {
				std::cout << line << " " << curr->value << std::endl;
				curr = curr->prev;
				line--;
			}
		}
};

void line_editor() {
	list *my_list = new list();
	std::regex insertEnd("^\\s*insertEnd\\s+\\\"(.*)\\\"");
	std::regex insert("^\\s*insert\\s+([0-9]+)\\s+\\\"(.*)\\\"");
	std::regex search("^\\s*search\\s+\\\"(.*)\\\"");
	std::regex edit("^\\s*edit\\s+([0-9]+)\\s+\\\"(.*)\\\"");
	std::regex delete_line("^\\s*delete\\s+([0-9]+)\\s*");

	while(true) {
		std::string user_input;
		std::getline (std::cin,user_input);

		if(user_input == "quit") {return;}
		else if(user_input == "print") {my_list->print_list();}

		if(std::regex_match(user_input,insertEnd)) {
			std::smatch match;
			std::regex_search(user_input,match,insertEnd);
			my_list->insert_end(match.str(1));
		} else if(std::regex_match(user_input,insert)) {
				std::smatch match;
				std::regex_search(user_input,match,insert);
				my_list->insert(stoi(match.str(1)), match.str(2));
		} else if(std::regex_match(user_input,search)) {
			std::smatch match;
			std::regex_search(user_input,match,search);
			my_list->search(match[1]);
		} else if(std::regex_match(user_input,edit)) {
			std::smatch match;
			std::regex_search(user_input,match,edit);
			my_list->edit_node(stoi(match.str(1)),match.str(2));
		} else if(std::regex_match(user_input,delete_line)) {
			std::smatch match;
			std::regex_search(user_input,match,delete_line);
			my_list->delete_node(stoi(match.str(1)));
		}
	}
}

int main() {
	line_editor();
	return 0;
}
