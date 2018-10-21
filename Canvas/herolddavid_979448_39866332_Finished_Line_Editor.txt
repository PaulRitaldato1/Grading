#include <string>
#include <iostream> 
using namespace std;

struct node {
    std::string data;
    node* next;
};

node *head;
node *tail;

void insert(std::string &str, int index){
    int counter = 2;
    int count = 0;
    node* prev = head;  
    node* curr = head;
    node* newNode = new node();
    newNode->data = str;   

    while (curr != nullptr) {
        curr = curr->next;
        count++;
    }
    curr = head;
    if (head == NULL){ // The linked list is empty
        head = newNode;
        return;
    }
    else if (index == 1){
        newNode->next = head;
        head = newNode;
    }
    else {
        curr = curr->next;
        while (curr != NULL){
            if (counter == index){
                prev->next = newNode;
                newNode->next = curr;
                break;
            }
            else{
                prev = prev->next;
                curr = curr->next;
                counter++;
            }
        }
       if (counter == index){
                prev->next = newNode;
                newNode->next = curr;
        }
    }
}

void insertEnd(std::string str){
    node* ptr = head;
    node* newNode = new node;
    newNode->data = str;

    if(head == nullptr){
        head = newNode;
        return;
    }

    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = newNode;
}

void deleteNode(int index){
    node** curr = &head;
    int currLine = 1;
    
    while(*curr != nullptr){
        if(currLine == index){
            *curr = (*curr)->next;
            return;
        }
        currLine++;
        curr = &((*curr)->next);
    }
}

void editNode(std::string str, int index){
    node* current = head;
    int counter = 0; // might be 1, fool around with it
    while (current != nullptr) {
        current = current->next;
        counter++;
    }
    current = head;
    if (index < counter && index >= 1) {
        for (int i = 1; i < index; i++)
            current = current->next;
        current->data = str;
    }
}

void printAll(){
    node* temp = head;
    int count = 1;
    while (temp != NULL){
        std::cout << count << " " << temp->data << std::endl;
        temp = temp->next;
        count++;
    }
}

void search(std::string str){
    node* current = head;
    int count = 1;
    std::string tempStr;
    bool found = false;
    
    while(current != NULL){      
        tempStr = current->data;
        if(tempStr.find(str) != std::string::npos){
            std::cout << count << " " << tempStr << std::endl;
            found = true;
        }
        count++;
        current = current->next;
    }
    if(!found){
        std::cout << "not found" << std::endl;
    }
}


int main(){
    std::string s1;
    std::string s2;
    std::string s3;
    size_t found1 = 0;
    size_t found2 = 0;
    size_t found3 = 0;
    

    while(s1 != "quit"){
        getline(std::cin, s1);
        
        if(s1.find("insertEnd") != std::string::npos){
            found1 = s1.find_first_of("\"");
            found2 = s1.find_last_of("\"");
            s2= s1.substr(found1+1,found2 - found1 - 1);
            insertEnd(s2);
        }
        
        else if(s1.find("insert") != std::string::npos){
            s2 = s1.substr(7, 8);
            int index = atoi(s2.c_str());
            found1 = s1.find_first_of("\"");
            found2 = s1.find_last_of("\"");
            s3 = s1.substr(found1+1,found2 - found1 - 1);
            insert(s3, index);                       
        }
        
        else if(s1.find("delete") != std::string::npos){
            s2 = s1.substr(7, 8);
            int index = atoi(s2.c_str());
            deleteNode(index);
        }
        
        else if(s1.find("edit") != std::string::npos){
            s2 = s1.substr(5, 6);
            int index = atoi(s2.c_str());
            found1 = s1.find_first_of("\"");
            found2 = s1.find_last_of("\"");
            s3 = s1.substr(found1+1,found2 - found1 - 1);     
            editNode(s3, index);
        }
        
        else if(s1.find("print") != std::string::npos){
            printAll();
        }
        
        else if(s1.find("search") != std::string::npos){
            found1 = s1.find_first_of("\"");
            found2 = s1.find_last_of("\"");
            s2= s1.substr(found1+1,found2 - found1 - 1); 
            search(s2);
        }
    }
    
    return 0;


}