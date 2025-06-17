//
//  ListaLivros.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef ListaLivros_h
#define ListaLivros_h
#include <stdio.h>
#include "livro.h"

#define MAX_TAM_STRING 50

typedef struct listaLivros ListaLivros;

ListaLivros *criaListaLivros();

ListaLivros *adicionaLivro(ListaLivros *ll, Livro *livro);

void liberaListaLivros(ListaLivros *ll);

ListaLivros retiraLivro(ListaLivros *ll, int id);

Livro *buscaLivro(ListaLivros *ll, int id);

#endif
