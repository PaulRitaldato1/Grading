
#include <string>
#include <iostream>
#include <vector>
class Node {
public:
	std::string line;
	Node* next = NULL;
};

class LinkedList
{
public:
	Node * FirstNode = NULL;
	Node* LastNode = NULL;
	int size = 0;

	void insert(std::string content)
	{
		Node* n = createNdoe(content);
		if (FirstNode == NULL)
		{
			FirstNode = n;
			LastNode = n;
		}
		else
		{
			LastNode->next = n;
			LastNode = n;
		}
		size++;
	}

	void insert(std::string content, int pos)
	{
		Node* n = createNdoe(content);
		if (pos == 0)
		{
			n->next = FirstNode;
			FirstNode = n;
			if (LastNode == NULL)
			{
				LastNode = n;
			}
		}
		else if (pos == size)
		{
			LastNode->next = n;
			LastNode = n;
		}
		else if (pos > size)
		{
			return;
		}
		else
		{
			Node* current = FirstNode;
			for (int i = 0; i < pos - 1; i++)
			{
				current = current->next;
			}
			n->next = current->next;
			current->next = n;
		}
		size++;
	}

	Node* createNdoe(std::string content)
	{
		Node* temp = new Node;
		temp->next = NULL;
		temp->line = content;
		return temp;
	}

	void deleteNode(int pos)
	{
		if (size == 0)
		{
			return;
		}
		if (pos == 0)
		{
			Node* temp = FirstNode;
			FirstNode = FirstNode->next;
			delete(temp);
		}
		else if (pos == size - 1)
		{
			Node* temp = LastNode;
			Node* current = FirstNode;
			for (int i = 0; i < pos - 1; i++)
			{
				current = current->next;
			}
			LastNode = current;
			LastNode->next = NULL;
			delete(temp);
		}
		else if (pos >= size)
		{
			return;
		}
		else
		{
			Node* current = FirstNode;
			for (int i = 0; i < pos - 1; i++)
			{
				if (i > size)
				{
					return;
				}
				current = current->next;
			}
			Node* temp = current->next;
			current->next = temp->next;
			delete(temp);

		}
		size--;
	}

	class Iterator;

	class Iterator
	{
	public:
		Iterator(Node *first)
		{
			currentnode = first;
		}

		// Prefix ++ overload 
		Iterator& operator++()
		{
			if (currentnode != NULL)
				currentnode = currentnode->next;
			return *this;
		}


		bool operator!=(const Iterator& iterator)
		{
			return currentnode != iterator.currentnode;
		}

		std::string operator*()
		{
			return currentnode->line;
		}

	private:
		Node * currentnode;
	};

	Iterator Begin()
	{
		return Iterator(FirstNode);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

};


class LineEditor
{
private:
	LinkedList * l;
public:
	LineEditor()
	{
		l = new LinkedList;
	}
	void insertEnd(std::string text)
	{
		l->insert(text);
	}
	void insert(int pos, std::string text)
	{
		if (pos <= l->size && pos >= 0) {
			l->insert(text, pos);
		}
	}
	void deleteLine(int pos)
	{
		if (pos <= l->size && pos >= 0) {
			l->deleteNode(pos);
		}
	}
	void edit(int pos, std::string text)
	{
		if (pos <= l->size && pos >= 0) {
			l->deleteNode(pos);
			l->insert(text, pos);
		}
	}

	void print()
	{

		int x = 1;
		for (LinkedList::Iterator start = l->Begin(); start != l->End(); ++start)
		{
			std::cout << x << " " << *start << "\n";
			x++;
		}

	}

	void search(std::string text)
	{
		int x = 1;
		bool found = false;
		for (LinkedList::Iterator start = l->Begin(); start != l->End(); ++start)
		{
			if ((*start).find(text) != std::string::npos)
			{
				found = true;
				std::cout << x << " " << *start << "\n";
			}
			x++;
		}
		if (!found)
		{
			std::cout << "not found" << "\n";
		}
	}
};



int main()
{
	LineEditor *l = new LineEditor;
	while (true) {
		std::string choice;
		std::getline(std::cin, choice);
		std::vector<std::string> words;
		size_t pos = 0;
		std::string token;
		while ((pos = choice.find(' ')) != std::string::npos || (pos = choice.find('\"')) != std::string::npos) {
			if (choice.at(0) == '\"')
			{
				choice.erase(0, 1);
				token = choice.substr(0, choice.find("\""));
				pos = token.length();
			}
			else
			{
				token = choice.substr(0, pos);
			}
			words.push_back(token);
			choice.erase(0, pos + 1);
		}
		words.push_back(choice);
		if (words.at(0).compare("print") == 0)
		{
			l->print();
		}
		else if (words.at(0).compare("insertEnd") == 0)
		{

			l->insertEnd(words.at(1));
		}
		else if (words.at(0).compare("insert") == 0)
		{

			l->insert(std::stoi(words.at(1)) - 1, words.at(2));
		}
		else if (words.at(0).compare("delete") == 0)
		{

			l->deleteLine(std::stoi(words.at(1)) - 1);
		}
		else if (words.at(0).compare("edit") == 0)
		{

			l->edit(std::stoi(words.at(1)) - 1, words.at(2));
		}
		else if (words.at(0).compare("search") == 0)
		{
			l->search(words.at(1));
		}
		else if (words.at(0).compare("quit") == 0)
		{
			break;
		}
	}


}
