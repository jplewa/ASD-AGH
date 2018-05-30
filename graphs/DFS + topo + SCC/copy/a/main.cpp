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
    int w;
    int value;
    type type;
    edge* next;
};
typedef edge edge;

struct vertex{
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
    tmp.d=0;
    tmp.f=0;
    tmp.parent=NULL;
    tmp.edges=NULL;
    tmp.color=white;
    G->vertices[(G->V)-1]=tmp;
}

void add_edge (graph* G, int u, int v){
    edge* p=new edge;
    p->value=-1;
    p->next=G->vertices[u].edges;
    edge* q=p;
    edge* r=p;
    while (r != NULL && r->value < v){
        q=r;
        r=r->next;
    }
    if (r != NULL && r->value == v) cout << "Krawedz z " << u << " do " << v << " juz istnieje!" << endl;
    else{
        q->next=new edge;
        q->next->value=v;
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

void output (graph* G){
    cout << "E: " << G->E << " | V: " << G->V << endl;
    for (int i=0; i<G->V; i++){
        cout << i << ": ";
        edge* tmp=G->vertices[i].edges;
        while (tmp != NULL){
            cout << tmp->value << "|";
            type_output(tmp->type);
            cout << " -> ";
            tmp=tmp->next;
        }
        cout << "NULL   (c: " << G->vertices[i].color << " | " << G->vertices[i].d << "/" << G->vertices[i].f << " | p: ";
        if (G->vertices[i].parent == NULL) cout << "NULL";
        else cout << G->vertices[i].parent->d << "/" << G->vertices[i].parent->f;
        cout << ") " << endl;
    }
}

void DFS_VISIT (graph* G, int u, int &time, bool cycle_search, bool &cycle_found, vertex_edge* t){
    if (!cycle_search || !cycle_found){
        time++;
        G->vertices[u].d=time;
        G->vertices[u].color=gray;
        edge* tmp=G->vertices[u].edges;
        while (tmp != NULL){
            if (G->vertices[tmp->value].color == white){
                tmp->type=T;
                G->vertices[tmp->value].parent=&(G->vertices[u]);
                DFS_VISIT (G, tmp->value, time, cycle_search, cycle_found, t);
            }
            else if (G->vertices[tmp->value].color == gray){
                tmp->type=B;
                if (cycle_search){
                    cycle_found=true;
                    break;
                }
            }
            else if (G->vertices[tmp->value].color == black && G->vertices[tmp->value].d > G->vertices[u].d) tmp->type=F;
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
    p->value=-1;
    p->next=G->vertices[u].edges;
    edge* q=p;
    edge* r=p;
    while (r != NULL && r->value < v){
        q=r;
        r=r->next;
    }
    if (r != NULL && r->value == v){
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
            add_edge(GT, tmp->value, i);
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

int main(){
    graph* G=new graph;
    G->V=1;
    G->E=0;
    G->vertices=(vertex*)(malloc(sizeof(vertex)));
    vertex tmp;
    tmp.d=0;
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
        add_edge(G, u, v);
        if (cycle(G)) remove_edge(G, u, v);
    }
    cout << endl;
    add_vertex(G);
    DFS(G);
    output(G);
    topological_output(G);

    add_vertex(G);
    add_vertex(G);
    while (G->E < 20){
        int u=rand()%(G->V);
        int v=rand()%(G->V);
        while (v == u) v=rand()%(G->V);
        add_edge(G, u, v);
    }
    cout << endl;
    output(G);
    cout << endl;
    SCC(G);
}
