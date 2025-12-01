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

Node *remover(Node *raiz, int valor)
{
    // buscar o valor
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor)
    {
        raiz->esq = remover(raiz->esq, valor);
        return raiz;
    }
    else if (valor > raiz->valor)
    {
        raiz->dir = remover(raiz->dir, valor);
        return raiz;
    }

    // remoção de folhas
    if (raiz->dir == NULL && raiz->esq == NULL)
    {
        free(raiz);
        return NULL;
    }

    // remoção de nó com 1 filho
    if (raiz->esq == NULL)
    {
        Node *temp = raiz;
        raiz = raiz->dir;
        free(temp);
        return raiz;
    }
    else if (raiz->dir == NULL)
    {
        Node *temp = raiz;
        raiz = raiz->esq;
        free(temp);
        return raiz;
    }
    // remoção de nó com 2 filhos (o sucessor da raiz removida torna-se a nova raiz)
    else
    {
        Node *temp = raiz->dir;
        while (temp->esq != NULL)
        {
            temp = temp->esq;
        }

        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
        return raiz;
    }
}

int buscarValor(Node *raiz, int valor)
{
    if (raiz == NULL)
    {
        return 0;
    }

    if (valor == raiz->valor)
    {
        return 1;
    }

    if (valor < raiz->valor)
    {
        return buscarValor(raiz->esq, valor);
    }

    else
    {
        return buscarValor(raiz->dir, valor);
    }
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

void imprimirPreOrdem(Node *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        imprimirPreOrdem(raiz->esq);
        imprimirPreOrdem(raiz->dir);
    }
}

void imprimirPosOrdem(Node *raiz)
{
    if (raiz != NULL)
    {
        imprimirPosOrdem(raiz->esq);
        imprimirPosOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

void liberarArvore(Node *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

Node *uiUsuario(Node *raiz)
{
    int resposta;
    do
    {
        printf("Qual a operação que deseja realizar?\n");
        printf("1. Inserir valor\n");
        printf("2. Buscar valor\n");
        printf("3. Remover valor\n");
        printf("4. Percorrer árvore\n");
        printf("0. Sair\n");
        scanf("%d", &resposta);

        switch (resposta)
        {
        case 1:
            printf("Qual valor deseja inserir: ");
            int valor;
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;

        case 2:
            printf("Qual valor deseja buscar: ");
            int valorBusca;
            scanf("%d", &valorBusca);

            if (buscarValor(raiz, valorBusca))
            {
                printf("Valor %d encontrado na árvore!\n", valorBusca);
            }
            else
            {
                printf("Valor %d não existe na árvore.\n", valorBusca);
            }
            break;

        case 3:
            printf("Qual dos valores deseja remover?\n");
            imprimirEmOrdem(raiz);
            int valorRemocao;
            scanf("%d", &valorRemocao);
            raiz = remover(raiz, valorRemocao);
            break;

        case 4:
            printf("Em qual ordem deseja mostrar a árvore\n");
            printf("1. Pré-ordem\n");
            printf("2. Em ordem\n");
            printf("3. Pós-ordem\n");
            int escolha;
            scanf("%d", &escolha);
            switch (escolha)
            {
            case 1:
                imprimirPreOrdem(raiz);
                break;
            case 2:
                imprimirEmOrdem(raiz);
                break;
            case 3:
                imprimirPosOrdem(raiz);
                break;
            }
            printf("\n");
            break;

            case 0: 
            liberarArvore(raiz);
            return NULL;
        }
    } while (resposta != 0);

    return raiz;
}

int main()
{
    Node *raiz = NULL;

    raiz = uiUsuario(raiz);

    return 0;
}