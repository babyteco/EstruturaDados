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
        if ((getIdLivro(nova->sugerido) == idLivro) && (getIdLeitor(nova->remetente) == idRemetente)){
            if (lr->primeiro == lr->ultimo){
                lr->primeiro = NULL;
                lr->ultimo = NULL;
                Livro *livroRecomendado = nova->sugerido;
                free(nova);
                return livroRecomendado;
            }
            
            if (nova == lr->primeiro){
                Celula *cel = lr->primeiro->prox;
                lr->primeiro = cel;
                if (cel != NULL) {
                    cel->ant = NULL;
                } else {
                    // Se não há próximo elemento, a lista fica vazia
                    lr->ultimo = NULL;
                }
                Livro *livroRecomendado = nova->sugerido;
                free(nova);
                return livroRecomendado;
            }

            if (nova == lr->ultimo){
                Celula *cel = lr->ultimo->ant;
                lr->ultimo = cel;
                if (cel != NULL) {
                    cel->prox = NULL;
                } else {
                    // Se não há elemento anterior, a lista fica vazia
                    lr->primeiro = NULL;
                }
                Livro *livroRecomendado = nova->sugerido;
                free(nova);
                return livroRecomendado;
            }
            
            Celula *celAnt = nova->ant;
            Celula *celPos = nova->prox;
            celAnt->prox = celPos;
            celPos->ant = celAnt;
            Livro *livroRecomendado = nova->sugerido;
            free(nova);
            return livroRecomendado;
        }
        nova = nova->prox;
    }
    return NULL;
}

Leitor *buscaRecomendacao(ListaRecomendacoes *lr, int idLivro, int idRemetente){
    Celula *nova = lr->primeiro;
    while (nova != NULL){
        if (getIdLivro(nova->sugerido) == idLivro && getIdLeitor(nova->remetente) == idRemetente){
            return nova->remetente;
        }
        nova = nova->prox;
    }
    return NULL;
}

void imprimeListaRecomendacoes(Leitor *l, FILE *saida){
    ListaRecomendacoes *recomendados = getListaRecomendacoesDeUmLeitor(l);
    Celula *temp = recomendados->primeiro;
    
    if (recomendados == NULL){
        printf("Lista de livros vazia\n");
        return;
    }

    while (temp != NULL){
        if(temp->prox == NULL){
            fprintf(saida, "%s\n", getTituloLivro(temp->sugerido));
        } else{
            fprintf(saida, "%s, ", getTituloLivro(temp->sugerido));
        }
        temp = temp->prox;
    }
    printf("\n");  
}