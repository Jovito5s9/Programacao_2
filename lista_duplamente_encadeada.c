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
    if (cabeca_antiga != NULL) {
        cabeca_antiga->anterior = novo_no;
    }
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


void add_no_meio(no_base **cabeca, int valor, int indice){
	no_base *novo = malloc(sizeof(no_base));
    novo->valor = valor;
    novo->proximo = NULL;
    if (*cabeca == NULL) {
        novo->anterior = NULL;
        *cabeca = novo;
        printf("\nnovo nó criado com valor: [%d]\n", valor);
        return;
    }
    no_base *alvo = *cabeca;
    for (int i = 1; i < indice-1; i++) {
	    if (alvo->proximo == NULL) {
	        printf("\na lista não possui o indice %d a inserção será tranferida para o indice %d\n", indice,i+1);
	        break;
	    }
	    alvo = alvo->proximo;
    }
    novo->proximo = alvo->proximo;
    alvo->proximo = novo;
    novo->anterior = alvo;
    if (novo->proximo != NULL) {
        novo->proximo->anterior = novo;
    }
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
    
    no_base *no_atual = *cabeca;
    int i;
    for (i = 1; no_atual != NULL && i < indice; i++) {
        no_atual = no_atual->proximo;
    }
    if (no_atual == NULL) {
        printf("\na lista não possui o indice %d para remover\n", indice);
        return;
    }
    printf("\nvalor %d no indice %d foi removido\n", no_atual->valor, indice);
    if (no_atual->anterior != NULL) {
        no_atual->anterior->proximo = no_atual->proximo;
    } else {
        *cabeca = no_atual->proximo;
    }
    if (no_atual->proximo != NULL) {
        no_atual->proximo->anterior = no_atual->anterior;
    }
    free(no_atual);
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


int teste(no_base *cabeca) {
    buscar(cabeca, 1);
    print_list(cabeca);
    add_no_cabeca(&cabeca,10);
    add_no_cabeca(&cabeca,11);
    add_no_cabeca(&cabeca,3);
    add_no_cauda(&cabeca,20);
    buscar(cabeca,4);
    remover_indice(&cabeca,2);
    add_no_meio(&cabeca,33,7);
    print_list(cabeca);
    return 0;
}


void interacao_usuario(no_base **cabeca){
	printf("\nQual operação com listas você deseja operar?\n");
	printf("1 - inserção de valores no inicio.\n");
	printf("2 - inserção de valores no final.\n");
	printf("3 - inserção de valores em um indice a escolha.\n");
	printf("4 - remover valores.\n");
	printf("5 - buscar.\n");
	printf("6 - listagem dos valores da lista.\n");
	int resposta, valor, indice;
	scanf("%d",&resposta);
	switch(resposta) {
        case 1:
            printf("Valor: ");
            scanf("%d", &valor);
            add_no_cabeca(cabeca, valor);
            break;
        case 2:
            printf("Valor: ");
            scanf("%d", &valor);
            add_no_cauda(cabeca, valor);
            break;
        case 3:
            printf("Valor: ");
            scanf("%d", &valor);
            printf("Indice ");
            scanf("%d", &indice);
            add_no_meio(cabeca, valor, indice);
            break;
        case 4:
            printf("Índice: ");
            scanf("%d", &indice);
            remover_indice(cabeca, indice);
            break;
        case 5:
            printf("Índice: ");
            scanf("%d", &indice);
            buscar(*cabeca, indice);
            break;
        case 6:
        	print_list(*cabeca);
        	break;
	}
}


int main(){
	no_base *cabeca=NULL;
	teste(cabeca);
	while (1){
		interacao_usuario(&cabeca);
		}
	return 0;
}
