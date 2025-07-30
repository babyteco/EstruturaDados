#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>

typedef struct no No;

typedef struct raiz Raiz;

Raiz* criaArvore(int (*comp)(void*, void*), void (*imprime)(void*, FILE*), void (*libera)(void*));

void insere(Raiz *r, void* dado);

void liberaArvore(Raiz *r);

void imprimeArvore(Raiz *a, FILE *arq);

#endif
