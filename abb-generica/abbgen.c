#include<stdio.h>
#include<stdlib.h>

#include "abbgen.h"

struct no{
    void *dado;
    No *esq;
    No *dir;
};

struct raiz{
    No *raiz;
    int (*comparador)(void*, void*);
    void (*libera)(void*);
    void (*imprime)(void*, FILE*);
};

Raiz* criaArvore(int (*comp)(void*, void*), void (*imprime)(void*, FILE*), void (*libera)(void*)){
    Raiz *r = (Raiz*) malloc(sizeof(Raiz));
    r->raiz = NULL;
    r->comparador = comp;
    r->imprime = imprime;
    r->libera = libera;
    return r;
}

No* helper_insere(No* no, void *dado, int (*comp)(void*, void*)){
    if(no == NULL){
        No *novo = (No*) malloc(sizeof(No));
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    
    int flag = comp(dado, no->dado);

    if (flag < 0){
        no->esq = helper_insere(no->esq, dado, comp);
    } else if(flag > 0){
        no->dir = helper_insere(no->dir, dado, comp);
    }

    return no;
}

void insere(Raiz *r, void* dado){
    if (r == NULL){
        printf("arvore ainda nao inicializada\n");
        return;
    }

    r->raiz = helper_insere(r->raiz, dado, r->comparador);
}

void helper_libera(No *no, void (*libera)(void*)){
    if (no == NULL){
        return;
    }
    
    
    libera(no->dado);
    helper_libera(no->esq, libera);
    helper_libera(no->dir, libera);
    free(no);
}

void liberaArvore(Raiz* r){
    helper_libera(r->raiz, r->libera);
    free(r);
}

void helper_imprime(No *no, void (*imprime)(void*, FILE*), FILE *arq){
    if (no == NULL){
        return;
    }
    
    helper_imprime(no->esq, imprime, arq);
    imprime(no->dado, arq);
    helper_imprime(no->dir, imprime, arq);
}

void imprimeArvore(Raiz *a, FILE *arq){
    if (a == NULL){
        printf("arvore nao incializada, nao ha como imprimir\n");
        return;
    }
    helper_imprime(a->raiz, a->imprime, arq);
}