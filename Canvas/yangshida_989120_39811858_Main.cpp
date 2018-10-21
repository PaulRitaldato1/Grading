#include <iostream>
#include <string>

using namespace std;

//your linked list implementation here
template <class T>
struct Node {
	T value;
	Node* next=NULL;
	Node(T value1) {
		value = value1;
	}
};

template <class T>
class LinkedList {
private:
	Node<T>* head;
public:
	//constructor
	LinkedList<T>(Node<T>* head1) {
		head = head1;
	}
	//add a node to anywhere in the linked list
	//if out of range, do nothing
	void addNode(T value, int index) {
		Node<T>* newNode = new Node<T>(value);
		//add to the first node
		if (index == 0) {
			newNode->next = head;
			head = newNode;
			return;
		}
		//add to middle or the end
		Node<T>* current = head;
		Node<T>* previous = NULL;
		while (index>0) {
			//exceed range
			if (current == NULL) {
				delete(newNode);
				return;
			}
			previous = current;
			current = current->next;
			index--;
		}
		previous->next = newNode;
		newNode->next = current;
		return;
	}
	//add a node to the end
	void addNode(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (head == NULL) {
			head = newNode;
			return;
		}
		Node<T>* current = head;
		Node<T>* previous = NULL;
		while (current!=NULL) {
			previous = current;
			current = current->next;
		}
		previous->next = newNode;
		return;
	}
	//delete a node in the linked list
	//if out of range, do nothing
	void deleteNode(int index) {
		//delete head
		if (index == 0 && head!=NULL) {
			Node<T>* temp = head;
			head = head->next;
			delete(temp);
			return;
		}
		//delete somewhere in the middle or the end
		Node<T>* current = head;
		Node<T>* previous = NULL;
		while (index > 0) {
			//check if out of range
			if (current == NULL) {
				return;
			}
			previous = current;
			current = current->next;
			index--;
		}
		if (current != NULL) {
			previous->next = current->next;
			delete(current);
		}
	}
	//delete the end node
	//if list is empty, do nothing
	void deleteNode() {
		//nothing in the list
		if (head == NULL) {
			return;
		}
		if (head->next == NULL) {
			Node<T>* temp = head;
			head = NULL;
			delete temp;
			return;
		}
		//delete tail
		Node<T>* current = head;
		Node<T>* previous = NULL;
		while (current->next != NULL) {
			previous = current;
			current = current->next;
		}
		previous->next = NULL;
		delete current;
	}
	Node<T>* getHead() {
		return head;
	}
};

//your line editor implementation here
class LineEditor {
private:
	LinkedList<string>* article;
	bool close;	//if the LineEditor is closed
public:
	//constructor
	LineEditor() {
		article = new LinkedList<string>(0);
		close = false;
	}
	//destructor
	~LineEditor() {
		delete(article);
	}
	//determine the input commands and decide what to do
	void control() {
		//separate command from parameter
		string input = "";
		getline(cin, input);
		input = trimString(input);
		string command = "";
		string param = "";
		int i = 0;
		for ( i ; i <= input.length(); i++) {
			if (input[i] == ' ') {
				command = input.substr(0, i);
				param = input.substr(i + 1);
				break;
			}
			if (input[i] == 0) {
				command = input;
			}
		}
		//determine action
		if (command == "insertEnd" && param[0] == '\"' && param[param.length() - 1] == '\"') {
			this->insertEnd(param.substr(1, param.length() - 2));
		}
		else if (command == "print" && param == "") {
			this->print();
		}
		else if (command == "search" && param[0] == '\"' && param[param.length() - 1] == '\"') {
			this->search(param.substr(1, param.length() - 2));
		}
		else if (command == "quit" && param == "") {
			this->quit();
		}
		else if(command=="delete" && isNum(param)){
			int lineNum = stoi(param);
			this->deleteLine(lineNum);
		}
		else if (command == "edit") {
			//separate parameter
			string param1 = "";
			string param2 = "";
			int i = 0;
			for (i; i <= param.length(); i++) {
				if (param[i] == ' ') {
					param1 = param.substr(0, i);
					param2 = param.substr(i + 1);
					break;
				}
				if (input[i] == 0) {
					param1 = param;
				}
			}
			if (isNum(param1) && param2[0] == '\"' && param2[param2.length() - 1] == '\"') {
				this->edit(param2.substr(1, param2.length() - 2), stoi(param1));
			}
		}
		else if (command == "insert") {
			//separate parameter
			string param1 = "";
			string param2 = "";
			int i = 0;
			for (i; i <= param.length(); i++) {
				if (param[i] == ' ') {
					param1 = param.substr(0, i);
					param2 = param.substr(i + 1);
					break;
				}
				if (input[i] == 0) {
					param1 = param;
				}
			}
			if (isNum(param1) && param2[0] == '\"' && param2[param2.length() - 1] == '\"') {
				this->insert(param2.substr(1, param2.length() - 2), stoi(param1));
			}
		}
	}
	//insert a line in the line editor
	void insert(string text, int lineNum) {
		article->addNode(text, lineNum-1);
	}
	//insert a line at the end
	void insertEnd(string text) {
		article->addNode(text);
	}
	//delete a line in the article
	void deleteLine(int lineNum) {
		article->deleteNode(lineNum-1);
	}
	//deelete the last line
	void deleteEnd() {
		article->deleteNode();
	}
	//print the article
	void print() {
		Node<string>* current = article->getHead();
		int count = 1;
		while (current != NULL) {
			cout << count << " " << current->value << endl;
			current = current->next;
			count++;
		}
	}
	//check if a string "text" contains another string "target"
	bool checkString(string text, string target) {
		if (target[0] == NULL) {
			return true;
		}
		if (text.length() < target.length()) {
			return false;
		}
		if (text[0] != target[0]) {
			return checkString(text.substr(1),target);
		}
		else {
			return checkString(text.substr(1), target.substr(1));
		}
	}
	//trim white spaces before and after string
	string trimString(string s) {
		if (s[0] != ' ' && s[s.length() - 1] != ' ') {
			return s;
		}
		if (s[0] == ' ') {
			s = s.substr(1);
		}
		if (s[s.length() - 1] == ' ') {
			s = s.substr(0, s.length() - 1);
		}
		return trimString(s);

	}
	//check if string "text" is a positive integer
	bool isNum(string text) {
		if (isdigit(text[0])) {
			if (text.length() == 1) {
				return true;
			}
			else{
				return isNum(text.substr(1));
			}
		}
		else {
			return false;
		}
	}
	//search for keywords in the article
	void search(string text) {
		Node<string>* current = article->getHead();
		int count = 1;
		int lengthOfText = text.length();
		bool found = false;
		while (current != NULL) {
			string currentText = current->value;
			if (currentText.length() < lengthOfText) {
				count++;
				current = current->next;
				continue;
			}
			else {
				if (checkString(currentText, text)) {
					cout << count << " " + currentText << endl;
					found = true;
				}
			}
			count++;
			current = current->next;
		}
		if (!found) {
			cout << "not found" << endl;
		}
	}
	//replace a line with string "text"
	void edit(string text, int lineNum) {
		Node<string>* current = article->getHead();
		if (lineNum <= 0) {
			return;
		}
		while (lineNum > 1) {
			if (current == NULL) {
				return;
			}
			else {
				current = current->next;
			}
			lineNum--;
		}
		if (current != NULL) {
			current->value = text;
		}
	}
	//quit
	void quit() {
		close = true;
	}
	//return if the line editor is closed
	bool getQuit() {
		return close;
	}
};

int main()
{
	//create a line editor
	LineEditor* le = new LineEditor();
	//loop until quit
	while (!(le->getQuit())) {
		//ask for input, determine action
		le->control();
	}
}