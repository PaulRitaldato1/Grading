#include<iostream>
#include<string>
using namespace std;


//your linked list implementation here
class Node {
    public:
        string lyric;
        int lineNum;
        Node* next = NULL;
};
        //your line editor implementation here
Node* deleteValue(Node*, int);

//takes in node(s), command and input
void editor (Node* song, string command, string input){
    //makes sure iterations start at beginning of list
    Node* head = song;
    
    if(command == "insertEnd"){
        //cout << "insertEnd used" << endl;
        //initialize line number variable and cleans '"' off lyric input
        int num = 2;
        input.erase(0,2);
        input.erase(input.size()-1);
        
        //creates new node with new lyric
        Node* newLyric = new Node();
        newLyric->lyric = input;
        
        //fills in front of list if empty
        if (song->lyric == ""){
            song->lyric = input;
            song->lineNum = 1;

        }
        //adds new lyric to the end of non-empty list
        else{        
            while(true){
                if (song->next == NULL){
                    newLyric->lineNum = num;
                    song->next = newLyric;
                    break;

                }
                else if (song->next!=NULL){
                    num++;
                    song=song->next;
                }
            }
        }
        
    }
    else if(command == "print"){
        //fix of deletion issue
        if(head->next->lineNum == 1)
            head=head->next;
        //prints list with line number and lyric
        while (head != NULL){          
                cout << head->lineNum << " " <<  head->lyric << endl;
                head=head->next;           
        }
        
    }
    else if(command == "search"){        
        //cleans input and initailizes checker if input is found
        input.erase(0,2);
        input.erase(input.size()-1);
        bool found = false;
        
        //scans through each lyric of each node and determines if input is found
        while(song!=NULL){
            for(int j=0; j<input.size() ; j++){
                if(song->lyric.substr(j,input.size()) == input){
                    cout << song->lineNum << " " << song->lyric << endl;
                    found = true;
                    break;
                }
            }
            song=song->next;            
        }
        
        if(!found){
            cout << "not found" << endl;
        }
        
    }
    else if(command == "edit"){
        //converts number in string input to an int
        int number = stoi(input);
        
        //finds input's line number, cleans input, and replaces lyric
        while(true){
            if(number == song->lineNum){
                input.erase(0,4);
                input.erase(input.size()-1);
                song->lyric = input;
                break;
            }
            else{
                song=song->next;
            }
        }
        
    }
    else if(command == "delete"){
        //converts input number to int and calls deleteValue function
        int number = stoi(input);
        
        //calls deleteValue method
        deleteValue(song, number);
        
    }
    else if(command == "insert"){
        //initilizes important variables, converts number from input to int, cleans input, creates new node and fills it with input
        Node *curr = song;
        int number = stoi(input);
        input.erase(0,4);
        input.erase(input.size()-1);
        Node* newLyric = new Node();
        newLyric->lyric = input;

        //not used if given line number is greater than current amount of lines
        while (song!=NULL && number >= song->lineNum){

            if(number-1 == song->lineNum){
                //inserts to line not in beginning of list
                Node* nextNode = song->next;
                song->next = newLyric;
                newLyric->next = nextNode;
                break;
            }
            else if(number==1){
                //inserts line in beginning
                newLyric->next = song;
                head = newLyric;
                break;
            }
            else
                song=song->next;
            
        }
        
        int line = 1;        
        while(head!=NULL){
            head->lineNum = line++;
            head=head->next;
        }
        
    }
    
}


Node* deleteValue(Node* head, int number){
    Node* curr = head;
    Node* prev = head;
    Node* temp;
    //not used if given line number is greater than current amount of lines
    while(curr != NULL && number>=curr->lineNum){
        
        if(number == 1){
            //for beginning of list            
            temp = head;
            curr = curr->next;
            head = curr;
            delete(temp);
            
            break;
        }
        else if(curr->lineNum == number){
            if(curr->next != NULL) {
                // for middle of list
                prev->next = curr->next;
                temp = curr;
                curr = curr->next;
                delete(temp);
            }
            else {
                // for end of list
                temp = curr;
                prev->next = NULL;
                curr = NULL;
                delete(temp);
            }
        }
        else {            
            prev = curr;
            curr = curr->next;
        }
    }
    
    //fills in appropriate line numbers
    int line = 1;
    while(head!=NULL){
        head->lineNum = line++;
        head=head->next;
    }
    
    return head;
}

int main()
{
    //initilize important variables
    string command;
    string input;
    Node* song = new Node();
    
    //first command input
    cin >> command;
    
    //cycles though taking and following commands until that command is 'quit'
    while (command != "quit"){
        getline(cin, input);
        editor(song, command, input);
        cin >> command;
    }
    
    //your code to invoke line editor here
}