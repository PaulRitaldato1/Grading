#include "pch.h"
#include <iostream>
#include <iomanip>
#include<string>
#include<cstring>
using namespace std;
class Node
{
	private:
		string data;
		Node* next;
	public:
		Node()
		{
			this->data = "";
			this->next = NULL;
		}
		Node(string a)
		{
			this->data = a;
			this->next = NULL;
		}
		string getData()
		{
			return this->data;
		}
		Node* getNext()
		{
				return this->next;
		}
		void setData(string new1)
		{
			this->data = new1;
		}
		void setNext(Node* ptr)
		{ 
			this->next = ptr;
		}
		void insert(string line)
		{
			if (next == NULL)
			{
				this->next = new Node(line);
				return;
			}
			this->next->insert(line);
		}
};
class LinkedList
{
private:
	Node * head;
public:
	LinkedList()
	{
		this->head = new Node();
		this->head = NULL;
	}
	void insert(string line)
	{
		if (head == NULL)
		{
			this->head = new Node(line);
		}
		else
			this->head->insert(line);
	}
	int listsize()
	{
		Node * current = this->head;
		int sum = 0;
		while (current != NULL)
		{
			sum++;
			current = current->getNext();
		}
		return sum;

	}
	void insert(string line, int pos)
	{
		if (pos == listsize())
			this->head->insert(line);
		else if (pos == 0)
		{
			Node* temp = this->head;
			this->head = new Node(line);
			this->head->setNext(temp);
		}
		else
		{

			Node* inserted = new Node(line);
			Node* curr = nodeAt(pos);
			Node* prev = nodeAt(pos - 1);
			inserted->setNext(curr);
			prev->setNext(inserted);
		}

	}
	Node* nodeAt(int pos)
	{
		Node* curr = this->head;
		int i = 0;
		if (pos > listsize())
		{
			return NULL;
		}
		else 
			while (i < pos)
			{
				curr = curr->getNext();
				i++;
			}
		return curr;
	}
	void print()
	{
		int i = 0;
		Node* curr = this->head;
		while (i<listsize())
		{
			cout << i + 1 << " " << curr->getData() << endl;
			i++;
			curr = curr->getNext();
		}

	}
	void search(string lookingFor)
	{
		bool found = false;
		Node*curr = this->head;
		int i = 0;
		while (curr!=NULL)
		{
			string temp = curr->getData();
			if (temp.find(lookingFor) != string::npos)
			//if(strstr(temp.c_str(), lookingFor.c_str()))
			
			{
				cout << i + 1 << " " << temp << endl;
				found = true;
			}
			i++;
			curr = curr->getNext();
		}
		if (!found)
			cout << "not found" << endl;
	}
	void edit(string line, int pos)
	{

		nodeAt(pos)->setData(line);
	}

	void deleter(int pos)
	{
		if (pos == 0)
		{
			this->head = this->head->getNext();
		}
		else
		{
			Node* prev = nodeAt(pos - 1);
			prev->setNext(prev->getNext()->getNext());
		}

	}




};

int main()
{
	LinkedList lineEdit = LinkedList();
	bool cont = true;
	string lineToParse;
	while (cont)
	{
		getline(cin,lineToParse);
		if (lineToParse.compare("quit") == 0)
		{
			cont = false;
		}
		else if (lineToParse.compare("print") == 0)
		{
			lineEdit.print();
		}
		else if (lineToParse.substr(0, 6).compare("delete") == 0)
		{
			if (stoi(lineToParse.substr(7, 8)) - 1 < lineEdit.listsize())
			{
				lineEdit.deleter(stoi(lineToParse.substr(7, 8)) - 1);
			}
		}
		else if (lineToParse.substr(0, 6).compare("search") == 0)
		{
			unsigned first = lineToParse.find("\"")+1;
			unsigned last = lineToParse.find_last_of("\"");
			string strNew = lineToParse.substr(first, last - first);
			lineEdit.search(strNew);
		}
		else if (lineToParse.substr(0, 4).compare("edit") == 0)
		{
			if (stoi(lineToParse.substr(5, 6)) - 1 < lineEdit.listsize())
			{
				unsigned first = lineToParse.find("\"") + 1;
				unsigned last = lineToParse.find_last_of("\"");
				string strNew = lineToParse.substr(first, last - first);
				lineEdit.edit(strNew, stoi(lineToParse.substr(5, 6)) - 1);
			}
		}
		else if (lineToParse.substr(0, 9).compare("insertEnd") == 0)
		{
			unsigned first = lineToParse.find("\"")+1;
			unsigned last = lineToParse.find_last_of("\"");
			string strNew = lineToParse.substr(first, last - first);
			lineEdit.insert(strNew);
		}
		else if (lineToParse.substr(0, 6).compare("insert") == 0)
		{
			if (stoi(lineToParse.substr(7, 8)) - 1 <= lineEdit.listsize())
			{
				unsigned first = lineToParse.find("\"") + 1;
				unsigned last = lineToParse.find_last_of("\"");
				string strNew = lineToParse.substr(first, last - first);
				lineEdit.insert(strNew, stoi(lineToParse.substr(7, 8)) - 1);
			}
		}
		else
			cout << "Uh what?"<<endl;
		cin.clear();
	}
	return 0;
}
