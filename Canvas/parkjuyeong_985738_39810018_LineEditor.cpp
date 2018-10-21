#include "stdafx.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

void program() {
	LinkedList *l = new LinkedList();
	string mystring;
	while (true) {
		getline(cin, mystring);
		if (mystring == "quit")
			break;
		if (mystring == "print") {
			l->print();
			continue;
		}
		string instruction = mystring.substr(0, mystring.find(" "));
		int start = mystring.find_first_of("\"");
		int end = mystring.find_last_of("\"");
		int numstart = mystring.find_first_of("1234567890");
		int numend = mystring.find_last_of("1234567890");
		int num;
		if (numstart!=string::npos && numend!=string::npos)
			num = stoi(mystring.substr(numstart, numend + 1));
		string line;
		if (start!=string::npos && end!=string::npos)
			line= mystring.substr(start+1,(end)-(start+1));
		if (instruction == "insertEnd")
			l->insert(line);
		else if (instruction == "insert")
			l->insert(num, line);
		else if (instruction == "delete")
			l->del(num);
		else if (instruction == "edit")
			l->edit(num, line);
		else if (instruction == "search") {
			pair<int, string> s=l->search(line);
			int n = get<0>(s);
			string st = get<1>(s);
			cout << n << " " << st << endl;
		}
	}
	delete l;
}

int main()
{
	program();
}

