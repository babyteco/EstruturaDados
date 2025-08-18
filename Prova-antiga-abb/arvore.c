#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

struct arvore{
    Arvore *esq;
    Arvore *dir;
    char palavra[100];
    int qtd;
};

Arvore *criaArvore(){
    Arvore *a = (Arvore*) malloc(sizeof(Arvore));
    a->dir = NULL;
    a->esq = NULL;
    a->palavra[0] = "\0";
    a->qtd = 0;
    return a;
}

Arvore *insereNaArvore(Arvore *a, char *palavra){
    if (!a){
        Arvore *nova = criaArvore();
        strcpy(nova->palavra, palavra);
        nova->qtd++;
        return nova;
    }

    int flag = strcmp(a->palavra, palavra);
    if (flag == 0){
        
    } else if (flag < 0){
        a->dir = insereNaArvore(a->dir, palavra);
        return a;
    } else if (flag > 0){
        a->esq = insereNaArvore(a->esq, palavra);
        return a;
    } else if(flag = 0){
        a->qtd++;
        return a;
    }
    
    return a;
}

int contaTotalPalavras(Arvore *a){
    if (a == NULL) return 0;
    
    
    int total = a->qtd;
    total += contaTotalPalavras(a->esq);
    total += contaTotalPalavras(a->dir);

    return total;
}

int contaPalavrasDistintas(Arvore *a){
    if (a == NULL) return 0;
    
    int total = 0;    
    if (a->qtd <= 1) total++;
    total += contaTotalPalavras(a->esq);
    total += contaTotalPalavras(a->dir);

    return total;
}

char *MaiorFrequencia(Arvore *a){

}