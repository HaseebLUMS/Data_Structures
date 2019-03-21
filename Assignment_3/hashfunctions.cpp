#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(string value,int a = 5){
	int stringLength = value.length();
	int firstExp = stringLength -1;
	int stringIndex = 0;

	unsigned long result = 0;
	while(stringIndex < stringLength){
		result += int(value[stringIndex])*(pow(a,firstExp));
		firstExp--;
		stringIndex++;
	}

	return result;
}
//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(string value){
	unsigned long bitwise_hash = 0;
	for(int i=0; i<value.length(); i++){

		unsigned long tmp = (bitwise_hash << 5) + (bitwise_hash >>2) + int(value[i]);
		bitwise_hash ^= tmp;
	}

	return bitwise_hash;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
	return (hash)%size;
}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
   
	return (a*hash + m)%size;
    return 0;
}
// 'm' and 'a' can take any value
#endif
// you may write your own program to test these functions.

// int main(){
// 	cout << madCompression(polyHash("haseebAshfaq",37), 5) <<endl;
// 	cout<< (bitHash("has")) <<endl;
// 	return 0;
// }