// aluno.h

#ifndef ALUNO_H
#define ALUNO_H

#define TAM_NOME 100

// Tipo opaco
typedef struct aluno Aluno;

// Cria e retorna um ponteiro para um novo aluno
Aluno* cria_aluno(const char* nome, int matricula, float nota);

// Define o nome do aluno
void set_nome(Aluno* a, const char* nome);

// Define a matricula do aluno
void set_matricula(Aluno* a, int matricula);

// Define a nota do aluno
void set_nota(Aluno* a, float nota);

// Obtem o nome do aluno
const char* get_nome(const Aluno* a);

// Obtem a matricula do aluno
int get_matricula(const Aluno* a);

// Obtem a nota do aluno
float get_nota(const Aluno* a);

// Imprime os dados do aluno
void imprime_aluno(const Aluno* a);

// Libera a memoria do aluno
void libera_aluno(Aluno* a);

#endif
