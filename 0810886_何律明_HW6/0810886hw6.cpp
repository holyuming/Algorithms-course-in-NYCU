#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

vector<int> X{6, 6, 6, 0, 8, 9, 4, 5, 7, 9, 4, 5, 3};
vector<int> Y{1, 6, 8, 0, 4, 8, 7, 5, 4, 8, 7, 7, 4, 1, 4};
int retrieve(vector<int> X, int i);
void LCS_length(vector<int> X, vector<int> Y, int** b, int** c);
void LCS( int** b, vector<int> X, int i, int j);
void output(vector<int> X);
void generate(vector <int> &x, int sz);
void pt(int **c, int m, int n);

int main(){
    srand(time(0));
    int m = X.size();
    int n = Y.size();
    int **b = new int*[m+1];
    int **c = new int*[m+1];
    for(int i=0 ; i<=m ; ++i){
        b[i] = new int[n+1];
        c[i] = new int[n+1];
    }
    cout<<"X:";
    output(X);
    cout<<"Y:";
    output(Y);
    LCS_length(X, Y, b, c);
    cout<<"Z:";
    LCS(b, X, m, n);
    cout<<endl;
    cout<<"Length:"<<c[m][n];
    cout<<endl<<endl;

    /*pt(c, m, n);
    pt(b, m, n);*/
    for(int i=0 ; i<=m ; ++i){
        delete[] b[i];
        delete[] c[i];
    }
    delete [] b;
    delete [] c;
    cout<<"Random generated array,"<<endl;
    cout<<"Please enter the size of X and Y respectively,"<<endl;
    int sizex, sizey, ts, te, ts1, te1;
    vector <int> x;
    vector <int> y;
    while(1){
        cout<<"X :";
        cin>>sizex;
        cout<<"Y :";
        cin>>sizey;
        generate(x, sizex);
        generate(y, sizey);
        b = new int*[sizex+1];
        c = new int*[sizex+1];
        for(int i=0 ; i<=sizex ; ++i){
            b[i] = new int[sizey+1];
            c[i] = new int[sizey+1];
        }

        cout<<"X:";
        output(x);
        cout<<"Y:";
        output(y);
        ts = clock();
        LCS_length(x, y, b, c);
        te = clock();
        cout<<"Z:";
        ts1 = clock();
        LCS(b, x, sizex, sizey);
        te1 = clock();
        cout<<endl;
        cout<<"Length:"<<c[sizex][sizey]<<endl;
        cout<<"Time: "<<endl;
        cout<<"LCS_length :"<<(te-ts)/1000.0<<" s"<<endl;
        cout<<"Print_LCS :"<<(te1-ts1)/1000.0<<" s";
        cout<<endl<<endl;
        for(int i=0 ; i<=sizex ; ++i){
            delete [] b[i];
            delete [] c[i];
        }
        delete [] b;
        delete [] c;
        x.clear();
        y.clear();
    }
    
    return 0;
}

int retrieve(vector<int> X, int i){
    return X[i-1];
}

void LCS_length(vector<int> X, vector<int> Y, int** b, int** c){
    int m = X.size();
    int n = Y.size();
    c[0][0] = 0;
    b[0][0] = 0;
    for(int i=1 ; i<=m ; ++i){
        c[i][0] = 0;
        b[i][0] = 0;
    }
        
    for(int i=1 ; i<=n ; ++i){
        c[0][i] = 0;
        b[0][i] = 0;
    }
        
    for(int i=1 ; i<=m ; ++i){
        for(int j=1 ; j<=n ; ++j){
            int xi = retrieve(X, i);
            int yj = retrieve(Y, j);
            if(xi == yj){
                c[i][j] = c[i-1][j-1]+1;
                b[i][j] = 1;
            }
            else if(c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = 2;
            }
            else{
                c[i][j] = c[i][j-1];
                b[i][j] = 3;
            }
        }
    }
}

void LCS( int** b, vector<int> X, int i, int j){
    if(i==0 || j==0)
        return;
    if(b[i][j]==1){
        LCS(b, X, i-1, j-1);
        cout<<retrieve(X,i)<<" ";
    }
    else if(b[i][j]==2)
        LCS(b, X, i-1, j);
    else
        LCS(b, X, i, j-1);
}

void output(vector<int> X){
    int len = X.size();
    for(int i=0 ; i<len ; ++i){
        cout<<X[i]<<" ";
    }
    cout<<endl;
}

void generate(vector <int> &x, int sz){
    for(int i=0 ; i<sz ; ++i){
        int num = rand()%(10);
        x.push_back(num);
    }
}

void pt(int **c, int m, int n){
    for(int i=0 ; i<=m ; ++i){
        for(int j=0 ; j<=n ; ++j){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
