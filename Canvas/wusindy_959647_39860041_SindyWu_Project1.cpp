#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
//your linked list implementation here

        //your line editor implementation here
struct Node {
	string val;
	Node* next = NULL;

};


class List {
	Node* head;

	public:
	List() {
		head = NULL;
	}

	void insertEnd(string line) {
		Node* current = new Node;
		current = head;
		Node* temp = new Node;
		temp->val = line;
		if(!head) {
			head = temp;
			return;
		}
		for (int i = 0; current->next != NULL; i++) {
		
	                current = current->next;
	            
	                
	        }
	        current->next = temp;
		return;
	}

	void insertN(int index, string line) {
		Node* current = new Node;
	    Node* previous = new Node;
	    Node* temp = new Node;
	    temp->val = line;
	    current = head;
	    if (index-1 == 0) {
	        temp->next = current;
	        head = temp;
	        return;
	    }
	    for (int i = 0; i < index -1; i++) {
	        if (current != NULL) {
	            previous = current;
	            if (current->next != NULL)
	                current = current->next;
	            else
	                current = NULL;
	        }
	        else 
	            return;
	    }
	    previous->next = temp;
	    temp->next = current;
	    return;
	}

	void deleteN(int index) {
		Node* current = new Node;
		Node* previous = new Node;
		if (head == NULL)
			return;
		current = head;
		
		if (index-1 == 0) {
			head = head->next;
			delete current;
			return;
		}
		for (int i = 0; i < index - 1; i++) {
			if (current != NULL) {
	            if (current->next != NULL) {
                    previous = current;
	                current = current->next;
	                
                }
                else
                    if (index > i)
                        return;
	        }
            
		}
		previous->next = current->next;
		delete current;
		return; 
	}

	void editN(int index, string line) {
		Node* current = new Node;
		if (head == NULL)
			return;
		current = head;
		for (int i = 0; i < index - 1; i++) {
			if (current != NULL) {
	            if (current->next != NULL)
	                current = current->next;
	            else
                    if (index > i)
                        return;
	        } 
		}
		current->val = line;
		return;
	}

	//contains given text -- partial text?
	void search(string line) {
        bool found = false;
		Node* current = new Node;
		if (head == NULL)
			return;
		current = head;
		int i = 1;
		while (current != NULL) {
			if (current->val.find(line)!= string::npos) {
				cout << i << " " << current->val << endl;
                found = true;
			}
				if (current->next != NULL)
					current = current->next;
				else
					current = NULL;
				i++;
			
			
		}
        if(!found)
		    cout << "not found" << endl;
		return;
	}

	void print() {
		Node* current = new Node;
		if(head==NULL)
			return;
		current = head;
		int i = 1;
		while (current != NULL) {
			cout << i << " " << current->val << endl;
			if (current->next != NULL){
			current = current->next; }
			else {
			current = NULL;
			}
			i++;
		}
		return;
	}
};

int main()
{
    string command = "";
    string s;
    List lineEditor;
    vector<string> result; //https://w...content-available-to-author-only...a.com/How-do-I-split-a-string-by-space-into-an-array-in-c++
	do {
		/*cout << "What would you like to do? You can:" << endl;
		cout << "insertEnd 'text'" << endl;
		cout << "insert n 'text'" << endl;
		cout << "delete n" << endl;
		cout << "edit n 'text'" << endl;
		cout << "print" << endl;
		cout << "search 'text'" << endl;
		cout << "quit" << endl;*/
		getline(cin, command);
		//parse command
size_t first = 0;
		if (command.length() < 6)
			result.push_back(command);
		for( size_t last=0; last<command.length(); last++){ //https://stackoverflow.com/questions/18675364/c-tokenize-a-string-with-spaces-and-quotes

		    char c = command[last];
		    if( c == ' ' ){
		        result.push_back(command.substr(first,last-first));
		        first = last + 1;
		    }else if(c == '\"' ){
		        last++;
		        first = last;
		        while( command[last] != '\"' ){ last++; }
		        result.push_back(command.substr(first,last-first));
		        
		    }else if(last == command.length() - 1){
		    	result.push_back(command.substr(first,last-first+1));
		        //cout << c;
		    }
		}
		/*for (int i = 0; i < result.size(); i++)
			cout << result[i] << endl;*/
			
		 if (result[0] == "insertEnd")
	    	lineEditor.insertEnd(result[1]);
	    else if (result[0] == "insert")
	    	lineEditor.insertN(stoi(result[1]), result[2]);
	    else if (result[0] == "delete")
	    	lineEditor.deleteN(stoi(result[1]));
	    else if (result[0] == "edit")
	    	lineEditor.editN(stoi(result[1]), result[2]);
	    else if (result[0] == "print")
	    	lineEditor.print();
	    else if (result[0] == "search")
	    	lineEditor.search(result[1]);
	    	
	    	
		result.clear();
		result.shrink_to_fit();
		

	} while (command != "quit");
	return 0;
    //your code to invoke line editor here
}

