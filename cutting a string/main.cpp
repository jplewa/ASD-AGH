#include <iostream>

using namespace std;

struct node{
    int v;
    node* next;
};
typedef node node;

int C (int L[], int m, int i, int j, node* l, node** l_fin){
    int cut=10000;
    for (int k=1; k<m; k++){
        if (L[k] < j && L[k] > i){
            node* tmp=new node;
            tmp->v=L[k];
            tmp->next=l;
            l=tmp;
            cut=min(cut, j-i+C(L, m, i, L[k], l, l_fin)+C(L, m, L[k], j, l, l_fin));
        }
    }
    if (cut == 10000) return 0;
    (*l_fin)=l;
    return cut;

}

int main(){
    //int n=21;
    int m=4;
    int L[4]={0, 2, 8, 10};
    node* l=new node;
    l=NULL;
    node* tmp=new node;
    tmp=NULL;
    cout << C(L, m, 0, 20, tmp, &l) << endl;
    while (l != NULL){
        cout << l->v << " ";
        l=l->next;
    }
    cout << endl;

}
