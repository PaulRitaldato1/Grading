// LineEditorCOP3530.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Structures.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;


int main() {

	string s, command, lineData;
	int lineNumber;
	linkedList editor;

	map<string, int> m;
	m["insertEnd"] = 1;
	m["insert"] = 2;
	m["delete"] = 3;
	m["edit"] = 4;
	m["print"] = 5;
	m["search"] = 6;
	m["quit"] = 7;

	while (1) {

		cout << "Welcome to the line editor, please enter a command: ";
		getline(cin, s);

		int pos = s.find_first_of(' ');
		command = s.substr(0, pos);

		if (command == "insertEnd" || command == "search") {

			if (s.substr(pos + 1).length() > 82 ) {
				continue;
			}

			lineData = s.substr(pos + 1);

			if (lineData.front() == '"') {
				lineData.erase(0, 1);
				lineData.erase(lineData.size() - 1);
			}

		}

		if (command == "insert" || command == "edit") {

			if (editor.getSize() + 1 < stoi(s.substr(pos + 1)) || s.substr(pos + 1).length() > 82 ) {
				continue;
			}

			lineNumber = stoi(s.substr(pos + 1));             
			lineData = s.substr(pos + 2);

			while (!lineData.empty() && isspace(*lineData.begin()))
				lineData.erase(lineData.begin());

			while (!lineData.empty() && isspace(*lineData.rbegin()))
				lineData.erase(lineData.length() - 1);

			if (lineData.front() == '"') {
				lineData.erase(0, 1);
				lineData.erase(lineData.size() - 1);
			}

		}

		if (command == "delete") {

			if (editor.getSize() < stoi(s.substr(pos + 1))) {
				continue;
			}

			lineNumber = stoi(s.substr(pos + 1));

		}



		switch (m[command]) {

		case 1: editor.insertEnd(lineData);
			break;
		case 2:	editor.insert(lineNumber, lineData);
			break;
		case 3:	editor.deleteLine(lineNumber);
			break;
		case 4:	editor.editLine(lineNumber, lineData);
			break;
		case 5:	editor.print();
			break;
		case 6:	editor.search(lineData);
			break;
		case 7:	cout << "Goodbye."; 
				return 0;
			break;

		}

	}

}

