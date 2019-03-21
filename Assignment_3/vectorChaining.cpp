#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "vectorChaining.h"
#include "hashfunctions.cpp"



HashC::HashC(int size){
	hashTable = new vector<string>[size];
	tableSize = size;
}

unsigned long HashC :: hash(string input){
	return divCompression((bitHash(input)),tableSize);
  return 0;  
}

void HashC::insert(string word){
	int key = hash(word);
	if(lookup(word) != "0000"){
		return;
	}
	(hashTable[key]).push_back(word);
  return;
}

string HashC :: lookup(string word){
	int key = hash(word);
	vector<string>::iterator it;
	it = find((hashTable[key]).begin(), (hashTable[key]).end(),word);
	if(it == (hashTable[key]).end()){
		return "0000";
	}
	int ind = it - (hashTable[key]).begin();
	return (hashTable[key])[ind];
}

void HashC :: deleteWord(string word){
	int key = hash(word);
	vector<string>::iterator it;
	it = find((hashTable[key]).begin(), (hashTable[key]).end(),word);
	if(it == (hashTable[key]).end()){
		return;
	}
	int ind = it - (hashTable[key]).begin();
	(hashTable[key]).erase((hashTable[key]).begin()+ind);
  return;
}

// int main(){
// 	HashC h(10);
// 	h.insert("a");
// 	h.insert("ab");
// 	h.insert("abc");

// 	return 0;
// }

#endif