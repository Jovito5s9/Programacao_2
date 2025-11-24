#include <stdio.h>
#include <stdlib.h>

typedef struct no_base{
	struct no_base *anterior;
	struct no_base *proximo;
	int valor;
	} no_base;

void add_no(no_base **cabeca, int valor){
	no_base *novo_no = malloc(sizeof(no_base));
	novo_no->valor=valor;
	no_base **cabeca_antiga=cabeca;
	*cabeca=novo_no;
	novo_no->proximo=*cabeca_antiga;
}

void print_list(no_base *cabeca){
	no_base *no_atual=cabeca;
	
	while (no_atual!=NULL){
		printf("%d",no_atual->valor);
		no_atual=no_atual->proximo;
	}
}

int main() {
    no_base *cabeca=NULL;
    print_list(cabeca);
    add_no(&cabeca,10);
    print_list(cabeca);
    return 0;
}
