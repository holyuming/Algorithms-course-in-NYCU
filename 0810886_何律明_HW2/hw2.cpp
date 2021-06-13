#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;


struct data {
    int maxright, maxleft, leftsumplusrightsum;
};


void ptarr(int arr[], int sz);
void ptdata(data input);
data FIND_MAX_CROSSING_SUBARRAY(int arr[], int low, int mid, int high);
data FIND_MAXIMUM_SUBARRAY(int arr[], int low, int high);
data Brute_Force(int arr[], int low, int high);



int main(){

    // User interface
    int sz;
    cout<<"Enter the size :";
    cin>>sz;

    //Array initialization
    int Arr[sz];
    srand(time(0));
    for (int i=0 ; i < sz ; ++i){
        Arr[i] = pow(-1, rand()) * rand();
    }

    int arr[sz-1];
    for(int i=0 ; i<sz-1 ; ++i){
        arr[i] = Arr[i+1] - Arr[i];
    }

    //Divide-and-Couquer
    double start = clock(), end;
    data ans1 = FIND_MAXIMUM_SUBARRAY(arr, 0, sz-2);
    ans1.maxright++;
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time for divide and conquer : "<<cpu_time_used*1000<<" ms"<<endl;
    ptdata(ans1);

    //Brute-Force
    start = clock();
    data ans2 = Brute_Force(Arr, 0, sz);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time for brute-force : "<<cpu_time_used*1000<<" ms"<<endl;
    ptdata(ans2);
    return 0;
}

void ptarr(int arr[], int sz){
    for (int i=0 ; i < sz ; ++i){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void ptdata(data input){
    cout<<"----------------------"<<endl;
    cout<<"Max-left : "<<input.maxleft<<endl;
    cout<<"Max-right : "<<input.maxright<<endl;
    cout<<"Difference : "<<input.leftsumplusrightsum<<endl;
    cout<<"----------------------"<<endl;
}

data FIND_MAX_CROSSING_SUBARRAY(int arr[], int low, int mid, int high){

    //Initialization
    data returndata;

    //Start finding
    int sum = 0;
    sum += arr[mid];
    int left_sum = sum;
    returndata.maxleft = mid;
    for (int i=mid-1 ; i>=low ; --i){
        sum += arr[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            returndata.maxleft = i;
        }  
    }

    sum = 0;
    sum += arr[mid+1];
    int right_sum = sum;
    returndata.maxright = mid+1;
    for (int j=mid+2 ; j<=high ; ++j){
        sum += arr[j];
        if (sum > right_sum)
        {
            right_sum = sum;
            returndata.maxright = j;
        }
    }   
    returndata.leftsumplusrightsum = left_sum + right_sum;

    return returndata; 
}

data FIND_MAXIMUM_SUBARRAY(int arr[], int low, int high){
    if (low == high){
        data tmp;
        tmp.maxleft = low;
        tmp.maxright = high;
        tmp.leftsumplusrightsum = arr[low];
        return tmp;
    }
    else{
        int mid = floor((low + high)/2);
        data left, right, cross;
        left =  FIND_MAXIMUM_SUBARRAY(arr, low, mid);
        right = FIND_MAXIMUM_SUBARRAY(arr, mid+1, high);
        cross = FIND_MAX_CROSSING_SUBARRAY(arr, low, mid, high);
        if(left.leftsumplusrightsum >= right.leftsumplusrightsum && left.leftsumplusrightsum >= cross.leftsumplusrightsum){
            return left;
        }
        else if(right.leftsumplusrightsum >= left.leftsumplusrightsum && right.leftsumplusrightsum >= cross.leftsumplusrightsum){
            return right;
        }
        else{
            return cross;
        }
    }
}

data Brute_Force(int arr[], int low, int high){
    data tmp;
    int diff = INT32_MIN;
    for(int i=low ; i<high ; ++i){
        for(int j=i+1 ; j<high ; ++j){
            if(arr[j] - arr[i] > diff){
                diff = arr[j] - arr[i];
                tmp.maxleft = i;
                tmp.maxright = j;
                tmp.leftsumplusrightsum = diff;
            }
        }
    }
    return tmp;
}