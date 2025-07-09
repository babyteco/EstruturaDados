#include<stdio.h>
#include<stdlib.h>  
#include "aluno.h"

typedef struct arv Arvore;

typedef struct aluno Aluno;

struct arv {
    Aluno *aluno;
    Arvore* esq;
    Arvore* dir;
};

//Cria uma árvore vazia
Arvore* arv_criavazia (void){
    return NULL;
}

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arvore* arv_cria (Aluno* c, Arvore* e, Arvore* d){
    Arvore *arv = (Arvore*) malloc(sizeof(Arvore));
    arv->aluno = c;
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
Arvore* arv_libera (Arvore* a){
    if (!arv_vazia(a)){
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    
    return NULL;
}


//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arvore* a, int mat){
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
void arv_imprime (Arvore* a){
    if (!arv_vazia(a)){
        imprime_aluno(a->aluno);
        arv_imprime(a->esq);
        arv_imprime(a->dir);
    }
}

//retorna a mãe/pai de um dado no que contém o aluno com a matrícula mat
Arvore* arv_pai (Arvore* a, int mat){
    if (arv_vazia(a)){
        return NULL;
    }
    

    if ((a->dir != NULL && get_matricula(a->dir->aluno) == mat) ||
        (a->esq != NULL && get_matricula(a->esq->aluno) == mat)) {
        return a;
    }
    Arvore *paiEsq = arv_pai(a->esq, mat);
    if (paiEsq != NULL) return paiEsq;
    
    Arvore *paiDir = arv_pai(a->dir, mat);
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

//retorna o numero de ocorrencias de um dado aluno na árvore
int ocorrencias (Arvore* a, int mat){
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
Aluno *getAluno(Arvore *arvore){
    return arvore->aluno;
}