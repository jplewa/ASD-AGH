#include <iostream>

using namespace std;

struct heap{
    int v[10];
    int s;
};

typedef heap heap;

int parent (int x){
    if (x==0) return -1;
    else return (x-1)/2;
}

int left (int x){
    return (x*2)+1;
}

int right (int x){
     return (x+1)*2;
}

void heapify (heap* A, int x){
    while (x <= ((A->s)/2)-1){
        if (right(x) < A->s){
            if (A->v[right(x)] > A->v[x] || A->v[left(x)] > A->v[x]){
                int tmp=0;
                if (A->v[right(x)] > A->v[left(x)]){
                    tmp=A->v[right(x)];
                    A->v[right(x)]=A->v[x];
                    A->v[x]=tmp;
                    x=right(x);
                }
                else{
                    tmp=A->v[left(x)];
                    A->v[left(x)]=A->v[x];
                    A->v[x]=tmp;
                    x=left(x);
                }
            }
            else if (A->v[right(x)] == A->v[x]){
                x=right(x);
            }
            else if (A->v[left(x)] == A->v[x]){
                x=left(x);
            }
            else{
                x=(A->s);
            }
        }
        else if (A->v[left(x)]>A->v[x]){
            int tmp=A->v[left(x)];
            A->v[left(x)]=A->v[x];
            A->v[x]=tmp;
            x=left(x);
        }
        else if (A->v[left(x)] == A->v[x]){
            x=left(x);
        }
        else{
            x=(A->s);
        }
    }
}

void build_heap (heap* A){
    for (int i=((A->s)-1)/2; i>=0; i--){
        heapify(A, i);
    }
}

int max_el (heap* A){
    return A->v[0];
}

void heap_sort (heap* A){
    while ((A->s)>1){
        int tmp = max_el(A);
        A->v[0]=A->v[(A->s)-1];
        A->v[(A->s)-1]=tmp;
        (A->s)--;
        heapify(A, 0);
    }
}

int main()
{
    heap A;
    A.s=10;
    for (int i=0; i<10; i++){
        cin >> A.v[i];
    }

    build_heap(&A);

    cout << endl;

    heap_sort(&A);

    for (int i=0; i<10; i++){
        cout << A.v[i] << " ";
    }
    cout << endl;


    return 0;
}
