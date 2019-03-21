#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "hashChaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
	hashTable = new HashD[size]();
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
	(hashTable[key]).insert(word);
  return;
}

block* HashC :: lookup(string word){
	int key = hash(word);
	return (hashTable[key]).lookup(word);
}

void HashC :: deleteWord(string word){
	int key = hash(word);
	hashTable[key].deleteWord(word);
  return;
}

#endif