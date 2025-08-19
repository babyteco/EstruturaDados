#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

int main(){
    Arvore *raiz = NULL;
    
    FILE *arq = fopen("input.txt", "r");
    
    char palavra[100];
    while (fscanf(arq, "%s", palavra) == 1){
        raiz = insereNaArvore(raiz, palavra);
    }
    
    printf("Total de palavras: %d\n", contaTotalPalavras(raiz));
    printf("Total de palavras distintas: %d\n", contaPalavrasDistintas(raiz));
    printf("Palavra com maior freq: %s\n", getPalavra(MaiorFrequencia(raiz)));
    printf("Frequencia da Palavra com maior freq: %d\n", getFrequencia(MaiorFrequencia(raiz)));

    fclose(arq);


    //segunda etapa
    int palavrasDistintas = contaPalavrasDistintas(raiz);
    Arvore *vetor[palavrasDistintas];
    anulaVetor(vetor, palavrasDistintas);
    preencheVetor(vetor, raiz, palavrasDistintas);
    
    int (*ptrCmp)(const void *, const void *);
    ptrCmp = compara;
    qsort(vetor, palavrasDistintas, sizeof(Arvore*), ptrCmp);
    
    FILE *saida = fopen("saida.txt", "w");
    imprimeArquivo(saida, vetor, palavrasDistintas, raiz);
    fclose(saida);
}
//enender por que o qsort nao esta ordenando corretamente