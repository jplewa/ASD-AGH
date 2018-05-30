#include <iostream>
#include <iomanip>

using namespace std;

/**
enum balance{
    right = 1, left = -1, balanced = 0
};

typedef balance balance;
**/

struct Node{
    int v;
    int b;
    Node* left;
    Node* right;
    Node* parent;
};

typedef Node Node;

int height (Node* T){
    if (T==NULL) return -1;
    else return T->b;
}

void update(Node* T){
    T->b=(max(height(T->left), height(T->right))+1);
}

int balance(Node* T){
    return height(T->right)-height(T->left);
}

void LR (Node** x){                 // tylko jeœli prawy syn nie jest NULL'em
    if ((*x)->right!=NULL){
        Node* y=(*x)->right;
        (*x)->right=y->left;
        if (y->left!=NULL) y->left->parent=(*x);
        y->parent=(*x)->parent;
        if ((*x)->parent!=NULL && (*x)->parent->left==(*x)) (*x)->parent->left=y;
        else if ((*x)->parent!=NULL && (*x)->parent->right==(*x)) (*x)->parent->right=y;
        y->left=(*x);
        (*x)->parent=y;

        (*x)=y;
    }
}

void RR (Node** y){
    if ((*y)->left!=NULL){
        Node* x=(*y)->left;
        (*y)->left=x->right;
        if ((*y)->left!=NULL) (*y)->left->parent=(*y);
        x->parent=(*y)->parent;
        if ((*y)->parent!=NULL && (*y)->parent->left==(*y)) (*y)->parent->left=x;
        else if ((*y)->parent!=NULL && (*y)->parent->right==(*y)) (*y)->parent->right=x;
        x->right=(*y);
        (*y)->parent=x;

        (*y)=x;
    }
}

void AVL_insert (Node** T, int x){
    if ((*T) == NULL){
        (*T)=new Node;
        (*T)->v=x;
        (*T)->right=NULL;
        (*T)->left=NULL;
        (*T)->parent=NULL;
        (*T)->b=0;
    }
    else{
        Node* p=(*T);
        Node* q=(*T);
        while (q!=NULL){
            p=q;
            if (x > q->v){
                q=q->right;
            }
            else{
                q=q->left;
            }
        }
        if (p->v < x){
            p->right=new Node;
            p->right->v=x;
            p->right->right=NULL;
            p->right->left=NULL;
            p->right->parent=p;
            p->right->b=0;
            q=p->right;
        }
        else{
            p->left=new Node;
            p->left->v=x;
            p->left->right=NULL;
            p->left->left=NULL;
            p->left->parent=p;
            p->left->b=0;
            q=p->left;
        }
        while (p!=NULL){
            if (p->right == q){
                p->b++;
                if (balance(p) == 2){
                    if (balance(q) == 0 || balance(q) == 1 || balance(q) == 2) LR(&p);
                    else{
                        RR(&q);
                        LR(&p);
                    }
                }
            }
            else{
                p->b--;
                if (balance(p) == -2){
                    if (balance(q)== 0 || balance(q) == -1 || balance(q) == -2) RR(&p);
                    else{
                        LR(&q);
                        RR(&p);
                    }
                }
            }

            if (p->left != NULL) update(p->left);
            if (p->right != NULL) update(p->right);
            if (p != NULL) update(p);
            q=p;
            p=p->parent;
        }
        (*T)=q;
    }
}

void traverse(Node* T){
    if (T->left!=NULL) traverse(T->left);
    cout << T->v << " ";
    if (T->right!=NULL) traverse(T->right);
}

void prettyprint(Node* p, int indent=50){
    if(p != NULL) {
        if(p->right) {
            prettyprint(p->right, indent+4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (p->right) cout<<" /\n" << setw(indent) << ' ';
        cout<< p->v << "\n ";
        if(p->left) {
            cout << setw(indent) << ' ' <<" \\\n";
            prettyprint(p->left, indent+4);
        }
    }
}

void print (Node* T){
    if (T->left != NULL) print (T->left);
    cout << endl<< "wartosc: " << T->v << " | wysokosc: " << T->b << " | balans: " << balance(T) << " | rodzic: ";
    if (T->parent != NULL) cout << T->parent->v;
    else cout << "NULL";
    cout << " | lewe dziecko: ";
    if (T->left != NULL) cout << T->left->v;
    else cout << "NULL";
    cout << " | prawe dziecko: ";
    if (T->right != NULL) cout << T->right->v;
    else cout << "NULL";
    if (T->right != NULL) print (T->right);
}

void check(Node* T){
    print(T);
    cout << endl << endl;
    prettyprint(T);
    cout << endl;
}

int main(){
    /**
    Node* T=new Node;
    T->v=5;
    T->parent=NULL;
    T->left=new Node;
    T->right=new Node;
    T->b=0;

    T->right->v=7;
    T->left->v=3;

    T->right->b=0;
    T->left->b=0;

    T->right->right=NULL;
    T->right->left=NULL;
    T->left->right=NULL;
    T->left->left=NULL;

    T->right->parent=T;
    T->left->parent=T;
**/
/**
    T->right->right=new Node;
    T->right->left=new Node;
    T->right->left->v=6;
    T->right->right->v=10;
    T->right->left->left=NULL;
    T->right->left->right=NULL;
    T->right->right->left=NULL;
    T->right->right->right=NULL;
**/
    Node* T=new Node;
    T=NULL;
    AVL_insert(&T, 15);
    check(T);
    //AVL_insert(&T, 1);
    //check(T);
    AVL_insert(&T, 7);
    check(T);
    AVL_insert(&T, 10);
    check(T);
    AVL_insert(&T, 13);
    check(T);
    AVL_insert(&T, 11);
    check(T);
    AVL_insert(&T, 14);
    check(T);
    AVL_insert(&T, 12);
    check(T);

    AVL_insert(&T, 8);
    check(T);
    AVL_insert(&T, 9);
    check(T);
}
