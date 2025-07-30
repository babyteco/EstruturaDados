#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "abbgen.h"

#define MAXSTRING 100

typedef struct aluno Aluno;

struct aluno{
    char nome[MAXSTRING];
    int matricula;
    int cr;
};

int compara(void *a1, void *a2){
    Aluno *aluno1 = (Aluno*) a1;
    Aluno *aluno2 = (Aluno*) a2;
    
    if (strcmp(aluno1->nome, aluno2->nome) < 0){
        return -1;
    } else return 1;
}

void imprime(void *a, FILE *arq){
    Aluno *alu = (Aluno*) a;
    fprintf(arq, "%d %s %d\n", alu->matricula, alu->nome, alu->cr);
}

void libera(void *a){
    Aluno *alu = (Aluno*) a;
    free(alu);
}

Aluno *criaAluno(int matricula, int cr, char *nome){
    Aluno *a = (Aluno*) malloc(sizeof(Aluno));
    a->cr = cr;
    a->matricula = matricula;
    strcpy(a->nome, nome);
    return a;
}

int main(){
    
    Raiz *raiz = criaArvore(compara, imprime, libera);

    
    FILE *arq = fopen("entrada.txt", "r");
    int matricula, cr;
    char nome[MAXSTRING];
    while (fscanf(arq, "%d %99s %d", &matricula, nome, &cr) == 3){
        Aluno *a = criaAluno(matricula, cr, nome);

        insere(raiz, (void*)a);
    }
    fclose(arq);
    

    FILE *saida = fopen("saida.txt", "w");
    fprintf(saida, "Arvore organizada por Nome:\n");
    imprimeArvore(raiz, saida);
    fclose(saida);


    liberaArvore(raiz);
    return 0;
}