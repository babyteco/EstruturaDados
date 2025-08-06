//  Created by Matheus Gon Zortea on 06/08/2025.

#include<stdio.h>
#include<stdlib.h>
#include "lista.h"
#include "arvore.h"

#define tam_ASCII 256

struct lista{
    Arvore *arv;
    Lista *prox;
    Lista *ant;
};


Lista* criaLista(){
    return NULL;
}

//insere uma árvore ordenadamente na lista de arvores
Lista* insereArvoreNaLista(Lista *l, Arvore *arv){
    Lista *nova = (Lista*) malloc(sizeof(Lista));
    nova->arv = arv;
    nova->prox = NULL;
    nova->ant = NULL;

    // Caso 1: lista vazia
    if (l == NULL) {
        return nova;
    }

    Lista *paliativa = l;

    // Caso 2: inserir no início
    if (getFrequencia(arv) <= getFrequencia(paliativa->arv)) {
        nova->prox = paliativa;
        paliativa->ant = nova;
        return nova;
    }

    // Caso 3: inserir no meio ou final
    while (paliativa->prox != NULL && getFrequencia(arv) > getFrequencia(paliativa->prox->arv)) {
        paliativa = paliativa->prox;
    }

    // Inserção após paliativa
    nova->prox = paliativa->prox;
    nova->ant = paliativa;

    if (paliativa->prox != NULL) {
        paliativa->prox->ant = nova;
    }

    paliativa->prox = nova;

    return l;
}

//retira a celula que contem determinada arvore, sem liberar essa arvore
Lista *RetiraArvoreDaLista(Lista *l, Arvore *arv){
    Lista *paliativa = l;
    while (paliativa != NULL){
        if (paliativa->arv == arv){
            if (paliativa->ant == NULL && paliativa->prox == NULL){
                desalocaCelula(paliativa);
                return NULL;
            }

            if (paliativa->ant == NULL){
                Lista *temp = paliativa->prox;
                temp->ant = NULL;
                desalocaCelula(paliativa);
                return temp;
            }
            
            if (paliativa->prox == NULL){
                Lista *temp = paliativa->ant;
                temp->prox = NULL;
                desalocaCelula(paliativa);
                return l;
            }
            
            Lista *tempAnt = paliativa->ant;
            Lista *tempProx = paliativa->prox;
            tempAnt->prox = tempProx;
            tempProx->ant = tempAnt;
            desalocaCelula(paliativa);
            return l;
        }
        paliativa = paliativa->prox;
    }
    return l;
}

void imprimeLista(Lista *l){
    printf("\nLISTA DE Arvores:\n\n");
    
    if (l == NULL){
        printf("Lista vazia :(\n");
    } else{
        Lista *atual = l;
        while (atual != NULL){
            imprimeArvore(atual->arv);
            atual = atual->prox;
        }   
    }
}

int getTamanhoLista(Lista *l){
    Lista *paliativo = l;
    
    if (l == NULL){
        return 0;
    }
    
    int soma = 0;
    while (paliativo != NULL){
        soma++;
        paliativo = paliativo->prox;
    }
    return soma;
}

Lista *obtemListaIdeal(Lista *l){
    int tam = getTamanhoLista(l);

    if (tam <= 1){
        return l;
    }
    
    Arvore *T1, *T2;
    T1 = l->arv;
    T2 = l->prox->arv;

    int somaFrequencia = getFrequencia(T1) + getFrequencia(T2);

    Arvore *nova = criaArvore('$', T1, T2, somaFrequencia);

    l = RetiraArvoreDaLista(l, T1);
    l = RetiraArvoreDaLista(l, T2);
    l = insereArvoreNaLista(l, nova);

    return obtemListaIdeal(l);
}

Arvore *getArvore(Lista *l){
    return l->arv;
}

Arvore *buscaArvore(Lista *l, char caractere){
    Lista *paliativo = l;
    while (paliativo != NULL){
        if (getCaractere(paliativo->arv) == caractere){
            return paliativo->arv;
        }
        paliativo = paliativo->prox;
    }
    
    return NULL;
}

void desalocaCelula(Lista *l){
    free(l);
}

void liberaLista(Lista *l){
    while (l != NULL){
        liberaArvore(l->arv);
        Lista *temp = l;
        l = l->prox;
        free(temp);
    }
}