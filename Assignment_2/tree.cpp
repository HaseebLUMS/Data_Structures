#ifndef __TREE_CPP
#define __LIST_CPP
#include "tree.h"
#include <fstream>
#include <algorithm>

Tree::Tree()
{
	head = NULL;
}

Tree::Tree(string fileName)
{
	head = NULL;
	int totalLines = 0;
	ifstream file;
	file.open(fileName);
	string line;
	while(!file.eof())
	{
		totalLines++;
		getline(file,line);
	}
	for(int i=1; i<= totalLines; i++)
	{
		vector<string> v = lineToVector(fileName,i);
		//cout<<"gp"<<endl;
		insert(v);
		//cout<<"xe"<<endl;
	}
	//cout<<"haseeb"<<endl;
}
Tree::~Tree()
{
}
vector<string> Tree::stringToVector(string line)
{
	///////////////////////////
	vector<string>v;
	line = line + '/';
	string s = "";
	for(int i=0; i< line.length(); i++) // 3
	{
		if(line[i] != '/')
			s = s+line[i];
		else
		{
			v.push_back(s);
			//cout<< s<<endl;
			s = "";
		}
	}
	return v;
	//////////////////////////
// 	vector<string> v;
// 	int total_slash=-1;
// 	for(int i=0; i< line.length(); i++)
// 	{
// 		char auxx = line[i];
// 		if(auxx == '/')
// 			total_slash++;
// 	}
// 	int totalSlash = total_slash;
// 	v.push_back(line.substr(0,2));
// 	int init = 3;
// BRB:
// 	string aux = line.substr(init,1);
// 	while(1)
// 	{
// 		init++;
// 		if(line.substr(init,1) != "/")
// 		{
// 			aux =aux + line.substr(init,1);
// 		}
// 		else
// 		{
// 			totalSlash--;
// 			v.push_back(aux);
// 			break;
// 		}
// 	}
// 	init++;
// 	if(totalSlash > 0)
// 	{
// 		goto BRB;
// 	}
// 	v.push_back(line.substr(init));
// 	return v;
}

vector<string> Tree::lineToVector(string fileName, int lineNumber)
{
	vector<string> v;
	
	ifstream file;
	file.open(fileName);
	string line;
	for(int i=0; i<lineNumber;i++)
	{
		getline(file,line);
	}
	v= stringToVector(line);
	//cout<<"haha"<<endl;
	return v;
}

void Tree::insert(vector<string> v)
{
	if(v.size() == 0)
	{
		//cout<<"DANGER"<<endl;
		return;
	}

	if(head == NULL)
	{

		TreeItem* newNode = new TreeItem(v[0]);
		head = newNode;

		if(v.size() < 2)
			return;

		TreeItem* newNode2 = new TreeItem(v[1]);
		head->FChild = newNode2;
		newNode2->Parent = head;
		//cout<< "CHILD :"<< newNode2->value << " PARENT : "<< head->value<<endl;
		TreeItem* par_point = newNode2;
		for(int i=0; i< v.size(); i++)
		{
			if(i > 1)
			{
				//cout<<"HELLLLLLLLo"<<endl;
				TreeItem* newNode3 = new TreeItem(v[i]);
				newNode3->Parent = par_point;
				TreeItem* rec= newNode3->Parent;
				par_point->FChild = newNode3;
				par_point = newNode3;
				//cout<< "CHILD :"<< newNode3->value
				// << " PARENT : "<< rec->value<<endl;

			}
		}
		return;
	}
	helpInsert(v,head);
}

void Tree::helpInsert(vector<string> v, TreeItem* point)
{
	if(v.size() == 0)
	{
		return;
	}
	if(v.size() == 2 )//&& v[0] == point->value)
	{//cout<<"lp"<<endl;
		TreeItem* tmp = point->FChild;
		if(tmp)
		{//cout<<"pl"<<endl;
			int i=0;
			//cout<<endl<<endl<<"LORA"<<endl<<endl;
			while(tmp->NextS)
			{
				i=1;
				tmp = tmp->NextS;
			}
			TreeItem* nNode = new TreeItem(v[1]);
			tmp->NextS = nNode;
			//cout<< "CHILD :"<< nNode->value
			 //<< " PARENT : "<< tmp->Parent->value <<endl;
			nNode->Parent = tmp->Parent;
			return;
		}//cout<<"pl"<<endl;
		TreeItem* nNode = new TreeItem(v[1]);
		//cout<<"flag"<<endl;
		point->FChild = nNode;
		nNode->Parent = point;
		return;
		
	}
	//cout<<"here"<<endl;
	
	v.erase(v.begin());
	//cout<<"there"<<endl;
	//cout<<"ALALA"<<endl;
	TreeItem* sib = NULL;
	if(point)
	{
		sib = point->FChild;
		while(sib && sib->value != v[0])
		{
			//cout<<"hello"<<endl;
			sib = sib->NextS;
		}
	}//cout<<"kk"<<endl;
	//cout<< v[0]<<endl;
	helpInsert(v,sib);
	//cout<<"ee"<<endl;
	return;
}


vector<string> Tree::Locate(string qry)
{
	 vector<string> v;
	 auxLocate(head,qry,v);
	 // if(v.size())
	 // 	v.push_back("C:");
	// v.push_back("KAAM , HARVARD, STANFROD, MIT, MICROSOFT");
	 return v;
}

string Tree::LComAc(string a, string b)
{
	vector<string> v1 = Locate(a);
	vector<string> v2 = Locate(b);
	for(int i=0; i <  v1.size(); i++)
	{
		if (find(v2.begin(), v2.end(), v1[i]) != v2.end())
		{
			return v1[i];
		}
	}
}

TreeItem* Tree::getHead()
{
	return head;
}
void Tree::auxCount(TreeItem* t,int& i)
{
	if(t == NULL)
		return;
	auxCount(t->NextS,i);
	//cout<< t->value <<"         - with parent - ";
	 if(!t->FChild)
	 {
	 	i++;
	 	//cout<<"A"<<endl;
	 	//cout<< t->Parent->value;
	 }
	auxCount(t->FChild,i);
}
int Tree::countFiles()
{
	int i=0;
	auxCount(head, i);
	return i;
}
TreeItem* Tree::auxDelete(TreeItem* t, vector<string> v, TreeItem* &t2)
{
	if(t == NULL)
		return NULL;
	auxDelete(t->NextS,v,t2);
	 if(t->value == v[0])
	 {
	 	TreeItem* par = t->Parent;
	 	if(par->FChild->value == t->value)
	 	{
	 		cout<< par->FChild->value<<endl;
	 		TreeItem* tmp3 = par->FChild;
	 		par->FChild = t->NextS;
	 		t2 = tmp3;
	 		return tmp3;
	 	}
	 	else
	 	{
	 		TreeItem* tmp = t->Parent->FChild;
	 		while(tmp)
	 		{
	 			if(tmp->NextS->value == t->value)
	 			{
	 				TreeItem* toReturn = tmp->NextS;
	 				//cout<< toReturn <<endl<< toReturn->value<<endl;
	 				tmp->NextS = tmp->NextS->NextS;
	 				t2 = toReturn;
	 				return toReturn;
	 			}
	 			
	 			{
	 				tmp = tmp->NextS;
	 			}
	 		}
	 	}
	 }
	auxDelete(t->FChild,v,t2);
}
void Tree::deleteFolder(vector<string> v)
{
	//auxDelete(head,v);
}
void Tree::insertInFolder(TreeItem* t,TreeItem* tmp, vector<string> v2)
{
	//cout<< t <<endl;
	//cout<<tmp<<endl;
	//cout<<v2[0]<<endl;
	if(t == NULL)
		return;
	insertInFolder(t->NextS,tmp,v2);
	if(t->value == v2[0])
	{
		//cout<<"kk "<< t->value << " "<< v2[0] <<endl;
		TreeItem* tmp2 = t->FChild;
		
		t->FChild = tmp;
		tmp->NextS = tmp2;
		tmp->Parent = t;
		return;
	}
	insertInFolder(t->FChild,tmp,v2);
}
void Tree::moveFolder(string fromFolder,string toFolder)
{
	vector<string> v1 = Locate(fromFolder);
	string anc = LComAc(fromFolder,toFolder);
	TreeItem* tmpp = NULL;
	
	TreeItem* tt = getParent(head, fromFolder, tmpp);
	if(anc == tmpp->value)
		return;
	vector<string> v2 = Locate(toFolder);
	//cout<< v1[0]<<endl;
	TreeItem* t2 = NULL;
	TreeItem* tmp = auxDelete(head,v1,t2);
	//cout<<t2->value << "YE" <<endl;
	insertInFolder(head,t2,v2);

}
TreeItem* Tree::getParent(TreeItem* t,string s,TreeItem* &t2)
{
	if(t == NULL)
		return t;
	getParent(t->NextS,s,t2);
	if(t->value == s)
	{
		t2 = t;
		return t;
	}
	getParent(t->FChild,s, t2);

}
void Tree::auxLocate(TreeItem* t,string qry, vector<string>& v)
{
	if(t == NULL)
	{
		return;
	}
	auxLocate(t->NextS, qry,v);
	{
		if(t->value == qry)
		{
			TreeItem* tmp = t;
			while(tmp)
			{
				//cout<< tmp->value << " ";
				v.push_back(tmp->value);
				tmp = tmp->Parent;
			}
			
		}
	}
	auxLocate(t->FChild, qry,v);
}

void Tree::printt(TreeItem* t)
{
	if(t == NULL)
		return;
	printt(t->NextS);
	cout<< t->value <<"         - with parent - ";
	 if(t->Parent){cout<< t->Parent->value;}cout<<endl;
	printt(t->FChild);
}
void Tree::print()
{
	printt(head);
}

// int main()
// {
// 	Tree* tr = new Tree("input_bonus.txt");
// 	 tr->print(); cout<<endl;
// 	// vector<string> v = tr->Locate("handout.pdf");
// 	// //cout<< v[0]<<endl;
// 	// tr->moveFolder("handout.pdf","Spring'13");
// 	// tr->print();
	
// 	return 0;
// }



#endif
