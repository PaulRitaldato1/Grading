#include <iostream>
using namespace std;

struct node
{
    string line;
    node* next = NULL;
};

//your linked list implementation here
class LinkedList
{
private:
    node* head = new node;
public:
    //your line editor implementation here
    void lineEditor()
    {
        while(cin)
        {
            string command;
            cin >> command;
            string restOfLine;
            int firstCommaPos = 0;
            int lastCommaPos = 0;
            string text;

            node* prev = new node;
            node* curr = new node;
            node* next = new node;

            if (command == "insertEnd")
            {
                getline(cin,restOfLine);

                //find first comma position

                for(int i=0; i <= restOfLine.length()-1; i++)
                {
                    if(restOfLine[i] == '\"')
                    {
                        firstCommaPos = i;
                        break;
                    }
                }

                //find second comma position
                for(int i = restOfLine.length()-1; i >= 0; i--)
                {
                    if(restOfLine[i] == '\"')
                    {
                        lastCommaPos = i;
                        break;
                    }
                }

                //if there are first and last commas create and add the text

                if(firstCommaPos != lastCommaPos)
                {
                    text = restOfLine.substr(firstCommaPos + 1,lastCommaPos - firstCommaPos -1);

                    //add text to end
                    if(head->line == "")
                    {
                         head->line = text;
                    }
                    else
                    {
                        prev = head;
                        while(prev->next != NULL)
                        {
                            prev = prev->next;
                        }
                        curr = new node;
                        curr->line = text;
                        prev->next = curr;
                    }
                }

            }
            else if (command == "insert")
            {
                int lineNum=0;
                cin >> lineNum;
                getline(cin,restOfLine);

                //find first comma position

                for(int i=0; i <= restOfLine.length()-1; i++)
                {
                    if(restOfLine[i] == '\"')
                    {
                        firstCommaPos = i;
                        break;
                    }
                }

                //find second comma position
                for(int i = restOfLine.length()-1; i >= 0; i--)
                {
                    if(restOfLine[i] == '\"')
                    {
                        lastCommaPos = i;
                        break;
                    }
                }

                //if there are first and last commas create and add the text

                if(firstCommaPos != lastCommaPos)
                {
                    text = restOfLine.substr(firstCommaPos + 1,lastCommaPos - firstCommaPos -1);

                    //if lineNum = 1

                    if(lineNum == 1)
                    {
                        if(head->line == "")
                        {
                            head->line = text;
                        }
                        else
                        {
                            node* n = new node;
                            n->line = text;
                            n->next = head;
                            head = n;
                        }
                    }
                    else
                    {
                        curr = head;
                        int stop = 0;
                        for(int i = 1; i < lineNum-1 ; i++)
                        {
                            if(curr->next == NULL)
                            {
                                stop = 1;
                                break;
                            }
                            curr = curr->next;
                        }
                        if(stop != 1)
                        {
                            if(curr->next == NULL)
                            {
                                node* n = new node;
                                n->line = text;
                                curr->next = n;
                            }
                            else
                            {
                                next = curr->next;
                                node* n = new node;
                                n->line = text;
                                curr->next = n;
                                n->next = next;
                            }
                        }
                    }

                }

            }
            else if (command == "delete")
            {
                int row;
                cin >> row;
                if(row == 1)
                {
                    node* temp = head;
                    head = head->next;
                    delete temp;
                }
                else
                {
                    curr = head;
                    int i=1;
                    while(i<row && (curr->next != 0))
                    {
                        if(i+1 == row)
                        {
                            prev = curr;
                        }
                        curr = curr->next;
                        i++;
                    }
                    if(i == row)
                    {
                        prev->next = curr->next;
                        node* temp = curr;
                        delete temp;
                    }
                }
            }
            else if (command == "edit")
            {
                int row;
                cin >> row;
                getline(cin,restOfLine);

                //find first comma position

                for(int i=0; i <= restOfLine.length()-1; i++)
                {
                    if(restOfLine[i] == '\"')
                    {
                        firstCommaPos = i;
                        break;
                    }
                }

                //find second comma position
                for(int i = restOfLine.length()-1; i >= 0; i--)
                {
                    if(restOfLine[i] == '\"')
                    {
                        lastCommaPos = i;
                        break;
                    }
                }

                //if there are first and last commas create and add the text

                if(firstCommaPos != lastCommaPos)
                {
                    text = restOfLine.substr(firstCommaPos + 1,lastCommaPos - firstCommaPos -1);
                    if(row == 1)
                    {
                        head->line = text;
                    }
                    else
                    {
                        curr = head;
                        int i=1;
                        while(i<row && (curr->next != 0))
                        {
                            curr = curr->next;
                            i++;
                        }
                        if(i == row)
                        {
                            curr->line = text;
                        }
                    }
                }
            }
            else if (command == "print")
            {
                int i = 1;
                curr = head;
                while(curr->next != NULL)
                {
                    cout << i << " " << curr->line << endl;
                    curr = curr->next;
                    i++;
                }
                cout << i << " " << curr->line << endl;
            }
            else if (command == "search")
            {
                getline(cin,restOfLine);
                int found = 0;

                //find first comma position

                for(int i=0; i <= restOfLine.length()-1; i++)
                {
                    if(restOfLine[i] == '\"')
                    {
                        firstCommaPos = i;
                        break;
                    }
                }

                //find second comma position
                for(int i = restOfLine.length()-1; i >= 0; i--)
                {
                    if(restOfLine[i] == '\"')
                    {
                        lastCommaPos = i;
                        break;
                    }
                }

                //if there are first and last commas create and add the text

                if(firstCommaPos != lastCommaPos)
                {
                    text = restOfLine.substr(firstCommaPos + 1,lastCommaPos - firstCommaPos -1);

                    curr = head;
                    int i = 1;
                    while(curr->next != NULL)
                    {
                       if (curr->line.find(text) != string::npos)
                       {
                           cout << i << " " << curr->line << endl;
                           found = 1;
                       }
                       curr = curr->next;
                       i++;
                    }
                    if (curr->line.find(text) != string::npos)
                    {
                        cout << i << " " << curr->line << endl;
                        found = 1;
                    }
                    if(found == 0)
                    {
                       cout << "not found"<< endl;
                    }
                }
            }
            else if (command == "quit")
            {
                return;
            }
        }
    }
};
