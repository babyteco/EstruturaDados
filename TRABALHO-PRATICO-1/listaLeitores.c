//
//  ListaLeitores.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLivros.h"
#include "livro.h"
#include "leitor.h"

typedef struct celula Celula;

typedef struct listaLeitores{
    Celula *primeiro;
    Celula *ultimo;
} ListaLeitores;

struct celula{
    Celula *prox;
    Celula *ant;
    Leitor *leitor;
};

ListaLeitores *criaListaLeitores(){
    ListaLeitores *ll = (ListaLeitores*) malloc(sizeof(ListaLeitores));
    ll->primeiro = NULL;
    ll->ultimo = NULL;
    return ll;
}

ListaLeitores *adicionaLeitor(ListaLeitores *ll, Leitor *leitor){
    Celula *cel = (Celula*) malloc(sizeof(Celula));
    cel->leitor= leitor;

    if (!(ll->primeiro)){
        ll->primeiro = cel;
        ll->ultimo = cel;
        ll->primeiro->prox = NULL;
        ll->primeiro->ant = NULL;
        return ll;
    }
    
    Celula *antigoUltimo = ll->ultimo;
    ll->ultimo->prox = cel;
    ll->ultimo = cel;
    ll->ultimo->prox = NULL;
    ll->ultimo->ant = antigoUltimo;

    return ll;
}

void liberaListaLeitores(ListaLeitores *ll){
    Celula *paliativa = ll->primeiro;
    for (int i = 0; paliativa!= NULL; i++){
        Celula *temp = paliativa;
        paliativa = paliativa->prox;
        liberaLivro(temp->leitor);
        free(temp);
    }
    free(ll);
}

void retiraLeitor(ListaLeitores *ll, int id){
    Celula *nova = ll->primeiro;

    for (int i = 0; nova != NULL; i++){
        if (getIdLeitor(nova->leitor) == id){
            if (ll->primeiro == ll->ultimo){
                free(ll->primeiro);
                ll->primeiro = NULL;
                ll->ultimo = NULL;
                return ll;
            }
            
            if (nova == ll->primeiro){
                Celula *cel = ll->primeiro->prox;
                free(ll->primeiro);
                ll->primeiro = cel;
                cel->ant = NULL;
                return ll;
            }

            if (nova == ll->ultimo){
                Celula *cel = ll->ultimo->ant;
                free(ll->ultimo);
                ll->ultimo = cel;
                cel->prox = NULL;
                return ll;
            }
            
            Celula *celAnt = nova->ant;
            Celula *celPos = nova->prox;
            free(nova);
            celAnt->prox = celPos;
            celPos->ant = celAnt;
        }
        nova = nova->prox;
    }
    return ll;
}

Leitor *buscaLeitor(ListaLeitores *ll, int id){
    Celula *temp = ll->primeiro;
    while (temp->prox != NULL){
        if (id == getIdLeitor(temp->leitor)){
            return temp->leitor;
        }
        temp = temp->prox;
    }
}