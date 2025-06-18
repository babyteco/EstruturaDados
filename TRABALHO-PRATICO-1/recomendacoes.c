//
//  recomendacoes.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "leitor.h"
#include "livro.h"

typedef struct celula Celula;

typedef struct listaListaRecomendacoes{
    Celula *primeiro;
    Celula *ultimo;
} ListaRecomendacoes;

struct celula{
    Leitor *remetente;
    Livro *sugerido;
    Celula *prox;
    Celula *ant;
};

ListaRecomendacoes *criaListaRecomendacoes(){
    ListaRecomendacoes *lr = (ListaRecomendacoes*) malloc(sizeof(ListaRecomendacoes));
    lr->primeiro = NULL;
    lr->ultimo = NULL;
    return lr;
}

ListaRecomendacoes *adicionaRecomendacaoLista(ListaRecomendacoes *lr, Leitor *Leitor, Livro *livro){
    Celula *cel = (Celula*) malloc(sizeof(Celula));
    cel->remetente = Leitor;
    cel->sugerido = livro;

    if (!(lr->primeiro)){
        lr->primeiro = cel;
        lr->ultimo = cel;
        lr->primeiro->prox = NULL;
        lr->primeiro->ant = NULL;
        return lr;
    }
    
    Celula *antigoUltimo = lr->ultimo;
    lr->ultimo->prox = cel;
    lr->ultimo = cel;
    lr->ultimo->prox = NULL;
    lr->ultimo->ant = antigoUltimo;

    return lr;
}

void liberaListaRecomendacoes(ListaRecomendacoes *lr){
    Celula *paliativa = lr->primeiro;
    for (int i = 0; paliativa!= NULL; i++){
        Celula *temp = paliativa;
        paliativa = paliativa->prox;
        free(temp);
    }
    free(lr);
}

Livro *retiraRecomendacao(ListaRecomendacoes *lr, int idLivro, int idRemetente){
    Celula *nova = lr->primeiro;

    for (int i = 0; nova != NULL; i++){
        if (getIdLivro(nova->sugerido) == idLivro && getIdLeitor(nova->remetente) == idRemetente){
            if (lr->primeiro == lr->ultimo){
                lr->primeiro = NULL;
                lr->ultimo = NULL;
                return nova->sugerido;
            }
            
            if (nova == lr->primeiro){
                Celula *cel = lr->primeiro->prox;
                lr->primeiro = cel;
                cel->ant = NULL;
                return nova->sugerido;
            }

            if (nova == lr->ultimo){
                Celula *cel = lr->ultimo->ant;
                lr->ultimo = cel;
                cel->prox = NULL;
                return nova->sugerido;
            }
            
            Celula *celAnt = nova->ant;
            Celula *celPos = nova->prox;
            celAnt->prox = celPos;
            celPos->ant = celAnt;
            return nova->sugerido;
        }
        nova = nova->prox;
    }

    return NULL;
}

Leitor *buscaRecomendacao(ListaRecomendacoes *lr, int idLivro, int idRemetente){
    Celula *nova = lr->primeiro;
    while (nova != NULL){
        if (getIdLivro(nova->sugerido) == idLivro && getIdLeitor(nova->remetente) == idRemetente){
            return nova;
        }
        nova = nova->prox;
    }
}
