//
//  livro.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "string.h"


typedef struct livro{
    char titulo[MAX_TAM_STRING];
    char autor[MAX_TAM_STRING];
    char genero[MAX_TAM_STRING];
    int ano;
    int id;
} Livro;

Livro *criaLivro(char *titulo, char *autor, char *genero, int ano, int id){
    Livro *l = (Livro*) malloc(sizeof(Livro));
    strcpy(l->titulo, titulo);
    strcpy(l->autor, autor);
    strcpy(l->genero, genero);
    l->ano = ano;
    l->id = id;
    return l;
}

void liberaLivro(Livro *l){
    free(l);
}

int getIdLivro(Livro *l){
    return l->id;
}

char *getTituloLivro(Livro *l){
    return l->titulo;
}
