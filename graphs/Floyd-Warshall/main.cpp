#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;

struct graph{
    int V;
    int** E;
    int** R;
    int** P;
    bool** T;
};
typedef graph graph;

void create (graph* G){
    G->E=(int**)(malloc((G->V)*sizeof(int*)));
    for (int i=0; i<G->V; i++) G->E[i]=(int*)(malloc((G->V)*sizeof(int)));
    G->P=(int**)(malloc((G->V)*sizeof(int*)));
    for (int i=0; i<G->V; i++) G->P[i]=(int*)(malloc((G->V)*sizeof(int)));
    for (int i=0; i<G->V; i++){
        for (int j=0; j<G->V; j++){
            G->E[i][j]=INT_MAX;
            G->P[i][j]=-1;
        }
        G->E[i][i]=0;
        G->P[i][i]=i;
    }
    G->R=(int**)(malloc((G->V)*sizeof(int*)));
    for (int i=0; i<G->V; i++) G->R[i]=(int*)(malloc((G->V)*sizeof(int)));
    G->T=(bool**)(malloc((G->V)*sizeof(bool*)));
    for (int i=0; i<G->V; i++) G->T[i]=(bool*)(malloc((G->V)*sizeof(bool)));
}

void make_copy (graph* G){
    for (int i=0; i<G->V; i++){
        for (int j=0; j<G->V; j++){
            G->R[i][j]=G->E[i][j];
            if (G->R[i][j] != 0 && G->R[i][j] < INT_MAX) G->P[i][j]=i;
        }
    }
}

void output (graph* G, bool p){
    for (int i=1; i<G->V; i++){
        cout << i << ": ";
        if (!p){
            for (int j=1; j<G->V; j++){
                cout << j << "[";
                if (G->E[i][j] == INT_MAX) cout << "oo";
                else cout << G->E[i][j];
                cout << "] ";
            }
        }
        else{
            for (int j=1; j<G->V; j++){
                cout << j << "[";
                if (G->R[i][j] == INT_MAX) cout << "oo";
                else cout << G->R[i][j];
                cout << "][p:" << G->P[i][j] << "] ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void FloydWarshall (graph* G){
    make_copy(G);
    int n=G->V;
    for (int k=0; k<n; k++){
        for (int j=0; j<n; j++){
            for (int i=0; i<n; i++){
                if (G->R[i][k] != INT_MAX && G->R[k][j] != INT_MAX){
                    if (G->R[i][j] > (G->R[i][k])+(G->R[k][j])){
                        G->R[i][j]=(G->R[i][k])+(G->R[k][j]);
                        G->P[i][j]=G->P[k][j];
                    }
                    // G->R[i][j]=min(G->R[i][j], (G->R[i][k])+(G->R[k][j]));
                }
            }
        }
    }
}

void PrintPaths (graph* G, int i, int j){
    if (G->P[i][j] == -1) cout << "brak";
    else if (i == j) cout << i;
    else{
        cout << j << "<-";
        PrintPaths(G, i, G->P[i][j]);
    }
}

void TransitiveClosure (graph* G){
    int n=G->V;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (G->E[i][j] == INT_MAX) G->T[i][j]=0;
            if (G->E[i][j] < INT_MAX) G->T[i][j]=1;
        }
    }
    for (int k=0; k<n; k++){
        for (int j=0; j<n; j++){
            for (int i=0; i<n; i++){
                G->T[i][j]=G->T[i][j]|(G->T[i][k]&G->T[k][j]);
            }
        }
    }
    for (int i=0; i<G->V; i++){
        cout << i << ": ";
        for (int j=0; j<G->V; j++){
            cout << G->T[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    graph* G=new graph;

    //CLRS 25.2-1.
    //CLRS 25.2-4.
    G->V=7;
    create(G);
    G->E[1][5]=-1;
    G->E[2][1]=1;
    G->E[2][4]=2;
    G->E[3][2]=2;
    G->E[3][6]=-8;
    G->E[4][1]=-4;
    G->E[4][5]=3;
    G->E[5][2]=7;
    G->E[6][3]=10;
    G->E[6][2]=5;
    output(G, false);
    FloydWarshall(G);
    output(G, true);
    cout << endl;

    for (int i=1; i<G->V; i++){
        for (int j=1; j<G->V; j++){
            cout << i << " do " << j << ": ";
            PrintPaths(G, i, j);
            cout << " | " << G->R[i][j] << endl;
        }
    }

    /**
    // CLRS 25.5
    G->V=4;
    create(G);
    G->E[3][0]=1;
    G->E[3][2]=-2;
    G->E[1][3]=5;
    G->E[1][2]=4;
    G->E[2][1]=-3;
    output(G, false);
    FloydWarshall(G);
    output(G, true);
    TransitiveClosure(G);
    **/
}
