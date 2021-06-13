#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

//print the whole sorted array
void ptarr(int arr[], int s){
    for(int i=0 ; i<s ; ++i){
        cout<<arr[i]<<" ";
    }    
    cout<<endl;
}

// Copy an array
void copyarr(int arr[], int tmp[], int s){
    for(int i=0 ; i<s ; ++i){
        tmp[i] = arr[i];
    }
}

//insertion sort
void insertionsort(int arr[], int s){
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

// Merge
void merge(int arr[], int p, int q, int r){
    int n1=q-p+1, n2=r-q;
    int L[n1], R[n2];
    for (int i = 0; i < n1; ++i){
        L[i] = arr[p+i];
    }
    for (int i = 0; i < n2; ++i){
        R[i] = arr[q+1+i];
    }
    int i=0, j=0;
    for (int k=p; k <= r; ++k){
        // R is empty or L <= R, move L to arr
        if ((j==n2 || L[i]<=R[j]) && i!=n1){
            arr[k] = L[i];
            ++i;
        }
        // L is empty or L > R, move R to arr
        else if((i==n1 || L[i]>R[j]) && j!=n2){
            arr[k] = R[j];
            ++j;
        }
    }
}

// Merge-Sort recursively
void mergesort(int arr[], int p, int r){
    if(p < r){
        double q = floor((p+r)/2);
        mergesort(arr, p, q);
        mergesort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

int main(){

    // Initial the clock variable
    double start, end;
    double cpu_time_used;

    // Let the user enter the array size
    srand(time(0));
    int s = -1;
    while(s < 0){
        cout<<"Enter the array size : ";
        cin>>s;
    }

    // Initialize the array
    int arr[s];
    for(int i=0 ; i<s ; ++i){
        arr[i] = rand();
    }

    cout<<"------------------------"<<endl;
    
    // Insertion sort
    int tmp[s];
    copyarr(arr, tmp ,s);
    start = clock();
    insertionsort(tmp, s);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time for insertion sort :"<<cpu_time_used<<" s"<<endl;

    cout<<"------------------------"<<endl;

    // Merge-Sort
    copyarr(arr, tmp, s);
    start = clock();
    mergesort(tmp, 0, s-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time for merger-sort :"<<cpu_time_used<<" s"<<endl; 

    cout<<"========================"<<endl;

    //main();
    return 0;
}
