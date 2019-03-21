//*****************************************************************************
//
// This part requires all the work to be done in this file only.
// You will be modifying this function only ->
//
//
//
//*****************************************************************************



#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "stack.cpp"

using namespace std;

void towers(Stack<int>& a, Stack<int>& b, Stack<int>& c);
bool testing();

int main()
{
	if (testing())
	{
		cout << "Test cases passed." << endl;
	} else {
		cout << "Test cases failed." << endl;
	}
}
void towers2(int tot, Stack<int>& a, Stack<int>& b, Stack<int>& c);

void towers(Stack<int>& a, Stack<int>& b, Stack<int>& c)
{
	//return;
	//for(int i=0; i< a.length(); i++)
	{
		towers2 (a.length(), a, b, c);
	}
}

void towers2(int tot, Stack<int>& a, Stack<int>& b, Stack<int>& c)
{
	if(tot < 1)
		return;
	towers2(tot-1, a, c, b);
	c.push(a.pop());
	towers2(tot-1, b,a,c);
	//towers2(tot-1, c ,a , b);
}

bool testing()
{
	srand(time(NULL));
	int maxValue = 500;
	
	for (int i = 1; i < 30; ++i)
	{
		Stack<int> a;
		Stack<int> b;
		Stack<int> c;
		vector<int> temp;
		//cout << "Here "<< i <<endl;
		for (int j = 0; j < i/**/; ++j)
			temp.push_back((rand()+1) % maxValue);
		sort(temp.begin(), temp.end());

		for (int j = 0; j < i /**/; ++j)
			a.push(temp[i /**/ - j - 1]);
		//cout << "Before" << i <<endl;
		towers(a, b, c);
		//cout << "Before" << i<<endl;
		for (int j = 0; j < i /**/; ++j)
		{
			if (   temp[j] != c.pop())
			{
				return false;
			}
			//cout << "XYZ" << i << " "<<j<<endl;
		}
		//cout <<"AFTER "<< i <<endl;
	}

	return true;
}

