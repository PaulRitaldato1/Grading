#include <iostream>
#include <string>
using namespace std;

class LinkedList{
    public:
        class Node{
            public:
                string str;
                Node* next;
                Node* prev;
        };

    private:
        int size;
        Node* head;
        
    public:
        LinkedList(){
            int size = 0;
            head = NULL;
        }
    
        Node* getHead(){
            return head;
        }
    
        void insertAtIndex(string str, int index){
            Node* currentNode = head;
            Node* newNode = new Node;
            newNode->str = str;
            if(currentNode == nullptr){
                head = newNode;
                return;
            }
            --index;
            while(--index){
                if(currentNode == nullptr) return;
                currentNode = currentNode->next;
            }
            if(currentNode == nullptr) return;
            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }
    
        void deleteNode(int index){
            Node* currentNode = head;
            Node* prevNode = nullptr;
            if(currentNode == nullptr){
                return;
            }
            if(index == 1){
                head = head->next;
            } else{
                while(--index){
                    if(currentNode == nullptr) return;
                    prevNode = currentNode;
                    currentNode = currentNode->next;
                }
                if(currentNode == nullptr) return;
                prevNode->next = currentNode->next;
            }
           
        }
    
        void edit(string str, int index){
            Node* currentNode = head;
            if(currentNode == nullptr){
                insertEnd(str);
                return;
            }
            while(--index > 0){
                currentNode = currentNode->next;
            }
            currentNode->str = str;
        }
    
        void insertEnd(string str){
            Node* currentNode = head;
            Node* newNode = new Node;
            newNode->str = str;
            newNode->next = nullptr;
            if(currentNode == nullptr){
                head = newNode;
                return;
            }
            
            while(currentNode->next != nullptr){
                currentNode = currentNode->next;
            }
            
            currentNode->next = newNode;
        }
    
        string find(string str){
            int i = 1;
            Node* currentNode = head;
            string found = "not found";
            while(currentNode != nullptr){
                if(currentNode->str.find(str) != std::string::npos){
                    if(found == "not found")
                        found = std::to_string(i) + "" + currentNode->str;
                    else{
                        found += "\n"+ std::to_string(i) + "" + currentNode->str;
                    }
                }
                ++i;
                currentNode = currentNode->next;
            }
            
            return found;
        }
};

string sanitizeStr(string str){
    std::size_t found = str.find_first_of("\"");
    while (found!=std::string::npos){
        str.replace(found, 1, "");
        found=str.find_first_of("\"",found+1);
    }
    str = str.substr(0, 81);
    return str;
}

int main()
{
    LinkedList *doc = new LinkedList();
    std::string command;
    std::string line;
    int index;
    std::cin >> command;
    while(command != "quit"){
        if(command == "insert"){
            std::cin >> index;
            getline(std::cin, line);
            line = sanitizeStr(line);
            doc->insertAtIndex(line, index);
        } else if(command == "insertEnd"){
            getline(std::cin, line);
            line = sanitizeStr(line);
            doc->insertEnd(line);
        } else if(command == "edit"){
            std::cin >> index;
            getline(std::cin, line);
            line = sanitizeStr(line);
            doc->edit(line, index);
        } else if(command == "delete"){
            std::cin >> index;
            doc->deleteNode(index);
        } else if(command == "print"){
            int i = 1;
            LinkedList::Node* temp = doc->getHead();
            while(temp != nullptr){
                std::cout<<std::to_string(i++)<<temp->str<<std::endl;
                temp = temp->next;
            }
        } else if(command == "search"){
            getline(std::cin, line);
            line = sanitizeStr(line);
            std::cout<< doc->find(line) <<std::endl;   
        }
        std::cin>> command;
    }
}