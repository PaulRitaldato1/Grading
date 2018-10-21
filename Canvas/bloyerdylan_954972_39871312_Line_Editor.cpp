#include <string>
#include <iostream>
using namespace std;

struct Node{
	string value;
	Node* next;
};

class linkedList{
public:
	Node* head;
	linkedList(){
		head = NULL;
	}
};

Node* insertEnd(Node* head, string text){
	Node* newTail = new Node;
	newTail->value = text;
	newTail->next = NULL;
	if(!head){ //If the list is empty, makes the new node the head.
		head = newTail;
		return head;
	}
	else{
		Node* temp = new Node;
		temp = head;
		while(temp->next){ //Runs to the end of the list and leaves the new node there.
			temp = temp->next;
		}
		temp->next = newTail;
		return head;
	}
}	

Node* insert(Node* head, int index, string text){
	Node* midLine = new Node;
	midLine->value = text;
	if(index == 1){ //If the new line is at the beginning, makes the node holding the line the head.
		midLine->next = head;
		head = midLine;
		return head;
	}
	else{
		Node* temp = new Node;
		temp = head;
		for(int i = 1; i < index - 1; i++){ //Iterates through the list until it hits the index just befor the desired index.
			temp = temp->next;
		}
		if(!temp->next){ //If the index is at the end of the list, inserts the new line at the end.
			temp->next = midLine;
			midLine->next = NULL;
			return head;
		}
		else{
			midLine->next = temp->next; //Causes the new node to point to the desired index.
			temp->next = midLine; //Causes the node before the desired index to point to the new node.
			return head;
		}
	}
}

Node* del(Node* head, int index){ 
	if(index == 1){ //if deleting the head, makes the second node the new head and deletes the previous head.
		Node* del = new Node;
		del = head;
		head = head->next;
		delete del;
		return head;
	}
	Node* temp = new Node;
	temp = head;
	for(int i = 1; i < index - 1; i++){ //Iterates to one index before the index to be deleted.
		temp = temp->next;
	}
	Node* connection = new Node;
	connection = temp;
	temp = temp->next; //Puts temp in the index to be deleted.
	if(!temp->next){ //Used if the index to be deleted is the last node in the list.
		delete(temp);
		connection->next = NULL;
		return head;
	}
	else{ //Otherwise the node in the index before the deletion is made to point to the index after the deletion before deleting the desired index.
		connection->next = temp->next;
		delete(temp);
		return head;
	}
}

Node* edit(Node* head, int index, string text){
	if(index == 1){ //Edits the head.
		head->value = text;
		return head;
	}
	else{ //Edits otherwise.
		insert(head,index,text);
		del(head,index + 1);
		return head;
	}
}

void print(Node* head){
	Node* temp = new Node;
	temp = head;
	int lineNumber = 1;
	while(temp){ //Runs through every node, printing the node and its line number.
		cout << lineNumber << " " << temp->value << "\n";
		temp = temp->next;
		lineNumber++;
	}
}

void search(Node* head, string text){
	Node* temp = new Node;
	temp = head;
	bool isIn = false; //This bool is used to make sure the text is found at least one.
	int lineCount = 1;
	string line;
	while(temp){ //Iterates through every node.
		line = temp->value;
		for(int i = 0; i < line.size(); i++){ //Checks if any character in the value of the node matches the first character of the text being searched for.
			if(line[i] == text[0]){
				int j = i + 1;
				bool matches = true;
				for(int k = 1; k < text.size(); k++){ //If a character in the node's value is found to match the first character of the text,
					if(line[j] == text[k]){ //compares the characters following the first character in each string.
						j++;
					}
					else{ //If they don't match, it goes back to comparing the beginning of the text string to each character in the node's value.
						matches = false;
						break;
					}
				}
				if(matches){
					cout << lineCount << " " << line << "\n";
					isIn = true; 
				}
			}
		}
		temp = temp->next;
		lineCount++;
	}
	if(!isIn){ //If there wasn't a single match, let's the user know.
		cout << "not found\n";
	}
}

int main(){
	string command;
	cin >> command;
	linkedList list;
	while(command != "quit"){
		if(command == "insertEnd"){
			string inEnd;
			string quote;
			cin.ignore();
			getline(cin,quote);
			if(quote.size() > 82){ //Makes sure the user isn't trying to insert something that's too long.
			}
			else{
				inEnd = quote.substr(1, quote.size() - 2); //Gets rid of the quotation marks.
				list.head = insertEnd(list.head, inEnd);
			}
		}
		else if(command == "insert"){
			int index;
			cin >> index;
			int indexCheck = 1;
			Node* temp = new Node;
			temp = list.head;
			while(temp){
				temp = temp->next;
				indexCheck++;
			}
			if(index > indexCheck){ //Makes sure the index isn't so large that it's out of the list.
			}
			else{
				string inMid;
				string quote;
				cin.ignore();
				getline(cin,quote);
				if(quote.size() > 82){ //Makes sure the user isn't trying to insert something that's too long.
				}
				else{
					inMid = quote.substr(1, quote.size() - 2); //Gets rid of the quotation marks.
					list.head = insert(list.head, index, inMid);
				}
			}
		}
		else if(command == "delete"){
			int index;
			cin >> index;
			int indexCheck = 0;
			Node* temp = new Node;
			temp = list.head;
			while(temp){
				temp = temp->next;
				indexCheck++;
			}
			if(index > indexCheck){ //Makes sure the index isn't so large it's out of the list.
			}
			else{
				list.head = del(list.head, index);
			}	
		}
		else if(command == "edit"){
			int index;
			cin >> index;
			int indexCheck = 0;
			Node* temp = new Node;
			temp = list.head;
			while(temp){
				temp = temp->next;
				indexCheck++;
			}
			if(index > indexCheck){ //Makes sure the index isn't so large it's out of the list.
			}
			else{
				string replace;
				string quote;
				cin.ignore();
				getline(cin,quote);
				if(quote.size() > 82){ //Makes sure the user isn't trying to insert something that's too long.
				}
				else{
					replace = quote.substr(1, quote.size() - 2); //Gets rid of the quotation marks.
					list.head = edit(list.head, index, replace);
				}
			}
		}
		else if(command == "print"){
			print(list.head);
		}
		else if(command == "search"){
			string look;
			string quote;
			cin.ignore();
			getline(cin, quote);
			if(quote.size() > 82){ //Makes sure the user isn't trying to insert something that's too long.
			}
			else{
				look = quote.substr(1, quote.size() - 2); //Gets rid of the quotation marks.
				search(list.head, look);
			}
		}
		else{
		}
		cin >> command;
	}
	return 0;
}