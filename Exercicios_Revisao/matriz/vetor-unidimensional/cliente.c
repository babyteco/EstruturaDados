#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(){
    int linha1, linha2, coluna1, coluna2;
    
    scanf("%d %d\n", &linha1, &coluna1);
    scanf("%d %d\n", &linha2, &coluna2);
    
    Matriz *m1, *m2, *mult, *transp;

    m1 = inicializaMatriz(linha1, coluna1);
    m2 = inicializaMatriz(linha2, coluna2);


    for (int i = 0; i < linha1; i++){
        for (int j = 0; j < coluna1; j++){
            int elem;
            scanf("%d\n", &elem);
            modificaElemento(m1, i, j, elem);
        }
    }
    printf("MATRIZ 1:\n");
    imprimeMatriz(m1);
    printf("\n");
    
    
    for (int i = 0; i < linha2; i++){
        for (int j = 0; j < coluna2; j++){
            int elem;
            scanf("%d\n", &elem);
            modificaElemento(m2, i, j, elem);
        }
    }
    printf("MATRIZ 2:\n");
    imprimeMatriz(m2);
    printf("\n");
    
    mult = multiplicacao(m1, m2);    
    printf("MATRIZ 1 * MATRIZ 2:\n");
    imprimeMatriz(mult);
    printf("\n");

    transp = transposta(m1);    
    printf("MATRIZ 1 TRANSPOSTA:\n");
    imprimeMatriz(transp);
    printf("\n");
    
    destroiMatriz(m1);
    destroiMatriz(m2);
    destroiMatriz(mult);
    destroiMatriz(transp);
}