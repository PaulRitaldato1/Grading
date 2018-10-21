#include <iostream>
#include <sstream>
#include "LinkedList.h"
using namespace std;




int main(int argc, char **argv) {
	
	
std::string fullLine;
	std::string function, lineNumber, stringInput;
	bool program = true;
	string functions[7] = {"insert", "edit", "insertEnd", "print", "search", "delete", "quit"};
	int lineNumberInt = 0;
	LinkedList* list = new LinkedList;
	string hold;
	string clear;
	char c = 'a';
	int check = 0;

	while (program) {
		//READ INPUT FROM GETLINE AND APPORTION IT INTO INPUT
		std::getline(std::cin, fullLine);
		std::istringstream iss(fullLine);
		iss >> function >> lineNumber;
		//fix input stuff
		c = lineNumber.at(0);
		check = (int)c;
		if ((check <= 57) && (check >= 48)) {
			lineNumberInt = check - 48;
			for (int z = 0; z < 14; z++) {
				iss >> hold;
				if (clear == hold) {
					break;
				}
				clear = hold;
				
				stringInput = stringInput.append(hold);
				stringInput = stringInput.append(" ");

			}
			stringInput = stringInput.substr(0, stringInput.size() - 1);
		}
		else {
			stringInput = lineNumber;
			for (int z = 0; z < 14; z++) {
				iss >> hold;
				if (clear == hold) {
					break;
				}
				clear = hold;
				stringInput = stringInput.append(" ");
				stringInput = stringInput.append(hold);

			}
		}
		
		
		clear = "";
		
		stringInput = stringInput.substr(1, stringInput.size() - 2);
		
		//POSSIBLE FUNCTIONS WITHIN PROGRAM TO BE CALLED BASED ON DESIGNATIONS
		if (function == functions[2]) {
			list->insertEnd(stringInput);
		}
		else if (function == functions[0]) {
			list->insert(stringInput, lineNumberInt);
		}
		else if (function == functions[1]) {
			list->edit(lineNumberInt, stringInput);
		}
		
		else if (function == functions[3]) {
			list->print();
		}
		else if (function == functions[4]) {
			list->search(stringInput);
		}
		else if (function == functions[5]) {
			list->deleteNode(lineNumberInt);
		}
		else if (function == functions[6]) {
			program = false; 
		}
		else { cout << "input invalid.  Please use proper formatting" << endl; }
		stringInput = "";

	}


	return 0;
}
