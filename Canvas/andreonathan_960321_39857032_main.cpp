#include <iostream>
#include <string>
// #include "main.h"

template < class T >
class LinkedList 
{
	private:
		struct Node 
		{
			T data;
			Node* next;
		};
		Node* head;
		
    public:
        void append( T s )
		{
			if (this->head == NULL)
			{
				this->head = new Node();
				this->head->data = s;
			}
			else
			{
				Node* temp = this->head;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				Node* new_node = new Node();
				temp->next = new_node;
				new_node->data = s;
			}
		};
		
		void print()
		{
			Node* temp = this->head;
			int line_count = 1;
			while (temp != NULL)
			{
				std::cout << line_count << ' ' << temp->data << '\n';
				temp = temp->next;
				line_count++;
			}
		};
		
		void insert( int index , T s )
		{
			if (index == 1)
			{
				Node* new_node = new Node();
				new_node->data = s;
				new_node->next = head;
				this->head = new_node;
			}
			else
			{
				Node* temp = this->head;
				int i = 1;
				while (i != index-1)
				{
					temp = temp->next;
					i++;
				}
				Node* new_node = new Node();
				new_node->data = s;
				new_node->next = temp->next;
				temp->next = new_node;
			}
		};
		
		void edit( int index, T s )
		{
			Node* temp = this->head;
			int i = 1;
			while (i != index)
			{
				temp = temp->next;
				i++;
			}
			temp->data = s;
		};
		
		void deleteNode( int index )
		{
			if (index == 1)
			{
				this->head = this->head->next;
				// TODO call destructor
			}
			else
			{
				Node* temp = this->head;
				int i = 1;
				while (i != index-1)
				{
					temp = temp->next;
					i++;
				}
				temp->next = temp->next->next;
				// TODO call destructor
			}
		};
		
		void search( T s )
		{
			Node* temp = this->head;
			int line_count = 1;
			while (temp != NULL && temp->data.find(s) == -1)
			{
				temp = temp->next;
				line_count++;
			}
			if (temp == NULL) return;
			std::cout << line_count << ' ' << temp->data << '\n';
		};
		
		LinkedList()
		{
			head = NULL;
		};
};

// template < class T >
// LinkedList<T>::LinkedList()
// {
	// std::cout << "creating List\n";
	// head = NULL;
// };

// template < class T >
// void LinkedList<T>::append( T s )
// {
	// if (this->head == NULL)
	// {
		// this->head = new Node();
		// this->head->data = s;
	// }
	// else
	// {
		// Node* temp = this->head;
		// while (temp->next != NULL)
		// {
			// temp = temp->next;
		// }
		// Node* new_node = new Node();
		// temp->next = new_node;
		// new_node->data = s;
	// }
// };

// template < class T >
// void LinkedList<T>::print()
// {
	// Node* temp = this->head;
	// int line_count = 1;
	// while (temp != NULL)
	// {
		// std::cout << line_count << ' ' << temp->data << '\n';
		// temp = temp->next;
		// line_count++;
	// }
// }

// template < class T >
// void LinkedList<T>::insert( int index, T s )
// {
	// if (index == 1)
	// {
		// Node* new_node = new Node();
		// new_node->data = s;
		// new_node->next = head;
		// this->head = new_node;
	// }
	// else
	// {
		// Node* temp = this->head;
		// int i = 1;
		// while (i != index-1)
		// {
			// temp = temp->next;
			// i++;
		// }
		// Node* new_node = new Node();
		// new_node->data = s;
		// new_node->next = temp->next;
		// temp->next = new_node;
	// }
// }

// template < class T >
// void LinkedList<T>::edit( int index, T s )
// {
	// Node* temp = this->head;
	// int i = 1;
	// while (i != index)
	// {
		// temp = temp->next;
		// i++;
	// }
	// temp->data = s;
// }

// template < class T >
// void LinkedList<T>::deleteNode( int index )
// {
	// if (index == 1)
	// {
		// this->head = this->head->next;
		// // TODO call destructor
	// }
	// else
	// {
		// Node* temp = this->head;
		// int i = 1;
		// while (i != index-1)
		// {
			// temp = temp->next;
			// i++;
		// }
		// temp->next = temp->next->next;
		// // TODO call destructor
	// }
// }

// template < class T >
// void LinkedList<T>::search( T s )
// {
	// Node* temp = this->head;
	// int line_count = 1;
	// while (temp != NULL && temp->data.find(s) == -1)
	// {
		// temp = temp->next;
		// line_count++;
	// }
	// if (temp == NULL) return;
	// std::cout << line_count << ' ' << temp->data << '\n';
// }


void main()
{
    LinkedList<std::string> list;
	std::string input;
	std::string skip;
	
	while (true)
	{
		std::cin >> input;
		
		if (input == "quit")
		{
			break;
		}
		else if (input == "print")
		{
			list.print();
		}
		else if (input == "insertEnd")
		{
			getline(getline(std::cin,skip,'"'),input,'"');
			list.append(input);
		}
		else if (input == "insert")
		{
			int index;
			std::cin >> index;
			getline(getline(std::cin,skip,'"'),input,'"');
			list.insert(index,input);
		}
		else if (input == "edit")
		{
			int index;
			std::cin >> index;
			getline(getline(std::cin,skip,'"'),input,'"');
			list.edit(index,input);
		}
		else if (input == "delete")
		{
			int index;
			std::cin >> index;
			list.deleteNode(index);
		}
		else if (input == "search")
		{
			getline(getline(std::cin,skip,'"'),input,'"');
			list.search(input);
		}
	}
}