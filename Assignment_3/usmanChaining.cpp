#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"
#include "LinkedList.cpp"


//hashtable is a LinkedList object
HashC::HashC(int size)
{
	tableSize = size;
	hashTable = new LinkedList<string>[size];   
}
HashC::~HashC()
{

}

unsigned long HashC :: hash(string input)
{
	unsigned long hs = 0;
	hs = divCompression(bitHash(input), tableSize);
  	return hs;  
}

void HashC::insert(string word)
{
	unsigned long hs = hash(word);
	hashTable[hs].insertAtHead(word);
  	return;
}

ListItem<string>* HashC :: lookup(string word)
{
	ListItem<string>* a = hashTable[hash(word)].searchFor(word);
	return a;
}

void HashC :: deleteWord(string word)
{
	hashTable[hash(word)].deleteElement(word);
  	return;
}

#endif