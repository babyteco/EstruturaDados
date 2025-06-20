//
//  leitor.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef leitor_h
#define leitor_h
#include <stdio.h>
#include "livro.h"
typedef struct listaLivros        ListaLivros;
typedef struct listaLeitores      ListaLeitores;
typedef struct listaListaRecomendacoes  ListaRecomendacoes;

#define MAX_TAM_STRING 50

typedef struct leitor Leitor;

Leitor *criaLeitor(char *nome, char **generos, int id, int numAfinidades);

void liberaLeitor(Leitor *l);

int getIdLeitor(Leitor *l);

char *getNomeLeitor(Leitor *l);

void adicionaLivroLido(Leitor *leitor, Livro *livro);

void adicionaLivroDesejado(Leitor *leitor, Livro *livro);

void adicionaLivroDesejadoPorRecomendacao(Leitor *leitor, Livro *livro, int idRemetente);

void adicionaRecomendacaoDada(Leitor *leitor, Livro *livro);

void aceitaRecomendacao(ListaLeitores *ll, int idDestinatario, int idLivro, int idRemetente);

void rejeitaRecomendacao(ListaLeitores *ll, int idDestinatario, int idLivro, int idRemetente);

ListaLivros *getListaLidosDeUmLeitor(Leitor *l);

ListaLivros *getListaDesejadosDeUmLeitor(Leitor *l);

ListaRecomendacoes *getListaRecomendacoesDeUmLeitor(Leitor *l);

char **getListaGeneros(Leitor *l);

int getNumGeneros(Leitor *l);

void adicionaNaListaSeTiverAfinidade(Leitor *leitorPrincipal, Leitor *candidato);

ListaLeitores *getListaAfinidade(Leitor *l);

void imprimeListaLidos(Leitor *l);

void imprimeListaDesejados(Leitor *l);

void imprimeLeitor(Leitor *l);

#endif
