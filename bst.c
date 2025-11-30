#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int valor;
    struct Node *dir, *esq;
} Node;

Node *criarNo(int valor)
{
    Node *novoNo = (Node *)malloc(sizeof(Node));
    novoNo->valor = valor;
    novoNo->dir = NULL;
    novoNo->esq = NULL;

    return novoNo;
}

Node *inserir(Node *raiz, int valor)
{
    if (raiz == NULL)
    {
        return criarNo(valor);
    }

    if (valor < raiz->valor)
    {
        raiz->esq = inserir(raiz->esq, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz;
}

void imprimirEmOrdem(Node *raiz)
{
    if (raiz != NULL)
    {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->dir);
    }
}

int main()
{
    Node *raiz = NULL;

    raiz = inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 60);
    inserir(raiz, 20);
    inserir(raiz, 40);
    inserir(raiz, 90);

    imprimirEmOrdem(raiz);
    printf("\n");

    return 0;
}