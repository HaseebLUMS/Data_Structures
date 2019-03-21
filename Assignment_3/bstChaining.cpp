#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "bstChaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
	hashTable = new BST<string>[size];
	tableSize = size;
}

unsigned long HashC :: hash(string input){
	return divCompression((bitHash(input)),tableSize);
  return 0;  
}

void HashC::insert(string word){
	int key = hash(word);
	// if(lookup(word) != NULL){
	// 	return;
	// }
	(hashTable[key]).insert(word,word);
  return;
}

node<string>* HashC :: lookup(string word){
	int key = hash(word);
	return (hashTable[key]).search(word);
}

void HashC :: deleteWord(string word){
	int key = hash(word);
	node<string>* a = (hashTable[key]).search(word);
	a->value = "0000";
  return;
}

#endif