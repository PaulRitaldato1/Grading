#ifndef LINKEDEDITOR_H_
#define LINKEDEDITOR_H_


template<class T>
class Node {
public:
	T data;
	Node<T> * next;
};

template <class T>
class LinkedList{
private:
	Node<T> * head;
	Node<T> * tail;
public:
	void insertEnd(T value);
	void insert(int index, T value);
	void edit(int index, T value);
	void remove(int index);
	void print();
	void find(string value);
};



#endif /* LINKEDEDITOR_H_ */
