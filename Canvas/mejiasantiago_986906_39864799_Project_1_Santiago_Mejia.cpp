#include <iostream>
#include <sstream>

using namespace std;

struct node {

    std::string sentence;
    node *next;
};

class linkedList {

public:
    node *head;
    node *tail;

    linkedList() {
        head = NULL;
        tail = NULL;
    }
};


void insert(node *&head, node *&tail, std::string sentence) {
    std::string insertVal = sentence;

    auto *temp = new node;
    temp->sentence = insertVal;
    temp->next = NULL;

    if (head == NULL) {   //if the linked list is empty it places the first node at the first entry
        head = temp;
        tail = temp;

    } else {              //pointing the next value to the last value in the linked list
        tail->next = temp;
        tail = temp;
    }
}

void insertAt(node *&head, int index, std::string value) {

    std::string insertVal = value;

    node *current;
    auto *prev = new node;
    auto *temp = new node;
    current = head;

    if (index == 1) {  //special case of the first index, placing the sentence at the head of the linked list
        temp->sentence = insertVal;
        temp->next = head;
        head = temp;

    } else {

        int insertInc = 1;

        while (insertInc != index) {//Loop iterating through linked list to insert at given index value
            insertInc++;
            prev = current;
            current = current->next;
        }

        temp->sentence = insertVal;
        prev->next = temp;
        temp->next = current;
    }
}

void deletePosition(node *&head, int index) {
    node *current;
    node *prev;
    current = head;
    int delIncrement = 0;

    while (delIncrement != index - 1) {/**loop to delete the given index input, shifting the linked list left until the index
                                       is found */

        delIncrement++;
        prev = current;
        current = current->next;
    }

    prev->next = current->next;
}


void print(node *&head) {

    node *temp;
    temp = head;
    int index = 0;

    while (temp != NULL) {
        index++; //index used to display the node index value
        std::cout << index << " " << temp->sentence << "\n";
        temp = temp->next;
    }
}

int linkedListSize(node *&head) { //created a "size" function to get the number of inputs currently in the list, used in main

    node *temp;
    temp = head;
    int sizeIncr = 0;

    while (temp != NULL) {
        sizeIncr++;
        temp = temp->next;
    }
    return sizeIncr;
}


void search(node *&head, std::string value) {

    node *temp;
    temp = head;
    int increment = 0;
    bool oneMatch = false;

    while (temp != NULL) {
        increment++;

        if(temp->sentence.find(value) != string::npos){ //the find function returns values within the sentence

            std::cout << increment << " " << temp->sentence << "\n";
            oneMatch = true;
        }

        temp = temp->next;
    }
    if(!oneMatch){//if  there is no match, it skips over and returns not found

        std::cout<<"not found\n";
    }
}


int main() {

    node *head = NULL;
    node *last = NULL;

    std::string userInput;

    do {

        std::getline(std::cin, userInput);
        std::string insertString = userInput;

        if (insertString.substr(0, 10) == "insertEnd ") {                 /**assumes a space after insertEnd, as per instructions
                                                                                 if input doesn't match, nothing is outputted**/
            std::string input = insertString.substr(10, insertString.size());

            if ((input.substr(0, 1) == "\"") && (input.substr(input.size() - 1, input.size()) == "\"")) {
                input = input.substr(1, input.size() - 2); //removing quotation marks from input

                if (input.length() <= 80) {
                    insert(head, last, input);             //input without quotations is placed at the end of the linked list
                }
            }
        }

        if (userInput == "print" or userInput == "print ") {//assumes either no space or a space

            print(head);
        }

        if (userInput.substr(0, 7) == "insert ") { //assumes one space between insert and an integer
            std::size_t found = userInput.find("\"");
            std::string insertIndex = userInput.substr(7, found);

            try {

                std::string rowVal = userInput.substr(7, found - 1);
                std::size_t found2 = rowVal.find("\""); //finds the last quotation mark
                std::string rowValue = rowVal.substr(0, found2);

                int rowIndex = std::stoi(rowValue);

                std::size_t notADigit = rowValue.find_first_not_of("0123456789 "); //checks if value is a digit

                if (notADigit != string::npos) {
                    rowIndex = 0;
                }

                std::string insertText = userInput.substr(found, userInput.length() - 1);

                if ((insertText.substr(0, 1) == "\"") &&
                    (insertText.substr(insertText.size() - 1, insertText.size()) == "\"") && rowIndex > 0 &&
                    rowIndex-1 <= linkedListSize(head)) { //removes quotations
                    std::string atInput = insertText.substr(1, insertText.size() - 2);

                    if (atInput.length() <= 80) { //80 character limit, given input length
                        insertAt(head, rowIndex, atInput);
                    }

                    if(rowIndex-1 == linkedListSize(head)){ //uses the size of the list to input at the end of the list

                        insert(head, last, atInput);
                    }
                }



            }
            catch (std::invalid_argument) {//ignores input that overflows or otherwise could not be casted to another type (string to int)

            }

            catch (std::out_of_range) {

            }
        }


        if (userInput.substr(0, 5) == "edit ") {//similar to "insert "
            std::size_t found = userInput.find("\"");
            std::string insertIndex = userInput.substr(7, found);

            try {

                std::string rowVal = userInput.substr(5, found - 1);
                std::size_t found2 = rowVal.find("\"");
                std::string rowValue = rowVal.substr(0, found2);
                int rowIndex = std::stoi(rowValue);

                std::size_t notADigit = rowValue.find_first_not_of("0123456789 ");

                if (notADigit != string::npos) {
                    rowIndex = 0;
                }

                std::string insertText = userInput.substr(found, userInput.length() - 1);

                if ((insertText.substr(0, 1) == "\"") &&
                    (insertText.substr(insertText.size() - 1, insertText.size()) == "\"") && rowIndex > 0 &&
                    rowIndex <= linkedListSize(head)) {
                    std::string atInput = insertText.substr(1, insertText.size() - 2);

                    if (atInput.length() <= 80) {

                        insertAt(head, rowIndex, atInput);
                        deletePosition(head, rowIndex + 1);

                    }

                }

            }
            catch (std::invalid_argument) {

            }

            catch (std::out_of_range) {

            }
        }

        if (userInput.substr(0, 7) == "search ") { //similar command to previous options

            std::size_t found = userInput.find("\"");
            std::string insertIndex = userInput.substr(7, found);

            std::string input = insertString.substr(7, insertString.size());

            if ((input.substr(0, 1) == "\"") && (input.substr(input.size() - 1, input.size()) == "\"")) {
                //checks if the variable searched is less than 80 characters, and removes quotations from the search input

                input = input.substr(1, input.size() - 2);

                if (input.length() <= 80) {
                    search(head, input);
                }
            }
        }

        if (userInput.substr(0, 7) == "delete ") {
            std::string deleteIndex = insertString.substr(7, insertString.size());
            std::size_t valEmptySpace = deleteIndex.find_last_of("123456789");


            if (valEmptySpace != string::npos) {
                deleteIndex = deleteIndex.substr(0,valEmptySpace+1);
            }


            try {
                int intDeleteIndex = std::stoi(deleteIndex);

                std::size_t notADigit = deleteIndex.find_first_not_of("123456789");\

                if (notADigit != string::npos) {
                    intDeleteIndex = 0;
                }

                if (intDeleteIndex == 1 && linkedListSize(head) >= 1) {//special case, if list has at least 1 element and deletes the first element

                    node *temp;
                    temp = head;
                    delete temp;
                    head = head->next;

                }

                else if (head != NULL && intDeleteIndex <= linkedListSize(head) && intDeleteIndex > 0) {
                    deletePosition(head, intDeleteIndex);
                }
            }
            catch (std::invalid_argument) {
            }
        }
    } while (userInput != "quit"); //in case user inputs a space after quit

}