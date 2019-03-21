#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
	hashTable = new LinkedList<string>[size];
	tableSize = size;
}

unsigned long HashC :: hash(string input){
	return divCompression((bitHash(input)),tableSize);
  return 0;  
}

void HashC::insert(string word){
	int key = hash(word);
	if(lookup(word) != NULL){
		return;
	}
	(hashTable[key]).insertAtHead(word);
  return;
}

ListItem<string>* HashC :: lookup(string word){
	int key = hash(word);
	return (hashTable[key]).searchFor(word);
  return NULL;
}

void HashC :: deleteWord(string word){
	int key = hash(word);
	
	(hashTable[key]).deleteElement(word);
  return;
}

#endif