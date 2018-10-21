/****************************************************
Steven Halam Paek
COP 3530
Programming Assignment 1
Line Editor with Linked List
*****************************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <regex>
/****************************************************
Class: List for linkedlist of Nodes
*****************************************************/
//template <typename T>
class List
{
	private:
		struct Node
		{
			std::string data;
			Node* prev;
			Node* next;
			Node(const std::string & d = std::string{}, Node * p = nullptr, Node * n = nullptr) : data{d},prev{p},next{n}{}
      Node(std::string && d, Node * p = nullptr, Node * n = nullptr): data{std::move(d)}, prev{p}, next{n}{}
		};
        Node* head;
        Node* curr;
		Node* temp;
        int theSize=0;
		
	public:
        List()
        {
            theSize = 0;
            head = nullptr;
            curr = nullptr;
            temp = nullptr;
        }

        ~List()
        {
            curr = head;
            while (curr != nullptr)
            {
                temp = curr->next;
                delete curr;
                curr = temp;
            }
            head = nullptr;
        }
        
        
/****************************************************
Function: insertEnd
*****************************************************/
        void insertEnd(std::string data)
        {
            if(data == "\0\0" )
            {
                return;
            }
            Node* newNode = new Node;
            newNode->next = nullptr;
            newNode->data = data;
            theSize++;
            if(head != nullptr)
            {
                curr = head;
                while(curr->next != nullptr)
                {
                    curr=curr->next;
                }
                curr->next = newNode;
            }
            else
            {
                head = newNode;
            }
        }
/****************************************************
Function: insertNode
*****************************************************/
        void insertNode(int node, std::string data)
        {
            if(data == "\0\0" || node == -1)
            {
                return;
            }
            theSize++;
            if (node > theSize)
            {
                //std::cout<<"Index out of bounds"<<std::endl;
                theSize--;
                return;
            }
            Node* addNode = new Node;
            addNode->next = nullptr;
            addNode->data = data;
            
            curr = head;
            temp = head;
            if((node==1) && (theSize==1))
            {
                head = addNode;
            }
            else if ((node==1) && (theSize > 1))
            {
                addNode->next = curr;
                head = addNode;
            }
            else
            {
                for(int k=1;k<node;k++)
                {
                    temp = curr;
                    curr = curr->next;
                }
                temp->next = addNode;
                addNode->next = curr;
            }
        }
/****************************************************
Function: deleteNode
*****************************************************/
        void deleteNode(int node)
        {
            if(node == -1 )
            {
                return;
            }
            if(node>theSize)
            {
                return;
            }
            Node* deleteNode = nullptr;
            temp = head;
            curr = head;
            if(node == 1)
            {
                curr = curr->next;
                head = curr;
                temp->next = nullptr;
                theSize--;
                return;
            }
            for(int j=1;j<node;j++)
            {
                temp = curr;
                curr = curr->next;
            }
            //std::cout<<temp->data<<std::endl;
            //std::cout<<curr->next->data<<std::endl;
            deleteNode = curr;
            curr = curr->next;
            temp->next = curr;
            theSize--;
            //delete deleteNode;
        }
/****************************************************
Function: editNode
*****************************************************/
        void editNode(int node, std::string data)
        {
            if(data == "\0\0" || node == -1)
            {
                return;
            }
            if ((node > theSize) || (node < 1))
            {
                //std::cout<<"Index out of bounds"<<std::endl;
                return;
            }
            curr = head;
            temp = head;
            for(int k=1;k<node;k++)
            {
                curr = curr->next;
            }
            curr->data = data;            
        }
/****************************************************
Function: searchNode
*****************************************************/ 
        void searchNode(std::string findphrase)
        {
            if(findphrase == "\0\0" )
            {
                return;
            }
            curr = head;
            int flag=0;
            for(int a=0;a<theSize;a++)
            {
                std::string phrase = curr->data;
                //index of phrase cannot possibly be greater than 80
                if((phrase.find(findphrase))<=80)
                {
                    flag = 0;
                    std::cout<<(a+1)<<" "<<curr->data<<std::endl;
                }
                else
                {
                    flag=1;
                }
                curr=curr->next;
            }
            if(flag == 1)
            {
                std::cout<<"not found"<<std::endl;
            }
        }
        
/****************************************************
Function: print
*****************************************************/
        void print()
        {
            curr = head;
            for(int i=0;i<theSize;i++)
            {
                std::cout<<(i+1)<<" "<<curr->data<<"\n";
                curr = curr->next;
            }      
        }
 
};//end of class

/****************************************************
Function: findData
*****************************************************/ 
std::string findData(std::string input)
{
    std::string data;
    std::string ros;
    if(input.find('"')<=80)
    {
        data = input.substr(input.find('"')+1, input.length()-input.find('"')-2);
    }
    else
    {
        data = "\0\0";
    }
    data = data.substr(0,80);
    return data;
}
/****************************************************
Function: findros
*****************************************************/ 
std::string findros(std::string input)
{
    std::string ros;
    
    if(input.find('"')<=80)
    {
        ros = input.substr(0,input.find('"'));
    }
    else
    {
        ros = input;
    }
    return ros;
}
/****************************************************
Function: findCommand
*****************************************************/ 
std::string findCommand(std::string ros)
{
    std::string command;
    int repeats=0;
    std::smatch match;
    std::regex regex("[a-zA-Z]+");
    while(std::regex_search(ros,match,regex))
    {
        repeats++;
        command = match[0];
        ros = match.suffix(); 
    }
    if(repeats>1)
    {
        std::cout<<command<<std::endl;
        std::cout<<repeats<<std::endl;
        command = "Error";
    }
    else if (repeats == 1)
    {
        command = command;
    }
    else
    {
        command = "Error";
    }
    return command;
}
/****************************************************
Function: findNumber
*****************************************************/ 
int findNumber(std::string ros)
{
    int number;
    int error_check=0;
    std::smatch matches;
    std::regex reg("\\d+");
    while(std::regex_search(ros,matches,reg))
    {
        error_check++;
        number = std::stoi(matches[0]);
        ros = matches.suffix(); 
    }
    if(error_check>1)
    {
        number = -1;
    }
    else if (error_check == 1)
    {
        number = number;
    }
    else
    {
        number = -1;
    }
    return number;
}

void getMoney(List& list, std::string& command, int number, std::string& data) {
    if (command == "insertEnd")
    {
        list.insertEnd(data); 
    }
    else if (command =="insert")
    {
        list.insertNode(number, data);
    }
    else if (command =="edit") 
    {
        list.editNode(number, data);
    }
    else if (command =="delete") 
    {
        list.deleteNode(number);
    }
    else if (command =="search") 
    {
        list.searchNode(data);
    }
    else if (command =="print") 
    {
        list.print();
    }
    else 
    {
        //std::cout<<"Error, invalid instruction!"<<std::endl;
        return;
    }
}


int main()
{
    //your code to invoke line editor here
    List list;
    std::string input;
    std::string data;
    std::string ros;
    std::string command;
    int number;
    std::getline(std::cin, input);
    
    
    while(input != "quit")
    {
        data = findData(input);
        ros = findros(input);
        number = findNumber(ros);
        command = findCommand(ros);
        getMoney(list,command,number,data);
        std::getline(std::cin, input);
    }
    
}