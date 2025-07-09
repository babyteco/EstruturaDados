#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "arvore.h"

int main(){
    Aluno *a1 = cria_aluno("alberto", 0, 6.5);
    Aluno *a2 = cria_aluno("breno", 1, 6.5);
    Aluno *a3 = cria_aluno("carlos", 2, 6.5);
    Aluno *a4 = cria_aluno("davi", 3, 6.5);
    Aluno *a5 = cria_aluno("edu", 4, 6.5);
    Aluno *a6 = cria_aluno("felipe", 5, 6.5);
    Aluno *a7 = cria_aluno("giovani", 6, 6.5);


    Arv *folha1 = arv_cria(a4, NULL, NULL);
    Arv *folha2 = arv_cria(a5, NULL, NULL);
    Arv *folha3 = arv_cria(a6, NULL, NULL);
    Arv *folha4 = arv_cria(a7, NULL, NULL);

    Arv *no1 = arv_cria(a2, folha1, folha2);
    Arv *no2 = arv_cria(a3, folha3, folha4);
    
    Arv *raiz = arv_cria(a1, no1, no2);

    int mat = 5;
    if (arv_pertence(raiz, mat)){
        printf("o aluno de matricula %d pertence à arvore!\n", mat);
    } else{
        printf("o aluno de matricula %d nao pertence à arvore!\n", mat);
    }
    
    int mat = 6;
    Arv *pai = arv_pai(raiz, mat);
    printf("a arvore pai do aluno de matricula %d eh:\n", mat);
    arv_imprime(pai);

    printf("A qtd de folhas da arvore eh: %d\n", folhas(raiz));

    int mat = 4;
    printf("O aluno de matricula %d aparece %d vezes na arvore\n", mat, ocorrencias(raiz, mat));

    return 0;
}