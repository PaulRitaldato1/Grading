#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct node
{
	string text;
	node *next;
};
class list
{
private:
	node *head, *tail;
public:
	list()
	{
		head = NULL;
		tail = NULL;
	}
	void insertEnd(string writing)
	{
		node *temp = new node;
		temp->text = writing;
		temp->next = NULL;
		if (this->head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			this->tail->next = temp;
			tail = temp;
		}
	}
	void insert(int num, string writing) {
		node *curr = new node;
		node *prev = new node;
		node *data = new node;
		curr = head->next;
		prev = head;
		data->text = writing;
		data->next = NULL;
		if (num == 1) {
			data->next = this->head;
			this->head = data;
		}

		for (int i = 1; i < num - 1; i++) {
			if (curr == NULL)
				return;
			prev = curr;
			curr = curr->next;
		}
		data->next = curr;
		prev->next = data;


	}
	void del(int index) {
		node *prev = new node;
		node *pointer = new node;
		prev = head;
		pointer = head->next;
		if (index == 1) {							//since the first point has nothing before it , it has its own way of happening
			head = head->next;
		}
		else {										// for everything else we take the the node before the index and make it point to the node after the index
			for (int i = 0; i < index - 2; i++) {
				prev = pointer;
				pointer = pointer->next;
				if (pointer == NULL)
					return;
			}
			if (pointer->next == NULL) {
				prev->next = NULL;
				return;
			}
			prev->next = pointer->next;

		}
	}
	void search(string writing) {                       // temp cycles to the given index and couting num for every line passed
		node *temp = new node;
		temp = this->head;
		int num = 1;
		int right = 0;
		while (temp != NULL) {
			if (temp->text.find(writing) < 10000000) {  // i had a hard time figuring out the .find method but i found out that if it doesnt occur the the value it produces is extremely huge while if it does occur it gives the index of the character where it first occurs, and since our strings can have no more than 80 characters, by putting a big number as a constant we guarantee that if a substring does occur it will be caught.
				cout << num << temp->text << endl;   	//prints data at temp and the num which is the number of lines that temp
				right++;
			}
			temp = temp->next;
			num++;
		}
		if (right == 0)
			cout << "not found" << endl;


	}
	void edit(int index, string writing)            // temp cycles to the proper index, then changes the text to the parameter text;
	{
		node *temp = new node;
		temp = head;
		for (int i = 1; i < index; i++) {
			temp = temp->next;
		}
		temp->text = writing;
	}
	void print() {                                // function loops through the linked list while there is still stuff in it and prints all data
		node *temp = new node;
		temp = head;
		int i = 1;
		while (temp) {
			cout << i << temp->text << endl;
			temp = temp->next;
			i++;
		}



	}
};


int main()
{

	string command;  //the direction which will be performed
	string writing;  //text inserted 
	int index;		// place where we insert 
	list linkedList; //create the linked list from the class above
	cin >> command;    // take in our first command
	while (command.compare("quit") != 0) {
		if (command.compare("insertEnd") == 0) {
			getline(cin, writing);
			writing.erase(remove(writing.begin(), writing.end(), '"'), writing.end()); //we trim the " " from the strings, same for                                     all methods with data;
			linkedList.insertEnd(writing);
		}
		else if (command.compare("insert") == 0) {                      //user input is index and data, insert data at index;
			cin >> index;
			getline(cin, writing);
			writing.erase(remove(writing.begin(), writing.end(), '"'), writing.end());
			linkedList.insert(index, writing);
		}
		else if (command.compare("print") == 0)                // prints the whole linked list, no parameters
			linkedList.print();
		else if (command.compare("delete") == 0) {				//if delete, send index which to delete
			cin >> index;
			linkedList.del(index);
		}
		else if (command.compare("search") == 0) {               // if search print the line and the text with parameter index ;
			getline(cin, writing);
			writing.erase(remove(writing.begin(), writing.end(), '"'), writing.end());
			linkedList.search(writing);
		}
		else if (command.compare("edit") == 0) {            //if edit, call edit method with the parameter of the index and the                                                                                         changed text
			cin >> index;
			getline(cin, writing);
			writing.erase(remove(writing.begin(), writing.end(), '"'), writing.end());
			linkedList.edit(index, writing);
		}
		cin >> command;  //take in our command for the next round, if its quit then loop will instanty terminate
	}
}
