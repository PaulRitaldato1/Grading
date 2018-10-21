//
//  main.cpp
//  COP3503 PA1
//
//  Created by Benjamin Clark on 9/19/18.
//  Copyright © 2018 Benjamin Clark. All rights reserved.
//
/*
 
 * Linked List
 
 */

#include<iostream>

#include<cstdio>

#include<cstdlib>

using namespace std;

/*
 
 * Declare Node
 
 */

struct node

{
    
    string info;
    
    struct node *next;
    
}*start;

/*
 
 * Declare Class
 
 */

class single_llist

{
    
public:
    
    /*
     
     * Creating Node
     
     */
    
    node *create_node(string value)
    
    {
        
        struct node *temp;
        
        temp = new(struct node);
        
        if (temp == NULL)
            
        {
            
            cout<<"Memory not allocated "<<endl;
            
            return 0;
            
        }
        
        else
            
        {
            
            temp->info = value;
            
            temp->next = NULL;
            
            return temp;
            
        }
        
    }
    
    /*
     
     * Insert Node at last
     
     */
    
    void insert_last()
    
    {
        
        string value;
        
        cout<<"Enter value: ";
        
        cin>>value;
        
        cout<<value<<endl;
        
        struct node *temp, *s;
        
        temp = create_node(value);
        
        s = start;
        
        if(s==NULL)
            
        {
            
            s=temp;
            
        }
        
        else
            
        {
            
            while (s->next != NULL)
                
            {
                
                s = s->next;
                
            }
            
            s->next = temp;
            
        }
        
        temp->next = NULL;
        
        cout<<"Element Inserted at last"<<endl;
        
    }
    
    /*
     
     * Insertion of node at a given position
     
     */
    
    void insert_pos()
    
    {
        
        int pos, counter = 0;
        
        string value;
        
        cout<<"Enter the value to be inserted: ";
        
        cin>>value;
        
        struct node *temp, *s, *ptr = nullptr;
        
        temp = create_node(value);
        
        cout<<"Enter the postion at which node to be inserted: ";
        
        cin>>pos;
        
        int i;
        
        s = start;
        
        while (s != NULL)
            
        {
            
            s = s->next;
            
            counter++;
            
        }
        
        if (pos == 1)
            
        {
            
            if (start == NULL)
                
            {
                
                start = temp;
                
                start->next = NULL;
                
            }
            
            else
                
            {
                
                ptr = start;
                
                start = temp;
                
                start->next = ptr;
                
            }
            
        }
        
        else if (pos > 1 && pos <= counter)
            
        {
            
            s = start;
            
            for (i = 1; i < pos; i++)
                
            {
                
                ptr = s;
                
                s = s->next;
                
            }
            
            ptr->next = temp;
            
            temp->next = s;
            
        }
        
        else
            
        {
            
            cout<<"Positon out of range"<<endl;
            
        }
        
    }
    
    /*
     
     * Delete element at a given position
     
     */
    
    void delete_pos()
    
    {
        
        int pos, i, counter = 0;
        
        if (start == NULL)
            
        {
            
            cout<<"List is empty"<<endl;
            
            return;
            
        }
        
        cout<<"Enter the position of value to be deleted: ";
        
        cin>>pos;
        
        struct node *s, *ptr = nullptr;
        
        s = start;
        
        if (pos == 1)
            
        {
            
            start = s->next;
            
        }
        
        else
            
        {
            
            while (s != NULL)
                
            {
                
                s = s->next;
                
                counter++;
                
            }
            
            if (pos > 0 && pos <= counter)
                
            {
                
                s = start;
                
                for (i = 1;i < pos;i++)
                    
                {
                    
                    ptr = s;
                    
                    s = s->next;
                    
                }
                
                ptr->next = s->next;
                
            }
            
            else
                
            {
                
                cout<<"Position out of range"<<endl;
                
            }
            
            free(s);
            
            cout<<"Element Deleted"<<endl;
            
        }
        
    }
    
    /*
     
     * Update a given Node
     
     */
    
    void update()
    
    {
        
        int pos, i;
        
        string value;
        
        if (start == NULL)
            
        {
            
            cout<<"List is empty"<<endl;
            
            return;
            
        }
        
        cout<<"Enter the node postion to be updated: ";
        
        cin>>pos;
        
        cout<<"Enter the new value: ";
        
        cin>>value;
        
        struct node *s;
        
        s = start;
        
        if (pos == 1)
            
        {
            
            start->info = value;
            
        }
        
        else
            
        {
            
            for (i = 0;i < pos - 1;i++)
                
            {
                
                if (s == NULL)
                    
                {
                    
                    cout<<"There are less than "<<pos<<" elements";
                    
                    return;
                    
                }
                
                s = s->next;
                
            }
            
            s->info = value;
            
        }
        
        cout<<"Updated"<<endl;
        
    }
    
    /*
     
     * Searching an element
     
     */
    
    void search()
    
    {
        
        string value;
        
        if (start == NULL)
            
        {
            
            cout<<"List is empty"<<endl;
            
            return;
            
        }
        
        cout<<"Enter text to be searched: ";
        
        cin>>value;
        
        struct node *s;
        
        s = start;
        
        int pos=0;
        
        while (s != NULL)
            
        {
            
            pos++;
            
            bool flag=false;
            
            for(int i=0; i<s->info.length() && i<value.length(); i++)
                
            {
                
                if(s->info.at(i)==value.at(i))
                    
                    flag=true;
                
            }
            
            if (flag==true)
                
            {
                
                cout<<"Element "<<value<<" is found at position "<<pos<<endl;
                
                return;
                
            }
            
            s = s->next;
            
        }
        
        cout<<value<<" not found in the list"<<endl;
        
    }
    
    /*
     
     * Show link list elements
     
     */
    
    void display()
    
    {
        
        struct node *temp;
        
        if (start == NULL)
            
        {
            
            cout<<"Empty list"<<endl;
            
            return;
            
        }
        
        int count=1;
        
        temp = start;
        
        cout<<"Elements of list are: "<<endl;
        
        while (temp != NULL)
            
        {
            
            cout<<count<<" "<< temp->info<<endl;
            
            count++;
            
            temp = temp->next;
            
        }
        
    }
    
    single_llist()
    
    {
        
        start = NULL;
        
    }
    
};

/*
 
 * Main :holds menu
 
 */

int main()

{
    
    int choice;
    
    single_llist sl;
    
    start = NULL;
    
    while (1)
        
    {
        
        cout<<endl<<"---------------------------------"<<endl;
        
        cout<<endl<<"Operations on singly linked list"<<endl;
        
        cout<<endl<<"---------------------------------"<<endl;
        
        cout<<"1.Insert node at last"<<endl;
        
        cout<<"2.Insert node at position"<<endl;
        
        cout<<"3.Delete a Particular Node"<<endl;
        
        cout<<"4.Update Node Value"<<endl;
        
        cout<<"5.Search Element"<<endl;
        
        cout<<"6.Display Linked List"<<endl;
        
        cout<<"7.Exit "<<endl;
        
        cout<<"Enter your choice : ";
        
        cin>>choice;
        
        switch(choice)
        
        {
                
            case 1:
                
                cout<<"Inserting Node at Last: "<<endl;
                
                sl.insert_last();
                
                cout<<endl;
                
                break;
                
            case 2:
                
                cout<<"Inserting Node at a given position:"<<endl;
                
                sl.insert_pos();
                
                cout<<endl;
                
                break;
                
            case 3:
                
                cout<<"Delete a particular node: "<<endl;
                
                sl.delete_pos();
                
                break;
                
            case 4:
                
                cout<<"Update Node Value:"<<endl;
                
                sl.update();
                
                cout<<endl;
                
                break;
                
            case 5:
                
                cout<<"Search element in Link List: "<<endl;
                
                sl.search();
                
                cout<<endl;
                
                break;
                
            case 6:
                
                cout<<"Display elements of link list"<<endl;
                
                sl.display();
                
                cout<<endl;
                
                break;
                
            case 7:
                
                cout<<"Exiting..."<<endl;
                
                exit(1);
                
                break;
                
            default:
                
                cout<<"Wrong choice"<<endl;
                
        }
        
    }
    
}
