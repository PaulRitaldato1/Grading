#include <iostream>
#include <string>
#include <cstring>

struct node{
	std::string value;
	node* next;
	node() : next(nullptr) {}
	node(std::string s) : value(s), next(nullptr) {}
};

/* Iterator class for linked list*/
class iterator{
public:
	node* itr;
	iterator() : itr(nullptr){}
	iterator(node* i) : itr(i){}
	iterator operator ++();
	bool operator ==(iterator i);
	bool operator !=(iterator i);
	std::string operator *();
};

iterator iterator::operator ++(){
	itr = itr->next;
	return *this;
}

bool iterator::operator ==(iterator i){
	return itr->value == i.itr->value;
}

bool iterator::operator !=(iterator i){
	return itr->value != i.itr->value;
}

std::string iterator::operator *(){
	return itr->value;
}



/* Linked List class*/
class list{
private:
	node* head;  // points to the first node in the list
	node* tail;  // points to the last node in the list
	int lsize;  // size of the list
public:
	list() : head(nullptr), tail(nullptr), lsize(0){}
	int size();
	iterator begin(); // returns iterator pointing to head
	iterator end();		// returns iterator pointing to a new node succeeding tail
	void push_back(std::string);
	void insert(int, std::string);
	void erase(int);
	void replace(int, std::string);
	void print();
	void search(std::string);
	~list(); // destructor

};

int list::size() { return lsize;}

list::~list(){	// releasing dynamically allocated memory
	iterator it = begin();
	node* tmp;
	while(it.itr != nullptr){
		tmp = it.itr;
		++it;
		delete tmp;
	}
}

iterator list::begin(){
	return *(new iterator(head));
}

iterator list::end(){
	return	*(new iterator(tail));
}

void list::push_back(std::string s){
	node* i = new node(s);
	if(lsize == 0) {
		tail = i;
		head = tail;
	}
	else{
		tail->next = i;
		tail = i;
	}
	lsize++;
}

void list::insert(int i, std::string s){
	iterator it = begin();
	if(i == 1){
		node* tmp = new node(s);
		tmp->next = head;
		head = tmp;
		lsize++;
		if(lsize == 1) tail = head;
	}
	else if(i > 1) {
		int index = 1;
		while(index < i - 1 && it.itr != nullptr){
			++it; ++index;
		}
		if(it.itr != nullptr){
		node* tmp = new node(s);
		tmp->next = it.itr->next;
		it.itr->next = tmp;
		lsize++;
	}
	}

}

void list::erase(int i){
	node* tmp;
	if(i == 1 && lsize >= 1){
		tmp = head;
		head = head->next;
		delete tmp;
		if(head == nullptr) tail = nullptr;
		lsize--;
	}
	else if(i > 1){
		int index = 1;
		iterator it = begin();
		while(index < i - 1 && it.itr != nullptr){
			++it; ++index;
		}
		if(it.itr != nullptr && it.itr->next != nullptr){
			tmp = it.itr->next;
			it.itr->next = tmp->next;
			delete tmp;
			if(it.itr->next == nullptr) tail = it.itr;
			lsize--;
		}
	}
}

void list::replace(int i, std::string s){
	iterator it = begin();
	int index = 1;
	while(index < i && it.itr != nullptr){
		++it; ++index;
	}
	if(it.itr != nullptr && i >= 1){
		it.itr->value = s;
	}
}

void list::print(){
	iterator it = begin();
	int index = 1;
	while(it.itr != nullptr){
		std::cout << index << " " << *it << std::endl;
		++it; ++index;
	}
}

void list::search(std::string s){
iterator it = begin();
bool found = false;
int index = 1;
	while(it.itr != nullptr){
		if((*it).find(s) != std::string::npos){
			found = true;
			std::cout << index << " " << *it << std::endl;
		}
		++it; index++;
	}
	if(!found) std::cout << "not found" << std::endl;
}


//The Line Editor
class LineEditor {
private:
	list editor;
public:
	void insertEnd(std::string);
	void print();
	void insert(int, std::string);
	void Delete(int);
	void edit(int, std::string);
	void search(std::string);
};

void LineEditor::print(){
	editor.print();
}

void LineEditor::insertEnd(std::string s){
	editor.push_back(s);
}

void LineEditor::insert(int i, std::string s){
	editor.insert(i,s);
}

void LineEditor::Delete(int i){
	editor.erase(i);
}

void LineEditor::edit(int i, std::string s){
	editor.replace(i,s);
}

void LineEditor::search(std::string s){
	editor.search(s);
}


int main(){
	// invoke the Line Editor
	std::string input;
	std::string command = "";
	char str[100];
	char* token;
	LineEditor editor;

		while(command != "quit"){
			std::getline(std::cin, input);	// getting the whole line
			if(input == "quit"){
				command = "quit";
				continue;
			}
			strcpy(str, input.c_str());		// converting to C string
			token = strtok(str," ");
			if(std::strcmp(token, "insertEnd") == 0){
				token = strtok(nullptr,"\"");
				std::string tmp(token);
				editor.insertEnd(tmp);
			}
			if(std::strcmp(token, "search") == 0){
				token = strtok(nullptr,"\"");
				std::string tmp(token);
				editor.search(tmp);
			}
			if(std::strcmp(token, "print") == 0){
				editor.print();
			}
			if(std::strcmp(token, "insert") == 0){
				token = strtok(nullptr," ");
				std::string tmp(token);
				if (tmp.find_first_not_of("0123456789") == std::string::npos){  // is a number?
					int i = atoi(token);
					token = strtok(nullptr,"\"");
					std::string s(token);
					editor.insert(i, s);
				}
			}
			if(std::strcmp(token, "edit") == 0){
				token = strtok(nullptr," ");
				std::string tmp(token);
				if (tmp.find_first_not_of("0123456789") == std::string::npos){  // is a number?
					int i = atoi(token);
					token = strtok(nullptr,"\"");
					std::string s(token);
					editor.edit(i, s);
				}
			}
			if(std::strcmp(token, "delete") == 0){
				token = strtok(nullptr," ");
				std::string tmp(token);
				if (tmp.find_first_not_of("0123456789") == std::string::npos){  // is a number?
					int i = atoi(token);
					editor.Delete(i);
				}
			}
		}

	return 0;
}
