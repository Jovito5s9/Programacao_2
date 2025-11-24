#include <stdio.h>
#include <stdlib.h>

typedef struct no_base{
	struct no_base *anterior;
	struct no_base *proximo;
	int valor;
	} no_base;

void adicionar_no(no_base **cabeca, int valor){
	no_base *novo_no = malloc(sizeof(no_base));
	novo_no->valor=valor;
	no_base *cabeca_antiga=cabeca;
	cabeca=&novo_no;
	novo_no->proximo=cabeca_antiga;
}

int main() {
    
    return 0;
}
