#include <string>
#include <iostream>

using namespace std;

template <typename T>
class linkedList{

    //Create the node struct
    struct Node {
        T item = nullptr;
        Node* next = nullptr;

        Node(const T& item, Node* next):
                item(item),
                next(next) {}

        ~Node(){};
    };

    Node* head = nullptr;
    int size = 0;


public:
    void insert(const T& item, int location){

        // check for errors in location
        if(location < 1 || location > size+1){
            return;
        }

        // Insert at the beginning
        if(location == 1){
            Node* node = new Node(item, head);
            head = node;
            size++;
            return;
        }

        // Add node to a different location
        Node* iter = head;
        for(int i = 0; i < (location-2); i++){
            iter = iter->next;
        }
        Node* node = new Node(item, iter->next);
        iter->next = node;
        size++;
        return;
    }

    //insert the item at the end
    void insertEnd(const T& item){
        //Add node to the head
        if(size < 1){
            Node* node = new Node(item, nullptr);
            head = node;
            size++;
            return;
        }

        //Iterate through linked list until you reach the end
        Node* iter = head;
        while(iter->next != NULL){
            iter = iter->next;
        }
        Node* node = new Node(item, nullptr);
        iter->next = node;
        size++;
        return;
    }

    // Delete the item at the specified location
    void del(int location){
        if(location < 1 || location > size){
            return;
        }

        // Delete head node
        if(location == 1){
            Node* del = head;
            head = head->next;
            size--;
            delete del;
            return;
        }

        // Delete the node at a specified location
        Node* curr = head;
        Node* prev = curr;
        for(int i = 0; i < (location-1); i++){
            prev = curr;
            curr = curr->next;
        }
        Node* del = curr;
        prev->next = curr->next;
        delete del;
        size--;
        return;
    }

    // Edit the line by first deleting the old item in
    // the linked list. This is followed by inserting
    // the new line into the old location.
    void edit(int location, const T& item){
        del(location);
        insert(item, location);
    }

    // searches for an item in the linked
    // list prints the item if it finds it
    void search(const T& item){
        Node* curr = head;
        bool found = false;
        //iterate through list
        for(int i = 1; i <= size; i++){
            //if the list's string contains the requested substring, print the line.
            if(curr->item.find(item) != string::npos){
                cout << i << " " << curr->item << "\n";
                found = true;
            }
            curr = curr->next;
        }
        //if we don't find the item, say so
        if(!found){
            cout << "not found\n";
        }
    }

    // print out the items in the linked list have the
    // position the linked list printed before the item
    void print(){
        Node* curr = head;
        for(int i = 1; i <= size; i++){
            cout << i << " " << curr->item << "\n";
            curr = curr->next;
        }
    }
};

int main() {
    string read;
    linkedList <string> list;
    while(getline(cin, read)){

        // Find out what the command, location, and the line is
        string command;
        string strLocation;
        string line;
        int spaceCount = 0;
        for(int i = 0; i < read.length(); i++){
            // check if there is a space to divide the command and line #
            if(read[i] == ' ' && spaceCount < 2){
                spaceCount++;
            } else if (spaceCount == 0){
                // get the command
                command += read[i];
            } else if (spaceCount == 1){
                // If the command doesn't have a number, check if it is one of the other commands without a number
                if(command == "insertEnd" || command == "search"){
                    line += read[i];
                    spaceCount++;
                    continue;
                } else if (command == "print" || command == "quit") {
                    break;
                }
                //get the location as a string
                strLocation += read[i];
            } else {
                // get the line to be added
                line += read[i];
            }
        }

        // Get the location as a number
        int location = -1;
        if(strLocation.length() > 0){
            bool test = true;
            for(int i = 0; i < strLocation.length(); i++) {
                if (strLocation[i] > '9' || strLocation[i] < '0') {
                    test = false;
                }
            }
            if(!test){
                continue;
            } else {
                location = stoi(strLocation);
            }
        }

        // Adjust the sentence to not have quotations
        if(line.length() > 0){
            if((line[0] == '\"') && (line[line.length()-1] == '\"')){
                line = line.substr(1,line.length()-2);
            } else continue;
        }

        //find what the command is and run the proper execution
        if(command == "quit") {
            return 0;
        } else if (command == "insertEnd"){
            list.insertEnd(line);
        } else if(command == "insert"){
            list.insert(line, location);
        } else if (command == "edit"){
            list.edit(location, line);
        } else if (command == "delete"){
            list.del(location);
        } else if (command == "search"){
            list.search(line);
        } else if (command == "print"){
            list.print();
        }

    }
}