#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "list.cpp"
#include "heap.cpp"
#include <algorithm>
#include <vector>

//=====================================================================================

void insertAndShift(long* finalArray, long ele, int pos, int upto){
	for(int k = upto; k > pos; k--){
		finalArray[k] = finalArray[k-1];
	}
	finalArray[pos] = ele;
}

void binaryInsert(long* finalArray, long ele, int upto){
	bool midway = false;
	int indOfInterest = upto-1;
	for(int i=0; i< upto; i++){
		if(finalArray[i] > ele){
			midway = true;
			insertAndShift(finalArray,ele,i,upto);
			break;
		}
	}

	if(!midway){
		finalArray[upto] = ele;
	}
}

void auxInsertionSort(long* numsArray,long* finalArray, int s){
	for(int i=0; i < s; i++){
		binaryInsert(finalArray, numsArray[i], i);
	}
}
void auxInsertionSortXX(long * &numsArray, int l){

	for(int i=1; i< l; i++){
		int k = numsArray[i];
		int j =i-1;
		while(j>=0 && numsArray[j] > k){
			numsArray[j+1] = numsArray[j];
			//swap(numsArray[j+1],numsArray[j]);
			j--;
		}
		numsArray[j+1] = k;

		// for(int k = i-1; k>=0; k--){
		// 	if(numsArray[i] < numsArray[k]){
		// 		swap(numsArray[i],numsArray[k]);
		// 	}

		// }	
	}
}
vector<long> InsertionSort(vector<long> nums)
{
	long* numsArray = new long[nums.size()];
	long* finalArray= new long[nums.size()];

	for(int i=0; i< nums.size(); i++){
		numsArray[i] = nums[i];
	}


	//auxInsertionSort(numsArray, finalArray, nums.size());
	auxInsertionSortXX(numsArray,nums.size());
	// int s = nums.size();
	// for(int j=0; j< s; j++){
	// 	binaryInsert(finalArray, numsArray[j], j);
	// }

	vector<long> fv;
	for(int j=0; j< nums.size(); j++){
		fv.push_back(numsArray[j]);
	}
	return fv;
}


//=====================================================================================
// void FrontBackSplit(ListItem<long>* source,ListItem<long>** frontRef, ListItem<long>** backRef)
// {
//     ListItem<long>* fast;
//  	ListItem<long>* slow;
//     slow = source;
//     fast = source->next;
 
//     /* Advance 'fast' two nodes, and advance 'slow' one node */
//     while (fast != NULL)
//     {
//     fast = fast->next;
//     if (fast != NULL)
//     {
//         slow = slow->next;
//         fast = fast->next;
//     }
//     }
 
//     /* 'slow' is before the midpoint in the list, so split it in two
//     at that point. */
//     *frontRef = source;
//     *backRef = slow->next;
//     slow->next = NULL;
// }

List<long>* mergeVecs(ListItem<long>* l,ListItem<long>* tmp)
{
	List<long>* finalList = new List<long>;
	while(l && tmp){
		if(l->value < tmp->value){
			finalList->insertAtHead(l->value);
			l = l->next;
		}
		else{
			finalList->insertAtHead(tmp->value);
			tmp = tmp->next;
		}
	}

	while(l){
		finalList->insertAtHead(l->value);
		l = l-> next;
	}

	while(tmp){
		finalList->insertAtHead(tmp->value);
		tmp = tmp-> next;
	}

	return finalList;
	//if(v1.length())
}
void auxMergeSort(List<long>* l, int len){
	if(len <=1)
		return;
	//ListItem<long>* ll = *l;
	int mid = len/2;
	List<long>* l1 = new List<long>;
	List<long>* l2 = new List<long>;
	//ListItem<long>* l2;
	ListItem<long>* tmp = l->getHead();
	for(int i=0; i< mid; i++){
		l1->insertAtHead(tmp->value);
		tmp = tmp->next;
	}
	while(tmp){
		l2->insertAtHead(tmp->value);
		tmp = tmp->next;
	}

	auxMergeSort(l1,mid);
	auxMergeSort(l2,len-mid);

	//vector<long> left, right;
	List<long>* fin1 = mergeVecs(l1->getHead(),l2->getHead());
	ListItem<long>* fin = fin1->getHead();
	//l->clear();

	while(l->getHead() != NULL){
		l->deleteHead();
	}
	//l->getHead() = NULL;
	for(int i=0; i< len; i++){
		l->insertAtHead(fin->value);
		fin = fin->next;
	}

	//delete fin1;
}

vector<long> MergeSort(vector<long> nums)
{
	if(nums.size() <= 1)
		return nums;
	List<long>* l = new List<long>;
	for(int i=0; i< nums.size(); i++){
		l->insertAtTail(nums[i]);
	}

	vector<long> v;
	auxMergeSort(l,nums.size());
	ListItem<long>* ll = l->getHead();

	for(int i=0; i< nums.size(); i++){
		v.push_back(ll->value);
		ll = ll->next;
	}	
	return v;
}

//=====================================================================================

int setSmallerLarger (long* &numsArray, int st, int en)
{
	int pivot = numsArray[en];

	int startingIndex = (st - 1);

	for (int i=st; i < en; i++){
		if (numsArray[i] <= pivot){
			startingIndex++;
			swap(numsArray[startingIndex], numsArray[i]);
		}
	}

	startingIndex = startingIndex+1;
	swap(numsArray[startingIndex], numsArray[en]);

	return (startingIndex);
}
void qSort(long* &numsArray,int st, int en){
	if(st>=en)
		return;

	int pivotPos = setSmallerLarger(numsArray, st, en);
	qSort(numsArray, st, pivotPos - 1);
	qSort(numsArray, pivotPos + 1, en);
}
vector<long> QuickSortArray(vector<long> nums)
{
	long* numsArray = new long[nums.size()];
	long* finalArray= new long[nums.size()];

	for(int i=0; i< nums.size(); i++){
		numsArray[i] = nums[i];
	}
	qSort(numsArray,0,nums.size()-1);
	vector<long> v;
	for(int i=0; i< nums.size(); i++){
		v.push_back(numsArray[i]);
	}

	return v;
}

//=====================================================================================
void auxqSortList(List<long>* &l, int s){
	if(s<=1){
		return;
	}
	
	int ra = (rand()%s);

	ListItem<long>* pivot = l->getHead();
	while(ra){
		//cout<<"here"<<endl;
		pivot = pivot->next;
		ra--;
	}
	List<long>* smallerNums = new List<long>;
	int l_sn = 0;
	List<long>* largerNums = new List<long>;
	int l_ln = 0;
	int counterOfPiv = 0;

	ListItem<long>* tmp = l->getHead();
//	tmp = tmp->next;
	while(tmp){
		if(tmp->value < pivot->value){
			smallerNums->insertAtHead(tmp->value);
			l_sn++;
		}
		if(tmp->value > pivot->value){
			largerNums->insertAtHead(tmp->value);
			l_ln++;
		}
		if(tmp->value == pivot->value){
			counterOfPiv++;
		}

		tmp = tmp->next;
	}
	auxqSortList(smallerNums, l_sn);
	auxqSortList(largerNums, l_ln);

	ListItem<long>* hs = smallerNums->getTail();
	ListItem<long>* hl = largerNums->getTail();
	List<long>* newL = new List<long>;
	while(hl){
		newL->insertAtHead(hl->value);
		hl = hl->prev;
	}
	while(counterOfPiv){
		newL->insertAtHead(pivot->value);
		counterOfPiv--;
	}
	while(hs){
		newL->insertAtHead(hs->value);
		hs = hs->prev;
	}

	l = newL;

}
vector<long> QuickSortList(vector<long> nums)
{
	if(nums.size() <= 1)
		return nums;
	List<long>* l = new List<long>;
	for(int i=0; i< nums.size(); i++){
		l->insertAtHead(nums[i]);
	}
	vector<long> v;
	auxqSortList(l,nums.size());
	ListItem<long>* ll = l->getHead();
	int ss = nums.size();
	for(int i=0; i< ss; i++){
		v.push_back(ll->value);
		ll = ll->next;
	}	
	return v;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
	int ns = nums.size();
	MinHeap* myHeap = new MinHeap(ns);
	for(int i=0; i< ns; i++){
		myHeap->insertKey(nums[i]);
	}

	vector<long> fv;
	for(int k=0; k< ns; k++){
		fv.push_back(myHeap->extractMin());
	}

	return fv;
}

// int main(){
// 	vector<long> v;
// 	// for(int i=900; i>0; i--){
// 	// 	v.push_back(i);
// 	// }
// 	v.push_back(2);
// 	v.push_back(3);
// 	v.push_back(1);
// 	// v.push_back(4);
// 	// v.push_back(100);
// 	// v.push_back(5);
// 	// v.push_back(0);
// 	// v.push_back(60);
// 	// v.push_back(-5);

// 	vector<long> vv = InsertionSort(v);
// 	for(int i=0; i< vv.size(); i++){
// 		cout<< vv[i]<< " "; 
// 	}cout<<endl;
// }

#endif