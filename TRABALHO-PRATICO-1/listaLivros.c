//
//  ListaLivros.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLivros.h"
#include "livro.h"

typedef struct celula Celula;

typedef struct listaLivros{
    Celula *primeiro;
    Celula *ultimo;
} ListaLivros;

struct celula{
    Celula *prox;
    Celula *ant;
    Livro *livro;
};

ListaLivros *criaListaLivros(){
    ListaLivros *ll = (ListaLivros*) malloc(sizeof(ListaLivros));
    ll->primeiro = NULL;
    ll->ultimo = NULL;
    return ll;
}

ListaLivros *adicionaLivro(ListaLivros *ll, Livro *livro){
    Celula *cel = (Celula*) malloc(sizeof(Celula));
    cel->livro = livro;

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

void liberaListaLivros(ListaLivros *ll){
    Celula *paliativa = ll->primeiro;
    for (int i = 0; paliativa!= NULL; i++){
        Celula *temp = paliativa;
        paliativa = paliativa->prox;
        liberaLivro(temp->livro);
        free(temp);
    }
    free(ll);
}

ListaLivros *retiraLivro(ListaLivros *ll, int id){
    Celula *nova = ll->primeiro;

    for (int i = 0; nova != NULL; i++){
        if (getIdLivro(nova->livro) == id){
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

Livro *buscaLivro(ListaLivros *ll, int id){
    Celula *temp = ll->primeiro;
    while (temp->prox != NULL){
        if (id == getIdLivro(temp->livro)){
            return temp->livro;
        }
        temp = temp->prox;
    }
}
