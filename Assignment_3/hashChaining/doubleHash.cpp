#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 1000; // you cant change this
    hashTable = new block*[tableSize];
    for(int i=0; i< tableSize; i++){
    	hashTable[i] = NULL;
    }
    count = 0;
}

HashD::~HashD(){

}

unsigned long HashD :: hash1(string value){
	return divCompression((bitHash(value)),tableSize);
    return 0;
}

unsigned long HashD :: hash2(string value){
	int q = 5;
	int k = divCompression(polyHash(value),tableSize);
	//return q-(k% q);
    return k;
}


void HashD::resizeTable(){
	tableSize = tableSize * 2;
	block** newHashTable = new block*[tableSize];
	for(int i=0; i< tableSize; i++){
    	newHashTable[i] = NULL;
    }


	block** tmp = newHashTable;
	newHashTable = hashTable;
	hashTable = tmp;
	count = 0;
	


    for(unsigned long i=0; i< tableSize/2; i++){


     	if(newHashTable[i] && newHashTable[i]->value != "-1"){
   			this->insert(newHashTable[i]->value);
   		}
   

    }

    //count = count/2;
    return;
}



void HashD::resizeTablePrime(){
	tableSize = tableSize/2;
	block** newHashTable = new block*[tableSize];
	for(int i=0; i< tableSize; i++){
    	newHashTable[i] = NULL;
    }


	block** tmp = newHashTable;
	newHashTable = hashTable;
	hashTable = tmp;
	count = 0;
	


    for(unsigned long i=0; i< tableSize*2; i++){


     	if(newHashTable[i] && newHashTable[i]->value != "-1"){
   			this->insert(newHashTable[i]->value);
   		}


    }

    //count = count/2;
    return;
}

void HashD::insert(string value){

	if(count/(tableSize*1.0) >= 0.4){
		resizeTable();
	}

	unsigned long index = (hash1(value) ) % tableSize;
	if(hashTable[index] && hashTable[index]->value == value)
		return;
	if( hashTable[index] == NULL || (hashTable[index] && hashTable[index]->value == "-1")){
		block* x = new block(index, value);
		hashTable[index] = x;
		count++;
	}
	else{
		bool inserted = false;
		unsigned long fec = 2;

		unsigned long index = (hash1(value) + hash2(value) )% tableSize;
		if(hashTable[index] && hashTable[index]->value == value)
			return;
		if( hashTable[index] == NULL || (hashTable[index] && hashTable[index]->value == "-1")){
			block* x = new block(index, value);
			hashTable[index] = x;
			count++;
			inserted = true;
			return;
		}
		while(inserted==false){
			index = (hash1(value) + (fec*hash2(value)) )% tableSize;
			if(hashTable[index] && hashTable[index]->value == value)
				return;
			if( hashTable[index] == NULL || (hashTable[index] && hashTable[index]->value == "-1")){
				block* x = new block(index, value);
				hashTable[index] = x;
				count++;
				inserted = true;
				return;
			}
			fec++;
		}
	}
}

void HashD::deleteWord(string value){

	if(count/(tableSize*1.0) <= 0.12){
		resizeTablePrime();
	}
	unsigned long index = (hash1(value))% tableSize;
	if(hashTable[index] && hashTable[index]->value == value){
		
		hashTable[index]->value = "-1";
		count--;
	}
	else{
		
		unsigned long fec = 1;
		unsigned long index = (hash1(value) + (fec*hash2(value)) )% tableSize;
		while(hashTable[index]){
			if(hashTable[index]->value == value){
				hashTable[index]->value = "-1";
				count--;
				break;
			}
			fec++;
			index = (hash1(value) + (fec*hash2(value)) )% tableSize;
		}
		return;

	}

	//(lookup(value))->value = "-1";
    return;
}

block* HashD::lookup(string value){

		

	unsigned long index = (hash1(value))% tableSize;
	if(hashTable[index] && hashTable[index]->value == value){
		
		return hashTable[index];
	}
	else{
		unsigned long i = index;
		unsigned long fec = 1;
		index = (hash1(value) + (fec*hash2(value)) )% tableSize;
		while(hashTable[index] && index != i){
			if(hashTable[index]->value == value){
				return hashTable[index];
			}
			fec++;
			index = (hash1(value) + (fec*hash2(value)) )% tableSize;
		}
		return NULL;

	}

    return NULL;
}

#endif