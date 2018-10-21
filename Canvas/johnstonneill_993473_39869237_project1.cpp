#include <iostream>
#include <string>
#define until_resch_figures_out_tophat while (true)

using namespace std;

/* The node class for a LinkedLines.
 */
class Line {
    public:
        Line* next;
        string* text;

        Line(string* text) {
            this->text = text;
        }

        ~Line() {
            delete this->text;
        }
};

/* Linked list of Lines, all operations are performed here.
 */
class LinkedLines {
    private:
        Line* head;
        Line* last;
        int length;
    public:
        Line* get(int index);
        void append(string* text);
        void insert(string* text, int index);
        void remove(int index);
        void set(string* text, int index);
        int get_length();

        LinkedLines() {
            this->head = NULL;
            this->last = NULL;
            this->length = 0;
        }
};

/* Get the Line pointer at a specified index.
 */
Line* LinkedLines::get(int index) {
    // Catch impossible indices
    if (index >= this->length || index < 0) return NULL;

    Line* current = this->head;
    while (--index >= 0)
        current = current->next;

    return current;
}

/* Append a new line containing text.
 */
void LinkedLines::append(string* text) {
    Line* newLine = new Line(text);

    if (this->length == 0) {
        this->head = newLine;
        this->last = newLine;
    }
    else {
        this->last->next = newLine;
        this->last = newLine;
    }

    this->length++;
}

/* Insert a new line containing text at the specified index.
 * For instance, inserting at index 0 will give the list a new head.
 */
void LinkedLines::insert(string* text, int index) {
    Line* newLine = new Line(text);

    // Catch impossible indices
    if (index > this->length || index < 0) return;

    // DRY if we're just inserting at the end of the list
    if (index == this->length) {
        this->append(text);
        return;
    }
    // If index is 0, the list head has to be modified
    else if (index == 0) {
        newLine->next = this->head;
        this->head = newLine;
    }
    else {
        Line* current = this->head;

        // Insert after current
        while (--index > 0)
            current = current->next;

        newLine->next = current->next;
        current->next = newLine;
    }

    this->length++;
}

/* Remove the line at index.
 */
void LinkedLines::remove(int index) {
    // Catch impossible indices
    if (index >= this->length || index < 0) return;

    // If index is 0, the list head has to be modified
    if (index == 0) {
        Line* temp = this->head;
        this->head = this->head->next;
        delete temp;

        // If the list also happens to be length 1, the list last changes as well
        if (this->length == 1)
            this->last = NULL;
    }
    else {
        Line* current = this->head;

        // Iterate to just before the specified index
        while (--index > 0)
            current = current->next;

        // Modify last if necessary
        if (current->next == this->last)
            this->last = current;

        Line* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    this->length--;
}

/* Set the string contained by the line at index to text.
 */
void LinkedLines::set(string* text, int index) {
    // Catch impossible indices
    if (index >= this->length || index < 0) return;

    // Only need to find the correct Line*
    Line* current = this->head;
    while (--index >= 0)
        current = current->next;

    delete current->text;
    current->text = text;
}

/* Return the list length.
 */
int LinkedLines::get_length() {
    return this->length;
}

/* Read an int from input.
 * Only complicated because sometimes reading in an int can fail drastically.
 */
int read_int() {
    int n;
    cin >> n;
    if (!cin.fail())
        return n;
    else {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
}

/* Read in a line of text from input, trim quote marks if possible.
 */
string* read_text() {
    string str;
    getline(cin, str);

    int a = str.find_first_of('\"') + 1;
    int b = str.find_last_of('\"');
    return new string(str.substr(a, min(b - a, 80)));
}

/* Implement a line editor using linked lists. You must implement your own
linked list.

A document will be represented by a linked list. Each line in the document is
a node in the linked list. Each line in the document is 80 characters. Users
can insert, delete or modify lines in the document or print the entire document.
Out of bounds print or delete requests are ignored.
 */
int main() {
    LinkedLines lines = LinkedLines();

    until_resch_figures_out_tophat {
        string command;
        cin >> command;
        cin.ignore();

        if (command == "quit") {
            Line* current = lines.get(0);
            while (current != NULL) {
                Line* temp = current->next;
                delete current;
                current = temp;
            }

            break;
        }
        else if (command == "insertEnd") {
            lines.append(read_text());
        }
        else if (command == "insert") {
            int index = read_int();
            lines.insert(read_text(), index - 1);
        }
        else if (command == "delete") {
            lines.remove(read_int() - 1);
        }
        else if (command == "edit") {
            int index = read_int();
            lines.set(read_text(), index - 1);
        }
        else if (command == "search") {
            string query = *read_text();

            int i = 1;
            Line* current = lines.get(0);
            // Need to be able to tell if nothing is found, to print a "not found"
            bool flag_found = false;

            while (i <= lines.get_length()) {
                // Print if we find a match
                if (current->text->find(query) != -1) {
                    cout << i << " " << *(current->text) << endl;
                    flag_found = true;
                }

                current = current->next;
                i++;
            }

            if (!flag_found)
                cout << "not found" << endl;
        }
        else if (command == "print") {
            int i = 1;
            Line* head = lines.get(0);
            while (i <= lines.get_length()) {
                cout << i << " " << *(head->text) << endl;
                head = head->next;
                i++;
            }
        }
    }

    return 0;
}
