#include <iostream>
#include <string>

//your linked list implementation here

struct Line {
	char* text;
	Line* next;
	Line();
	Line(char *t);
	~Line();
	void Print();
	void Edit(char *t);
};

Line::Line() {
	text = new char[80];
	for (int i = 0; i < 80; i++) {
		text[i] = '\0';
	}

	next = nullptr;
}

Line::Line(char* t) {
	text = new char[80];

	for (int i = 0; i < 80; i++) {
		text[i] = '\0';
	}

	int n = 0;

	while ((t[n] != '\0') && (n < 80)) {
		text[n] = t[n];
		n++;
	}

	next = nullptr;

}

Line::~Line() {
	delete[] text;
}

void Line::Print() {
	int i = 0;

	while ((text[i] != '\0') && (i < 80)) {
		std::cout << text[i];
		i++;
	}
}

void Line::Edit(char* t) {
	for (int i = 0; i < 80; i++) {
		text[i] = '\0';
	}

	int n = 0;
	while ((t[n] != '\0') && (n < 80)) {
		text[n] = t[n];
		n++;
	}
}



struct Document {
	Line * head;
	Document();
	void InsertEnd(char* t);
	void Insert(int ind, char* t);
	void Delete(int ind);
	void Edit(int ind, char* t);
	void Print();
	void Search(char* t);
};

Document::Document() {
	head = nullptr;
}

void Document::InsertEnd(char* t) {
	Line* newLine = new Line(t);

	if (head == nullptr) {
		head = newLine;
	}
	else {
		Line* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newLine;
	}
}

void Document::Insert(int ind, char* t) {
	Line* newLine = new Line(t);
	int count = 0;
	Line* counter = head;
	while (counter != nullptr) {
		counter = counter->next;
		count++;
	}

	if (ind == 1) {
		newLine->next = head;
		head = newLine;
	}
	else if (ind > count + 1) {
		// Do nothing
	}
	else if (ind < 1) {
		// Do nothing
	}
	else {
		int n = 1;
		Line* current = head;
		while (n < (ind - 1)) {
			current = current->next;
			n++;
		}

		newLine->next = current->next;
		current->next = newLine;
	}
}

void Document::Delete(int ind) {
	Line* current = head;
	int count = 0;
	Line* counter = head;

	while (counter != nullptr) {
		count++;
		counter = counter->next;
	}
	if (ind > count) {
		// Do nothing
	} else if (ind == 1) {
		head = current->next;
		current->~Line();

	} else {
		int n = 1;
		while (n < (ind - 1)) {
			current = current->next;
			n++;
		}

		Line* del = current->next;
		current->next = del->next;
		del->~Line();
	}
}

void Document::Edit(int ind, char* t) {
	Line* current = head;

	int n = 1;
	while (n < ind) {
		current = current->next;
		n++;
	}

	current->Edit(t);
}

void Document::Print() {
	Line* current = head;

	int i = 1;
	while (current != nullptr) {
		std::cout << i << " ";
		current->Print();
		std::cout << "\n";
		current = current->next;
		i++;
	}
}

void Document::Search(char* t) {
	int lineNumber = 1;
	Line* current = head;
	bool found = false;
	std::string searchTerm(t);
	while (current != nullptr) {
		std::string currentText(current->text);
		if (currentText.find(searchTerm) != std::string::npos) {
			std::cout << lineNumber << " ";
			current->Print();
			std::cout << "\n";
			found = true;
		}
		current = current->next;
		lineNumber++;
	}
	if (found == false) {
		std::cout << "not found\n";
	}

}

//your line editor implementation here

void InsertEnd(Document &d) {
	std::string text;
	std::getline(std::cin, text);
	int size = (int)(text.size() - 2);
	char* arr = new char[size];

	for (int i = 1; i < size; i++) {
		arr[i - 1] = text.c_str()[i + 1];
	}

	arr[size - 1] = '\0';
	d.InsertEnd(arr);
}

void Insert(Document &d) {
	int index;
	std::string text;
	std::cin >> index;
	std::getline(std::cin, text);
	int size = (int)(text.size() - 2);

	char* arr = new char[size];

	for (int i = 1; i < size; i++) {
		arr[i - 1] = text.c_str()[i + 1];
	}

	arr[size - 1] = '\0';
	d.Insert(index, arr);
}

void Delete(Document &d) {
	int index;
	std::cin >> index;
	d.Delete(index);
}

void Edit(Document &d) {
	int index;
	std::string text;
	std::cin >> index;
	std::getline(std::cin, text);
	int size = (int)(text.size() - 2);

	char* arr = new char[size];

	for (int i = 1; i < size; i++) {
		arr[i - 1] = text.c_str()[i + 1];
	}

	arr[size - 1] = '\0';
	d.Edit(index, arr);
}

void Search(Document &d) {
	std::string text;
	std::getline(std::cin, text);
	int size = (int)(text.size() - 2);

	char* arr = new char[size];

	for (int i = 1; i < size; i++) {
		arr[i - 1] = text.c_str()[i + 1];
	}

	arr[size - 1] = '\0';
	d.Search(arr);
}


int main() {

	Document d;
	bool resume = true;

	while (resume) {

		std::string command;
		// Take in the initial command
		std::cin >> command;

		if (command == "quit") {
			resume = false;
		}
		else if (command == "insertEnd") {
			InsertEnd(d);
		}
		else if (command == "insert") {
			Insert(d);
		}
		else if (command == "delete") {
			Delete(d);
		}
		else if (command == "edit") {
			Edit(d);
		}
		else if (command == "search") {
			Search(d);
		}
		else if (command == "print") {
			d.Print();
		}
	}

	return 0;
}