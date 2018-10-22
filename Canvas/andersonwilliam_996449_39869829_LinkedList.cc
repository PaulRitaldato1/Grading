#include <initializer_list>
#include <iterator>
#include <utility>
#include <iostream>

template <class T>
class ListIterator;

template <class T>
class Node;

template <class T>
class LinkedList {

    public:

        LinkedList() {};

        LinkedList(std::initializer_list<T> list) {
            for (auto element : list) {
                add(element);
            }
        }

        int getSize() const {
            return size;
        }

        bool isEmpty() const {
            return size == 0;
        }

        void clear() {
            while (head != nullptr) {
                Node<T> *node = head;
                head = head->next;
                delete node;
            }
            tail = nullptr;
        }

        T get(int index) const {
            return getNode(index)->value;
        }

        T getFirst() const {
            return head->value;
        }

        T getLast() const {
            return tail->value;
        }

        void add(T element) {
            linkLast(element);
        }

        void addFirst(T element) {
            linkFirst(element);
        }

        void addLast(T element) {
            linkLast(element);
        }

        void remove(int index) {
            unlink(getNode(index));
        }

        void removeFirst() {
            unlinkFirst();
        }

        void removeLast() {
            unlinkLast();
        }

        void set(int index, T element) {
            getNode(index)->value = element;
        }

        void insert(int index, T element) {
            if (index == size) {
                linkLast(element);
            } else {
                linkBefore(getNode(index), element);
            }
        }

        int indexOf(T element) const {
            int idx = 0;
            Node<T> *node = head;
            while (node != nullptr) {
                if (node->value == element) {
                    return idx;
                }
                idx++;
                node = node->next;
            }
            return -1;
        }

        bool contains(T element) const {
            return indexOf(element) != -1;
        }

        ListIterator<T> begin() {
            return ListIterator<T>(head);
        }

        ListIterator<T> end() {
            return ListIterator<T>(nullptr);
        }

    private:

        int size = 0;
        Node<T> *head = nullptr, *tail = nullptr;

        Node<T> *getNode(int index) const {
            Node<T> *node;
            if (index < size / 2) {
                node = head;
                for (int i = 0; i < index; i++) {
                    node = node->next;
                }
            } else {
                node = tail;
                for (int i = size - 1; i > index; i--) {
                    node = node->prev;
                }
            }
            return node;
        }

        void linkFirst(T element) {
            Node<T> *node = new Node<T>(element);
            if ((node->next = head) != nullptr) {
                head->prev = node;
            } else {
                tail = node;
            }
            head = node;
            size++;
        }

        void linkLast(T element) {
            Node<T> *node = new Node<T>(element);
            if ((node->prev = tail) != nullptr) {
                tail->next = node;
            } else {
                head = node;
            }
            tail = node;
            size++;
        }

        void linkBefore(Node<T> *before, T element) {
            Node<T> *node = new Node<T>(element);
            node->next = before;
            if ((node->prev = before->prev) != nullptr) {
                node->prev->next = node;
            } else {
                head = node;
            }
            before->prev = node;
            size++;
        }

        void unlink(Node<T> *node) {
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            } else {
                tail = node->prev;
            }
            if (node->prev != nullptr) {
                node->prev->next = node->next;
            } else {
                head = node->next;
            }
            size--;
        }

        void unlinkFirst() {
            if (head != nullptr) {
                if ((head = head->next) != nullptr) {
                    head->prev = nullptr;
                }
                size--;
            }
        }

        void unlinkLast() {
            if (tail != nullptr) {
                if ((tail = tail->prev) != nullptr) {
                    tail->next = nullptr;
                }
                size--;
            }
        }

};

template <class T>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<int, T>> {

    public:

        explicit ListIterator(Node<T> *node) : node(node) {};

        T getValue() const {
            return node->value;
        }

        int getIndex() const {
            return index;
        }

        std::pair<int, T> operator*() const {
            return std::pair<int, T>(index, node->value);
        };

        ListIterator<T> operator++() {
            node = node->next;
            index++;
            return *this;
        }

        ListIterator<T> operator--() {
            node = node->prev;
            index--;
            return *this;
        }

        const ListIterator<T> operator++(int) {
            ListIterator<T> copy(node);
            operator++();
            return copy;
        }

        const ListIterator<T> operator--(int) {
            ListIterator<T> copy(node);
            operator--();
            return copy;
        }

        bool operator==(const ListIterator<T> &other) const {
            return node == other.node;
        }

        bool operator!=(const ListIterator<T> &other) const {
            return !operator==(other);
        }

    private:

        int index = 0;
        Node<T> *node;

};

template <class T>
class Node {

        friend class LinkedList<T>;
        friend class ListIterator<T>;

    public:

        explicit Node(T value) : value(value) {};

    private:

        T value;
        Node<T> *next = nullptr, *prev = nullptr;

};