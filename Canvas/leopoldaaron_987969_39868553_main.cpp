#include "LinkedList.h"
#include <string>

struct Document
{
	LinkedList<std::string> lines;

	void insert(std::string &line);
	void insert(int lineNum, std::string &line);
	void remove(int lineNum);
	void edit(int lineNum, std::string &line, Document &d);
	void search(std::string &target);
	void print(Document &d);
};

void RemovePunct(std::string &line);
void CheckProperInput(std::string &line);
std::string GetInstruction(std::string &line);
int GetIndex(std::string &line);
//void ReadWords(Document &document);

int main()
{
	Document document;
	std::string buffer = "";

	while (true)
	{
		std::getline(std::cin, buffer);
		if (buffer == "quit")
			break;
		else if (buffer == "print")
		{
			document.print(document);
			continue;
		}

		std::string instruction = GetInstruction(buffer);

		if (instruction == "insertEnd")
		{
			//if (buffer.length() > 80)
				//buffer = buffer.substr(0, 80);
			CheckProperInput(buffer);
			RemovePunct(buffer);
			if (buffer == "")
				continue;

			document.insert(buffer);
			
		}
		else if (instruction == "insert")
		{
			int lineNum = GetIndex(buffer);

			//if (buffer.length() > 80)
				//buffer = buffer.substr(0, 80);
			
			CheckProperInput(buffer);
			RemovePunct(buffer);
			if (buffer == "")
				continue;

			document.insert(lineNum - 1, buffer);
		}
		else if (instruction == "delete")
		{
			int lineNum = GetIndex(buffer);
			document.remove(lineNum - 1);
		}
		else if (instruction == "edit")
		{
			int lineNum = GetIndex(buffer);

			//if (buffer.length() > 80)
				//buffer = buffer.substr(0, 80);
				
			CheckProperInput(buffer);
			RemovePunct(buffer);
			if (buffer == "")
				continue;

			document.edit(lineNum - 1, buffer, document);
		}
		else if (instruction == "search")
		{
			CheckProperInput(buffer);
			RemovePunct(buffer);
			if (buffer == "")
			{
				std::cout << "not found" << std::endl;
				continue;
			}

			document.search(buffer);
		}

		buffer = "";
		std::cin.clear();
	}
	return 0;
}

void CheckProperInput(std::string &line)
{
	while (line[0] != '"')
	{
		if (line == "")
			break;

		line = line.substr(1, line.length());
	}
	
	while(line[line.length() - 1] != '"')
	{
		if (line == "")
			break;
		
		line = line.substr(0, line.length() - 1);
	}
}

void RemovePunct(std::string &line)
{
	std::string temp = "";
	for (char letter : line)
	{
		if (letter == '"')
			continue;
		
		temp += letter;
	}

	line = temp;
}

std::string GetInstruction(std::string &line)
{
	std::string instruction = "";
	for (char letter : line)
	{
		if (letter == ' ')
			break;

		else
			instruction += letter;
	}

	line.erase(0, instruction.length() + 1);
	return instruction;
}

int GetIndex(std::string &line)
{
	std::string temp = "";
	for (char curr : line)
	{
		if (isdigit(curr))
		{
			temp += curr;
		}

		else
			break;
	}

	line.erase(0, temp.length() + 1);
	return stoi(temp);

}

void Document::insert(std::string &line)
{
	this->lines.add(line);
}

void Document::insert(int lineNum, std::string &line)
{
	this->lines.insert(lineNum, line);
}

void Document::remove(int lineNum)
{
	this->lines.remove_at(lineNum);
}

void Document::edit(int lineNum, std::string &line, Document &d)
{
	if (d.lines.at(lineNum) != NULL)
		d.lines.at(lineNum)->data = line;
}

void Document::search(std::string &target)
{
	// make contains in linked list template
	this->lines.print_matches(target);
}

void Document::print(Document &d)
{
	d.lines.print();
}
