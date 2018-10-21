#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cstring>
#include <string>
#include <vector>

class linkedList {
private:
    struct node {
        int index;
        node* next;
        std::string name;
    };
    typedef struct node* nodePtr;
    nodePtr head;
    nodePtr current;
    nodePtr temp;
public:
    linkedList();
    void insertEnd(std::string line);
    void insert(int location, std::string userInput);
    void Delete(int location);
    void print();
    void correctionOfIndices();
    void search(std::string userInput);
    void edit(int location, std::string userInput);
};
linkedList::linkedList() {
    head = NULL;
    current = NULL;
    temp = NULL;
} //constructor

void linkedList::insertEnd(std::string line) {
    static int count = 1;
    nodePtr n = new node;
    n -> index = count;
    n -> next = NULL;
    n -> name = line;
    if(head != NULL){
        current = head;
        while(current -> next != NULL){
            current = current -> next;
        }
        current -> next = n;
    }
    else{
        head = n;
    }
    count++;
    this->correctionOfIndices();
} //adds nodes

void linkedList::Delete(int location) {
    bool evidenceOfChange = false;
    nodePtr delPtr = NULL;
    temp = head;
    current = head;
    while(current != NULL){
        if(current->index == location){
            delPtr = current;
            current = current -> next;
            temp -> next = current;
            if (delPtr == head){
                head = head ->next;
                temp = NULL;
            }
            delete delPtr;
            evidenceOfChange = true;
        }
        if(evidenceOfChange && current != NULL){
            current -> index = current ->index -1;
        }
        if(current == NULL){
            break;
        }
        temp = current;
        current = current -> next;
    }
    if (current == NULL && !evidenceOfChange){
        delete delPtr;
    }

} //deletes nodes

void linkedList::print() {
    current = head;
    while (current != NULL){
        std::cout << current -> index << " " << current ->name << "\n";
        current = current -> next;
    }
} //prints the linked list

void linkedList::search(std::string userInput){
    std::string sample;
    bool wasThereAMatch = false;
    const auto match = userInput.size();
    unsigned long count;
    char * arrayOfCharacters = new char[userInput.size()+1];
    std::strcpy(arrayOfCharacters,userInput.c_str());
    current = head;
    while(current != NULL){
        count = 0;
        sample = current ->name;
        for(std::string::iterator i = sample.begin(); i != sample.end(); ++i){
            if(count > match){
                current = NULL;
                break;
            }
            if(*i == arrayOfCharacters[count]){
                count++;
            }
            else if( count > 0 &&  *i != arrayOfCharacters[count]){
                break;
            }
            if(count == match){
                std::cout << current -> index << " " << current->name << std::endl;
                wasThereAMatch = true;
                break;
            }
        }
        if(current == NULL){
            break;
        }
        current = current -> next;
    }
    if(!wasThereAMatch){
        std::cout << "not found" << std::endl;
    }
}

void linkedList::edit(int location, std::string userInput) {
    current = head;
    while(current != NULL){
        if(current -> index == location){
            current -> name = userInput;
        }
        current = current -> next;
    }
}

void linkedList::insert(int location, std::string userInput) {
    nodePtr temp;
    bool evidenceOfChange = false;
    int count = 1;
    nodePtr n = new node;
    n -> index = location;
    n -> next = NULL;
    n -> name = userInput;
    if(head != NULL){
        current = head;
        while(current != NULL){
            if(current -> index == location - 1){
                n -> next = current -> next;
                current -> next = n;
                evidenceOfChange = true;
            }
            count += 1;
            current = current -> next;

        }
        if(count > location && !evidenceOfChange){
            this->insertEnd(userInput);
        }
        this->correctionOfIndices();
    }
}
void linkedList::correctionOfIndices() {
    temp = head;
    current = temp -> next;
    while(current != NULL){
        if(temp -> index != current -> index - 1){
            current -> index = temp -> index + 1;
        }
        temp = current;
        current = current -> next;
    }
}
int main() {
    linkedList list;
    std::string userInput;
    int placeInList;
    while (getline(std::cin,userInput)){
        if(userInput.size() > 80) {
            std::cout << "limit is 80 characters" << std::endl;
            continue;
        }
        std::string input;
        bool finished = false;
        char * arrayOfCharacters = new char[userInput.size()+1];
        std::strcpy(arrayOfCharacters,userInput.c_str());
        if(arrayOfCharacters[0] == 'i' && arrayOfCharacters[8] == 'd'){
            for(std::string::iterator i= userInput.begin(); i!= userInput.end(); ++i){
                if(*i == '"'){
                    finished = true;
                }
                else if(finished){
                    input.push_back(*i);
                }
                else if(*i=='"'){
                    finished = false;
                    break;
                }
            }
            list.insertEnd(input);
        }
        else if(arrayOfCharacters[0] == 'i'){
            placeInList = (int) arrayOfCharacters[7] - '0';
            for(std::string::iterator i= userInput.begin(); i!= userInput.end(); ++i){
                if(*i == '"'){
                    finished = true;
                }
                else if(finished){
                    input.push_back(*i);
                }
                else if(*i=='"'){
                    finished = false;
                    break;
                }
            }
            list.insert(placeInList,input);
        }
        else if(arrayOfCharacters[0] == 'd'){
            placeInList = (int) arrayOfCharacters[7] - '0';
            list.Delete(placeInList);
        }
        else if(arrayOfCharacters[0] == 's'){
            for(std::string::iterator i= userInput.begin(); i!= userInput.end(); ++i){
                if(*i == '"'){
                    finished = true;
                }
                else if(finished){
                    input.push_back(*i);
                }
                else if(*i=='"'){
                    finished = false;
                    break;
                }
            }
            list.search(input);
        }
        else if(userInput == "print"){
            list.print();
        }
        else if(arrayOfCharacters[0] == 'e'){
            placeInList = (int) arrayOfCharacters[5] - '0';
            for(std::string::iterator i= userInput.begin(); i!= userInput.end(); ++i){
                if(*i == '"'){
                    finished = true;
                }
                else if(finished){
                    input.push_back(*i);
                }
                else if(*i=='"'){
                    finished = false;
                    break;
                }
            }
            list.edit(placeInList,input);
        }
        else if(userInput == "quit"){
            break;
        }
        else{
            std::cout << "invalid input" <<std::endl;
        }
    }
}
