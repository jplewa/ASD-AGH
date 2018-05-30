#include <iostream>
#include <cstdlib>
#include <climits>
#include <queue>

using namespace std;

struct edge{
    int u;
    int v;
    int w;
    edge* next;
};
typedef edge edge;

struct vertex{
    int u;
    int rankv;
    bool processed;
    vertex* parent;
    edge* edges;
    bool operator<(vertex a) const{
        return rankv > a.rankv;
    }
};
typedef vertex vertex;

struct graph{
    int E;
    int V;
    vertex* vertices;
    edge* edges;
};
typedef graph graph;

void swp (int &a, int &b){
    a-=b;
    b+=a;
    a=b-a;
}

void add_vertex(graph* G){
    if (G->V == 0){
        G->E=0;
        G->vertices=(vertex*)(malloc(sizeof(vertex)));
    }
    else G->vertices=(vertex*)(realloc(G->vertices, ((G->V)+1)*sizeof(vertex)));
    G->vertices[G->V].edges=NULL;
    G->vertices[G->V].u=G->V;
    G->V++;
}

edge* adding (graph* G, int u, int v, int w){
    edge* p=new edge;
    p->v=-1;
    p->next=G->vertices[u].edges;
    edge* q=p;
    edge* r=p;
    while (r != NULL && r->v < v){
        q=r;
        r=r->next;
    }
    if (r != NULL && r->v == v) return NULL;
    else{
        q->next=new edge;
        q->next->u=u;
        q->next->v=v;
        q->next->w=w;
        q->next->next=r;
        G->vertices[u].edges=p->next;
        return q->next;
    }
}

edge* add_edge (graph* G, int u, int v, int w){
    if (((G->V)*((G->V)-1))/2 > G->E){
        edge* tmp=new edge;

        if (u > v){
            tmp=adding(G, u, v, w);
            if (tmp != NULL){
                adding(G, v, u, w);
            }
        }
        else if (u < v){
            tmp=adding(G, v, u, w);
            if (tmp != NULL){
                adding(G, u, v, w);
            }
        }
        if (tmp != NULL){
            if (G->E == 0){
                G->edges=new edge;
                G->edges->w=-1;
                G->edges->next=NULL;
            }
            edge* p=G->edges;
            while (p->next != NULL && p->next->w < w) p=p->next;
            edge* e=new edge;
            if (v < u) swp(u, v);
            e->u=u;
            e->v=v;
            e->w=w;
            e->next=p->next;
            p->next=e;
            G->E++;
        }
        return tmp;
    }
    return NULL;
}

void output (graph* G, bool p){
    cout << "E: " << G->E << " | V: " << G->V << endl;
    edge* tmp=G->edges->next;
    while (tmp != NULL){
        cout << "(" << tmp->u << "," << tmp->v << ")[" << tmp->w << "] ";
        tmp=tmp->next;
    }
    cout << endl;
    for (int i=0; i<G->V; i++){
        cout << i;
        if (p){
            if (G->vertices[i].parent == NULL) cout << " /NULL/ ";
            else cout << " /" << G->vertices[i].parent->u << "/ ";
            cout << "[" << G->vertices[i].rankv << "] : ";
        }
        else cout << ": ";
        edge* tmp=G->vertices[i].edges;
        while (tmp != NULL){
            cout << tmp->v << " [" << tmp->w << "] -> ";
            tmp=tmp->next;
        }                               //(c: " << G->vertices[i].color << " | " << G->vertices[i].d << "/" << G->vertices[i].f << " | p: ";
        cout << "NULL" << endl;
        //if (G->vertices[i].parent == NULL) cout << "NULL";
        //else cout << G->vertices[i].parent->d << "/" << G->vertices[i].parent->f;
        //cout << ") " << endl;
    }
}

void random_edges (graph* G, int n){
	for (int i=0; i<n && ((((G->V)-1)*(G->V))/2) > G->E; i++){
        int u, v;
        int w=rand()%20;
        do{
            u=rand()%(G->V);
            v=rand()%(G->V);
            while (u == v) v=rand()%(G->V);
        }
        while (add_edge(G, u, v, w) == NULL);
    }
}

bool correct(graph* G){
    for (int i=0; i < G->V; i++){
        edge* tmp=G->vertices[i].edges;
        while (tmp != NULL){
            edge* tmp2=G->vertices[tmp->v].edges;
            while (tmp2->v != i) tmp2=tmp2->next;
            if (tmp->w != tmp2->w) return false;
            tmp=tmp->next;
        }
    }
    return true;
}

void MakeSet (vertex* x){
    x->parent=x;
    x->rankv=0;
}

vertex* FindSet (vertex* x){
    if (x->parent != x) x->parent=FindSet(x->parent);
    return x->parent;
}

void Union (vertex* x, vertex* y){
    x=FindSet(x);
    y=FindSet(y);
    if (y->rankv < x->rankv) y->parent=x;
    else{
        x->parent=y;
        if (x->rankv == y->rankv) y->rankv++;
    }
}

graph* Kruskal (graph* G){
    graph* T=new graph;
    T->V=0;
    T->edges=new edge;
    T->edges->w=-1;
    T->edges->next=NULL;
    for (int i=0; i<G->V; i++) add_vertex(T);
    for (int i=0; i<G->V; i++) MakeSet(&(G->vertices[i]));
    edge* e=G->edges->next;
    while (e != NULL){
        if ((FindSet(&(G->vertices[e->u]))) != (FindSet(&(G->vertices[e->v])))){
            add_edge(T, e->u, e->v, e->w);
            Union(&(G->vertices[e->u]), &(G->vertices[e->v]));
        }
        e=e->next;
    }
    return T;
}

void Prim (graph* G, int r){
    for (int i=0; i<G->V; i++){
        G->vertices[i].rankv=INT_MAX;
        G->vertices[i].parent=NULL;
        G->vertices[i].processed=false;
    }
    G->vertices[r].rankv=0;
    priority_queue < vertex > Q;
    Q.push(G->vertices[r]);
    while (!Q.empty()){
        int u=Q.top().u;
        Q.pop();
        if (G->vertices[u].processed == false){
            G->vertices[u].processed=true;
            edge* tmp=G->vertices[u].edges;
            while (tmp != NULL){
                if (tmp->w < G->vertices[tmp->v].rankv && G->vertices[tmp->v].processed == false){
                    G->vertices[tmp->v].parent=&(G->vertices[u]);
                    G->vertices[tmp->v].rankv=tmp->w;
                    Q.push(G->vertices[tmp->v]);
                }
                tmp=tmp->next;
            }
        }
    }
}

int main(){
	graph* G=new graph;
	G->V=0;
	for (int i=0; i<10; i++) add_vertex(G);
    add_edge(G, 1, 2, 4);
    add_edge(G, 1, 8, 8);
    add_edge(G, 2, 3, 7);
    add_edge(G, 2, 8, 11);
    add_edge(G, 3, 4, 7);
    add_edge(G, 4, 5, 9);
    add_edge(G, 5, 6, 10);
    add_edge(G, 6, 7, 2);
    add_edge(G, 7, 8, 1);
    add_edge(G, 9, 8, 7);
    add_edge(G, 8, 7, 6);
    add_edge(G, 3, 9, 2);
    add_edge(G, 6, 3, 4);
    add_edge(G, 6, 4, 14);
    if (correct(G)) output(G, false);
    else cout << "error" << endl;
    graph* T=Kruskal(G);
    cout << endl;
    if (correct(T)) output(T, false);
    else cout << "error" << endl;
    cout << endl;
    Prim(G, 1);
    cout << endl;
    output(G, true);
}
