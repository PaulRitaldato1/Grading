using namespace std;

#include <string>
#include <iostream>


class Node {
		public:
        string message;
        Node* next = NULL;
};





class project1{
public:	
static Node* insert(Node* head, int index, string valueInput){
		
    Node *pre=new Node;
    Node *cur=new Node;
    Node *temp=new Node;
    cur=head;
    
    if (index == 0){
          temp->message=valueInput;
          temp->next = head;
        return temp;
    }      
    
    
    for(int i=1;i<=index;i++)
    {
      if (!cur){
          return NULL;
      }
      pre=cur;
      cur=cur->next;
    }
    temp->message=valueInput;
    pre->next=temp;	
    temp->next=cur;
    return head; 
}

static Node* insertEnd(Node* head,string valueInput){
    Node* cur = head;
    int counter = 0;
    for (int i = 0; cur; i++){
        cur = cur->next;
        counter ++;
    }
	
    return insert(head,counter -1,valueInput);
}

static Node* deleteNode(Node* head, int index){
    Node* previous = NULL;
    Node* current = head;
    
    if (index == 0){
        return head->next;
    }
    
    for (int i =0; i <index; i ++){
        previous = current;
        current = current->next;
    }
    
    previous->next = current->next;
    
    delete current;
    
    return head;
}

static Node* editNode(Node* head, int index, string message){
    
    Node* current = head;
    
    for (int i =0; i < index; i ++){
        current = current->next;
    }
    
    current->message = message;
    return head;
}

static void searchList(Node* head, string x){
	
	Node* cur = head;
	int lineNum = 0;
	
	bool found = false;
	
	
	
	while (cur->next){
		
		if (cur->message.find(x) != string::npos){
			cout << lineNum + 1 << " " <<cur->message << "\n";
			found = true;
		}
		cur = cur->next;
		lineNum++;
		
	}
	
	if(!found){
		cout << "not found" << "\n";
	}
	
}
static void printList(Node* head){
    Node* current = head;
	int lineNum = 1;
    while (current->next){
		
        cout << lineNum << " " << current->message << "\n";
		current = current->next;
		lineNum ++;
    }
}
};

int main()
{
	bool valid = true;
	Node* head;
	
	while(valid){
		string command;
		cin >> command;
		
		
		
		if (command.find("insertEnd")==0){
			string message;
			getline(cin,message);
			message.pop_back();
			message = message.substr(2,message.length()-1);
			
			head = project1::insertEnd(head,message);
			
		}
		else if (command.find("insert") == 0){
			string index;
			
			cin >> index;
			
			string message;			
			getline(cin,message);
			message.pop_back();
			message = message.substr(2,message.length()-1);
			
			int i = stoi(index)-1;
			head = project1::insert(head,i,message);
		}
		else if (command.find("quit") == 0){
			
			valid = false;
		}
		else if (command.find("print") == 0){
			project1::printList(head);
		}
		else if (command.find("delete") == 0){
			string index;
			
			cin >> index;
			int i = stoi(index)-1;
			head = project1::deleteNode(head,i);
		}
		else if (command.find("edit") == 0){
			string index;			
			cin >> index;
			int i = stoi(index) -1;
			
			string message;			
			getline(cin,message);
			message.pop_back();
			message = message.substr(2,message.length()-1);
			
			head = project1::editNode(head,i,message);			
			
		}else if (command.find("search")){
			string message;			
			getline(cin,message);
			message.pop_back();
			message = message.substr(2,message.length()-1);
			
			project1::searchList(head,message);
		}
	}
}

