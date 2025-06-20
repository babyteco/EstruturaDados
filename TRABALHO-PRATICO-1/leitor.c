//
//  leitor.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Leitor *criaLeitor(char *nome, char **generos, int id, int numAfinidades){
    Leitor *l = (Leitor*) malloc(sizeof(Leitor));
    strcpy(l->nome, nome);
    l->id = id;
    l->numAfinidades = numAfinidades;

    l->generos = (char**) malloc(numAfinidades * sizeof(char*));
    for (int i = 0; i < numAfinidades; i++){
        l->generos[i] = (char*) malloc(MAX_TAM_STRING * sizeof(char));
        strcpy(l->generos[i], generos[i]);
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

void adicionaLivroLido(Leitor *leitor, Livro *livro, FILE *saida){
    if (buscaLivro(leitor->lidos, getIdLivro(livro)) == NULL){
        leitor->lidos = adicionaLivro(leitor->lidos, livro);
        fprintf(saida, "%s leu \"%s\"\n", leitor->nome, getTituloLivro(livro));
    }
}

void adicionaLivroDesejado(Leitor *leitor, Livro *livro, FILE *saida){
    if (buscaLivro(leitor->lidos, getIdLivro(livro)) == NULL){
        leitor->desejados = adicionaLivro(leitor->desejados, livro);
        fprintf(saida, "%s deseja ler \"%s\"\n", leitor->nome, getTituloLivro(livro));
    }
}

void adicionaLivroDesejadoPorRecomendacao(Leitor *leitor, Livro *livro, int idRemetente){
    // Verificar se leitor e livro existem
    if (leitor == NULL || livro == NULL){
        printf("Erro: Leitor ou livro não encontrado\n");
        return;
    }
    
    if (buscaRecomendacao(leitor->recomendacoes, getIdLivro(livro), idRemetente) == NULL){
        leitor->desejados = adicionaLivro(leitor->desejados, livro);
    }
    // printf("%s deseja ler \"%s\"\n", leitor->nome, getTituloLivro(livro));
}

void adicionaRecomendacaoDada(Leitor *destinatario, Livro *livro, Leitor *remetente, FILE *saida){
    // Verificar se leitor e livro existem
    if (destinatario == NULL || livro == NULL){
        printf("Erro: Leitor ou livro não encontrado para adicionar recomendacao\n");
        return;
    }
    
    // Livro *livroExistenteNaLista = buscaLivro(leitor->lidos, getIdLivro(livro));
    // imprimeLivro(livro);
    if (buscaRecomendacao(destinatario->recomendacoes, getIdLivro(livro), getIdLeitor(remetente)) == NULL){
        destinatario->recomendacoes = adicionaRecomendacaoLista(destinatario->recomendacoes, remetente, livro);
        fprintf(saida, "recomenda \"%s\" para %s\n", getTituloLivro(livro), destinatario->nome);
    }
}

void aceitaRecomendacao(ListaLeitores *ll, int idDestinatario, int idLivro, int idRemetente, FILE *saida){
    Leitor *leitor = buscaLeitor(ll, idDestinatario);
    Leitor *remetente = buscaLeitor(ll, idRemetente);
    
    // Verificar se leitor e remetente existem
    if (leitor == NULL || remetente == NULL){
        printf("Erro: Leitor ou remetente não encontrado\n");
        return;
    }
    
    Livro *livro = retiraRecomendacao(leitor->recomendacoes, idLivro, idRemetente);
    
    // Verificar se a recomendação foi encontrada
    if (livro == NULL){
        printf("Erro: Nao foi possivel aceitar a recomendacao pois ela nao esta na lista\n");
        return;
    }
    
    //adiciona livro em desejados apenas se ele ja nao estava la
    if (buscaLivro(leitor->desejados, idLivro) == NULL){
        adicionaLivroDesejadoPorRecomendacao(leitor, livro, getIdLeitor(remetente));
        fprintf(saida, "%s aceita recomendação \"%s\" de %s\n", leitor->nome, getTituloLivro(livro), remetente->nome);
    }
}

void rejeitaRecomendacao(ListaLeitores *ll, int idDestinatario, int idLivro, int idRemetente, FILE *saida){
    Leitor *remetente = buscaLeitor(ll, idRemetente);
    Leitor *leitor = buscaLeitor(ll, idDestinatario);
    
    // Verificar se leitor e remetente existem
    if (leitor == NULL || remetente == NULL){
        printf("Erro: Leitor ou remetente não encontrado\n");
        return;
    }
    
    Livro *livro = retiraRecomendacao(leitor->recomendacoes, idLivro, idRemetente);
    
    // Verificar se a recomendação foi encontrada
    if (livro == NULL){
        printf("Erro: Recomendação não encontrada\n");
        return;
    }
    
    fprintf(saida, "%s rejeita recomendação \"%s\" de %s\n", leitor->nome, getTituloLivro(livro), remetente->nome);
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

void imprimeLeitor(Leitor *l){
    printf("Nome: %s\n", l->nome);
    printf("Id: %d\n", l->id);
    printf("NumAfiniades: %d\n", l->numAfinidades);
    for (int i = 0; i < l->numAfinidades; i++){
        printf("Afinidade[%d]: %s\n", i, l->generos[i]);
    }
    printf("\n");
}