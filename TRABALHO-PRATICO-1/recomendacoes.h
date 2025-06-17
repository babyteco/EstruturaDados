//
//  recomendacoes.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef ListaRecomendacoes_h
#define ListaRecomendacoes_h
#include <stdio.h>
#include "leitor.h"
#include "livro.h"

typedef struct celula Celula;

typedef struct listaListaRecomendacoes{
    Celula *primeiro;
    Celula *ultimo;

} ListaRecomendacoes;


ListaRecomendacoes *criaListaRecomendacoes();

ListaRecomendacoes *adicionaLeitor(ListaRecomendacoes *ll, Leitor *Leitor);

void liberaListaRecomendacoes(ListaRecomendacoes *ll);

void retiraLeitor(ListaRecomendacoes *ll, int id);

Leitor *buscaLeitor(ListaRecomendacoes *ll, Leitor *l, int id);

#endif