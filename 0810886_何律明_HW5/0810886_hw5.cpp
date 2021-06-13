#include <iostream>
using namespace std;

int price[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
int Memorized_Cut_Rod(int price[], int n, int r[], int s[]);
int Memorized_Cut_Rod_Aux(int price[], int n, int r[], int s[]);
int Extended_Bottom_Up_Cut_Rod(int price[], int n, int r[], int s[]);
int Print_Cut_Rod_Solution(int n, int s[]);
void ck(int r1[], int sz);

int main(){
    int td=87, bu=14;
    int r1[td+1], r2[bu+1];
    int s1[td+1]={0}, s2[bu+1]={0};

    //Top down
    cout<<"Top Down :"<<endl;
    cout<<"Total length : "<<td<<endl;
    cout<<"Price :"<<Memorized_Cut_Rod(price, td, r1, s1)<<endl;
    cout<<Print_Cut_Rod_Solution(td, s1)<<" pieces of rod"<<endl<<endl;
    /*ck(r1,88);
    ck(s1,88);*/

    //Bottom up
    cout<<"Bottom up :"<<endl;
    cout<<"Total length : "<<bu<<endl;
    cout<<"Price :"<<Extended_Bottom_Up_Cut_Rod(price, bu, r2, s2)<<endl; 
    cout<<Print_Cut_Rod_Solution(bu, s2)<<" pieces of rod"<<endl<<endl;
    /*ck(r2,15);
    ck(s2,15);*/
    return 0;
}

int Memorized_Cut_Rod(int price[], int n, int r[], int s[]){
    r[0] = 0;
    for(int i=1 ; i<=n ; ++i){
        r[i] = INT_MIN;
    }
    return Memorized_Cut_Rod_Aux(price, n, r, s);
}

int Memorized_Cut_Rod_Aux(int price[], int n, int r[], int s[]){
    int q;
    if(r[n] >= 0){
        return r[n];
    }
    else{
        q = INT_MIN;
        for(int i=1 ; i<=n ; ++i){
            int tmp, m;
            if(i>10){
                tmp = r[i];
            }
            else
                tmp = price[i-1];
            m = Memorized_Cut_Rod_Aux(price, n-i, r, s);
            if(q < tmp+m){
                q = tmp+m;
                s[n] = i;
            }
        }
    }
    r[n] = q;
    return q;
}

int Extended_Bottom_Up_Cut_Rod(int price[], int n, int r[], int s[]){
    r[0] = 0;
    for(int i=1 ; i<=n ; ++i){
        r[i] = INT_MIN;
    }
    int q;
    for(int j=1 ; j<=n ; ++j){
        q = INT_MIN;
        for(int i=1 ; i<=j ; ++i){
            int tmp;
            if(i>10)
                tmp = r[i];  
            else
                tmp = price[i-1];
            if(q < tmp+r[j-i]){
                q = tmp+r[j-i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return r[n];
}

int Print_Cut_Rod_Solution(int n, int s[]){
    int time = 0;
    while(n>0){
        cout<<s[n]<<" ";
        ++time;
        n -= s[n];
    }
    cout<<endl;
    return time;
}

void ck(int r1[], int sz){
    for(int i=0 ; i<sz ; ++i){
        cout<<r1[i]<<" ";
    }
    cout<<endl;    
}