#include <iostream>
#include <string>

using namespace std;

class Node{
private:
    string Data;
    Node* Next = nullptr;
    Node* Previous = nullptr;



public:
    //Constructor
    //This Node should never be empty, therefore there is only one constructor
    //Pointing to the inintial data
    Node(string _data);
    //Modifiers
    void setData(string _data);
    void setNext(Node* _node);
    void setPrevious(Node* _node);

    //Accessors
    string getData();
    Node* getNext();
    Node* getPrevious();
//    ~Node();
//    Node& operator=(const Node& rhs);
//    Node(const Node& rhs);

};


class LinkedList{

private:
    unsigned int Size = 0;
    Node* Head = nullptr;
    Node* Tail = nullptr;

public:
    //Modifiers
    Node* add(string data);
    Node* add(int index,string data);
    void remove(int index);
    string set(int index, string data);



    //Accessors
    string get(int index);


    //Node Accessors
    Node* getHead();
    Node* getTail();


    int size();
};

//Node Definitions

Node::Node(string _data){
    setData(_data);
}


void Node::setData(string _data){
    this->Data = _data;
}


void Node::setNext(Node* _node){
    this->Next = _node;

}


void Node::setPrevious(Node* _node){
    this->Previous = _node;
}


string Node::getData(){
    return this->Data;
}

Node* Node::getNext(){
    return this->Next;
}

Node* Node::getPrevious(){
    return this->Previous;
}

//Node::~Node() = default;
//Node::Node(const Node &rhs) = default;
//Node& Node::operator=(const Node &rhs) { this->Data = rhs.Data; this->Next = rhs.Next; this->Previous = rhs.Previous;}


//Linked List Implementations


Node* LinkedList::add(string data){
    //defines the head
    if(this->Head == nullptr){
        this->Head = new Node(data);
        this->Tail = this->Head;
        this->Size++;
        return this->Head;
    }

    //To add to the end:
    //Takes the tail and points to the new node, set the previous, then define the new tail
    this->Tail->setNext(new Node(data));
    this->Tail->getNext()->setPrevious(this->Tail);
    this->Tail = this->Tail->getNext();
    this->Size++;
    return this->Tail;
}


Node* LinkedList::add(int index, string data){
    if(index < 0 or index > this->Size){

    }
    else if(index == this->Size or this->Size == 0){
        return add(data);
    }
    else{
        Node* currentNode = this->Head;
        //Iterates until the Node before the desired index
        for(unsigned int i = 1; i < index; i++){
            currentNode = currentNode->getNext();
        }
        Node* newNode = new Node(data);
        //set the old index previous to the new node
        //set the new node Next
        //set the current Node to the new node
        //set the current Node previous
        currentNode->getNext()->setPrevious(newNode);
        newNode->setNext(currentNode->getNext());
        currentNode->setNext(newNode);
        newNode->setPrevious(currentNode);
        this->Size++;
        return newNode;
    }
}


void LinkedList::remove(int index){
    if(index < 0 or index >= this->size()){

    }
    else if(this->size() == 1){
        this->Head = nullptr;
        this->Tail = nullptr;
        this->Size--;
    }
    else if(index == 0){
        this->getHead()->getNext()->setPrevious(this->getHead());
        this->Head = this->getHead()->getNext();
        this->Size--;
    }
    else if(index == this->size() - 1){
        this->getTail()->getPrevious()->setNext(this->getTail());
        this->Tail = this->getTail()->getPrevious();
        this->Size--;
    }
    else{
        Node* currentNode = this->Head;
        //Iterates until the Node before the desired index
        for(unsigned int i = 0; i < index; i++){
            currentNode = currentNode->getNext();
        }
        currentNode->getPrevious()->setNext(currentNode->getNext());
        currentNode->getNext()->setPrevious(currentNode->getPrevious());
        this->Size--;

    }
}


string LinkedList::set(int index, string data){
    Node* currentNode = this->Head;
    //Iterates until the Node before the desired index
    for(unsigned int i = 0; i < index; i++){
        currentNode = currentNode->getNext();
    }
    currentNode->setData(data);
    return data;
}



string LinkedList::get(int index){
    Node* currentNode = this->Head;
    //Iterates until the Node before the desired index
    for(unsigned int i = 0; i < index; i++){
        currentNode = currentNode->getNext();
    }
    return currentNode->getData();
}


Node* LinkedList::getHead(){
    return this->Head;
}


Node* LinkedList::getTail(){
    return this->Tail;
}


int LinkedList::size(){
    return this->Size;
}







//your line editor implementation here
class LineEditor{

private:

    LinkedList linesList;
    int lineNum = 0; //may not be necessary due to LinkedList size



public:
    void insertEnd(string text);
    void insert(int line, string text);
    void remove(int line);
    void edit(int line, string text);
    void print();

    int search(string text);
    bool quit(bool& key);
    int Size(){return this->linesList.size();}
};

void LineEditor::insertEnd(string text){
    this->linesList.add(text);
}

void LineEditor::insert(int line, string text){
    this->linesList.add(line - 1, text);
}
void LineEditor::remove(int line){
this->linesList.remove(line - 1);
}
void LineEditor::edit(int line, string text){
    this->linesList.set(line - 1, text);
}
void LineEditor::print(){
    Node* currentLine = this->linesList.getHead();
    for(unsigned int i = 0; i < linesList.size(); i++){
        cout << i + 1 << " " << currentLine->getData() << endl;
        currentLine = currentLine->getNext();
    }
}

int LineEditor::search(string text){
    Node* currentLine = this->linesList.getHead();
    int x = 0;
    for(unsigned int i = 0; i < linesList.size(); i++){
        if(currentLine->getData().find(text) != string::npos){
            cout << i+1 << " " << currentLine->getData() << endl;
            x++;
        }
        currentLine = currentLine->getNext();
    }
    if(x == 0)
    cout << "not found" << endl;

    return -1;
}

bool LineEditor::quit(bool& key){
    key = false;
    return false;
}

void TestInsertEnd(LineEditor& lineEditor);
void TestInsertIndex(LineEditor& lineEditor);
void TestDelete(LineEditor& lineEditor);
void TestEdit(LineEditor& lineEditor);
void TestPrint(LineEditor& lineEditor);
void TestSearch(LineEditor& lineEditor);


int main(){

    LineEditor lineEditor;
//    TestInsertEnd(lineEditor);
//    TestInsertIndex(lineEditor);
//    TestDelete(lineEditor);
//    TestEdit(lineEditor);
    bool exit = true;
    string input;
    string string1;
    string string2;
    string string3;
    while(exit){
        getline(cin, input);

        string1 = input.substr(0, input.find(" "));
//        cout <<  input.size()-input.find(" ")<< endl;
        string2 = input.substr(input.find(" ")+1, input.size());
        if(string2.find('"') > 1){
            string3 = string2.substr(string2.find(" ")+2, string2.size()-string2.find(" ")-3);
            string2 = input.substr(input.find(" ")+1, string2.find('"')-1);

        }
        else{
            string2 = string2.substr(1, string2.size()-2);
        }

        if (string1 == "insertEnd") {
//            string2 = string2.substr(1, string2.size()-2);
            lineEditor.insertEnd(string2);
        }
        else if (string1 == "insert") {
//            string2 = string2.substr(0, string2.find(" "));
//            string3 = input.substr(input.find(string2), )
            lineEditor.insert(stoi(string2), string3);
        }

        else if (string1 == "edit")
            lineEditor.edit(stoi(string2), string3);

        else if (string1 == "print")
            lineEditor.print();

        else if (string1 == "search")
            lineEditor.search(string2);

        else if (string1 == "delete")
            lineEditor.remove(stoi(string2));

        else if (string1 == "quit" || string1 == "Quit") {
            lineEditor.quit(exit);
            break;
        }

    }


}

void TestInsertEnd(LineEditor& lineEditor){
    cout << "Testing insertEnd()" << endl;
    string string1 = "All that is gold does not glitter";
    string string2 = "Not all those who wander are lost";

    lineEditor.insertEnd(string1);
    lineEditor.insertEnd(string2);

}
void TestInsertIndex(LineEditor& lineEditor){
    cout << "Testing insertIndex()" << endl;
    string string1 = "The old that is strong does not wither";
    string string2 = "Deep roots are not reached by the frost";

    lineEditor.insertEnd(string2);
    lineEditor.insert(3, string1);
}

void TestDelete(LineEditor& lineEditor){
    cout << "Testing delete()" << endl;
    string string1 = "There are three things all wise men fear: the sea in storm, a night with no moon, and the anger of a gentle man.";
    lineEditor.insert(2,string1);
    lineEditor.remove(2);
}

void TestEdit(LineEditor& lineEditor){
    cout << "Testing edit()" << endl;
    string string1 = "A light from the shadows shall spring";
    string string2 = "From the ashes, a fire shall be awoken";
    lineEditor.insertEnd(string2);
    lineEditor.edit(lineEditor.Size(), string1);

}
