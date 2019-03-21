#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this

    hashTable = new block*[tableSize];
    for(int i=0; i< tableSize; i++){
    	hashTable[i] = NULL;
    }
    count = 0;

}

HashL::~HashL(){
    
}

unsigned long HashL :: hash(string value){
	return divCompression((bitHash(value)), tableSize);
    return 0;
}

void HashL::resizeTable(){
	tableSize = tableSize * 2;
	block** newHashTable = new block*[tableSize];
	for(int i=0; i< tableSize; i++){
    	newHashTable[i] = NULL;
    }


	block** tmp = newHashTable;
	newHashTable = hashTable;
	hashTable = tmp;
	count = 0;
	


    for(int i=0; i< tableSize/2; i++){
    	if(newHashTable[i] != NULL){

	  		string value = newHashTable[i]->value;
	     	unsigned long key = hash(value);
			if(!hashTable[key]){
				block*x = new block(key, value);
			 	hashTable[key] = x;
			 	count++;
			 }
			else{
				unsigned long k = key;
				while(hashTable[k] != NULL){
					k++;
					k = k%tableSize;
				}
				hashTable[k] = new block(k, value);
				count++;
			}
    	}
    }

    //count = count/2;
    return;
}

void HashL::resizeTablePrime(){
	tableSize = tableSize/3;
	block** newHashTable = new block*[tableSize];
	for(int i=0; i< tableSize; i++){
    	newHashTable[i] = NULL;
    }


	block** tmp = newHashTable;
	newHashTable = hashTable;
	hashTable = tmp;
	count = 0;
	


    for(int i=0; i< (tableSize*3); i++){
    	if(newHashTable[i] != NULL){

	  		string value = newHashTable[i]->value;
	     	unsigned long key = hash(value);
			if(!hashTable[key]){
				block*x = new block(key, value);
			 	hashTable[key] = x;
			 	count++;
			 }
			else{
				unsigned long k = key;
				while(hashTable[k] != NULL){
					k++;
					k = k%tableSize;
				}
				hashTable[k] = new block(k, value);
				count++;
			}
    	}
    }

    //count = count/2;
    return;
}


void HashL::insert(string value){
	//cout << count/(tableSize*1.0) << endl;
	if(count/(tableSize*1.0) >= 0.4){
		resizeTable();
	}
	//cout<<count<< endl;
	unsigned long key = hash(value);
	if(!hashTable[key]){
		block*x = new block(key, value);
	 	hashTable[key] = x;
	 	count++;
	 }
	else{
		if(hashTable[key]->value == value)
			return;
		unsigned long k = key;
		while(hashTable[k] != NULL && (hashTable[k] && hashTable[k]->value != "-1") && (hashTable[k] && hashTable[k]->value != value)){
			k++;
			k = k%tableSize;
		}
		if(hashTable[k] && hashTable[k]->value == value){
			return;
		}
		hashTable[k] = new block(k, value);
		count++;
	}
    return;
}

void HashL::deleteWord(string value){

	if(count/(tableSize*1.0) <= 0.2){
		resizeTablePrime();
	}
	unsigned long key = hash(value);
	unsigned long ck = key;
	if(hashTable[key] == NULL){
		return;
	}
	else{
		if(hashTable[key]->value == value){
			hashTable[key]->value = "-1";
			return;
		}
		else{
			key++;
			while(hashTable[key] != NULL && (key != ck) &&hashTable[key]->value != value){
				key++;
				key = key%tableSize;
			}

			if(ck == key || hashTable[key] == NULL){
				return;
			}
			else{
				hashTable[key]->value = "-1";
			}
		}
	}
    return;
}
block* HashL::lookup(string value){
	unsigned long key = hash(value);
	unsigned long ck = key;
	if(hashTable[key]->value == value){
		return hashTable[key];
	}
	else{
		key++;
		while(hashTable[key] != NULL && (key != ck) && hashTable[key]->value != value){
			key++;
			key = key%tableSize;
		}

		if(hashTable[key] == NULL || ck == key){
			return NULL;
		}
		else{
			return hashTable[key];
		}
	}
    return NULL;
}


// #include <iostream>
// using namespace std;

// int main(){
// 	HashL ha;
// 	ha.insert("a");
// 	ha.insert("ab");
// 	ha.insert("abc");
// 	ha.insert("abcd");
// 	ha.deleteWord("abcd") ;
// 	if(ha.lookup("abcd") == NULL){
// 		cout<<"NULL"<<endl;
// 	}
// 	cout << ha.lookup("ab")->value <<endl;
// 	cout<< "a"<<endl;
// 	if(ha.lookup("abcdef") == NULL)
// 		cout<<"nulla"<<endl;
// 	cout<< "aa"<<endl;

// }
#endif