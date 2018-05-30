#include <iostream>
#include <stdlib.h>

using namespace std;

struct node{
    int value;
    node* next;
};
typedef node node;

struct graph{
    int E;
    int V;
    node** edges;
};
typedef graph graph;

void add_V (graph* G){
    G->V++;
    G->edges=(node**)(realloc((G->edges), (G->V)*sizeof(node*)));
    G->edges[(G->V)-1]=NULL;
}

void add_E (graph* G, int u, int v){
    if (u < G->V && v < G->V){
        node* tmp=G->edges[u];
        G->edges[u]=new node;
        G->edges[u]->value=v;
        G->edges[u]->next=tmp;
        G->E++;
    }
}

void output (graph* G){
    for (int i=0; i < G->V; i++){
        cout << i << ": ";
        node* p=G->edges[i];
        while (p != NULL){
            cout << p->value << " -> ";
            p=p->next;
        }
        cout << "NULL" << endl;
    }
    cout << endl;
}

bool E_exists (graph* G, int u, int v){
    if (u >= G->V || v >= G->V) return false;
    node* p=G->edges[u];
    while(p != NULL){
        if (p->value == v) return true;
        p=p->next;
    }
    return false;
}


int main(){
    graph* G=new graph;
    G->V=1;
    G->E=0;
    G->edges=(node**)(malloc(sizeof(node*)));
    G->edges[0]=NULL;
    /**
    add_V(G);
    add_V(G);
    add_V(G);
    add_V(G);
    output(G);
    add_E(G, 0, 1);
    output(G);
    add_E(G, 0, 2);
    output(G);
    add_E(G, 2, 1);
    output(G);
    if (E_exists(G, 2, 1)) cout << "Istnieje brzeg z 2 do 1" << endl;
    else cout << "Nie istnieje brzeg z 2 do 1" << endl;
    if (E_exists(G, 2, 0)) cout << "Istnieje brzeg z 2 do 0" << endl;
    else cout << "Nie istnieje brzeg z 2 do 0" << endl;
    if (E_exists(G, 0, 5)) cout << "Istnieje brzeg z 0 do 5" << endl;
    else cout << "Nie istnieje brzeg z 0 do 5" << endl;
    **/
}
