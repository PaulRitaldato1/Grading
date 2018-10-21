//
// Created by Owner on 9/15/2018.
//
#include <string>
#include <iostream>
#include <sstream>

struct Node
{
    Node(const std::string &v, Node *n, Node *pr) : value(v), next(n), prev(pr)
    {}

public:
    std::string value;
    Node *next;
    Node *prev;
};

class const_iterator
{
public:
    const_iterator() : current{nullptr}  // initializer
    {}
    const std::string & operator*() const
    {
        return retrieve();
    }    // return string value in current node
    const_iterator & operator++()
    {
        current = current->next;
        return *this;
    } // current equals next node
protected:
    Node *current;
    std::string & retrieve() const
    {
        return current->value;
    }    //returns string at current node
    const_iterator(Node *p) : current{p} //iterator at specified node
    {}
    friend class List;
};


class iterator : public const_iterator
{
public:
    iterator() = default;       // initializer
    std::string & operator*()
    {
        return const_iterator::retrieve();
    }             // return string at current node
    const std::string & operator*() const
    {
        return const_iterator::operator*();
    } // return string at current node
    iterator & operator++()
    {
        this->current = this->current->next;
        return *this;
    }               // current equals next node
    void setValue(std::string s)
    {
        current->value = std::move(s);
    }

protected:
    iterator(Node *p) : const_iterator{p}       // iterator starts at p
    {}
    friend class List;

};



class List
{
    private:            // do I want this private or public? How will I iterate if I can't access, or can I access?
        Node *head;     // pointer to first line of the document
        Node *tail;     // pointer to last line of the document
        int mySize;     // size of list

    public:
    List()      // initialize private values
    {
        head = nullptr;
        tail = nullptr;
        mySize = 0;
    }
    iterator begin()        //return head
    {
        return {head};
    }

    iterator end()      //return tail
    {
        return {tail};
    }

    void push_front(const std::string &x)   // uses insert with string parameter. in insert. make new head. create new node within method. increment size.
    {
       Node *temp = new Node{head->value, head, nullptr};
       head->prev = temp;
       insert(temp, x);
       head = temp->next;
       delete (temp);
    }

    void push_back(const std::string &x)    // uses insert with string parameter. make new tail. create node within method. increment size.
    {
        insert(end(), x);
    }

    void insert(iterator it, const std::string &x)  // creates a new node and adds it after iterator. for inserting in between, the intMid method finds it then calls insert. iterator parameter is begin() when coming from push_front
    {
        if(it.current != nullptr)
        {
            Node *p = it.current;
            Node *add = new Node{x, p->next, p};
            if(p->next != nullptr)
              p->next = p->next->prev = add;
            else
            {
              p->next = add;
              tail = add;
            }
        }
        else
        {
          Node *add = new Node{x, nullptr, nullptr};
          head = add;
          tail = add;
        }
        mySize++;
    }
    void erase(iterator it)     // remove node at iterator. delete node at it
    {
        Node *p = it.current;
        p->prev->next = p->next;
        if(p != tail)
            p->next->prev = p->prev;
        mySize--;
        delete p;
}
    int size()      //size of list
    {
        return mySize;
    }

};



void InsertEnd(List &myList, std::string add)   //use push_back
{
    myList.push_back(add);
}

void instMid(List &myList, std::string add, int loc)  // find it and call insert
{
    iterator it = myList.begin();

    if(loc == myList.size() + 1)
        InsertEnd(myList, add);
    else if(loc < myList.size() + 1 && loc > 1)
    {
        for (int i = 0; i < loc - 2; i++)
        {
            it.operator++();
        }

        myList.insert(it, add);
    }
    else if(loc == 1)
    {
        myList.push_front(add);
    }
}

void del(List &myList, int loc)     // find it and call erase
{
    if(loc > 0 && loc <= myList.size())
    {
        iterator it = myList.begin();

        for (int i = 0; i < loc - 1; i++) {
            it.operator++();
        }

        myList.erase(it);
    }
}

void edit(List &myList, std::string add, int loc)   // change value of string at current
{
    iterator it = myList.begin();


    for(int i = 0; i < loc-1; i++)
    {
        it.operator++();
    }

    it.setValue(add);

}

void search(List &myList, std::string look)     // print line every time it is found
{
    iterator it = myList.begin();
    std::string itVal;
    int count = 0;

    for(int i = 0; i < myList.size(); i++)
    {
        itVal = *it;

        if(itVal.find(look) != std::string::npos)
        {
            std::cout << i+1 << " " << itVal << std::endl;
            count = i+1;
        }

        it.operator++();

    }

    if(count == 0)
        std::cout << "not found" << std::endl;

}

std::string reduce(std::string add)     // remove quotations from string
{
    int first;
    int last;
    first = add.find_first_of('\"');
    last = add.find_last_of('\"');
    add = add.substr(first + 1, last - first - 1);
    return add;
}


//take in first word with one cin
//decide what type of variable to take in after reading
//can use getline to insert a phrase
int main()
{
    List myList;

    bool cont = true;
    std::string call;
    std::string add;
    int loc;
    Node *track;

    while(cont)
    {
        std::cin >> call;

        if(call == "quit")
            cont = false;
        else if(call == "insertEnd")
        {
            getline(std::cin, add);
            add = reduce(add);
            if(add.size() <= 80)
                InsertEnd(myList, add);
        }
        else if(call == "insert")
        {
            std::cin >> add;
            std::stringstream(add) >> loc;
            getline(std::cin, add);
            add = reduce(add);
            if(add.size() <= 80)
                instMid(myList, add, loc);
        }
        else if(call == "search")
        {
            getline(std::cin, add);
            add = reduce(add);
            if(add.size() <= 80)
                search(myList, add);
        }
        else if(call == "edit")
        {
            std::cin >> add;
            std::stringstream(add) >> loc;
            getline(std::cin, add);
            add = reduce(add);
            if(add.size() <= 80)
                edit(myList, add, loc);
        }
        else if(call == "print")
        {
            iterator it = myList.begin();

            for(int i = 0; i < myList.size(); i++)
            {
                std::cout << i+1 << " " << *it << std::endl;
                it.operator++();
            }
        }
        else if(call == "delete")
        {
            std::cin >> add;
            std::stringstream(add) >> loc;
            del(myList, loc);
        }
        else
        {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }


}