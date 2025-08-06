//  Created by Matheus Gon Zortea on 06/08/2025.

#ifndef _LISTA_
#define _LISTA_

#include "arvore.h"

typedef struct lista Lista;

Lista* criaLista();

Lista* insereArvoreNaLista(Lista *l, Arvore *arv);

Lista *RetiraArvoreDaLista(Lista *l, Arvore *arv);

void desalocaCelula(Lista *l);

Arvore *buscaArvore(Lista *l, char caractere);

void liberaLista(Lista *l);

#endif // Lista
