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

}

int main(){
    inicializarNIL();
    raiz=NIL;
    criarNo(10);
    return 0;
}