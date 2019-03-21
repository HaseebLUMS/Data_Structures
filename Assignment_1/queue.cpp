#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue)
{
	LinkedList<T> otherList = otherQueue.list;
	ListItem<T>* tmp = otherList.getHead();
	while(tmp)
	{
		list.insertAtTail(tmp->value);
		tmp = tmp->next;
	}
}

template <class T>
Queue<T>::~Queue()
{
	while(list.length())
	{
		list.deleteTail();
	}
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	return (list.getHead())->value;
}

template <class T>
T Queue<T>::dequeue()
{
	T tmp = (list.getHead())->value;
	list.deleteHead();
	return tmp;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	if(list.length > 0)
		return 1;
	return 0;
}


#endif
