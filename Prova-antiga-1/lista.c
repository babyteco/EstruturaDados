#include<stdio.h>
#include<stdlib.h>

#define GATO 0
#define CACHORRO 1

struct lista{
    Celula *primeiro;
    Celula *ultimo;
};

typedef struct celula{
    Celula *prox;
    Celula *ant;
    Cachorro *dog;
    Gato *cat;
} Celula;

Lista *CriaLista(){
    Lista *l = (Lista*) malloc(sizeof(Lista));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}

