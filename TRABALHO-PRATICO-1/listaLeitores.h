//
//  ListaLeitores.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef LISTA_LEITORES_H 
#define LISTA_LEITORES_H
#include <stdio.h>
typedef struct leitor Leitor;

typedef struct listaLeitores ListaLeitores;

ListaLeitores *criaListaLeitores();

ListaLeitores *adicionaLeitor(ListaLeitores *ll, Leitor *leitor);

void liberaListaLeitores(ListaLeitores *ll);

void retiraLeitor(ListaLeitores *ll, int id);

Leitor *buscaLeitor(ListaLeitores *ll, int id);

int verificaSeTemComum(Leitor *l1, Leitor *l2);

void preencheListaAfinidadesDiretas(ListaLeitores *l);

int verificaSeTemAfinidade(ListaLeitores *ll, int id1, int id2);

void imprimeLeitores(ListaLeitores *ll);

#endif