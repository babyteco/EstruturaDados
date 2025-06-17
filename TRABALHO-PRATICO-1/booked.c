//
//  booked.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include "listaLeitores.h"
#include "listaLivros.h"
#include "recomendacoes.h"

typedef struct booked{
    ListaLeitores *listaLeitores;
    ListaLivros *catalogoLivros;
} Booked;

Booked *criaBooked(){
    Booked *b = (Booked*) malloc(sizeof(Booked));
    b->listaLeitores = criaListaLeitores();
    b->catalogoLivros = criaListaLivros();
    return b;
}

void leLivrosTxt(Booked *b){
    FILE *arq = fopen("Livros.txt", "r");
    char titulo[MAX_TAM_STRING];
    char autor[MAX_TAM_STRING];
    char genero[MAX_TAM_STRING];
    int ano;
    int id;
    while (fscanf(arq, "%d;""%49[^;]""%49[^;]""%49[^;]""%d\n", &id, titulo, autor, genero, &ano)){
        Livro *l = criaLivro(titulo, autor, genero, ano, id);
        b->catalogoLivros = adicionaLivro(b->catalogoLivros, l);
    }
    fclose(arq);
}

void leLeitoresTxt(Booked *b){
    FILE *arq = fopen("Leitores.txt", "r");
    char nome[MAX_TAM_STRING];
    char **generos;
    int numAfinidades;
    int id;
    while (fscanf(arq, "%d;""%49[^;]""%d", &id, nome, &numAfinidades)){
        for (int i = 0; i < numAfinidades; i++){
            fscanf(arq, "%49[^;]", generos[i]);
        }
        Leitor *l = criaLeitor(nome, generos, id, numAfinidades); 
        b->listaLeitores = adicionaLeitor(b->listaLeitores, l);
    }
    fclose(arq);
}

void comandosTxt(Booked *b){
    FILE *arq = fopen("Comandos.txt", "r");
    int funcionalidade, param1, param2, param3;
    while (sscanf(arq, "%d;""%d;""%d;""%d;", &funcionalidade, &param1, &param2, &param3)){
        Livro *livro = buscaLivro(b->catalogoLivros, param2);
        Leitor *leitor = buscaLeitor(b->listaLeitores, param1);
        
        switch (funcionalidade)
        {
        case 1:
            adicionaLivroLido(leitor, livro);
            break;
        case 2:
            adicionaLivroDesejado(leitor, livro);
            break;
        case 3:
            adicionaRecomendacaoDada(leitor, livro);
            break;
        case 4:
        //acetar recomendacoes
            break;
        case 5:
        //rejeitar recomendacoes
            break;
        case 6:
        //descobrir livro em comuns entre leitores
            break;
        case 7:
        //verificar afinidade
            break;
        case 8:
        //imprime booked
            break;

        default:
            break;
        }
    }
    fclose(arq);
}

void liberaBooked(Booked *b);
