#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct node
{
	string data;
	node* parent;
	node* f_child;
	node* sibling;
	node(string num)
	{
		data = num;
		parent = NULL;
		f_child = NULL;
		sibling = NULL;
	}
};
class tree
{
	node* head;
public:
	tree()
	{
		head = NULL;
	}
	// tree(vector<string> v)
	// {
	// 	if(v.size() == 0)
	// 	{
	// 		head = NULL;
	// 	}

	// }
	void insert(vector<string> v)
	{
		if(v.size() == 0)
		{
			cout<<"DANGER"<<endl;
			return;
		}
		if(head == NULL)
		{
			node* newNode = new node(v[0]);
			head = newNode;
			if(v.size() < 2)
				return;
			node* newNode2 = new node(v[1]);
			head->f_child = newNode2;
			newNode2->parent = newNode;
			node* par_point = newNode2;
			for(int i=0; i< v.size(); i++)
			{
				if(i > 1)
				{
					node* newNode3 = new node(v[i]);
					newNode3->parent = par_point;
					par_point->f_child = newNode3;
					par_point = newNode3;
				}
			}
			return;
		}
		helpInsert(v,head);
	}

	void helpInsert(vector<string> v, node* point)
	{//cout<<"Flag "<< v[0] << " "<<point->data <<endl;
		if(v.size() == 2 )//&& v[0] == point->data)
		{
			node* tmp = point->f_child;
			if(tmp)
			{
				while(tmp->sibling)
			 		tmp = tmp->sibling;
				node* nNode = new node(v[1]);
				tmp->sibling = nNode;
				nNode->parent = tmp ->parent;
				return;
			} //cout<<"lop"<<endl;
			node* nNode = new node(v[1]);
			if(nNode->data == "CS 678")
			{
				for(int i=0; i< v.size(); i++)
				{
					//cout<<"++++++ "<< v[i] <<endl;
				}
			}
			point->f_child = nNode;
			nNode->parent = point;
			return;
			
		}
		//cout<< "see" << v[0]<<" "<< point->f_child->data << endl;
		v.erase(v.begin());
		//cout<< "see2" << v[0]<<" "<< point->f_child->data <<endl;
		node* sib = point->f_child;
	//	cout<< point->f_child->sibling->data<<endl;
		while(sib && sib->data != v[0])
		{

			sib = sib->sibling;
		}
		helpInsert(v,sib);
		return;
		 	

	}
	
	void print(node* t)
	{
		if(t == NULL)
			return;
		print(t->sibling);
		cout<< t->data <<"-------";
		if(t->parent)
			cout<<t->parent->data;
		cout<<endl;
		print(t->f_child);
	}
	void printt()
	{
		print(head);
	}


	vector<string> stringToVector(string line)
{
	vector<string> v;
	int total_slash=-1;
	for(int i=0; i< line.length(); i++)
	{
		char auxx = line[i];
		if(auxx == '/')
			total_slash++;
	}
	int totalSlash = total_slash;
	int init = 3;
BRB:
	string aux = line.substr(init,1);
	while(1)
	{
		init++;
		if(line.substr(init,1) != "/")
		{
			aux =aux + line.substr(init,1);
		}
		else
		{
			totalSlash--;
			v.push_back(aux);
			break;
		}
	}
	init++;
	if(totalSlash > 0)
	{
		goto BRB;
	}
	v.push_back(line.substr(init));
	return v;
}


vector<string> lineToVector(string fileName, int lineNumber)
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
	return v;
}
};
int main()
{
	tree* tr = new tree;
	tr->insert(tr->lineToVector("input_test.txt",1));
	tr->insert(tr->lineToVector("input_test.txt",2));
	tr->insert(tr->lineToVector("input_test.txt",3));
	tr->insert(tr->lineToVector("input_test.txt",4));
	tr->insert(tr->lineToVector("input_test.txt",5));
	tr->insert(tr->lineToVector("input_test.txt",6));
	tr->insert(tr->lineToVector("input_test.txt",7));
	tr->insert(tr->lineToVector("input_test.txt",8));
	tr->insert(tr->lineToVector("input_test.txt",9));
	tr->insert(tr->lineToVector("input_test.txt",10));
	tr->insert(tr->lineToVector("input_test.txt",11));
	tr->insert(tr->lineToVector("input_test.txt",12));
	tr->insert(tr->lineToVector("input_test.txt",13));

	cout<<endl<<endl;
	tr->printt();
	return 0;
}