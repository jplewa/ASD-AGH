#include <iostream>
#include <cstdlib>
#include <climits>

#define N 6

using namespace std;

void paranthesis (int* p, int** m, int** s, int n){
    for (int i=1; i<=n; i++) m[i][i]=0;
    for (int l=2; l<=n; l++){
        for (int i=1; i<=n-l+1; i++){
            int j=i+l-1;
            m[i][j]=INT_MAX;
            for (int k=i; k<j; k++){
                int q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if (q < m[i][j]){
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
}

void print (int** s, int i, int j){
    if (i == j) cout << "A" << i;
    else{
        cout << "(";
        print(s, i, s[i][j]);
        print(s, s[i][j]+1, j);
        cout << ")";
    }
}

int main(){
    int p[N+1]={30, 35, 15, 5, 10, 20, 25};
    int** m=(int**)malloc((N+1)*sizeof(int*));
    for (int i=0; i<=N; i++) m[i]=(int*)malloc((N+1)*sizeof(int));
    int** s=(int**)malloc((N+1)*sizeof(int*));
    for (int i=0; i<=N; i++) s[i]=(int*)malloc((N+1)*sizeof(int));

    paranthesis(p, m, s, N);
    cout << m[1][N] << endl;
    print(s, 1, N);
    cout << endl;

}
