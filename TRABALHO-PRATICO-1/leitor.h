//
//  leitor.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef leitor_h
#define leitor_h
#include <stdio.h>
#include "livro.h"

#define MAX_TAM_STRING 50

typedef struct leitor Leitor;

Leitor *criaLeitor(char nome, char generos, int id, int numAfinidades);

void liberaLeitor(Leitor *l);

int getIdLeitor(Leitor *l);

char *getNomeLeitor(Leitor *l);

void *adicionaLivroLido(Leitor *leitor, Livro *livro);

void *adicionaLivroDesejado(Leitor *leitor, Livro *livro);

void *adicionaRecomendacaoDada(Leitor *leitor, Livro *livro);

#endif
