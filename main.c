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

void BuscarPrimeiraSugestao(NoTrie* atual, char* buffer, int nivel) {
    if (atual->FimPalavra) {
        buffer[nivel] = '\0';
        printf("- %s\n", buffer);
    }
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (atual->proximo[i] != NULL) {
            buffer[nivel] = i + 'a';
            BuscarPrimeiraSugestao(atual->proximo[i], buffer, nivel + 1);
        }
    }
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
    BuscarPrimeiraSugestao(atual, buffer, i);
}

bool temFilhos(NoTrie* no) {
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (no->proximo[i] != NULL){
            return true;
        }
    }
    return false;
}

NoTrie* remover(NoTrie* raiz, char* palavra, int nivel) {
    if (raiz == NULL) return NULL;

    if (palavra[nivel] == '\0') {
        if (raiz->FimPalavra) raiz->FimPalavra = false;
        if (!temFilhos(raiz)) {
            free(raiz);
            raiz = NULL;
        }
        return raiz;
    }

    int indice = LetraPraNum(palavra[nivel]);
    if (indice != 26) {//recursao
        raiz->proximo[indice] = remover(raiz->proximo[indice], palavra, nivel + 1);
    }

    if (!temFilhos(raiz) && !raiz->FimPalavra) {
        free(raiz);
        raiz = NULL;
    }

    return raiz;
}


int main() {
    NoTrie *raiz = CriarNo();
    int opc = -1;
    char buffer[100];

    while (opc != 0) {
        printf("\n--- MENU TRIE ---\n");
        printf("1 - inserir palavra\n");
        printf("2 - sugerir palavra (auto-completar)\n");
        printf("3 - remover palavra\n");
        printf("0 - sair\n");
        printf("escolha: ");
        
        if (scanf("%d", &opc) != 1) {
            printf("entrada invalida\n");
            while(getchar() != '\n');
            continue;
        }
        switch (opc) {
            case 1:
                printf("digite a palavra para inserir: ");
                scanf("%s", buffer);
                inserir(buffer, raiz);
                printf("palavra '%s' inserida com sucesso.\n", buffer);
                break;
            case 2:
                printf("digite o prefixo: ");
                scanf("%s", buffer);
                printf("sugestao encontrada: ");
                SugerirPalavra(raiz, buffer); 
                printf("\n");
                break;
            case 3:
                printf("digite a palavra para remover: ");
                scanf("%s", buffer);
                char* palavra_limpa = lower(buffer);
                raiz = remover(raiz, palavra_limpa, 0);
                free(palavra_limpa);
                printf("operacao de remocao concluida.\n");

                if (raiz == NULL) {
                    raiz = CriarNo();
                }
                break;
            case 0:
                printf("saindo\n");
                break;
            default:
                printf("opcao invalida\n");
                break;
        }
    }
    return 0;
}