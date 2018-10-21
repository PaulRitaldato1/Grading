#include <string>
#include <iostream>

template <typename T>
class List {

    private:

        struct Node {
            T data;
            Node* prev;
            Node* next;

            Node() {
                prev = nullptr;
                next = nullptr;
                data = T();
            }
        };
        
    public:

        class const_iterator {

            public: 
                const_iterator() : current(nullptr) {}

                const T& operator* () const {
                    return retrieve();
                }

                const_iterator& operator++ () {
                    current = current->next;
                    return *this;
                }

                const_iterator operator++ (int) {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }

                const_iterator& operator-- () {
                    current = current->prev;
                    return *this;
                }

                const_iterator operator-- (int) {
                    const_iterator old = *this;
                    --(*this);
                    return old;
                }

                bool operator== (const const_iterator& rhs) const {
                    return current == rhs.current;
                }

                bool operator!= (const const_iterator &rhs) const {
                    return !(*this == rhs);
                }

            protected:
                Node* current;

                T& retrieve() const {
                    return current->data;
                }

                const_iterator(Node*p) : current(p) {}

                friend class List<T>;

        };

        class iterator : public const_iterator {

            public:

                iterator() {}

                T& operator*() {
                    return const_iterator::retrieve();
                }

                const T& operator* () const {
                    return const_iterator::operator*();
                }

                iterator& operator++() {
                    this->current = this->current->next;
                    return *this;
                }

                iterator operator++(int) {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }

                iterator& operator--() {
                    this->current = this->current->prev;
                    return *this;
                }

                iterator operator--(int) {
                    iterator old = *this;
                    --(*this);
                    return old;
                }

            protected:

                iterator(Node* p) : const_iterator(p) {}

                friend class List<T>;

        };

        List() {
            init();
        }
    
        ~List() {
            clear();
            delete head;
            delete tail;
        }

        iterator begin() {
            return (head->next);
        }

        iterator end() {
            return (tail);
        }

        const_iterator begin() const {
            return (head->next);
        }

        const_iterator end() const {
            return (tail);
        }
    
        T& back() {
            return *(--end());
        }
    
    
        T& front() {
            return *(begin());
        }
    
        void push_back(const T& data) {
            insert(--end(), data);
        }
    
        void push_front(const T& data) {
            insert(begin(), data);
        }
    
        void pop_back() {
            if (tail->prev != head) {
                Node* temp = tail->prev;
                tail->prev = temp->prev;
                delete temp;
                listSize--;
            };
        }
    
        void pop_front() {
            if (head->next != tail) {
                Node* temp = head->next;
                head->next = temp->next;
                delete temp;
                listSize--;
            };
        }
        
        iterator insert(iterator itr, const T &data) {
            Node* targetNode = itr.current;
            
            Node* newNode = new Node();
            newNode->data = data;

            newNode->prev = targetNode;
            newNode->next = targetNode->next;
            targetNode->next->prev = newNode;
            targetNode->next = newNode;
            
            

            listSize++;
            

            return iterator(newNode);
        }
        
        iterator remove(iterator itr) {
            Node* targetNode = itr.current;
            Node* returnNode = targetNode->next;

            targetNode->prev->next = targetNode->next;
            targetNode->next->prev = targetNode->prev;
            
            delete targetNode;

            listSize--;

            return iterator(returnNode);
        }
    
        bool empty() const {
            return listSize ==  0;;
        }
    
        void clear() {
            while (!empty()) {
                pop_front();
            }
            listSize = 0;
        }
        
        int size() {
            return listSize;
        }
    
    private:

        int listSize;
        Node* head;
        Node* tail;
    
        void init() {
            listSize = 0;
            head = new Node();
            tail = new Node();
            head->next = tail;
            tail->prev = head;
        }
    
};

class LineEditor {
    private:
        List<std::string>* list;
    
    public:
        LineEditor() {
            list = new List<std::string>();
        }
    
        void insertEnd(std::string str) {
            list->push_back(str);
        }
    
        void search(std::string str) {
            int index = 1;
            bool found = false;

            for (List<std::string>::iterator itr = list->begin(); itr != list->end(); ++itr) {
                if (std::string(*itr).find(str) != std::string::npos) {
                    std::cout << index << " " << *itr << std::endl;
                    found = true;
                }
                index++;
            }
            
            if (!found) {
                std::cout << "not found" << std::endl;
            }
        }
    
        void edit(int line, std::string str) {
            if (line >= 1 && line <= list->size()) {
                deleteAt(line);
                insertAt(line, str);
            }
        }
    
        void insertAt(int line, std::string str) {
            if (line >= 1 && line <= list->size() + 1) {
                List<std::string>::iterator itr = list->begin();



                for (int i = 1; i < line - 1; i++) {
                    itr++;
                }

                list->insert(itr, str);
            }
        }
    
        void deleteAt(int line) {
            if (line >= 1 && line <= list->size() ) {
                List<std::string>::iterator itr = list->begin();

                for (int i = 1; i < line; i++) {
                    itr++;
                }

                list->remove(itr);
            }
        }
    
        void print() {
            int index = 1;
            
            for (List<std::string>::iterator itr = list->begin(); itr != list->end(); ++itr) {
                std::cout << index << " " << *itr << std::endl;
                index++;
            }
        }
};

int main()
{
    LineEditor editor = LineEditor();

    std::string arg[2] = {};

    while (arg[0] != "quit") {

        std::cin >> arg[0];

        if (arg[0] == "insertEnd") {

            std::cin.ignore(100, '\"');
            std::getline(std::cin, arg[1], '\"');

            editor.insertEnd(arg[1]);

        } else if (arg[0] == "edit") {
            
            std::cin >> arg[1];
            std::cin.ignore(100, '\"');
            std::getline(std::cin, arg[2], '\"');
            
            editor.edit(std::stoi(arg[1]), arg[2]);

        } else if (arg[0] == "insert") {
            
            std::cin >> arg[1];
            std::cin.ignore(100, '\"');
            std::getline(std::cin, arg[2], '\"');
            
            editor.insertAt(std::stoi(arg[1]), arg[2]);
            
        } else if (arg[0] == "delete") {
            
            std::cin >> arg[1];
            
            editor.deleteAt(std::stoi(arg[1]));
            
        } else if (arg[0] == "search") {
            
            std::cin.ignore(100, '\"');
            std::getline(std::cin, arg[1], '\"');

            editor.search(arg[1]);
            
        } else if (arg[0] == "print") {

            editor.print();
            
        } else if (arg[0] == "quit") {
            
        }

    }

    return 0;

}