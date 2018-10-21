// COP3530Assignment1.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class LineList 
{
	private:
		struct Node
		{
			string data;
			Node *prev;
			Node *next;

			Node(const string & d = string{}, Node * p = nullptr, Node * n = nullptr)
				: data{ d }, prev{ p }, next{ n } { }

			Node(string && d, Node * p = nullptr, Node * n = nullptr)
				: data{ std::move(d) }, prev{ p }, next{ n } {}

		};
	public:
		class const_iterator
		{
			public:
				const_iterator() : current{ nullptr } {}

				const string & operator* () const 
					{ return retrieve(); }
				
				const_iterator & operator++ ()
				{
					current = current->next;
					return *this;
				}

				const_iterator operator++ (int)
				{
					const_iterator old = *this;
					++(*this);
					return old;
				}

				bool operator== (const const_iterator & rhs) const
					{ return current == rhs.current; }
				bool operator!= (const const_iterator & rhs) const
					{ return !(*this == rhs); }

			protected:
				Node *current;

				string & retrieve() const
					{ return current->data; }
				const_iterator(Node *p) : current{ p } {}

				friend class LineList;
		};
		class iterator : public const_iterator
		{
			public:
				iterator(){}

				string & operator* ()
					{ return const_iterator::retrieve(); }
				const string & operator* () const
					{ return const_iterator::operator*(); }

				iterator & operator++ ()
				{
					this->current = this->current->next;
					return *this;
				}

				iterator operator++ (int)
				{
					iterator old = *this;
					++(*this);
					return old;
				}

			protected:
				iterator(Node *p) : const_iterator{ p } {}

				friend class LineList;
		};
	public:
		//LinkedList Operators and constructs
		LineList()
			{ init(); }

		~LineList()
		{
			clear();
			delete head;
			delete tail;
		}

		LineList( const LineList & rhs )
		{
			init();
			for (auto & x : rhs)
				push_back(x);
		}

		LineList & operator= (const LineList & rhs)
		{
			LineList copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		LineList(LineList && rhs)
			: theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
		{
			rhs.theSize = 0;
			rhs.head = nullptr;
			rhs.tail = nullptr;
		}

		LineList & operator= (LineList && rhs)
		{
			std::swap(theSize, rhs.theSize);
			std::swap(head, rhs.head);
			std::swap(tail, rhs.tail);

			return *this;
		}

		//iterator and const_iterator functions
		iterator begin()
			{ return { head->next }; }
		const_iterator begin() const 
			{ return { head->next }; }
		iterator end() 
			{ return { tail->prev }; }
		const_iterator end() const
			{ return { tail->prev }; }

		int size() const
			{ return theSize; }
		bool empty() const
			{ return size() == 0; }

		void clear()
		{
			while (!empty())
				pop_front();
		}

		string & front()
			{ return *begin(); }
		const string & front() const
			 { return *begin(); }
		string & back()
			 { return *end(); }
		 const string & back() const
			 { return *end(); }

		 void push_front(const string & x)
			 { insert(begin(), x); }
		 void push_front(string && x)
			 { insert(begin(), std::move(x)); }
		 void push_back(const string & x)
			 { insert(++end(), x); }
		 void push_back(string && x)
		 { insert(++end(), std::move(x)); }
		 void pop_front()
			 { erase(begin()); }
		 void pop_back()
			 { erase(++end()); }

		 iterator insert(iterator itr, const string & x)
		{
			 Node *p = itr.current;
			 theSize++;
			 return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
		 }
		 iterator insert(iterator itr, string && x)
		{
			 Node *p = itr.current;
			 theSize++;
			 return { p->prev = p->prev->next = new Node{ std::move(x), p->prev, p } };
		 }

		 iterator erase(iterator itr)
		{
			 Node *p = itr.current;
			 iterator retVal{ p->next };
			 p->prev->next = p->next;
			 p->next->prev = p->prev;
			 delete p;
			 theSize--;
			 return retVal;
		 }

		 iterator erase(iterator from, iterator to)
		{
			 for (iterator itr = from; itr != to; )
				 itr = erase(itr);

			 return to;
		 }

	private:
		int theSize;
		Node *head;
		Node *tail;

		void init()
		{
			theSize = 0;
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->prev = head;
		}

};

int main()
{ 
	LineList lineList{};
	LineList::iterator lineIter = lineList.begin();
	string lineInput;
	string command;
	string line;
	int commandNum = 0;
	int amount = 0;

	
	cout << "User commands:" << endl << endl;
	cout << "insertEnd \"text\" -- insert given text at the end of the document" << endl;
	cout << "insert # \"text\" -- insert given text at the line indicated by index(#) given" << endl;
	cout << "delete # -- delete line at index(#) given" << endl;
	cout << "edit # \"text\" -- replace the line at the index(#) given with the given text" << endl;
	cout << "print -- print the entire document, with line numers" << endl;
	cout << "search \"text\" -- print the line number and line that contains the given text." << endl;
	cout << "quit -- quit/exit the program" << endl << endl;

	while (getline(cin, lineInput))
	{
		for (int i = 0; i < lineInput.length(); i++)
		{
			if (lineInput[i] != ' ' && line.empty())
				command += lineInput[i];
			else
			{
				if (i < lineInput.length() - 1)
						line += lineInput[i + 1];
				else
					break;
			}
		}
		line.erase(remove(line.begin(), line.end(), '\"'), line.end());
		if (command == "insertEnd")
			commandNum = 1;
		else if (command == "insert")
			commandNum = 2;
		else if (command == "delete")
			commandNum = 3;
		else if (command == "edit")
			commandNum = 4;
		else if (command == "print")
			commandNum = 5;
		else if (command == "search")
			commandNum = 6;
		else if (command == "quit")
			commandNum = 7;
	
		if ((command == "insert" || command == "delete" || command == "edit") && isdigit(line[0]))
		{
			bool wordWritten = false;
			amount = line[0] - '0';
			for (int i = 1; i < line.length(); i++)
			{
				if (line[i] != ' ' && wordWritten == false)
				{
					line = line.substr(i, line.length() - i + 1);
					wordWritten = true;
				}
				else if (line[i] == ' ' && wordWritten == false)
					continue;
				else if (wordWritten == true)
					break;
			}

		}
	
		if (line.length() > 80)
		{
			cout << "Out of Bounds(line too long): Please try again" << endl;
			line = "";
			command = "";
			continue;
		}
		switch (commandNum)
		{
		case(1):
			lineList.push_back(line);
			break;
		case(2):
			if (amount <= lineList.size())
			{
				lineIter = lineList.begin();
				for (int i = 0; i < lineList.size(); i++)
				{
					if (i == amount - 1)
					{
						lineList.insert(lineIter, line);
					}
					lineIter++;
				}
			}
			break;
		case(3):
			if (amount <= lineList.size())
			{
				lineIter = lineList.begin();
				for (int i = 0; i < lineList.size(); i++)
				{
					if (i == amount - 1)
					{
						lineList.erase(lineIter);
						break;
					}
					lineIter++;
				}
			}

			break;
		case(4):
			if (amount <= lineList.size())
			{
				lineIter = lineList.begin();
				for (int i = 0; i < lineList.size(); i++)
				{
					if (i == amount - 1)
					{
						lineList.insert(lineIter, line);
						lineList.erase(lineIter);
						break;
					}
					lineIter++;
				}
			}
			break;
		case(5):
			lineIter = lineList.begin();
			for (int i = 0; i < lineList.size(); i++)
			{
				cout << i + 1 << " " << *lineIter << endl;
				lineIter++;
			}

			break;
		case(6):
			lineIter = lineList.begin();
			for (int i = 0; i < lineList.size(); i++)
			{
				if (line == *lineIter)
				{
					cout << i + 1 << " " << *lineIter << endl;
					break;
				}
				if (i == lineList.size() - 1)
					cout << "not found" << endl;
				lineIter++;
			}
			break;
		case(7):
			exit(0);
			break;
		}
		
		commandNum = 0;
		command = "";
		line = "";
			
	}

    return 0;
}

