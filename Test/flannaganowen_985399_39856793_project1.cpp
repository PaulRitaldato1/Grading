#include <iostream>
#include <string>

using namespace std;

class Node {
	public:
		string value;
		Node *next = NULL;
};

class LinkedList {
	private:
		Node *head;
		Node *tail;

	public:
		LinkedList () {
			head = new Node();
			tail = head;
		}

		void insert(int index, string valueInput)
		{
			Node* thisNode = head;
			for (int i = 1; i < index; i++) {
				thisNode = thisNode->next;
				if (thisNode == NULL) {
					return;
				}
			}
			Node* newNode = new Node();
			newNode->next = thisNode->next;
			newNode->value = valueInput;
			if (index == 0) {
				newNode->next = head;
				head = newNode;
			}
			thisNode->next = newNode;
			if (tail == NULL && newNode->next == NULL) {
					tail = newNode;
			}
			return;
		}

		void push(string valueInput) {
			Node* newNode = new Node();
			newNode->value = valueInput;
			tail->next = newNode;
			tail = newNode;
			return;
		}

		void find(string valueInput)	{
			Node* thisNode = head;
			int index = 0;
            bool flag = false;
			for (thisNode; thisNode != NULL; thisNode = thisNode->next) {
				if ((thisNode->value).find(valueInput) != string::npos) {
					cout << index << " " << thisNode->value << endl;
                    flag = true;
                }
				index++;
			}
            if (!flag) {
                cout << "not found" << endl;
            }
            return;
		}

		Node* edit(int index, string valueInput) {
			Node* thisNode = head;
			for (int i = 0; i < index; i++) {
				thisNode = thisNode->next;
			}
			thisNode->value = valueInput;
		}

		void remove(int index) {
				Node* thisNode = head;
				for (int i = 1; i < index; i++) {
					thisNode = thisNode->next;
                    if (thisNode->next == NULL) {
                        return;
                    }
				}
				Node* delNode = thisNode->next;
				thisNode->next = delNode->next;
				delete delNode;
		}

		void print() {
			Node* thisNode = head;
            thisNode = thisNode->next;
			int index = 1;
			for (thisNode; thisNode != NULL; thisNode = thisNode->next) {
				cout << index << " " << thisNode->value << endl;
				index++;
			}
            return;
		}
};

int main() {
	LinkedList lineEditor;
	int firstQuote, lastQuote;
	string inputString;
	int loc = 0;
	int index = 0;
    int length = 0;

	while(true) {
		getline(cin, inputString);
		if (inputString.find("insertEnd") == 0) {
			firstQuote = inputString.find("\"") + 1;
			lastQuote = inputString.find("\"", firstQuote);
            length = lastQuote - firstQuote;
			string fString = inputString.substr(firstQuote, length);
			lineEditor.push(fString);
		} else if (inputString.find("insert ") == 0) {
			inputString = inputString.substr(7);
			index = stoi(inputString);
			firstQuote = inputString.find("\"") + 1;
			lastQuote = inputString.find("\"", firstQuote);
			length = lastQuote - firstQuote;
			string fString = inputString.substr(firstQuote, length);
			lineEditor.insert(index, fString);
		} else if (inputString.find("delete ") == 0) {
			inputString = inputString.substr(7);
			index = stoi(inputString);
			lineEditor.remove(index);
		} else if (inputString.find("edit ") == 0) {
			inputString = inputString.substr(5);
			index = stoi(inputString);
			firstQuote = inputString.find("\"") + 1;
			lastQuote = inputString.find("\"", firstQuote);
			length = lastQuote - firstQuote;
			string fString = inputString.substr(firstQuote, length);
			lineEditor.edit(index, fString);
		} else if (inputString.find("print") == 0) {
			lineEditor.print();
		} else if (inputString.find("search ") == 0) {
			firstQuote = inputString.find("\"") + 1;
			lastQuote = inputString.find("\"", firstQuote);
			length = lastQuote - firstQuote;
			string fString = inputString.substr(firstQuote, length);
			lineEditor.find(fString);
		} else if (inputString.find("quit") == 0) {
			break;
		} else {
			break;
		}
	}
	return 0;
}
