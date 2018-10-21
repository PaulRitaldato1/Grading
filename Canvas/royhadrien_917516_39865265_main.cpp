#include <iostream>
#include <sstream>
#include <string>


/*
 * NODE DECLARATION
 */
struct Node  // node class
{
public:
    std::string data;         // string as value for node
    Node *next = NULL;
};

/*
 * LIST DECLARATION
 */
class List {
private:
    Node *head;
    Node *tail;

public:
    List() {
        head = NULL;
        tail = NULL;
    }

    // method declarations
    void insertEnd(std::string text);
    void insert(int index, std::string text);
    void deleteNode(int index);
    void edit(int index, std::string text);
    void search(std::string text);
    void print();

    bool isIndexGood(int index, std::string choice);

}; // end class list


/*
 * MEMBER FUNCTIONS
 */
void List::insertEnd(std::string text)
{
    Node *addNode = new Node();
    addNode->data = text;
    addNode->next = NULL;

    if (head == NULL) //if no list
    {
        head = addNode; //make addNode head
        tail = addNode; //make addNode tail
        addNode = NULL; //take away addNode
    }
    else {
        tail->next = addNode;
        tail = addNode;
    }
}

void List::insert(int index, std::string text)
{
    Node *current = new Node();
    Node *previous = new Node();
    Node *addNode = new Node(); //create new node
    addNode->data = text;  //put text in new node

    current = head;
    for (int i = 1; i < index; i++)  //go through list to get to index
    {
        previous = current;
        current = current->next;
    }
    previous->next = addNode; //insert new node
    addNode->next = current;
}

void List::deleteNode(int index)
{
    Node *current = new Node(); //create current node
    Node *previous = new Node(); //create previous node
    current = head; //make current head

    for (int i = 1; i < index; i++) //go thru list to index
    {
        previous = current;
        current = current->next;
    }
    previous->next = current->next; // take out node by linked previous with current
}

void List::edit(int index, std::string text)
{
    Node *current = new Node();

    if (index == 0) //invalid index catch
    {
        std::cout << "Invalid index, please try again." << std::endl;

    }
    current = head;
    for (int i = 0; i < index-1; i++)  //go through list to index
    {
        current = current->next;
    }
    current->data = text; //insert text
}

void List::search(std::string text)
{
    Node *current = new Node();
    current = head;
    int index = 1;

    while (current != NULL)
    {
        std::string str = current -> data;

        if (str.find(text) != std::string::npos) //if text is substring of node data its good
        {
            std::cout << index << " " << str << std::endl;
        }
        else if (current->next == NULL)
        {
            std::cout << "not found" << std::endl; //search not found
        }
        current = current->next;
        index++;
    }
}

void List::print()
{
    int index = 1;
    Node *current; //create node
    current = head; //make new node start at head
    while (current != NULL)
    {   //print out in format
        std::cout << index  << " " <<  (current->data)  << std::endl;
        current = current->next;    //goes to next node
        index ++;
    }
}

bool List::isIndexGood(int index, std::string choice) //check to see if index is valid for edit, insert, and delete
{
    if (index == 0) // if index is 0
    {
        return false;
    }
    Node *current = new Node();
    current = head;

    int count = 1; //counter to count nodes in list
    while (current != NULL)
    {
        current = current->next;    //goes to next node
        count ++;
    }
    if ((index < count) && (index > 0) && (choice == "delete")) //delete index restrictions
    {
        return true;
    }
    else if ((index <= count) && (index > 0) && (choice == "insert")) //insert index restrictions
    {
        return true;
    }
    else if ((index < count) && (index > 0) && (choice == "edit")) //edit index restrictions
    {
        return true;
    }
    else //if restrictions not met return false
    {
        return false;
    }
}


/*
 * FUNCTIONS
 */
int indexToInt(std::string indexTemp)
{
    int index;
    index = std::stoi(indexTemp); //convert index to int
    return index;
}


/*
 * MAIN
 */
int main()
{
    List list;
    A:

    //Variable Declaration
    std::string input;
    std::string choice;
    std::string temp;
    std::string temp2;
    std::string indexTemp;
    std::string text;
    bool goodIndex;
    int index;

    std::getline(std::cin, input);//get user input


    //go through input for choice
    for (int i = 0; i < input.length(); i++)
    {
        //(2+ segments)
        //to get choice ( insertEnd, insert, search, edit, delete )
        if (input[i] == ' ')
        {
            choice = input.substr(0, i); //get choice
            temp.append(input.substr(i + 1, input.length() - 1)); //place rest in temp
            if (choice != "insertEnd" && choice != "insert" && choice != "search" && choice != "edit" && choice != "delete")
            {
                std::cout << "Not acceptable input try again" << std::endl;
                goto A;
            }
            else
            {
                goto B; //if good choices go to choice selection
            }
        }
            //print or quit (1 segment)
        else if (i == input.length()-1)
        {
            choice.append(input.substr(0, i+1)); //get choice print or quit
            if (choice != "print" && choice != "quit")
            {
                std::cout << "Not acceptable input try again" << std::endl;
                goto A;
            }
            else
            {
                goto B;
            }
        }
    }

    B:
    if (choice == "delete") {
        indexTemp.append(temp.substr(0)); //get index string
    }
    else if (choice == "insert" || choice == "edit") {
        indexTemp.append(temp.substr(0));
        text.append(temp.substr(3, temp.length() - 4));
        if (text.length() > 80) //if input is too long try again
        {
            std::cout << "Not acceptable input try again" << std::endl;
            goto A;
        }
    }
    else if (choice == "insertEnd" || choice == "search") {
        text.append(temp.substr(1, temp.length() - 2));
        if (text.length() > 80) //if input is too long try again
        {
            std::cout << "Not acceptable input try again" << std::endl;
            goto A;
        }
    }

    //select method by choice
    //go back to user input if not quit
    while (choice != "quit") {
        if (choice == "insertEnd")
        {
            list.insertEnd(text);
            goto A;
        }
        if (choice == "insert")
        {
            index = indexToInt(indexTemp); //returns index
            goodIndex = list.isIndexGood(index, choice); // returns false if index isn't true
            if (goodIndex) //if index good insert
            {
                list.insert(index, text);
            }
            goto A;
        }
        if (choice == "delete")
        {
            index = indexToInt(indexTemp); //returns index
            goodIndex = list.isIndexGood(index, choice); // returns false if index isn't true
            if (goodIndex) //if index good delete
            {
                list.deleteNode(index);
            }
            goto A;
        }
        if (choice == "edit")
        {
            index = indexToInt(indexTemp); //returns index
            goodIndex = list.isIndexGood(index, choice); // returns false if index isn't true
            if (goodIndex) //if index good then edit
            {
                list.edit(index, text);
            }
            goto A;
        }
        if (choice == "search")
        {
            list.search(text); //search
            goto A;
        }
        if (choice == "print")
        {
            list.print(); //print
            goto A;
        }
    }
    return 0; //end main
}

