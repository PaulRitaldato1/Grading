#include <iostream>
#include <string>
#include <vector>
/**
 *  UTILITY FUNCTIONS
 */
void printLine(std::string str){
  std::cout << str << std::endl;
}
void printLine(char c){
  std::cout << c << std::endl; 
}
std::vector<std::string> splitUntil(std::string str, char delim, size_t limit){
  std::vector<std::string> splits;
  std::string stringBuf;
  for(int i = 0; i < str.length(); i++ ){ if(i < limit && str[i] == delim){
      splits.push_back(stringBuf);
      stringBuf = "";
    }
    else{
      stringBuf += str[i];
    }
  }
  splits.push_back(stringBuf);
  return splits;
};
std::string strip(std::string str, char removeCharacter){
  std::string retString;
  for(char character : str){
    if(character != removeCharacter)
      retString += character;
  }
  return retString;
};

template<typename T> 
struct Node{
  Node* next;
  T item;
};
template<typename T> 
class LinkedList{
  public:
  LinkedList(){
    head = nullptr; 
    tail = nullptr;
    size = 0;
  };
  void push_back(T item){
    Node<T>* node = nodeFactory(item);

    if(!head && !tail)
      head = tail = node;

    else if(!tail->next)
      tail = tail->next = node;

    else return;

    size++;
  }
  void insert(int index, T item){
    Node<T>* node = nodeFactory(item);

    if(index == 0){
      node->next = head;
      head = node;
    } 
    else if(index == size){
      push_back(item);
    }
    else{
      Node<T>* curr = nodeFactory();
      Node<T>* prev = nodeFactory();
      
      curr = head;
      prev->next = NULL;
      
      int it = 0;
      while(curr != NULL && it != index){
        prev = curr;
        curr = curr->next;
        it++;
      }

      if(it != index){
        //printLine("ERROR out of bounds!");
      }
      else{
        prev->next = node;
        node->next = curr;
        size++;
      }

    }
  };

  void erase(int index){

    if(index == 0)
      head = head->next;

    else{
      Node<T>* curr = nodeFactory();
      Node<T>* prev = nodeFactory();
      
      curr = head;
      prev->next = NULL;
      
      int it = 0;
      while(curr->next != NULL && it != index){
        prev = curr;
        curr = curr->next;
        it++;
      }

      if(it != index){
        //printLine("ERROR out of bounds!");
      }
      else{
        prev->next = curr->next;
        size--;
      }
    }
  };

  void edit(int index, T item){
    Node<T>* curr = head;
    int it = 0;
    while(curr != NULL && it != index){
      curr = curr->next;
      it++;
    }

    if(it != index){
      //printLine("ERROR out of bounds!");
    }
    else
      curr->item = item;
    
  };
  /*
   * ITERATOR METHODS/ CLASSES
   * (for those range based for loops, ayy)
   */
  class Iterator{

    Node<T>* node;
    int position;

  public:
    Iterator(Node<T>* node):
      node(node){};

    // To dereference and obtain the value
    T& operator*(){ return node->item; }

    // Advance to next node
    Iterator& operator++() {
      node = node->next;
      return *this;
    }
    bool operator != (Iterator& it) { 
      return node != it.node;
    };
  };

  Iterator begin() { return head; };
  Iterator end()   { return tail->next; };
private:
  unsigned int size;
  Node<T>* head;
  Node<T>* tail;
  Node<T>* nodeFactory(T item){
    Node<T>* node = new Node<T>();
    node->item = item;
    return node;
  };
  Node<T>* nodeFactory(){
    return new Node<T>();
  }
};
class Editor{
  private:
    LinkedList<std::string> lines;
    bool isDone;
    /*
     * EDITOR FUNCTIONS
     */
    void insertEnd(std::string line){ /* insert at end of this->lines */ 
      lines.push_back(line);
    };
    void insert(int lineNum, std::string line){ /* insert at lineNum */
      lines.insert(lineNum - 1, line);
    };
    void search(std::string query){ /* print out line that has substr */
      int index = 0;
      bool found = false;
      for(std::string line : lines){
        ++index;
        if(line.find(query) != std::string::npos){
          printLine(std::to_string(index) + " " + line);
          found = true;
        }
      }
      if(!found)
        printLine("not found");
    };
    void edit(int lineNum, std::string line){ /* replace node at lineNum with line */
      lines.edit(lineNum - 1, line);
    };
    void deleteLine(int lineNum){ /* delete node at lineNum */
      // Offset by one because lines are 1 index while we are 0
      if(lineNum > 0)
        lines.erase(lineNum - 1);
      //else
        //printLine("ERROR lines start from 1");

    };
    void print(){ /* print values of each node in list on each line */
      int index = 0;
      for(auto line : lines)
	printLine(std::to_string(++index) + " " + line); 
    };
  public:
    Editor():isDone(false){};
    void interpretCommand(std::string command){ 
      std::vector<std::string> splits = splitUntil(command, ' ', command.find("\""));
      std::string operation = splits[0];

      if(operation == "insertEnd")
        insertEnd(strip(splits[1], '"'));
      
      else if(operation == "insert")
        insert(stoi(splits[1]), 
               strip(splits[2], '"'));
      
      else if(operation == "search")
        search(strip(splits[1], '"'));
      
      else if(operation == "edit")
        edit(stoi(splits[1]),
             strip(splits[2], '"'));
      
      else if(operation == "delete")
        deleteLine(stoi(splits[1]));

      else if(operation == "print")
        print();
      
      else if(operation == "quit")
        isDone = true;
      
      else
        printLine("Unknown operation " + operation);

    };
    bool done(){ return isDone; };
};
int main(){
  Editor editor;
  std::string line;
  while(!editor.done() && std::getline(std::cin, line)){
    editor.interpretCommand(line);
  }
  return 0;
}
