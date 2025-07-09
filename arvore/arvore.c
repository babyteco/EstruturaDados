#include<stdio.h>
#include<stdlib.h>  
#include "aluno.h"

typedef struct arv Arvore;

typedef struct aluno Aluno;

typedef struct arv {
    Aluno *aluno;
    Arvore* esq;
    Arvore* dir;
} Arv;

//Cria uma árvore vazia
Arv* arv_criavazia (void){
    return NULL;
}

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arv* arv_cria (Aluno* c, Arv* e, Arv* d){
    Arv *arv = (Arv*) malloc(sizeof(Arv));
    arv->aluno = c;
    arv->dir = d;
    arv->esq = e;
    return arv;
}

//libera o espaço de memória ocupado pela árvore a
Arv* arv_libera (Arv* a){
    if (!arv_vazia(a)){
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    
    return NULL;
}

//retorna true se a árvore estiver vazia e false caso contrário
int arv_vazia (Arv* a){
    if (a == NULL){
        return 1;
    }
    return 0;
}

//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arv* a, int mat){
    if (arv_vazia(a)){
        return 0;
    }
    
    
    if (get_matricula(a->aluno) == mat){
        return 1;
    } else if(arv_pertence(a->dir, mat) || arv_pertence(a->esq, mat)){
        return 1;
    }
    return 0;
}

//imprime as informações dos nós da árvore
void arv_imprime (Arv* a){
    if (!arv_vazia(a)){
        imprime_aluno(a->aluno);
        arv_imprime(a->esq);
        arv_imprime(a->dir);
    }
}

//retorna a mãe/pai de um dado no que contém o aluno com a matrícula mat
Arv* arv_pai (Arv* a, int mat){
    if (arv_vazia(a)){
        return NULL;
    }
    

    if ((a->dir != NULL && get_matricula(a->dir->aluno) == mat) ||
        (a->esq != NULL && get_matricula(a->esq->aluno) == mat)) {
        return a;
    }
    Arv *paiEsq = arv_pai(a->esq, mat);
    if (paiEsq != NULL) return paiEsq;
    
    Arv *paiDir = arv_pai(a->dir, mat);
    if (paiDir != NULL) return paiDir;

    return NULL;
}

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arv* a){
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

//retorna o numero de ocorrencias de um dado aluno na árvore
int ocorrencias (Arv* a, int mat){
    if (a == NULL){
        return 0;
    }
    
    int numOcorrencia = 0;
    
    if (get_matricula(a->aluno) == mat) numOcorrencia++;

    numOcorrencia += ocorrencias(a->esq, mat);
    numOcorrencia += ocorrencias(a->dir, mat);
    
    return numOcorrencia;
}

//retorna a altura da árvore a
int altura(Arv* a){
    
}