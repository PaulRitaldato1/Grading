/*
Author: Kejti Lita
UFID: 9455-0140
Date: 09/21/2018
Class: COP3530
Description: A line editor that implements a linked list 
				to insert, delete, search, edit or print the lines.
*/
#include <iostream>
#include <string>
#include "Pa1.h"
#include <stdlib.h>
#include <sstream>

using namespace std;

int main() {
	 //Creating the list and initializing the command string.
	string command = "Nothing";
	LinkedList myList;
	//While loop to stop when user inputs quit.
	while (command != "quit") {
		getline(cin, command);
	
		string action, lineToAdd;
		int position;
		//Searching if there is a string that needs to be inserted, searched or edited and parsing it approprietly. 
		position = command.find("\"");
		if (position != string::npos) {
			lineToAdd = command.substr(position + 1, command.length() - (2 + position));
			action = command.substr(0, position);

		}
		//Call the insert function if the user input insert or insertEnd.
		if (action.find("insert") != string::npos) {
			//Getting the position for the insertion.
			if (action.find("End") == string::npos) {
				string insertPos = action.substr(7, position);
				int insertPosInt = stoi(insertPos);
				myList.add(lineToAdd, insertPosInt);
			}
			//Assigning the insert position as 0 to call insertEnd, since the user will not input 0 for a regular insert.
			else {
				myList.add(lineToAdd, 0);
			}
		}
		//Calling the edit function.
		else if (action.find("edit") != string::npos) {
			string insertPos = action.substr(5, position);
			int insertPosInt = stoi(insertPos);
			myList.edit(lineToAdd, insertPosInt);
		}
		//Calling the delete function
		else if (command.find("delete") != string::npos) {
			string deletePos;
			deletePos = command.substr(7);
			int deletePosInt = stoi(deletePos);
			myList.deleteNode(deletePosInt);
	
		}
		//Calling search function.
		else if (action.find("search") != string::npos) {
			myList.search(lineToAdd);
		}
		//Calling the print function.
		else if (command.find("print") != string::npos){
			myList.print();	
		}
		//Taking into account that the user might neither of the allowed options.
		else if (command.find("quit") == string::npos) {
			command = "return";
		}


	}
}
