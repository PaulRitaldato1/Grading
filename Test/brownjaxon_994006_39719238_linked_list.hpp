#pragma once
#include "linked_list.h"

template<typename T>
Linked_List<T>::Linked_List() : size(0) {

}

template<typename T>
void Linked_List<T>::push_back(T val) {
    LLNode* newNode = new LLNode;
    newNode->val = val;
    newNode->next = nullptr;

    if(tail == nullptr) {
        newNode->last = nullptr;
        head = newNode;
        tail = newNode;
    } else {
        newNode->last = tail;
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

template<typename T>
void Linked_List<T>::push_front(T val) {
    LLNode* newNode = new LLNode;
    newNode->val = val;
    newNode->last = nullptr;

    if(head == nullptr) {
        newNode->next = nullptr;
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->last = newNode;
        head = newNode;
    }

    size++;
}

template<typename T>
typename Linked_List<T>::LLNode* Linked_List<T>::nodeAt(int index) {
    LLNode* node;
    if(index > size / 2) {
        node = tail;
        for(int i = 0; i < size - index - 1; i++) {
            if(node == nullptr) return nullptr;
            node = node->last;
        }
    } else {
        node = head;
        for(int i = 0; i < index; i++) {
            if(node == nullptr) return nullptr;
            node = node->next;
        }
    }
    return node;
}

template<typename T>
bool Linked_List<T>::insert(int index, T val) {
    LLNode* node = nodeAt(index);
    if(node == nullptr) return false;

    LLNode* newNode = new LLNode;
    newNode->val = val;
    newNode->last = node->last;
    newNode->next = node;

    node->last->next = newNode;
    node->last = newNode;

    size++;
    return true;
}

template<typename T>
bool Linked_List<T>::modify(int index, T val) {
    LLNode* node = nodeAt(index);
    if(node == nullptr) return false;

    node->val = val;
    return true;
}

template<typename T>
bool Linked_List<T>::remove_back() {
    LLNode* remNode = tail;
    if(remNode == nullptr)
        return false;

    if(remNode->last != nullptr) {
        remNode->last->next = nullptr;
        tail = remNode->last;
    } else {
        head = nullptr;
        tail = nullptr;
    }

    delete remNode;

    size--;
    return true;
}

template<typename T>
bool Linked_List<T>::remove_front() {
    LLNode* remNode = head;
    if(remNode == nullptr)
        return false;

    if(remNode->next != nullptr) {
        remNode->next->last = nullptr;
        head = remNode->next;
    } else {
        head = nullptr;
        tail = nullptr;
    }

    delete remNode;

    size--;
    return true;
}

template<typename T>
bool Linked_List<T>::remove(int index) {
    LLNode* remNode = nodeAt(index);
    if(remNode == nullptr)
        return false;

    if(remNode->next != nullptr)
        remNode->next->last = remNode->last;
    else
        tail = remNode->last;

    if(remNode->last != nullptr)
        remNode->last->next = remNode->next;
    else
        head = remNode->next;

    delete remNode;

    size--;
    return true;
}

template<typename T>
typename Linked_List<T>::iterator Linked_List<T>::begin() {
    return Linked_List::iterator(head);
}

template<typename T>
typename Linked_List<T>::iterator Linked_List<T>::end() {
    return Linked_List::iterator(nullptr);
}

template<typename T>
bool Linked_List<T>::LLIterator::operator==(const Linked_List::LLIterator& other) {
    return loc == other.loc;
}

template<typename T>
bool Linked_List<T>::LLIterator::operator!=(const Linked_List::LLIterator& other) {
    return loc != other.loc;
}

template<typename T>
typename Linked_List<T>::LLIterator& Linked_List<T>::LLIterator::operator++() {
    if(loc != nullptr) {
        loc = loc->next;
    }
    return *this;
}

template<typename T>
typename Linked_List<T>::LLIterator& Linked_List<T>::LLIterator::operator++(int i) {
    return operator++();
}

template<typename T>
typename Linked_List<T>::LLIterator& Linked_List<T>::LLIterator::operator--() {
    if(loc != nullptr) {
        loc = loc->last;
    }
    return *this;
}

template<typename T>
typename Linked_List<T>::LLIterator& Linked_List<T>::LLIterator::operator--(int i) {
    return operator--();
}

template<typename T>
T& Linked_List<T>::LLIterator::operator*() {
    return loc->val;
}
