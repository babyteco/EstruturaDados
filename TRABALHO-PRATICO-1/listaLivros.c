//
//  ListaLivros.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLivros.h"
#include "livro.h"
#include "leitor.h"

typedef struct celula Celula;

typedef struct listaLivros{
    Celula *primeiro;
    Celula *ultimo;
} ListaLivros;

struct celula{
    Celula *prox;
    Celula *ant;
    Livro *livro;
};

ListaLivros *criaListaLivros(){
    ListaLivros *ll = (ListaLivros*) malloc(sizeof(ListaLivros));
    ll->primeiro = NULL;
    ll->ultimo = NULL;
    return ll;
}

ListaLivros *adicionaLivro(ListaLivros *ll, Livro *livro){
    Celula *cel = (Celula*) malloc(sizeof(Celula));
    cel->livro = livro;

    if (!(ll->primeiro)){
        ll->primeiro = cel;
        ll->ultimo = cel;
        ll->primeiro->prox = NULL;
        ll->primeiro->ant = NULL;
        return ll;
    }
    
    Celula *antigoUltimo = ll->ultimo;
    ll->ultimo->prox = cel;
    ll->ultimo = cel;
    ll->ultimo->prox = NULL;
    ll->ultimo->ant = antigoUltimo;

    return ll;
}

void liberaListaLivros(ListaLivros *ll){
    Celula *paliativa = ll->primeiro;
    for (int i = 0; paliativa!= NULL; i++){
        Celula *temp = paliativa;
        paliativa = paliativa->prox;
        liberaLivro(temp->livro);
        free(temp);
    }
    free(ll);
}

ListaLivros *retiraLivro(ListaLivros *ll, int id){
    Celula *nova = ll->primeiro;

    for (int i = 0; nova != NULL; i++){
        if (getIdLivro(nova->livro) == id){
            if (ll->primeiro == ll->ultimo){
                free(ll->primeiro);
                ll->primeiro = NULL;
                ll->ultimo = NULL;
                return ll;
            }
            
            if (nova == ll->primeiro){
                Celula *cel = ll->primeiro->prox;
                free(ll->primeiro);
                ll->primeiro = cel;
                cel->ant = NULL;
                return ll;
            }

            if (nova == ll->ultimo){
                Celula *cel = ll->ultimo->ant;
                free(ll->ultimo);
                ll->ultimo = cel;
                cel->prox = NULL;
                return ll;
            }
            
            Celula *celAnt = nova->ant;
            Celula *celPos = nova->prox;
            free(nova);
            celAnt->prox = celPos;
            celPos->ant = celAnt;
        }
        nova = nova->prox;
    }
    return ll;
}

Livro *buscaLivro(ListaLivros *ll, int id){
    Celula *temp = ll->primeiro;
    while (temp != NULL){
        if (id == getIdLivro(temp->livro)){
            return temp->livro;
        }
        temp = temp->prox;
    }
    return NULL;
}

int livrosEmComum( ListaLeitores *ll, int id1, int id2){
    ListaLivros *l1 = getListaLidosDeUmLeitor(buscaLeitor(ll, id1));
    ListaLivros *l2 = getListaLidosDeUmLeitor(buscaLeitor(ll, id2));
    int flag = 0;
    printf("Livros em comum entre %s e %s: ", getNomeLeitor(buscaLeitor(ll, id1)), getNomeLeitor(buscaLeitor(ll, id2)));

    Celula *primeiraLista = l1->primeiro;
    while (primeiraLista != NULL){
        Celula *segundaLista = l2->primeiro;
        while (segundaLista != NULL){
            if (getIdLivro(primeiraLista->livro) == getIdLivro(segundaLista->livro)){
                printf("%s, ", getTituloLivro(primeiraLista->livro));
                flag = 1;
            }
            segundaLista = segundaLista->prox;
        }
        primeiraLista = primeiraLista->prox;        
    }
    if (flag == 1){
        return 1;
    }
    printf("Nenhum livro em comum\n");
    return 0;
}

void imprimeLivrosLidos(ListaLivros *lidos){
    Celula *temp = lidos->primeiro;

    while (temp != NULL){
        printf("%s ", getTituloLivro(temp->livro));
        temp = temp->prox;
    }
    printf("\n");
}