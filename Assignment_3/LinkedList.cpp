#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"


#include <iostream>
using namespace std;


template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	ListItem<T>* tmp =  otherLinkedList.head;
	if(tmp == NULL)
	{
		head = NULL;
		return;
	}
	head = NULL;
	while(tmp != NULL)
	{
		insertAtTail(tmp->value);
		tmp = tmp->next;
	}


}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T>* tmp = head;
	while(tmp)
	{
		ListItem<T>* tmp2 = tmp->next;
		delete tmp;
		tmp = tmp2;
	}
}
template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T>* newNode = new ListItem<T>(item);

	ListItem<T>* tmp = head;
	if (head == NULL)
	{
		head = newNode;

		return;
	}
	head = newNode;
	newNode->next = tmp;
	newNode->prev = NULL;
	newNode->next->prev = newNode;
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	ListItem<T>* tmp = head;
	ListItem<T>* newNode = new ListItem<T>(item);
	if(head == NULL)
	{
		insertAtHead(item);
		return;
	}
	while(tmp -> next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = newNode;
	newNode->next = NULL;
	newNode->prev = tmp;
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	if(head == NULL)
	{
		insertAtHead(toInsert);
		return;
	}
	ListItem<T>* tmp = new ListItem<T>(toInsert);
	ListItem<T>* after = head;
	while(after->value != afterWhat && after->next != NULL)
	{
		after = after->next;
	} 
	if(after->next == NULL)
	{
		insertAtTail(toInsert);
		return;
	}
	tmp->next = after->next;
	after->next = tmp;
	tmp->next->prev = tmp;
	tmp->prev = after;
}

template <class T>
void LinkedList<T>::insertSorted(T item)
{
	ListItem<T>* tmp = head;
	ListItem<T>* newNode = new ListItem<T>(item);
	if(head == NULL)
	{
		insertAtHead(item);
		return;
	}
	if(head->value > item)
	{
		insertAtHead(item);
		return;
	}
	if(head->value < item && head->next == NULL)
	{
		insertAtTail(item);
		return;
	}

	while(tmp->next != NULL && tmp->next->value <= item)
	{
		tmp = tmp->next;
	}
	if(tmp->next == NULL)
	{
		insertAtTail(item);
		return;
	}
	insertAfter(item, tmp->value);
	return;

}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	ListItem<T>* tmp = head;
	if(head == NULL)
		return NULL;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return tmp;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	ListItem<T>* tmp = head;
	if (head == NULL)
		return NULL;
	while(tmp->next != NULL && tmp->value != item)
	{
		tmp = tmp->next;
	}
	if (tmp -> value == item)
		return tmp;
	return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	ListItem<T>* tmp = searchFor(item);
	if(tmp == NULL)
	{
		return;
	}
	if(tmp == head)
	{
		deleteHead();
		return;
	}
	if(tmp->next == NULL)
	{
		deleteTail();
		return;
	}
	
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	//delete tmp;
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if (head == NULL)
		return;
	if(head->next == NULL)
	{
		head = NULL;
		return;
	}
	ListItem<T>* tmp = head;
	head = head->next;
	head->prev = NULL;
	delete tmp;
}

template <class T>
void LinkedList<T>::deleteTail()
{
	ListItem<T>* tmp = getTail();
	if(tmp == NULL)
		return;
	if(head->next == NULL)
	{
		deleteHead();
		return;
	}
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	delete tmp;
}

template <class T>
int LinkedList<T>::length()
{
	ListItem<T>* tmp = head;
	int coun=0;
	while(tmp != NULL)
	{
		coun++;
		tmp = tmp->next;
	}
	return coun;
}

template <class T>
void LinkedList<T>::reverse()
{
	if(head == NULL || head->next == NULL)
		return;
	ListItem<T>* tmpT = head;
	ListItem<T>* tmpTT = head;
	int totNodes = 0;
	cout<<"abc"<<endl;
	while(tmpT->next != NULL)
	{
		totNodes++;
		tmpT = tmpT->next;
		
	}
	totNodes++;
	ListItem<T>* tmp = head;
	ListItem<T>* tmp2 = head;
	for(int i=0; i< totNodes ; i++)
	{
		ListItem<T>* tmp3 = tmp->next;
		tmp->next = tmp->prev;
		tmp->prev = tmp3;
		tmp = tmp->prev;
	}
	head = tmpT;

}

template <class T>
void LinkedList<T>::parityArrangement()
{
	ListItem<T>* tmp = head;
	if(head == NULL || head->next == NULL)
		return;
	// if(head ->next->next == NULL)
	// {
	// 	//reverse();
	// 	return;
	// }
	int totNodes=0;
	//cout<<endl;
	while(tmp->next != NULL)
	{
		
		totNodes++;
		tmp = tmp->next;
	}
	totNodes++;
	ListItem<T>* arr[totNodes];
	ListItem<T>* tmpTT = head;
	int i = 0;
	while(tmpTT != NULL)
	{
		arr[i] = tmpTT;
		tmpTT = tmpTT->next;
		i++;
	}

	for(int i=0; i< totNodes; i=i+2)
	{
		if(arr[i]->next != NULL)
		{
			if(i+2 < totNodes)
			arr[i]->next = arr[i+2];
			if(i+2 < totNodes)
			arr[i+2]->prev = arr[i];
			//cout<<"1"<<endl;
		}
	}

	//cout<< "abc"<<endl;
	for(int i=1; i< totNodes-1; i = i+2)
	{
		if(arr[i]->next != NULL && arr[i]->next->next != NULL)
		{
			arr[i]->next = arr[i+2];
			arr[i+2]->prev = arr[i];
		}
	} 
	//cout<<"xyz"<<endl;
	if(totNodes % 2)
	{
		//arr[totNodes-2]->next = arr[0];
		//arr[0]->prev = arr[totNodes-2];
		 arr[totNodes-1]->next = arr[1];
		 arr[1]->prev = arr[totNodes-1];
		arr[totNodes-2]->next = NULL;
		//arr[totNodes-1]->next = NULL;
		//head = arr[1];
	}
	else
	{
		// arr[totNodes-1]->next = arr[0];
		// arr[0]->prev = arr[totNodes-1];
		// arr[totNodes-2]->next = NULL;
		// head = arr[1];
		arr[totNodes-2]->next = arr[1];
		arr[1]->prev = arr[totNodes-2];
		arr[totNodes-1]->next = NULL;
	}

	
}

template <class T>
void LinkedList<T>::print()
{
	ListItem<int>* tmp = head;
	while (tmp !=NULL)
	{
		cout<< tmp->value <<" ";
		tmp = tmp->next;
	}cout<<endl;
}

template <class T>
bool LinkedList<T>::isPalindrome()
{
	ListItem<T>* tmp = getTail();
	ListItem<T>* tmpI= head;
	if(head == NULL)
		return 0;
	while(tmpI)
	{
		if(tmp->value != tmpI->value)
			return 0;
		tmpI = tmpI->next;
		tmp = tmp->prev;
	}
	return 1;
}
#endif

// int main()
// {
// 	LinkedList<int>* l = new LinkedList<int>;
// 	// l->insertAtTail(6);
// 	// l->insertAtTail(6);
// 	// l->insertAtTail(5);
// 	// l->insertAtTail(4);
// 	// l->insertAtTail(9);
// 	// l->insertAtTail(4);
// 	// l->insertAtTail(5);
// 	// l->insertAtTail(6);
// 	// //ListItem<int>* pp =  l->getTail();
// 	//cout<< pp <<endl;
// 	//ListItem<int>* p =  l->searchFor(0);
// 	//l->reverse();
// //	l->print();
// 	// l->reverse();
// 	// l->print();
// 	//l->parityArrangement();

// 	//cout<<"abcef"<<endl;
// 	l->print();
// 	cout<< l->isPalindrome()<<endl;
	  

// }