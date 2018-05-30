#include <iostream>

using namespace std;

int main(){
    int n=6;
    int* A=new int[n];
    for (int i=0; i<n; i++) cin >> A[i];
    int* tak=new int[n];
    int* nie=new int[n];
    int* p=new int[n];
    p[0]=0;
    tak[0]=A[0];
    nie[0]=0;
    for (int i=1; i<n; i++){
        nie[i]=max(tak[i-1], nie[i-1]);
        tak[i]=nie[i-1]+A[i];

    }
    for (int i=0; i<n; i++){
        cout << i << ": tak - " << tak[i] << "| nie - " << nie[i] << endl;
    }
}
