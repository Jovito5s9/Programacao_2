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
    NovoNo->FimPalavra=false;
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

bool BuscarPrimeiraSugestao(NoTrie* atual, char* buffer, int nivel) {
    if (atual->FimPalavra) {
        buffer[nivel] = '\0';
        return true; 
    }
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (atual->proximo[i] != NULL) {
            buffer[nivel] = i + 'a';
            if (BuscarPrimeiraSugestao(atual->proximo[i], buffer, nivel + 1)) {
                return true;
            }
        }
    }

    return false;
}

void SugerirPalavra(NoTrie* raiz, char* prefixo) {
    NoTrie* atual = raiz;
    char buffer[100];
    int i;
    for (i = 0; prefixo[i] != '\0'; i++) {
        int indice = LetraPraNum(prefixo[i]);
        if (indice == 26 || atual->proximo[indice] == NULL) {
            return;
        }
        buffer[i] = prefixo[i];
        atual = atual->proximo[indice];
    }
    if (BuscarPrimeiraSugestao(atual, buffer, i)) {
        printf("%s", buffer);
    }
}

int main() {
    NoTrie *raiz = CriarNo();
    inserir("palavra", raiz);
    inserir("para", raiz);
    inserir("par", raiz);
    inserir("pa", raiz);
    printf("palavra sugerida: ");
    SugerirPalavra(raiz, "pala"); 
    
    printf("\n");
    return 0;
}