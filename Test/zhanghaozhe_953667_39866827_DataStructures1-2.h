#include<iostream>
#include <sstream>
#include<string>

using namespace std;

void returnError();
void returnError2();
int getNextNum(string input);
string getRest(string input, int size);
bool isNumber(string str);
string truncateIt(string str, int choice, int indexlength);
string purifiCation(string str);

struct node {
	string name;
	node* next;
};

class list {
private:
	node * head, *tail, *lIst;
public:
	list()
	{	head = NULL;
		tail = NULL;
	}
	void insertEnd(string textToInsert);
	void insert(string textToInsert, int indexNum);
	void deletion(int indexNum);
	void edit(string textToDelete, int indexNum);
	void print();
	void search(int indexNum);
	void searchTerms(string textToSearch);
	void firstNode(string textToInsert);
	int getSize();
};