#include "bstChaining.cpp"
#ifndef CHAINING__H
#define CHAINING__H
#include <string>
#include <vector>
#include <algorithm>
#include "bst.cpp" // Your Own Implementation
using namespace std;
class HashC
{
	private:
		long tableSize;
		BST<string>* hashTable;
		unsigned long hash(string input); // Given a String, return its hash
	public:
		HashC(int);
		~HashC(); // Destructor
		void insert(string word); // Takes a hash of 'word' and inserts it into hashTable accordingly
		void deleteWord(string word);
		node<string>* lookup(string word);
};
#endif
