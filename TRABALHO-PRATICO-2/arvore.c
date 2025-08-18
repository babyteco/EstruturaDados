//  Created by Matheus Gon Zortea on 06/08/2025.

#include<stdio.h>
#include<stdlib.h>  
#include <string.h>
#include "bitmap.h"

typedef struct arv Arvore;

struct arv {
    unsigned char caractere;
    int frequencia;
    Arvore* esq;
    Arvore* dir;
};

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arvore* criaArvore (unsigned char c, Arvore* e, Arvore* d, int frequencia){
    Arvore *arv = (Arvore*) malloc(sizeof(Arvore));
    arv->caractere = c;
    arv->frequencia = frequencia;
    arv->dir = d;
    arv->esq = e;
    return arv;
}

//retorna true se a árvore estiver vazia e false caso contrário
int arv_vazia (Arvore* a){
    if (a == NULL){
        return 1;
    }
    return 0;
}

//libera o espaço de memória ocupado pela árvore a
Arvore* liberaArvore (Arvore* a){
    if (!arv_vazia(a)){
        liberaArvore(a->esq);
        liberaArvore(a->dir);
        free(a);
    }
    
    return NULL;
}

//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arvore* a, unsigned char caractere){
    if (arv_vazia(a)){
        return 0;
    }
    
    
    if (a->caractere == caractere){
        return 1;
    } else if(arv_pertence(a->dir, caractere) || arv_pertence(a->esq, caractere)){
        return 1;
    }
    return 0;
}

//imprime as informações dos nós da árvore
void imprimeArvore (Arvore* a){
    if (!arv_vazia(a)){
        printf("caractere: %c\n", a->caractere);
        imprimeArvore(a->esq);
        imprimeArvore(a->dir);
    }
}

Arvore* arv_pai (Arvore* a, unsigned char caractere){
    if (arv_vazia(a)){
        return NULL;
    }
    

    if ((a->dir != NULL && a->caractere == caractere) ||
        (a->esq != NULL && a->esq->caractere == caractere)) {
        return a;
    }
    Arvore *paiEsq = arv_pai(a->esq, caractere);
    if (paiEsq != NULL) return paiEsq;
    
    Arvore *paiDir = arv_pai(a->dir, caractere);
    if (paiDir != NULL) return paiDir;

    return NULL;
}

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arvore* a){
    if (a == NULL){
        return 0;
    }
    
    int qtdFolhas = 0;
    
    if (a->dir==NULL && a->esq==NULL){
        return 1;
    }

    qtdFolhas += folhas(a->esq);
    qtdFolhas += folhas(a->dir);
    
    return qtdFolhas;
}

//retorna a altura da árvore a
int altura(Arvore* a){
    if (a == NULL) {
        return -1;  // árvore vazia tem altura -1
    }

    int alt_esq = altura(a->esq);
    int alt_dir = altura(a->dir);

    if (alt_esq > alt_dir)
        return alt_esq + 1;
    else{
        return alt_dir + 1;

    }
}

int ehFolha(Arvore *a){
    if (a->dir == NULL && a->esq == NULL){
        return 1;
    }
    return 0;
}

void atualizaFrequencia(Arvore *arv, int freq){
    arv->frequencia = freq;
}

unsigned char getCaractere(Arvore *arvore){
    return arvore->caractere;
}

int getFrequencia(Arvore *arv){
    return arv->frequencia;
}

char** preencheTabelaHuffman(Arvore *arvIdeal, char **tabela, char *codigoAtual) {
    if (ehFolha(arvIdeal)) {
        if (codigoAtual[0] == '\0') {
            // Caso especial: árvore com apenas uma folha
            tabela[(unsigned char)arvIdeal->caractere] = strdup("0");
        } else {
            tabela[(unsigned char)arvIdeal->caractere] = strdup(codigoAtual);
        }
        return tabela;
    }

    // percorre esquerda com '0'
    char esq[256], dir[256];
    strcpy(esq, codigoAtual);
    strcat(esq, "0");

    strcpy(dir, codigoAtual);
    strcat(dir, "1");

    //nao eh necessario igualar a tabela a chamada da função pois dentro dela a tabela ja e atualizada por referencia
    if (arvIdeal->esq)
        preencheTabelaHuffman(arvIdeal->esq, tabela, esq);

    if (arvIdeal->dir)
        preencheTabelaHuffman(arvIdeal->dir, tabela, dir);

    return tabela;
}

void escreveCabecalho(Arvore *arv, bitmap *bm) {
    if (arv == NULL) return;

    if (ehFolha(arv)) {
        // Escreve bit '1' indicando que é folha
        bitmapAppendLeastSignificantBit(bm, 1);

        // Escreve os 8 bits do caractere
        unsigned char c = getCaractere(arv);
        for (int i = 7; i >= 0; i--) {
            unsigned char bit = (c >> i) & 1;
            bitmapAppendLeastSignificantBit(bm, bit);
        }
    } else {
        // Escreve bit '0' indicando que é nó interno
        bitmapAppendLeastSignificantBit(bm, 0);

        // Continua a travessia em pré-ordem
        escreveCabecalho(arv->esq, bm);
        escreveCabecalho(arv->dir, bm);
    }
}

Arvore* reconstroiArvore(bitmap *bm, int *pos) {
    if (bitmapGetBit(bm, (*pos)++) == 1) {
        unsigned char c = 0;
        for (int i = 0; i < 8; i++) {
            c = (c << 1) | bitmapGetBit(bm, (*pos)++);
        }
        return criaArvore(c, NULL, NULL, 0);
    } else {
        Arvore* esq = reconstroiArvore(bm, pos);
        Arvore* dir = reconstroiArvore(bm, pos);
        return criaArvore('$', esq, dir, 0);
    }
}


void decodificaBitmapComArvore(bitmap *bm, int pos, Arvore *arv, FILE *saida, int n) {
    if (!bm || !arv || !saida) return;

    if (ehFolha(arv)) {
        for (int i = 0; i < n; ++i) {
            fputc(getCaractere(arv), saida);
        }
        return;
    }

    Arvore* atual = arv;
    int emitidos = 0;

    while (pos < bitmapGetLength(bm) && emitidos < n) {
        char bit = bitmapGetBit(bm, pos++);
        if (bit == 0){
            atual = atual->esq;
        }
        else{
            atual = atual->dir;
        }

        if (ehFolha(atual)) {
            fputc(getCaractere(atual), saida);
            emitidos++;
            atual = arv;
        }
    }
}