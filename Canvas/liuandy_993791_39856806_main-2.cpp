#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <tuple>
#include <iostream>
// Linked list implementation
struct Line
{
	Line *next;
	std::string content;
};
class Document
{
	private:
		Line *head;
		int length;
	public:
		Document();
		void insertEnd(std::string text);
		void insert(int position, std::string text);
		void remove(int position);
		void edit(int position, std::string text);
		std::vector<std::tuple<int, Line*>> search(std::string text);
		void print();
		bool empty();
};
Document::Document(void)
{
	head = nullptr;
}
bool Document::empty(){
	return head == nullptr;
}
void Document::insertEnd(std::string text)
{
	Line *line = new Line;
	line->content = text;
	if (empty()){
		line->next = nullptr;
		head = line;
	} else {
		Line *temp = head;
		while (temp->next != nullptr){
			temp = temp->next;
		}
		line->next = nullptr;
		temp->next = line;
	}
}
void Document::insert(int position, std::string text)
{
	Line *line = new Line;
	line->content = text;
	Line *temp = head;
	int count = 1;
	while (temp != nullptr && count != position - 1)
	{
		count++;
		temp = temp->next;
	}
	if (temp != nullptr){
		line->next = temp->next;
		temp->next = line;
	}
}
void Document::remove(int position)
{
	Line *temp = head, *prev = nullptr;
	int count = 1;
	while (temp != nullptr && count != position)
	{
		count++;
		prev = temp;
		temp = temp->next;
	}
	if (temp != nullptr){
		prev->next = temp->next;
		delete temp;
	}
}
void Document::edit(int position, std::string text)
{
	Line *temp = head;
	int count = 1;
	while (temp != nullptr && count != position)
	{
		count++;
		temp = temp->next;
	}
	temp->content = text;
}
std::vector<std::tuple<int, Line*>> Document::search(std::string text)
{
	std::vector<std::tuple<int, Line*>> found;
	int count = 1;
	Line *temp = head;
	while (temp != nullptr)
	{
		if ((temp->content).find(text) != std::string::npos)
		{
			found.push_back(std::make_tuple(count, temp));
		}
		count++;
		temp = temp->next;
	}
	return found; 
}
void Document::print()
{
	int count = 1;
	Line *temp = head;
	while (temp != nullptr)
	{
		std::cout<<(count++)<<" "<<temp->content<<std::endl;
		temp = temp->next;
	}
}
// Main 
int main()
{
	Document document;
	std::string input;
	getline(std::cin, input);
	while (input != "quit")
	{
		if (input.substr(0, 9) == "insertEnd")
		{
			document.insertEnd(input.substr(11, (input.length() - 2) - 11 + 1));
		} 
		else if (input.substr(0, 6) == "insert")
		{
			int quotation_index = input.find("\"");
			document.insert(std::stoi(input.substr(7, (quotation_index - 1) - 7 + 1)), input.substr(quotation_index + 1, (input.length() - 2) - (quotation_index + 1) + 1));
		}
		else if (input.substr(0, 6) == "delete")
		{
			document.remove(std::stoi(input.substr(7)));
		}
		else if (input.substr(0, 4) == "edit")
		{
			int quotation_index = input.find("\"");
			document.edit(std::stoi(input.substr(5, (quotation_index - 1) - 5 + 1)), input.substr(quotation_index + 1, (input.length() - 2) - (quotation_index + 1) + 1));
		}
		else if (input.substr(0, 5) == "print")
		{
			document.print();
		}
		else if (input.substr(0, 6) == "search")
		{	
			std::vector<std::tuple<int, Line*>> found = document.search(input.substr(8, (input.length() - 2) - 8 + 1));
			if (found.empty()){
				std::cout<<"not found"<<std::endl;
			} 
			else 
			{
				for (std::tuple<int, Line*> tuple : found){
					int index;
					Line* line;
					std::tie(index, line) = tuple;
					std::cout<<index<<" "<<line->content<<std::endl;
				}
			}
		}
		getline(std::cin, input);
	}
}