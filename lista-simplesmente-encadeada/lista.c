#include<stdio.h>
#include<stdlib.h>
#include "lista.h"
#include "produto.h"

typedef struct celula Celula;

struct celula{
    Produto *prod;
    Celula *proxima;
};


struct lista{
    Celula *primeiro;
    Celula *ultimo;
};


Lista* criaLista(){
    Lista *l = (Lista*) malloc(sizeof(Lista));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}

Lista* insereProduto(Lista *l, Produto *p){
    Celula *nova = (Celula*) malloc(sizeof(Celula));  
    nova->prod = p;
    nova->proxima = NULL;

    //impede que produtos ja existentes sejam adicionados
    Celula *paliativa = l->primeiro;
    while (paliativa != NULL){
        if (getCodigoProduto(paliativa->prod) == getCodigoProduto(p)){
            printf("FALHA: Esse produto ja está cadastrado!\n");
            return l;
        } 
        paliativa = paliativa->proxima;
    }
    

    //a lista esta vazia
    if (l->ultimo == NULL && l->primeiro == NULL){
        l->primeiro = nova;
        l->ultimo = nova;
        return l;
    }

    //a lista so contem uma celula
    if (l->ultimo == l->primeiro){
        l->primeiro->proxima = nova;
        l->ultimo = nova;
        return l;
    }
    

    l->ultimo->proxima = nova;
    l->ultimo = nova;

    return l;
}

Lista* RetiraProduto(Lista *l, int codigo){
    Celula *atual = l->primeiro;
    
    //se o profuto for o unico
    if (getCodigoProduto(l->primeiro->prod) == getCodigoProduto(l->ultimo->prod) && getCodigoProduto(l->primeiro->prod) == codigo){
        liberaProduto(l->primeiro->prod);
        free(l->primeiro);
        l->primeiro = l->ultimo = NULL;
        return l;
    }
    
    
    //se o produto for o primeiro
    if (getCodigoProduto(atual->prod) == codigo){
        Celula *temp = l->primeiro;
        l->primeiro = l->primeiro->proxima;
        liberaProduto(temp->prod);
        free(temp);
        return l;
    }
    
    
    //caso geral, em que o produto nao e o primeiro da lista 
    while (atual != NULL){
        
        if (getCodigoProduto(atual->proxima->prod) == codigo){
            Celula *temp = atual->proxima;
            
            //se o produto for o ultimo
            if (atual->proxima->proxima == NULL){
                liberaProduto(l->ultimo->prod);
                free(l->ultimo);
                l->ultimo = atual;
                atual->proxima = NULL;
                return l;
            }
            
            atual->proxima = temp->proxima;
            liberaProduto(temp->prod);
            free(temp);
            break;
        }

        atual = atual->proxima;
    }

    return l;
}

void imprimeLista(Lista *l){
    printf("\nLISTA DE PRODUTOS:\n\n");
    
    if (l->primeiro == NULL){
        printf("Lista vazia :(\n");
    }
    

    Celula *atual = l->primeiro;
    while (atual != NULL){
        imprimeProduto(atual->prod);
        atual = atual->proxima;
    }   
}

void liberaListaCelula(Lista *l){
    Celula *atual = l->primeiro;
    while (atual != NULL){
        liberaProduto(atual->prod);
        Celula *temp = atual;
        atual = atual->proxima;
        free(temp);
    }
    free(l);   
}

