#include <stdio.h>
#include <stdlib.h>

// Definição da Estrutura do Nó
typedef struct no{
    int valor;
    struct no *esquerda, *direito;
    short altura;
} No;

// --- PROTÓTIPOS DAS FUNÇÕES ---
short alturaDoNo(No *no);
short maior(short a, short b);
short fatorDeBalanceamento(No *no);
No* novoNo(int x);
No* rotacaoEsquerda(No *r);
No* rotacaoDireita(No *r);
No* rotacaoDireitaEsquerda(No *r);
No* rotacaoEsquerdaDireita(No *r);
No* balancear(No *raiz);
No* inserir(No *raiz, int x);
No* remover(No *raiz, int chave);
void imprimir(No *raiz, int nivel);
// ------------------------------


// Funções de Altura e Auxiliares

// Função ESSENCIAL: Retorna a altura do nó (ou -1 se o nó for NULL)
short alturaDoNo(No *no) {
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

// Retorna o maior entre dois shorts
short maior(short a, short b) {
    return (a > b) ? a : b;
}

// Calcula o Fator de Balanceamento (FB)
short fatorDeBalanceamento(No *no) {
    if (no)
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direito));
    else
        return 0;
}

// Cria um novo nó
No* novoNo(int x) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo) {
        novo->valor = x;
        novo->esquerda = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    } else
        printf("\nERRO ao alocar nó em novoNO!\n");
    return novo;
}


// Funções de Rotação

No* rotacaoEsquerda(No *r) {
    No *y, *f;

    y = r->direito;
    f = y->esquerda;

    // Realiza a rotação
    y->esquerda = r;
    r->direito = f;

    // Recalcula a altura dos nós
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoDireita(No *r) {
    No *y, *f;

    y = r->esquerda;
    f = y->direito;

    // Realiza a rotação
    y->direito = r;
    r->esquerda = f;

    // Recalcula a altura dos nós
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoDireitaEsquerda(No *r) {
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

No* rotacaoEsquerdaDireita(No *r) {
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}


// Funções de Balanceamento e Operação Principal

No* balancear(No *raiz) {
    short fb = fatorDeBalanceamento(raiz);

    // Rotação Simples à Esquerda (fb < -1 e Ramo Dir. mais pesado ou igual)
    if (fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação Simples à Direita (fb > 1 e Ramo Esq. mais pesado ou igual)
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação Dupla Esquerda-Direita (fb > 1 e Ramo Esq. pende p/ dir.)
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação Dupla Direita-Esquerda (fb < -1 e Ramo Dir. pende p/ esq.)
    else if (fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

No* inserir(No *raiz, int x) {
    if (raiz == NULL)
        return novoNo(x);
    else {
        if (x < raiz->valor)
            raiz->esquerda = inserir(raiz->esquerda, x);
        else if (x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", x);
    }

    // Recalcula a altura e balanceia
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direito)) + 1;
    raiz = balancear(raiz);

    return raiz;
}

No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if (raiz->valor == chave) {
            // Caso 1: Nó folha
            if (raiz->esquerda == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            // Caso 2: Nó com 2 filhos
            else if (raiz->esquerda != NULL && raiz->direito != NULL) {
                No *aux = raiz->esquerda;
                // Busca o antecessor (maior valor na subárvore esquerda)
                while (aux->direito != NULL)
                    aux = aux->direito;
                    
                // Troca o valor do nó a ser removido pelo antecessor
                raiz->valor = aux->valor;
                
                // Remove o nó antecessor que agora tem o valor original
                raiz->esquerda = remover(raiz->esquerda, aux->valor); 
                return raiz;
            }
            // Caso 3: Nó com 1 filho
            else {
                No *aux;
                if (raiz->esquerda != NULL)
                    aux = raiz->esquerda;
                else
                    aux = raiz->direito;
                free(raiz);
                printf("Elemento com 1 filho removido: %d !\n", chave);
                return aux;
            }
        } else {
            // Procura o nó recursivamente
            if (chave < raiz->valor)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }
    }

    // Recalcula a altura e balanceia
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direito)) + 1;
    raiz = balancear(raiz);

    return raiz;
}


// Função de Impressão (Visual)
void imprimir(No *raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        // Imprime o valor, altura e fator de balanceamento para visualização
        printf("%d (h=%d, fb=%d)", raiz->valor, raiz->altura, fatorDeBalanceamento(raiz)); 
        imprimir(raiz->esquerda, nivel + 1);
    }
}


// Função Principal (Menu)
int main() {
    int opcao, valor;
    No *raiz = NULL;

    do {
        printf("\n\n--- MENU AVL ---\n");
        printf("\t0 - Sair\n");
        printf("\t1 - Inserir\n");
        printf("\t2 - Remover\n");
        printf("\t3 - Imprimir Arvore\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo!!!\n");
                break;
            case 1:
                printf("\tDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("\tDigite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
            case 3:
                printf("\n--- ARVORE AVL ---\n");
                imprimir(raiz, 1);
                printf("\n------------------\n");
                break;
            default:
                printf("\nOpcao invalida!!!\n");
        }
    } while (opcao != 0);

    return 0;
}