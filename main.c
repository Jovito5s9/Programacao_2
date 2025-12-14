#include <stdio.h>
#include <stdlib.h>

typedef struct RBNo{
    int data;
    char cor;
    struct RBNo *esquerda, *direita, *pai; 
}RBNo;

RBNo *raiz = NULL;
RBNo *NIL; //Esse é o nó sentinela

void inicializarNIL(){
    NIL = (RBNo *)malloc(sizeof(RBNo));
    NIL->cor='B';//cor preta padrao pros espacos vazios
    NIL->esquerda=NIL->direita=NIL->pai=NULL;
}

RBNo* criarNo(int data){
    RBNo *no = (RBNo *)malloc(sizeof(RBNo));
    no->data=data;
    no->cor='R';
    no->esquerda=no->direita=no->pai=NIL;
    return no;
}

void rotacionarEsq(RBNo *x){
    RBNo *y;
    y=x->direita;
    x->direita=y->esquerda;
    if (y->esquerda!= NIL){
        y->esquerda->pai=x;
    }
    y->pai=x->pai;
    if(x->pai==NIL){
        raiz=y;
    }
    else if(x==x->pai->esquerda){
        x->pai->esquerda=y;
    }
    else{
        x->pai->direita=y;
    }
    y->esquerda=x;
    x->pai=y;
}

void rotacionarDir(RBNo *x){
    RBNo *y;
    y=x->esquerda;
    x->esquerda=y->direita;
    if (y->direita!= NIL){
        y->direita->pai=x;
    }
    y->pai=x->pai;
    if(x->pai==NIL){
        raiz=y;
    }
    else if(x==x->pai->direita){
        x->pai->direita=y;
    }
    else{
        x->pai->esquerda=y;
    }
    y->direita=x;
    x->pai=y;
}


void corrigirInsercao(RBNo *z){
    while(z->pai->cor=='R'){
        if (z->pai==z->pai->pai->esquerda){
            RBNo *y=z->pai->pai->direita;
            if(y->cor=='R'){
                z->pai->cor='B';
                y->cor='B';
                z->pai->pai->cor='R';
                z=z->pai->pai;
            }else{
                if (z==z->pai->direita){
                    z=z->pai;
                    rotacionarEsq(z);
                }
                z->pai->cor='B';
                z->pai->pai->cor='R';
                rotacionarDir(z->pai->pai);
            }
        }else {
            RBNo *y = z->pai->pai->esquerda;
            if (y->cor == 'R') {
                z->pai->cor = 'B';
                y->cor = 'B';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
                if (z == z->pai->esquerda) {
                    z = z->pai;
                    rotacionarDir(z);
                }
                z->pai->cor = 'B';
                z->pai->pai->cor = 'R';
                rotacionarEsq(z->pai->pai);
            }
        }
    }
    raiz->cor = 'B';
}

void insercao(int data){
    RBNo *z = criarNo(data);
    RBNo *y = NIL;
    RBNo *x = raiz;

    while (x!=NIL){
        y=x;
        if(z->data < x->data){
            x=x->esquerda;
        }else{
            x=x->direita;
        }
    }

    z->pai=y;
    if(y==NIL){
        raiz=z;
    }else if(z->data < y->data){
        y->esquerda=z;
    }else{
        y->direita=z;
    }
    corrigirInsercao(z);
}

int main(){
    inicializarNIL();
    raiz=NIL;

    insercao(10);
    return 0;
}