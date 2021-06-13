#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;

void random_in_size(vector<int> &worst);
int hire_assistant(vector<int> v);

int main(){

    //User interface
    srand(time(0));
    int sz = -1;
    cout<<"Enter the size of the array :";
    cin>>sz;
    vector <int> worst;
    vector <int> best;

    //Worst-case
    for(int i=0 ; i<sz ; ++i){
        worst.push_back(i+1);
    }
    cout<<"----------------"<<endl;
    cout<<"People hired(worst-case) : "<<hire_assistant(worst)<<" people."<<endl;
    
    //Best-case
    for(int i=0 ; i<sz ; ++i){
        best.push_back(sz-i);
    }
    cout<<"----------------"<<endl;
    cout<<"People hired(best-case) : "<<hire_assistant(best)<<" people."<<endl;

    //Build the random vector
    int avg[20];
    int sum=0;
    for (int i=0 ; i<20 ; ++i){
        random_in_size(worst);
        avg[i] = hire_assistant(worst);
    }
    for(int i=0 ; i<20 ; ++i){
        sum += avg[i];
    }
    sum = sum/20;
    cout<<"----------------"<<endl;
    cout<<"People hired(random-scenario, avergae) : "<<sum<<" people."<<endl;
    cout<<"----------------"<<endl;

    main();
    return 0;
}

void random_in_size(vector<int> &worst){
    int sz = worst.size();
    int part = (sz/20000);
    if(part < sz/20000.0)
        part++;
    for(int i=0 ; i<worst.size() ; ++i){
        int randompart = rand()%(part);
        int remain = sz - (part-1)*20000;
        int randremain = rand()%(remain);
        int randomnumber = randompart*20000 + randremain;
        //Swap worst[i] with worst[randomnumber]
        int temp  = worst[i];
        worst[i] = worst[randomnumber];
        worst[randomnumber] = temp;
    }
}

int hire_assistant(vector<int> v){
    int hire = 1;
    int best = 0;
    for(int i=1 ; i<v.size() ; ++i){
        //Interview candidate
        if(v[i] > v[best]){
            best = i;
            hire++;
        }
    }
    return hire;
}
