#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
public:
	string line;
	Node* next;

	Node()
	{
		this->line = "";
		this->next = nullptr;
	}
	Node(string line, Node* next)
	{
		this->line = line;
		this->next = next;
	}
};

void insertEnd(string text, Node* head)
{
	if (head->line == "")
	{
		head->line = text;
		return;
	}

	Node* current = head;
	while (current->next != nullptr)
		current = current->next;

	Node* newEnd = new Node(text, nullptr);
	current->next = newEnd;
}

void insertLine(int lineNum, string text, Node* head)
{
	int size = 0;
	Node* temp1 = head;
	while (temp1 != nullptr)
	{
		size++;
		temp1 = temp1->next;
	}
	if (lineNum > size + 1)
		return;
	else if (lineNum == size + 1)
	{
		insertEnd(text, head);
		return;
	}

	Node* current = head;

	if (lineNum == 1)
	{
		head = new Node(text, nullptr);
	}
	else
	{
		for (int i = 1; i < lineNum - 1; i++)
			current = current->next;

		Node* newNode = new Node(text, nullptr);
		if (current->next == nullptr)
		{
			current->next = newNode;
		}
		else
		{
			newNode->next = current->next;
			current->next = newNode;
		}
	}
}

void deleteLine(int lineNum, Node* head)
{
	int size = 0;
	Node* temp1 = head;
	while (temp1 != nullptr)
	{
		size++;
		temp1 = temp1->next;
	}
	if (lineNum > size)
		return;

	Node* current = head;
	if (lineNum == 1)
	{
		current = head->next;
		delete head;
		head = current;
	}
	else
	{
		for (int i = 1; i < lineNum - 1; i++)
			current = current->next;

		Node* temp = current->next;
		current->next = temp->next;
		delete temp;
	}
}

void editLine(int lineNum, string text, Node* head)
{
	Node* current = head;
	for (int i = 1; i < lineNum; i++)
		current = current->next;

	current->line = text;
}

void print(Node* head)
{
	int index = 1;
	Node* current = head;
	while (current != nullptr)
	{
		cout << index << " " << current->line << endl;
		index++;
		current = current->next;
	}
}

void search(string text, Node* head)
{
	Node* current = head;
	int index = 1;
	bool isFind = false;
	while (current != nullptr)
	{
		size_t found = current->line.find(text);
		if (found != std::string::npos)
		{
			cout << index << " " << current->line << endl;
			isFind = true;
		}

		current = current->next;
		index++;
	}

	if (!isFind)
		cout << "not found" << endl;
}


int main()
{
	Node* head = new Node;

	while (true)
	{
		char inputChar[80];
		std::cin.getline(inputChar, 80);
		string input;
		input = inputChar;
		stringstream ss(input);
		string token;

		getline(ss, token, ' ');

		if (token == "insertEnd")
		{
			getline(ss, token, '"');
			getline(ss, token, '"');
			string text = token;

			insertEnd(text, head);
		}
		else if (token == "insert")
		{
			getline(ss, token, ' ');
			int lineNum = stoi(token);

			getline(ss, token, '"');
			getline(ss, token, '"');
			string text = token;
			insertLine(lineNum, text, head);
		}
		else if (token == "delete")
		{
			getline(ss, token, ' ');
			int lineNum = stoi(token);

			deleteLine(lineNum, head);
		}
		else if (token == "edit")
		{
			getline(ss, token, ' ');
			int lineNum = stoi(token);
			getline(ss, token, '"');
			getline(ss, token, '"');
			string text = token;

			editLine(lineNum, text, head);
		}
		else if (token == "print")
		{
			print(head);
		}
		else if (token == "search")
		{
			getline(ss, token, '"');
			getline(ss, token, '"');
			string text = token;
			search(text, head);
		}
		else if (token == "quit")
		{
			break;
		}
		else
		{
			cout << "Invalid input!" << endl;
		}

	}

	return 0;
}