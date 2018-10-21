#include <iostream>
using namespace std;

struct Node
{
    public:
    string textLine;
    Node *next;
};

class linked_list
{
	public:
	int numOfLines;
	Node *head;
	Node *tail;

	linked_list() //initialize linked list
	{
	    numOfLines = 0;
        head = NULL;
        tail=NULL;
	}
	void deleteLinked_list(linked_list &currList)
    {
        Node *itr = currList.head;
        Node *next;
        while(itr!=NULL)
        {
            //cout<< itr->textLine<<endl;
            next = itr->next;
            delete itr;
            itr = next;
        }
        currList.head=NULL;
        currList.tail=NULL;
	}
	void insertEnd (linked_list &currList, string text);
	void insertMid(linked_list &currList, int index, string text);
	void deleteLine (linked_list &currList, int index);
	void editLine (linked_list &currList, int lineNum, string newText);
	void searchLine (linked_list &currList, string text);
	void print (linked_list &currList);
	int getNumOfLines (linked_list &currList);
};

int getNumOfLines (linked_list &currList)
{
    Node *itr = currList.head;
    int i =0;
     while(itr!=NULL)
    {
        itr = itr->next;
        ++i;
    }
    return i;
}
void insertEnd (linked_list &currList, string text)
{
	//create node
	Node *temp = new Node;
	temp->textLine = text;
	temp->next = NULL;

	//if list is empty
	if(currList.head==NULL)
	{
		currList.head=temp;
		currList.tail=temp;
		temp=NULL;
	}

	//list isn't empty, append node to end of list
	else
	{
		currList.tail->next = temp;
		currList.tail=temp;
		temp=NULL;
	}
	//increment list count
	++currList.numOfLines;
}

void insertMid(linked_list &currList, int index, string text)
{
	//create node
	Node *temp = new Node;
	temp->textLine = text;

	if (index == 1)
    {
        temp->next = currList.head;
        currList.head = temp;
    }
    else if (index == 2)
    {
        temp->next = currList.head->next;
        currList.head->next = temp;
        //temp=NULL;
    }
    else if (index == (getNumOfLines(currList)+1))
    {
        insertEnd(currList, text);
        delete temp;
    }
    else if (index >(getNumOfLines(currList)+1))
    {
        delete temp;
    }
    else
    {
        Node *itr = currList.head;
        for(int i=2; i < index; ++i)
        {
            itr= itr->next;
        }
        temp->next = itr->next;
        itr->next = temp;
    }
}

void deleteLine (linked_list &currList, int index)
{
    //iterate through list and remove node
    Node *temp, *prev, *next;

    if(index==1)
    {
        next = currList.head->next;
        delete currList.head;
        currList.head = next;
    }
    else
    {
        prev= currList.head;
        temp = currList.head->next;

        for(int i = 2; (i<index) && (prev->next !=NULL); ++i)
        {
            prev = prev->next;
            temp = temp->next;
        }
        if (prev->next !=NULL)
        {
             prev->next = temp->next;
             delete temp;
        }
        else
        {
            temp=NULL;
            prev=NULL;
            return;
        }
    }
    temp=NULL;
    prev=NULL;
}

void editLine (linked_list &currList, int lineNum, string newText)
{
    Node *itr = currList.head;
    int i =1;
    while(i<lineNum)
    {
        itr = itr->next;
        ++i;
    }

    itr->textLine = newText;
}

void searchLine (linked_list &currList, string textVal)
{
    Node *itr = currList.head;
    int lineNum = 1;
    size_t found;
    int yes = 0;
    while (itr!=NULL)
    {
        found=itr->textLine.find(textVal);
        if(found!=std::string::npos)
        {
            cout << lineNum << " " <<itr->textLine<<endl;
             ++lineNum;
            itr = itr->next;
            yes = 1;
            //return;
        }
        else
        {
            ++lineNum;
            itr = itr->next;
        }
    }
    if(yes==0)
    {
    cout << "not found"<<endl;
    }
}

void print (linked_list &currList)
{
    Node *itr = currList.head;
    int i =1;
    while(itr!=NULL)
    {
        cout << i << " " << itr->textLine<<endl;
        itr = itr->next;
        ++i;
    }
}

#include <iostream>
using namespace std;

int main()
{
    string order;//take in first order and loop until quit is called
    //initialize linked list
    linked_list myList;
    do
    {
        cin >> order;   //take in order

        if (order.compare("insertEnd") == 0) //take in line and call insertEnd method
        {
            string newLine;    //data for node

            getline(cin, newLine); //take in input
            //erase quotes

            int lineSize = newLine.length();
            newLine = newLine.substr(2,(lineSize-3));

            insertEnd(myList, newLine); //put new line in the list
        }

        else if (order.compare("insert") == 0) //take in line and index and call insert method
        {
            int lineNum; //line text will be inserted at
            string newLine;    //data for node
            cin >> lineNum;
            getline(cin, newLine);
            //erase quotes

            int lineSize = newLine.length();
            newLine = newLine.substr(2,(lineSize-3));

            insertMid(myList, lineNum, newLine);
        }

        else if (order.compare("delete") == 0) //take in index and call delete method
        {
            int lineNum;
            cin >> lineNum; //take in line number to delete
            deleteLine(myList, lineNum);
        }

        else if (order.compare("edit") == 0) //take in line and index and call edit method
        {
            int lineNum;
            string difLine;
            cin >> lineNum; //take in line number to edit
            getline(cin, difLine);
            //erase quotes

            int lineSize = difLine.length();
            difLine = difLine.substr(2,(lineSize-3));
            editLine(myList, lineNum, difLine);
        }
        else if (order.compare("print") == 0) // print out list data with line numbers
        {
            //call print method
            print(myList);
        }

        else if (order.compare("search") == 0) //take in string and call search method
        {
            string searchVal;
            getline(cin, searchVal);
            //erase quotes
            int lineSize = searchVal.length();
            searchVal = searchVal.substr(2,(lineSize-3));
            searchLine(myList, searchVal);
        }

        else if (order.compare("quit") == 0) // deallocate and end program
        {
            order = "stop";
            myList.deleteLinked_list(myList);
        }

        else
        {
            continue;
            //cout << "invalid input, try again" << endl;
        }

    } while(order.compare("stop") != 0);

  //end program when out of loop
  return 0;
}


