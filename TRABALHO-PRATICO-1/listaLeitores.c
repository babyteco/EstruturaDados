//
//  ListaLeitores.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLeitores.h"
#include "listaLivros.h"
#include "livro.h"
#include "leitor.h"
#include "recomendacoes.h"

typedef struct celula Celula;

typedef struct listaLeitores{
    Celula *primeiro;
    Celula *ultimo;
} ListaLeitores;

struct celula{
    Celula *prox;
    Celula *ant;
    Leitor *leitor;
};

ListaLeitores *criaListaLeitores(){
    ListaLeitores *ll = (ListaLeitores*) malloc(sizeof(ListaLeitores));
    ll->primeiro = NULL;
    ll->ultimo = NULL;
    return ll;
}

ListaLeitores *adicionaLeitor(ListaLeitores *ll, Leitor *leitor){ 
    Celula *cel = (Celula*) malloc(sizeof(Celula));
    cel->leitor= leitor;

    if (ll->primeiro == NULL){
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

void liberaListaLeitores(ListaLeitores *ll){
    Celula *paliativa = ll->primeiro;
    for (int i = 0; paliativa!= NULL; i++){
        Celula *temp = paliativa;
        paliativa = paliativa->prox;
        liberaLeitor(temp->leitor);
        free(temp);
    }
    free(ll);
}

void liberaCelulasListaAfinidades(ListaLeitores *ll){
    Celula *paliativa = ll->primeiro;
    while(paliativa!= NULL){
        Celula *temp = paliativa->prox;
        free(paliativa);
        paliativa = temp;
    }
    free(ll);
}

void retiraLeitor(ListaLeitores *ll, int id){
    Celula *nova = ll->primeiro;

    for (int i = 0; nova != NULL; i++){
        if (getIdLeitor(nova->leitor) == id){
            if (ll->primeiro == ll->ultimo){
                free(ll->primeiro);
                ll->primeiro = NULL;
                ll->ultimo = NULL;
                return;
            }
            
            if (nova == ll->primeiro){
                Celula *cel = ll->primeiro->prox;
                free(ll->primeiro);
                ll->primeiro = cel;
                if (cel != NULL) {
                    cel->ant = NULL;
                } else {
                    // Se não há próximo elemento, a lista fica vazia
                    ll->ultimo = NULL;
                }
                return;
            }

            if (nova == ll->ultimo){
                Celula *cel = ll->ultimo->ant;
                free(ll->ultimo);
                ll->ultimo = cel;
                if (cel != NULL) {
                    cel->prox = NULL;
                } else {
                    // Se não há elemento anterior, a lista fica vazia
                    ll->primeiro = NULL;
                }
                return;
            }
            
            Celula *celAnt = nova->ant;
            Celula *celPos = nova->prox;
            free(nova);
            celAnt->prox = celPos;
            celPos->ant = celAnt;
        }
        nova = nova->prox;
    }
}

Leitor *buscaLeitor(ListaLeitores *ll, int id){
    Celula *temp = ll->primeiro;
    while (temp != NULL){
        if (id == getIdLeitor(temp->leitor)){
            return temp->leitor;
        }
        temp = temp->prox;
    }
    return NULL;
}

void preencheListaAfinidadesDiretas(ListaLeitores *l){
    Celula *temp = l->primeiro;
    while (temp != NULL){
        Celula *candidato = l->primeiro;
        while (candidato != NULL){
            adicionaNaListaSeTiverAfinidade(temp->leitor, candidato->leitor);
            candidato = candidato->prox;
        }
        temp = temp->prox;
    }
}

int verificaSeTemComum(Leitor *l1, Leitor *l2){   
    if (l1 == l2){
        return 0;
    }
    
    
    char **listaGeneros1 = getListaGeneros(l1);
    char **listaGeneros2 = getListaGeneros(l2);
    int qtd1 = getNumGeneros(l1);
    int qtd2 = getNumGeneros(l2);
    
    for (int i = 0; i < qtd1; i++){
        for (int j = 0; j < qtd2; j++){
            if (strcmp(listaGeneros1[i], listaGeneros2[j]) == 0){
                return 1;
            }
        }    
    }
    return 0;
}

int verificaSeTemAfinidade(ListaLeitores *ll, int id1, int id2){
    Leitor *l1 = buscaLeitor(ll, id1);
    Leitor *l2 = buscaLeitor(ll, id2);
    
    // Verificar se os leitores existem
    if (l1 == NULL || l2 == NULL){
        printf("Erro: Leitor não encontrado\n");
        return 0;
    }
    
    ListaLeitores *afinidadesPrimarias = getListaAfinidade(l1);
    
    Celula *temp = afinidadesPrimarias->primeiro;
    while (temp != NULL){
        if (temp->leitor == l2){
            return 1;
        }
        
        ListaLeitores *afinidadesSecundarias = getListaAfinidade(temp->leitor);
        Celula *temp2 = afinidadesSecundarias->primeiro;
        while (temp2 != NULL){
            if (temp2->leitor == l2){
                return 1;
            }
            temp2 = temp2->prox;
        }
        temp = temp->prox;
    }
    return 0;
}   

void imprimeLeitores(ListaLeitores *ll, FILE *saida){
    if (ll == NULL || ll->primeiro == NULL){
        printf("Lista de leitores vazia\n");
        return;
    }
    
    Celula *temp = ll->primeiro;
    
    while (temp != NULL){
        fprintf(saida, "\nLeitor: %s\n", getNomeLeitor(temp->leitor));
        fprintf(saida, "Lidos: ");
        imprimeLivrosLidos(temp->leitor, saida);
        fprintf(saida, "Desejados: ");
        imprimeLivrosDesejados(temp->leitor, saida);
        fprintf(saida, "Recomendacoes: ");
        imprimeListaRecomendacoes(temp->leitor, saida);
        fprintf(saida, "Afinidades: ");
        imprimeAfinidades(getListaAfinidade(temp->leitor), saida);
        temp = temp->prox;
    }

}

void imprimeAfinidades(ListaLeitores *afinidades, FILE *saida){
    Celula *temp = afinidades->primeiro;
    
    while (temp != NULL){
        if(temp->prox == NULL){
            fprintf(saida, "%s\n", getNomeLeitor(temp->leitor));
        } else{
            fprintf(saida, "%s, ", getNomeLeitor(temp->leitor));
        }
        temp = temp->prox;
    }
}