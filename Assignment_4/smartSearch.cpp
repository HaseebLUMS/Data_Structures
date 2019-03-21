#include <fstream>
#include "sorts.cpp"
#include <algorithm>
#include <time.h>
using namespace std;


// A single pair is stored in a Vector<long>
// You have to return a vector of all pairs.
vector< vector<long> > smartSearch(vector<long> nums, long k)
{
    nums = QuickSortArray(nums);
    vector<long> numsArray;
    bool Gr = false;
    int indVec = 0;
    int indArr = 0;
    while(!Gr){
        if(nums[indVec] <= k){
            numsArray.push_back(nums[indVec]);
            indVec++;
        }else{
            Gr = true;
        }
    }

    int st = 0;
    int en = indVec-1;
    vector< vector<long> > finalResult;

    while(st< en){
        long sum = numsArray[st]+numsArray[en];
        if(sum == k){
            vector<long> v;
            v.push_back(numsArray[st]);
            v.push_back(numsArray[en]);
            finalResult.push_back(v);
            vector<long> v1;
            v1.push_back(numsArray[en]);
            v1.push_back(numsArray[st]);
            finalResult.push_back(v1);
            st++;
        }else if(sum < k){
            st++;
        }else if(sum >k){
            en--;
        }
    }

    return finalResult;

    
}


int main()
{
    clock_t tStart = clock();
    vector<long> nums;
    ifstream in("random.txt");
    long n;
    while(in >> n)
        nums.push_back(n);
    in.close();

    long k;
    cout << "Enter the value of K: ";
    cin >> k;

    vector< vector<long> > result = smartSearch(nums, k);
    cout<< result.size()<<endl;
    for(int i = 0; i < result.size(); i++)
        cout << result[i][0] << ", " << result[i][1] << endl;


    
    cout<<"Test Passes in "<< (double(clock() - tStart)/CLOCKS_PER_SEC) << " seconds."<<endl;
    return 0;
}