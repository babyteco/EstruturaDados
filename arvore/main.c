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


    Arvore *folha1 = arv_cria(a4, NULL, NULL);
    Arvore *folha2 = arv_cria(a5, NULL, NULL);
    Arvore *folha3 = arv_cria(a6, NULL, NULL);
    Arvore *folha4 = arv_cria(a7, NULL, NULL);

    Arvore *no1 = arv_cria(a2, folha1, folha2);
    Arvore *no2 = arv_cria(a3, folha3, folha4);
    
    Arvore *raiz = arv_cria(a1, no1, no2);

    int mat = 5;
    if (arv_pertence(raiz, mat)){
        printf("o aluno de matricula %d pertence à arvore!\n", mat);
    } else{
        printf("o aluno de matricula %d nao pertence à arvore!\n", mat);
    }
    
    mat = 6;
    Arvore *pai = arv_pai(raiz, mat);
    printf("O nome do pai do aluno de matricula %d eh: %s\n", mat, get_nome(getAluno(pai)));

    printf("A qtd de folhas da arvore eh: %d\n", folhas(raiz));

    mat = 4;
    printf("O aluno de matricula %d aparece %d vezes na arvore\n", mat, ocorrencias(raiz, mat));


    printf("A altura da arvore eh %d\n", altura(raiz));

    arv_libera(raiz);
    return 0;
}