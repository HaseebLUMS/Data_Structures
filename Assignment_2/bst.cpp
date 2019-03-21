#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}
template <class T>
BST<T>::BST(node<T>* tmp){
	root = tmp;;
}

template <class T>
BST<T>:: ~BST(){

    // your destructor code goes here
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
	if(p){
		fixHeight(p);
		return  p->height;
	}
	else
		return -1;
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if(!p)
    {
    	return 0;
    }
    fixHeight(p);
	if(p->right && p->left)
	{
		return ((p->right->height)-(p->left->height));
	}
	else if (!p->right && p->left)
	{
		return (-(p->left->height) + (-1) );
	}
	else if(!p->left && p->right)
	{
		return ((p->right->height) - (-1) );
	}
	else
	{
		return 0;
	}
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
	if(!p)
	{
		return;
	}
	fixHeight(p->left);
	fixHeight(p->right);
	
	{
		int left = (p->left) ? (p->left->height) : -1;
		int right = (p->right) ? (p->right->height) : -1;
		p->height = (left > right) ? (1+left) : (1 + right); 
	}
    // use this function to fix height of a node after insertion or deletion.
    return;
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
	node<T>* tmp = p->right;
	node<T>* tmp2 = tmp->left;

	tmp->left = p;
	p->right = tmp2;
	p = tmp;


	// p->height = 1+ p->left->height > p->right->height?
	//             (p->left->height):(p->right->height) ;

	//  tmp->height = 1+ tmp->left->height > tmp->right->height?
	//             (tmp->left->height):(tmp->right->height);
	fixHeight(p);
    return p;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
	node<T>* tmp= p->left;
	node<T>* tmp2= tmp->right;

	tmp->right = p;
	p->left = tmp2;
	p = tmp;

	 // p->height = 1+ p->left->height > p->right->height?
	 //            (p->left->height):(p->right->height) ;

	 // tmp->height = 1+ tmp->left->height > tmp->right->height?
	 //            (tmp->left->height):(tmp->right->height);
	fixHeight(p);
    return p;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){    
    fixHeight(p);
    if(!p)
    	return NULL;
    p->right = balance(p->right);
    p->left = balance(p->left);
    if(balanceFactor(p) > 1)
    {
    	if(height(p->right->right) >= height(p->right->left))
    	{

    		p = rotateleft(p);
    	}
    	else 
    	{
    		// right - left case
    		p->right=rotateright(p->right);
    		p = rotateleft(p);
    	}
    }
    else if(balanceFactor(p) < -1)
    {
    	if(height(p->left->right) <= height(p->left->left))
    	{
    		// left left case
    		p = rotateright(p);
    	}
    	else 
    	{
    		// left - right case
    		p->left = rotateleft(p->left);
    		p = rotateright(p);
    	}
    }

    fixHeight(p);
    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
    root = balance(root);
}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
   // cout<<1<<endl;
    if(!p)
    {
    	node<T>* nNode = new node<T>(k,value);
    	p = nNode;
    	//return p;
    }
    else if(p->key > k)
    {
    	p->left = insertHelper(value,k,p->left);
    }
    else
    {
    	p->right = insertHelper(value,k,p->right);
    }
    //cout<<21<<endl;
    return (p);
}
template<class T>
node<T>* BST<T> :: auxsearch(node<T>* p, T k){
	if(p->key == k)
	{
		return p;
	}
	else if(p->right == NULL && p->left == NULL)
	{
		return NULL;
	}
	else if(p->key > k)
	{
		return auxsearch(p->left,k);
	}
	else
		return auxsearch(p->right,k);
    //return NULL;
    // Search code goes here.
}
template<class T>
node<T>* BST<T> :: search(T key){
	
    return auxsearch(root,key);
    // Search code goes here.
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
	if(!p)
	{
		return p;
	}
	else if(p->left == NULL)
		return p;
	return findmin(p->left);
    // This function finds the min node of the tree.
    //return NULL;
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
	if(p == NULL)
	{
		p = NULL;
		return p;
	}
	if(p->left)
	{
		p->left = removemin(p->left);
	}
	else{
		p = p->right;
	}
	return balance(p);
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
    root = balance(root);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
	if(p == NULL)
	{
		return (p);
	}
	if(p->key == k)
	{
		// if it is a leaf node.
		if(p->left == NULL && p->right == NULL)
		{
			//cout<<"LEAF : " <<p->key<<endl;
			//node<T>* tmpp = p;
			p = NULL;
			//cout<< p->key <<endl;
			//delete tmpp;
		}
		// if it has only one child
		// if it has two child
		else if(p->left && p->right)
		{
			//cout<<"two child : " <<p->key<<endl;
			node<T>* succ = findmin(p->right);
			 p->value = succ->value;
			 p->key = succ->key;
			 p->right = removemin(p->right);
		}
		else if(p->left != NULL || p->right != NULL)
		{
			//cout<<"one cjhild : " <<p->key<<endl;
			if(p->left != NULL)
			{
				node<T>* tmp = p;
				p = p->left;
				delete tmp;
			}
			else
			{
				node<T>* tmp = p;
				p = p->right;
				delete tmp;
			}
		}
	}
	else if(p->key > k)
	{
		p->left = remove(p->left,k);
	}else
	{
		p->right= remove(p->right,k);
	}
	return balance(p);

    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}

template<class T>
void print(node<T>* temp, int val =0){
	if(temp){
		print(temp->right,val+1);
		for (int i = 0; i < val; ++i)
		{
			cout << "|   ";
		}
		cout << temp->key << endl;
		print(temp->left,val+1);
	}
}
//int main()
// {
// 	BST<int>* tree=new BST<int>();
// //------------------------
// 	tree->insert("a",34);
// 	tree->insert("b",7);
// 	tree->insert("c",53);
// 	tree->insert("d",12);
// 	tree->insert("e",68);
// 	tree->insert("f",90);
// 	print(tree->getRoot());
// 	node<int>* temp = tree->getRoot();
// 	temp->left = tree->rotateleft(temp->left);
// 	cout << endl;
// 	print(temp);

// }

#endif
