#include <stdio.h>
#include <stdbool.h>

#define ALFABETO_SIZE 26

typedef struct NoTrie{
    struct NoTrie *proximo[ALFABETO_SIZE];
    bool FimPalavra;
}NoTrie;

int main(){
    return 0;
}