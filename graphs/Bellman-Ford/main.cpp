#include <iostream>
#include <cstdlib>
#include <climits>
#include <queue>

using namespace std;

struct edge{
    int u;          // only used for output
    int v;
    int w;
    edge* next;
};
typedef edge edge;

struct vertex{
    int u;
    int d;
    vertex* parent;
    edge* edges;
    bool operator<(vertex a) const{
        return d > a.d;
    }
};
typedef vertex vertex;

struct graph{
    int E;
    int V;
    vertex* vertices;
    edge* edges;           // only for swsssssssssssssssssssssssssssssstopological sort
};
typedef graph graph;

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
        G->vertices[u].u=u;
        return q->next;
    }
}

edge* add_edge (graph* G, int u, int v, int w){
    if (((G->V)*((G->V)-1)) > G->E){
        edge* tmp=new edge;
        tmp=adding(G, u, v, w);
        if (tmp != NULL){
            if (G->E == 0){
                G->edges=new edge;
                G->edges->w=-1;
                G->edges->next=NULL;
            }
            edge* p=G->edges;
            while (p->next != NULL && p->next->w < w) p=p->next;
            edge* e=new edge;
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

void output (graph* G){
    cout << "E: " << G->E << " | V: " << G->V << endl;
    edge* tmp=G->edges->next;
    while (tmp != NULL){
        cout << "(" << tmp->u << "," << tmp->v << ")[" << tmp->w << "] ";
        tmp=tmp->next;
    }
    cout << endl;
    for (int i=0; i<G->V; i++){
        cout << i << " /p:";
        if (G->vertices[i].parent == NULL) cout << "NULL";
        else cout << G->vertices[i].parent->u;
        cout << "/" << G->vertices[i].d << "/: ";
        edge* tmp=G->vertices[i].edges;
        while (tmp != NULL){
            cout << tmp->v << " [" << tmp->w << "] -> ";
            tmp=tmp->next;
        }
        cout << "NULL" << endl;
    }
}

void random_edges (graph* G, int n){
	for (int i=0; i<n && ((((G->V)-1)*(G->V))) > G->E; i++){
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

void initialize (graph* G, int s){
    for (int i=0; i<G->V; i++){
        G->vertices[i].d=INT_MAX;
        G->vertices[i].parent=NULL;
    }
    G->vertices[s].d=0;
}

void relax (graph* G, int u, int v, int w){
    if (G->vertices[u].d < INT_MAX && G->vertices[v].d > G->vertices[u].d + w){
        G->vertices[v].d=G->vertices[u].d+w;
        if (G->vertices[v].parent == NULL) G->vertices[v].parent=new vertex;
        G->vertices[v].parent=&(G->vertices[u]);
    }
}

bool BellmanFord (graph* G, int s){
    initialize(G, s);
    for (int i=0; i < (G->V)-1; i++){
        edge* e=G->edges->next;
        while (e != NULL){
            relax(G, e->u, e->v, e->w);
            e=e->next;
        }
        //output(G);
        //cout << endl;
    }
    edge* e=G->edges->next;
    bool okay=true;
    while (e != NULL){
        if (G->vertices[e->v].d > G->vertices[e->u].d + e->w){
            G->vertices[e->v].d=INT_MIN;
            okay=false;
        }
        e=e->next;
    }
    if (okay) return true;
    else return false;
}

int main(){
    graph* G=new graph;
    G->V=0;

    // CLRS 24.4-2.
    for (int i=0; i<6; i++) add_vertex(G);
    add_edge(G, 2, 1, 4);
    add_edge(G, 5, 1, 5);
    add_edge(G, 4, 2, -6);
    add_edge(G, 2, 3, 1);
    add_edge(G, 1, 4, 3);
    add_edge(G, 3, 4, 5);
    add_edge(G, 5, 4, 10);
    add_edge(G, 3, 5, -4);
    add_edge(G, 4, 5, -8);
    for (int i=1; i<6; i++) add_edge(G, 0, i, 0);
    if (BellmanFord(G, 0)) output(G);
    output(G);

    /** CLRS 24.4-1.
    for (int i=0; i<7; i++) add_vertex(G);
    add_edge(G, 2, 1, 1);
    add_edge(G, 4, 1, -4);
    add_edge(G, 3, 2, 2);
    add_edge(G, 5, 2, 7);
    add_edge(G, 6, 2, 5);
    add_edge(G, 6, 3, 10);
    add_edge(G, 2, 4, 2);
    add_edge(G, 1, 5, -1);
    add_edge(G, 4, 5, 3);
    add_edge(G, 3, 6, -8);
    for (int i=1; i<7; i++) add_edge(G, 0, i, 0);
    if (BellmanFord(G, 0)) output(G);
    **/

    /** CLRS Rys. 24.4.
    for (int i=0; i<5; i++) add_vertex(G);
    add_edge(G, 0, 1, 6);
    add_edge(G, 1, 2, 5);
    add_edge(G, 2, 1, -2);
    add_edge(G, 1, 3, -4);
    add_edge(G, 3, 2, 7);
    add_edge(G, 4, 3, 9);
    add_edge(G, 3, 0, 2);
    add_edge(G, 4, 2, -3);
    add_edge(G, 0, 4, 7);
    add_edge(G, 1, 4, 8);
    if (BellmanFord(G, 0)) output(G);
    **/



}
