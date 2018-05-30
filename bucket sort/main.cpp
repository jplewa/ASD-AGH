#include <iostream>
#include<random>

using namespace std;

struct Node{
    Node* next;
    double value;
};

typedef Node Node;

Node* sortList(Node* L){
    Node* L2=L;
    int n=0;
    while (L2!=NULL){
        n++;
        L2=L2->next;
    }
    Node** buckets=new Node*[n];
    for (int i=0; i<n; i++){
        buckets[i]=new Node;
        (buckets[i])->value=5.0;
        (buckets[i])->next=NULL;
    }
    L2=L;
        while (L2!=NULL){
        Node* L3=L2->next;
        double x=(L2->value)/5.0;
        x*=n;
        int index=(int) x;
        Node* tmp=buckets[index];
        if (((buckets[index])->value)==5.0){
                (buckets[index]->value)=L2->value;
        }
        else if (L2->value < tmp->value){
            L2->next=tmp;
            buckets[index]=L2;
        }
        else{
            while (tmp->next != NULL && tmp->next->value < L2->value) tmp=tmp->next;
            Node* tmp2 = new Node;
            tmp2=tmp->next;
            tmp->next=L2;
            L2->next=tmp2;
        }
        L2=L3;
    }
    int y=0;
    while((((buckets[y])->value)==5.0) && y<n){
        y++;
    }
    for (int i=y; i<n; i++){
        if (buckets[i]->next!=NULL){

        }
    }
    Node* L3=new Node;
    L3->value=5.0;
    for (int i=y; i<n; i++){
        if ((buckets[i]->value)!=5.0){
            L3->next=buckets[i];
            while (L3->next!=NULL){
                L3=L3->next;
            }
        }
    }
    L3->next=NULL;
    return buckets[y];
}

int main(){
    int n;
    cin >> n;
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0, 5);
    Node* L=new Node;
    L=NULL;
    for (int i=0; i<n; i++) {
        Node* tmp=new Node;
        tmp->value=dis(gen);
        tmp->next=L;
        L=tmp;
    }
    Node* L2=new Node;
    L2=L;
    while (L2!=NULL){
      cout << L2->value << endl;
      L2=L2->next;
    }
    L2=sortList(L);
    cout << endl << "Po sortowaniu:" << endl;
    while (L2!=NULL){
      cout << L2->value << endl;
      L2=L2->next;
    }
}
