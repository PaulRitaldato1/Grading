using namespace std;
#include <iostream>
#include <string>
#include "linkededitor.h"

template <class T> void LinkedList<T>::insertEnd(T value){
	if(head==NULL){
		head = new Node<T>();
		head->data = value;
		tail = head;
		return;
	}
	tail->next = new Node<T>();
	tail->next->data = value;
	tail = tail->next;
}

template <class T> void LinkedList<T>::insert(int index,T value){
	if(index == 1){
		Node <T> * newNode = new Node<T>();
		newNode->data = value;
		newNode->next = head;
		head = newNode;
		return;
	}
	Node <T> * current = head;
	for(int i = 1; i < index - 1; ++i){ // For the insertion loop, we are fine landing on current = NULL, so we check BEFORE the loop so that if the index is too high, we don't
		if(current->next == NULL)       // go PAST current = null.
			return;
		current = current->next;
	}
	Node <T> * newNode = new Node<T>();
	newNode->data = value;
	newNode->next = current->next;
	current->next = newNode;
	if(current == tail)
		tail = newNode;
}

template <class T> void LinkedList<T>::remove(int index){
	Node <T> * current = head;
	if(current == NULL)     					 // If index given is anything, but the list is empty, we have to check here so delete 1 doesn't break the code.
		return;
	if(index == 1){
		head = head->next;
		delete current;
		current = NULL;
		return;
	}
	if(current->next == NULL) 					 // If index is 2, loop won't run, so have to check here if the size is 1, so delete 2 doesn't break the code.
		return;
	for(int i = 1; i < index - 1; ++i){			 // For the deletion loop here, we don't want to have current = NULL. We may be able to insert on NULL but we can't delete on it,
		current = current->next;				 // hence, we check for NULL after the indexing.
		if(current->next == NULL)
			return;
	}

	Node <T> * temp = current->next;
	current->next = temp->next;
	if(temp == tail)
		tail = current;
	delete temp;
	temp = NULL;
}

template <class T> void LinkedList<T>::print(){
	Node <T> * temp = head;
	int count = 1;
	while(temp != NULL){
		cout << count << " " << temp->data << endl;
		temp = temp->next;
		count++;
	}
}

template <class T> void LinkedList<T>::edit(int index, T value){
	Node <T> * temp = head;
	if(temp == NULL) 							// Same logic as delete function for handling empty linked list.
		return;
	for(int i = 0; i < index - 1; i++){
		if(temp->next == NULL)
			return;
		temp = temp->next;
	}
	temp->data = value;
}

template <class T> void LinkedList<T>::find(string value){
	Node <T> * temp = head;
	bool found = false;
	int count = 1;
	while(temp != NULL){
		if(temp->data.find(value) != string::npos){
			cout << count << " " << temp->data << endl;
			found = true;
		}
		if(temp->next == NULL)
			break;
		temp = temp->next;
		count++;
	}
	if(!found)
		cout << "not found" << endl;
}

string stringAfterSpace(string word){
	for(unsigned int i = 0; i < word.size(); i++) // Finds the string input after a space
		if (isspace(word[i]))
			return word.substr(i+1);
	return "";
}

string stringBeforeSpace(string word){
    for(unsigned int i = 0; i < word.size(); i++) // Finds the string input before a space
        if (isspace(word[i]))
        	return word.substr(0,i);
    return word;
}

string removeQuotes(string word){
	return word.substr(1,word.size()-2);		// Simple algorithm to remove quotes to make inputs easier
}

int toInt(string numStr){
	return numStr[0] - '0';
}

int main() {
	LinkedList <string> * linkedList = new LinkedList<string>();
	int index = 0;
	string userInputLine = "", input = "", command = "";
	bool running = true;

	while(running){

		getline (cin, userInputLine);

		if(userInputLine.size() > 0){
			input = stringAfterSpace(userInputLine);
			command = stringBeforeSpace(userInputLine);

			if(command == "insertEnd"){
				linkedList->insertEnd(removeQuotes(input));
			}
			else if(command == "insert"){
				index = toInt(stringBeforeSpace(input));
				input = stringAfterSpace(input);
				linkedList->insert(index, removeQuotes(input));
			}
			else if(command == "search"){
				linkedList->find(removeQuotes(input));
			}
			else if(command == "delete"){
				index = toInt(stringBeforeSpace(input));
				linkedList->remove(index);
			}
			else if(command == "print"){
				linkedList->print();
			}
			else if(command == "edit"){
				index = toInt(stringBeforeSpace(input));
				input = stringAfterSpace(input);
				linkedList->edit(index, removeQuotes(input));
			}
			else if(command == "quit"){
				running = false;
			}
		}
	}
	return 0;
}






