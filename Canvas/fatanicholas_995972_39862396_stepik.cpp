#include<string>
#include<iostream>

/*
 Node class which includes two parameters:
 std::string text: the text that is in the line represented by the Node in the linked list
 Node* next: the node that follows this node in the linked list. Its default value is NULL, that is, it's the last node in the linked list.
 */
class Node
{
public:
    std::string text;
    Node* next = NULL;
};

/*
 The Linked List class implements a linked list composed of a series of nodes, starting with the head.
 Its one class variable, head, is a reference to the Node that is the first node of the linked list, so when a linked list is first initialized, its default value is NULL until the first Node is placed into the list.
 This class include methods which insert, edit, delete, and find particular Nodes based on their text or the line number specified by the LineEditor.
 */
class LinkedList
{
public:
    // A reference to the first Node in the linked list.
    Node* head = NULL;
    
    // Inserts a new Node at the end of the linked list with the specified text passed in as the parameter text.
    void insertEnd(std::string text)
    {
        // Initializes a new Node called newText, which is the Node to be inserted at the end of the linked list. Also initailizes a Node called current, which keeps track of the current Node in the traversal, which is currently the head of the list.
        Node* current = head;
        Node* newText = new Node();
        newText->text = text;
        
        // If the head is a NULL reference, then the newText Node will become the head of the linked list, if not, the list is traversed until the current Node's next node is a NULL reference, where the NULL reference will be replaced by the newText Node reference.
        if (current == NULL)
        {
            head = newText;
        }
        else
        {
            while(current->next != NULL)
            {
                current = current->next;
            }
            
            current->next = newText;
        }
    }
    
    // Inserts a new Node with the specified text at a specific position of the linked list specified by the lineNumber parameter, where 1 is the beginning of the linked list.
    void insert(std::string text, int lineNumber)
    {
        // Initializes a new Node called newText, which is the Node to be inserted at the specified position of the linked list. Also initailizes a Node called current, which keeps track of the current Node in the traversal, which is currently the head of the list, and a Node called previous, set to NULL, which tracks the Node that precedes the current Node.
        Node* previous = NULL;
        Node* current = head;
        Node* newText = new Node();
        newText->text = text;
        
        // Traverses the linked list starting at position 1, incrementing until the position is equal to the specified position in the parameter of this method, where the previous Node's next reference will be set to the newText Node and the newText Node's next Node reference will be set to the current Node. Traversal ceases once the position is found. If the position is 1, then the newNoe becomes the head of the linked list.
        if (lineNumber == 1)
        {
            head = newText;
            newText->next = current;
            return;
        }
        
        previous = current;
        current = current->next;
        int i = 2;
        
        while(current != NULL)
        {
            if (i == lineNumber)
            {
                previous->next = newText;
                newText->next = current;
                return;
            }
            
            previous = current;
            current = current->next;
            i++;
        }
        
        if (i == lineNumber)
        {
            previous->next = newText;
        }
    }
    
    // Traverses the entire linked list and prints the line number and line text of the Node that contains text which includes the string passed in as the parameter text.
    void search(std::string text)
    {
        // Initializes the current Node to be a reference to the head of the linked list.
        Node* current = head;
        
        // Initializes a boolean found to false, representing whether a line of text contai ning the specified text was found.
        bool found = false;
        
        // Traverses the linked list starting at position 1, incrementing until the text of the current Node contains the specified text in the parameter of the method. If there is a match, the line number and line text are printed to the command line, and traversal ceases.
        for(int i = 1; current != NULL; i++)
        {
            if(current->text.find(text) != std::string::npos)
            {
                std::cout << i << " " << current->text << "\n";
                found = true;
            }
            
            current = current->next;
        }
        
        // If the entire loop is traversed without a match, the text "Not Found" is printed.
        if (!found)
            std::cout << "not found" << "\n";
    }
    
    // Edits the text of a Node at the position specified by lineNumber, by replacing its current text with the text passed in as the parameter text.
    void edit(std::string text, int lineNumber)
    {
        // Initializes the current Node to be a reference to the head of the linked list.
        Node* current = head;
        
        // Traverses the linked list starting at position 1, incrementing until the position is equal to the specified position in the parameter of this method, where the text of the current Node is then set to the new text passed in as the text parameter of this method. Traversal ceases once the position is found.
        for (int i = 1; current != NULL; i++)
        {
            if (i == lineNumber)
            {
                current->text = text;
                return;
            }
            
            current = current->next;
        }
    }
    
    // Deletes a Node in the linked list based on the position specified by the lineNumber parameter.
    void deleteEntry(int lineNumber)
    {
        // Initailizes a Node called current, which keeps track of the current Node in the traversal, which is currently the head of the list, and a Node called previous, set to NULL, which tracks the Node that precedes the current Node.
        Node* current = head;
        Node* previous = NULL;
        
        // Traverses the linked list starting at position 1, incrementing until the position is equal to the specified position in the parameter of this method, where the previous Node's next Node is assigned to the reference of the current Node's next Node. Traversal ceases once the position is found. If the position of deletion is 1, then the head Node is deleted and the head is assigned to the reference of the next node.
        if (lineNumber == 1)
        {
            head = current->next;
            return;
        }
        
        previous = current;
        current = current->next;
        
        for(int i = 2; current != NULL; i++)
        {
            if (i == lineNumber)
            {
                previous->next = current->next;
                current->next = NULL;
                return;
            }
            
            previous = current;
            current = current->next;
        }
    }
    
    // Traverses the entire linked list and prints out the position (line number) and text of each node.
    void printList() {
        
        Node* current = head;
        
        for(int i = 1; current != NULL; i++)
        {
            std::cout << i << " " << current->text << "\n";
            current = current->next;
        }
        
    }
};

int main()
{
    // Declares and initializes a new LinkedList called line editor, which will be the line editor of this program.
    LinkedList* lineEditor = new LinkedList();
    
    // While the "quit" command is not entered, this loop will continue to accept input indefinitely.
    while (true)
    {
        // Declares string variables which will hold various aspects of each command line input.
        std::string query, command, arg1, arg2, arguments;
        
        // The string query is initializes with the entire command line input.
        std::getline(std::cin, query);
        
        // Checks whether the command line input is either quit or print. If so the entire string query is the command. If not, the various arguments need to be parsed based on command.
        if (query.find("quit") != std::string::npos || query.find("print") != std::string::npos)
        {
            command = query;
        }
        else {
            
            // Since there is a space between the command and its arguments, the first space is found and is used to determine the length of the substring which contains just the string of the command, and then the string command is initialized to this substring.
            std::size_t posOfSpace = query.find(" ");
            command = query.substr(0, posOfSpace);
            
            // After the command substring is initialized, the string arguments is initialized to the rest of the input, and is parsed further based on command type.
            posOfSpace += 1;
            arguments = query.substr(posOfSpace);
            
            // If the command is an insert or edit command, there will be two arguments, a number and text enclosed in quotes. The string arg1 is initialized to the number string and the string arg2 is initialized to the text in the quotes.
            if ((command.find("insert") != std::string::npos && command.find("End") == std::string::npos) || command.find("edit") != std::string::npos)
            {
                std::size_t argSpace = arguments.find(" ");
                arg1 = arguments.substr(0, argSpace);
                arg2 = arguments.substr(argSpace+2, (arguments.length() - argSpace - 3));
            }
            // If the command is a delete command, then there is only a number argumnet, so the string arg1 is initialized to the number string.
            else if (command.find("delete") != std::string::npos)
            {
                arg1 = arguments;
            }
            // If the command is an insertEnd or search command, the only argument is the text to insert at the end of the list or to find in the list, so string arg1 is initialized to the text inside the quotes.
            else
            {
                arg1 = arguments.substr(1, (arguments.length() - 2));
            }
            
        }
        
        // These conditional statements figure out which command was specified in the command line input, and then call the specific LinkedList method based on the command specified, with their corresponding parsed arguments, if applicable. If the command is quit, execution terminates. If the command is invalid, the text "Invalid input" is printed and execution continues.
        if (command.find("quit") != std::string::npos)
            return 0;
        else if (command.find("End") != std::string::npos)
            lineEditor->insertEnd(arg1);
        else if (command.find("insert") != std::string::npos)
            lineEditor->insert(arg2, std::stoi(arg1, nullptr));
        else if (command.find("delete") != std::string::npos)
            lineEditor->deleteEntry(std::stoi(arg1, nullptr));
        else if (command.find("print") != std::string::npos)
            lineEditor->printList();
        else if (command.find("edit") != std::string::npos)
            lineEditor->edit(arg2, std::stoi(arg1, nullptr));
        else if (command.find("search") != std::string::npos)
            lineEditor->search(arg1);
        else
        {
            std::cout << "Invalid input." << "\n";
            continue;
        }
    }
    
    return 0;
}
