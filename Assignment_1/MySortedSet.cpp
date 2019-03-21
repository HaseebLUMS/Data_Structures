#include "MySortedSet.h"

template <class T>
MySortedSet<T>::MySortedSet()
{

}

template <class T>
MySortedSet<T>::~MySortedSet()
{
	ListItem<T>* tmp = container.getHead();
	while(tmp)
	{
		ListItem<T>* tmp2 = tmp->next;
		delete tmp;
		tmp = tmp2;
	}
}
template <class T>
int MySortedSet<T>::count()
{
	return container.length();
}
template <class T>
ListItem<T>* MySortedSet<T>::getListHead()
{
	return container.getHead();
}

template <class T>
int MySortedSet<T>::insert(T ele)
{
	ListItem<T>* tmp = container.getHead();
	while(tmp)
	{
		if(tmp->value == ele)
			return 0;
		tmp = tmp->next;
	}
	container.insertAtTail(ele);
}

template <class T>
int MySortedSet<T>::deleteEle(T ele)
{
	ListItem<T>* tmp = container.getHead();
	while(tmp)
	{
		if(tmp->value == ele)
		{
			container.deleteElement(ele);
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

template <class T>
int MySortedSet<T>::isEmpty()
{
	if(container.length() == 0)
		return 1;
	return 0;
}

template <class T>
int MySortedSet<T>::isMember(T ele)
{
	ListItem<T>* tmp = container.getHead();
	while(tmp)
	{
		if(tmp->value == ele)
		{
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

template <class T>
int MySortedSet<T>::isEqual(MySortedSet<T>* anotherset)
{
	ListItem<T>* tmp = container.getHead();
	ListItem<T>* tmp2= anotherset->container.getHead();
	if(anotherset->container.length() != this->container.length())
		return 0;
	while(tmp2)
	{
		if(container.searchFor(tmp2->value) == NULL)
			return 0;
		tmp2 = tmp2->next;
	}
	return 1;
}

template <class T>
int MySortedSet<T>::isSubset(MySortedSet<T>* anotherset)
{
	ListItem<T>* tmp2= anotherset->container.getHead();
	if(anotherset->container.length() > container.length())
		return 0;
	while(tmp2)
	{
		if(container.searchFor(tmp2->value) == NULL)
			return 0;
		tmp2 = tmp2->next;
	}
	return 1;
}

template <class T>
MySortedSet<T>* MySortedSet<T>::setUnion(MySortedSet<T>* anotherset)
{
	MySortedSet<T>* unionOfSets = new MySortedSet<T>();
	ListItem<T>* tmp = this->container.getHead();
	while(tmp)
	{
		(unionOfSets)->insert(tmp->value);
		tmp = tmp->next;
	}
	ListItem<T>* tmp2 = anotherset->container.getHead();
	while(tmp2)
	{
		(unionOfSets)->insert(tmp2->value);
		tmp2 = tmp2->next;
	}
	return unionOfSets;
}

template <class T>
MySortedSet<T>* MySortedSet<T>::setIntersection(MySortedSet<T>* anotherset)
{
	MySortedSet<T>* intersectionOfSets = new MySortedSet<T>();
	ListItem<T>* tmp = this->container.getHead();
	ListItem<T>* tmp2 = anotherset->container.getHead();

	while(tmp)
	{
		if(anotherset->isMember(tmp->value) == 1)
		{
			intersectionOfSets->insert(tmp->value);
		}
		tmp = tmp->next;
	}
	while(tmp2)
	{
		if(this->isMember(tmp2->value) == 1)
		{
			intersectionOfSets->insert(tmp2->value);
		}
		tmp2 = tmp2->next;
	}
	return intersectionOfSets;
}

template <class T>
MySortedSet<T>* MySortedSet<T>::setDifference(MySortedSet<T>* anotherset)
{
	MySortedSet<T>* intersectionOfSets = new MySortedSet<T>();
	ListItem<T>* tmp = this->container.getHead();
	ListItem<T>* tmp2 = anotherset->container.getHead();
	
	while(tmp)
	{
		if(anotherset->isMember(tmp->value) == 0)
		{
			intersectionOfSets->insert(tmp->value);
		}
		tmp = tmp->next;
	}
	// while(tmp2)
	// {
	// 	if(this->isMember(tmp2->value) == 0)
	// 	{
	// 		intersectionOfSets->insert(tmp2->value);
	// 	}
	// 	tmp2 = tmp2->next;
	// }
	return intersectionOfSets;
}