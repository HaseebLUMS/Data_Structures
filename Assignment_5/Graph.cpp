#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <map>
#include <set>
#include <algorithm>
#include <limits>
#include <utility>
#include <bits/stdc++.h>

bool operator == (edge a, edge b)
{
	bool ans;
	a.weight == b.weight ? ans = true : ans = false;
	return ans;
}

bool operator < (edge a, edge b)
{
	bool ans;
	a.weight < b.weight ? ans = true : ans = false;
	return ans;
}

bool operator > (edge a, edge b)
{
	bool ans;
	a.weight > b.weight ? ans = true : ans = false;
	return ans;
}
bool operator < (node a, node b)
{
	bool ans;
	a.dist < b.dist ? ans = true : ans = false;
	return ans;
}
bool operator > (node a, node b)
{
	bool ans;
	a.dist > b.dist ? ans = true : ans = false;
	return ans;
}
bool operator == (node a, node b)
{
	bool ans;
	a.dist == b.dist ? ans = true : ans = false;
	return ans;
}

node* giveNode(string n,vector<node*> vec){
	for(int i=0; i < vec.size(); i++){
		if(vec[i]->name == n)
			return vec[i];
	}
	return NULL;
}
vector<edge> giveEdge(string n,vector<edge> arcs){
	vector<edge> edg;
	for(int i=0; i< arcs.size(); i++){
		if((arcs[i].Origin)->name == n || (arcs[i].Dest)->name == n){
			edg.push_back(arcs[i]);
		}
	}
	return edg;
}
Graph::Graph(char* file)
{
	ifstream fd;
	fd.open(file);
	string mode;
	float xaxis;
	float yaxis;
	fd >> mode;
	fd >> mode;
	map<string,node*> st2node;
	while(mode != "ARCS"){
		fd >> xaxis >> yaxis;
		node* newNode = new node;
		newNode->x = xaxis;
		newNode->y = yaxis;
		newNode->name = mode;
		newNode->visit = 0;
		newNode->prev = NULL;
		newNode->dist = 0;

		st2node.insert(pair<string,node*> (mode,newNode));
		this->cities.push_back(newNode);
		fd >> mode;
	}

	string city1;
	string city2;
	float we;

	while(!fd.eof()){
		fd >> city1 >> city2 >> we;
		edge newEdge;
		newEdge.Origin = (st2node.find(city1))->second;
		newEdge.Dest = (st2node.find(city2))->second;
		newEdge.weight = we;
		this->arcs.push_back(newEdge);
	}

	for(int i=0; i< cities.size(); i++){
		cities[i]->edges = giveEdge(cities[i]->name,arcs);
	}

	//display(cities[0]);

}
node* Graph::getCity(string s)
{
	for(int i=0; i< cities.size(); i++){
		if(cities[i]->name == s)
			return cities[i];
	}
}
void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "AT: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}
void printNode(node* n){
	cout<<n->name<<endl;
	for(int i=0; i< n->edges.size(); i++){
		cout<< n->edges[i].Origin->name << " " << n->edges[i].Dest->name << " "<< n->edges[i].weight<<"-";
	}cout<<endl;
}
void printSet(set<node*> s){
	set<node*>::iterator it;
	for(it = s.begin(); it != s.end(); it++){
		printNode(*it);
	}
}


int isThere(set<node*> ss,node* a,node* b){
	set<node*>::iterator it;
	int ans1=0;
	int ans2=0;
	for(it = ss.begin(); it != ss.end(); it++){
		if((*it)->name == a->name)
			ans1 = 1;
		if((*it)->name == b->name)
			ans2 = 1;
	}
	if(ans1 == 1 && ans2 == 1)
		return 1;
	else
		return 0;
}
bool homoSet(vector<set<node*> > allNodes, node* a, node* b){
	int ans1 = 0;
	//cout<<allNodes.size()<<endl;
	for(int i=0; i< allNodes.size(); i++){
		ans1 += isThere(allNodes[i],a,b);
	}

	if(ans1 == 0)
		return false;
	else
		return true;
	
}

set<node*> findSetwithNode(vector<set<node*> > allNodes,node* a){
	for(int i=0; i< allNodes.size(); i++){
		set<node*>::iterator it;
		for(it = allNodes[i].begin(); it != allNodes[i].end(); it++){
			if((*it)->name == a->name){
				return allNodes[i];
			}
		}
	}
}

 
     


bool equalSets(set<node*> a, set<node*> b){
	return a==b;
}
vector<set<node*> > mergeNodes(vector<set<node*> > allNodes,node* a, node* b,edge ed){
	set<node*> setA = findSetwithNode(allNodes,a);
	set<node*> setB = findSetwithNode(allNodes,b);

	set<node*>::iterator iter1 = setA.begin();

	for(iter1 = setA.begin(); iter1 != setA.end(); iter1++){
		if((*iter1) && (*iter1)->name == a->name)
			break;
	}

	set<node*>::iterator iter2 = setB.begin();
	for(iter2 = setB.begin(); iter2 != setB.end(); iter2++){
		if((*iter2) && (*iter2)->name == b->name)
			break;
	}
	ed.Origin = *iter1;
	ed.Dest   =  *iter2;
	(*iter1)->edges.push_back(ed);
	(*iter2)->edges.push_back(ed);


	vector<set<node*> >::iterator it1 = allNodes.begin();
	vector<set<node*> >::iterator it2 = allNodes.begin();


	for(it1 = allNodes.begin(); it1 != allNodes.end(); it1++){
		if(equalSets(setA,(*it1))){
			//cout<<"Hey"<<endl;
			break;
		}
	}


	allNodes.erase(it1);
	for(it2 = allNodes.begin(); it2 != allNodes.end(); it2++){
		if(equalSets(setB,*it2)){
			break;
		}
	}
	allNodes.erase(it2);


	setA.insert(setB.begin(),setB.end());
	allNodes.push_back(setA);




	return allNodes;
}
edge findEdge(vector<edge> arcs, float edWeight){
	for(int i=0; i< arcs.size(); i++){
		if(arcs[i].weight == edWeight)
			return arcs[i];
	}
}

vector<node*> Graph::Prims()
{
	vector<edge> minimumSpanning;
	vector<node*> copyCities;
	for(int i=0; i< cities.size(); i++){
		node* n = new node;
		n->visit = 0;
		n->dist = 0;
		n->name = cities[i]->name;
		n->prev = NULL;
		n->x = cities[i]->x;
		n->y = cities[i]->y;
		copyCities.push_back(n);
	}



	

	vector<set<node*> > allNodes;
	for(int i=0; i< copyCities.size(); i++){
		set<node*> s;
		s.insert(copyCities[i]);
		allNodes.push_back(s);
	}



	int totalEdges = arcs.size();
	MinHeap<float> que(totalEdges);
	for(int i=0; i< totalEdges; i++){
		float a = arcs[i].weight;
		que.insertKey(a);
	}

	// for(int i=0; i< totalEdges; i++){
	// 	cout<< que.ExtractMin()<<endl;
	// }




	int tot = que.getHeapSize();
	while(tot){
		float edWeight = que.extractMin();
		edge ed = findEdge(arcs,edWeight);
		//cout<<ed.weight<<endl;
		if(!homoSet(allNodes, ed.Origin, ed.Dest) && ed.Origin->name != ed.Dest->name){
			allNodes = mergeNodes(allNodes,ed.Origin,ed.Dest, ed);
		}
		tot--;
	}

	//printSet(allNodes[0]);

	set<node*> s = allNodes[0];
	vector<node*> v;
	copy(s.begin(),s.end(), back_inserter(v));
	return v;
}
vector<node*> Graph::Kruskal()
{
	vector<edge> minimumSpanning;
	vector<node*> copyCities;
	for(int i=0; i< cities.size(); i++){
		node* n = new node;
		n->visit = 0;
		n->dist = 0;
		n->name = cities[i]->name;
		n->prev = NULL;
		n->x = cities[i]->x;
		n->y = cities[i]->y;
		copyCities.push_back(n);
	}



	

	vector<set<node*> > allNodes;
	for(int i=0; i< copyCities.size(); i++){
		set<node*> s;
		s.insert(copyCities[i]);
		allNodes.push_back(s);
	}



	int totalEdges = arcs.size();
	MinHeap<float> que(totalEdges);
	for(int i=0; i< totalEdges; i++){
		float a = arcs[i].weight;
		que.insertKey(a);
	}

	// for(int i=0; i< totalEdges; i++){
	// 	cout<< que.ExtractMin()<<endl;
	// }




	int tot = que.getHeapSize();
	while(tot){
		float edWeight = que.extractMin();
		edge ed = findEdge(arcs,edWeight);
		//cout<<ed.weight<<endl;
		if(!homoSet(allNodes, ed.Origin, ed.Dest) && ed.Origin->name != ed.Dest->name){
			allNodes = mergeNodes(allNodes,ed.Origin,ed.Dest, ed);
		}
		tot--;
	}

	//printSet(allNodes[0]);

	set<node*> s = allNodes[0];
	vector<node*> v;
	copy(s.begin(),s.end(), back_inserter(v));
	return v;
	// return v;
}
int indexOf(node*n, node** arr, int s){
	for(int i=0; i< s; i++){
		if(arr[i]->name == n->name){
			return i;
		}
	}
	return -1;
}

// class myComparisionOperator
// {
// public:
// 	bool operator() (const node* p1,const node* p2){
// 		if(p1->dist < p2->dist){
// 			return true;
// 		}
// 	}
// };



bool IsLessNode(node * a, node * b)
{
	return a->dist < b->dist;
}

int indexOfExistingNode(node* inq, node** arr,int totalSize){

	for(int i=0; i< totalSize; i++){
		if(arr[i]->name == inq->name){
			return i;
		}
	}

	return - 1;
}



vector<string> Graph::Dijkstra(string city, string destination, float &d)
{
	vector<string> vec;
	node* toPlace = this->getCity(city);
	node* fromPlace = this->getCity(destination);
	if (toPlace->name == fromPlace->name)
		return vec;
	vector<node*> dijkstraPath;
	for (int i = 0; i < cities.size(); ++i)
	{
		if (cities[i]->name	== city)
			cities[i]->dist = 0;
		else 
			cities[i]->dist = numeric_limits<float>::max();
	}
	//
	MinHeap<node*> path(cities.size(),&IsLessNode);

	for (int i = 0; i < cities.size(); ++i)
	{
		path.insertKey(cities[i]);
	}

	while(path.getHeapSize())
	{
		node* a = path.extractMin();
		vector<pair<node*,float> > neighbours;
		for(int i=0; i < a->edges.size();i++)
		{
			if (a->edges[i].Origin == a)
			{
				pair<node*, float > a1 = make_pair(a->edges[i].Dest,a->edges[i].weight);
				neighbours.push_back(a1);
			}

			else
			{
				pair<node*,float> a2 = make_pair(a->edges[i].Origin,a->edges[i].weight);
				neighbours.push_back(a2);
			}
		}

		for(int k=0; k< neighbours.size();k++)
		{
			if(neighbours[k].second + a->dist < neighbours[k].first->dist)
			{
				neighbours[k].first->dist = a->dist + neighbours[k].second;
				int ind = indexOf(neighbours[k].first,path.getHeap(),path.getHeapSize());
				path.decreaseKey(ind,neighbours[k].first);
				neighbours[k].first->prev = a;
			}
		}
	}
	node* temp = fromPlace;
	while(temp)
	{
		vec.push_back(temp->name);
		cout << "At: " << temp->name << " -> " << temp->dist << endl;
		temp = temp->prev;
	}
	reverse(vec.begin(), vec.end());
	return vec;
}

/*
WashingtonDC 5.71 2.25
Minneapolis 3.76 2.93
SanFrancisco 0.278 2.31
LasVegas 1.11 1.85
Dallas 3.31 1.04
*/
// int main(){
// 	Graph* g = new Graph((char*)"Small.txt");
// 	//g->display(g->cities[0]);
// 	//cout<<endl;
// 	//vector<node*> xxx = g->Kruskal();
// 	// cout << xxx[0]->edges.size() <<  endl;
// 	//g->display(xxx[0]);
// 	//printNode(xxx[1]);
// 	//cout<<endl;
// 	float td = 0;
// 	vector<string> v = g->Dijkstra("WashingtonDC","Dallas",td);



// }
#endif


// homo set mein masla he