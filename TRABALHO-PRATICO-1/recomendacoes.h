//
//  recomendacoes.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef ListaRecomendacoes_h
#define ListaRecomendacoes_h
#include <stdio.h>
typedef struct leitor Leitor;
typedef struct livro  Livro;

typedef struct listaListaRecomendacoes ListaRecomendacoes;

ListaRecomendacoes *criaListaRecomendacoes();

ListaRecomendacoes *adicionaRecomendacaoLista(ListaRecomendacoes *lr, Leitor *Leitor, Livro *livro);

Livro *retiraRecomendacao(ListaRecomendacoes *lr, int idLivro, int idRemetente);

Leitor *buscaRecomendacao(ListaRecomendacoes *lr, int idLivro, int idRemetente);

void liberaListaRecomendacoes(ListaRecomendacoes *lr);

void imprimeListaRecomendacoes(Leitor *l, FILE *saida){

#endif