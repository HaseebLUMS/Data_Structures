#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"


MinHeap::MinHeap(int cap)
{
	try{
		capacity = cap;
		if(cap < 0){
			throw("Negative size is not feasible");
		}
		int* heapArray = new int[cap];
		//int heapArray[cap];
		harr = heapArray;
		heap_size = 0;
	}catch(string msg){
		cout<< msg <<endl;
	}
}

void MinHeap::MinHeapify(int i)
{
	if(i >= heap_size)
		return;

	int minInd = left(i);

	if(minInd < heap_size && right(i) < heap_size &&  harr[minInd] > harr[right(i)]){
		minInd = right(i);
	}
	if(minInd < heap_size && harr[minInd] < harr[i]){
		swap(harr[minInd], harr[i]);
		MinHeapify(minInd);
	}
	return;

}
 
int MinHeap::parent(int i)
{
	return (i-1)/2;
}
 
int MinHeap::left(int i)
{
	return 2*i + 1;
}
 
int MinHeap::right(int i)
{
	return 2*i +2;
}
 
int MinHeap::extractMin()
{
	if(heap_size){
		int toret = harr[0];
		deleteKey(0);
		return toret;
	}
	else{
		return 0;
	}
}

void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	//MinHeapify(0);

	int curr = i;

	while(curr > 0){
		if(new_val < harr[parent(curr)]){
			swap(harr[curr],harr[parent(curr)]);
		}
		else{
			break;
		}
		curr = parent(curr);
	}
}
 
int MinHeap::getMin()
{
	return harr[0];
}
 
void MinHeap::deleteKey(int i)
{
	if(i < heap_size){
		swap(harr[i], harr[heap_size-1]);
		heap_size--;
		MinHeapify(i);
	}
}
 
void MinHeap::insertKey(int k)
{
	if(heap_size >= capacity){
		return;
	}
	harr[heap_size] = k;
	if(heap_size == 0){
		heap_size++;
		return;
	}
	heap_size++;

	int curr = heap_size-1;

	while(curr > 0){
		if(k < harr[parent(curr)]){
			swap(harr[curr],harr[parent(curr)]);
		}
		else{
			break;
		}
		curr = parent(curr);
	}
}

int* MinHeap::getHeap()
{
	return harr;
}

// void MinHeap::printHeap(){
// 	for(int i=0; i< heap_size; i++){
// 		cout<< harr[i]<< " ";
// 	}cout<<endl;
// }

// int main(){
// 	MinHeap a(10);
// 	a.insertKey(1);
// 	a.insertKey(90);
// 	a.insertKey(91);
// 	// a.insertKey(3);
// 	// a.insertKey(40);
// 	// a.insertKey(5);
// 	// a.insertKey(6);
// 	// a.insertKey(70);
// 	// a.insertKey(8);
// 	// a.insertKey(11);
// 	// a.insertKey(1430);
// 	// a.insertKey(30);
// 	// a.insertKey(1);
// 	//a.insertKey(10);
// 	// a.insertKey(15);
// 	// a.insertKey(100);
// 	// a.insertKey(200);
// 	// a.insertKey(-400);
// 	//int d = a.extractMin();
// 	//cout<< d<<endl;
// 	// a.deleteKey(0);
// 	// a.printHeap();
// 	// a.insertKey(0);
// 	cout << a.extractMin();
// 	cout << a.extractMin();
// 	// a.extractMin();
// 	// a.extractMin();
// 	// a.extractMin();
// 	//a.in
// 	// a.insertKey(0);
// 	//a.printHeap();
// }

#endif