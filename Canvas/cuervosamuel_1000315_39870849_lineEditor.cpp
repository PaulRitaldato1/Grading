#include <iostream>
#include <sstream>
#include "lineEditor.h"
#include <string>

using namespace std;

list doc;

int main()
{
	string in;
	
	cout << "Welcome to Line Editor!" << endl
		<< endl
		<< "Here are the commands: " << endl
		<< endl
		<< "insertEnd \"text\"  -- insert given text at the end of the document" << endl
		<< "insert *line Number* \"text\" -- insert given text at the line indicated by index given" << endl
		<< "delete *line Number* -- delete line at index given" << endl
		<< "edit *line Number* \"text\" -- replace the line at the index given with the given text" << endl
		<< "print -- print the entire document, with line numbers" << endl
		<< "search \"text\" -- print the line number and line that contains the given text.print \"Not found\" if it is not found" << endl
		<< "quit - quit or exit the program" << endl << endl;


	getline(cin, in);
	while (in != "quit")					//Loops until quit is called
	{
		string com = in.substr(0, in.find(" "));

		if (com == "insertEnd")				//Insert End command: grabs a string token found inbetween two "" and then calls pushEnd from the header file
		{
			string value = in.substr(in.find("\"") + 1,
				((in.find("\"", in.find("\"") + 1)) - (in.find("\"") + 1)));

			doc.pushEnd(value);
		}
		if (com == "insert")				//Insert command: grabs two string token found inbetween two _ and inbetween two "", changed the numerical token into an int and then calls add from the header file
		{
			string pos = in.substr(in.find(" ") + 1,
				((in.find(" ", in.find(" ") + 1)) - (in.find(" ") + 1)));
			stringstream line(pos);
			int lineInt = 0;
			line >> lineInt;

			string value = in.substr(in.find("\"") + 1,
				((in.find("\"", in.find("\"") + 1)) - (in.find("\"") + 1)));

			doc.add(lineInt, value);
		}
		if (com == "delete")				//Delete command: grabs a numerical token and changes it into an int then calls remove from the header file
		{
			string pos = in.substr(in.find(" ") + 1,
				((in.find(" ", in.find(" ") + 1)) - (in.find(" ") + 1)));
			stringstream line(pos);
			int lineInt = 0;
			line >> lineInt;

			doc.remove(lineInt);
		}
		if (com == "edit")					//Edit command: grabs a numerical token and changes it into an int and grabs the string inbetween "" and then calls replace from the header file
		{
			string pos = in.substr(in.find(" ") + 1,
				((in.find(" ", in.find(" ") + 1)) - (in.find(" ") + 1)));
			stringstream line(pos);
			int lineInt = 0;
			line >> lineInt;

			string value = in.substr(in.find("\"") + 1,
				((in.find("\"", in.find("\"") + 1)) - (in.find("\"") + 1)));

			doc.replace(lineInt, value);
		}
		if (com == "search")				//Search command: grabs the string inbetween "" and then calls findText in the header file
		{
			string value = in.substr(in.find("\"") + 1,
				((in.find("\"", in.find("\"") + 1)) - (in.find("\"") + 1)));

			doc.findText(value);
		}
		if (in == "print")					//Print command: calls display in the header file
		{
			doc.display();
		}

		getline(cin, in);
	}

}