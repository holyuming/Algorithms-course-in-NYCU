#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

void Quicksort(vector <int> &A, int p, int r);
int Partition(vector <int> &A, int p, int r);
void RM_Quicksort(vector <int> &A, int p, int r);
int RM_Partition(vector <int> &A, int p, int r);
void random_in_size(vector<int> &v);
void Insertionsort(vector <int> &arr);
void copyandnew(vector <int> &a, vector <int> &b); //Copy the element from b to a

double timesofcomparisons = 0;

int main(){

    //(a)
    //Initialize the 1000 elements vector 
    srand(time(0));
    double ts, te, sum = 0;
    vector <int> v[10];
    for(int i=0 ; i<1000 ; ++i){
        v[0].push_back(999-i);
    }
    for(int j=0 ; j<9 ; ++j){
        copyandnew(v[j+1], v[j]);
    }
    for(int i=0 ; i<10 ; ++i){
        ts = clock();
        RM_Quicksort(v[i], 0, v[i].size());
        te = clock();
        sum = sum + (te-ts);
    }
    cout<<"When the array size is 1000 : "<<endl;
    cout<<"(a)"<<endl<<"The average times of comparisons in each RM_Quicksort is : ";
    cout<<timesofcomparisons/10.0<<endl;
    cout<<"Average excution time : "<<sum/10.0<<" ms"<<endl;
    
    //(b)
    timesofcomparisons = 0;
    sum = 0;
    for(int i=0 ; i<10 ; ++i){
        random_in_size(v[i]);
        ts = clock();
        Quicksort(v[i], 0, v[i].size());
        te = clock();
        sum = sum + (te-ts);      
    }
    cout<<"(b)"<<endl<<"The average times of comparisons in each Quicksort after random permutations : ";
    cout<<timesofcomparisons/10.0<<endl;
    cout<<"Average excution time : "<<sum/10.0<<" ms"<<endl;

    //(c)
    cout<<"----------------------------"<<endl<<"(c)"<<endl;
    vector <int> v1; //For randomized quicksort 
    vector <int> v2; //For insertion sort
    while(1){
        int sz;
        cout<<"Enter the size of the array : ";
        cin>>sz;
        for(int i=0 ; i<sz ; ++i){
            v1.push_back(i);
        }
        random_in_size(v1);
        copyandnew(v2, v1);
        ts = clock();
        RM_Quicksort(v1, 0, v1.size()-1);
        te = clock();
        cout<<"Time for RM_Quicksort : "<<(te-ts)<<" ms "<<endl;
        ts = clock();
        Insertionsort(v2);
        te = clock();
        cout<<"Time for Insertionsort : "<<(te-ts)<<" ms "<<endl;
    }
    return 0;
}

void Quicksort(vector <int> &A, int p, int r){
    if (p < r){
        int q = Partition(A, p, r);
        Quicksort(A, p, q-1);
        Quicksort(A, q+1, r);
    }
}

int Partition(vector <int> &A, int p, int r){
    int x = A[r];
    int i = p - 1; //Start from -1
    for (int j=p ; j<r ; ++j){
        timesofcomparisons++;
        if(A[j] <= x){
            ++i;
            //Swap
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}

void RM_Quicksort(vector <int> &A, int p, int r){
    if (p < r){
        int q = RM_Partition(A, p, r);
        RM_Quicksort(A, p, q-1);
        RM_Quicksort(A, q+1, r);
    }   
}

int RM_Partition(vector <int> &A, int p, int r){
    //Random(p, r)
    int sz = r-p+1;
    int i;
    if (sz >= 20000){
        int part = (sz/20000);
        if(part < sz/20000.0)
            part++;
        int randompart = rand()%(part);
        int remain = sz - (part-1)*20000;
        int randremain = rand()%(remain);
        int randomnumber = randompart*20000 + randremain; 
        i = randomnumber + p;
    }
    else{
        i = rand()%(sz) + p;
    }
    i = rand()%(sz) + p;
    int tmp = A[i];
    A[i] = A[r];
    A[r] = tmp;
    return Partition(A, p, r);
}

void random_in_size(vector<int> &v){
    int sz = v.size();
    int part = (sz/20000);
    if(part < sz/20000.0)
        part++;
    for(int i=0 ; i<v.size() ; ++i){
        int randompart = rand()%(part);
        int remain = sz - (part-1)*20000;
        int randremain = rand()%(remain);
        int randomnumber = randompart*20000 + randremain;
        //Swap v[i] with v[randomnumber]
        int temp  = v[i];
        v[i] = v[randomnumber];
        v[randomnumber] = temp;
    }
}

void Insertionsort(vector <int> &arr){
    int s = arr.size();
    for(int i=1 ; i<s ; ++i){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && key<arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void copyandnew(vector <int> &a, vector <int> &b){
    int sz = b.size();
    for(int i=0 ; i<sz ; ++i){
        a.push_back(b[i]);
    }
}