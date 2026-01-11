#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALFABETO_SIZE 26

typedef struct NoTrie{
    struct NoTrie *proximo[ALFABETO_SIZE];
    bool FimPalavra;
}NoTrie;


NoTrie* CriarNo(){
    NoTrie *NovoNo = (NoTrie *)malloc(sizeof(NoTrie));
    return NovoNo;
}

char* lower(char *palavra){
    int limite = strlen(palavra);
    char *palavra_lower = (char *)malloc((limite +1) * sizeof(char));
    for(int i=0;i<=limite;i++){
        palavra_lower[i] = tolower((unsigned char)palavra[i]);
    }
    return palavra_lower;
}

int main(){
    NoTrie *raiz = CriarNo();
    int i=10;
    char letra='a';
    printf("%c",i+letra);//base pra achar as letras
    char *palavra = lower("TESTANDO ISSO");
    printf("%s", palavra);
    free(palavra);
    return 0;
}