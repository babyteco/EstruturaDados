// arvore.h

#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>
#include "aluno.h"

// Tipo opaco
typedef struct arvore Arvore;

// Cria e retorna um ponteiro para uma nova arvore
Arvore* cria_arvore();

// Imprime os dados da arvore
Arvore* insere_aluno(Arvore *arv, Aluno* aluno);

//busca aluno por matricua
Aluno *busca_aluno(Arvore *arv, int matricula);

//retira um aluno da arvore
Arvore* retira_aluno(Arvore *arv, Aluno *aluno);

// Libera a memoria da arvore
void libera_arvore(Arvore* a);

//imprime a arvore
void imprime_arvore(Arvore *a);

#endif
