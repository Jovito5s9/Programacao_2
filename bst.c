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
    //buscar o valor
    if (raiz == NULL)
    {
        return NULL;
    }

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
    // remoção de nó com 2 filhos
    else
    {
        Node *temp = raiz->dir;
        while (temp->esq != NULL)
        {
            temp = raiz->esq;
        }

        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
        return raiz;
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

void uiUsuario(raiz)
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
            inserir(raiz, valor);
            break;

        case 2:
            // buscarValor()
            break;

        case 3:
            printf("Qual dos valores deseja remover?");
            imprimirEmOrdem(raiz);
            int valor;
            scanf("%d", &valor);
            remover(raiz, valor);
            break;

        case 4:
            printf("Em qual ordem deseja mostrar a árvore");
            printf("1. Pré-ordem");
            printf("2. Em ordem");
            printf("3. Pós-ordem");
            int escolha;
            scanf("%d", &escolha);
            switch (escolha)
            {
            case 1:

                break;

            case 2:

                break;

            case 3:
                imprimirEmOrdem(raiz);
                break;
            }
        }
    } while (resposta != 0);

    raiz = inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 60);
    inserir(raiz, 20);
    inserir(raiz, 40);
    inserir(raiz, 90);

    remover(raiz, 50);

    imprimirEmOrdem(raiz);
    printf("\n");
}

int main()
{
    Node *raiz = NULL;

    int resposta;

    return 0;
}