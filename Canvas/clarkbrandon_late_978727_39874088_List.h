#ifndef LIST_H
#define LIST_H
#include <string>


class List{
    private:
        typedef struct node{
            std::string data;
            node* next; 
        }* nodePtr;
    nodePtr head; 
    nodePtr temp;

    public:
        List(); 
        void InsertEnd(std::string input);
        void InsertLine(int lineNum, std::string input);
        void DeleteLine(int lineNum);
        void PrintList();
        void EditLine(int lineNum, std::string data);
        void Search(std::string input); 
};
#endif