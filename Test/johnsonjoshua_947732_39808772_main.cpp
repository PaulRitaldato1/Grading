//Line Editor Canvas Submission
//Joshua Johnson
#include <string>
#include <iostream>

//your linked list implementation here

class LinkedList{
    public:
    class Node{
        public:
        std::string data;
        Node* next;
    };

    private:
    Node* head;
    unsigned int nodeCount;

    public:
    //Accessors
    void print() const;        //print entire document
    void search(std::string text);

    //Insertion
    void insertEnd(const std::string &data); //insert given text at the end of the document
    void insertAt(const std::string &data, unsigned int index);

    //Modify
    void edit(const std::string &data, unsigned int index);

    //Removal
    void removeAt(unsigned int index);  //delete line at index

    //Construction
    LinkedList();
};

LinkedList::LinkedList(){
    head = nullptr;
    nodeCount = 0;
}

void LinkedList::print() const{
    Node* current = head;
    int i = 1;
    while(current != nullptr){
        std::cout << i << " " << current->data << std::endl;
        current = current->next;
        i++;
    }
}

void LinkedList::insertEnd(const std::string &data){
    LinkedList::Node* node = new LinkedList::Node();

    //Current Node Changes
    node->data = data;
    node->next = nullptr;

    if(nodeCount == 0){
        head = node;
    }
    else{
        //Get to last node in current list
        Node* current = head;
        for(int i=0; i<nodeCount-1; i++){
            current = current->next;
        }

        current->next = node; //Set "node" as the new last node
    }

    nodeCount++;
}

void LinkedList::insertAt(const std::string &data, unsigned int index){
    
    //Error Checking
    if(index>nodeCount){
        return;             //do nothing
    }
    
    LinkedList::Node* newNode = new LinkedList::Node();

    //Current Node Changes
    newNode->data = data;


    if (index < nodeCount){    //and index >= 0?
        //insert in front of the index
        //("current" is one in front of the index)
        if(index!=0){
            Node* current = head;
            for (unsigned int i = 0; i < index-1; i++){
                current = current -> next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        else{
            newNode->next = head;
            head = newNode;
        }

        nodeCount++;
    }
    else if (index == nodeCount){
        //insert at the end
        delete newNode;
        insertEnd(data);
    }
    //else invalid index and ignore it
}

void LinkedList::edit(const std::string &data, unsigned int index) {
    Node* current = head;
    //Get to node of interest
    for (unsigned int i = 0; i < index; i++){
        current = current -> next;
    }

    current->data = data; //edit data
}

void LinkedList::removeAt(unsigned int index) {
    if(index>nodeCount-1){
        return;             //do nothing
    }
    else if(index == 0){
        head = head->next;
    }
    else{
        Node* current = head;
        //Get to node of interest
        for (unsigned int i = 0; i < index-1; i++){
            current = current -> next;
        }

        current->next = current->next->next;
    }

    nodeCount--;
}

void LinkedList::search(std::string text) {
    Node* current = head;

    bool foundLine = false;

    for(unsigned int i=0; i<nodeCount; i++){
        if(current->data.find(text) != std::string::npos){
            std::cout << i+1 << " " << current->data << std::endl;
            foundLine = true;
        }
        current = current->next;
    }

    if(!foundLine){
        std::cout << "not found" << std::endl;
    }
}




    //your line editor implementation here
class LineEditor{
    private:
    LinkedList list;

    //One function
    public:
    bool doYoThang(std::string line);

    //Takes in a string and manipulates "list" based upon input
    //return false if "quit" is called
};

bool LineEditor::doYoThang(std::string line){
    if(line == "print"){
        list.print();
    }
    else if(line == "quit"){
        return false;
    }
    else if(line.compare(0,9,"insertEnd") == 0){
        //Remove quotation marks
        std::size_t startPos = line.find("\"");
        std::string text = line.substr(startPos+1,line.size()-startPos-2);

        list.insertEnd(text);
    }
    else if(line.compare(0,6,"insert") == 0){
        int index = std::stoi(line.substr(7,8), nullptr);

        //Remove quotation marks
        std::size_t startPos = line.find("\"");
        std::string text = line.substr(startPos+1,line.size()-startPos-2);

        list.insertAt(text, (unsigned int) index-1); //convert to computer index
    }
    else if(line.compare(0,4,"edit") == 0){
        int index = std::stoi(line.substr(5,8), nullptr);

        //Remove quotation marks
        std::size_t startPos = line.find("\"");
        std::string text = line.substr(startPos+1,line.size()-startPos-2);

        list.edit(text, (unsigned int) index-1);
    }
    else if(line.compare(0,6,"delete") == 0){
        int index = std::stoi(line.substr(7,8), nullptr);
        list.removeAt((unsigned int) index-1);
    }
    else if(line.compare(0,6,"search") == 0){
        //Remove quotation marks
        std::size_t startPos = line.find("\"");
        std::string text = line.substr(startPos+1,line.size()-startPos-2);

        list.search(text);
    }
    return true;
}



int main()
{
    //your code to invoke line editor here
    LineEditor le;


    //loop to take in user input
    bool running = true;

    std::string line;
    while(running){
        getline(std::cin, line);

        running = le.doYoThang(line);
    }
    return 0;
}