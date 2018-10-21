#include <iostream>
#include <string>


class Line {
    private:
        std::string value; // string value contained in current node
        Line* next; // pointer to next node
        int id; // the line number

    public:
        // Constructors
        Line();
        Line(std::string value, int id);

        // Getters
        std::string getValue(); // get line string
        Line* getNext(); // get next node
        int getId(); // get line number

        // Setters
        void setValue(std::string value); // set line string
        void setNext(Line* next); // set next node
        void setId(int id); // set line number
};


// Constructors
Line::Line(){
    next = nullptr;
    value = "";
    id = 0;
}

Line::Line(std::string value, int id){
    next = nullptr;
    this->value = value;
    this->id = id;
}

// Getters
// get line string
std::string Line::getValue(){
    return value;
}
// get next node
Line* Line::getNext(){
    return next;
}
// get line number
int Line::getId(){
    return id;
}

// Setters
// set line string
void Line::setValue(std::string value){
    this->value = value;
}
// set next node
void Line::setNext(Line* next){
    this->next = next;
}
// set line number
void Line::setId(int id){
    this->id = id;
}

////////////////////////////////////////////////////////////////////

class Page {
    private:
        Line* firstLine; // the first line on the page

    public:
        Page();  // Constructor
        int lineCount; // number of lines on the page

        // Getter & Setter
        Line* getFirstLine(); // get the firstLine node
        void setFirstLine(Line* firstLine); // set the firstLine node

        // Other Methods
        bool insertEnd(std::string line); // 1. add line to bottom of page
        bool edit(int lineNum, std::string line); // 2. overwrite line at given line number
        bool search(std::string substr); // 4. search for a substring and print the line containing it
        bool deleteLine(int lineNum); // 5. delete line at given line number
        bool insert(int lineNum, std::string line); // 6. insert new line at given line number
        void print(); // 3. print the entire page
};

// Constructor
Page::Page(){
    firstLine = new Line();
    lineCount = 0;
}

// Getter & Setter
// get the firstLine node
Line* Page::getFirstLine() {
    return firstLine;
}
// set the firstLine node
void Page::setFirstLine(Line* firstLine) {
    this->firstLine = firstLine;
}


// Other Methods
// 1. add new line to bottom of page
bool Page::insertEnd(std::string line){
    if (line == ""){
        return false;
    } else if (lineCount == 0) { // Empty Page
        getFirstLine()->setValue(line);
        lineCount++;
        getFirstLine()->setId(lineCount);
        return true;
    } else { // Non-empty Page
        Line* curr = getFirstLine();
        while (curr->getNext() != nullptr)
            curr = curr->getNext();

        lineCount++;
        Line* newLine = new Line(line, lineCount);
        curr->setNext(newLine);
        return true;
    }
}

// 2. overwrite line at given line number
bool Page::edit(int lineNum, std::string line){
    Line* curr = getFirstLine();
    while (curr->getId() != lineNum){
        if (curr->getNext() == nullptr)
            return false;
        curr = curr->getNext();
    }
    curr->setValue(line);
    return true;
}

// 3. print the entire page
void Page::print(){
    if (lineCount == 0){
        std::cout << "doc is empty" << std::endl;
        return;
    } else {
        Line* curr = getFirstLine();
        while (curr != nullptr){
            std::cout << curr->getId() << " " << curr->getValue() << std::endl;
            curr = curr->getNext();
        }
    }
}

// 4. search for a substring and print the line containing it
bool Page::search(std::string substr){
    Line* curr = getFirstLine();
    bool found = false;

    while (curr != nullptr){
        std::string mystr = curr->getValue();

        // find the line matching given substring
        for (int ii = 0; ii <= mystr.size() - substr.size(); ii++) {
            int jj;
            for (jj = 0; jj < substr.size(); jj++){
                if (mystr.at(ii+jj) != substr.at(jj))
                    break;
            }

            if (jj == substr.size()){
                std::cout << curr->getId() << " " << curr->getValue() << std::endl;
                found = true;
                break;
            }
        }

        curr = curr->getNext(); // move to next line
    }

    return found;
}

// 5. delete line at given line number
bool Page::deleteLine(int lineNum){
    Line* curr = getFirstLine();
    Line* prev = curr;
    while (curr->getId() != lineNum){
        if (curr->getNext() == nullptr)
            return false;
        prev = curr;
        curr = curr->getNext();
    }

    if (prev == curr)
        setFirstLine(getFirstLine()->getNext());
    else
        prev->setNext(curr->getNext());
    delete curr;

    // reset all the remaining Ids
    Line* ncurr = prev->getNext();
    while (ncurr != nullptr){
        ncurr->setId(lineNum);
        lineNum++;
        ncurr = ncurr->getNext();
    }
    return true;
}

// 6. insert new line at given line number
bool Page::insert(int lineNum, std::string line){
    if (lineNum == lineCount + 1){
        insertEnd(line);
        return true;
    }

    Line* curr = getFirstLine();
    Line* prev = curr;
    while (curr->getId() != lineNum){
        if (curr->getNext() == nullptr)
            return false;
        prev = curr;
        curr = curr->getNext();
    }

    // create the new node
    Line* newLine = new Line(line, lineNum);
    if (prev == curr){ // insert new head
        newLine->setNext(getFirstLine());
        setFirstLine(newLine);
    } else {
        newLine->setNext(curr);
        prev->setNext(newLine);
    }

    // reset all the remaining Ids
    while (curr != nullptr){
        lineNum++;
        curr->setId(lineNum);
        curr = curr->getNext();
    }
    return true;
}

///////////////////////////////////////////////////////////////////////
// Extra Methods for getting line data
std::string getQuotedStr(){
    std::string data;
    std::getline(std::cin, data);
    if (data.size() >= 2)
        return data.substr(2, data.size()-3);
    else
        return "";
}

////////////////////////////////////////////////////////////////////
int main()
{
    std::string cmd, arg1, arg2, stop;
    bool success;
    Page* Editor = new Page();

    while (true) {
        std::cin >> cmd;

        if (cmd == "quit" || cmd == "q"){
            delete Editor;
            return 0;

        } else if (cmd == "print") {
            Editor->print();

        } else if (cmd == "insertEnd") {
            arg1 = getQuotedStr();
            success = Editor->insertEnd(arg1);
            if (!success)
                std::cout << "insert failed" << std::endl;

        } else if (cmd == "insert") {
            std::cin >> arg1;
            arg2 = getQuotedStr();
            success = Editor->insert(stoi(arg1), arg2);
            if(!success)
                std::cout << "insert failed" << std::endl;

        } else if (cmd == "edit") {
            std::cin >> arg1;
            arg2 = getQuotedStr();
            success = Editor->edit(stoi(arg1), arg2);
            if(!success)
                std::cout << "edit failed" << std::endl;

        } else if (cmd == "delete") {
            std::cin >> arg1;
            success = Editor->deleteLine(stoi(arg1));
            if (!success)
                std::cout << "deletion failed" << std::endl;

        } else if (cmd == "search") {
            arg1 = getQuotedStr();
            success = Editor->search(arg1);
            if (!success)
                std::cout << "not found" << std::endl;

        } else
            std::cout << "Please enter a valid command" << std::endl;
    }
}
