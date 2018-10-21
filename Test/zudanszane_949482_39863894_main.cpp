//
//  main.cpp
//  LineEditor
//
//  Created by Zane Pierce Zudans on 9/19/18.
//

#include <iostream>
#include <string>

using namespace std;

class Node //singley linked node with a string of text as its data.
{
    public:
        string line;
        Node* next = NULL;
};

/* The class below is a singley Linked-List whose nodes each represent a single line of the document. The public member methods represent each of the commands the assignment requires to be executable on the document. (i.e., the below class is a linked-list object representing a document, hence the name "dList".)
*/

class dList
{
    private:
        Node* head = new Node(); //The head node, or first line of the document
    public:
        void insertEnd(string text)
        {
            Node* insertedLine = new Node();
            insertedLine->line=text;
            
            //Below is sends the marker node to the end of the document.
            Node* curr = head;
            while(curr->next!=NULL)
            {
                curr=curr->next;
            }
            //Below makes the inserted line linked to the tail node.
            curr->next=insertedLine;
        }
    
        //Below inserts a node (line) at the desired index
        void insert(int index, string text)
        {
            Node* insertedLine = new Node();
            insertedLine->line=text;
            
            //Iterates marker node (curr) to the node before the desired index.
            Node* curr = head;
            for(int i=0;i<(index-1);i++)
            {
                curr=curr->next;
            }
            
            //Linking insertedLine to next node
            insertedLine->next=curr->next;
            //Linking pervious line to subsequent insertedLine (node)
            curr->next=insertedLine;
        }
        /*Below moves to the node before the one to be deleted, links it to the node after the one to be deleted, then deletes the desired node.*/
        void deleteLine(int index)
        {
            Node* curr = head;
            //iterates to the node before that which is to be deleted
            for(int i=0;i<(index-1);i++)
            {
                curr=curr->next;
            }
            
            Node* forDeletion = curr->next;
            //Links node before the deleted to the node after deleted.
            curr->next=forDeletion->next;
            delete forDeletion;
        }
    
        //Below replaces text at node of indicated index
        void editLine(int index, string text)
        {
            Node* curr = head;
            for(int i=0;i<index;i++)
            {
                curr=curr->next;
            }
            curr->line=text;
        }
    
        //Below prints each line as a line on the console, starting w head
        void printDoc()
        {
            string currLine;
            int lineCounter=0;
            
            Node* curr = head->next;
            while(curr!=NULL)
            {
                lineCounter++;
                currLine=to_string(lineCounter);
                currLine.append(" ");
                currLine.append(curr->line);
                cout<<currLine<<endl;
                curr=curr->next;
            }
            cout<<""<<endl;
        }
    
        /*Below takes a string for the searching of, then prints a report of every location at which the desired string may be found*/
        void searchDoc(string wanted)
        {
            Node* curr = head;
            
            bool wantedFound = false; //For the "Not Found" case.
            string report = "\"";
            report.append(wanted);
            report.append("\"");
            report.append(" was found on line(s): ");
            int index = 0;
            string indexStr; //For appending to the report.
            
            string currLine;
            while(curr!=NULL) //Iterates through the list.
            {
                //below creates a report
                currLine=curr->line;
                if (currLine.find(wanted)!=-1)
                {
                    indexStr = to_string(index+1);
                    report.append(indexStr);
                    report.append(", ");
                    wantedFound=true;
                }
                curr=curr->next;
                index++;
            }
            if(!wantedFound) report = "Not Found";
            /*Else gets rid of the ", " ending to the report, then replaces it with "."*/
            else
            {
                for(int i=0;i<2;i++) report.pop_back();
                report.append(".");
            }
            cout<<report<<endl;
        }
};

//The object below handles input output interactions, and operates its dList (document) member accordingly.
class userInterface
{
    private:
        dList* document = new dList(); //The document to be edited.
        string input; //What the user types into console.
        int param; //For cases that address specific lines.
        string text; //Will ultimately be a substring of input, if used; the text to be added to the line.
    public:
        /*Since the .find() method can't distinguish between "insert" and "insertEnd" directly, I made them two separate subcases of an insert case*/
        void insertCase(string input)
        {
            //insertEnd Case
            if(input.find("insertEnd")!=-1)
            {
                text=input.substr(11);
                text.pop_back();
                document->insertEnd(text);
            }
            
            //insert Case
            else
            {
                param = stoi(input.substr(7,1)); /*Converts the input string to a parameter. In this case, the parameter is used as the index for insertion*/
                text = input.substr(10);
                text.pop_back();
                document->insert(param,text);
            }
        }
        //The four cases below are fairly self-explanatory.
        void deleteCase(string input)
        {
            param = stoi(input.substr(7,1));
            document->deleteLine(param);
        }
        void editCase(string input)
        {
            param = stoi(input.substr(5,1));
            text = input.substr(8);
            text.pop_back(); //removes ending quotation marks.
            document->editLine(param,text);
        }
        void printCase()
        {
            document->printDoc();
        }
        void searchCase(string input)
        {
            text = input.substr(8);
            text.pop_back(); //removes ending quotation marks.
            document->searchDoc(text);
        }
        /*controller basically sends the user interface into one of the above command cases depending on what it reads from the user input line.*/
        void controller()
        {
            cout<<"Please input valid command: "<<endl;
            getline(cin,input);
                
            if(input.find("insert")!=-1) insertCase(input);
            else if(input.find("delete")!=-1) deleteCase(input);
            else if(input.find("edit")!=-1)editCase(input);
            else if(input.find("print")!=-1)printCase();
            else if(input.find("search")!=-1)searchCase(input);
            //Below uses an exit code if the user command is "quit".
            else if(input.find("quit")!=-1)
            {
                cout<<"...Program Ending..."<<endl;
                exit(0);
            }
        }
};



int main(int argc, const char * argv[])
{
    userInterface* uI = new userInterface();
    
    while(true) uI->controller();//i.e., runs the controller until the quit statement.
    
    return 0;
}
