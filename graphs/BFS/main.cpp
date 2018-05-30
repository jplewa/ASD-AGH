#include <iostream>
#include <stdlib.h>
#include <queue>
#include <limits.h>

using namespace std;

enum color{
    white=0,
    gray=1,
    black=2,
};

struct node{
    int value;
    node* next;
};
typedef node node;

struct vertice{
    color color;
    int distance;
    vertice* parent;
    node* edges;
};
typedef vertice vertice;

struct graph{
    int E;
    int V;
    vertice* vertices;
};
typedef graph graph;

void add_V (graph* G){
    G->V++;
    G->vertices=(vertice*)(realloc((G->vertices), (G->V)*sizeof(vertice)));
    G->vertices[(G->V)-1].edges=NULL;
}

void add_E (graph* G, int u, int v){
    if (u < G->V && v < G->V){
        node* tmp=G->vertices[u].edges;
        G->vertices[u].edges=new node;
        G->vertices[u].edges->value=v;
        G->vertices[u].edges->next=tmp;
        G->E++;
    }
}

void output (graph* G){
    for (int i=0; i < G->V; i++){
        cout << i << ": ";
        node* p=G->vertices[i].edges;
        while (p != NULL){
            cout << p->value << " -> ";
            p=p->next;
        }
        cout << "NULL" << endl;
    }
    cout << endl << "edges: " << G->E << endl << "vertices: " << G->V << endl << endl;
}

bool E_exists (graph* G, int u, int v){
    if (u >= G->V || v >= G->V) return false;
    node* p=G->vertices[u].edges;
    while(p != NULL){
        if (p->value == v) return true;
        p=p->next;
    }
    return false;
}

void BFS (graph* G, int s){
    for (int i=0; i<G->V; i++){
        G->vertices[i].color=white;
        G->vertices[i].distance=INT_MAX;
        G->vertices[i].parent=NULL;
    }
    G->vertices[s].color=gray;
    G->vertices[s].distance=0;
    G->vertices[s].parent=NULL;

    queue < vertice* > Q;
    Q.push(&(G->vertices[s]));
    while (Q.size() != 0){
        vertice* u=Q.front();
        Q.pop();
        node* p=u->edges;
        while (p != NULL){
            if (G->vertices[p->value].color == white){
                G->vertices[p->value].color=gray;
                G->vertices[p->value].parent=u;
                G->vertices[p->value].distance=(u->distance)+1;
                Q.push(&(G->vertices[p->value]));
            }
            p=p->next;
        }
        u->color=black;
    }
}

int main(){
    graph* G=new graph;
    G->V=1;
    G->E=0;
    G->vertices=(vertice*)(malloc(sizeof(vertice)));
    G->vertices[0].edges=NULL;
    for (int i=1; i<10; i++) add_V(G);
    for (int i=1; i<=20; i++){
        int a=rand()%10;
        int b=rand()%10;
        while (a == b || E_exists(G, a, b)) b=rand()%10;
        add_E(G, a, b);
    }
    output(G);
    BFS(G, 3);
    for (int i=0; i<10; i++){
        cout << i << " - distance from 3: " << G->vertices[i].distance << endl;
    }
}
