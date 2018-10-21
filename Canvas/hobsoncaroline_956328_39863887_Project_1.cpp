//Caroline Hobson
//Section 12129
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//Implemented a single linked list with the string data and the next pointer
class Line {
public:
	string line;
	Line* next = NULL;
};


//any method with return Line* you are returning the newly edited head
//first value starts at head->next


Line* insertEnd(Line* head, string input) {
	//If character max is 80+, cant be added
	if (input.length() > 80) {

		return head;
	}
	//Create new node
	Line *lineAdd = new Line();
	lineAdd->line = input;
	lineAdd->next = NULL;

	//Create a current node to go to the end of the list

	Line *current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	//Current will be taken to the end of the list, and then addNode will be added to the end
	current->next = lineAdd;
	return head;

}


Line* insert(Line* head, int lineNum, string input) {
	//Default
	//Create current node that starts at the begining
	Line *previous = head;
	Line *current = head->next;


	//Create new node
	Line *lineAdd = new Line();
	lineAdd->line = input;
	lineAdd->next = NULL;

	int count = 1;

	//Add node will be inserted between current and previous if the counter reached the desired line
	while (current != NULL) {
		if (count == lineNum) {
			lineAdd->next = current;
			previous->next = lineAdd;
			return head;
		}
		else {
			current = current->next;
			previous = previous->next;
			count++;
		}
	}
	//if the list went to the end, check if we can add it to the end of the list
	if (count == lineNum) {
		return insertEnd(head, input);
	}
	else {
		return head;
	}
}


Line* deleteLine(Line* head, int lineNum) {
	Line* current = head->next;
	Line* previous = head;
	int count = 1;
	//Goes through the list to the desired line, and then deletes current , making previous go to the next one in the list
	while (current != NULL) {
		if (count == lineNum) {
			previous->next = current->next;
			delete current;
			return head;
		}
		else {
			current = current->next;
			previous = previous->next;
			count++;
		}
	}


	return head;
}


Line* edit(Line* head, int lineNum, string input) {
	//Create current node that starts at the begining
	Line *current = head->next;
	int count = 1;
	// while loop finds index, then replaces the line with the new input, similar to delete except changing the line not deleting
	while (current != NULL) {
		if (count == lineNum) {
			current->line = input;
			return head;
		}
		else {
			current = current->next;
			count++;
		}
	}


	return head;
}



void print(Line* head) {
	Line* current = head->next;
	int count = 1;
	//Goes through the list and prints the value
	while (current != NULL) {
		cout << count << " " << current->line << endl;
		current = current->next;
		count++;
	}
}


void search(Line* head, string input) {
	Line* current = head->next;
	int count = 1;
	string compareL;
	bool found = false;
	//Loop will print out any line that has the word in it using the .find method
	while (current != NULL) {
		compareL = current->line;
		if (compareL.find(input) != std::string::npos) {
			cout << count << " " << compareL << endl;
			found = true;
		}
		current = current->next;
		count++;
	}
	//if the list was iterated through and never found anything, will print "not found"
	if (found != true) {
		cout << "not found" << endl;
	}

}

int main()
{
	//Create the document which will be a linked list
	Line *document = new Line();

	//Declaring Variables before the while loop begins
	string input;
	string textQuote;
	string text;

	int endindex;
	int lineNum;
	int finalIndex;


	bool run = true;
	while (run) {
		//retrieves the input
		getline(cin, input);

		//If statements will compare the first part of the string to go to a specific command, that then requires the number or text if needed

		//insertEnd
		if (input.substr(0, 9).compare("insertEnd") == 0) {
			//creates a string that has the quote with and ending "
			textQuote = input.substr(11);
			finalIndex = textQuote.length() - 1;
			//takes off the final " of the textQuote to just have the text
			text = textQuote.substr(0, finalIndex);
			insertEnd(document, text);
		}

		//insert
		else if (input.substr(0, 6).compare("insert") == 0) {

			//since char is in ascii, need to shift the numbers to get the correct decimal num
			lineNum = (int)input.at(7) - '0';


			textQuote = input.substr(10);
			finalIndex = textQuote.length() - 1;
			text = textQuote.substr(0, finalIndex);
			insert(document, lineNum, text);

		}

		//delete
		else if (input.substr(0, 6).compare("delete") == 0) {
			lineNum = (int)input.at(7) - '0';
			deleteLine(document, lineNum);
		}

		//edit
		else if (input.substr(0, 4).compare("edit") == 0) {

			lineNum = (int)input.at(5) - '0';

			textQuote = input.substr(8);
			finalIndex = textQuote.length() - 1;
			text = textQuote.substr(0, finalIndex);
			edit(document, lineNum, text);
		}

		//print
		else if (input.substr(0, 5).compare("print") == 0) {
			print(document);
		}
		//search
		else if (input.substr(0, 6).compare("search") == 0) {
			textQuote = input.substr(8);
			finalIndex = textQuote.length() - 1;
			text = textQuote.substr(0, finalIndex);
			search(document, text);
		}
		//quit
		else if (input.substr(0, 4).compare("quit") == 0) {
			return 0;
		}



	}
}
