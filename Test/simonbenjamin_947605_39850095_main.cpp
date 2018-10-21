/*
 * main2.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: bsimon
 */
#include <iostream>
#include <string>
#include <regex>

class Node {
    public:
        std::string textLine;
        Node* next;
        Node* prev;
};

class Document {
private:
	int size;
	Node *head;
	Node *tail;
public:
	Document()
	{
		init();
	}
	void init()
	{
		size = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}

	void insertEnd(std::string insertionText)
	{
		Node* tempNode = new Node;
		tempNode->textLine = insertionText;
		if(size == 0)
		{
			head = tempNode;
			head->next = tail;
			size++;
			return;
		}
		else if(size == 1)
		{
			head->next = tempNode;
			tail = tempNode;
			size++;
			return;
		}
		else
		{
			tempNode->prev = tail->prev;
			tail->next = tempNode;
		}
		tail = tempNode;
		size++;
	}
	void insertItem(int insertionIndex, std::string insertionText)
	{
		Node* tempNode = new Node;
		tempNode->textLine = insertionText;
		if(insertionIndex == 1)
		{
			if(head->textLine != "")
			{
			tempNode->next = head;
			}
			head = tempNode;
		}
		else if(insertionIndex == size+1)
		{
			tail->next = tempNode;
			tempNode->prev = tail;
			tail = tempNode;
		}
		else if(insertionIndex > size+1)
		{
			return;
		}
		else
		{
			int currentIndex = 1;
			Node *lastItem;
			Node *currentItem = head;
			while(currentIndex < insertionIndex && currentItem != NULL)
			{
				lastItem = currentItem;
				currentItem = currentItem->next;
				currentIndex++;
			}
			if(insertionIndex <= currentIndex)
			{
				tempNode->next = currentItem;
				lastItem->next = tempNode;
			}
		}
		size++;
	}
	void deleteItem(int deletionIndex)
	{
		if(deletionIndex == 1)
		{
			Node* temp = head;
			head = head->next;
			head->prev = NULL;
            delete(temp);
		}
		else if(deletionIndex > size)
		{
			return;
		}
		else if(deletionIndex == size)
		{
			Node* temp = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete(temp);
		}
		else
		{
			int currentIndex = 1;
			Node* lastItem = NULL;
			Node* currentItem = head;
			Node* nextItem = currentItem->next;
			while(currentItem->next != NULL && currentIndex<deletionIndex)
			{
				lastItem = currentItem;
				currentItem = currentItem->next;
				nextItem = currentItem->next;
				currentIndex++;
			}
			lastItem->next = nextItem;
            nextItem->prev = lastItem;
			delete(currentItem);
		}
		size--;
	}
	void editItem(int editIndex, std::string editText)
	{
		deleteItem(editIndex);
		insertItem(editIndex,editText);
	}
	void printDocument()
	{
		if(size == 0)
		{
			return;
		}
		Node* currentItem = head;
		std::string print;
		int lineNumber = 1;
		while(lineNumber < size)
		{
			print += std::to_string(lineNumber)+" "+currentItem->textLine+"\n";
			currentItem = currentItem->next;
			lineNumber++;
		}
		print+= std::to_string(lineNumber) + " "+ currentItem->textLine+"\n";
		std::cout<<print;
	}
	void searchDocument(std::string searchText)
	{
		Node* currentItem = head;
		std::string results;
		int resultCount = 0;
		int currentIndex = 1;
		while(currentItem->next != NULL)
		{
			if((currentItem->textLine).find(searchText) != std::string::npos)
			{
				resultCount++;
				results+=std::to_string(currentIndex)+" "+currentItem->textLine+"\n";
			}
			currentItem = currentItem->next;
			currentIndex++;
		}
		if((currentItem->textLine).find(searchText) != std::string::npos)
		{
			resultCount++;
			results+=std::to_string(currentIndex)+" "+currentItem->textLine+"\n";
		}
		else if(resultCount == 0)
		{
			std::cout<< "not found\n";
			return;
		}
		std::cout<< results;
	}
};

int getLineIndex(std::string command)
{
	return std::stoi (command.substr(command.find_first_of("0123456789"),(command.find_first_of("\"")-command.find_first_of("0123456789")-1)));
}

std::string getCommandText(std::string command)
{
	return command.substr(command.find_first_of("\"")+1,(command.find_last_of("\"")-command.find_first_of("\"")-1));
}

int main()
{
	std::string command;
	std::string insertEnd_regex = R"(^insertEnd\s"[^"]*"\s*$)";
	std::string insert_regex = R"(^insert\s\d+\s"[^"]*"\s*$)";
	std::string delete_regex = R"(^delete\s\d+\s*$)";
	std::string edit_regex = R"(^edit\s\d\s"[^"]*"\s*$)";
	std::string print_regex = R"(^print\s*$)";
	std::string search_regex = R"(^search\s"[^"]*"\s*$)";
	Document* doc1 = new Document;
	do
	{
		std::getline(std::cin,command);
		if(std::regex_match(command,std::regex(insertEnd_regex)))
		{
			doc1->insertEnd(getCommandText(command));

		}
		else if(std::regex_match(command,std::regex(insert_regex)))
		{
			doc1->insertItem(getLineIndex(command),getCommandText(command));
		}
		else if(std::regex_match(command,std::regex(delete_regex)))
		{
			doc1->deleteItem(getLineIndex(command));
		}
		else if(std::regex_match(command,std::regex(edit_regex)))
		{
			doc1->editItem(getLineIndex(command),getCommandText(command));
		}
		else if(std::regex_match(command,std::regex(print_regex)))
		{
			doc1->printDocument();
		}
		else if(std::regex_match(command,std::regex(search_regex)))
		{
			doc1->searchDocument(getCommandText(command));
		}
	}
	while(command != "quit");
	return 0;
}
