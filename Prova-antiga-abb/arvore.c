#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

struct arvore{
    Arvore *esq;
    Arvore *dir;
    char palavra[100];
    int qtd;
};

Arvore *criaArvore(){
    Arvore *a = (Arvore*) malloc(sizeof(Arvore));
    a->dir = NULL;
    a->esq = NULL;
    strcpy(a->palavra, "");
    a->qtd = 0;
    return a;
}

Arvore *insereNaArvore(Arvore *a, char *palavra){
    if (!a){
        Arvore *nova = criaArvore();
        strcpy(nova->palavra, palavra);
        nova->qtd = 1;
        return nova;
    }

    int flag = strcmp(a->palavra, palavra);
    if (flag == 0){
        a->qtd++;
        return a;
    } else if (flag < 0){
        a->dir = insereNaArvore(a->dir, palavra);
        return a;
    } else if (flag > 0){
        a->esq = insereNaArvore(a->esq, palavra);
        return a;
    }
    
    return a;
}

int contaTotalPalavras(Arvore *a){
    if (a == NULL) return 0;
    
    
    int total = a->qtd;
    total += contaTotalPalavras(a->esq);
    total += contaTotalPalavras(a->dir);

    return total;
}

int contaPalavrasDistintas(Arvore *a){
    if (a == NULL) return 0;
    
    int total = 1;
    total += contaPalavrasDistintas(a->esq);
    total += contaPalavrasDistintas(a->dir);

    return total;
}

Arvore* MaiorFrequencia(Arvore *a){
    if (a == NULL) return NULL;
    
    Arvore *ArvEsq = MaiorFrequencia(a->esq);
    Arvore *ArvDir = MaiorFrequencia(a->dir);
    int totalEsq;
    int totalDir;
    
    
    if(!ArvEsq){
        totalEsq = 0;
    } else totalEsq = ArvEsq->qtd;
    if(!ArvDir){
        totalDir = 0;
    } else totalDir = ArvDir->qtd;

    int atual = a->qtd;

    if (totalDir >= totalEsq){
        if (totalDir >= atual){
            return a->dir;
        } else return a;   
    } else if(totalEsq >= atual){
        return a->esq;
    } else return a;
}

char *getPalavra(Arvore *a){
    return a->palavra;
}

int getFrequencia(Arvore *a){
    return a->qtd;
}

int compara(const void *a1, const void *a2){
    Arvore *aa1 = *(Arvore **)a1;
    Arvore *aa2 = *(Arvore **)a2;

    int flag = aa1->qtd - aa2->qtd;
    if (flag == 0){
        return strcmp(aa1->palavra, aa2->palavra);
    } else return aa1->qtd - aa2->qtd;
}

void anulaVetor(Arvore *vetor[], int tam){
    for (int i = 0; i < tam; i++){
        vetor[i] = NULL;
    }
}

void preencheVetor(Arvore *vetor[], Arvore *a, int tam){
    if (a == NULL) return;

    for (int i = 0; i < tam; i++){
        if (vetor[i] == NULL){
            vetor[i] = a;
            break;
        }
    }

    preencheVetor(vetor, a->esq, tam);
    preencheVetor(vetor, a->dir, tam);
}

void imprimeArquivo(FILE *arq, Arvore *vetor[], int tam, Arvore *raiz){
    if (arq == NULL){
        printf("o arquivo é nulo\n");
    }
    
    for (int i = 0; i < tam; i++){
        fprintf(arq, "%s %d\n", vetor[i]->palavra, vetor[i]->qtd);
    }
    fprintf(arq, "------------------------\n");
    fprintf(arq, "%d palavras distintas encontradas\n", tam);
    fprintf(arq, "%d palavras no total\n", contaTotalPalavras(raiz));
    fprintf(arq, "%s é a palavra de maior frequência (%d)\n", getPalavra(MaiorFrequencia(vetor[tam-1])), getFrequencia(MaiorFrequencia(vetor[tam-1])));
}