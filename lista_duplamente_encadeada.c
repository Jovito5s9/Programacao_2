#include <stdio.h>
#include <stdlib.h>

typedef struct no_base{
	struct no_base *anterior;
	struct no_base *proximo;
	int valor;
	} no_base;

void add_no(no_base **cabeca, int valor){
	no_base **cabeca_antiga=cabeca;
	no_base *novo_no = malloc(sizeof(no_base));
	novo_no->valor=valor;
	novo_no->proximo=*cabeca_antiga;
	novo_no->anterior=NULL;
	*cabeca=novo_no;
}

void print_list(no_base *cabeca){
	no_base *no_atual=cabeca;
	printf("\nNULL");
	while (no_atual!=NULL){
		printf(" <-> [%d] <-> ",no_atual->valor);
		no_atual=no_atual->proximo;
	}
	printf("NULL");
}

int main() {
    no_base *cabeca=NULL;
    print_list(cabeca);
    add_no(&cabeca,10);
    add_no(&cabeca,11);
    print_list(cabeca);
    return 0;
}
