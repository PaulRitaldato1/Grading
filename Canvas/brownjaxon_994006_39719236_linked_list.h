#pragma once
#include <iterator>

/**
 * Implements a doubly linked list
 * @tparam T data type to store
 */
template<typename T>
class Linked_List {
private:
    /**
     * Represents a node of the linked list
     * Links forwards and backwards
     */
    struct LLNode {
        LLNode* next;
        LLNode* last;
        T val;
    };

    /**
     * Implements an iterator to step through the items in the linked list
     */
    class LLIterator {
    private:
        LLNode* loc;

    public:
        /**
         * Setup iterator
         * @param loc position to start the iterator
         */
        explicit LLIterator(LLNode* loc) : loc(loc) {}
        inline bool operator==(const LLIterator& other);
        inline bool operator!=(const LLIterator& other);
        inline LLIterator& operator++();
        inline LLIterator& operator++(int i);
        inline LLIterator& operator--();
        inline LLIterator& operator--(int i);
        inline T& operator*();
    };


    LLNode* head = nullptr; // Head of the linked list
    LLNode* tail = nullptr; // Tail of the linked list
    int size; // Size of the linked list (for optimization of RRWs)

    /**
     * Finds the node at an index
     * @param index index to search for node
     * @return node at specified index, nullptr if index doesn't exist
     */
    LLNode* nodeAt(int index);

public:
    /**
     * Iterator to step through items in the linked list
     */
    typedef LLIterator iterator;

    /**
     * Construct a linked list
     */
    Linked_List();
    /**
     * Put value at the end of the linked list
     * @param val value to add to the linked list
     */
    void push_back(T val);
    /**
     * Put value at the beginning of the linked list
     * @param val value to add to the linked list
     */
    void push_front(T val);
    /**
     * Put value at index of the linked list
     * @param index index to insert at. The value will end up at this index
     * @param val value to add to the linked list
     * @return true if successful
     */
    bool insert(int index, T val);
    /**
     * Replace value at index of the linked list
     * @param index index to replace
     * @param val value to replace with
     * @return true if successful
     */
    bool modify(int index, T val);
    /**
     * Remove the last item in the linked list
     * @return true if something was removed
     */
    bool remove_back();
    /**
     * Remove the first item in the linked list
     * @return true if something was removed
     */
    bool remove_front();
    /**
     * Remove the item at index
     * @param index index of item to remove
     * @return true if something was removed
     */
    bool remove(int index);
    /**
     * Get iterator for the beginning of the linked list
     * @return iterator at the first item
     */
    iterator begin();
    /**
     * Get iterator fot the end of the linked list
     * @return iterator for nullptr
     */
    iterator end();
};

#include "linked_list.hpp"