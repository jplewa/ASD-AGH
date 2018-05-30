#include <iostream>
#include <cstdlib>

using namespace std;

struct node{
    int v;
    node* next;
};
typedef node node;

int** lcs (int* X, int* Y, int m, int n, int** b){
	int** c=(int**)(malloc((m+1)*sizeof(int*)));
    for (int i=0; i<=m; i++) c[i]=(int*)(malloc((n+1)*sizeof(int)));
	for (int i=0; i<=m; i++) c[i][0]=0;
	for (int i=0; i<=n; i++) c[0][i]=0;
	for (int i=1; i<=m; i++){
		for (int j=1; j<=n; j++){
			if (X[i] == Y[j]){
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=0;
			}
			else if (c[i-1][j] >= c[i][j-1]){
				c[i][j]=c[i-1][j];
				b[i][j]=1;
			}
			else{
				c[i][j]=c[i][j-1];
				b[i][j]=-1;
			}
		}
	}
	return c;
}

void print_lcs (int** b, int* x, int i, int j){
    if (i != 0 && j != 0){
        if (b[i][j] == 0){
            print_lcs(b, x, i-1, j-1);
            cout << x[i] << " ";
        }
        else if (b[i][j] == 1) print_lcs(b, x, i-1, j);
        else print_lcs(b, x, i, j-1);
    }
}

void print_lcs2 (int** c, int* x, int i, int j){ // bez u¿ycia dodatkowej tablicy b
    if (c[i][j] > 0) {
        if (c[i-1][j] == c[i][j-1] && c[i-1][j] < c[i][j]){
            print_lcs2(c, x, i-1, j-1);
            cout << x[i] << " ";
        }
        else if (c[i-1][j] == -1 || c[i][j-1] == -1){
            print_lcs2(c, x, i-1, j-1);
            cout << x[i] << " ";
        }
        else if (c[i-1][j] >= c[i][j-1]) print_lcs2(c, x, i-1, j);
        else print_lcs2(c, x, i, j-1);
    }
}

int lcs_memo_aux (int* X, int* Y, int m, int n, int** b, int** c, int i, int j){
    if (c[i][j] > -1) return c[i][j];
    if (X[i] == Y[j]){
        b[i][j]=0;
        c[i][j]=lcs_memo_aux(X, Y, m, n, b, c, i-1, j-1)+1;
    }
    else if (lcs_memo_aux(X, Y, m, n, b, c, i-1, j) >= lcs_memo_aux(X, Y, m, m, b, c, i, j-1)){
        b[i][j]=1;
        c[i][j]=lcs_memo_aux(X, Y, m, n, b, c, i-1, j);
    }
    else{
        b[i][j]=-1;
        c[i][j]=lcs_memo_aux(X, Y, m, n, b, c, i, j-1);
    }
}

int lcs_memo (int* X, int* Y, int m, int n, int** b, int** c){ // top-down with memoization
	for (int i=0; i<=m; i++){
        for (int j=0; j<=n; j++) c[i][j]=-1;
	}
	for (int i=0; i<=m; i++) c[i][0]=0;
	for (int i=0; i<=n; i++) c[0][i]=0;
    return lcs_memo_aux(X, Y, m, n, b, c, m, n);
}

void print_lis (int* X, int* P, int i){
    if (P[i] > -1) print_lis(X, P, P[i]);
    cout << X[i] << " ";
}

int lis (int* X, int n){
    int* f=(int*)(malloc(n*sizeof(int)));   // f[i] = d³ugoœæ najd³u¿szego ci¹gu rosn¹cego koñcz¹cego siê na i
    int* p=(int*)(malloc(n*sizeof(int)));
    int M=1;
    int M_index=0;
    f[0]=1;
    p[0]=-1;
    for (int i=1; i<n; i++){
        f[i]=1;
        p[i]=-1;
        for (int j=0; j<i; j++){
            if (X[j] < X[i] && f[j]+1 > f[i]){
                f[i]=f[j]+1;
                p[i]=j;
            }
        }
        if (f[M_index] < f[i]){
            M_index=i;
        }
    }
    print_lis(X, p, M_index);
    cout << endl;
    return M;
}

int binary (int a, int* B, int i, int j){
    if (B[j] < a) return j;
    if (B[i] < a && B[i+1] >= a) return i;
    if (B[j-1] < a && B[j] >= a) return j-1;
    else if (j < i) return -1;
    else{
        if (B[(i+j)/2] > a) return binary (a, B, i, ((i+j)/2)-1);
        else return binary (a, B, 1+(i+j)/2, j);
    }
}

void output (node* p){
    if (p->next != NULL) output(p->next);
    cout << p->v << " ";
}

void lis2 (int* A, int n){
    int* B=(int*)(malloc(n*sizeof(int)));
    node** C=(node**)(malloc(n*sizeof(node*)));
    for (int i=0; i<n; i++){
        B[i]=10000;
        C[i]=NULL;
    }
    int L=1;
    for (int i=0; i<n; i++){
        if (A[i] < B[1]){
            B[1]=A[i];
            if (C[1] == NULL) C[1]=new node;
            C[1]->next=NULL;
            C[1]->v=A[i];
        }
        else{
            int j=binary(A[i], B, 0, n-1);
            B[j+1]=A[i];
            C[j+1]=new node;
            C[j+1]->v=A[i];
            C[j+1]->next=C[j];
            if (j+1 > L) L++;
        }
    }
    output(C[L]);
    cout << endl;
}

int main(){
	int m=7;
	int n=6;
	int X[8]={0, 1, 2, 3, 2, 4, 1, 2};
	int Y[7]={0, 2, 4, 3, 1, 2, 1};
	int** c=(int**)(malloc((m+1)*sizeof(int*)));
	for (int i=0; i<=m; i++) c[i]=(int*)(malloc((n+1)*sizeof(int)));
	int** b=(int**)(malloc((m+1)*sizeof(int*)));
	for (int i=0; i<=m; i++) b[i]=(int*)(malloc((n+1)*sizeof(int)));
	c=lcs(X, Y, m, n, b);
	cout << c[7][6] << endl;
	print_lcs(b, X, m, n);
	cout << endl;
    print_lcs2(c, X, m, n);
    cout << endl << endl;
    cout << lcs_memo(X, Y, m, n, b, c) << endl;
    print_lcs2(c, X, m, n);
    cout << endl << endl;

    for (int i=0; i<=m; i++){
        for (int j=0; j<=n; j++) cout << c[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    int A[9]={0, 1, 0, 0, 1, 0, 1, 0, 1};
    int B[10]={0, 0, 1, 0, 1, 1, 0, 1, 1, 0};
    int a=8;
    int bb=9;
    int** d=(int**)(malloc((a+1)*sizeof(int*)));
	for (int i=0; i<=a; i++) d[i]=(int*)(malloc((bb+1)*sizeof(int)));
	int** e=(int**)(malloc((a+1)*sizeof(int*)));
	for (int i=0; i<=a; i++) e[i]=(int*)(malloc((bb+1)*sizeof(int)));
	// /**
	d=lcs(A, B, a, bb, e);
	cout << endl << d[a][bb] << endl;
	print_lcs2(d, A, a, bb);
	// **/

	/**
	cout << endl << lcs_memo(A, B, a, bb, e, d) << endl;
	for (int i=0; i<=a; i++){
        for (int j=0; j<=bb; j++) cout << d[i][j] << " ";
        cout << endl;
	}
	cout << endl;
	print_lcs2(d, A, a, bb);
	**/

	cout << endl << endl;

	int H[]={1, 4, 3, 6, 1, 8, 9, 10, 5, 11};
	lis(H, 10);
	lis2(H, 10);


}
