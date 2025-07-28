#include<stdio.h>
#include<stdlib.h>
#include "aluno.h"
#include "arvore.h"


// Tipo opaco
typedef struct arvore{
    Arvore *esq;
    Arvore *dir;
    Aluno *aluno;
} Arvore;

// Cria e retorna um ponteiro para uma nova arvore
Arvore* cria_arvore(){
    return NULL;
}

// Imprime os dados da arvore
Arvore* insere_aluno(Arvore *arv, Aluno* aluno){
    if (arv == NULL){
        Arvore *a = (Arvore*) malloc(sizeof(Arvore));
        a->aluno = aluno;
        a->esq = NULL;
        a->dir = NULL;
        arv = a;
        return arv;
    } else if(get_matricula(aluno) < get_matricula(arv->aluno)){
        arv->esq = insere_aluno(arv->esq, aluno);
    } else if(get_matricula(aluno) > get_matricula(arv->aluno)){
        arv->dir = insere_aluno(arv->dir, aluno);
    }
    return arv;
}

//busca aluno por matricua
Aluno *busca_aluno(Arvore *arv, int matricula){
    if (arv == NULL){
        printf("nao foi possivel achar o aluno de matricula: %d\n", matricula);
    }
    
    
    if (get_matricula(arv->aluno) == matricula){
        return arv->aluno;
    } else if(get_matricula(arv->aluno) > matricula){
        return busca_aluno(arv->esq, matricula);
    } else if(get_matricula(arv->aluno) < matricula){
        return busca_aluno(arv->dir, matricula);
    }

    return NULL;
}

//retira um aluno da arvore
Arvore* retira_aluno(Arvore *arv, Aluno *aluno){
    if (arv == NULL){
        return NULL;
    }

    int matAluno = get_matricula(aluno);
    int matArv = get_matricula(arv->aluno);
    
    
    if (matArv > matAluno){
        arv->esq = retira_aluno(arv->esq, aluno);
    } else if(matArv < matAluno){
        arv->dir = retira_aluno(arv->dir, aluno);
    } else if(matAluno == matArv){
        if (arv->dir == NULL && arv->esq == NULL){
            libera_aluno(arv->aluno);
            free(arv);
            arv = NULL;
        } else if(arv->dir == NULL || arv->esq == NULL){
            if (arv->dir == NULL){
                Arvore *temp = arv;
                arv = arv->esq;
                libera_aluno(temp->aluno);
                free(temp);
            } else{
                Arvore *temp = arv;
                arv = arv->dir;
                libera_aluno(temp->aluno);
                free(temp);
            } 
        } else {
            Arvore *paliativa = arv->esq;
            Arvore *paiPaliativa = arv;
            while (paliativa->dir != NULL){
                paiPaliativa = paliativa;
                paliativa = paliativa->dir;
            }
            libera_aluno(arv->aluno);
            arv->aluno = paliativa->aluno;
            if (paiPaliativa == arv) {
                arv->esq = paliativa->esq;
            } else {
                paiPaliativa->dir = paliativa->esq;
            }
            free(paliativa);
        }
    }
    
    return arv;
}

// Libera a memoria da arvore
void libera_arvore(Arvore* a){
    
    if (a != NULL){
        arv_libera(a->esq);
        arv_libera(a->dir);
        libera_aluno(a->aluno);
        free(a);
    }
    
    return NULL;
}

//imprime a arvore
void imprime_arvore(Arvore *a){
    if (a != NULL){
        imprime_aluno(a->aluno);
        arv_imprime(a->esq);
        arv_imprime(a->dir);
    }
}
