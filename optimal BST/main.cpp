#include <iostream>
#include <iomanip>

#define M 10000

using namespace std;

void optimal_bst(double* p, double* q, int n, double** &e, int** &root){
    double** w=new double*[n+2];        // w[i][j]=w[i][j-1]+p[j]+q[j]
    e=new double*[n+2];
    root=new int*[n+1];
    for (int i=0; i<n+1; i++){
        w[i]=new double[n+1];
        e[i]=new double[n+1];
        root[i]=new int[n+1];
    }
    w[n+1]=new double[n+1];
    e[n+1]=new double[n+1];
    for (int i=1; i<n+2; i++){
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }
    for (int l=1; l<=n; l++){
        for (int i=1; i<=n-l+1; i++){
            int j=l+i-1;
            e[i][j]=M;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            if (i == j){
                int r=j;
                double t=e[i][r-1]+e[r+1][j]+w[i][j];
                //cout << r << ": " << e[i][r-1] << "+" << e[r+1][j] << "+" << w[i][j] << "=" << t << " | " << e[i][j] << endl;
                if (t+0.01 < e[i][j]){
                    e[i][j]=t;
                    root[i][j]=r;
                }
            }
            else{
                for (int r=root[i][j-1]; r<=root[i+1][j]; r++){
                    double t=e[i][r-1]+e[r+1][j]+w[i][j];
                    //cout << r << ": " << e[i][r-1] << "+" << e[r+1][j] << "+" << w[i][j] << "=" << t << " | " << e[i][j] << endl;
                    if (t+0.01 < e[i][j]){
                        e[i][j]=t;
                        root[i][j]=r;
                    }
                }
            }
        }
    }
    cout << endl;
}

void output_aux (int** root, int n, int i, int j, int r){
    if (i == j){
        cout << "d" << i-1 << " jest lewym dzieckiem k" << r << endl;
        cout << "d" << i << " jest prawym dzieckiem k" << r << endl;
    }
    else if (i > j){
        cout << "d" << j << " jest prawym dzieckiem k" << j << endl;
    }
    else if (i < j){
        if (root[i][root[i][j]-1] > 0){
            cout << "k" << root[i][root[i][j]-1] << " jest lewym dzieckiem k" << r << endl;
            output_aux(root, n, i, root[i][j]-1, root[i][root[i][j]-1]);
        }
        if (root[i][j]+1 <= n){
            if (root[root[i][j]+1][j] <= n && root[root[i][j]+1][j] > 0){
                cout << "k" << root[root[i][j]+1][j] << " jest prawym dzieckiem k" << r << endl;
            }
            output_aux(root, n, root[i][j]+1, j, root[root[i][j]+1][j]);
        }
        else if (root[i][j] == j){
            cout << "d" << j << " jest prawym dzieckiem k" << j << endl;
        }
    }
}

void output (int** root, int n){
    cout << "k" << root[1][n] << " jest korzeniem" << endl;
    output_aux(root, n, 1, n, root[1][n]);
}

int main(){

    double p[8]={0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
    double q[8]={0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    int n=7;

/**
    int n=5;
    double p[6]={0, 0.15, 0.10, 0.05, 0.10, 0.20};
    double q[6]={0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
**/
    double** e=new double*[n+2];
    int** root=new int*[n+1];
    for (int i=0; i<n+1; i++){
        root[i]=new int[n+1];
        for (int j=0; j<n+1; j++) root[i][j]=0;
    }
    for (int i=0; i<=n+1; i++){
        e[i]=new double[n+1];
        for (int j=0; j<n+1; j++) e[i][j]=0;
    }
    optimal_bst(p, q, n, e, root);
    cout << fixed << setprecision(2);
    for (int i=1; i<=n+1; i++){
        for (int j=0; j<=n; j++){
            if (j >= i-1) cout << e[i][j] << " ";
            else cout << "     ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            if (1 <= i && i <= j && j<= n) cout << root[i][j] << " ";
            else cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
    output(root, n);
}
