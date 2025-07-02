#include<stdio.h>
#include<stdlib.h>  

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
        return 0;
    }
    return 1;
}

//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arv* a, int mat);

//imprime as informações dos nós da árvore
void arv_imprime (Arv* a);

//retorna a mãe/pai de um dado no que contém o aluno com a matrícula mat
Arv* arv_pai (Arv* a, int mat);

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arv* a);

//retorna o numero de ocorrencias de um dado aluno na árvore
int ocorrencias (Arv* a, int mat);

//retorna a altura da árvore a
int altura(Arv* a);
 