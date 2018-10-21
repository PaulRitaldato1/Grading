//Dylan Chopra
//COP3530
//Programming Assignment 1

#include <string>
#include <iostream>
using namespace std;

class Node{
    public:
        string input;
        Node* next = NULL;
};
 
class Project1{
	public:

static Node* insert(Node* head, int index, string valueInput){
    Node* newNode = new Node();
    newNode->input = valueInput;
    Node* curr = new Node();
    Node* prev = new Node();
    curr = head;
    
    if(head == NULL){
        return NULL;
    }
    if(index == 0){
        newNode->next= head;
        return newNode;
    }
    else{
        for(int i = 1; i < index+1; i++){
            if(!curr){
                return NULL;
            }
            prev = curr;
            curr = curr->next;
        }
        
        prev->next = newNode;
        newNode->next = curr;
        return head;
    }
}

static Node* insertEnd(Node* head, string valueInput){
    Node* curr = head;
    int count = 0;
    for(int i = 0; curr; i++){
        curr = curr->next;
        count++;
    }
  return insert(head,count-1,valueInput);
}

static Node* deleteNode(Node* head, int index){
    Node* curr = head;
    Node* prev = NULL;
    if(index == 0){
        return head->next;
    }
    
    for(int i = 0; i < index; i++){
        prev = curr;
        curr = curr->next;
    }
   prev->next = curr->next;
   delete curr;
   return head;
}

static Node* editNode(Node* head, int index, string valueInput){
    Node* curr = head;
    
    for(int i = 0; i<index; i++){
        curr = curr->next;
    }
    
    curr->input = valueInput;
    return head;
}

static void printList(Node* head){
    Node* curr = head;
    int count = 1;
    while(curr->next){
        cout << count << " " << curr->input << endl;
        curr = curr->next;
        count++;
    }
  }
 static void searchList(Node* head, string inputValue){
	bool x = false;
    Node* curr = head;
    int count = 0;
    string message = inputValue;
    while(curr->next){
		if(curr->input.find(message) != string::npos){
			cout << count+1 << " " << curr->input << endl;
			x = true;
		}
        curr = curr->next;
        count++;
    }
    if(!x){
		cout << "not found" << endl;
	}
  }
};

int main(){
		Node* head = new Node();
		bool x = true;
		
		while(x){
		string command;
		cin >> command;
		
		if(command.compare("quit") == 0){
			x = false;
		}
		else if(command.compare("insertEnd") == 0){
			string message1;
			getline(cin,message1);
			message1.pop_back();
			string parse = message1.substr(2, message1.length()-1);
			head = Project1::insertEnd(head,parse);
		}
		else if(command.compare("insert") == 0){
			string message1;
			string message2;
			cin >> message1;
			getline(cin,message2);
			message2.pop_back();
			string parse = message2.substr(2, message2.length()-1);
			int index = stoi(message1)-1;
			head = Project1::insert(head,index,parse);
		}
		else if(command.compare("print") == 0){
			Project1::printList(head);
		}
		else if(command.compare("edit") == 0){
			string message1;
			string message2;
			cin >> message1;
			getline(cin,message2);
			message2.pop_back();
			string parse = message2.substr(2, message2.length()-1);
			int index = stoi(message1)-1;
			head = Project1::editNode(head,index,parse);
		}
		else if(command.compare("delete") == 0){
			string message1;
			getline(cin,message1);
			int index = stoi(message1)-1;
			head = Project1::deleteNode(head, index);
		}
		else if(command.compare("search") == 0){
			string message1;
			getline(cin,message1);
			message1.pop_back();
			string parse = message1.substr(2, message1.length()-1);
			Project1::searchList(head,parse);
		}
      }	
 }
