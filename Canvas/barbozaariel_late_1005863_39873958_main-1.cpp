#include <iostream>
#include <string>
#include <sstream>



using namespace std;

struct Node
{
	string data;
	Node * next;
};
Node * head = nullptr;
Node* NodeCreate(string value);
void insertEnd(Node * ptr, string text);
void insert(Node * ptr, int index, string text);
void removeIndex(Node * ptr, int index);
void edit(Node * ptr, int index, string text);
void print(Node * ptr);
void find(Node * ptr, string text);

int main()
{
	string option;
	string tmp;
	string stringIterator;
	int index;
	int part;
	stringstream stringStream;

	while (1)
	{
		getline(cin, option);

		if (option == "quit")
		{
			break;
		}
		else if (option == "print")
		{
			print(head);
		}

		else if (option.substr(0, 4) == "edit")
		{
			part = option.find(" ", 5);
			stringIterator = option.substr(5, part - 5);//
			stringStream << stringIterator;
			stringStream >> index;
			stringStream.clear();
			tmp = option.substr(part + 2);
			tmp.pop_back();
			edit(head, index, tmp);
		}
		else if (option.substr(0, 6) == "search")
		{
			tmp = option.substr(9);
			tmp.pop_back();
			find(head, tmp);

		}

		else if (option.substr(0, 9) == "insertEnd")
		{
			tmp = option.substr(11);
			tmp.pop_back();
			insertEnd(head, tmp);
		}
		else if (option.substr(0, 6) == "delete")
		{
			stringIterator = option.substr(7);
			stringStream << stringIterator;
			stringStream >> index;
			stringStream.clear();
			removeIndex(head, index);
		}
		else
		{
			part = option.find(" ", 7);
			stringIterator = option.substr(7, part - 7);
			stringStream << stringIterator;
			stringStream >> index;
			stringStream.clear();
			tmp = option.substr(part + 2);
			tmp.pop_back();
			insert(head, index, tmp);
		}
	}
	return 0;
}

Node* NodeCreate(string text)
{
	Node *n = new Node;
	n->data = text;
	n->next = nullptr;
	return(n);
}
void insertEnd(Node *pointer, string text)
{
	Node *n;
	n = NodeCreate(text);
	if (head == nullptr)
		head = n;
	else
	{
		while (pointer->next != nullptr)
			pointer = pointer->next;
		pointer->next = n;
	}
}
void insert(Node *pointer, int index, string text)
{
	Node *prev = nullptr;
	Node* holder = NodeCreate(text);
	int i;
	if (index < 5) {
		for (i = 1; i < index; i++)
		{
			prev = pointer;
			pointer = pointer->next;
		}
		if (prev == nullptr)
		{
			holder->next = head;
			head = holder;
		}
		else
		{
			holder->next = pointer;
			prev->next = holder;
		}
	}
}

void removeIndex(Node * ptr, int index)
{
	Node * tmp = nullptr;
	for (int i = 1; i < index; i++)
	{
		tmp = ptr;
		ptr = ptr->next;
	}
	tmp->next = ptr->next;
	delete ptr;
}

void edit(Node *pointer, int index, string text)
{
	for (int i = 1; i < index; i++)
	{
		pointer = pointer->next;
	}
	pointer->data = text;
}


void find(Node *pointer, string text)
{
	bool r = true;
	int i = 1;
	int count = 0;
	while (pointer)
	{
		if (pointer->data.find(text) != -1)
		{
			cout << i << " " << pointer->data << endl;
			r = false;
		}
		pointer = pointer->next;
		count++;
		i++;
	}
	if (pointer == nullptr && r != false) //string not found
		cout << "not found" << endl;
	//pointer = head;
	//bool cond = (pointer->data.find(text) == 0); //string not found
	//int r = 0;
	//int nodeCount = 0;
	//while (r < count && pointer != nullptr)
	//{
	//	if (cond)
	//	{
	//		r++;
	//	}
	//	nodeCount++;
	//	pointer = pointer->next;

	//}
	//if (r == nodeCount)
	//{
	//	cout << "not found" << endl;
	//}
	//	
}

void print(Node *pointer)
{
	if (pointer == nullptr)
		cout << "Document is empty" << endl;
	else
	{
		
		int i = 1;
		while (pointer)
		{
			cout << i << " " << pointer->data << endl;
			pointer = pointer->next;
			i++;
		}
	}
}