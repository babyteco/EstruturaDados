#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "produto.h"

struct produto{
    int codigo;
    char nome[100];
    int preco;
};

Produto* criaProduto(int preco, int codigo, char *nome){
    Produto *p = (Produto*) malloc(sizeof(Produto));
    p->codigo = codigo;
    strcpy(p->nome, nome);
    p->preco = preco;
    return p;
}

void imprimeProduto(Produto *p){
    printf("PRODUTO:\n");
    printf("Nome: %s\n", p->nome);
    printf("Codigo: %d\n", p->codigo);
    printf("Preco: %d\n\n", p->preco);
}

void liberaProduto(Produto *p){
    free(p);
}

int getCodigoProduto(Produto *p){
    return p->codigo;
}