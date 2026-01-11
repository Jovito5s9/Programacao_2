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
    for(int i=0;i< ALFABETO_SIZE;i++){
        NovoNo->proximo[i]=NULL;
    }
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

int LetraPraNum(char letra){
    if (isalpha(letra)) {
        return(int)(letra-'a');
    }
    return 26;
}

NoTrie* inserir(char* palavra, NoTrie* raiz){
    if (raiz == NULL) {
        raiz = CriarNo();
    }

    palavra=lower(palavra);
    NoTrie *trie=raiz;

    for(int i=0;palavra[i] != '\0';i++){
        char letra=palavra[i];
        int numero=LetraPraNum(letra);
        if(numero==26){
            continue;
        }
        if(trie->proximo[numero]==NULL){
            trie->proximo[numero]=CriarNo();
        }
        trie=trie->proximo[numero];
    }

    free(palavra);
    trie->FimPalavra=true;

    return raiz;
}

void SugerirPalavra(NoTrie* atual, char* prefixo_atual, int nivel){
    if(atual->FimPalavra){
        prefixo_atual[nivel] = '\0';
        printf("sugestão: %s\n",prefixo_atual);
    }

    for(int i=0; i<ALFABETO_SIZE;i++){
        if(atual->proximo[i]!=NULL){
            prefixo_atual[nivel] = i + 'a';
            SugerirPalavra(atual->proximo[i], prefixo_atual, nivel + 1);
        }
    }
}

int main(){
    NoTrie *raiz = CriarNo();
    int i=10;
    char letra='a';
    printf("%c",i+letra);//base pra achar as letras
    char *palavra = lower("TESTANDO ISSO");
    printf("%s", palavra);
    printf("%d", LetraPraNum('j'));
    free(palavra);
    return 0;
}