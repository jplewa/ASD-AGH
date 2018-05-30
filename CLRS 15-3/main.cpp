#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>
#include <cfloat>

using namespace std;

double bitonic_dist(int* x, int* y, int n){
    cout << setprecision(4);
    double** dist=new double*[n];
    for (int i=0; i<n; i++) dist[i]=new double[n];
    double** dp=new double*[n];
    for (int i=0; i<n; i++) dp[i]=new double[n];
    for (int i=1; i<8; i++){
        for (int j=1; j<8; j++) dist[i][j]=sqrt((double)((((x[i]-x[j])*(x[i]-x[j]))+((y[i]-y[j])*(y[i]-y[j])))));
    }

    dp[1][1]=0;
    for (int j=2; j<n; j++) dp[1][j]=dp[1][j-1]+dist[j-1][j];

    for (int i=2; i<n; i++){
        for (int j=i; j<n; j++){
            if (i == j-1 || i == j){
                dp[i][j]=30.0;
                for (int k=1; k<i; k++){
                    if (dp[k][i]+dist[k][j] < dp[i][j]) dp[i][j]=dp[k][i]+dist[k][j];
                }
            }
            else dp[i][j]=dp[i][j-1]+dist[j-1][j];
        }
    }
    return dp[n-1][n-1];
}

int main(){
    int x[8]={0, 0, 1, 2, 5, 6, 7, 8};
    int y[8]={0, 0, 6, 3, 2, 5, 1, 4};

    cout << bitonic_dist(x, y, 8);
}
