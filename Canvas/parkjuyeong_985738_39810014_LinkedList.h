#pragma once
#include "Node.h"
#include <utility>

using namespace std;

class LinkedList
{
private:
	int size;
	Node* head;

public:
	LinkedList();
	~LinkedList();
	void insert(string line);
	void insert(int n, string line);
	void del(int n);
	void edit(int n, string str);
	pair<int, string> search(string str);
	void print();
};

