#include <cstddef>
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
struct Node {
    std::string value;
    Node* next = NULL;
};
class linklist{
    private:
        Node *head,*tail,*temp, *tempp;
    public:
        linklist(){
            head = NULL;
            tail = NULL;
            temp = NULL;
            tempp= NULL;
        }
		~linklist(){
			Node* toDelete = head;
			while(toDelete!=NULL){
				Node* next = toDelete->next;
				delete toDelete;
				toDelete = next;
			}
		}
        int listSize(){
            if(head==NULL){
                return 0;}
            temp = head;
            int i = 1;
            while(temp != tail){
                temp = temp->next;
            i++;}
            return i;}		
		void insertEnd(std::string s){
			 if(!(s.size()>80)){
			 
				Node* nsrt = new Node();
    			nsrt->value = s;
     		 	if(head!=NULL){
   					tail->next = nsrt;
                	tail = nsrt;
       		 	}else{
     			   head = nsrt;
      			  tail = nsrt;}
			  }
        }
        void insertIndex(int indx, std::string s){
           	if(!(s.size()>80)){
	            if(indx>this->listSize()+1){
	            }
	            else if(!(head == NULL)){
	                Node* nsrt = new Node();
	                if(indx != 1){
	                    temp = head->next;
	                    tempp= head;
	                    for(int i = 2; i<indx && temp!=NULL ; i++){
	                        tempp=temp;
	                        temp = temp->next; 
	                    }
	                    tempp->next = nsrt;
	                    nsrt->next= temp;
	                    if(temp==NULL){
	                        tail = nsrt;}
	                }else{
	                    nsrt->next = head;
	                    head = nsrt;}
	                 nsrt->value = s; 
                
	            }else{
	                Node* nsrt = new Node();
	                head = nsrt;
	                tail = nsrt;
	                nsrt->value = s; 
	            }
			}     
        }
		void editIndex(int indx, std::string s){
			if(!(this->listSize() == 0)&&(!(indx>this->listSize()))){
				temp = head;
				for(int i = 1;(i<indx)&&(temp!=NULL);i++){
					temp = temp->next;	
				}
				if(!(temp==NULL)&&(!(temp->value.size()+s.size()>80))){
					
					temp->value = s;
				}
			}
			
		}
        void delIndex(int index){
			if(head==NULL){}
            else if(index == 1){
                temp = head->next;
				delete head;
				head = temp;    
            }else{
                temp = head->next;
                tempp = head;
                for(int i = 2; i<index && temp!=NULL ; i++){
                    tempp=temp;
                    temp = temp->next;   
				}
                if(temp!=NULL){
                tempp->next=temp->next;
				delete temp;}
           	}
		}
		void findIndex(std::string s){
			temp = head;
			int i = 0;
			int j = 0;
			while(temp!=NULL){
				if (temp->value.find(s) != std::string::npos) {
					std::cout<<i+1<<" "<<temp->value<<std::endl;
					j++;
				}
				temp = temp->next;
				i++;
			}
			if(j==0){
				std::cout<<"not found"<<std::endl;
			}
			
				
		}
		void printList(){
            if(head!=NULL){
                temp = head;
                int i = 0;
                while(temp!=NULL){
                    std::cout<<++i<< " "<<temp->value<<std::endl;
                    temp = temp->next;
                }
            }
        }
		
    
};

int main(){
    linklist myList;
	std::string input;
	std::string command;
	std::string arguments[2] = {"",""};
	int index;
    while(true){
		std::getline(std::cin,input);
		command = "";
		arguments[0] = "";arguments[1]= "";	
		for(int i =0; i<input.length();i++){
			if(input[i]== ' '){
				index = i;
				break;
			}
			command+=input[i];
		}
		
		if(command=="insert" || command == "edit"){		
			for(int j =index+1; j<input.length();j++){
				if(input[j]== ' '){
					index = j;
					break;
				}
				arguments[0]+=input[j];
			}
            if(input.length() > index+2){
				if(input[index+1] == '\"'&&input[input.length()-1]=='"'){
					for(int j =index+2; j<input.length();j++){
						if(input[j]== '\"'){
							break;
						}
						arguments[1]+=input[j];
					}
					if(!arguments[0].empty() && std::find_if(arguments[0].begin(), arguments[0].end(), [](char c) { return !std::isdigit(c); }) == arguments[0].end()){
						if(command =="insert"){
							myList.insertIndex(stoi(arguments[0]),arguments[1]);
						}else if(command =="edit"){
							myList.editIndex(stoi(arguments[0]),arguments[1]);
						}
					
					}
				}	
			}
		}
		else if(command=="print"){
			if(command == input){
				myList.printList();
			}
		}else if(command == "insertEnd"){
			if(input.length() > index+2){
				if(input[index+1] == '\"'&&input[input.length()-1]=='"'){

					for(int j =index+2; j<input.length();j++){
						if(input[j]== '\"'){
							break;
						}
						arguments[1]+=input[j];
					}
					myList.insertEnd(arguments[1]);
					
				}
			}	
			//put my fucken insert end code here kidd
		}else if(command=="quit"){
			break;
		}
		else if(command =="delete"){
			for(int j =index+1; j<input.length();j++){
				if(input[j]== ' '){
					index = j;
					break;
				}
				arguments[0]+=input[j];
			}
			if(!arguments[0].empty() && std::find_if(arguments[0].begin(), arguments[0].end(), [](char c) { return !std::isdigit(c); }) == arguments[0].end()){
				myList.delIndex(stoi(arguments[0]));
			}
		}
		else if(command == "search"){
            if(input.length() > index+2){
				if(input[index+1] == '\"'&&input[input.length()-1]=='"'){
					for(int j =index+2; j<input.length();j++){
						if(input[j]== '\"'){
							break;
						}
						arguments[1]+=input[j];
					}
					myList.findIndex(arguments[1]);
				}
			}	
			
		}
	}
	return 0;	
}

	
    
   
