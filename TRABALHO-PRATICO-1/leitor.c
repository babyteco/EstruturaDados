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
#include "listaLeitores.h"


typedef struct leitor{
    char nome[MAX_TAM_STRING];
    char **generos;
    int numAfinidades;
    int id;
    ListaLivros *lidos;
    ListaLivros *desejados;
    ListaRecomendacoes *recomendacoes;
    ListaLeitores *afinidades;
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
    l->afinidades = criaListaLeitores();


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

void adicionaLivroLido(Leitor *leitor, Livro *livro){
    if (buscaLivro(leitor->lidos, getIdLivro(livro)) == NULL){
        leitor->lidos = adicionaLivro(leitor->lidos, livro);
        printf("%s leu ""%s""\n", leitor->nome, getTituloLivro(livro));
    }
}

void adicionaLivroDesejado(Leitor *leitor, Livro *livro){
    if (buscaLivro(leitor->lidos, getIdLivro(livro)) == NULL){
        leitor->desejados = adicionaLivro(leitor->desejados, livro);
        printf("%s deseja ler ""%s""\n", leitor->nome, getTituloLivro(livro));
    }
}

void adicionaRecomendacaoDada(Leitor *leitor, Livro *livro){
    if (buscaLivro(leitor->lidos, getIdLivro(livro)) == NULL){
        leitor->recomendacoes = adicionaRecomendacaoLista(leitor->recomendacoes, leitor, livro);
        printf("recomenda ""%s"" para %s\n", getTituloLivro(livro), leitor->nome);
    }
}

void aceitaRecomendacao(ListaLeitores *ll, int idDestinatario, int idLivro, int idRemetente){
    Leitor *leitor = buscaLeitor(ll, idDestinatario);
    Leitor *remetente = buscaLeitor(ll, idRemetente);
    Livro *livro = retiraRecomendacao(leitor->recomendacoes, idLivro, idRemetente);
    //adiciona livro em desejados apenas se ele ja nao estava la
    if (buscaLivro(leitor->desejados, idLivro) == NULL){
        adicionaLivroDesejado(leitor, livro);
        printf("%s aceita recomendação ""%s"" de %s\n", leitor->nome, getTituloLivro(livro), remetente->nome);
    }
}

void rejeitaRecomendacao(ListaLeitores *ll, int idDestinatario, int idLivro, int idRemetente){
    Leitor *remetente = buscaLeitor(ll, idRemetente);
    Leitor *leitor = buscaLeitor(ll, idDestinatario);
    Livro *livro = retiraRecomendacao(leitor->recomendacoes, idLivro, idRemetente);    
    printf("%s rejeita recomendação ""%s"" de %s\n", leitor->nome, getTituloLivro(livro), remetente->nome);

}

ListaLivros *getListaLidosDeUmLeitor(Leitor *l){
    return l->lidos;
}

ListaLivros *getListaDesejadosDeUmLeitor(Leitor *l){
    return l->desejados;
}

ListaRecomendacoes *getListaRecomendacoesDeUmLeitor(Leitor *l){
    return l->recomendacoes;
}

char **getListaGeneros(Leitor *l){
    return l->generos;
}

int getNumGeneros(Leitor *l){
    return l->numAfinidades;
}

ListaLeitores *getListaAfinidade(Leitor *l){
    return l->afinidades;
}

void adicionaNaListaSeTiverAfinidade(Leitor *leitorPrincipal, Leitor *candidato){    
    if (verificaSeTemComum(leitorPrincipal, candidato)){
        leitorPrincipal->afinidades = adicionaLeitor(leitorPrincipal->afinidades, candidato);
    }
}

void imprimeListaLidos(Leitor *l){
    imprimeLivrosLidos(l->lidos);
}

void imprimeListaDesejados(Leitor *l){
    imprimeLivrosLidos(l->desejados);
}