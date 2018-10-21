#include<bits/stdc++.h>
using namespace std;

struct node
{
   string data;
   struct node *next;
};

//Declration of Variables
struct node *start=NULL;

//Declaration of Functions
struct node* create(void);
void insertEnd(struct node *,string);
void insert(struct node *,int,string);
void deleteNode(struct node *,int);
void edit(struct node *,int,string);
void search(struct node *,string);
void print(struct node *);


int main()
{
   string command;
   string temp;
   string str_index;
   int index, p;
   stringstream ss;

   while(1) //Program will loop until user quits
   {
      getline(cin,command);

      if(command == "print")
      {
         print(start);
      }

      else if(command == "quit")
      break;

      else if(command.substr(0,6) == "search")
      {
         temp = command.substr(8);
         temp.pop_back(); //Removes quote
         search(start,temp);
      }

      else if(command.substr(0,4) == "edit")
      {
         p = command.find(" ",5);
         str_index = command.substr(5,p-5);

         ss << str_index;
         ss >> index;
         ss.clear();

         temp = command.substr(p+2);
         temp.pop_back(); //Removes other quote
         edit(start,index,temp);
      }

      else if(command.substr(0,6) == "delete")
      {
         str_index = command.substr(7);

         ss << str_index;
         ss >> index;
         ss.clear();
         deleteNode(start,index);
      }

      else if(command.substr(0,9) == "insertEnd")
      {
         temp = command.substr(11);
         temp.pop_back(); //Removes quote
         insertEnd(start,temp);
      }

      else
      {
         p = command.find(" ",7);

         str_index = command.substr(7,p-7);

         ss << str_index;
         ss >> index;
         ss.clear();

         temp = command.substr(p+2);
         temp.pop_back(); //Removes other quote
         insert(start,index,temp);
      }
   }
   return 0;
}

//Create new node
struct node* create(string value)
{
   struct node *n = new node;
   n->data = value;
   n->next = NULL;
   return(n);
}

//Print current list
void print(struct node *p)
{
   int i = 1;
   while(p)
   {
      cout<<i<<" "<<p->data<<endl;
      p = p->next;
      i++;
   }
}

//Inserts new line at the end
void insertEnd(struct node *p, string temp)
{
   struct node *n;
   n = create(temp);
   if(start == NULL)
   start = n;
   else
   {
      while(p->next != NULL) //Move to the end of list
      p = p->next;
      p->next = n; //Add new line
   }
}

//Inserts new line at specified position
void insert(struct node *p, int index, string temp)
{
   struct node *prev = NULL; //Stores node previous to new one
   struct node *n = create(temp);
   int i;
   for(i = 1; i < index; i++)
   {
      prev = p;
      p = p->next;
   }
   if(prev == NULL) //If node is to be added at first position
   {
      n->next = start;
      start = n;
   }
   else
   {
      n->next = p;
      prev->next = n;
   }
}

//Delete a line at specified position
void deleteNode(struct node *p, int index)
{
   struct node *q; //Stores line to be deleted
   struct node *prev = NULL; //Stores node previous to deleted

   for(int i = 1; i < index; i++)
   {
      prev = p;
      p = p->next;
   }
   if(prev == NULL) //If first line is to be deleted
   {
      q = p;
      start = start->next;
   }
   else
   {
      q = p;
      prev->next = p->next;
   }
   delete q; //Frees up node
}

//Edits line at specific position
void edit(struct node *p, int index, string temp)
{
   int i;
   for(i = 1; i < index; i++)
   {
      p = p->next;
   }
   p->data = temp;
}

//Purpose is to find node user was searching for
void search(struct node *p,string temp)
{
   int i = 1;
   int count = 0;
   while(p)
   {
      if(p->data.find(temp) != -1)
      {
         cout << i << " " << p->data <<endl;
         count = 1;
      }
      p = p->next;
      i++;
   }
   if(count == 0)
   cout << "not found" << endl;
}
