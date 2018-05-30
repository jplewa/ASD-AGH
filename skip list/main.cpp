#include <iostream>
#include <random>
#include <climits>
#include <limits.h>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0, 1);

struct SL_Node{
    int value;
    SL_Node** next;
};

typedef SL_Node SL_Node;

struct SkipList{
    SL_Node* first;
    SL_Node* last;
    int level;
};

typedef SkipList SkipList;

SL_Node* SL_Search (SkipList* L, int x){
    SL_Node* node=L->first;
    for (int i=L->level; i>=0; i--){
            while (node->next[i]->value < x) node=node->next[i];
    }
    if (node->next[0]->value == x) return node->next[0];
    else return NULL;
}

int GetLevel(){
    int level=0;
    while (dis(gen) < 0.5){
        level++;
    }
    return level;
}

void SL_Insert (SkipList* L, int val){
    int newlevel=GetLevel();
    if (newlevel > L->level){
        L->first->next=(SL_Node**)realloc(L->first->next, ((newlevel+1)*sizeof(SL_Node*)));
        L->last->next=(SL_Node**)realloc(L->last->next, ((newlevel+1)*sizeof(SL_Node*)));
        for (int i=newlevel; i>L->level; i--){
            L->first->next[i]=L->last;
            L->last->next[i]=NULL;
        }
        L->level=newlevel;
    }
    SL_Node** prev=(SL_Node**)malloc(((L->level)+1)*sizeof(SL_Node*));
    SL_Node* q=L->first;
    for (int i=L->level; i>=0; i--){
        while (q->next[i]->value < val) q=q->next[i];
        prev[i]=q;
    }
    if (prev[0]->value != val){
        SL_Node* node=new SL_Node;
        node->value=val;

        node->next=(SL_Node**)malloc((newlevel+1)*sizeof(SL_Node*));
        for (int i=0; i<=newlevel ; i++) node->next[i]=(SL_Node*)malloc(sizeof(SL_Node));
        for (int i=newlevel; i>=0; i--){
            node->next[i]=prev[i]->next[i];
            prev[i]->next[i]=node;
        }
    }
}

void SL_Delete (SkipList* L, int val){
    int l=-1;
    SL_Node* q=L->first;
    for (int i=L->level; i >= 0 && l == -1; i--){
        while (q->next[i]->value < val) q=q->next[i];
        if (q->next[i]->value == val) l=i;
    }
    SL_Node** prev=(SL_Node**)malloc((l+1)*sizeof(SL_Node*));
    prev[l]=q;
    for (int i=l-1; i>=0; i--){
        while (q->next[i]->value < val) q=q->next[i];
        prev[i]=q;
    }
    for (int i=l; i>=0; i--){
        prev[i]->next[i]=prev[i]->next[i]->next[i];
        delete(prev[i]->next[i]);
    }
}


void print(SkipList* L){
    for (int i=L->level; i>=0; i--){
        SL_Node* q=L->first;
        while (q!=NULL){
            cout << q->value << " -> ";
            q=q->next[i];
        }
        cout << "NULL" << endl;
    }
    cout << endl;
}


int main(){
    SkipList* L=new SkipList;
    L->level=0;
    L->first=new SL_Node;
    L->first->value=INT_MIN;
    L->first->next=(SL_Node**)malloc(((L->level)+1)*sizeof(SL_Node*));
    L->last=new SL_Node;
    L->last->value=INT_MAX;
    L->last->next=(SL_Node**)malloc(((L->level)+1)*sizeof(SL_Node*));
    L->first->next[0]=L->last;
    L->last->next[0]=NULL;

    for (int i=0; i<5; i++){
        int x=dis(gen);
        SL_Insert(L, rand());
        print(L);
    }
    SL_Insert(L, 50);
    SL_Insert(L, 51);

    print(L);
    for (int i=0; i<3; i++){
        SL_Insert(L, rand());
        print(L);
    }
    SL_Delete(L, 50);
    print(L);
    SL_Node* x=SL_Search(L, 50);

    if (x != NULL) cout << x->value;
}
