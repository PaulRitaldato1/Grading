#pragma once
#include <string>

class LinkedList
{
private:
	struct Node {
		Node* next;
		std::string data;
		int lineNum;
	};
	Node* head;
	Node* tail;
	Node* iter;
	
public:
	LinkedList();
	~LinkedList();
	void insertEnd(std::string newLine);
	void insert(std::string insertLine, int insertSlot);
	void print();
	void edit(int lineNum, std::string editLine);
	void deleteNode(int deleteSlot);
	void search(std::string searchString);
	void fixLineNum();
};


