#include <iostream>
#include <string>

struct Node  // struct Node
{
    std::string line;
    Node* next = NULL;
};


Node* insertEnd(Node* head, std::string txt) //inserts node at the end of the list
{
    Node* curr = head;
    Node* newNode = new Node();  // node to be stored

    newNode->line=txt;

    if(head == NULL)  // If head is Null insert text here
    {
        head=newNode;
        return head;
    }

    else    // will find the next null node and put new node there
    {
        while(curr->next != NULL)  //loop until next==null
        {
            curr = curr->next;
        }

        curr->next = newNode;
        return head;
    }
}

Node* insert(Node* head, int line, std::string txt) // inserts string at specific location
{
    if(line<1)      // checks if input is negative
    {
        return head;
    }

    Node* curr = head;
    Node* temp = new Node();
    Node* newNode = new Node();
    newNode->line=txt;

    int pos=1;

    if(head == NULL && line==1)  // If line is one and head is Null insert text here
    {
        head=newNode;
        return head;
    }

    else
    {
        while(pos!=line-1)  // loops until line position to see if its in linkedlist
        {
            if(curr->next == NULL)
            {
                return head;
            }

            else
            {
                curr=curr->next;
                pos++;
            }
        }

        temp=curr->next;        // stores node into linkedlist
        curr->next=newNode;
        newNode->next=temp;

        return head;
    }
}

Node* del (Node* head, int line) //deletes a specific method
{

    Node* curr = head;
    Node* test = head;
    Node* temp = new Node();

    int canD=0;

    curr=head;
    int pos=1;

    while(test != NULL)  // checks if line is in node
    {
        canD++;
        test=test->next;
    }

    if(line>canD)  // if line is not in list don't delete
    {
        return head;
    }


    if(line==1)  // if deleting head
    {
        temp = head;
        head=curr->next;
        delete temp;
        return head;
    }

    while(curr != NULL)  // if deleting any other node
    {
        if(pos==line-1)
        {
            temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            return head;
        }

        else
        {
            curr=curr->next;
            pos++;
        }

    }

    return head;

}

Node* edit(Node* head, int line, std::string txt) // replaces line at specific value
{

    if(line<1)  // checks if value is negative
    {
        return head;
    }

    Node* curr = head;

    int pos=1;

    while(pos!=line)  // loops until it finds pos in list
    {
        if(curr->next == NULL)
        {
            return head;
        }

        else
        {
           curr=curr->next;
           pos++;
        }
    }

    curr->line=txt; // stores txt in line
    return head;

}

void print(Node* head) // prints all of the nodes
{
    Node* curr = head;

    int lCnt=1; // counts number of nodes in LinkedList

    while(curr != NULL)
    {
        std::cout<< lCnt <<" "<< curr->line<<"\n";
        lCnt++;
        curr=curr->next;
    }
}

void search(Node* head, std::string txt) // search nodes for specific line
{
    Node* curr = head;      //sets curr to head
    int lCnt=1;             // keeps track of nodes
    int sLen = txt.length();    // gets txt length
    std::string needTxt;
    bool found=false;


    while(curr != nullptr)  //loops through linked List until null hit
    {
        needTxt=curr->line.substr(0,sLen); // takes part of the string in the curr node node

        if(needTxt == txt)
        {
            std::cout<< lCnt<<" "<< curr->line<<std::endl;     //prints out if desired node is found
            found=true;
            //return;
        }

        else
        {
            int end = curr->line.length()- sLen;

            for(int i=0; i<=end; i++)
            {
                needTxt=curr->line.substr(i,sLen); // takes part of the string in the curr node node

                if(needTxt == txt)
                {
                    found =true;
                    std::cout<< lCnt<<" "<< curr->line<<std::endl;     //prints out if desired node is found

                }
            }
        }
            lCnt++;
            curr=curr->next;  // goes to next node

            if(found && curr== nullptr)
        {
           return;
        }

    }

    std::cout<< "not found"<<std::endl; //prints if not found
    return;
  }

int main () // Main Method
{
    Node* realHead = new Node(); //Actual Linked List of Node
    realHead=NULL;


    while(true)
    {
        //string vars
        std::string userI; // may not need
        std::string comC; //Command Choice
        std::string text; //text

        //Char vars
        char space = 'a';

        //int vars
        int sLen; // string length
        int ton; // number (was for Text or Num)
        int cnt=0; // location right before space
        int cnt2=0; // locations of right before second space


        //Used for debugging
        /*
        std::cout << "Please select on of the following Choices" << std::endl;
        std::cout << "1: InsertEnd" << std::endl;
        std::cout << "2: Insert" << std::endl;
        std::cout << "3: Delete" << std::endl;
        std::cout << "4: Edit" << std::endl;
        std::cout << "5: Print" << std::endl;
        std::cout << "6: Search" << std::endl;
        std::cout << "7: Quit" << std::endl;
        std::cout <<"Your Input: ";
        */

        std::getline(std::cin, userI); //gets user input on one line


        if(userI.substr(0,4) == "quit")  //quits prog if quit is call
        {
            break;
        }

        cnt=0;
        sLen = userI.length();

        while(cnt != sLen) //gets the commands from user inputs
        {
            space = userI.at(cnt);

            if(space == ' ') // break on space
                break;

            else
                cnt++;
        }

        comC=userI.substr(0,cnt); // get command to be called

        if(comC=="insertEnd" && comC.length()==9) //calls insertEnd commmand
        {
            std::string txtLen = userI.substr(cnt+2); //gets the length of the text to be inserted
            int y = txtLen.length();

            text= userI.substr(cnt+2, y-1);

            realHead = insertEnd(realHead, text);
        }


        if(comC=="insert") // if comC is is insert
        {

            space='a';
            cnt2=cnt;
            int numLen=0;

            while(space != ' ')  // gets locations of space in text
            {
                space = userI[cnt2];
                cnt2++;
                numLen++;
            }

            std::string z= userI.substr(cnt+1,numLen);  // makes string in int
            ton = atoi((z.c_str()));

            text = userI.substr(cnt2+3);

            int txtLen = text.length();
            text = userI.substr(cnt2+3,txtLen-1); // gets text from line

            realHead=insert(realHead,ton,text);
        }

        if(comC=="delete")
        {
            //code below gets all the required info for delete to work
            bool notI = false;
            std::string txtLen = userI.substr(cnt+1);
            int y = txtLen.length();

            text = userI.substr(cnt+1,y);

                for(int i=0; i<y;i++)
                {
                    if (isdigit(txtLen[i]))
                    {
                        //does nothing
                    }

                    else
                    {
                       notI=true;
                    }
                }

                if(notI)
                {
                    continue;
                }

                ton = atoi((text.c_str()));

                realHead = del(realHead, ton);
        }

        if(comC=="edit")
        {
            space='a';
            cnt2=cnt;
            int numLen=0;

            while(space != ' ') // gets location of space
            {
                space = userI[cnt2];
                cnt2++;
                numLen++;
            }

            std::string z= userI.substr(cnt+1,numLen); // store string into int
            ton = atoi((z.c_str()));

            text = userI.substr(cnt2+3);

            int txtLen = text.length();  // gets text from line
            text = userI.substr(cnt2+3,txtLen-1);

            realHead=edit(realHead, ton,text);
        }

        if(comC=="print")
        {
            print(realHead);

        }

        if(comC=="search")
        {
            std::string txtLen = userI.substr(cnt+2); // gets int
            int y = txtLen.length();

            text= userI.substr(cnt+2, y-1);
            search(realHead,text);
        }
    }
    return 0;
}

