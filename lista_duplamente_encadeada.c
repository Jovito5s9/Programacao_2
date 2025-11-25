#include <stdio.h>
#include <stdlib.h>

typedef struct no_base{
	struct no_base *anterior;
	struct no_base *proximo;
	int valor;
	} no_base;


void add_no_cabeca(no_base **cabeca, int valor){
	no_base *cabeca_antiga=*cabeca;
	no_base *novo_no = malloc(sizeof(no_base));
	novo_no->valor=valor;
	novo_no->proximo=cabeca_antiga;
	novo_no->anterior=NULL;
	*cabeca=novo_no;
	printf("\nnovo nó criado com valor: [%d]\n",valor);
}


void add_no_cauda(no_base **cabeca, int valor){
    no_base *novo = malloc(sizeof(no_base));
    novo->valor = valor;
    novo->proximo = NULL;
    if (*cabeca == NULL) {
        novo->anterior = NULL;
        *cabeca = novo;
        printf("\nnovo nó criado com valor: [%d]\n", valor);
        return;
    }
    no_base *ultimo = *cabeca;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = novo;
    novo->anterior = ultimo;

    printf("\nnovo nó criado com valor: [%d]\n", valor);
}


void buscar(no_base *cabeca,int indice){
	if (cabeca==NULL){
		printf("A lista está vazia, não há nenhum elemento para buscar nela");
		return;
	}
	no_base *no_atual=cabeca;
	for (int i = 1; i < indice; i++) {
	    if (no_atual->proximo == NULL) {
	        printf("\na lista não possui o indice %d para buscar\n", indice);
	        return;
	    }
	    no_atual = no_atual->proximo;
	}
	printf("\nvalor no indice %d: %d\n",indice, no_atual->valor);
}


void remover_indice(no_base **cabeca, int indice){
    if (*cabeca == NULL){
        printf("\nA lista está vazia, não há nenhum elemento para remover nela\n");
        return;
    }

    no_base *no_removido = *cabeca;

    // Caso especial: remover o primeiro nó
    if (indice == 1){
        *cabeca = no_removido->proximo;
        if (*cabeca != NULL)
            (*cabeca)->anterior = NULL;
        printf("\nvalor %d no indice 1 foi removido\n", no_removido->valor);
        free(no_removido);
        return;
    }
    for (int i = 1; i < indice; i++) {
        if (no_removido->proximo == NULL) {
            printf("\na lista não possui o indice %d para remover\n", indice);
            return;
        }
        no_removido = no_removido->proximo;
    }
    printf("\nvalor %d no indice %d foi removido\n", no_removido->valor, indice);
	no_base *anterior=no_removido->anterior;
	no_base *proximo=no_removido->proximo;
    if (anterior != NULL){
        anterior->proximo = proximo;
    }
    if (proximo != NULL){
        proximo->anterior = anterior;
    }

    free(no_removido);
    no_removido=NULL;
}


void print_list(no_base *cabeca){
	no_base *no_atual=cabeca;
	printf("\nLista atual:\nNULL <-");
	while (no_atual !=NULL){
		printf("-> [%d] <-",no_atual->valor);
		no_atual=no_atual->proximo;
	}
	printf("-> NULL\n");
}


int main() {
    no_base *cabeca=NULL;
    buscar(cabeca, 1);
    print_list(cabeca);
    add_no_cabeca(&cabeca,10);
    add_no_cabeca(&cabeca,11);
    add_no_cabeca(&cabeca,3);
    add_no_cauda(&cabeca,20);
    buscar(cabeca,4);
    remover_indice(&cabeca,2);
    print_list(cabeca);
    return 0;
}
