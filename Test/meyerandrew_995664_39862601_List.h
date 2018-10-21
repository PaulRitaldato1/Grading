#ifndef LIST_H
#define LIST_H
#include<string>

struct Node {
	std::string line;
	Node* next;
	Node(std::string line);
};

class List {
	private:
		int size = 0;
		Node* head;
		Node* tail;
	public:
		void insert(std::string line, int index);
		void insertEnd(std::string line);
		void remove(int index);
		void edit(std::string newLine, int index);
		void print();
		void search(std::string line);
};

void printMenu();

#endif