//  Created by Matheus Gon Zortea on 06/08/2025.
#ifndef arvore_h
#define arvore_h

#include "bitmap.h"
#include <stdio.h>

typedef struct arv Arvore;

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arvore* criaArvore (unsigned char c, Arvore* e, Arvore* d, int frequencia);

//libera o espaço de memória ocupado pela árvore a
Arvore* liberaArvore (Arvore* a);

//retorna true se a árvore estiver vazia e false caso contrário
int arv_vazia (Arvore* a);

//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arvore* a, unsigned char caractere);

//imprime as informações dos nós da árvore
void imprimeArvore (Arvore* a);

//retorna a mãe/pai de um dado no que contém o aluno com a matrícula mat
Arvore* arv_pai (Arvore* a, unsigned char caractere);

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arvore* a);

//retorna o numero de ocorrencias de um dado aluno na árvore
int ocorrencias (Arvore* a, int mat);

//retorna a altura da árvore a
int altura(Arvore* a);

void atualizaFrequencia(Arvore *arv, int freq);

unsigned char getCaractere(Arvore *arvore);

int getFrequencia(Arvore *arv);

char** preencheTabelaHuffman(Arvore *arvIdeal, char **tabela, char *codigoAtual);

void escreveCabecalho(Arvore *arv, bitmap *bm);

Arvore* reconstroiArvore(bitmap* bm, int* pos);

void decodificaBitmapComArvore(bitmap *bm, int pos, Arvore *arv, FILE *saida, int n);

#endif 