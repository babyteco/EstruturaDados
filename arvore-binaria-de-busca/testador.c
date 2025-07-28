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

    Arvore *arvore = cria_arvore();
    
    arvore = insere_aluno(arvore, a1);
    arvore = insere_aluno(arvore, a2);
    arvore = insere_aluno(arvore, a3);
    arvore = insere_aluno(arvore, a4);
    arvore = insere_aluno(arvore, a5);
    arvore = insere_aluno(arvore, a6);
    arvore = insere_aluno(arvore, a7);

    int matricula = 4;
    printf("aluno de matricula %d da arvore:\n", matricula);
    Aluno *aluno = busca_aluno(arvore, matricula);
    imprime_aluno(aluno);


    printf("retirando aluno de matricula: %d\n", matricula);
    arvore = retira_aluno(arvore, aluno);


    printf("imprimindo arvore:\n");
    imprime_arvore(arvore);

    libera_arvore(arvore);


    
    return 0;
}