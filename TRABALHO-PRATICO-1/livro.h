//
//  livro.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef livro_h
#define livro_h
#include <stdio.h>

#ifndef MAX_TAM_STRING
#define MAX_TAM_STRING 50
#endif

typedef struct livro Livro;

Livro *criaLivro(char *titulo, char *autor, char *genero, int ano, int id);

void liberaLivro(Livro *l);

int getIdLivro(Livro *l);

char *getTituloLivro(Livro *l);

void imprimeLivro(Livro *l);

#endif
