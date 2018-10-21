#include<iostream>
#include<string>
using namespace std;

struct node
{
	string line;
	node* next = NULL;
};

node* insertEnd(node *head, string s)
{
	node* n = new node;
	n->line = s;
	n->next = NULL;
	if(head == NULL)
	{
		head = n;
	}
	else
	{
		node *temp = new node;
		temp = head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = n;
	}
	return head;
}
node* insert(node* head, int lineNum, string s)
{
	node* n = new node();
	n->line = s;
	n->next = NULL;
	if(lineNum == 1)
	{
		if(head != NULL)
		{
			n->next = head->next;
		}
		head = n;
	}
	else
	{
		node* temp = head;
		for(int i = 0; i < lineNum-2; i++)
		{
			temp = temp->next;
		}
		n->next = temp->next;
		temp->next = n;
	}
	return head;
}
node* deleteLine(node* head, int lineNum)
{
	if(lineNum == 1)
	{
		head = head->next;
	}
	else
	{
		node* temp = head;
		for(int i = 0; i < lineNum-2; i++)
		{
			temp = temp->next;
		}
		temp->next = temp->next->next;
	}
	return head;
}
void edit(node* head, int lineNum, string s)
{
	if(head != NULL)
	{
		for(int i = 0; i < lineNum-1; i++)
		{
			head = head->next;
		}
		head->line = s;
	}
}
void print(node* head)
{
	int i = 1;
	while(head != NULL)
	{
		cout << i << " " << head->line << "\n";
		head = head->next;
		i++;
	}
}
void search(node* head, string s)
{
	int i = 1;
	bool found = false;
	while(head != NULL)
	{
		if(head->line.find(s) != string::npos)
		{
			found = true;
			cout << i << " " << head->line << "\n";
		}
		head = head->next;
		i++;
	}
	if(!found)
	{
		cout << "not found";
	}
}

int main()
{
	bool run = true;
	string one;
	string two;
	string three;
	node* start = NULL;
	//start->line = NULL;
	//start->next = NULL;
	while(run)
	{
		cin >> one;
		
		if(one.compare("insertEnd") == 0)
		{
			getline(cin, two);
			two = two.substr(2,two.size()-3);
			start = insertEnd(start, two);
		}
		else if(one.compare("insert") == 0)
		{
			cin >> two;
			getline(cin, three);
			three = three.substr(2,three.size()-3);
			start = insert(start, stoi(two), three);
		}
		else if(one.compare("delete") == 0)
		{
			cin >> two;
			start = deleteLine(start, stoi(two));
		}
		else if(one.compare("edit") == 0)
		{
			cin >> two;
			getline(cin, three);
			three = three.substr(2,three.size()-3);
			edit(start, stoi(two), three);
		}
		else if(one.compare("print") == 0)
		{
			print(start);
		}
		else if(one.compare("search") == 0)
		{
			getline(cin, two);
			two = two.substr(2,two.size()-3);
			search(start, two);
		}
		else if(one.compare("quit") == 0)
		{
			run = false;
		}
		
	}
}