
//I know this is bad practice, but I was too far to go back and at std:: to all of my code.
using namespace std;
#include <string>
#include <iostream>

class Node {
    public:
        string value;
        Node* next = NULL;
};





//This method will run the entire program


//This will allow the user to insert a node at the end of the list
Node* insertEnd(Node* head, string str){
	Node* temp = new Node;
    temp->value = str;
    temp ->next = NULL;
	Node* prv = head;
    if(head == NULL){
        temp ->next = head;
        head=temp;

        delete prv;
        return head;
    }
	else{
		while(prv->next != NULL){
			prv = prv->next;
		}
		prv->next = temp;
	}
    //delete temp;
    return head;

}


//This wil allow the user to insert a node anywhere in the list
Node* insert(Node* head, int local, string str){
	Node* temp = new Node;
	temp->value = str;
	Node* prv = head;
	Node* nxt = head;
	
	int tempint = local-1;
	
	
	if(tempint == 0){
        temp->next = head;
        return temp;
        delete temp;
        delete prv;
        delete nxt;
    }
	for(int i=0; i<tempint-1;i++){
		prv = prv->next;
		nxt = nxt->next;
	}
	
	if(nxt->next != NULL){
		temp->next = nxt->next;
	}
	else{
		temp->next = nullptr;	
	}
	
	prv->next = temp;
	
	return head;
	delete temp;
	delete prv;
	delete nxt;

}


Node* del(Node* head, int local){
	Node* prv = head;
	Node* nxt = head;
	
	int tempint=local-1;
	
	if(tempint == 0){
        if(prv ->next != NULL){
		    prv = prv->next;
            head = prv;
        }
        else{
            head = NULL;    
        }
            
        //delete prv;
		delete nxt;
		return head;
	
	}

	for(int i = 0; i<tempint-1;i++){
		prv = prv->next;
		nxt = nxt->next;
	}
	
	if(nxt->next->next){
		prv->next = nxt->next->next;
	}
	else{
		prv->next = nullptr;
	}
	
    return head;
	delete(prv);
	delete(nxt);
	
}

//This will allow the user to override an existing node in the list
Node* edit(Node* head, string local, string str){
	Node* temp = new Node;
    temp -> value = str;
	int tempint = atoi(local.c_str());
    tempint--;
	Node* prv = head;
	Node* nxt = head;
    
    if(tempint == 0){
    	if(prv -> next != NULL){
		    temp-> next = prv->next;
            head = temp;
        }
        else{
            head = temp;    
        }
        return head;
        delete prv;
		delete nxt;    	 	
    }
        
	for(int i = 0; i<tempint-1;i++){
		prv = prv->next;
		nxt = nxt->next;
		
		if(prv == NULL){
			cout<<"Text does not exist in this list"<<endl;
			delete(temp);
			delete(prv);
			delete(nxt);
			return head;
		}
	}
	
    if(nxt->next->next == NULL){
		temp->next = nullptr;
	}
	else{
        temp->next = nxt ->next->next;
	}
    
	prv->next = temp;

	//delete(temp);
	//delete(prv);
	//delete(nxt);
	return head;
	
}
    
//This will print the entire list
void print(Node* head){ 
	Node* temp = head;
	int counter = 1;
	while(temp != NULL){
		cout << counter << " " << temp->value << endl;
		temp = temp->next;
        counter++;
	}
	delete temp;	
}

//This will search for a specific 
void search(Node* head, string str){
	Node* temp = head;
	int counter = 1;
	string strTemp;
	bool found = false;
	
	while(temp != NULL){
		strTemp = temp->value;
		if(strTemp.find(str) != string::npos){
			cout << counter << " " <<strTemp<<endl;
			found = true;
		}
		counter++;
		temp = temp->next;
        
	}
	if(!found)
		cout<<"not found"<<endl;
}    
    
int main(){
    Node* head = new Node;
    head = NULL;
    int countit = 0;
	while(true){
		string inpt;	
		getline(cin,inpt);

		if(inpt.substr(0,9) == "insertEnd"){
			head = insertEnd(head, inpt.substr(11,inpt.size()-12));
			countit++;
			continue;
		}
		else if(inpt.substr(0,6) == "insert"){
			string loc = inpt.substr(7,8);
			int tempint = atoi(loc.c_str());

			
			if(tempint == countit+1){
				head = insertEnd(head, inpt.substr(10,inpt.size()-11));
				countit++;
				continue;
			}
			else if(tempint > countit)
					continue; 
			head = insert(head, tempint, inpt.substr(10,inpt.size()-11));
			countit++;
			continue;
		}
		else if(inpt.substr(0,6) == "delete"){
			string loc = inpt.substr(7,8);
			int tempint = atoi(loc.c_str());
			if(tempint > countit)
				continue;
			head = del(head, tempint);
			countit--;
			continue;
		}
		else if(inpt.substr(0,4) == "edit"){
			string loc = inpt.substr(5,6);
			head = edit(head, loc, inpt.substr(8,inpt.size()-9));
			continue;
		}
		else if(inpt.substr(0,5) == "print"){
			print(head);
			continue;
		}
		else if(inpt.substr(0,6) == "search"){
			search(head, inpt.substr(8,inpt.size()-9));
			continue;
		}
		else if(inpt.substr(0,4) == "quit"){
			break;
		}
		else{
			cout<<"That is not a valid command"<<endl;
			continue;
		}
	break;
    }
	
	//cout << "Thank you for using this Program, have a pleasant day" << endl;
	return 0;

} 
