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

int main(){
    inicializarNIL();
    raiz=NIL;

    return 0;
}