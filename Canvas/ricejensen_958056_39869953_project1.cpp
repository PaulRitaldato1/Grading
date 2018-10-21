#include <iostream>
#include <string>
using namespace std;

//the nodes of a linked list, with a string line that carries the line and a reference to the next Node in the list]
class Node{
	public:
	string line;
	Node* nextNode;
};


int main(){
	//intiializes a head and tail which are the same node in the beginning
	Node* head = new Node();
	Node* tail = new Node();
	tail=head;
	string input;
	//sizeoflist helps manage insertions and deletions
	int sizeOfList = 0;
	//get the line and quit if that is the input and print if thats the input
  while(input!="quit"){
	getline(cin, input);
	if(input=="quit")
		return 0;
	else if(input=="print"){
		//iterates through the nodes and prints their contents with the trackerNum
		Node* tracker = head;
		int trackerNum = 1;
		while(tracker!=NULL){
			cout<< trackerNum<<" " <<tracker->line<< "\n";
			tracker=tracker->nextNode;
			trackerNum++;
		}
	}
	else{
	//if the input is not "print" or "quit" parse and apply the code
	//parsetracker to keep track of each word
	int parsetracker = 0;
	string firstWord = "";
	string secWord = "";
	string thirdWord = "";
	//iterates through every character of the input
	for(auto x : input){
		if(x=='\"'){
		//ignores quotes - instructor was very unclear about improper input so I didn't handle it too much
		}
		//adds space to string that is in quotes and ignores otherwise - adds one to parsetracker to keep track of spaces
		else if(x==' '){
			if(parsetracker>=1 && (firstWord == "insertEnd" || firstWord == "search")){
				secWord=secWord+x;
			}
			else if(parsetracker>1){
					thirdWord=thirdWord+x;
			}
				parsetracker++; 
		}
		else if(parsetracker==0){
			//adds the character to firstWord if a space has not been encountered yet
			firstWord=firstWord+x;
		}
		else if(parsetracker==1 || firstWord == "insertEnd" || firstWord == "search"){
			//adds the character to secWord if a space has been encountered or if the firstWord is insertEnd or search
			secWord=secWord+x;
		}
		else{
			//adds the character to thirdword if the previous criteria havent been met
			thirdWord=thirdWord+x;
		}
	
	}

	//inserts a node at the index given in input
	if(firstWord == "insert"){
		//stoi converts secWord to an int, the try and catch resets the loop in secWord is not a number based string
		int indexPlace = 0;
		try{
			indexPlace = stoi(secWord);
		}
		catch(...){
			continue;
		}
		//creates the node to be inserted and initilizes its line variable
		Node* insertion = new Node();
		insertion->line=thirdWord;
		//if the index is 1 then it refers to the head of the list and the insert should happen there
		if(indexPlace == 1){
			if(sizeOfList>0)
				insertion->nextNode=head;
			head=insertion;
			sizeOfList++;
		}
		else if (indexPlace>sizeOfList+1)
		{
			//out of bounds
		}
		//if index at end then iterate to the end an insert the new node and set the tail reference equal to it
		else if(indexPlace==sizeOfList+1){
			Node* tracker = head;
			while(tracker->nextNode!=NULL){
				tracker=tracker->nextNode;
			}
			tracker->nextNode=insertion;
			tail=insertion;
			sizeOfList++;
		}
		else{
			//if the insert point is in the middle of the linked list then iterate to the index before the insertion and
			//set it as the next node and the insertions next node as the next node
		Node* tracker = head;
		int trackerNum = 1;
		while(tracker->nextNode!=NULL && trackerNum<indexPlace-1){
			tracker=tracker->nextNode;
			trackerNum++;
		}

			insertion->nextNode=tracker->nextNode;
			tracker->nextNode=insertion;
			sizeOfList++;
		}
		}

	else if(firstWord == "edit"){
				int indexPlace = 0;
		try{
			indexPlace = stoi(secWord);
		}
				catch(...){
			continue;
		}

		if(indexPlace>sizeOfList & indexPlace>1){
			//out of bounds
		}
		else if(indexPlace==1){
			//edits the head
			head->line=thirdWord;
		}
		else if(indexPlace==sizeOfList){
			//iterates to the end and edits
			Node* tracker = head;
			while(tracker->nextNode!=NULL){
				tracker=tracker->nextNode;
			}
			tracker->line=thirdWord;
		}
		else{
			//iterates to the edit index and edits the line
		Node* tracker = head;
		int trackerNum = 1;
		while(tracker->nextNode!=NULL & trackerNum<indexPlace-1){
			tracker=tracker->nextNode;
			trackerNum++;
		}
		
		if(indexPlace==1){
		head->line=thirdWord;
		}
		else{
		tracker=tracker->nextNode;
		tracker->line=thirdWord;
		}
		}
	}
	else if(firstWord == "insertEnd"){
		if(sizeOfList==0){
			//if head has no value then give it a value
			head->line=secWord;
			sizeOfList++;
		}
		else{
			//attatches to the tail and sets the inserted node as a tail
		Node* insertion = new Node();
		insertion->line=secWord;
		Node* tracker = head;
		tail->nextNode=insertion;
		tail = insertion;
		sizeOfList++;
	}
		/*if(sizeOfList==0){
		head->line=secWord;
		sizeOfList++;
		}
		else{
			while(tracker->nextNode!=NULL){
				tracker=tracker->nextNode;
			}
		tracker->nextNode=insertion;
		sizeOfList++;
		}*/
			}


	else if(firstWord == "delete"){
		int del;
		try{
			del = stoi(secWord);
		}
		catch(...){
			continue;
		}

		int trackerNum = 1;
		trackerNum++;
		Node* tracker = head;
		Node* afterTracker = head;
		//deletes the head and moves it on if there are multiple nodes in the list - otherwise gets rid of the head value and sets sizeoflist to 0
		if (del==1)
		{
			if(head->nextNode!=NULL){
				Node * deletion = head;
				head = head->nextNode;
				delete deletion;
				sizeOfList--;
			}
			else{
				head->line="";
				sizeOfList--;
			}
		}
		else if(del>sizeOfList){
			//out of bounds
		}
		else if(del==sizeOfList){
			//iterates to the end and deletes the tail and sets tail equal to the node before the previous tail
			bool begin = false;
			while(tracker->nextNode!=NULL){
				if(begin){
					afterTracker=tracker;
				}
				else{
					begin = true;
				}
				tracker=tracker->nextNode;
			}
			afterTracker->nextNode=NULL;
			delete tracker;
			sizeOfList--;
		}
		else{
			//iterates to the node to delete and links the nodes before and after then deletes the node from memory
		while(tracker->nextNode!=NULL & trackerNum<del){
			tracker=tracker->nextNode;
		}
		Node * deletion = tracker->nextNode; 
		tracker->nextNode=tracker->nextNode->nextNode;
		sizeOfList--;
		delete deletion;
	}
	}
	else if(firstWord == "search"){
		bool found1 = false;
		int trackerNum = 1;
		int found = -1;
		Node* tracker = head;
		//if line.find returns a value greater than -1 then secWord has been found in the line
		//prints out if found, sets the found1 bool to true
		found = tracker->line.find(secWord);
		if(found>-1){
			cout<< trackerNum << " " << tracker->line << "\n";
			found1 = true;
		}
		//reset found for future checks
		found = -1;
		//does the same operatoin as above in a loop untill the linked list ends
		while(tracker->nextNode!=NULL){
			tracker=tracker->nextNode;
			found = tracker->line.find(secWord);
			trackerNum++;
			if(found>-1){
			cout<< trackerNum << " " << tracker->line << "\n";
			found1 = true;
			}
			found = -1;
		}
		//if secWord was not found return false
		if(found1==false){
			cout<<"not found"<< "\n";
		}
		
	}
	}
  }
}