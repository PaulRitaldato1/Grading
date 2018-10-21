#include <string>
#include <iostream>

using namespace std;

struct Node 
{
    string sentence;
    Node* next;

    Node() {
        sentence = "";
        next = NULL;
    }

};

class LinkedList
/**
 *  In here nodes are indexed from [0-n), so if someone enters a 1 (actual position) we
 *  will subtract one. The length though is counted from [1-n). Seemed more official.
 * 
 *  The linked list is normal, not doubly, so nodes link to eachother from head -> tail but
 *  not the other way. I chose this because it made everything more consistent and easy to
 *  read, and made the nodes less complicated to re-attach. 
 */
{
    private:
        Node *headNode;
        int listLength;

    public:

        LinkedList() {
            headNode = new Node;
            listLength = 0;
        }

        int getListLength() {
            return listLength;
        }        
        
        void insertNode(string insert, int pos) 
        {
            if (pos < 0) {
                return;
            }
            Node* addedNode = new Node;
            addedNode->sentence = insert;
            if(pos == 0) { //if this is a front insert
                if(listLength == 0) { //if list is empty
                    headNode = addedNode;
                }
                else { //if list is not empty
                    addedNode->next = headNode;
                    headNode = addedNode;
                }
                listLength++; //increment list length
            }
            else if(pos < listLength) { //iterator is required for insert
                Node* prevFinder = headNode;

                for(int i = 0; i < pos - 1; i++) {
                    prevFinder = prevFinder->next;
                }

                Node* posFinder = prevFinder->next;

                prevFinder->next = addedNode;
                addedNode->next = posFinder;
                listLength++; //increment list length
            }
            else if(pos == listLength) { //insert at end of list

                Node* posFinder = headNode;

                while(posFinder->next != NULL) {
                    posFinder = posFinder->next;
                }

                posFinder->next = addedNode;

                listLength++; //increment list length
            }
            else {}
        }

        void deleteNode(int pos) 
        {
            if(pos < listLength) { //if pos is within bounds
                if (pos == 0) { //if deleting first entry
                    if (headNode->next == NULL) { //if its the only thing
                        headNode->sentence = "";
                    }
                    else {
                        Node* temp = headNode->next;
                        headNode = temp;
                    }
                }
                else if (pos == listLength - 1) { //if its the last thing
                    Node* iterator = headNode;
                    Node* deleter = new Node;
                    deleter->next = iterator;
                    while(iterator->next != NULL) {
                        iterator = iterator->next;
                        deleter = deleter->next;
                    }
                    
                    deleter->next = NULL;
                    delete iterator;
                }
                else {//it must be in the middle
                    Node* iterator = headNode;
                    
                    for(int i = 0; i < pos - 1; i++) {
                        iterator = iterator->next;
                    }

                    Node* newNext = iterator->next;
                    newNext = newNext->next;
                    delete iterator->next;
                    iterator->next = newNext;
                } 
                listLength--;
            }
            else {}
        }

        void replaceNode(string s, int pos) 
        {
            if (pos < 0) {
                return;
            }

            if (pos < listLength){ //if pos is within bounds

                Node* iterator = headNode;

                for(int i = 0; i < pos; i++) {
                    iterator = iterator->next;
                }

                iterator->sentence = s;
                
            }
            else { }
        }

        void retrieveNode(string findIt) 
        {
            Node* iterator = headNode;
            
            int numb = 1;
            bool found = false;

            while (iterator->next != NULL) {
                if(iterator->sentence.find(findIt) != string::npos){
                    cout << numb<< " " << iterator->sentence + "\n";
                    found = true;
                }
                iterator = iterator->next;
                numb++;
            }

            if(iterator->sentence.find(findIt) != string::npos){
                cout << numb << " " << iterator->sentence + "\n";
                found = true;
            }
            if(!found) { cout << "not found\n";}
        }

        void printList() 
        {
            Node* iterator = headNode;
            int counter = 1;

            while(iterator->next != NULL) {
                cout << counter << " " + iterator->sentence + "\n";
                counter++;
                iterator = iterator->next;
                
            }
            cout << counter << " " + iterator->sentence + "\n";
        }

};

string giveString(string parseThis) { //this will find the quotes and return the input
    if(parseThis.find_first_of("\"") != string::npos && 
       parseThis.find_first_of("\"") != parseThis.find_last_of("\"")){

        string returnThis = parseThis.substr(parseThis.find_first_of("\"") + 1, parseThis.find_last_of("\"") - parseThis.find_first_of("\"") - 1);
        return returnThis;    
    }
    else {
        return "#*#"; //this is a secret error message, I hope noone tries entering this
    }
}

int main() 
{
    LinkedList texts = LinkedList();
    string input = "";
    int pos = 0;
    string convert = "";
    

    while(input.compare("quit") != 0) {
        getline(cin, input);
        
        if (input.substr(0, 10).compare("insertEnd ") == 0) {
            input.erase(0,10);
            texts.insertNode(giveString(input), texts.getListLength());
        }
        else if (input.substr(0, 7).compare("insert ") == 0) {
            input.erase(0,7);

            string sentence = giveString(input);
            if (sentence.compare("#*#") != 0) {
                input.erase(input.find(sentence) - 2, sentence.length() + 2);
                try {
                    pos = stoi (input);
                    texts.insertNode(sentence, pos - 1);
                }
                catch (exception e) {
                    cout << "it would appear you have used incorrect syntax";
                }
            }
            else { cout << "Please enter valid syntax \n";}
        }
        else if (input.substr(0, 7).compare("delete ") == 0) {
            input.erase(0,7);
            try {
                pos = stoi (input);
                texts.deleteNode(pos - 1);
            }
            catch (exception e) {
                cout << "it would appear you have used incorrect syntax";
            }
        }
        else if (input.substr(0, 5).compare("edit ") == 0) {
           
            input.erase(0,5);
            string sentence = giveString(input);           
            if (sentence.compare("#*#") != 0) {
                input.erase(input.find(sentence) - 2, sentence.length() + 2);
                try {
                    pos = stoi (input);
                    texts.replaceNode(sentence, pos - 1);
                }
                catch (exception e) {
                    cout << "it would appear you have used incorrect syntax";
                }
            }
            else { cout << "Please enter valid syntax \n";}
        }
        else if(input.substr(0, 5).compare("print") == 0) {
            texts.printList();
        }
        else if (input.substr(0, 7).compare("search ") == 0) {

            input.erase(0,7);
            input = giveString(input);
            if (input.compare("#*#") != 0) {
                texts.retrieveNode(input);
            }
            else { cout << "Please enter valid syntax \n";}
        }
    }
    return 0;
}