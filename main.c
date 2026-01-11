#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ALFABETO_SIZE 26

typedef struct NoTrie{
    struct NoTrie *proximo[ALFABETO_SIZE];
    bool FimPalavra;
}NoTrie;


NoTrie* CriarNo(){
    NoTrie *NovoNo = (NoTrie *)malloc(sizeof(NoTrie));
    return NovoNo;
}



int main(){
    NoTrie *raiz = CriarNo();
    int i=10;
    char letra='a';
    printf("%c",i+letra);//base pra achar as letras
    return 0;
}