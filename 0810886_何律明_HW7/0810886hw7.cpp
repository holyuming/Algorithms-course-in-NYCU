#include <iostream>
#include <vector>
#include <string>
using namespace std;


//For first optimal bst
vector<double> pi = {   0, 0.05, 0.04, 0.05, 0.07, 0.08, 0.09, 0.04, 0.08}; //first 0 is a dummy
vector<double> qi = {0.08, 0.06, 0.04, 0.06, 0.03, 0.06, 0.07, 0.06, 0.04};

//For second optimal bst in the discussion part
/*vector<double> pi = {   0, 0.05, 0.15, 0.05, 0.15, 0.15}; //first 0 is a dummy
vector<double> qi = {0.10, 0.05, 0.05, 0.10, 0.05, 0.10};*/ 

void new2d(double** &e, double** &w, double** &root);
void delete2d(double** &e, double** &w, double** &root);
void Optimal_BST(vector<double> pi, vector<double> qi, double** &e, double** &w, double** &root);
void ck(double** t, int m, int n);
int caldepth(double** root, int k, int i, int j);
void drawBST(double** &e, double** &root);


int main(){
    double **e, **w, **root;
    int n = pi.size() - 1;
    new2d(e, w, root);
    Optimal_BST(pi, qi, e, w, root);
    cout<<"Smallest search cost : "<<e[1][n]<<endl;
    cout<<"Root : "<<root[1][n]<<endl;
    /*ck(e, n+2, n+1);
    ck(w, n+2, n+1);
    ck(root, n+1, n+1);*/
    cout<<endl<<endl;
    drawBST(e, root);
    delete2d(e, w, root);
    return 0;
}

void new2d(double** &e, double** &w, double** &root){
    int n = pi.size()-1; //8
    e = new double* [n+2]; //[0~n+1, 0~n] (n+2)*(n+1)
    w = new double* [n+2]; //[0~n+1, 0~n] (n+2)*(n+1)
    root = new double*[n+1]; //[0~n, 0~n] (n+1)*(n+1)
    for(int i=0 ; i<n+2 ; ++i){
        e[i] = new double[n+1];
        w[i] = new double[n+1];
    }
    for(int i=0 ; i<n+1 ; ++i){
    	root[i] = new double[n+1];
	}
    //Init w and e
    for(int i=0 ; i<n+2 ; ++i){
        for(int j=0 ; j<n+1 ; ++j){
            e[i][j] = 0;
            w[i][j] = 0;
        }
    }
    //Init root
    for(int i=0 ; i<n+1 ; ++i){
        for(int j=0 ; j<n+1 ; ++j){
            root[i][j] = 0;
        }
    }    
}

void delete2d(double** &e, double** &w, double** &root){
    int n = pi.size()-1;
    for(int i=0 ; i<=n+1 ; ++i){
        if(i <= n){
            delete[] e[i];
            delete[] w[i];
            delete[] root[i];
        }
        else{
            delete[] e[i];
            delete[] w[i];                      
        }
    }
    delete[] e;
    delete[] w;
    delete[] root;    
}

void Optimal_BST(vector<double> pi, vector<double> qi, double** &e, double** &w, double** &root){
    int n = pi.size()-1;
    for(int i=1 ; i<=n+1 ; ++i){
        e[i][i-1] = qi[i-1];
        w[i][i-1] = qi[i-1];
    }
    for(int l=1 ; l<=n ; ++l){
        for(int i=1 ; i<=n-l+1 ; ++i){
            int j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j-1] + pi[j] + qi[j];
            for(int r=i ; r<=j ; ++r){
                double t = e[i][r-1] + e[r+1][j] + w[i][j];
                if(t <= e[i][j]){
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void ck(double** t, int m, int n){
    for(int i=0 ; i<m ; ++i){
        for(int j=0 ; j<n ; ++j){
            cout<<t[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

int caldepth(double** root, int k, int i, int j){
    int r = root[i][j];
    if(k == r){
        return 0;
    }
    else if(k < r){
        return caldepth(root, k, i, r-1) + 1;
    }
    else
        return caldepth(root, k, r+1, j) + 1;
}

void drawBST(double** &e, double** &root){
    int n = pi.size()-1;
    int maxdepth = 0, tmp;
    for(int i=1 ; i<=n ; ++i){
        tmp = caldepth(root, i, 1, n);
        if(tmp > maxdepth)
            maxdepth = tmp;
    }
    // Add the depth of dummys
    ++maxdepth; 
    //Init table for drawing BST
    string **t = new string* [maxdepth+1];
    for(int i=0 ; i<=maxdepth ; ++i){
        t[i] = new string[2*n + 1];
    }
    for(int i=0 ; i<=maxdepth ; ++i){
        for(int j=0 ; j<2*n + 1 ; ++j){
            t[i][j] = "  ";
        }
    }
    //Put ki in the table
    int dep;
    for(int i=1 ; i<=n ; ++i){
        dep = caldepth(root, i, 1, n);
        t[dep][2*i - 1] = "k" + to_string(i);
    }
    //Put dummy in the table
    int d0 = caldepth(root, 1, 1, n);
    t[d0+1][0] = "d" + to_string(0);
    int d8 = caldepth(root, n, 1, n);
    t[d8+1][2*n] = "d" + to_string(n);
    for(int i=1 ; i<n ; ++i){
    	int q1 = caldepth(root, i, 1, n);
		int q2 = caldepth(root, i+1, 1, n);
		if(q1 > q2){ //Put on the right subtree of ki
			t[q1+1][2*i] = "d" + to_string(i);
		}
		else if(q1 < q2){ //Put on the left subtree of ki+1
			t[q2+1][2*i] = "d" + to_string(i);
		}
    	
	}
    //Print
    for(int i=0 ; i<=maxdepth ; ++i){
        for(int j=0 ; j<2*n + 1 ; ++j){
            cout<<t[i][j]<<" ";
        }
        cout<<endl<<endl;
    }
    //Free the space
    for(int i=0 ; i<=maxdepth ; ++i){
        delete [] t[i];
    }
    delete [] t;
}
