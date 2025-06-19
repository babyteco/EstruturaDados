//
//  livro.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef livro_h
#define livro_h
#include <stdio.h>

#define MAX_TAM_STRING 50

typedef struct livro Livro;

Livro *criaLivro(char *titulo, char *autor, char *genero, int ano, int id);

void liberaLivro(Livro *l);

int getIdLivro(Livro *l);

char *getTituloLivro(Livro *l);

#endif
