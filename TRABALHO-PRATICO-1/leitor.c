//
//  leitor.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "leitor.h"
#include "listaLivros.h"
#include "recomendacoes.h"


typedef struct leitor{
    char nome[MAX_TAM_STRING];
    char **generos;
    int numAfinidades;
    int id;
    ListaLivros *lidos;
    ListaLivros *desejados;
    ListaRecomendacoes *recomendacoes;
} Leitor;

Leitor *criaLeitor(char nome, char **generos, int id, int numAfinidades){
    Leitor *l = (Leitor*) malloc(sizeof(Leitor*));
    strcpy(l->nome, nome);
    l->id = id;
    l->numAfinidades = numAfinidades;

    l->generos = (char**) malloc(numAfinidades * sizeof(char*));
    for (int i = 0; i < numAfinidades; i++){
        l->generos[i] = (char*) malloc(MAX_TAM_STRING * sizeof(char));
    }
    
    l->lidos = criaListaLivros();
    l->desejados = criaListaLivros();
    l->recomendacoes = criaListaRecomendacoes();

    return l;
}

void liberaLeitor(Leitor *l){
    for (int i = 0; i < l->numAfinidades; i++){
        free(l->generos[i]);
    }
    free(l->generos);
    liberaListaLivros(l->lidos);
    liberaListaLivros(l->desejados);
    liberaListaRecomendacoes(l->recomendacoes);
    free(l);
}

int getIdLeitor(Leitor *l){
    return l->id;
}

char *getNomeLeitor(Leitor *l){
    return l->nome;
}

void *adicionaLivroLido(Leitor *leitor, Livro *livro){
    leitor->lidos = adicionaLivro(leitor->lidos, livro);
}

void *adicionaLivroDesejado(Leitor *leitor, Livro *livro){
    leitor->desejados = adicionaLivro(leitor->desejados, livro);
}

void *adicionaRecomendacaoDada(Leitor *leitor, Livro *livro){
    leitor->recomendacoes = adicionaRecomendacaoLista();
}
