#include "fila.h"
#include "amostra.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct celula Celula;

struct celula{
    Amostra *a;
    Celula *prox;
    Celula *ant;
};


struct fila{
    Celula *primeiro;
    Celula *ultimo;
};

Fila *criaFila(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->primeiro = NULL;
    f->ultimo = NULL;
    return f;
}

void insereAmostra(Amostra *a, Fila *f){
    Celula *amostra = (Celula*) malloc(sizeof(Amostra));
    amostra->a = a;
    
    //se a lista estiver vazia
    if(f->primeiro == NULL){
        f->primeiro = amostra;
        f->ultimo = amostra;
        amostra->prox = NULL;
        amostra->ant = NULL
        return;
    }
    
    //se nao for idoso
    if(retornaIdade(a) < 60){    
        f->ultimo->prox = amostra;
        amostra->ant = f->ultimo;
        f->ultimo = amostra;
        amostra->prox = NULL;
        return;
    }

    else if(retornaIdade(a) >= 60){ 
        f->primeiro->ant = amostra;
        amostra->prox = f->primeiro;
        amostra->ant = NULL; 
        f->primeiro = amostra;
        return;
    }
}

Amostra *removeAmostra(fila *f){
    if(f->primeiro == NULL){
        printf("a lista esta vazia nao e possivel remover\n");
        return NULL;
    }

    if(f->primeiro == f->ultimo){
        Celula *amostra = f->primeiro;
        f->
    }
    
    Celula *prox = f->primeiro->prox;
    Celula *prim = f->primeiro;
    prox->ant = NULL
    fila->primeiro = prox;
    

}