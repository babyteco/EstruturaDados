#include<stdio.h>
#include<stdlib.h>
#include "lista.h"
#include "arvore.h"


struct lista{
    Arvore *arv;
    Lista *prox;
    Lista *ant;
};


Lista* criaLista(){
    return NULL;
}

Lista* insereArvore(Lista *l, Arvore *arv){
    
    //impede que Arvores ja existentes sejam adicionados
    Lista *paliativa = l;
    while (paliativa != NULL){
        if (getCaractere(paliativa->arv) == getCaractere(arv)){
            printf("FALHA: Esse Arvore ja está na arvore!\n");
            return l;
        } 
        paliativa = paliativa->prox;
    }
    
    
    //a lista esta vazia
    if (l == NULL){
        l = (Lista*) malloc(sizeof(Lista));
        l->arv = arv;
        l->ant = NULL;
        l->prox = NULL;
        return l;
    }

    Lista *nova = (Lista*) malloc(sizeof(Lista));  
    nova->arv = arv;
    nova->prox = l;
    nova->ant = NULL;
    l->ant = nova;

    return nova;
}

Lista *RetiraArvore(Lista *l, int codigo){
    Lista *atual = l;
    
    //se o profuto for o unico
    if ((getCodigoArvore(l->prod) == codigo) && (l->ant == NULL && l->prox == NULL)){
        liberaArvore(l->prod);
        free(l);
        return NULL;
    }
    
    
    //se o Arvore for o primeiro
    if (getCodigoArvore(l->prod) == codigo){
        Lista *temp = l->prox;
        liberaArvore(l->prod);
        free(l);
        temp->ant = NULL;
        return temp;
    }
    
    //caso geral, em que o Arvore nao e o primeiro da lista 
    while (atual != NULL){

        if (getCodigoArvore(atual->prod) == codigo){

            //se o Arvore for o ultimo
            if (atual->prox == NULL){
                Lista *temp = atual->ant;
                liberaArvore(atual->prod);
                free(atual);
                temp->prox = NULL;
                return l;
            }
            Lista *tempAnt = atual->ant;
            Lista *tempProx = atual->prox;

            liberaArvore(atual->prod);
            free(atual);

            tempAnt->prox = tempProx;
            tempProx->ant = tempAnt;

            return l;
        }

        atual = atual->prox;
    }

    return l;
}

void imprimeLista(Lista *l){
    printf("\nLISTA DE ArvoreS:\n\n");
    
    if (l == NULL){
        printf("Lista vazia :(\n");
    } else{
        Lista *atual = l;
        while (atual != NULL){
            imprimeArvore(atual->prod);
            atual = atual->prox;
        }   
    }
}

void liberaLista(Lista *l){
    while (l != NULL){
        liberaArvore(l->prod);
        Lista *temp = l;
        l = l->prox;
        free(temp);
    }
}