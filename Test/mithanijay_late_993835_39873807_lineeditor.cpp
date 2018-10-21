#include <iostream>
#include <sstream>
#include <string>

template <class T>
struct ListNode {
	ListNode<T>* next;
	ListNode<T>* prev;
	T data;
};

template <class T>
class LinkedList {
	private:
		ListNode<T>* head;
		ListNode<T>* tail;
		int size;
	public:
		LinkedList() {
			// create dummy head and tail
			head = new ListNode<T>();
			tail = new ListNode<T>();
			head->next = tail;
			tail->prev = head;
			//set size initially to 0
			size = 0;
		}
		~LinkedList() {
			ListNode<T>* cur_node = head->next;
			while (true) {
				delete cur_node->prev;
				if (cur_node->next == NULL) {
					delete cur_node;
					return;
				}
				cur_node = cur_node->next;
			}
		}
		void insert(int index, T a) {
			if (index > size + 1 || index < 1) return; // ignore out of bounds requests
			
			// create new node to be inserted
			ListNode<T>* new_node = new ListNode<T>();
			new_node->data = a;
			// start at head and iterate until index is reached
			int pos = 1;
			ListNode<T>* prev_node = head;
			while (pos != index) {
				prev_node = prev_node->next;
				pos++;
			}
			ListNode<T>* next_node = prev_node->next;
			
			//insert the new node
			prev_node->next = new_node;
			new_node->prev = prev_node;
			next_node->prev = new_node;
			new_node->next = next_node;
			size++;
		}
		void insertEnd(T a) {
			// create new node to be inserted
			ListNode<T>* new_node = new ListNode<T>();
			new_node->data = a;
			
			ListNode<T>* prev_node = tail->prev;
			
			// insert the new node before the tail
			prev_node->next = new_node;
			new_node->prev = prev_node;
			tail->prev = new_node;
			new_node->next = tail;
			size++;
		}
		void del(int index) {
			if (index > size || index < 1) return; // ignore out of bounds requests
			
			// start at head and iterate until index is reached
			int pos = 1;
			ListNode<T>* prev_node = head;
			while (pos != index) {
				prev_node = prev_node->next;
				pos++;
			}
			ListNode<T>* next_node = prev_node->next->next;
			
			//delete the node in between
			delete prev_node->next;
			prev_node->next = next_node;
			next_node->prev = prev_node;
			size--;
		}
		void edit(int index, T a) {
			if (index > size || index < 1) return; // ignore out of bounds requests
			
			// create new node to be inserted
			ListNode<T>* new_node = new ListNode<T>();
			new_node->data = a;
			// start at head and iterate until index is reached
			int pos = 1;
			ListNode<T>* prev_node = head;
			while (pos != index) {
				prev_node = prev_node->next;
				pos++;
			}
			ListNode<T>* next_node = prev_node->next->next;

			//insert the new node
			delete prev_node->next;
			prev_node->next = new_node;
			new_node->prev = prev_node;
			next_node->prev = new_node;
			new_node->next = next_node;
		}
		ListNode<T>* getHead() {
			return head;
		}
		ListNode<T>* getTail() {
			return tail;
		}
		int getSize() {
			return size;
		}
};

class LineEditor {
	private:
		LinkedList<std::string>* lines;
		const int MAX_LINE_LEN;
	public:
		LineEditor(int line_capacity)
		: MAX_LINE_LEN(line_capacity) {
			lines = new LinkedList<std::string>();
		}
		~LineEditor() {
			delete lines;
		}
		void insert(int index, std::string line) {
			if (line.length() <= MAX_LINE_LEN)
				lines->insert(index, line);
		}
		void insertEnd(std::string line) {
			lines->insertEnd(line);
		}
		void del(int index) {
			lines->del(index);
		}
		void edit(int index, std::string line) {
			if (line.length() <= MAX_LINE_LEN)
				lines->edit(index, line);
		}
		void search(std::string text) {
			ListNode<std::string>* cur_node = lines->getHead();
			bool not_found = true;
			for (int i = 1; i <= lines->getSize(); i++) {
				cur_node = cur_node->next;
				if (cur_node->data.find(text) != std::string::npos) {
					std::cout << i << " " << cur_node->data << std::endl;
					not_found = false;
				}
			}
			if (not_found)
				std::cout << "not found" << std::endl;
		}
		void print() {
			ListNode<std::string>* cur_node = lines->getHead();
			for (int i = 1; i <= lines->getSize(); i++) {
				cur_node = cur_node->next;
				std::cout << i << " " << cur_node->data << std::endl;
			}
		}
};

int main() {
	LineEditor* document = new LineEditor(80);
	while (true) {
		std::string input;
		getline(std::cin, input);
		std::string command = input.substr(0, input.find(' '));
		if (command == "insertEnd") {
			int quote_pos_1 = input.find('"');
			int quote_pos_2 = input.find('"', quote_pos_1 + 1);
			std::string text = input.substr(quote_pos_1 + 1, quote_pos_2 - quote_pos_1 - 1); // remove quotes
			document->insertEnd(text);
		}
		else if (command == "insert") {
			std::stringstream ss(input);
			std::string temp;
			int line_number;
			while(std::getline(ss, temp, ' '))
				if(std::stringstream(temp) >> line_number)
					break;
			int quote_pos_1 = input.find('"');
			int quote_pos_2 = input.find('"', quote_pos_1 + 1);
			std::string text = input.substr(quote_pos_1 + 1, quote_pos_2 - quote_pos_1 - 1); // remove quotes
			document->insert(line_number, text);
		}
		else if (command == "delete") {
			std::stringstream ss(input);
			std::string temp;
			int line_number;
			while(std::getline(ss, temp, ' '))
				if(std::stringstream(temp) >> line_number)
					break;
			document->del(line_number);
		}
		else if (command == "edit") {
			std::stringstream ss(input);
			std::string temp;
			int line_number;
			while(std::getline(ss, temp, ' '))
				if(std::stringstream(temp) >> line_number)
					break;
			int quote_pos_1 = input.find('"');
			int quote_pos_2 = input.find('"', quote_pos_1 + 1);
			std::string text = input.substr(quote_pos_1 + 1, quote_pos_2 - quote_pos_1 - 1); // remove quotes
			document->edit(line_number, text);
		}
		else if (command == "print") {
			document->print();
		}
		else if (command == "search") {
			int quote_pos_1 = input.find('"');
			int quote_pos_2 = input.find('"', quote_pos_1 + 1);
			std::string text = input.substr(quote_pos_1 + 1, quote_pos_2 - quote_pos_1 - 1); // remove quotes
			document->search(text);
		}
		else if (command == "quit") {
			break;
		}
	}
	delete document;
}