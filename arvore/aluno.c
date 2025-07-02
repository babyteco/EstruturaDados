// aluno.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

// Definicao da struct interna
struct Aluno {
    char nome[TAM_NOME];
    int matricula;
    float nota;
};

Aluno* cria_aluno(const char* nome, int matricula, float nota) {
    Aluno* a = (Aluno*) malloc(sizeof(Aluno));
    if (a != NULL) {
        strncpy(a->nome, nome, TAM_NOME - 1);
        a->nome[TAM_NOME - 1] = '\0';  
        a->matricula = matricula;
        a->nota = nota;
    }
    return a;
}

void set_nome(Aluno* a, const char* nome) {
    if (a != NULL) {
        strncpy(a->nome, nome, TAM_NOME - 1);
        a->nome[TAM_NOME - 1] = '\0';
    }
}

void set_matricula(Aluno* a, int matricula) {
    if (a != NULL) {
        a->matricula = matricula;
    }
}

void set_nota(Aluno* a, float nota) {
    if (a != NULL) {
        a->nota = nota;
    }
}

const char* get_nome(const Aluno* a) {
    return (a != NULL) ? a->nome : NULL;
}

int get_matricula(const Aluno* a) {
    return (a != NULL) ? a->matricula : -1;
}

float get_nota(const Aluno* a) {
    return (a != NULL) ? a->nota : -1.0f;
}

void imprime_aluno(const Aluno* a) {
    if (a != NULL) {
        printf("Aluno: %s\nMatricula: %d\nNota: %.2f\n", a->nome, a->matricula, a->nota);
    }
}

void libera_aluno(Aluno* a) {
    free(a);
}
