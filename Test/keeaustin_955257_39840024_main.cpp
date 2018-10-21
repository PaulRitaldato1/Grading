//
//  main.cpp
//  COP3530 PA1
//
//  Created by Austin Kee on 9/17/18.
//  Copyright © 2018 Austin Kee. All rights reserved.
//

#include <iostream>
#include <string>

struct Line
{
    std::string text;
    Line* next;
};

bool quitFlag = 0;

char cmd[9];
int lineIndex = 0;
std::string input;

Line* head = NULL;

/*
void printMenu()
{
    std::cout << "****************************************************************************" << std::endl;
    std::cout << "*                      LINKED LIST LINE EDITOR                             *" << std::endl;
    std::cout << "****************************************************************************" << std::endl;
    std::cout << "* COMMANDS:                                                                *" << std::endl;
    std::cout << "* 1.) insertEnd <text>  -- insert given text at the end of the document    *" << std::endl;
    std::cout << "* 2.) insert <i> <text> --insert given text at the line indicated by index *" << std::endl;
    std::cout << "* 3.) delete <i> --- delete line at index                                  *" << std::endl;
    std::cout << "* 4.) edit <i> <text> --- replace the line at the index given              *" << std::endl;
    std::cout << "* 5.) print -- print the entire document, with line numbers                *" << std::endl;
    std::cout << "* 6.) search <text> -- print the line number and line                      *" << std::endl;
    std::cout << "* 7.) quit - quit/exit the program                                         *" << std::endl;
    std::cout << "****************************************************************************" << std::endl;
}
*/

void insert(Line* root, int i)
{
   if(root -> next != NULL)
   {
       if(lineIndex == i)
       {
           Line* temp = new Line;
           temp -> text = root -> next -> text;
           temp -> next = root -> next -> next;
           root -> next -> text = input;
           root -> next -> next = temp;
       }
       else
       {
           insert(root -> next, ++i);
       }
   }
   else
   {
       if(lineIndex == i)
       {
           root -> next = new Line;
           root -> next -> text = input;
           root -> next -> next = NULL;
       }
       else
       {
           /*
           root -> next = new Line;
           root -> next -> text = "";
           root -> next -> next = NULL;
           insert(root -> next, ++i);
            */
       }
   }
}

void insert()
{
    int i = 1;
    if(head != NULL)
    {
        if(lineIndex == i)
        {
            Line* temp = new Line;
            temp -> text = head -> text;
            temp -> next = head -> next;
            head -> text = input;
            head -> next = temp;
        }
        else
        {
            insert(head, ++i);
        }
    }
    else
    {
        if(lineIndex == i)
        {
            head = new Line;
            head -> text = input;
            head -> next = NULL;
        }
        else
        {
            /*
            head = new Line;
            head -> text = "";
            head -> next = NULL;
            insert(head, ++i);
            */
        }
    }
}

void insertEnd(Line* root)
{
    if(root -> next != NULL)
    {
        insertEnd(root -> next);
    }
    else
    {
        root -> next = new Line;
        root -> next -> text = input;
        root -> next -> next = NULL;
    }
}

void insertEnd()
{
    if(head != NULL)
    {
        insertEnd(head);
    }
    else
    {
        head = new Line;
        head -> text = input;
        head -> next = NULL;
    }
}

void deleteLine(Line* root, int i)
{
    if(root -> next != NULL)
    {
        if(lineIndex == i)
        {
            Line* temp = root -> next;
            root -> next = temp -> next;
            delete(temp);
        }
        else
        {
            deleteLine(root -> next, ++i);
        }
    }
}

void deleteLine()
{
    int i = 1;
    if(head != NULL)
    {
        if(lineIndex == i)
        {
            if(head -> next != NULL)
            {
                Line* temp = head -> next;
                delete(head);
                head = temp;
            }
            else
            {
                delete(head);
                head = NULL;
            }
        }
        else
        {
            deleteLine(head, ++i);
        }
    }
}

void edit(Line* root, int i)
{
    if(lineIndex == i)
    {
        root -> text = input;
    }
    if(root -> next != NULL)
    {
        edit(root -> next, ++i);
    }
}

void edit()
{
    int i = 1;
    edit(head, i);
}

void printDoc(Line* root, int i)
{
    std::cout << i << " " << root -> text << std::endl;
    if(root -> next != NULL)
    {
        printDoc(root -> next, ++i);
    }
}

void printDoc()
{
    int i = 1;
    if(head != NULL)
    {
        printDoc(head, i);
    }
}

void search(Line* root, int i, bool* found)
{
    if((root->text).find(input) != std::string::npos)
    {
        std::cout << i << " " << root -> text << std::endl;
        *found = 1;
    }
    if(root -> next != NULL)
    {
        search(root -> next, ++i, found);
    }
}

void search()
{
    int i = 1;
    bool found = 0;
    if(head != NULL)
    {
        search(head, i, &found);
        if(!found)
        {
            std::cout << "not found" << std::endl;
        }
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

void quit(Line* root)
{
    // Check if the end of the linked list
    if(root -> next != NULL)
    {
        // Go to the next node
        quit(root -> next);
    }
    // Delete the pointers once the end is reached
    delete(root);
    root = NULL;
}

void quit()
{
    //Destroy the document
    if(head != NULL)
    {
        quit(head);
    }
    
    //Flip the quit bit
    quitFlag = 1;
}

int main(int argc, const char* argv[])
{
    //printMenu(); // Print out the mess of a menu
    
    while(!quitFlag)
    {
        
        std::cin >> cmd;
        std::cin.ignore();
        
        switch(cmd[0])
        {
            case 'i':
                if(cmd[6] != 'E')
                {
                    std::cin >> lineIndex;
                    std::cin.ignore(2);
                    std::getline(std::cin,input);
                    input.pop_back();
                    while(input.length() > 80)
                    {
                        input.pop_back();
                    }
                    insert();
                }
                else
                {
                    std::cin.ignore();
                    std::getline(std::cin,input);
                    input.pop_back();
                    while(input.length() > 80)
                    {
                        input.pop_back();
                    }
                    insertEnd();
                }
                break;
            case 'd':
                std::cin >> lineIndex;
                deleteLine();
                break;
            case 'e':
                std::cin >> lineIndex;
                std::cin.ignore(2);
                std::getline(std::cin,input);
                input.pop_back();
                while(input.length() > 80)
                {
                    input.pop_back();
                }
                edit();
                break;
            case 'p':
                printDoc();
                break;
            case 's':
                std::cin.ignore();
                std::getline(std::cin,input);
                input.pop_back();
                while(input.length() > 80)
                {
                    input.pop_back();
                }
                search();
                break;
            case 'q':
                quit();
                break;
        }
        
    }
    
    return 0;
    
}
