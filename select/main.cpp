#include <iostream>
#include <stdlib.h>

using namespace std;

void swp (int* A, int a, int b){
    int tmp=A[a];
    A[a]=A[b];
    A[b]=tmp;
}

int qs_partition (int* A, int p, int r){
    int x=A[r];
    int i=p-1;
    for (int j=p; j<r; j++){
        if (A[j] <= x){
            i++;
            swp(A, i, j);
        }
    }
    swp(A, i+1, r);
    return i+1;
}

int randomized_partition (int* A, int p, int r){
    int q=p+rand()%(r-p+1);
    swp(A, r, q);
    return qs_partition(A, p, r);
}

void quicksort (int* A, int p, int r){
    if (p < r){
        int q=randomized_partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

int randomized_select (int* A, int p, int r, int x){
    if (p == r) return A[p];
    int q=randomized_partition(A, p, r);
    int k=q-p+1;        // pozycja pivota
    if (k == x) return A[q];
    else if (x < k) return randomized_select(A, p, q-1, x);
    else return randomized_select(A, q+1, r, x-k);
}

void insertion_sort (int* A, int p, int r){
    for (int i=p+1; i<=r; i++){
        int x=A[i];
        int j=i-1;
        while (j >= p && A[j] > x){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=x;
    }
}

int Partition5 (int* A, int p, int r){
    if (p == r) return p;
    insertion_sort(A, p, r);
    return p+((r-p)/2);
}
int Select(int* A, int p, int r, int n);

int Pivot (int* A, int p, int r){
    if (r-p < 5) return Partition5(A, p, r);
    for (int i=p; i<=r; i+=5){
        int j=i+4;
        if (j > r) j=r;
        int median5=Partition5(A, i, j);
        swp(A, median5, p+((i-p)/5));
    }
    int q=p+(r-p)/5;
    if ((r-p)%5 == 0) q--;
    return Select(A, p, q, p+(r-p)/10);
}

int Select (int* A, int p, int r, int n){
    while (true){
        if (p == r) return p;
        int index=Pivot(A, p, r);
        swp(A, index, r);
        index=qs_partition(A, p, r);
        if (n == index) return n;
        else if (n < index) r=index-1;
        else p=index+1;
    }
}

int main(){
    int n=10000000;
    int x=3141529;
    int* A=new int[n];
    for (int i=0; i<n; i++) A[i]=rand();
    //for (int i=0; i<n; i++) cout << A[i] << " ";
    //cout << endl;
    //cout << randomized_select(A, 0, n-1, x+1) << endl;
    cout << A[Select(A, 0, n-1, x)] << endl;
    //quicksort(A, 0, n-1);
    //for (int i=0; i<n; i++) cout << A[i] << " ";
    //cout << endl;
    //cout << A[x];
}
