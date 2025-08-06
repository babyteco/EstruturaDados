//  Created by Matheus Gon Zortea on 06/08/2025.

#include<stdio.h>
#include<stdlib.h>  

typedef struct arv Arvore;

struct arv {
    char caractere;
    int frequencia;
    Arvore* esq;
    Arvore* dir;
};

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arvore* criaArvore (char c, Arvore* e, Arvore* d, int frequencia){
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
int arv_pertence (Arvore* a, char caractere){
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

Arvore* arv_pai (Arvore* a, char caractere){
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

void atualizaFrequencia(Arvore *arv, int freq){
    arv->frequencia = freq;
}

char getCaractere(Arvore *arvore){
    return arvore->caractere;
}

int getFrequencia(Arvore *arv){
    return arv->frequencia;
}