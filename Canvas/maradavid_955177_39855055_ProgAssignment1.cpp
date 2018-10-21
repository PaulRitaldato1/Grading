#include <iostream>
#include <queue> 
#include <string>
using namespace std;



class line
{
	
public:
	string text;
	int lineNumber;
	line *next = NULL;

	
};
class LinkedList
{
private:
	line *head;
	
public:
		
		LinkedList() {
			head = NULL;
			
		}
		void add(string value) {
			int lineNUmber = 1;
			line* nextLine = new line();
			nextLine->text = value;
			if (head == NULL) {
				head = nextLine;
				nextLine->lineNumber = 1;
			}
			else{
				
				line* cursor = head;
				while (cursor->next != NULL) {
					cursor = cursor->next;					
				}
				cursor->next = nextLine;
				nextLine->lineNumber = cursor->lineNumber + 1;
			}
			
		}
		void print() {
			line* cursor = head;
			while (cursor != NULL) {
				string displayedLine = to_string(cursor->lineNumber) + " " + cursor->text;			
			std::cout << displayedLine << std::endl;
			cursor = cursor->next;
			}

		}
		void search(string str) {
			line* cursor = head;
			bool foundWord = false;
			while (cursor != NULL) {
				if (cursor->text.find(str) != string::npos) {
					string displayedLine = to_string(cursor->lineNumber) + " " + cursor->text;
					std::cout << displayedLine << std::endl;
					foundWord = true;
				}
				cursor = cursor->next;
			}
			if (cursor == NULL&&foundWord==false) {
				cout << "not found\n";
			}
		}
		void edit(int i, string str) {
			line* cursor = head;
			while (cursor->lineNumber != i||cursor==NULL) {
				cursor = cursor->next;
			}
			if (cursor->lineNumber == i) {
				cursor->text = str;
			}

		}
		void insert(int i, string str) {
			line* newLine = new line();
			newLine->text = str;
			newLine->lineNumber = i;
			if (i == 1) {
				newLine->next = head;
			}
			else{
				line* cursor = head;
				while (cursor->next != NULL) {
					if (cursor->next->lineNumber==i) {
						newLine->next = cursor->next;
						cursor->next = newLine;
						cursor = cursor->next;
						cursor = cursor->next;
							while (cursor != NULL) {								
								
								cursor->lineNumber = cursor->lineNumber + 1;
								cursor = cursor->next;
							}
						break;
					}
					cursor = cursor->next;
				}
				if(cursor!=NULL){
					if (cursor->lineNumber == (i - 1)) {
						cursor->next = newLine;
					}
				}
				

			}

			
		}
		void deleteNode(int i) {
			if (i == 1) {
				
				head = head->next;
			}
			else {
				line* cursor = head;
				while (cursor->next->next != NULL) {
					if (cursor->next->lineNumber ==i) {
						cursor->next = cursor->next->next;												
						cursor = cursor->next;
						while (cursor != NULL) {

							cursor->lineNumber = cursor->lineNumber - 1;
							cursor = cursor->next;
						}
						break;
					}
					else if(cursor->next != NULL)
					{
						if (cursor->next->lineNumber == i) {
							cursor->next = NULL;
							break;
						}

					}
					
					cursor = cursor->next;
				}if(cursor!=NULL)
				if (cursor->next != NULL) {
					if (cursor->next->lineNumber == i) {
						cursor->next = NULL;
					}
				}
				

			}


		}
};


int main() {
	LinkedList lineEditor = LinkedList();
	string cmd;
	string str;
	getline(cin, str);
	int pos = str.find(" ");
	cmd = str.substr(0, pos);
	while (cmd != "quit") {
		if (cmd == "insertEnd") {
			string args = str.substr(pos + 2, str.size() - (pos + 2) - 1);
			lineEditor.add(args);
		}
		if (cmd == "print") {
			lineEditor.print();
		}
		if (cmd == "search") {
			string args = str.substr(pos + 2, str.size() - (pos + 2) - 1);
			lineEditor.search(args);
		}
		if (cmd == "edit") {
			string lineNumber = str.substr(pos+1,1);
			
			int lineNum = stoi(lineNumber);
			string args = str.substr(pos + 4, str.size() - (pos + 4) - 1);
			lineEditor.edit(lineNum,args);
		}
		if (cmd == "insert") {
			string lineNumber = str.substr(pos + 1, 1);

			int lineNum = stoi(lineNumber);
			string args = str.substr(pos + 4, str.size() - (pos + 4) - 1);
			lineEditor.insert(lineNum, args);
		}
		if (cmd == "delete") {
			string lineNumber = str.substr(pos + 1, 1);

			int lineNum = stoi(lineNumber);			
			lineEditor.deleteNode(lineNum);
		}

		
		getline(cin, str);
		pos = str.find(" ");
		cmd = str.substr(0, pos);
	}

}

