#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

class LinkedList
{
public:
	struct Node
	{
		string data;
		Node *prev;
		Node *next;

	};
	void insertEnd(const string&data);
	void insert(const string&data, unsigned int index);
	void Delete(unsigned int index);
	void print() const;
	void find(const string&data);
	void edit(const string&data, unsigned int index);
	Node *GetNode(unsigned int index);

	LinkedList();
	LinkedList(const LinkedList &list);
	~LinkedList();

private:
	Node * head;
	Node *tail;
	unsigned int count_;
};

LinkedList::LinkedList()
{
	this->count_ = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

LinkedList::LinkedList(const LinkedList &list)
{
	this->count_ = list.count_;
	this->head = list.head;
	this->tail = list.tail;
}

LinkedList::~LinkedList()
{
	if (head != nullptr) {
		Node *current = head;

		while (current != nullptr) {
			Node *next = current->next;
			delete current;
			current = next;
			//cout << "destructor called" << endl;
		}
		head = nullptr;
		tail = nullptr;

	}


}

void LinkedList::insertEnd(const string&data)
{
	Node *temp = new Node;

	if (this->count_ == 0) {
		temp->data = data;
		this->head = temp;
		this->tail = temp;

	}
	else {
		temp->data = data;
		temp->next = nullptr;
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	this->count_ += 1;
}

void LinkedList::insert(const string&data, unsigned int index)
{

	Node *current = GetNode(index);
	Node *temp = new Node;
	if (index == 0) {
		temp->data = data;
		temp->next = head;
		temp->prev = nullptr;
		head->prev = temp;
		head = temp;
	}
	else if (index == count_) {
		temp->data = data;
		temp->next = nullptr;
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	else {
		temp->data = data;
		temp->next = current;
		temp->prev = current->prev;
		current->prev->next = temp;
		current->prev = temp;
	}
	this->count_ += 1;
}

LinkedList::Node* LinkedList::GetNode(unsigned int index)
{
	Node *current = head;
	if (index == count_) {
		for (unsigned int i = 1; i < index; i++) {
			current = current->next;
		}
	}
	else {
		for (unsigned int i = 0; i < index; i++) {
			current = current->next;
		}
	}
	return current;
}

void LinkedList::Delete(unsigned int index)
{
	Node *temp = GetNode(index);
	Node *previous = temp->prev;
	Node *next = temp->next;
	previous->next = next;
	next->prev = previous;
	delete temp;
	this->count_ -= 1;
}

void LinkedList::print() const {
	Node *current = head;
	int line = 1;
	while (current != nullptr) {
		cout << line << " " << current->data << endl;
		current = current->next;
		line += 1;
	}

}
void LinkedList::find(const string&data)
{
	Node *current = head;
	int line = 1;
	while (current != nullptr) {
		if (current->data.find(data, 0) != string::npos) {
			cout << line << " " << current->data << endl;
			break;
		}
		else {
			current = current->next;
			line += 1;
		}
	}


}

void LinkedList::edit(const string&data, unsigned int index)
{
	Node *current = GetNode(index);
	current->data = data;
	// GetNode(index)->data = data;
}

int main()
{
	LinkedList list;
	string str1;

	while (str1 != "quit") {
		char choice[80];
		cin.getline(choice, sizeof(choice));
		string command = choice;

		if (command.find("print") != string::npos) {

			list.print();
		}
		if (command.find("insertEnd") != string::npos) {
			list.insertEnd(command.substr(11, command.size() - 12));
		}
		if (command.find("insert ") != string::npos) {
			string str = command.substr(7, command.size() - 12);
			const char * info = str.c_str();
			int index = atoi(info);
			list.insert(command.substr(10, command.size() - 11), index - 1);
		}

		if (command.find("delete ") != string::npos) {
			string str = command.substr(7, command.size() - 12);
			const char * info = str.c_str();
			int index = atoi(info);
			list.Delete(index);
		}
		if (command.find("edit") != string::npos) {
			string str = command.substr(5, command.size() - 12);
			const char * info = str.c_str();
			int index = atoi(info);
			list.edit(command.substr(8, command.size() - 9), index);

		}
		if (command.find("search") != string::npos) {
			list.find(command.substr(8, command.size() - 12));
		}
		if (command.find("quit") != string::npos) {
			str1 = "quit";
		}

	}

	return 0;
}