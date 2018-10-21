#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Node
{
    public:
    Node* next;
    std::string line;
    Node(){
        next = NULL;
        line = "";
    }
};

//Users can insert, delete, search, or modify lines in the document.  They can print the entire document.
class LinkedList{
	private:
		Node *head;
		int size;
	public:
		LinkedList();
		int getSize();
		void insertEnd(std::string input);
        void insert(std::string input, int index);
		void remove(int index);
        void edit(std::string input, int index);
		void print();
		void search(std::string value);
};

LinkedList::LinkedList(){
	head = NULL;
	size = 0;
}

int LinkedList::getSize(){
	return size;
}

void LinkedList::insertEnd(std::string input){
    std::string input2 = "";
    if (input.size()<=0){
        return;
    }
    //if input is greater than 80 chars
    if (input.size() > 80){
        input2 = input.substr(80, input.size());
        input = input.substr(0, 80);
        //std::cout<<input2;
    }

    //if linked list is empty
	if (head==NULL){
		head=new Node();
		head->line=input;
		size++;
		return;
	}

	Node *temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next = new Node();
	temp->next->line = input;
    size++;

    insertEnd(input2);
}

void LinkedList::insert(std::string input, int index){
    index--; //to make the index 0-based

    std::string input2 = "";
    if (input.size()<=0){
        return;
    }
    //if input is greater than 80 chars
    if (input.size() > 80){
        input2 = input.substr(80, input.size());
        input = input.substr(0, 80);
    }

    Node* temp = head;
    if (index == 0){
        Node* newpt = new Node();
        newpt->line = input;
        newpt->next = temp;
        head = newpt;
        return;
    }

    for (int i=0; i<index-1; i++){
        if (temp == NULL){
            //std::cout<<"Invalid index. "<<std::endl;
            return;
        }
        temp = temp->next;
    }
    if (temp == NULL){
        //std::cout<<"Invalid index. "<<std::endl;
        return;
    }
    Node* temp2 = temp->next;
    temp->next = new Node();
    temp = temp->next;
    temp->line = input;
    temp->next = temp2;

    insert(input2, index+2);
}

void LinkedList::remove(int index){
    index--; //makes index 0-based

    //nothing to remove
	if (head==NULL){
        //std::cout<<"The document is empty."<<std::endl;
		return;
	}

	//if removing the first element
	Node *temp=head;
	if (index==0){
		head=head->next;
		delete temp;
		return;
	}

	Node *previous;
	for (int i=0; i<index; i++){
		//if the index is out of bound
		if (temp->next==NULL){
            //
            //std::cout<<"Invalid index."<<std::endl;
			return;
		}
		previous=temp;
		temp=temp->next;
	}

	previous->next=temp->next;
	delete temp;
}

void LinkedList::edit(std::string input, int index){
    index--; //makes index 0-based

	//if document is empty
	if (head==NULL){
        //std::cout<<"The document is empty."<<std::endl;
		return;
	}

    std::string input2 = "";
    //if length of input is greater than 80 characters
    if (input.size() > 80){
        input2 = input.substr(80, input.size());
        input = input.substr(0, 80);
    }

	//find the element to change
	Node *temp=head;
	for (int i=0; i<index; i++){
		//if the index is out of bound
		if (temp->next==NULL){
            //std::cout<<"Invalid index."<<std::endl;
			return;
		}
		temp=temp->next;
	}

	//change the element
	temp->line=input;

    insert(input2, index+2); //will only make a change if the input is too long (>80)
}

//traverse the linked list
void LinkedList::print(){
	if (head==NULL){
		//std::cout<<"N/A"<<std::endl;
		return;
	}
	Node *temp=head;
	int counter=1; //for formatting the printing
	while (temp!=NULL){
		std::cout<<counter<<" "<<temp->line<<std::endl;
		counter++;
		temp=temp->next;
	}
}

//no return value since only printing is required
void LinkedList::search(std::string input){
	
    //if linked list is empty
	if (head==NULL){
        //std::cout<<"Not found."<<std::endl;
		return;
	}

	//search for the element
	Node *temp=head;
	int index=0;
    bool found = false;
	while (temp!=NULL){
		if (temp->line.find(input) != std::string::npos){
            std::cout<<index+1<<" "+temp->line<<std::endl;
            found = true;
		}
		index++;
		temp=temp->next;
	}
    if (!found){
        std::cout<<"not found"<<std::endl;
    }
	return;
}

//for trimming without boost library
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

bool isSurroundedByQuotes(std::string line){
    if (line[0] != '\"' || line[line.length()-1] != '\"'){
        return false;
    }
    return true;
}

bool process(std::string command, LinkedList* list){
    //cin does not take in spaces by default!!
    if (command == "quit"){
        return false;
    }
    else if (command == "insertEnd"){
        std::string text;
        std::getline(std::cin, text); 
        //boost::trim_if(text, &isSpaceOrQuote);   //trim off spaces and quotes
        text = trim(text);
        //check if the input format is correct
        if (isSurroundedByQuotes(text)){
            text = text.substr(1,text.length()-2);
        }
        else{
            return true;
        }
        list->insertEnd(text);
        return true;
    }
    else if (command == "insert"){
        int line_num;
        std::cin >> line_num; 
        if (std::cin.fail()){
            //std::cout<<"Invalid line number. It needs to be an integer."<<std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return true;
        }
        std::string text;
        std::getline(std::cin, text); 
        //boost::trim_if(text, &isSpaceOrQuote);   //trim off spaces and quotes
        text = trim(text);
        //check if the input format is correct
        if (isSurroundedByQuotes(text)){
            text = text.substr(1,text.length()-2);
        }
        else{
            return true;
        }
        list->insert(text, line_num);
        return true;
    }
    else if (command == "delete"){
        int line_num;
        std::cin >> line_num;
        if (std::cin.fail()){
            //std::cout<<"Invalid line number. It needs to be an integer."<<std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return true;
        }
        list->remove(line_num);
        return true;
    }
    else if (command == "edit"){
        int line_num;
        std::cin >> line_num; 
        if (std::cin.fail()){
            //std::cout<<"Invalid line number. It needs to be an integer."<<std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return true;
        }
        std::string text;
        std::getline(std::cin, text); 
        //boost::trim_if(text, &isSpaceOrQuote);   //trim off spaces and quotes
        text=trim(text);
        //check if the input format is correct
        if (isSurroundedByQuotes(text)){
            text = text.substr(1,text.length()-2);
        }
        else{
            return true;
        }
        list->edit(text, line_num);
        return true;
    }
    else if (command == "print"){
        list->print();
        return true;
    }
    else if (command == "search"){
        std::string text;
        std::getline(std::cin, text); 
        //boost::trim_if(text, &isSpaceOrQuote);   //trim off spaces and quotes
        text=trim(text);
        //check if the input format is correct
        if (isSurroundedByQuotes(text)){
            text = text.substr(1,text.length()-2);
        }
        else{
            return true;
        }

        list->search(text);
        return true;
    }
    else{
        //std::cout<<"Your command is incorrect."<<std::endl;
    }
    return true;
}

int main(){
    LinkedList document = LinkedList();
    std::string user_command;
    bool flag = true;
    while (flag==true){
        std::cin>>user_command;
        flag = process(user_command, &document);
    }
    return 0;
}