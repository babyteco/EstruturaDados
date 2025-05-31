#include<stdio.h>
#include<stdlib.h>
#include "lista.h"
#include "produto.h"


struct lista{
    Produto *prod;
    Lista *prox;
    Lista *ant;
};


Lista* criaLista(){
    return NULL;
}

Lista* insereProduto(Lista *l, Produto *p){
    
    //impede que produtos ja existentes sejam adicionados
    Lista *paliativa = l;
    while (paliativa != NULL){
        if (getCodigoProduto(paliativa->prod) == getCodigoProduto(p)){
            printf("FALHA: Esse produto ja está cadastrado!\n");
            return l;
        } 
        paliativa = paliativa->prox;
    }
    
    
    //a lista esta vazia
    if (l == NULL){
        l = (Lista*) malloc(sizeof(Lista));
        l->prod = p;
        l->ant = NULL;
        l->prox = NULL;
        return l;
    }

    Lista *nova = (Lista*) malloc(sizeof(Lista));  
    nova->prod = p;
    nova->prox = l;
    nova->ant = NULL;
    l->ant = nova;

    return nova;
}

Lista *RetiraProduto(Lista *l, int codigo){
    Lista *atual = l;
    
    //se o profuto for o unico
    if ((getCodigoProduto(l->prod) == codigo) && (l->ant == NULL && l->prox == NULL)){
        liberaProduto(l->prod);
        free(l);
        return NULL;
    }
    
    
    //se o produto for o primeiro
    if (getCodigoProduto(l->prod) == codigo){
        Lista *temp = l->prox;
        liberaProduto(l->prod);
        free(l);
        temp->ant = NULL;
        return temp;
    }
    
    //caso geral, em que o produto nao e o primeiro da lista 
    while (atual != NULL){

        if (getCodigoProduto(atual->prod) == codigo){

            //se o produto for o ultimo
            if (atual->prox == NULL){
                Lista *temp = atual->ant;
                liberaProduto(atual->prod);
                free(atual);
                temp->prox = NULL;
                return l;
            }
            Lista *tempAnt = atual->ant;
            Lista *tempProx = atual->prox;

            liberaProduto(atual->prod);
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
    printf("\nLISTA DE PRODUTOS:\n\n");
    
    if (l == NULL){
        printf("Lista vazia :(\n");
    } else{
        Lista *atual = l;
        while (atual != NULL){
            imprimeProduto(atual->prod);
            atual = atual->prox;
        }   
    }
}

void liberaLista(Lista *l){
    while (l != NULL){
        liberaProduto(l->prod);
        Lista *temp = l;
        l = l->prox;
        free(temp);
    }
}