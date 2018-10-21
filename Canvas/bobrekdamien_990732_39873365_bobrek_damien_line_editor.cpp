#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
class LinkedList
{
private:
  struct node {
    T contents;
	
    node * prev = nullptr;
    node * next = nullptr;
  };

  size_t list_size = 0;
  
  node * head = nullptr;
  node * tail = nullptr;
  
  node * get_node(size_t position)
  {
    if (list_size == 0)
      throw std::out_of_range("trying to get a node from an empty linked list");
    if (position >= list_size)
      throw std::out_of_range("trying to get a node from a linked list outside of the valid range");
    
    if (position == 0)
      return head;
    else if (position == (list_size-1))
      return tail;
    else if (position <= (list_size/2))
      {
        node * parser = head;
        for(size_t i = 0; i < position; i++)
          parser = parser->next;

        return parser;
      }
    else // if (position > (list_size/2))
      {
        node * parser = tail;
        for (size_t i = (list_size-1); i > position; i--)
          parser = parser->prev;

        return parser;
      }
  }
    
public:
  // default constructor
  LinkedList() {};

  // default destructor
  ~LinkedList()
  {
    while (list_size != 0)
      {
        remove(0);
      }
  }

  size_t size() { return list_size; }
  
  void insert(size_t position, T new_item)
  {
    if(position > list_size)
      throw std::out_of_range("trying to insert a node into a linked list outside of the valid range");
    
    node * new_node = new node();
    new_node->contents = new_item;

    if(list_size == 0)
      {
        // this new node is both the head and tail
        head = new_node;
        tail = new_node;
      }
    else if (position == 0)
      {
        // link the new head with the old head
        head->prev = new_node;
        new_node->next = head;

        // set head to indicate that the new node is now it
        head = new_node;
      }
    else if (position == list_size)
      {
        // link the new tail with the old tail
        tail->next = new_node;
        new_node->prev = tail;

        // set tail to indicate that the new node is now it
        tail = new_node;
      }
    else
      {
        node * next_node = get_node(position);
        node * prev_node = next_node->prev;

        //link the new node with the one before it
        prev_node->next = new_node;
        new_node->prev = prev_node;

        //link the new node with the one after it
        next_node->prev = new_node;
        new_node->next = next_node;
      }

    list_size++;
  }

  T remove(size_t position)
  {
    // by calling get_node(), exceptions will be thrown for improper position values
    node * node_removed = get_node(position);
    
    if (position == 0)
      {
        // reposition head
        head = node_removed->next;

        // change prev pointer of new head
        if(head != nullptr)
          head->prev = nullptr;
      }
    else if (position == (list_size-1))
      {
        // reposition tail
        tail = node_removed->prev;

        // change the next pointer of the new tail
        if(tail != nullptr)
          tail->next = nullptr;
      }
    else
      {
        (node_removed->prev)->next = node_removed->next;
        (node_removed->next)->prev = node_removed->prev;
      }
    
    T contents = node_removed->contents; 
    
    delete node_removed;
    list_size--;

    return contents;
  }

  void push_front(T new_item) { insert(0, new_item); }
  void push_back(T new_item) { insert(list_size, new_item); }

  T pop_front() { return remove(0); }
  T pop_back() { return remove(list_size-1); }
  
  // by calling get_node(), exceptions will be thrown for improper position values
  T access(size_t position) { return (get_node(position))->contents; }
  T front() { return access(0); }
  T back() { return access(list_size-1); }
};


string * get_quoted_line(string input);
size_t get_line_num(string input);

int main()
{
  
  LinkedList<string> document;
  
  while(true)
    {
      string input;
      std::getline(cin, input);

      string command = input.substr(0, input.find_first_of(' '));

      
      // break the while-loop if the quit command is issued
      if(command.compare("quit") == 0)
        {
          break;
        }
      
      else if(command.compare("insertEnd") == 0)
        { 
          string * line = get_quoted_line(input);

          if (line != nullptr)
            {
              document.push_back(*line);
              delete line;
            }
        }
      
      else if(command.compare("insert") == 0)
        {
          size_t line_num = get_line_num(input);

          // accounting for invalid line positions
          if (line_num == 0 || line_num > (document.size()+1) )
            continue; // leave this iteration of the loop
          
          string * line = get_quoted_line(input);

          // the pre-decrement is used to switch to zero-indexing for the linked list
          if (line != nullptr)
            {
              document.insert(--line_num, *line);
              delete line;
            }
        }
      
      else if(command.compare("delete") == 0)
        {
          size_t line_num = get_line_num(input);

          // accounting for invalid line positions
          if (line_num == 0 || line_num > document.size())
              continue; // leave this iteration of the loop

          // the pre-decrement is used to switch to zero-indexing for the linked list
          document.remove(--line_num);
        }
      
      else if(command.compare("edit") == 0)
        {
          size_t line_num = get_line_num(input);

          // accounting for invalid line positions
          if (line_num == 0 || line_num > document.size())
              continue; // leave this iteration of the loop
          
          string * line = get_quoted_line(input);

          if (line != nullptr)
            {
              // the pre-decrement is used to switch to zero-indexing for the linked list
              document.remove(--line_num); // remove the old line that held the position
              document.insert(line_num, *line); // insert the new line into its place
              delete line;
            }
        }
      
      else if(command.compare("print") == 0)
        {
          for(size_t i = 0; i < document.size(); i++)
            cout << i+1 << " " << document.access(i) << endl;
        }
      
      else if(command.compare("search") == 0)
        { 
          string * search_term = get_quoted_line(input);

          if (search_term != nullptr)
            {
              bool term_found = false;

              for(size_t i = 0; i < document.size(); i++)
                {
                  string current_line = document.access(i);

                  size_t term_position = current_line.find(*search_term);
              
                  if (term_position != string::npos)
                    {
                      cout << i+1 << " " << current_line << endl;
                      term_found = true;
                    }
                }

              if (term_found == false)
                cout << "not found" << endl;

              delete search_term;
            }
        }
    }

}

string * get_quoted_line(const string input)
{
  size_t line_start = input.find_first_of('"');
  size_t line_end = input.find_last_of('"');

  if ( line_start == line_end || line_start == string::npos )
    {
      return nullptr;
    }

  // change the index to the start of the line instead of the quotation mark
  line_start++;

  // the line_size is the size of the string of text provided
  size_t line_size = line_end - line_start;

  // limit the line size to 80 characters
  if (line_size > 80)
    {
      return nullptr;
    }

  string * quoted_line = new string;
  *quoted_line = input.substr(line_start, line_size);
  
  return quoted_line;
}

size_t get_line_num(const string input)
{
  // copy the string into a cstring
  char * input_c = new char[input.size() + 1];
  memset(input_c, '\0', input.size()+1); // initially fill it with null values
  strcpy(input_c, input.c_str());

  // getting the line number from the string using cstring tokenization
  char * p = strtok(input_c, " \f\n\r\t\v");
  // have p point to the second token in the cstring: the line number value
  p = strtok(nullptr, " \f\n\r\t\v");
  
  // convert line number to unsigned size_t int type
  size_t line_num = abs(strtol(p, nullptr, 10));
  
  delete input_c;

  return line_num;
}

