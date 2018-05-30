#include <iostream>
#include <cstdlib>

using namespace std;

struct edge{
    int v;
    int w;
    edge* next;
};
typedef edge edge;

struct vertex{
    int d;
    int u;
    color color;
    vertex* parent;
    edge* edges;
};
typedef vertex vertex;

struct graph{
    int E;
    int V;
    vertex* vertices;
};
typedef graph graph;

void add_vertex (graph* G){
    G->V++;
    G->vertices=(vertex*)(realloc(G->vertices, G->V*sizeof(vertex)));
    vertex tmp;
    tmp.d=0;
    tmp.f=0;
    tmp.parent=NULL;
    tmp.edges=NULL;
    tmp.color=white;
    G->vertices[(G->V)-1]=tmp;
}

void add_edge (graph* G, int u, int v){
    node* p=new node;
    p->value=-1;
    p->next=G->vertices[u].edges;
    node* q=p;
    node* r=p;
    while (r != NULL && r->value < v){
        q=r;
        r=r->next;
    }
    if (r != NULL && r->value == v) cout << "Krawedz z " << u << " do " << v << " juz istnieje!" << endl;
    else{
        q->next=new node;
        q->next->value=v;
        q->next->next=r;
        G->vertices[u].edges=p->next;
        G->E++;
    }
}

vertex_node* topological (graph* G){
    for (int i=0; i<G->V; i++){
        G->vertices[i].color=white;
        G->vertices[i].parent=NULL;
    }
    int time=0;
    bool tmp=false;
    vertex_node* t=new vertex_node;
    t->index=-1;
    t->next=NULL;
    for (int i=0; i<G->V; i++){
        if (G->vertices[i].color == white) DFS_VISIT(G, i, time, false, tmp, t);
    }
    return t->next;
}

void topological_output (graph* G){
    vertex_node* t=new vertex_node;
    t=topological(G);
    cout << endl;
    while (t != NULL){
        cout << t->index << " -> ";
        t=t->next;
    }
    cout << "NULL" << endl << endl;
}

int main(){

}
