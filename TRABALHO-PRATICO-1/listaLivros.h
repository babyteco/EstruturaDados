//
//  ListaLivros.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef LISTA_LIVROS_H 
#define LISTA_LIVROS_H
#include <stdio.h>
#include "livro.h"
typedef struct listaLeitores ListaLeitores;
#include "listaLeitores.h"

typedef struct listaLivros ListaLivros;

ListaLivros *criaListaLivros();

ListaLivros *adicionaLivro(ListaLivros *ll, Livro *livro);

void liberaListaLivros(ListaLivros *ll);

ListaLivros *retiraLivro(ListaLivros *ll, int id);

Livro *buscaLivro(ListaLivros *ll, int id);

int livrosEmComum(ListaLeitores *ll, int id1, int id2, FILE *saida);

void imprimeLivrosLidos(Leitor *leitor, FILE *saida);

void imprimeLivrosDesejados(Leitor *leitor, FILE *saida);

void liberaCelulasListaLivros(ListaLivros *ll);

#endif
