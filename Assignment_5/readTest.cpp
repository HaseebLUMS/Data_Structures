#include <iostream>
#include <fstream>
using namespace std;
int main(){
	string name = "Small.txt";
	ifstream file;
	file.open(name);
	string test;
	file >> test;
	file >>test;
	cout<<test<<endl;
	int a;
	file >> a;
	cout<<a<<endl;
	while(!file.eof()){
		file >> test;
		cout<<test<<endl;
	}
	return 0;
}