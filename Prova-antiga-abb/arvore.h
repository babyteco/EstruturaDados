#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore *criaArvore();

Arvore *insereNaArvore(Arvore *a, char *palavra);

int contaTotalPalavras(Arvore *a);

int contaPalavrasDistintas(Arvore *a);

Arvore* MaiorFrequencia(Arvore *a);

char *getPalavra(Arvore *a);

int getFrequencia(Arvore *a);

int compara(const void *a1, const void *a2);

void preencheVetor(Arvore *vetor[], Arvore *a, int tam);

void imprimeArquivo(FILE *arq, Arvore *vetor[], int tam, Arvore *raiz);

void anulaVetor(Arvore *vetor[], int tam);

#endif