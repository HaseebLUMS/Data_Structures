#include <iostream>
#include "bst.h"
#include <vector>
#include <algorithm>

using namespace std;
template <class T>
void treeToVector(node<T>* tree, vector<node<T>*>& v)
{
	if(tree == NULL)
		return;
	treeToVector(tree->left,v);
	node<T>* tmp = tree;
	v.push_back(tmp);
	treeToVector(tree->right,v);
}
template<class T>
node<T>* vectorToTree(node<T>* tree, vector<node<T>*> v1v2)
{
	if(v1v2.size() < 2)
	{
		v1v2[0]->left = NULL;
		v1v2[0]->right = NULL;
		return v1v2[0];
	}
	if(v1v2.size() == 2)
	{

		v1v2[0]->left = NULL;
		v1v2[0]->right = NULL;
		node<T>* tm = v1v2[0];
		if(tm->key < v1v2[1]->key){
			v1v2[1]->left = v1v2[0];
			v1v2[1]->right = NULL;
		}
		else{
			v1v2[1]->right= v1v2[0];
			v1v2[1]->left = NULL;

		}
		return v1v2[1];
	}
	node<T>* tmp = v1v2[(v1v2.size())/2 ];
	tree = tmp;
	vector<node<T>*> vL;
	for(int i=0; i< v1v2.size()/2; i++)
	{
		vL.push_back(v1v2[i]);
	}
	vector<node<T>*> vR;
	for(int i=v1v2.size()/2 + 1; i< v1v2.size(); i++)
	{
		vR.push_back(v1v2[i]);
	}
	if(vR.size() == 3)
	{
		for(int i=0; i< vR.size() ; i++)
			cout<< vR[i]->key<< " ";
	}cout<<endl;
	tree->left = vectorToTree(tree->left,vL);
	tree->right= vectorToTree(tree->right,vR);

	
	return tree;
}
template<class T>
vector<node<T>*> mergeVecs(vector<node<T>*> v1,vector<node<T>*> v2)
{
	vector<node<T>*> v1v2;
	reverse(v1.begin(),v1.end());
	reverse(v2.begin(),v2.end());
	while(v1.size() != 0 || v2.size() != 0)
	{
		if(v1.size() == 0)
		{
			while(v2.size())
			{
				v1v2.push_back(v2[v2.size()-1]);
				v2.pop_back();
			}
			break;
		}
		if(v2.size() == 0)
		{
			while(v1.size())
			{
				v1v2.push_back(v1[v1.size()-1]);
				v1.pop_back();
			}
			break;
		}
		if(v1[(v1.size())-1]->key < v2[(v2.size())-1]->key)
		{
			v1v2.push_back(v1[v1.size() -1]);
			if(v1v2.size() > 1)
			{
				if(v1v2[v1v2.size() -1]->key == v1v2[v1v2.size()-2]->key)
					v1v2.pop_back();
			}
			v1.pop_back();
		}
		else if(v1[(v1.size())-1]->key > v2[(v2.size())-1]->key)
		{
			v1v2.push_back(v2[v2.size() -1]);
			if(v1v2.size() > 1)
			{
				if(v1v2[v1v2.size() -1]->key == v1v2[v1v2.size()-2]->key)
					v1v2.pop_back();
			}
			v2.pop_back();
		}
		else
		{
			v1v2.push_back(v1[(v1.size())-1]);
			if(v1v2.size() > 1)
			{
				if(v1v2[v1v2.size() -1]->key == v1v2[v1v2.size()-2]->key)
					v1v2.pop_back();
			}
			v1.pop_back();
			v2.pop_back();
		}
	}
	return v1v2;
}
template <class T>
BST<T>* bst_Union(BST<T>* tree1,BST<T>* tree2){
	vector<node<T>*> v1;
	vector<node<T>*> v2;
	treeToVector(tree1->getRoot(), v1);
	treeToVector(tree2->getRoot(), v2);


	vector<node<T>*> v1v2 = mergeVecs(v1,v2);
	
	BST<T>* unionedTree = new BST<T>();
	node<T>* ab  = vectorToTree(unionedTree->getRoot(),v1v2);
	BST<T>* unionedTree1 = new BST<T>(ab);

	return unionedTree1;
}

// int main()
// {
// 	BST<int>* bst = new BST<int>();
// 	bst->insert("haseeb",1);
// 	bst->insert("Faseeb",3);
// 	bst->insert("Zaseeb",5);
// 	bst->insert("Maseeb",7);
// 	BST<int>* bst2 = new BST<int>();
// 	bst2->insert("haseebb",0);
// 	bst2->insert("Faseebb",2);
// 	bst2->insert("Zaseebb",4);
// 	bst2->insert("Maseebb",-1);
// 	bst_Union(bst,bst2);
// 	// vector<node<int>*> v;
// 	// treeToVector(bst->getRoot(),v);
// 	// for(int i=0; i< v.size(); i++)
// 	// {
// 	// 	cout<< v[i]->key<< " ";
// 	// }cout<<endl;
// 	// print(bst->getRoot(),0);
// 	return 0;
// }