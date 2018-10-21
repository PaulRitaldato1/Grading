#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
        string data;
        Node* next = nullptr;
    };


class LinkedList {
   
    
    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        unsigned int count = 0;
    
    public:
       
        void insertEnd(string input) {
           Node* newNode = new Node();
           newNode->data = input;
           
           if(count == 0) {
               head = newNode;
               tail = newNode;
               count++;
           }
            
           else {
               tail->next = newNode;
               tail = newNode;
               count++;
           } 
        }
    
        void insert(int index, string input) {
            if((index <= count + 1) && (index >=1)) {
               Node* newNode = new Node();
               newNode->data = input;
               if(index == 1) {
                   newNode->next = head;
                   head = newNode;
                   count++;
               }
               
               else if(index == count + 1) {
                   tail->next = newNode;
                   tail = newNode;
                   count++;
               }
                
               else {
                   Node* current = head;
                   int i = 1;
         
                   while(i < index - 1) {
                       current = current->next;
                       i++;
                   }
                   Node* temp = current->next;
                   current->next = newNode;
                   newNode->next = temp;
                   count++;
                }
            }
        }
    
        void Delete(int index) {
            if((index <= count) && (index >=1)) {
               if(index == 1) {
                   Node* newHead = head->next;
                   delete head;
                   head = newHead;
               }
               else {
                   Node* current = head;
                   Node* previous = head;
                   int i = 1;
         
                   while(i < index) {
                       previous = current;
                       current = current->next;
                       i++;
                   }
                   Node* temp = current->next;
                   delete current;
                   previous->next = temp;
                }
                count--;
            }
        }
           
        void print() {
            Node* current = head;
            int i = 1;
            while(i <= count) {
                cout << i << " " << current->data << endl;
                current = current->next;
                i++;
            }
        }
        
        void search(string value) {
            Node* current = head;
            int i = 1;
            bool found = false;
            while(i <= count) {
                string temp = current->data;
                string str(value);
                size_t isFound = temp.find(str);
                if(isFound != string::npos) {
                    cout << i << " " << temp << endl;
                    found = true;
                    current = current->next;
                    i++;
                }
                else {
                    current = current->next;
                    i++;
                }
            }
            if(!found) {
                cout << "not found" << endl;
            }
        }
                
    
        void edit(int index, string input) {
            Node* current = head;
            int i = 1;
            while(i < index) {
                current = current->next;
                i++;
            }
            current->data = input;
        }
    
};
    
        

        //your line editor implementation here

int main()
{
    
    LinkedList list;
   
    string input;
    while(input != "quit") {
        cin >> input;
        if(input == "insertEnd") {
            string added = "";
            cin.ignore();
            getline(cin, added);
            added.erase(remove( added.begin(), added.end(), '\"' ));
            added.erase(remove( added.begin(), added.end(), '\"' ));
            list.insertEnd(added);
        }
        else if(input == "insert") {
            int index;
            cin >> index;
            string added;
            cin.ignore();
            getline(cin,added);
            added.erase(remove( added.begin(), added.end(), '\"' ));
            added.erase(remove( added.begin(), added.end(), '\"' ));
            list.insert(index, added);
        }
        else if(input == "edit") {
            int index;
            cin >> index;
            string added;
            cin.ignore();
            getline(cin,added);
            added.erase(remove( added.begin(), added.end(), '\"' ));
            added.erase(remove( added.begin(), added.end(), '\"' ));
            list.edit(index, added);
        }
        else if(input == "delete") {
            int index;
            cin >> index;
            list.Delete(index);
        }
        else if(input == "search") {
            string searchTerm;
            cin.ignore();
            getline(cin,searchTerm);
            searchTerm.erase(remove(searchTerm.begin(), searchTerm.end(), '\"' ));
            searchTerm.erase(remove( searchTerm.begin(), searchTerm.end(), '\"' ));
            list.search(searchTerm);
        }
        else if(input == "print") {
            list.print();
        }
    }    

         
}