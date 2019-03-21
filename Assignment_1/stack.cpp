#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
	//list = new LinkedList<T>();
}
    
template <class T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
	//list = LinkedList<T>(otherStack.list);
	LinkedList<T> otherList = otherStack.list;
	ListItem<T>* tmp = otherList.getHead();
	while(tmp)
	{
		list.insertAtTail(tmp->value);
		tmp = tmp->next;
	}
}

template <class T>
Stack<T>::~Stack()
{
	while(list.length())
	{
		list.deleteTail();
	}
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Stack<T>::top()
{
	return (list.getTail())->value;
}

template <class T>
T Stack<T>::pop()
{
	if (length() == 0)
		return NULL;
	T tmp = top();
	list.deleteTail();
	return tmp;
}

template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
	if(list.length() < 1)
		return 1;
	return 0;
}

#endif
