#include <iostream>
#include <cstdlib>

using namespace std;

enum color{
    white=0,
    gray=1,
    black=2,
};

enum type{
    T=0,
    F=1,
    B=2,
    C=-1,
};

struct edge{
    int v;
    int w;
    type type;
    edge* next;
};
typedef edge edge;

struct vertex{
    int u;
    int d;
    int f;
    color color;
    vertex* parent;
    edge* edges;
};
typedef vertex vertex;

struct vertex_edge{
    int index;
    vertex_edge* next;
};
typedef vertex_edge vertex_edge;

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
    tmp.u=(G->V)-1;
    tmp.d=0;
    tmp.f=0;
    tmp.parent=NULL;
    tmp.edges=NULL;
    tmp.color=white;
    G->vertices[(G->V)-1]=tmp;
}

void add_edge (graph* G, int u, int v, int w){
    edge* p=new edge;
    p->v=-1;
    p->next=G->vertices[u].edges;
    edge* q=p;
    edge* r=p;
    while (r != NULL && r->v < v){
        q=r;
        r=r->next;
    }
    if (r != NULL && r->v == v) cout << "Krawedz z " << u << " do " << v << " juz istnieje!" << endl;
    else{
        q->next=new edge;
        q->next->v=v;
        q->next->w=w;
        q->next->next=r;
        G->vertices[u].edges=p->next;
        G->E++;
    }
}

void type_output(type type){
    if (type == T) cout << "T";
    else if (type == F) cout << "F";
    else if (type == B) cout << "B";
    else cout << "C";
}

void output (graph* G, bool p){
    cout << "E: " << G->E << " | V: " << G->V << endl;
    for (int i=0; i<G->V; i++){
        cout << i;
        if (p){
            if (G->vertices[i].parent == NULL) cout << " <- NULL";
            else cout << " <- " << G->vertices[i].parent->u;
            cout << " ["  << G->vertices[i].d  << "]";
        }
        cout << ": ";
        edge* tmp=G->vertices[i].edges;
        while (tmp != NULL){
            cout << tmp->v;
            if (!p){
                cout << "|";
                type_output(tmp->type);
            }
            else cout << "[" << tmp->w << "]";
            cout << " -> ";
            tmp=tmp->next;
        }
        cout << "NULL";
        if (!p){
            cout << "   c: " << G->vertices[i].color << " | " << G->vertices[i].d << "/" << G->vertices[i].f << " | p: ";
            if (G->vertices[i].parent == NULL) cout << "NULL";
            else cout << G->vertices[i].parent->d << "/" << G->vertices[i].parent->f;
            cout << ") ";
        }
        cout << endl;
    }
}

void DFS_VISIT (graph* G, int u, int &time, bool cycle_search, bool &cycle_found, vertex_edge* t){
    if (!cycle_search || !cycle_found){
        time++;
        G->vertices[u].d=time;
        G->vertices[u].color=gray;
        edge* tmp=G->vertices[u].edges;
        while (tmp != NULL){
            if (G->vertices[tmp->v].color == white){
                tmp->type=T;
                G->vertices[tmp->v].parent=&(G->vertices[u]);
                DFS_VISIT (G, tmp->v, time, cycle_search, cycle_found, t);
            }
            else if (G->vertices[tmp->v].color == gray){
                tmp->type=B;
                if (cycle_search){
                    cycle_found=true;
                    break;
                }
            }
            else if (G->vertices[tmp->v].color == black && G->vertices[tmp->v].d > G->vertices[u].d) tmp->type=F;
            else tmp->type=C;
            tmp=tmp->next;
        }
        G->vertices[u].color=black;
        if (t->index == -1){
            vertex_edge* tmp=new vertex_edge;
            tmp->index=u;
            tmp->next=t->next;
            t->next=tmp;
        }
        time++;
        G->vertices[u].f=time;
    }
}

void DFS (graph* G){
    for (int i=0; i<G->V; i++){
        G->vertices[i].color=white;
        G->vertices[i].parent=NULL;
    }
    int time=0;
    bool tmp=false;
    vertex_edge* t=new vertex_edge;
    t->index=0;
    t->next=NULL;
    for (int i=0; i<G->V; i++){
        if (G->vertices[i].color == white) DFS_VISIT(G, i, time, false, tmp, t);
    }
    delete t;
}

bool cycle (graph* G){
    if (G->E > 2*G->V - 2) return true;
    for (int i=0; i<G->V; i++){
        G->vertices[i].color=white;
        G->vertices[i].parent=NULL;
    }
    int time=0;
    bool found=false;
    vertex_edge* t=new vertex_edge;
    t->index=0;
    t->next=NULL;
    for (int i=0; i<G->V; i++){
        if (G->vertices[i].color == white) DFS_VISIT(G, i, time, true, found, t);
    }
    delete t;
    if (found) return true;
    else return false;
}

void remove_edge (graph* G, int u, int v){
    edge* p=new edge;
    p->v=-1;
    p->next=G->vertices[u].edges;
    edge* q=p;
    edge* r=p;
    while (r != NULL && r->v < v){
        q=r;
        r=r->next;
    }
    if (r != NULL && r->v == v){
        q->next=r->next;
        G->vertices[u].edges=p->next;
        G->E--;
    }
    else cout << "Taka krawedz nie istnieje!" << endl;
}

vertex_edge* topological (graph* G){
    for (int i=0; i<G->V; i++){
        G->vertices[i].color=white;
        G->vertices[i].parent=NULL;
    }
    int time=0;
    bool tmp=false;
    vertex_edge* t=new vertex_edge;
    t->index=-1;
    t->next=NULL;
    for (int i=0; i<G->V; i++){
        if (G->vertices[i].color == white) DFS_VISIT(G, i, time, false, tmp, t);
    }
    return t->next;
}

void topological_output (graph* G){
    vertex_edge* t=new vertex_edge;
    t=topological(G);
    cout << endl;
    while (t != NULL){
        cout << t->index << " -> ";
        t=t->next;
    }
    cout << "NULL" << endl << endl;
}

graph* transpose (graph* G){
    graph* GT=new graph;
    GT->E=0;
    GT->V=G->V;
    GT->vertices=(vertex*)(malloc((GT->V)*sizeof(vertex)));
    for (int i=0; i<GT->V; i++){
        GT->vertices[i].d=0;
        GT->vertices[i].f=0;
        GT->vertices[i].parent=NULL;
        GT->vertices[i].color=white;
        GT->vertices[i].edges=NULL;
    }
    for (int i=0; i<G->V; i++){
        edge* tmp=G->vertices[i].edges;
        while (tmp != NULL){
            add_edge(GT, tmp->v, i, tmp->w);
            tmp=tmp->next;
        }
    }
    return GT;
}

void SCC (graph* G){
    for (int i=0; i<G->V; i++){
        G->vertices[i].color=white;
        G->vertices[i].parent=NULL;
    }
    int time=0;
    bool tmp=false;
    vertex_edge* t=new vertex_edge;
    t->index=-1;
    t->next=NULL;
    for (int i=0; i<G->V; i++){
        if (G->vertices[i].color == white) DFS_VISIT(G, i, time, false, tmp, t);
    }
    graph* GT=transpose(G);
    for (int i=0; i<GT->V; i++){
        GT->vertices[i].color=white;
        GT->vertices[i].parent=NULL;
    }
    time=0;
    t=t->next;
    while (t != NULL){
        vertex_edge* s=new vertex_edge;
        s->index=-1;
        s->next=NULL;
        if (GT->vertices[t->index].color == white){
            DFS_VISIT(GT, t->index, time, false, tmp, s);
            s=s->next;
            while (s != NULL){
                cout << s->index << " -> ";
                s=s->next;
            }
            cout << "NULL" << endl;
        }
        t=t->next;
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
    if (G->vertices[u].d != INT_MAX && G->vertices[v].d > G->vertices[u].d + w){
        G->vertices[v].d=G->vertices[u].d+w;
        G->vertices[v].parent=&(G->vertices[u]);
    }
}

void DAG_sp (graph* G, int s){
    vertex_edge* t=topological(G);
    initialize(G, s);
    while (t != NULL){
        edge* tmp=G->vertices[t->index].edges;
        while (tmp != NULL){
            relax(G, t->index, tmp->v, tmp->w);
            tmp=tmp->next;
        }
        t=t->next;
    }
}

int main(){
    graph* G=new graph;
    G->V=1;
    G->E=0;
    G->vertices=(vertex*)(malloc(sizeof(vertex)));
    vertex tmp;
    tmp.d=0;
    tmp.u=0;
    tmp.f=0;
    tmp.color=white;
    tmp.parent=NULL;
    tmp.edges=NULL;
    G->vertices[0]=tmp;
    for (int i=0; i<5; i++) add_vertex(G);
    while (G->E < 10){
        int u=rand()%(G->V);
        int v=rand()%(G->V);
        while (v == u) v=rand()%(G->V);
        add_edge(G, u, v, rand()%20);
        if (cycle(G)) remove_edge(G, u, v);
    }
    cout << endl;
    add_vertex(G);
    DFS(G);
    output(G, false);
    topological_output(G);

    add_vertex(G);
    add_vertex(G);
    while (G->E < 20){
        int u=rand()%(G->V);
        int v=rand()%(G->V);
        while (v == u) v=rand()%(G->V);
        add_edge(G, u, v, rand()%20);
    }
    cout << endl;
    output(G, false);
    cout << endl;
    SCC(G);

    graph* D=new graph;
    D->V=1;
    D->E=0;
    D->vertices=(vertex*)(malloc(sizeof(vertex)));
    vertex tmp2;
    tmp2.d=0;
    tmp2.u=0;
    tmp2.f=0;
    tmp2.color=white;
    tmp2.parent=NULL;
    tmp2.edges=NULL;
    D->vertices[0]=tmp2;
    for (int i=0; i<5; i++) add_vertex(D);
    cout << endl;
    add_edge(D, 0, 1, 5);
    add_edge(D, 0, 2, 3);
    add_edge(D, 1, 2, 2);
    add_edge(D, 1, 3, 6);
    add_edge(D, 2, 3, 7);
    add_edge(D, 3, 5, 1);
    add_edge(D, 3, 4, -1);
    add_edge(D, 4, 5, -2);
    add_edge(D, 2, 4, 4);
    add_edge(D, 2, 5, 2);
    output(D, true);
    cout << endl;
    DAG_sp(D, 0);
    output(D, true);
}
