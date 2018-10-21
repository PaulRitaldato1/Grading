#pragma once
#include<string>

using namespace std;

class Node
{
public:
	string line;
	Node* next;

public:
	Node();
	Node(string line);
	~Node();
};

