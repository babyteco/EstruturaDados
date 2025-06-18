//
//  ListaLeitores.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef ListaLeitores_h
#define ListaLeitores_h
#include <stdio.h>
#include "leitor.h"
#include "Leitor.h"

#define MAX_TAM_STRING 50

typedef struct listaLeitores ListaLeitores;

ListaLeitores *criaListaLeitores();

ListaLeitores *adicionaLeitor(ListaLeitores *ll, Leitor *Leitor);

void liberaListaLeitores(ListaLeitores *ll);

void retiraLeitor(ListaLeitores *ll, int id);

Leitor *buscaLeitor(ListaLeitores *ll, int id);

int verificaSeTemComum(Leitor *l1, Leitor *l2);

void preencheListaAfinidadesDiretas(ListaLeitores *l);

int verificaSeTemAfinidade(ListaLeitores *ll, int id1, int id2);

#endif