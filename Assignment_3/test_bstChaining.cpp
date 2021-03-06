#include <iostream>
#include "bstChaining.h"
#include <fstream>
#include <vector>
#include <time.h>


#include <thread>
#include <chrono>
#include <future>



using namespace std;

bool timeOut;

promise<bool> done;
void timer(future<bool> done_future){
    std::chrono::seconds span (20);
    if(done_future.wait_for(span) == std::future_status::timeout) {
        timeOut = true;
    }
}

void test(vector<string> allWords, vector<string> queries, promise<bool> done_future){
    using namespace std::chrono;
    HashC* map = new HashC(202001);
    high_resolution_clock::time_point timeStart = high_resolution_clock::now();;
    // LOADING ALL THE ENTRIES
    for(int i=0;i<allWords.size();i++){
        map->insert(allWords[i]);
        if(timeOut){
            cout << "TEST FALED\n" << "TIMED OUT"<<endl;
            return;
        }
        
    }
    // SEARCHING ALL THE ENTRIES
    for(int i=0;i<allWords.size();i++){
        
        if (map->lookup(allWords[i])->value != allWords[i]){
            cout << "TEST FAILED\n" << "LOOKUP FAILED" << endl;
            return;
        }
        if(timeOut){
            cout << "TEST FAILD\n" << "TIMED OUT"<<endl;
            return;
        }
    }
    // //DELETING SOME ENTRIES
    for(int i=0;i<queries.size();i++){
        map->deleteWord(queries[i]);
        if(timeOut){
            cout << "TEST fAILED\n" << "TIMED OUT"<<endl;
            return;
        }
    }
    for(int i=0;i<queries.size();i++){
        if (map->lookup(queries[i])->value != "0000"){
           
            cout << "TEST FAILLED\n" << "L0oKUP FAILED" << endl;
        }
        if(timeOut){
            cout << "TEST FAInLED\n" << "TIMED OUT"<<endl;
            return;
        }
    }
    done_future.set_value(true);
    high_resolution_clock::time_point timeEnd = high_resolution_clock::now();;
    duration<double> totalTime = duration_cast<duration<double>>(timeEnd - timeStart);
    cout << "TEST PASSED IN : " << totalTime.count() << " SECONDS."<<endl;
}

int main(){
    vector<string> allWords;
    vector<string> queries;
    srand(time(NULL));
    ifstream file;
    file.open("words.txt");
    cout << "LOADING THE FILE" << endl;
    string temp;
    while(!file.eof()){
        file >> temp;
        allWords.push_back(temp);
        int x = rand()%5;
        if (x<2){
            queries.push_back(temp);
        }
    }
    file.close();
    cout << allWords.size() << " words loaded." << endl;
    timeOut = false;
    
    future<bool> done_future = done.get_future();
    thread first (timer, move(done_future));
    test(allWords, queries, move(done));
    first.join();
    return 0;
}